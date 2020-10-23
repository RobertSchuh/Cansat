#include <SPI.h>
#include <SD.h>
#include "i2c.h"
#include "i2c_BMP280.h"

#define N_CALIB_ACC    100
#define N_CALIB_HEIGHT  10

#define FILE_NAME "data.txt"

#define R_PIN 9
#define G_PIN 6
#define B_PIN 5

#define G_STUTTGART 9.83184

#define FILTER_ACC    0.9
#define FILTER_HEIGHT 0.9

#define DROP_CRIT_ACC    9 //5
#define DROP_CRIT_HEIGHT 1
#define DROP_TEST_DURATION 1000 // in ms 

#define CHUTE_CRIT_TIME 2000   // in ms
#define CHUTE_CRIT_HEIGHT -100 // height above ground

#define LANDED_TEST_WINDOW 100    // Number of measurements of height to decide stability of readings
#define LANDED_HEIGHT_VARIATION 1 // Largest difference between min and max reading in window that confirms landing

#define SERIAL_OUT true //Send sensor data to serial, SD, Buffer?
#define SD_DIRECT false
#define SD_BUFFER false

BMP280 bmp280;
File file;

enum State {INITIALIZATION, CLIMBING, FREEFALL, CHUTEFALL, LANDED, FAIL};
State state;

float ACC_SCALE_FACTOR = 1;
float HEIGHT__OFFSET = 0;

float reading_temperature;
float reading_pressure;
float reading_height; bool first_reading_height = true;
float reading_height_filtered;

float reading_acc_x;
float reading_acc_y;
float reading_acc_z;
float reading_acc; bool first_reading_acc = true;
float reading_acc_filtered;

void setup() {
  Serial.begin(9600);
  set_state(INITIALIZATION);
  initialize_BMP280(); // make sure that this one is called first as it is the one that contains the call to "wire.begin();"
  initialize_MPU6050();
  initialize_output();
}

void loop() {
  switch (state) {
    case INITIALIZATION:
      set_state(CLIMBING);
      break;

    case CLIMBING:
      read_BMP280(); // The next four lines take 1/25 seconds to execute
      read_MPU6050();
      apply_filter();
      output_data();
      if (test_freefall()) {
        set_state(FREEFALL);
      }
      break;

    case FREEFALL:
      read_BMP280();
      read_MPU6050();
      apply_filter();
      output_data();
      if (test_chutefall()) {
        set_state(CHUTEFALL);
      }
      break;

    case CHUTEFALL:
      read_BMP280();
      read_MPU6050();
      apply_filter();
      output_data();
      if (test_landed()) {
        set_state(LANDED);
      }
      break;

    case LANDED:
      break;

      //case FAIL: // No need to implement as long as state change to FAIL is done using set_state(...) which is the ONLY correct way
  }
}
