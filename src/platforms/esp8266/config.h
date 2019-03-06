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

#ifndef ESP8266_CONFIG_H
#define ESP8266_CONFIG_H

// nodemcu v0.9 pin mapping
// A0 -> Usable
// D0 -> Usable
// ~D1 -> SDA
// ~D2 -> SCL
// ~D3 -> Usable
// ~D4 -> Usable
// ~D5 -> SPI CLK
// ~D6 -> SPI Q
// ~D7 -> SPI D (Not connected)
// ~D8 -> SPI CS (Not connected)
// ~D9 -> Serial RX
// ~D10 -> Serial TX

// Thermocouples CS Pins
#define TC_ET_PIN A0
#define TC_BT_PIN D0

// Fan and heat control
#define FAN_PWM_PIN D3
#define HEATER_PIN  D4

// Modbus addresses
#define ROAST_ENABLE_ADDR 100
#define ROAST_ET_ADDR     101
#define ROAST_BT_ADDR     102
#define ROAST_ROR_ADDR    103
#define ROAST_SP_ADDR     201
#define ROAST_FAN_ADDR    202

#endif
