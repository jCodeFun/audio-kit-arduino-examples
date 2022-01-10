#include <SPI.h>
#include <SD.h>

#define BUFFER_SIZE 1
#define SD_SS 4

long begintime;
long endtime;

int16_t i;
const int S = 128;
short buffer[S];

void setup()
{
    Serial.begin(115200);
    SD.begin(SD_SS);
    
    digitalWrite(SD_SS,HIGH);

    Serial.print ("START\n");
      File f = SD.open("1.wav");
      if (f) {
        begintime=micros();
        while (true) {
          //int16_t n = f.read((char*)buff,BUFFER_SIZE);
          int n = f.read(buffer,sizeof(buffer));
          if (!n)
          break;

            for(i=0;i<S;i++)
            Serial.print(buffer[i],HEX);
            Serial.println("");
        }
        endtime=micros();
        f.close();
        Serial.print("STOP(");
        Serial.print(endtime-begintime);
        Serial.print(")\n\n");
      }
}
void loop()
{
}
