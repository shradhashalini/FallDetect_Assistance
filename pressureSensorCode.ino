/* FSR simple testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
 
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrPin1 = 1;
int fsrPin2 = 2;
int fsrPin3 = 3;
int fsrPin4 = 4;
int fsrPin5 = 5;

int fsrReading;     // the analog reading from the FSR resistor divider
int fsrReading1; 
int fsrReading2;
int fsrReading3;
int fsrReading4;
int fsrReading5;

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
}
 
void loop(void) {
  fsrReading = analogRead(fsrPin); 
  fsrReading1 = analogRead(fsrPin1);
  fsrReading2 = analogRead(fsrPin2);
  fsrReading3 = analogRead(fsrPin3);
  fsrReading4 = analogRead(fsrPin4);
  fsrReading5 = analogRead(fsrPin5);
 
  
/*--------combination with different pressure sensor ---------------- */
   if (fsrReading > 1 && fsrReading1 > 1) {
    Serial.println(" Someone fell at location 0 & 1");
  } 
   else if (fsrReading1 > 1 && fsrReading2 > 1) {
    Serial.println(" Someone fell at location 1 & 2");
  } 
   else if (fsrReading2 > 1 && fsrReading3 > 1) {
    Serial.println(" Someone fell at location 2 & 3");
  }
     else if (fsrReading3 > 1 && fsrReading4 > 1) {
    Serial.println(" Someone fell at location 3 & 4");
  }
     else if (fsrReading4 > 1 && fsrReading5 > 1) {
    Serial.println(" Someone fell at location 4 & 5");
  }


  
 delay(1000);
} 
