/* FSR simple testing sketch. 
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
 

#define stp 2
#define dir 3
#define MS2 5
#define EN  6

//Declare variables for functions
char user_input;
int x;
int y;
int z = 0;
// states variables that will be used in the program
int numberOfStep = 0;
 
 
 
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
/*---- ultrasonic distance sensor------*/
const int trigPin = 12;
const int echoPin = 13;

long duration;
int distance;
/*------------ LED lights---------------- */
int leds =  11;
volatile int i=100;//initializing a integer for incrementing and decrementing duty ratio.
/*-----------Motor------------*/
const int stepPin = 5; //CLK+
const int dirPin = 2; //CW+ Directin of the motor
const int enPin = 8;

const int interruptPin_CW = 18;
const int interruptPin_CCW = 19;


void setup(void) {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states



  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);  
  pinMode(leds, OUTPUT);   // sets the pin3 as output
    pinMode(trigPin, OUTPUT); //distance sensor
  pinMode(echoPin, INPUT);   //distance sensor
   pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  pinMode(interruptPin_CW, INPUT);
  pinMode(interruptPin_CCW, INPUT);
  digitalWrite(enPin,LOW);
}
 
void loop(void) {
 digitalWrite(EN, LOW); //Pull enable pin low to allow motor control



  fsrReading = analogRead(fsrPin); 
  fsrReading1 = analogRead(fsrPin1);
  fsrReading2 = analogRead(fsrPin2);
  fsrReading3 = analogRead(fsrPin3);
  fsrReading4 = analogRead(fsrPin4);
  fsrReading5 = analogRead(fsrPin5);

/*--------------------LED lights---------------------------------------- */
  analogWrite(3, i);  // analogWrite values from 0 to 255
  
/*distance */  
   digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

/*--------combination with different pressure sensor ---------------- */
   if (fsrReading > 1 && fsrReading1 > 1) {
    i = 255;
    Serial.println(" Someone fell at location 0 & 1");
    z = 200;
    StepForwardDefault(z);
    
    if(digitalRead(interruptPin_CW)){
     VMotor_CW();
    }
    if(distance < 10) {
    //stop the motor
    }
    
  } 
   else if (fsrReading1 > 1 && fsrReading2 > 1) {
    i = 255;
    z = 400;
    StepForwardDefault(z);
    Serial.println(" Someone fell at location 1 & 2");
  } 
   else if (fsrReading2 > 1 && fsrReading3 > 1) {
    i = 255;
    z = 600;
    StepForwardDefault(z);
    Serial.println(" Someone fell at location 2 & 3");
  }
     else if (fsrReading3 > 1 && fsrReading4 > 1) {
      i = 255;
      z = 800;
    StepForwardDefault(z);
    Serial.println(" Someone fell at location 3 & 4");
  }
     else if (fsrReading4 > 1 && fsrReading5 > 1) {
      i = 255;
      z = 1000;
    StepForwardDefault(z);
    Serial.println(" Someone fell at location 4 & 5");
  } 
  else if (digitalRead(interruptPin_CCW)) {
    VMotor_CCW();
    ReverseStepDefault(z);
  }

/* ---------------- ultrasonic distance sensor---------------------*/


  Serial.println("distance: ");
    Serial.println(distance);
  resetEDPins();
 delay(1000);
} 

void VMotor_CW() 
{
 digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 800; x++) 
  {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
}

void VMotor_CCW()
{
  digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 800; x++) 
  {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
  }


void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}

//Default microstep mode function
void StepForwardDefault(int steps)
{
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  while(numberOfStep < steps)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
    steps++;
  }
}

//Reverse default microstep mode function
void ReverseStepDefault(int steps)
{
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  while(steps > 0)//Loop the stepping enough times for motion to be visible
  {  
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
    numberOfStep--;
  }
  Serial.println("Enter new option");
  Serial.println();
}
