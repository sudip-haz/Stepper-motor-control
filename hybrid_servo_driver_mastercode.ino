const int stepPin = 3; // step input
const int dirPin = 11; // directional input
const byte epinA = 2; // input for position from the encoder
volatile int encoderCount = 0;
int step_to_turn = 0; // hybrid stepper position
long int motorstep = 1; // no. of steps to move
byte switch_START = 5; // Start Button
int switch_STOP = 3;// Stop Button
int A;
byte switch_1 = 7; // button cw pin
byte switch_2 = 6; // button ccw pin
//byte switch_A = 5; // Start/Stop Button
int a = 0; //assigning the starting value to 1 for the button counter
int i; // motorstep counter
int customDelayMapped = 0;
int read_interval = 1; // intervals at which the interrupts should be implemented.

void setup() {
 //   Serial.begin(115200);
    pinMode(stepPin, OUTPUT); // pulse output defined on stepPin 
    pinMode(dirPin, OUTPUT); // Direction output defined on dirPin
    digitalWrite(dirPin, HIGH); // defined initial direction of rotation towards the homing button
    pinMode(switch_1, INPUT_PULLUP); // set the direction change buttons to a value of 1 as default
    pinMode(switch_2, INPUT_PULLUP); // set the direction change buttons to a value of 1 as default
 //   pinMode(switch_A, INPUT_PULLUP);   
    pinMode(epinA, INPUT_PULLUP);  
    attachInterrupt(digitalPinToInterrupt(epinA), eintA, CHANGE);
  /* while (!digitalRead(switch_2)) { // Do this until the switch is not activated
      digitalWrite(dirPin, HIGH); 
      digitalWrite(stepPin, HIGH);
      delay(5);                       // More delay to slow even more while moving away from switch
      digitalWrite(stepPin, LOW);
*/}

void loop() {
  
  static unsigned long pt = millis();
  unsigned long ct = millis();

  int encoderRead = 0;

 if(ct - pt >= read_interval){
    cli();
    encoderRead = encoderCount;
    encoderCount = 0;
    sei();
    step_to_turn += encoderRead;
    movemot(motorstep);
  }
}
  
void movemot(int motorstep){
   while(i <= motorstep){
      customDelayMapped = speedUp(); // Gets custom delay values from the custom speedUp function
      
      if (digitalRead(switch_1) == 0 && digitalRead(switch_2) == 1) {
      digitalWrite(dirPin, LOW);
      }
      if (digitalRead(switch_2) == 0 && digitalRead(switch_1) == 1) {
      digitalWrite(dirPin, HIGH);
      }
      if( i <= 0.5*motorstep)
      {
        customDelayMapped = (customDelayMapped*0.0000001*(motorstep-i));
        }
      if(i >= 0.5*motorstep)
      {
        customDelayMapped = (customDelayMapped*0.000001*i);
        }
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(200);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1);
      
      i++;
    } 
    i = 0;
}

// Function for reading the Potentiometer
int speedUp() {
  int customDelay = analogRead(A0); // Reads the potentiometer
  int newCustom = map(customDelay, 0, 1023, 500,10000); // Convrests the read values of the potentiometer from 0 to 1023 into desireded delay values (300 to 4000)
  return newCustom;  
}

void eintA(){
  // if the pins read the same we're going one direction
  // else we're going the other direction.
  if((PIND & 2) == 1 && (PIND & 2) == 0){
    encoderCount++;
  }
  else {
    encoderCount--;
  }
}
