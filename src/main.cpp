#include "main.h"

LiquidCrystal_I2C lcd(0x27,16,2);

MAX6675 TC_ET;
MAX6675 TC_BT;

ModbusIP mb;

i2cScreen screen(&lcd);
RoastManager g_roast;
Roaster *roasterState = g_roast.getRoasterState();


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
    g_roast.addEnvTempFunc(getETTemp);
    g_roast.addBeanTempFunc(getBTTemp);
    g_roast.addSetpointTempFunc(mbToSP);
    g_roast.addFanSetDutyFunc(setFan);
    g_roast.addHeaterEnabledFunc(setHeater);
    g_roast.addRoastEnabledFunc(mbToRoastEnabled);
    g_roast.addScreen(&screen);
}

void config(void) {
    WiFiManager wManager;
    pinMode(HEATER_PIN, OUTPUT);
    pinMode(FAN_PWN_PIN, OUTPUT);
    lcd.setCursor(0, 0);
    lcd.print("      WiFi     ");
    lcd.setCursor(0, 1);
    lcd.print(" not configured ");
    wManager.autoConnect("GhettoRoaster", "gimmecoffee");
    lcd.clear();
}

void setup(void) {
    config();
    // Map to 0-100%
    analogWriteRange(100);
    initMAX6675();
    initModbus();
    initRoaster();
}

void populateModbusRegisters(void) {
    mb.Ireg(ROAST_ET_ADDR, (unsigned int)(roasterState->getET()*10));
    mb.Ireg(ROAST_BT_ADDR, (unsigned int)(roasterState->getBT()*10));
    mb.Ireg(ROAST_ROR_ADDR, (unsigned int)(roasterState->getROR()*10));
}

void loop(void) {
    screen.setWIFIStatus(WiFi.status() == WL_CONNECTED);
    g_roast.tick();
    populateModbusRegisters();
    mb.task();
    delay(1000/REFRESH_RATE);
}
