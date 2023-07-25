#include <SoftwareSerial.h>

SoftwareSerial gps(16, 17);  //---RX=D3 and TX=D2
String lattitude, longitude;
String data[5];
int i = 0;
char c;


void setup() {
  Serial.begin(9600);
  gps.begin(9600);
  Serial.println("wait for 5 sec");
  delay(5000);
  gps.println("AT+CGNSPWR=1");
  delay(2000);
  gps.println("AT+CGNSSEQ=\"RMC\"");
  delay(2000);
}

void loop() {
    int i=0;
    longitude = "";
    lattitude = "";
      for(i=0; i<5; i++)
        data[i]="";
    i=0;
    Serial.println("----Command given----");
    gps.flush();        
    long int time = millis();
    gps.println("AT+CGNSINF");
    
    while ((time+1000 ) > millis()){
    while(gps.available()){
        c = gps.read();
        if (c != ',') {
          data[i] +=c;
          delay(20);
         } 
         else 
         i++;
        }
        if(i==5)
        break;
    }
    
    lattitude = data[3];
    longitude = data[4];
    
    Serial.println(lattitude);
    Serial.println(longitude);
    
    Serial.println("----Response Print-1--");
    delay(10000);
 }
