#ifndef WLED_NETWORK_H
#define WLED_NETWORK_H

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#else // ESP32
  #include <WiFi.h>
  #include <ETH.h>
#endif

// WLED's Network abstraction layer
// Renamed from Network to WLEDNet to avoid conflict with Arduino's Network library
class WLEDNetworkClass
{
public:
  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  void localMAC(uint8_t* MAC);
  bool isConnected();
  bool isEthernet();
};

extern WLEDNetworkClass WLEDNet;

// Legacy alias for compatibility
#define Network WLEDNet
#define NetworkClass WLEDNetworkClass

#endif // WLED_NETWORK_H