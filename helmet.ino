#include <SPI.h>
#include <Wire.h>
#include <Adafruit_LSM9DS0.h>
#include "Adafruit_NeoPixel_Custom.h"

#define PIN 6
#define RED   strip.Color(0xFF,0x00,0x00)
#define AMBER strip.Color(0xFF,0x37,0x00)
#define WHITE strip.Color(0xFF,0xFF,0xFF)
#define BLACK strip.Color(0,0,0)
#define PERIOD 2500

#define INPUT_MODE_NONE 1
#define INPUT_MODE_NOD  2

#define OUTPUT_MODE_NORMAL     1
#define OUTPUT_MODE_LEFT_TURN  2
#define OUTPUT_MODE_RIGHT_TURN 3

Adafruit_NeoPixel_Custom strip = Adafruit_NeoPixel_Custom(60, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);
uint8_t input_mode  = INPUT_MODE_NONE;
uint8_t output_mode = OUTPUT_MODE_NORMAL;

void setup() {
  Serial.begin(115200);
  //while (!Serial);
  
  lsm.begin();
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
  
  strip.begin();
  strip.setBrightness(0x7F);
  strip.show();
}

void loop() {
  sensor_t s_accel, s_mag, s_gyro, s_temp;
//  lsm.getSensor(&s_accel, &s_mag, &s_gyro, &s_temp);
  Serial.println(s_accel.min_delay);
  
  sensors_event_t accel, mag, gyro, temp;
//  lsm.getEvent(&accel, &mag, &gyro, &temp);
  
//  Serial.println(accel.acceleration.y);
//  strip.setBrightness(255 * (accel.acceleration.y+1));
  
  /*
  switch (input_mode) {
    default:
    case INPUT_MODE_NONE:
      if (gyro.gyro.x > 50) {
        input_mode = INPUT_MODE_NOD;
      }
      break;
    
    case INPUT_MODE_NOD:
      if (gyro.gyro.x > 50) {
        input_mode =  INPUT_MODE_NONE;
        output_mode = OUTPUT_MODE_NORMAL;
      }
      if (gyro.gyro.z > 50) {
        input_mode  = INPUT_MODE_NONE;
        output_mode = OUTPUT_MODE_LEFT_TURN;
      }
      if (gyro.gyro.z < -50) {
        input_mode  = INPUT_MODE_NONE;
        output_mode = OUTPUT_MODE_RIGHT_TURN;
      }
  }
  */
  
  /*
  switch (output_mode) {
    default:
    case OUTPUT_MODE_NORMAL:
      pattern_default();
      break;
    
    case OUTPUT_MODE_LEFT_TURN: 
      pattern_left_turn();
      break;
      
    case OUTPUT_MODE_RIGHT_TURN:
      pattern_right_turn();
      break;
  }
  */
  
  pattern_default();
  strip.show();
//  delay(10);
}

void solid(int a, int b, uint32_t color) {solid(a,b,color,255);}
void solid(int a, int b, uint32_t color, uint8_t brightness)
{
  int count = abs(a-b)+1;
  for (int i = 0; i < abs(a-b)+1; i++) {
    int pixel = map(i, 0, count-1, a, b);
    strip.setPixelColor(pixel, color, brightness);
  }
}

void chase(int a, int b, uint32_t color) {chase(a,b,color,255,10);}
void chase(int a, int b, uint32_t color, uint8_t brightness, uint8_t width)
{
  int count = abs(a-b)+1;
  float t = (float)(millis()%PERIOD)/PERIOD;
  float centera = (float)count * (t-1);
  float centerb = (float)count * (t);
  float centerc = (float)count * (t+1);
  
  for (int i = 0; i < abs(a-b)+1; i++) {
    float f = 0
            + max(0,(1-abs(centera-i)/width))
            + max(0,(1-abs(centerb-i)/width))
            + max(0,(1-abs(centerc-i)/width))
            ;
    f = pow(f,2.5);
    
    int pixel = map(i, 0, count-1, a, b);
    strip.setPixelColor(pixel, color, f*brightness);
  }
}

void pulse(int a, int b, uint32_t color) {pulse(a,b,color,255);}
void pulse(int a, int b, uint32_t color, uint8_t brightness)
{
  int count = abs(a-b)+1;
  float t = (float)(millis()%PERIOD)/PERIOD;
  float f = abs(sin(t*3.14));
  f = pow(f, 2.5);
  f = 0.5 + 0.5*f;
  for (int i = 0; i < abs(a-b)+1; i++) {
    int pixel = map(i, 0, count-1, a, b);
    strip.setPixelColor(pixel, color, f*brightness);
  }
}

void pattern_default()
{
  pulse( 0,  4, RED);
  chase(19,  4, AMBER);
  pulse(20, 27, WHITE, 127);
  chase(28, 43, AMBER);
  pulse(44, 48, RED);
}

void pattern_left_turn()
{ 
  chase(0,  11, AMBER, 255, 6);
  chase(23, 12, AMBER, 255, 6);
  solid(24, 48, BLACK);
  chase(30, 24, AMBER, 127, 3);
  chase(42, 48, AMBER, 127, 3);
}

void pattern_right_turn()
{
  chase(24, 35, AMBER, 255, 6);
  chase(48, 36, AMBER, 255, 6);
  solid( 0, 23, BLACK);
  chase( 5,  0, AMBER, 127, 3);
  chase(18, 23, AMBER, 127, 3);
}

void pattern_disco()
{
  for (int i=0; i<48; i++) {
    strip.setPixelColor(
      i,
      strip.Color(random(0x00,0xFF),
                  random(0x00,0xFF),
                  random(0x00,0xFF)),
      random(0xF0,0xFF)
    );
    strip.show();
  }
}
