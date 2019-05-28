/*
Copyright 2019 Stephane Albert

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "pid.h"

GhettoPID::GhettoPID(double kP, double kI, double kD) : m_kP(kP), m_kI(kI), m_kD(kD) {
  init();
}

GhettoPID::~GhettoPID() {
  delete mp_pid;
  delete mp_pidATune;
}

void GhettoPID::init() {
  if (mp_pid) {
    delete mp_pid;
    mp_pid = nullptr;
  }
  mp_pid = new PID(&m_IN, &m_OUT, &m_SET, m_kP, m_kI, m_kD, m_pidMode, DIRECT);
  setResolution(m_resolution);
}

void GhettoPID::reset() {
  if (isEnabled()) {
    mp_pid->SetMode(MANUAL);
    mp_pid->SetMode(AUTOMATIC);
  }
}

void GhettoPID::setTunings(double kp, double ki, double kd, int mode) {
  m_kP = kp;
  m_kI = ki;
  m_kD = kd;
  m_pidMode = mode;
  mp_pid->SetTunings(kp, ki, kd, mode);
}

void GhettoPID::setThreshold(unsigned int threshold) {
  m_activationThreshold = threshold;
}

bool GhettoPID::isTempRaising() {
  if (m_warmupTempCheck < ATUNE_WARMUP_LOOP_WAIT)
    return ++m_warmupTempCheck;
  // NOTE(sheeprine): If temperature moved less than ATUNE_WARMUP_THRESHOLD
  // between checks then consider it flat.
  bool tempChanged = m_lastIN < (m_IN - ATUNE_WARMUP_THRESHOLD);
  m_warmupTempCheck = 0;
  m_lastIN = m_IN;
  return tempChanged;
}

void GhettoPID::warmup() {
#ifdef DEBUG
  Serial.println("Starting PID Auto Tune, warming up.");
#endif
  m_OUT = m_resolution/2;
  m_warmupTimeoutTime = millis() + m_warmupTimeout;
  m_autoTune = true;
  m_lastIN = m_IN;
}

void GhettoPID::startAutotune() {
  // Disable PID before starting auto tuning
  mp_pid->SetMode(MANUAL);
  if (!m_autoTune)
    warmup();
  if (!mp_pidATune && !m_warmupTimeoutTime) {
    mp_pidATune = new PID_ATune(&m_IN, &m_OUT);
    // NOTE(sheeprine): Tune for full P I D
    mp_pidATune->SetControlType(1);
    mp_pidATune->SetOutputStep(m_resolution/ATUNE_STEP_RATIO);
    mp_pidATune->SetLookbackSec(30);
    mp_pidATune->SetNoiseBand(1);
  }
}

void GhettoPID::finalizeAutotune() {
#ifdef DEBUG
  Serial.println("PID AutoTune done.");
  Serial.print("Kp: ");
  Serial.println(mp_pidATune->GetKp());
  Serial.print("Ki: ");
  Serial.println(mp_pidATune->GetKi());
  Serial.print("Kd: ");
  Serial.println(mp_pidATune->GetKd());
#endif
  mp_pid->SetTunings(
    mp_pidATune->GetKp(),
    mp_pidATune->GetKi(),
    mp_pidATune->GetKd());
  cancelAutotune();
}

void GhettoPID::cancelAutotune() {
  m_autoTune = false;
  if (mp_pidATune) {
    mp_pidATune->Cancel();
    delete mp_pidATune;
    mp_pidATune = nullptr;
  }
  m_OUT = 0;
}

void GhettoPID::enable() {
  mp_pid->SetMode(AUTOMATIC);
}

void GhettoPID::disable() {
  mp_pid->SetMode(MANUAL);
  m_OUT = 0;
}

bool GhettoPID::isEnabled() {
  return (mp_pid->GetMode() == AUTOMATIC);
}

void GhettoPID::setInput(double IN) {
  m_IN = IN;
}

void GhettoPID::setSetPoint(double SP) {
  m_SET = SP;
}

double GhettoPID::getSetPoint() {
  return m_SET;
}

double GhettoPID::getOutput() {
  return m_OUT;
}

bool GhettoPID::isOutputActivated() {
    // FIXME(sheeprine): Using a threshold on the PID output as PWM is
    // inefficient on Zero Cross SSR. We should implement something more robust
    // and customizable.
    return m_OUT > m_activationThreshold;
}

void GhettoPID::setResolution(unsigned int resolution) {
  m_resolution = resolution;
  mp_pid->SetOutputLimits(0, m_resolution);
}

void GhettoPID::update() {
  if (m_autoTune) {
    // NOTE(sheeprine): Check if warmup condition is met.
    if (m_warmupTimeoutTime) {
      if (!isTempRaising()) {
        m_warmupTimeoutTime = 0;
        startAutotune();
      }
    }
    if (mp_pidATune && mp_pidATune->Runtime())
      finalizeAutotune();
  }
  else {
    mp_pid->Compute();
  }
}
