
#include "vfd_20T201DA2.h"
//1   VCC
//2   CLK
//3   GND
//4   DATA
//5   RESET
const int CLK = 2;  // -> CLOCK
const int DATA = 4; // -> DATA
const int RST = 5;   // -> RESET


vfd_20T201DA2 display(CLK, DATA, RST);
void setup() {
  Serial.begin(115200);
  display.begin(20, 2);
  display.clear();
  display.writeText("00:00");
  
  display.setFlashRate(FLASH_1HZ);
  display.flashOn();
  display.setCursorPos(4,1);
  display.writeText("hello world!");
  display.setCursorPos(0,0);
  display.setFlashPos(2,0,2,0);
}

int i = 0;

void loop() {
  if (Serial.available())
  {
    String s = Serial.readStringUntil('\n');
    if (s.equals("CD")) display.clear();
    else if (s.equals("RES")) display.clear();
    else {
      display.writeText(s);
      Serial.println(s);
    }
  }
}
