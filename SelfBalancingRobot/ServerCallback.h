#pragma once

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class BLEServerCallbackHandler : public BLEServerCallbacks 
{
  void onConnect(BLEServer* server) 
  {
    Serial.println("New device connected. Currently connected Devices: " + String(server->getConnectedCount() + 1) + "\n");
  }
  void onDisconnect(BLEServer* server)
  {
    Serial.println("Device disconnected. Currently connected Devices: " + String(server->getConnectedCount() - 1) + "\n");
      BLEDevice::startAdvertising();
  }
};