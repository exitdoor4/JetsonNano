#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include "DAVIDBackpack.h"

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

int main(){
    HT16K33 *displayMatrix = new HT16K33() ;
    // Default I2C Bus 1
    int err = displayMatrix -> openHT16K33();
    if(err <0){
        printf("error: %d", displayMatrix->error);
    } else {
        printf("HT16K33 Device Address: 0x%02X\n", displayMatrix->kI2CAddress);
        printf("HT16K33 Device Bus: 0x%02X\n", displayMatrix->kI2CBus);
        displayMatrix->begin() ;
        displayMatrix->clear();

        displayMatrix->writeDigitNum(0,1);
        displayMatrix->writeDigitNum(1,2);
        displayMatrix->writeDigitNum(2,3);
        displayMatrix->writeDigitNum(3,4);

        displayMatrix->writeDisplay();

        //try to print a number thats the too long
        // show dashes & blink
        displayMatrix->print(10000,DEC);
        displayMatrix->writeDisplay();
        displayMatrix->blinkRate(HT16K33_BLINK_2HZ);
        sleep(5);

        displayMatrix->blinkRate(HT16K33_BLINK_OFF);

        displayMatrix->print(0XBEEF,HEX);
        displayMatrix->writeDisplay();
        sleep(5);

        displayMatrix->printFloat(0.586, 3, DEC);
        displayMatrix->writeDisplay();
        sleep(5);

     printf("Starting Count Down, Engines On\n") ;
        // print with print/println
        for (int counter = 10; counter >= 0; counter--) {
           displayMatrix->println(counter);
           displayMatrix->writeDisplay();
           sleep(1);
        }
    printf("Hit ESC key to exit\n");
        // Minutes and seconds - Start a 9:50 to show an exciting time change at 10:00!
        uint16_t counter = 590 ;
        bool drawDots = false ;
        while(displayMatrix->error >= 0 && getkey() != 27){
                // display as hours and minutes
                int hours = counter / 60 ;
                int minutes = counter % 60 ;
                // printf("Counter: %d\n", counter);
                displayMatrix->writeDigitNum(0, (hours / 10), drawDots);
                displayMatrix->writeDigitNum(1, hours  % 10, drawDots);
                displayMatrix->drawColon(true);
                displayMatrix->writeDigitNum(3, (minutes / 10) % 10, drawDots);
                displayMatrix->writeDigitNum(4, minutes % 10, drawDots);
                displayMatrix->writeDisplay() ;
                counter ++ ;
                sleep(1) ;
        }        displayMatrix->print(10000, DEC);
        displayMatrix->writeDisplay();
        displayMatrix->blinkRate(HT16K33_BLINK_2HZ) ;
        sleep(5) ;

        displayMatrix->blinkRate(HT16K33_BLINK_OFF) ;

        // print a hex number
        displayMatrix->print(0xBEEF, HEX);
        displayMatrix->writeDisplay();
        sleep(5);

        // print a floating point number
        displayMatrix->printFloat(0.596,3,DEC);
        displayMatrix->writeDisplay();
        sleep(5);

        printf("Starting Count Down, Engines On\n") ;
        // print with print/println
        for (int counter = 10; counter >= 0; counter--) {
           displayMatrix->println(counter);
           displayMatrix->writeDisplay();
           sleep(1);
        }

    }
    displayMatrix->end() ;
    displayMatrix->closeHT16K33();
}
