#include "platforms/esp8266/config.h"
#include "platforms/esp8266/modbus.h"

extern RoastManager g_roast;

ModbusIP mb;

bool mbToRoastEnabled() {
    return mb.Coil(ROAST_ENABLE_ADDR);
}

double mbToSP(void) {
    return mb.Hreg(ROAST_SP_ADDR) / 10;
}

unsigned int mbToFan() {
    return mb.Hreg(ROAST_FAN_ADDR);
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
    mb.addHreg(ROAST_FAN_ADDR);
}

void addModbusCallbacks() {
    g_roast.addSetpointTempFunc(mbToSP);
    g_roast.addRoastEnabledFunc(mbToRoastEnabled);
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
