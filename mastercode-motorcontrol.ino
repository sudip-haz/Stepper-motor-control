const int stepPin = 10; // step input
const int dirPin = 11; // directional input
long int motorstep = 6509; // no. of steps to move
byte switch_START = 5; // Start Button
int switch_STOP = 3;// Stop Button
int A,  dir;
int previous;
int x;
byte switch_1 = 7; // button cw pin
byte switch_2 = 6; // button ccw pin
int a = 0; //assigning the starting value to 1 for the button counter
int i, b;
int customDelayMapped = 0;

void setup() {
    Serial.begin(9600);
    pinMode(stepPin, OUTPUT); // pulse output defined on stepPin 
    pinMode(dirPin, OUTPUT); // Direction output defined on dirPin
   
    pinMode(switch_1, INPUT_PULLUP); // set the direction change buttons to a value of 1 as default
    pinMode(switch_2, INPUT_PULLUP); // set the direction change buttons to a value of 1 as default
    pinMode(switch_START, INPUT_PULLUP);   
    pinMode(switch_STOP, INPUT_PULLUP); 
    while (!digitalRead(switch_1)) { // Do this until the switch is not activated
      digitalWrite(dirPin, HIGH); 
      digitalWrite(stepPin, HIGH);
      delay(5);                       // More delay to slow even more while moving away from switch
      digitalWrite(stepPin, LOW);
    
  }
   digitalWrite(dirPin, LOW); // defined initial direction of rotation towards the homing button
}
void loop() {
          
{
  if (digitalRead(switch_START) == 0 && digitalRead(switch_STOP) == 1) {
      A = 0;
      }
  else if (digitalRead(switch_STOP) == 0 && digitalRead(switch_START) == 1) {
      A = 1;
      }
 
  if(A == 1)
      movemot(motorstep); 
  else
      digitalWrite(stepPin, LOW);
}
} 

void movemot(int motorstep){
   while(i <= motorstep){
      customDelayMapped = speedUp(); // Gets custom delay values from the custom speedUp function
      int z= customDelayMapped;      
      if (digitalRead(switch_START) == 0 && digitalRead(switch_STOP) == 1) {
       break; }
      if (digitalRead(switch_1) == 0 && digitalRead(switch_2) == 1) {
      digitalWrite(dirPin, HIGH);    
      }     
      if (digitalRead(switch_2) == 0 && digitalRead(switch_1) == 1) {
      digitalWrite(dirPin, LOW);      
      }   
      if( i <= 0.19*motorstep)
      {
        customDelayMapped = (((0.1*motorstep)-i)*customDelayMapped);
        //customDelayMapped = (customDelayMapped*0.0000001*(motorstep-i));
        }
     /* if(i >= 0.75*motorstep)
      {
        //(motorstep-i)/customDelayMapped
        customDelayMapped = (customDelayMapped*0.000001*i);
        }*/
      digitalWrite(stepPin, LOW);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(customDelayMapped);
      i++;


    } 
    i = 0;
}

int speedUp() {
  int customDelay = analogRead(A0); // Reads the potentiometer
  int newCustom = map(customDelay, 0, 1023, 0,1000); // Convrests the read values of the potentiometer from 0 to 1023 into desireded delay values (300 to 4000)
  return newCustom;  
}
