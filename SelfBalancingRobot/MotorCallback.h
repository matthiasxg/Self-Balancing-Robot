#pragma once

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "Config.h"
#include "MotorControl.h"

class MotorCallback : public BLECharacteristicCallbacks
{

  void onWrite(BLECharacteristic *characteristic)
  {
    std::string value = characteristic->getValue();
    uint8_t *data = characteristic->getData();
    if (value.length() > 0)
    {
      Serial.print("Motor event, written: \'");
      for (int i = 0; i < value.length(); i++)
      {
        Serial.print(value[i]);
      }
      Serial.print("\'[str]; \'");
      for (int i = 0; i < characteristic->getLength(); i++)
      {
        Serial.print(data[i]);
      }
      Serial.print("\'[uint8_t];");
    }
    Serial.println();

    MotorControl::getInstance().drive(STEPS_PER_REVOLUTION, 200, true);
  }
};
