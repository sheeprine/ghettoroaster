#include "main.h"

LiquidCrystal_I2C lcd(0x27,16,2);

MAX6675 TC_ET;
MAX6675 TC_BT;

ModbusIP mb;

i2cScreen screen(&lcd);
RoastManager roast;
Roaster *roasterState = roast.getRoasterState();


bool mbToRoastEnabled(void) { return mb.Coil(ROAST_ENABLE_ADDR); }
double mbToSP(void) { return mb.Hreg(ROAST_SP_ADDR) / 10; }
unsigned int mbToFan(void) { return mb.Hreg(ROAST_FAN_ADDR); }
double getETTemp(void) { return TC_ET.readCelsius(); }
double getBTTemp(void) { return TC_BT.readCelsius(); }
void setFan(unsigned int dutyCycle) { analogWrite(FAN_PWN_PIN, dutyCycle); }
void setHeater(bool enabled) { digitalWrite(HEATER_PIN, enabled); }

void initMAX6675(void) {
    SPI.begin();
    TC_ET.begin(TC_ET_PIN);
    TC_BT.begin(TC_BT_PIN);
}

void initModbus(void) {
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

void initRoaster(void) {
    roast.addEnvTempFunc(getETTemp);
    roast.addBeanTempFunc(getBTTemp);
    roast.addSetpointTempFunc(mbToSP);
    roast.addFanSetDutyFunc(setFan);
    roast.addHeaterEnabledFunc(setHeater);
    roast.addRoastEnabledFunc(mbToRoastEnabled);
    roast.addScreen(&screen);
}

void setup(void) {
    // Map to 0-100%
    analogWriteRange(100);
    initMAX6675();
    initModbus();
    initRoaster();
}

void populateModbusRegisters(void) {
    mb.Ireg(ROAST_ET_ADDR, roasterState->getET());
    mb.Ireg(ROAST_BT_ADDR, roasterState->getBT());
    mb.Ireg(ROAST_ROR_ADDR, roasterState->getROR());
}

void loop(void) {
    screen.setWIFIStatus(WiFi.isConnected());
    roast.tick();
    populateModbusRegisters();
    mb.task();
    delay(1000/REFRESH_RATE);
}
