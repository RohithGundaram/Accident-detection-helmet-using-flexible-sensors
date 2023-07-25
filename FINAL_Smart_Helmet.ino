#include <SoftwareSerial.h>

int button = 5;
char phone[]="8247447352";  // "Family Phone number";

SoftwareSerial sim808(16, 17);  //---RX=16 and TX=17
String latitude, longitude;
String data[5];
int i = 0;
char c;
int val1=0;
int val2=0;
int val3=0;
int count = 0;


void setup() {
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  sim808.begin(9600);
  //miss_call();
  sim808.println("AT+CGNSPWR=1");
  delay(2000);
  sim808.println("AT+CGNSSEQ=\"RMC\"");
  delay(2000);
}

void loop() {
  Serial.println("scanning button");
  gps_location();
  delay(1000);
  
  val1=analogRead(32);
  delay(10);
  val2=analogRead(34);
  delay(10);
  val3=analogRead(35);
  delay(10);
  
  Serial.print(val1);
  Serial.print(", ");
  Serial.print(val2);
  Serial.print(", ");
  Serial.print(val3);
  Serial.print('\n');

  if((val1>70 || val2>150 || val3>150) && count < 2){
    delay(40);                         
    Serial.println("Accident Detected \n Sending location details to family");
    gps_location();
    miss_call();
    sms_send();
    count = count +1 ;
  }
  
  delay(1000);
  if(digitalRead(button)==LOW){
    delay(40);                          //wait 40mSec to debounce
    while(digitalRead(button)==LOW);    //wait till button released
    Serial.println("Button pressed");
    Serial.println("Accident Detected \n Sending location details to family");
//    Serial.println("Sending location details to family");
    gps_location();
    miss_call();
    sms_send();
  }
 }

void miss_call(){
  Serial.println("Calling.......");
  sim808.print("ATD");                      // Call command ATD6309334707;
  sim808.print(phone);                      
  sim808.println(";");
  delay(10000);
  Serial.println("Call disconected");
  sim808.println("ATH");
  delay(1000); 
}

 void sms_send()
 {    sim808.println("AT+CMGF=1");                // Select Text mode for messsaging
      delay(100);
      sim808.print("AT+CMGS=\"");               
      sim808.print(phone);
      sim808.println("\"");
      delay(1000);
      sim808.print("HELP!!\n I met with an accident \n Location: \n");   
      sim808.print("http://maps.google.com/maps?q=loc:");
      sim808.print(latitude);
      sim808.print(",");
      sim808.print(longitude);
      delay(500);     
      sim808.println((char)26);
      delay(100);
      Serial.println("Message is sent");
      delay(100);
 }
 
void gps_location(){
    int i=0;
    longitude = "";
    latitude = "";
      for(i=0; i<5; i++)
        data[i]="";
    i=0;
    Serial.println("--GPS--request--given----");
    sim808.flush();        
    long int time = millis();
    sim808.println("AT+CGNSINF");
    while ((time+1000 ) > millis()){
    while(sim808.available()){
        c = sim808.read();
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
    latitude = data[3];
    longitude = data[4];
    Serial.print("latitude = ");
    Serial.println(latitude);
    Serial.print("longitude = ");
    Serial.println(longitude);
 }
