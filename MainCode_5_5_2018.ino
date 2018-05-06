// defines pins numbers
const int stepPin = 5; //CLK+
const int dirPin = 2; //CW+ Directin of the motor
const int enPin = 8;

// rope motor
const int stepPin2 = 6; //CLK+
const int dirPin2 = 4; //CW+ Directin of the motor
const int enPin2 = 3;

const int ledPin = 13;
const int interruptPin_CW = 18;
const int interruptPin_CCW = 19;
long X = 0;
long Y = 0;
long Z = 0;
bool is_reset = 0;
int position_var;
long target_step = 0;
long vertical_step = 5000;


//small linear actuator
//Declare pin functions on Redboard
#define stp 22
#define dir 12
#define EN  11

// states variables that will be used in the program
long numberOfStep = 0;



int flag = 0;
void setup() { 
  position_var = 3;
 
  // Sets the two pins as Outputs
  Serial.begin(2000000);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);

  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(enPin2,OUTPUT);


  pinMode(interruptPin_CW, INPUT);
  pinMode(interruptPin_CCW, INPUT);
  digitalWrite(enPin,LOW);  
  digitalWrite(enPin2,LOW);
  //attachInterrupt(digitalPinToInterrupt(interruptPin_CW), VMotor_CW, RISING);
  //attachInterrupt(digitalPinToInterrupt(interruptPin_CCW), VMotor_CCW, RISING);

  //small linear actuator
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(EN, OUTPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  
}
void loop() {
  
    digitalWrite(EN, LOW); //Pull enable pin low to allow motor contro
    //StepForwardDefault();
    
//  if(position_var == 1) {
//    Serial.println("Position is 1");
//    target_step = 42667;
//    Serial.print("target step = ");
//    Serial.println(target_step);
//    VMotor_CW1(target_step); 
//    position_var = 0;
//
//  }
////
//    if(position_var == 2) {
//    Serial.println("Position is 2");
//    target_step = 105333;
//    Serial.print("target step = ");
//    Serial.println(target_step);
//    VMotor_CW1(target_step); 
//    position_var = 0;
//
//  }
////
  if(position_var == 3) {
    Serial.println("Position is 3");
    target_step = 105333;
    Serial.print("target step = ");
    Serial.println(target_step);
    StepForwardDefault(); 
    VMotor_CW1(target_step);
    position_var = 0;

  }
//  
  if(digitalRead(interruptPin_CCW) == 1 ){ // reset
    reset(); 
   
  }
  resetEDPins();

}



/*-----------Function Calling-----------*/


void VMotor_CW1(long target_step) 
{
  Serial.print("target step = ");
  Serial.println(target_step);
 digitalWrite(dirPin,LOW); // MOVE TO THE LEFT SIDE.
  // Makes 200 pulses for making one full cycle rotation
  for (X = X; X <= target_step; X++) 
  {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(5); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(5); 
    Serial.print("current steps = ");
    Serial.println(X);
    
    if(digitalRead(interruptPin_CCW) == 1){
    reset();
    break;
   }
  }
  vertical_motor();
}

void reset() // to go to 
{
  reverse_vertical_motor();
  digitalWrite(dirPin,HIGH); //MOVE TO THE RIGHT SIDE.
  // Makes 400 pulses for making two full cycle rotation
 for (X = X; X >= 0; X--) 
  {

    digitalWrite(stepPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(5);
    
    Serial.println(X);
  }
  X = 0;

  ReverseStepDefault();
  
}

//small linear actuator
void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(EN, HIGH);
}

//Default microstep mode function
void StepForwardDefault()
{
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  while(numberOfStep < 66000)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delayMicroseconds(350);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(350);
   Serial.print("Invalid option entered: ");
   Serial.println(numberOfStep);
    numberOfStep++;
  }
}
//Reverse default microstep mode function
void ReverseStepDefault()
{
  Serial.println("Moving in reverse at default step mode.");

//Reset Easy Driver pins to default states
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  while(numberOfStep > 0)//Loop the stepping enough times for motion to be visible
  {  
    digitalWrite(stp,HIGH); //Trigger one step
    delayMicroseconds(500);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(500);
    numberOfStep--;
  }
}


void vertical_motor()
{
  Serial.print("Vertical step = ");
  Serial.println(vertical_step);
  digitalWrite(dirPin2,LOW); // MOVE TO THE LEFT SIDE.
  // Makes 200 pulses for making one full cycle rotation
  for (int x = 0; x <= vertical_step; x++) 
  {
    digitalWrite(stepPin2,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPin2,LOW); 
    delayMicroseconds(1500); 
    Serial.print("current steps = ");
    Serial.println(x);
    if(digitalRead(interruptPin_CCW) == 1){
      reset();
      break;
    }
  }
}
void reverse_vertical_motor() 
{
  Serial.print("Vertical step = ");
  Serial.println(vertical_step);
  digitalWrite(dirPin2,HIGH); // MOVE TO THE LEFT SIDE.
  // Makes 200 pulses for making one full cycle rotation
  for (int x = vertical_step; x >= 0; x--) 
  {
    digitalWrite(stepPin2,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPin2,LOW); 
    delayMicroseconds(1500); 
    Serial.print("current steps = ");
    Serial.println(x);
    
    if(digitalRead(interruptPin_CCW) == 1){
    reset();
      break;
   }
  }
}
void pullUp_Button(){
  Serial.print("Vertical step = ");
  Serial.println(vertical_step);
  digitalWrite(dirPin2,HIGH); // MOVE TO THE LEFT SIDE.
  for (int x = vertical_step; x >= (vertical_step-500); x--) 
  {
    digitalWrite(stepPin2,HIGH); 
    delayMicroseconds(1500); 
    digitalWrite(stepPin2,LOW); 
    delayMicroseconds(1500); 
    Serial.print("current steps = ");
    Serial.println(x);
    
    if(digitalRead(interruptPin_CCW) == 1){
      reset();
      break;
     }
  }
}
