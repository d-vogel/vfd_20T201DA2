#include "Arduino.h"
#include "vfd_20T201DA2.h"

#include "vfd_20T201DA2.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

vfd_20T201DA2::vfd_20T201DA2(int CLK, int DATA, int RESET)
{
    pinMode(CLK, OUTPUT);
    pinMode(DATA, OUTPUT);
    pinMode(RESET, OUTPUT);
    _CLK_pin = CLK;
    _DATA_pin = DATA;
    _RESET_pin = RESET;
}

void vfd_20T201DA2::begin(int cols, int rows)
{
    _SIZE_COLS = cols;
    _SIZE_ROWS = rows;
}

void vfd_20T201DA2::clear()
{
  digitalWrite(_RESET_pin, HIGH);
  delay(1);
  digitalWrite(_RESET_pin, LOW);
  delay(4);
}

void vfd_20T201DA2::setCursorPos(int col, int row)
{
    uint8_t char_pos = _SIZE_COLS*row + col+1;
    write(vfd_20T201DA2_SC); write(char_pos);
}

void vfd_20T201DA2::write(byte data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(_DATA_pin, (data >> 7 - i) & 0b00000001);
    delayMicroseconds(12);
    digitalWrite(_CLK_pin, LOW);
    delayMicroseconds(8);
    digitalWrite(_CLK_pin, HIGH);
    delayMicroseconds(16);
  }
  delayMicroseconds(40);
}

void vfd_20T201DA2::setCursorMode(CURSOR_MODE mode)
{
    write(vfd_20T201DA2_CM); write(mode);
}

void vfd_20T201DA2::setBrightness(uint8_t val)
{
    write(vfd_20T201DA2_SB); write(val);
}

void vfd_20T201DA2::setFlashPos(int colStart, int rowStart, int colEnd, int rowEnd)
{
    int idxStart = (uint8_t)(_SIZE_COLS*rowStart+colStart+1);
    int idxEnd = (uint8_t)(_SIZE_COLS*rowEnd+colEnd+1);
    write(vfd_20T201DA2_FP); write(idxStart);write(idxEnd); 
}

void vfd_20T201DA2::flashOn()
{
    write(vfd_20T201DA2_FM); write(0x02);
}
void vfd_20T201DA2::flashOff()
{
    write(vfd_20T201DA2_FM); write(0x01);
}

void vfd_20T201DA2::setFlashRate(FLASH_RATE rate)
{
    write(vfd_20T201DA2_FR); write(rate);
}

void vfd_20T201DA2::setCharFont(CHAR_FONT font)
{
    write(vfd_20T201DA2_FO); write(font);
}


void vfd_20T201DA2::writeText(String text)
{
    byte data[text.length()];
    for (int i = 0; i < text.length(); i++) {
        char c = text.charAt(i);
        data[i] = (c >= 0x20) ? c : 0x20;
    }
    for (int i = 0; i < text.length(); i++) {
        write(data[i]);
    }
}
