#pragma once

class Motor {
private:
  int enablePin_;
  int stepPin_;
  int dirPin_;
public:
  Motor(int enablePin, int stepPin, int dirPin)
        : enablePin_(enablePin), stepPin_(stepPin), dirPin_(dirPin)
  {
    pinMode(enablePin_, OUTPUT);
    pinMode(stepPin_, OUTPUT);
    pinMode(dirPin_, OUTPUT);
    digitalWrite(enablePin_, LOW);
  }

  void drive(int steps, int speed, bool clockwise) 
  {
    digitalWrite(dirPin_, clockwise ? HIGH : LOW);

    for (int i = 0; i < steps; i++) 
    {
      digitalWrite(stepPin_, HIGH);
      delayMicroseconds(speed);
      digitalWrite(stepPin_, LOW);
      delayMicroseconds(speed);
    }
  }
};
