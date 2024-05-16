#pragma once

#include "Config.h"
#include "Wire.h"
#include <MPU6050_light.h>

struct AccelerometerData
{
  float x;
  float y;
  float z;
};

struct GyroscopeData
{
  float x;
  float y;
  float z;
};

struct AccAngleData
{
  float x;
  float y;
};

class MPU
{
private:
  MPU6050 mpu_;

public:
  MPU(uint8_t addr) : mpu_(Wire)
  {
    mpu_.setAddress(addr);
    byte status = mpu_.begin(MPU_CONFIG_GYR, MPU_CONFIG_ACC);
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while (status != 0)
    {
    } // stop everything if could not connect to MPU6050

    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu_.calcOffsets(true, true);
    Serial.println("Done!\n");
  }

  void update()
  {
    mpu_.update();
  }

  AccAngleData getAccAngle()
  {
    AccAngleData data;
    data.x = mpu_.getAccAngleX();
    data.y = mpu_.getAccAngleY();
    return data;
  }
  AccelerometerData getAccelerometerData()
  {
    AccelerometerData data;
    data.x = mpu_.getAccX();
    data.y = mpu_.getAccY();
    data.z = mpu_.getAccZ();
    return data;
  }

  GyroscopeData getGyroscopeData()
  {
    GyroscopeData data;
    data.x = mpu_.getGyroX();
    data.y = mpu_.getGyroY();
    data.z = mpu_.getGyroZ();
    return data;
  }
};