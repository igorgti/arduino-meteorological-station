#include <Wire.h>
#include <dht.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

//Definicoes do sensor de pressao e temperatura
Adafruit_BMP280 bmp;

//Definicoes do display Oled
Adafruit_SSD1306 display = Adafruit_SSD1306();

//Definicoes do sensor temperatura e umidade
dht DHT;

#define DHT11_PIN 2
#define BTNRED_PIN 3
#define BTNWHITE_PIN 4
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)


/*
#define red 4
#define yellow 3
#define green 2
*/

const uint8_t storm[] PROGMEM = {

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF,
0x80, 0x00, 0x00, 0x00, 0x07, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x60, 0x00, 0x00, 0x00,
0x0C, 0x00, 0x60, 0x00, 0x00, 0x00, 0x18, 0x00, 0x30, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x00,
0x00, 0x00, 0x10, 0x00, 0x18, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x1E, 0x00, 0x00, 0x07, 0xE0, 0x00,
0x0F, 0x00, 0x00, 0x0C, 0x00, 0x04, 0x01, 0x80, 0x00, 0x18, 0x00, 0x0C, 0x00, 0xC0, 0x00, 0x18,
0x00, 0x1C, 0x00, 0x40, 0x00, 0x10, 0x00, 0x1C, 0x00, 0x60, 0x00, 0x30, 0x00, 0x3C, 0x00, 0x60,
0x00, 0x30, 0x00, 0x6C, 0x00, 0x60, 0x00, 0x30, 0x00, 0xCC, 0x00, 0x60, 0x00, 0x10, 0x00, 0xCC,
0x00, 0x60, 0x00, 0x10, 0x01, 0x88, 0x00, 0x40, 0x00, 0x18, 0x03, 0x08, 0x00, 0xC0, 0x00, 0x0C,
0x06, 0x08, 0x01, 0x80, 0x00, 0x07, 0x06, 0x1F, 0xC3, 0x80, 0x00, 0x03, 0xFC, 0x0F, 0xFE, 0x00,
0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x1F, 0x83, 0x00, 0x00, 0x00, 0x00, 0x01, 0x86,
0x00, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x8C, 0x30, 0x00, 0x00, 0x03,
0xC1, 0x18, 0x78, 0x00, 0x00, 0x07, 0xC1, 0x30, 0xF8, 0x00, 0x00, 0x0C, 0xC3, 0x31, 0x98, 0x00,
0x00, 0x08, 0x83, 0x63, 0x18, 0x00, 0x00, 0x18, 0x83, 0xC3, 0x10, 0x00, 0x00, 0x19, 0x83, 0x83,
0x30, 0x00, 0x00, 0x0F, 0x83, 0x01, 0xF0, 0x00, 0x00, 0x07, 0x07, 0x00, 0xE0, 0x00, 0x00, 0x00,
0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};
const uint8_t pressure[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x00,
0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x3F, 0xC0, 0x03, 0xFC, 0x00, 0x00, 0x7E, 0x03, 0xC0,
0x7E, 0x00, 0x00, 0xF8, 0x03, 0xC0, 0x1F, 0x00, 0x01, 0xF0, 0x03, 0xC0, 0x0F, 0x80, 0x03, 0xE6,
0x03, 0xC0, 0x67, 0xC0, 0x07, 0xCE, 0x03, 0xC0, 0x73, 0xE0, 0x0F, 0x8F, 0x03, 0xC0, 0xF1, 0xF0,
0x0F, 0x07, 0x83, 0xC1, 0xE0, 0xF0, 0x1E, 0x07, 0xC0, 0x03, 0xE0, 0x78, 0x1C, 0x03, 0xC0, 0x03,
0xC0, 0x38, 0x3C, 0x01, 0x80, 0x01, 0x80, 0x3C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x78, 0x00,
0x00, 0x00, 0x00, 0x1E, 0x7B, 0x80, 0x01, 0x80, 0x01, 0xDE, 0x73, 0xF0, 0x01, 0x80, 0x0F, 0xCE,
0x73, 0xF8, 0x01, 0x80, 0x1F, 0xCE, 0xF1, 0xF8, 0x01, 0x80, 0x1F, 0x8F, 0xF0, 0x30, 0x01, 0x80,
0x0C, 0x0F, 0xE0, 0x00, 0x01, 0x80, 0x00, 0x07, 0xE0, 0x00, 0x03, 0xC0, 0x00, 0x07, 0xE0, 0x00,
0x03, 0xC0, 0x00, 0x07, 0xE0, 0x00, 0x03, 0xC0, 0x00, 0x07, 0xF0, 0x00, 0x03, 0xC0, 0x00, 0x0F,
0xF0, 0xF0, 0x03, 0xC0, 0x0F, 0x0F, 0xF3, 0xF8, 0x07, 0xE0, 0x1F, 0xCF, 0x73, 0xF8, 0x0F, 0xF0,
0x1F, 0xCE, 0x73, 0xC0, 0x1F, 0xF8, 0x03, 0xCE, 0x78, 0x00, 0x1F, 0xF8, 0x00, 0x1E, 0x38, 0x00,
0x1F, 0xF8, 0x00, 0x1C, 0x38, 0x00, 0x1F, 0xF8, 0x00, 0x1C, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00,
0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t rain[] PROGMEM = {

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x18, 0x00, 0x00,
0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x00, 0x00, 0x60, 0x02, 0x00, 0x00, 0x00, 0x00, 0x40, 0x03,
0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x07, 0x80, 0x01, 0x80, 0x00, 0x00, 0x1E,
0x00, 0x00, 0xE0, 0x00, 0x00, 0x30, 0x00, 0x00, 0x18, 0x00, 0x00, 0x60, 0x00, 0x00, 0x08, 0x00,
0x00, 0x40, 0x00, 0x00, 0x0C, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x04, 0x00, 0x00, 0xC0, 0x00, 0x00,
0x04, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x04, 0x00, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x00, 0x40,
0x00, 0x00, 0x0C, 0x00, 0x00, 0x60, 0x00, 0x00, 0x18, 0x00, 0x00, 0x38, 0x00, 0x00, 0x30, 0x00,
0x00, 0x0F, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x01,
0x80, 0x00, 0x00, 0x0F, 0x07, 0x03, 0xC0, 0x00, 0x00, 0x1B, 0x09, 0x04, 0xC0, 0x00, 0x00, 0x32,
0x19, 0x0C, 0x80, 0x00, 0x00, 0x32, 0x19, 0x0C, 0x80, 0x00, 0x00, 0x1E, 0x0F, 0x07, 0x00, 0x00,
0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x70, 0x00, 0x00, 0x00, 0x00, 0xA0, 0xD0,
0x00, 0x00, 0x00, 0x03, 0xA1, 0x10, 0x00, 0x00, 0x00, 0x02, 0x21, 0x30, 0x00, 0x00, 0x00, 0x03,
0x61, 0xB0, 0x00, 0x00, 0x00, 0x01, 0xC0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t temp[] PROGMEM = {

0x00, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0xF9, 0xE0,
0x00, 0x00, 0x00, 0x01, 0xE0, 0x70, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x70, 0x00, 0x00, 0x00, 0x03,
0x80, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x80, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x80, 0x38, 0x00, 0x00,
0x00, 0x03, 0x80, 0x38, 0x00, 0x00, 0x00, 0x03, 0x80, 0x38, 0x00, 0x00, 0x00, 0x03, 0x80, 0x39,
0xFC, 0x00, 0x00, 0x03, 0x80, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x8E, 0x38, 0x00, 0x00, 0x00, 0x03,
0x9F, 0x38, 0x00, 0x00, 0x00, 0x03, 0x9F, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x9F, 0x39, 0xFC, 0x00,
0x00, 0x03, 0x9F, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x9F, 0x38, 0x00, 0x00, 0x00, 0x03, 0x9F, 0x38,
0x00, 0x00, 0x00, 0x03, 0x9F, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x9F, 0x39, 0xFC, 0x00, 0x00, 0x03,
0x9F, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x9F, 0x38, 0x00, 0x00, 0x00, 0x03, 0x9F, 0x38, 0x00, 0x00,
0x00, 0x03, 0x9F, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x9F, 0x39, 0xFC, 0x00, 0x00, 0x03, 0x9F, 0x38,
0x00, 0x00, 0x00, 0x07, 0x9F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x1E, 0x00, 0x00, 0x00, 0x1E,
0x3F, 0x87, 0x00, 0x00, 0x00, 0x1C, 0x7F, 0xC7, 0x00, 0x00, 0x00, 0x38, 0xFF, 0xE3, 0x80, 0x00,
0x00, 0x39, 0xFF, 0xF3, 0x80, 0x00, 0x00, 0x31, 0xFF, 0xF1, 0x80, 0x00, 0x00, 0x73, 0xFF, 0xF9,
0xC0, 0x00, 0x00, 0x73, 0xFF, 0xF9, 0xC0, 0x00, 0x00, 0x73, 0xFF, 0xF9, 0xC0, 0x00, 0x00, 0x73,
0xFF, 0xF9, 0xC0, 0x00, 0x00, 0x31, 0xFF, 0xF1, 0x80, 0x00, 0x00, 0x39, 0xFF, 0xF1, 0x80, 0x00,
0x00, 0x38, 0xFF, 0xE3, 0x80, 0x00, 0x00, 0x1C, 0x7F, 0xC7, 0x00, 0x00, 0x00, 0x1E, 0x3F, 0x87,
0x00, 0x00, 0x00, 0x0F, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x07, 0x80, 0x3C, 0x00, 0x00, 0x00, 0x03,
0xF1, 0xF8, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00

};
const uint8_t sunny[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x04, 0x00, 0x00, 0x00, 0x00,
0x83, 0x04, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08, 0x00, 0x00,
0x00, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x10, 0x30, 0x38, 0x20, 0x00, 0x00, 0x18, 0xC0, 0x0C,
0x60, 0x00, 0x00, 0x0C, 0x80, 0x04, 0xC0, 0x00, 0x00, 0x01, 0x80, 0x02, 0x00, 0x00, 0x00, 0x01,
0x00, 0x03, 0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00,
0x00, 0x72, 0x00, 0x01, 0x38, 0x00, 0x00, 0x72, 0x00, 0x01, 0x38, 0x00, 0x00, 0x02, 0x00, 0x01,
0x00, 0x00, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01,
0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x80, 0x06, 0x80, 0x00, 0x00, 0x1C, 0xC0, 0x0C, 0xE0, 0x00,
0x00, 0x10, 0x70, 0x38, 0x20, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x08,
0x00, 0x00, 0x00, 0x00, 0x43, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x83, 0x04, 0x00, 0x00, 0x00, 0x00,
0x83, 0x04, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};
const uint8_t cloudy[] PROGMEM = {

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x40, 0x00,
0x00, 0x00, 0x03, 0x08, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x3C,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x31, 0x81, 0x8C, 0x00, 0x00, 0x00,
0x1B, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x02, 0x00, 0x60, 0x00, 0x00, 0x00, 0x06, 0x00, 0x20, 0x00,
0x00, 0x00, 0x3F, 0x80, 0x20, 0x00, 0x00, 0x00, 0xE0, 0xC0, 0x10, 0x00, 0x00, 0x00, 0x80, 0x60,
0x17, 0x00, 0x00, 0x01, 0x80, 0x30, 0x10, 0x00, 0x00, 0x03, 0x00, 0x10, 0x10, 0x00, 0x00, 0x02,
0x00, 0x10, 0x20, 0x00, 0x00, 0x1E, 0x00, 0x1C, 0x20, 0x00, 0x00, 0x7C, 0x00, 0x0E, 0x48, 0x00,
0x00, 0xC0, 0x00, 0x01, 0xCC, 0x00, 0x00, 0x80, 0x00, 0x01, 0x84, 0x00, 0x01, 0x80, 0x00, 0x00,
0x80, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x01, 0x00,
0x00, 0x00, 0xC0, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x80, 0x00,
0x00, 0xC0, 0x00, 0x01, 0x80, 0x00, 0x00, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFE,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};
const uint8_t hum[] PROGMEM = {
0x32, 0x00, 0x34, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x10, 
};
void setup(){
  display.setTextSize(1); 
  Serial.begin(9600);
  Wire.begin();
  bmp.begin(0x76);
  pinMode(BTNRED_PIN, INPUT);
  pinMode(BTNWHITE_PIN, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  
   //Display Oled
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Loop eterno
  }
  
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}
void topLogo(){
  display.setTextSize(2); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  display.setCursor(33,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Tempo");
}
void generalInfo(){
  int chk = DHT.read11(DHT11_PIN);

  topLogo();

  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  
  display.setCursor(0,20); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("Temperatura = ");
  display.print(DHT.temperature, 1);
  display.println("'C");
  
  display.print("Umidade = ");
  display.print(DHT.humidity, 1);
  display.println("%");

  display.print(F("Pressao = "));
  display.print(bmp.readPressure()/100);
  display.println("hPa");

  display.print(F("Altitude = "));
  display.print(bmp.readAltitude(1016)/10); /* Adjusted to local forecast! */
  display.println("m");
}
void logo(){
  display.setTextSize(2); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.setCursor(30,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.println("Ryujin");
  display.setCursor(34,20); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.println("Alpha");
  display.setCursor(38,40); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
  display.print("v1.0");
}
void weather(){
  if (((bmp.readPressure()/100)<=1000.59)&&((bmp.readPressure()/100)>998.5)&&(DHT.humidity < 70)&&(DHT.humidity > 60)){
    display.drawBitmap(10, 15,cloudy, 20, 20, 1);
    display.setCursor(60,45);
    display.print("Nublado");
  }
  else if(((bmp.readPressure()/100)<998.5)&&((bmp.readPressure()/100)>996.5)&&(DHT.humidity > 70)){
    display.drawBitmap(10, 15,rain, 20, 20, 1);
    display.setCursor(66,38);
    display.print("Chuva");
  }
  else if(((bmp.readPressure()/100)>1000.6)&&((bmp.readPressure()/100)<1050)&&(DHT.humidity < 70)){
    display.drawBitmap(10, 15,sunny, 20, 20, 1);
    display.setCursor(50,45);
    display.print("Ceu Limpo");
  }
  else if(((bmp.readPressure()/100)>990)&&((bmp.readPressure()/100)<=996.4)&&(DHT.humidity > 70)&&(DHT.humidity > 26)){
    display.drawBitmap(10, 15,storm, 200, 200, 1);
    display.setCursor(60,45);
    display.print("Temporal");
  }
  else{
    display.setCursor(40,40);
    display.print("Erro!");
  }
}
void temperat(){
  display.setCursor(0,10);
  display.print("Temperatura");

  display.setCursor(55,40);
  display.print(DHT.temperature, 1);
  display.setCursor(97,40);
  display.print("C");
  display.drawBitmap(0, 17,temp , 200, 200, 1);
}
void humid(){
  display.setCursor(0,10);
  display.print(" Umidade");

  display.setCursor(55,40);
  display.print(DHT.humidity, 1);
  display.setCursor(97,40);
  display.print("%");
  display.drawBitmap(0, 17,hum , 80, 80, 1);
}
void pres(){
  display.setCursor(32,10);
  display.print(" Pressao");
  display.setCursor(65,45);
  display.print(bmp.readPressure()/100);
  display.setCursor(70,60);
  display.print("hPa");
  display.drawBitmap(50, 17,pressure , 100, 60, 1);
}
void menu(){
  
  int i;
  int valrd = digitalRead(BTNRED_PIN);
  int valwht = digitalRead(BTNWHITE_PIN);

  if(valrd == LOW){
    i=+1;  
  }
  switch(i){
    case 1:
      generalInfo();
    break;
    case 2:
      display.print("cu");
    break;
    default: logo();
  }
  
}

void loop(){
  display.clearDisplay();
  menu();
  display.display(); //EFETIVA A ESCRITA NO DISPLAY
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  delay(3000);
}