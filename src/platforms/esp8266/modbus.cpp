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

#include "platforms/esp8266/config.h"
#include "platforms/esp8266/modbus.h"

extern RoastManager g_roast;

ModbusIP mb;

bool mbToRoastEnabled() {
    return mb.Coil(ROAST_ENABLE_ADDR);
}

double mbToSP() {
    return mb.Hreg(ROAST_SP_ADDR) / static_cast<double>(10);
}

unsigned int mbToFan() {
    return mb.Hreg(ROAST_FAN_ADDR);
}

bool mbToAutoFanEnabled() {
    return mb.Coil(AUTOFAN_ENABLE_ADDR);
}

bool mbToPIDSetup() {
    return mb.Coil(PID_SETUP_ADDR);
}

double mbToPIDKp() {
    return mb.Hreg(PID_KP_ADDR)/10;
}

double mbToPIDKi() {
    return mb.Hreg(PID_KI_ADDR)/10;
}

double mbToPIDKd() {
    return mb.Hreg(PID_KD_ADDR)/10;
}

bool mbToPIDMode() {
    return mb.Coil(PID_PONM_ADDR);
}

bool mbToPIDATune() {
    return mb.Coil(PID_ATUNE_ADDR);
}

void initModbus() {
    // NOTE(sheeprine): The modbus library is always trying connect to WiFi and
    // will not check for errors.
    // We use empty SSID and PSK as it will cancel the connection attempt but
    // still continues normal setup.
    mb.config("", "");
    mb.addCoil(ROAST_ENABLE_ADDR, false);
    mb.addIreg(ROAST_ET_ADDR);
    mb.addIreg(ROAST_BT_ADDR);
    mb.addIreg(ROAST_ROR_ADDR);
    mb.addHreg(ROAST_SP_ADDR);
    mb.addCoil(AUTOFAN_ENABLE_ADDR, false);
    mb.addHreg(ROAST_FAN_ADDR);
    mb.addCoil(PID_SETUP_ADDR, false);
    mb.addHreg(PID_KP_ADDR);
    mb.addHreg(PID_KI_ADDR);
    mb.addHreg(PID_KD_ADDR);
    mb.addCoil(PID_PONM_ADDR, false);
    mb.addCoil(PID_ATUNE_ADDR, false);
}

void addModbusCallbacks() {
    g_roast.addSetpointTempFunc(mbToSP);
    g_roast.addFanDutyFunc(mbToFan);
    g_roast.addGetAutoFanState(mbToAutoFanEnabled);
    g_roast.addRoastEnabledFunc(mbToRoastEnabled);
    g_roast.addPIDSetupFunc(mbToPIDSetup);
    g_roast.addPIDKpFunc(mbToPIDKp);
    g_roast.addPIDKiFunc(mbToPIDKi);
    g_roast.addPIDKdFunc(mbToPIDKd);
    g_roast.addPIDModeFunc(mbToPIDMode);
    g_roast.addPIDATuneFunc(mbToPIDATune);
}

void populateModbusRegisters() {
    Roaster *roasterState = g_roast.getRoasterState();
    mb.Ireg(ROAST_ET_ADDR, (unsigned int)(roasterState->getET()*10));
    mb.Ireg(ROAST_BT_ADDR, (unsigned int)(roasterState->getBT()*10));
    mb.Ireg(ROAST_ROR_ADDR, (unsigned int)(roasterState->getROR()*10));
}

void updateModbus() {
    mb.task();
}

void register_modbus() {
    registerInitCallback(addModbusCallbacks);
    registerInitCallback(initModbus);
    registerUpdateCallback(updateModbus);
    registerUpdateCallback(populateModbusRegisters);
}
