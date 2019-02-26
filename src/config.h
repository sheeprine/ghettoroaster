#ifndef CONFIG_H
#define CONFIG_H

// Number of time per second to refresh the roast state
#define REFRESH_RATE 10

// Fan and heat control
#define FAN_PWN_PIN D0
#define HEATER_PIN D1

// Thermocouples CS Pins
#define TC_ET_PIN D3
#define TC_BT_PIN D4

// Modbus addresses
#define ROAST_ENABLE_ADDR 100
#define ROAST_ET_ADDR 101
#define ROAST_BT_ADDR 102
#define ROAST_ROR_ADDR 103
#define ROAST_SP_ADDR 201
#define ROAST_FAN_ADDR 202

#endif
