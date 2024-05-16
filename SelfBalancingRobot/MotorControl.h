#pragma once

#include "Motor.h"
#include "Config.h"

class MotorControl
{

private:
  Motor left_;
  Motor right_;

  MotorControl()
      : left_(TMC_2_ENABLE, TMC_2_STEP, TMC_2_DIR),
        right_(TMC_1_ENABLE, TMC_1_STEP, TMC_1_DIR)
  {
  }

public:
  static MotorControl &getInstance()
  {
    static MotorControl instance;
    return instance;
  }

  MotorControl(const MotorControl &) = delete;
  MotorControl &operator=(const MotorControl &) = delete;

  void drive(int steps, int speed, bool clockwise)
  {
    for (int i = 0; i < steps; i++)
    {
      left_.drive(1, speed, clockwise);
      right_.drive(1, speed, !clockwise);
    }
  }
};
