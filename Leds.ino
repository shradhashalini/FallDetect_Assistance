

int leds =  11;
volatile int i=0;//initializing a integer for incrementing and decrementing duty ratio.

void setup()
{
                pinMode(leds, OUTPUT);   // sets the pin3 as output
}
void loop()
{
                if (i<255)
                { 
                          analogWrite(3, i);  // analogWrite values from 0 to 255
                          i++;//if pin0 is pressed and the duty ratio value is less than 255
                          delay(30);
                }
                if (i==255)
                {
                    while(i != 0){
                        i--;// if pin1 is pressed and the duty ratio value is greater than 0
                        analogWrite(3, i);
                        delay(30);
                    }
                }
}
