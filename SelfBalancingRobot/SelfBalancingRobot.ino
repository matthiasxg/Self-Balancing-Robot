#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#include "MotorCallback.h"
#include "ServerCallback.h"
#include "Config.h"

#include "MPUControl.h"

int acc = 0;
float t = 0;
BLECharacteristic *characteristic_acc = NULL;
BLECharacteristic *characteristic_motor = NULL;

unsigned long timer = 0;

void createServices(BLEServer *server)
{
  Serial.print("Creating services... ");

  createEnvironmentService(server);
  createControlService(server);

  Serial.println("Done");
}

void createEnvironmentService(BLEServer *server)
{
  BLEService *environment_service = server->createService(SERVICE_ENVIRONMENT_UUID);

  characteristic_acc = environment_service->createCharacteristic(CHARACTERISTIC_ACC_UUID,
                                                                 BLECharacteristic::PROPERTY_READ |
                                                                     // BLECharacteristic::PROPERTY_INDICATE | // if we want to have the characteristic acknowledged
                                                                     BLECharacteristic::PROPERTY_NOTIFY);

  characteristic_acc->addDescriptor(new BLE2902());

  environment_service->start();
}

void createControlService(BLEServer *server)
{
  BLEService *environment_service = server->createService(SERVICE_CONTROL_UUID);

  characteristic_motor = environment_service->createCharacteristic(CHARACTERISTIC_MOTOR_UUID,
                                                                   BLECharacteristic::PROPERTY_WRITE);

  // add callback for motor control
  characteristic_motor->setCallbacks(new MotorCallback());
  characteristic_motor->addDescriptor(new BLE2902());

  environment_service->start();
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Setup BLE");

  BLEDevice::init("Self balancing robot");
  BLEServer *server = BLEDevice::createServer();
  BLEServerCallbackHandler *ServerCallbackHandler = new BLEServerCallbackHandler();
  server->setCallbacks(ServerCallbackHandler);

  createServices(server);

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_ENVIRONMENT_UUID);
  pAdvertising->addServiceUUID(SERVICE_CONTROL_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("Setup TMC");

  pinMode(TMC_1_ENABLE, OUTPUT);
  pinMode(TMC_1_STEP, OUTPUT);
  pinMode(TMC_1_DIR, OUTPUT);
  digitalWrite(TMC_1_ENABLE, LOW);

  Serial.println("Setup done");
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(1000);

  AccAngleData accAngleData = MPUControl::getInstance().getAccAngle();
  Serial.print("AccAngleX: ");
  Serial.print(accAngleData.x);
  Serial.print("\tAccAngleY: ");
  Serial.println(accAngleData.y);

  AccelerometerData accData = MPUControl::getInstance().getAccelerometerData();
  Serial.print("AccX: ");
  Serial.print(accData.x);
  Serial.print("\tAccY: ");
  Serial.print(accData.y);
  Serial.print("\tAccZ: ");
  Serial.println(accData.z);

  GyroscopeData gyroData = MPUControl::getInstance().getGyroscopeData();
  Serial.print("GyroX: ");
  Serial.print(gyroData.x);
  Serial.print("\tGyroY: ");
  Serial.print(gyroData.y);
  Serial.print("\tGyroZ: ");
  Serial.println(gyroData.z);

  if (accAngleData.y < -80)
  {
    MotorControl::getInstance().drive(STEPS_PER_REVOLUTION, 200, true);
  }
}