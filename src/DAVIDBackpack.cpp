#include <DAVIDBackpack.h>

HT16K33::HT16K33(int address) {
    kI2CBus = 1;
    KI2CAddress = address;
    error = 0;
    position = 0;
}

HT16K33::~HT16K33(){
    closeHT16K33();
}

bool HT16K33::openHT16K33()
{
    char fileNameBuffer[32];
    sprintf(fileNameBuffer, "/dev/i2c-%d", KI2CBus);
    KI2CFileDescripter = open(fileNameBuffer, O_RDWR);
    if(KI2CFileDescripter <0){
        파일이 열리지 않았다
        error = errno;
        return false;
    }
    if(ioctl(KI2CFileDescripter, I2C_SLAVE, KI2CAddress) < 0) {
        // 버스에 있는 디바이스가 열리지 않았다
        error =errno;
        return false;
    }
    return true;
}

int HT16K33::i2cwrite(int writeValue){
    int toReturn = i2c_smbus_write_byte() // runs an SMBus "Send byte" transaction
    if(toReturn < 0){
        print("HT16K33 Write error: %d", errno);
        error = errno;
        toReturn = -1;
    }
    return toReturn 
}

void HT16K33::begin(){
    i2cwrite(0x21); // turn on oscillator 
    blinkRate(HT)

    setBrightness(15);
}

void HT16K33:blinkRate(uint8_t b){
    if(b > 3) b = 0;
    i2cwrite(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPAYON | (b << 1));
}