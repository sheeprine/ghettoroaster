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
#pragma once

#include <Arduino.h>
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

#define DEFAULT_MODE P_ON_E
#define DEFAULT_WARMUP_TIMEOUT_S 30
#define DEFAULT_RESOLUTION 255
#define ATUNE_WARMUP_LOOP_WAIT 100
#define ATUNE_WARMUP_THRESHOLD 1/2
#define ATUNE_STEP_RATIO 5

class GhettoPID {
   private:
  PID *mp_pid = nullptr;
  PID_ATune *mp_pidATune = nullptr;
  int m_pidMode = DEFAULT_MODE;
  unsigned int m_resolution = DEFAULT_RESOLUTION;
  unsigned int m_activationThreshold = DEFAULT_RESOLUTION / 2;
  unsigned int m_warmupTimeout = DEFAULT_WARMUP_TIMEOUT_S;
  unsigned long m_warmupTimeoutTime = 0;
  unsigned short m_warmupTempCheck = 0;
  bool m_autoTune = false;
  double m_lastIN, m_IN, m_OUT, m_SET, m_kP, m_kI, m_kD = 0;
  void init();
  void warmup();
  bool isTempRaising();
  void finalizeAutotune();

   public:
  GhettoPID(double kP, double kI, double kD);
  ~GhettoPID();
  void startAutotune();
  void cancelAutotune();
  void setTunings(double kp, double ki, double kd, int mode);
  void setThreshold(unsigned int threshold);
  void setResolution(unsigned int resolution);
  void reset();
  void enable();
  void disable();
  bool isEnabled();
  void setInput(double IN);
  void setSetPoint(double SET);
  double getSetPoint();
  double getOutput();
  bool isOutputActivated();
  void update();
};
