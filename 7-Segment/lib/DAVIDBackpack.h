#ifndef _DAHT16K33_H
#define _DAHT16k33_H

#include <cstddef> // NULL, size_t 사용
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> // 하드웨어의 제어와 상태정보를 얻음
#include <cstdlib> // exit(), abort(), atexit()
#include <cstdio> // c언어의 stdio.h와 같음
#include <fcntl.h> // 파일을 열고, 잠금 및 다른 작업을 할 수 있음
#include <unistd.h> // 다양한 필수 POSIX 함수와 상수 read, write
#include <errno.h>
#include <stdint.h> // uint8_t 같은 자료형을 사용 가능



#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0xE0

class HT16K33
{
public:
    unsigned char kI2CBus ;         // I2C bus of the HT16K33
    int kI2CFileDescriptor ;        // File Descriptor to the HT16K33
    int kI2CAddress ;               // Base address of HT16K33; defaults to 0x70
    int error ;
    HT16K33(int address=0x70);
    ~HT16K33() ;
    uint16_t displayBuffer[10];

    bool openHT16K33() ;
    void closeHT16K33();
    int getError() ;

    int i2cwrite(int writeValue) ;

    void begin();
    void end() ;
    void setBrightness(uint8_t b);
    void blinkRate(uint8_t b);
    int writeDisplay(void);
    void clear(void);

   void init(uint8_t a);


    size_t write(uint8_t c);

     void print(char, int = BYTE);
     void print(unsigned char, int = BYTE);
     void print(int, int = DEC);
     void print(unsigned int, int = DEC);
     void print(long, int = DEC);
     void print(unsigned long, int = DEC);
     void print(double, int = 2);
     void println(char, int = BYTE);
     void println(unsigned char, int = BYTE);
     void println(int, int = DEC);
     void println(unsigned int, int = DEC);
     void println(long, int = DEC);
     void println(unsigned long, int = DEC);
     void println(double, int = 2);
     void println(void);

     void writeDigitRaw(uint8_t x, uint8_t bitmask);
     void writeDigitNum(uint8_t x, uint8_t num, bool dot = false);
     void drawColon(bool state);
     void printNumber(long, uint8_t = 2);
     void printFloat(double, uint8_t = 2, uint8_t = DEC);
     void printError(void);

     void writeColon(void);

     uint8_t position;

    
};


#endif