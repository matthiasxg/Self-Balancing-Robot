#pragma once

#include "MPU.h"
#include "Config.h"

class MPUControl
{
private:
  MPU mpu1_;
  MPU mpu2_;

  MPUControl() : mpu1_(MPU_ADDRESS_1), mpu2_(MPU_ADDRESS_2) {}

  float mergeValues(float value1, float value2)
  {
    return (value1 + value2) / 2;
  }

public:
  static MPUControl &getInstance()
  {
    static MPUControl instance;
    instance.update();
    return instance;
  }

  MPUControl(const MPUControl &) = delete;
  MPUControl &operator=(const MPUControl &) = delete;

  void update()
  {
    mpu1_.update();
    mpu2_.update();
  }

  AccAngleData getAccAngle()
  {
    AccAngleData data1 = mpu1_.getAccAngle();
    AccAngleData data2 = mpu2_.getAccAngle();
    AccAngleData mergedData;
    mergedData.x = mergeValues(data1.x, data2.x);
    mergedData.y = mergeValues(data1.y, data2.y);
    return mergedData;
  }

  AccelerometerData getAccelerometerData()
  {
    AccelerometerData data1 = mpu1_.getAccelerometerData();
    AccelerometerData data2 = mpu2_.getAccelerometerData();
    AccelerometerData mergedData;
    mergedData.x = mergeValues(data1.x, data2.x);
    mergedData.y = mergeValues(data1.y, data2.y);
    mergedData.z = mergeValues(data1.z, data2.z);
    return mergedData;
  }

  GyroscopeData getGyroscopeData()
  {
    GyroscopeData data1 = mpu1_.getGyroscopeData();
    GyroscopeData data2 = mpu2_.getGyroscopeData();
    GyroscopeData mergedData;
    mergedData.x = mergeValues(data1.x, data2.x);
    mergedData.y = mergeValues(data1.y, data2.y);
    mergedData.z = mergeValues(data1.z, data2.z);
    return mergedData;
  }
};