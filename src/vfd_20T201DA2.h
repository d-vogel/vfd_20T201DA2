#ifndef vfd_20T201DA2_h
#define vfd_20T201DA2_h

#include "Arduino.h"

#define vfd_20T201DA2_NP 0x00 //No Operation
#define vfd_20T201DA2_CD 0x01 //Clear Entire Display
#define vfd_20T201DA2_SC 0x02 //Set Cursor Position
#define vfd_20T201DA2_CM 0x03 //Set Cursor Mode
#define vfd_20T201DA2_SB 0x04 //Set Display Brightness Level
#define vfd_20T201DA2_IO 0x05 //Set Input/Output Mode
#define vfd_20T201DA2_FP 0x06 //Set Flash Position
#define vfd_20T201DA2_FM 0x07 //Flash Mode
#define vfd_20T201DA2_FR 0x08 //Set lash Rate
#define vfd_20T201DA2_FO 0x09 //Select Character Font
#define vfd_20T201DA2_DC 0x0A //Load User Definable Character
#define vfd_20T201DA2_BM 0x0B //Set Buffered Mode
#define vfd_20T201DA2_PB 0x0C //Print Message Buffer
#define vfd_20T201DA2_C1 0x18 //Print UDF #1
#define vfd_20T201DA2_C2 0x19 //Print UDF #2
#define vfd_20T201DA2_C3 0x1A //Print UDF #3
#define vfd_20T201DA2_C4 0x1B //Print UDF #4
#define vfd_20T201DA2_C5 0x1C //Print UDF #5
#define vfd_20T201DA2_C6 0x1D //Print UDF #6
#define vfd_20T201DA2_C7 0x1E //Print UDF #7
#define vfd_20T201DA2_C8 0x1F //Print UDF #8

typedef enum{
    CURSOR_MODE_AUTO_INC = 0x01,
    CURSOR_MODE_AUTO_DEC = 0x02,
    CURSOR_MODE_NONE = 0x03
} CURSOR_MODE;

typedef enum{
    FLASH_50HZ = 0x01,
    FLASH_1HZ = 0x30,
    FLASH_0HZ1 = 0xFF
} FLASH_RATE;

typedef enum{
    CHAR_WEST_EURO = 0x01,
    CHAR_KATAKANA = 0x02
} CHAR_FONT;


class vfd_20T201DA2
{
  public:
    //Low level stuff
    vfd_20T201DA2(int CLK, int DATA, int RESET);
    void begin(int cols, int rows);
    void clear();
    void setCursorPos(int col, int row);
    void write(byte data);
    void setCursorMode(CURSOR_MODE mode);
    void setBrightness(uint8_t val);
    void setFlashPos(int colStart, int rowStart, int colEnd, int rowEnd);
    void flashOn();
    void flashOff();
    void setFlashRate(FLASH_RATE rate);
    void setCharFont(CHAR_FONT font);

    void writeText(String text);
    
  private:
    int _CLK_pin, _DATA_pin, _RESET_pin;
    int _SIZE_COLS, _SIZE_ROWS;
};

#endif
