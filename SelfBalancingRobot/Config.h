#pragma once

// BLE
#define SERVICE_ENVIRONMENT_UUID "70a9dda7-b73c-42cb-9ef3-a452d0844d10"
#define CHARACTERISTIC_ACC_UUID "e72b4c33-50cb-4440-8f17-2a9bed3cf63a"

#define SERVICE_CONTROL_UUID "74741977-c0c4-4f8a-9831-a261f8b83d16"
#define CHARACTERISTIC_MOTOR_UUID "c7c70dec-ee2d-4212-8183-49060f283bff"

// Motors
const int TMC_1_ENABLE = 32;
const int TMC_1_STEP = 25;
const int TMC_1_DIR = 12;

const int TMC_2_ENABLE = 33;
const int TMC_2_STEP = 26;
const int TMC_2_DIR = 13;

const int STEPS_PER_REVOLUTION = 3200;

// MPU
const int MPU_ADDRESS_1 = 0x68;
const int MPU_ADDRESS_2 = 0x69;

const int MPU_CONFIG_ACC = 1;
const int MPU_CONFIG_GYR = 1;