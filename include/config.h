#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>



#define AP_SSID "fshg-ap-1"
#define AP_PASS "fshg-ap-1" 

#define UDP_IP "192.168.4.255" 
#define UDP_PORT 12345

// Hardware Pin Mapping 
#define BME_SCK  6
#define BME_MISO 5  // SDI
#define BME_MOSI 7  // SDO
#define BME_CS   8

#define OTHER_CS 10 

#define POLLING_RATE_MS 2000

#endif