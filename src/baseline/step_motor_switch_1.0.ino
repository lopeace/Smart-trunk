// Include the Stepper library:
// D2 Switch rotation change

#include <Stepper.h>
// Define number of steps per revolution:
const int stepsPerRevolution = 200;
// Give the motor control pins names:
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13
#define PUSH_SW  2
#define CLOSE 0
#define OPEN 1

int pressed = false; 
void set_stepper(int condition);
// Initialize the stepper library on the motor shield:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);


void setup() {
  // Set the PWM and brake pins so that the direction pins can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
  pinMode(PUSH_SW, INPUT);    // Direction pin on channel A
  // Set the motor speed (RPMs):
  myStepper.setSpeed(15);
}
void loop() {

  /* Read button */
  if (digitalRead(PUSH_SW) == false) // push : 0, NOP : 1
  {
    set_stepper(OPEN);

  }
  else{
    set_stepper(CLOSE);
  }
  delay(20); //ms
}
void set_stepper(int condition){
  // stepper motor의 구동을 condition(OPEN/CLOSE)에 따라 제어하는 함수. 정해진 위치까지 loop마다 일정하게 회전하도록 작동할 것.
  // stub function. please add contents after unit-test.

if (condition == OPEN){
    myStepper.step(-50);
    delay(1000);
  }
if (condition == CLOSE){
    myStepper.step(50);
    delay(1000);
  }
}
