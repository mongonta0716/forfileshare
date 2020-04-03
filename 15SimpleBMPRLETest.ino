
#include <M5StackUpdater.h>
#include <Wire.h>
#include <SD.h>
#include <LovyanGFX.hpp>

static LGFX tft;
static LGFX_Sprite sprite(&tft);

// for M5Stack
#define BUTTON_A_PIN 39
#define BUTTON_B_PIN 38
#define BUTTON_C_PIN 37

void setup() {
pinMode(BUTTON_A_PIN, INPUT_PULLUP);
pinMode(BUTTON_B_PIN, INPUT_PULLUP);
pinMode(BUTTON_C_PIN, INPUT_PULLUP);

#ifdef _SD_H_
  SD.begin(4, SPI, 20000000);
#endif
#ifdef __M5STACKUPDATER_H
  Wire.begin();
  if(digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD);
    ESP.restart();
  }
#endif

  Serial.begin(115200);
  while (!Serial);
  Serial.println("------------ Start ------------");

  // tft hardware init 
  tft.init();
  tft.setRotation(1);
  tft.setColorDepth(8);
  tft.setSwapBytes(true);
  tft.fillScreen(0xFFFFFFU);
//----------------------------------------
// ここまでテンプレート
//----------------------------------------
  tft.setCursor(0,0);
  tft.setTextSize(2);
  tft.drawBmpFile(SD, "/bmp/mouth_cl_angry_rle.bmp", 0, 0);
  //tft.println("drawBMPFile");
  
  sprite.createFromBmpFile(SD, "/bmp/mouth_cl_angry_rle.bmp");
  sprite.setTextSize(2);
  //sprite.println("createFromBmpFile");
  sprite.pushSprite(160, 120);
//  uint32_t pindex = sprite.getPaletteIndex(0x010102U);
//  Serial.printf("INDEX:%d\n", pindex);
//  pindex = sprite.getPaletteIndex(0xFF5B);
//  Serial.printf("INDEX:%d\n", pindex);
//  pindex = sprite.getPaletteIndex(0xf1ddcfU);
//  Serial.printf("INDEX:%d\n", pindex);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
