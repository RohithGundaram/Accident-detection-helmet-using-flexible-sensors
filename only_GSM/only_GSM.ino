 #include<SoftwareSerial.h>

char phone[]="6309334707";  // "your phone number";

SoftwareSerial gsm(16, 17);

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);
  delay(5000);
  Serial.println("Calling.......");
  gsm.print("ATD");                      // Call command ATD9730579463;
  gsm.print(phone);                      
  gsm.println(";");
  
  delay(10000);
  Serial.println("Call disconected");
  gsm.println("ATH");
  delay(1000);
  
  gsm.println("AT+CMGF=1");                // Select Text mode for messsaging
  delay(1000);

    gsm.print("AT+CMGS=\"");               //AT+CGMS="9730579463"
      gsm.print(phone);
      gsm.println("\"");
      delay(100);
      gsm.print("Hello Rohith!! -- from your mom");      //>Message to be sent
      gsm.println((char)26);    // ASCII of CTRL+Z
      
      delay(100);
      Serial.println("message is sent");
      
      Serial.println("Calling.......");
      gsm.print("ATD");                      // Call command ATD9730579463;
      gsm.print(phone);                      
      gsm.println(";");
      delay(10000);
      Serial.println("Call disconected");
      gsm.println("ATH");
 }


void loop() {
}
