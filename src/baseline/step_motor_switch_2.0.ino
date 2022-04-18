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

// State condition flag definition 
#define STATE_IDLE 0
#define STATE_BEGIN 1
#define STATE_RUN 2

// System condition definition
#define OFF 0
#define ON 1
#define CLOSE 0
#define OPEN 1
#define ANGLE_MAX 200
#define ANGLE_MIN 0

// Pin mapping



// Global variables declaration
int flag_state = STATE_IDLE;            // flag_State = 구동시작, 구동중, 구동완료 구분 플래그    STATE_ILDE(0) = 구동 완료/대기  STATE_BEGIN(1) = 구동 시작    STATE_RUN(2) = 구동 중
int flag_open = CLOSE;                  // flag_Open = 열림 상태 구분 플래그                     CLOSE(0) = 닫힘           OPEN(1) = 열림
int stepper_cnt = 0;

int pressed = false; 
int pressedkey = true; 
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
  myStepper.setSpeed(30);
//  SerialASC.begin(9600);
}
void loop() {
//  SerialASC.println(flag_state);
    /* Read button */
  if (digitalRead(PUSH_SW) == false) // push : 0, NOP : 1
  {
    if (pressedkey == true){
      pressedkey = false;
      if (flag_state == STATE_IDLE){
        flag_state = STATE_BEGIN;
      }
      else if (flag_state == STATE_BEGIN){
        flag_state = STATE_RUN;
      }
      else{
        flag_state = STATE_RUN;
      }
      
    }
  }
  else{
    pressedkey = true;
  }
  delay(20); //ms
  
  // State condition
  if (flag_state == STATE_RUN){                       // STATE_RUN      구동 중인 상태
    
    if (flag_open == OPEN){                           // 열리는 상태
      set_stepper(OPEN);                              // 열리는 포지션으로 가는 코드
      stepper_cnt++;
      if(stepper_cnt == ANGLE_MAX) {flag_state = STATE_IDLE; flag_open = OPEN;}   // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
    else{                                             // 닫히는 상태
      set_stepper(CLOSE);                             // 열리는 포지션으로 가는 코드
      stepper_cnt--;
      if(stepper_cnt == ANGLE_MIN) {flag_state = STATE_IDLE; flag_open = CLOSE;}   // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
     
  }
  else if (flag_state == STATE_BEGIN){                // STATE_BEGIN    구동 시작하는 상태
    
    if (flag_open == CLOSE){                           // 열린 상태
//      flag_state = STATE_RUN;                         // 구동 상태를 구동 중으로 변경
      set_stepper(OPEN);                              // 열리는 포지션으로 가는 코드
      stepper_cnt++;
      if(stepper_cnt == ANGLE_MAX) {flag_state = STATE_IDLE; flag_open = OPEN;}   // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
    else{                                             // 닫힌 상태
//      flag_state = STATE_RUN;                         // 구동 상태를 구동 중으로 변경
      set_stepper(CLOSE);                             // 닫히는 포지션으로 가는 코드
      stepper_cnt--;
      if(stepper_cnt == ANGLE_MIN) {flag_state = STATE_IDLE; flag_open = CLOSE;}   // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
  }
  else{                                               // STATE_IDLE     구동 완료 or 대기 상태
  }
  

}
void set_stepper(int condition){
  // stepper motor의 구동을 condition(OPEN/CLOSE)에 따라 제어하는 함수. 정해진 위치까지 loop마다 일정하게 회전하도록 작동할 것.
  // stub function. please add contents after unit-test.

if (condition == OPEN){
    myStepper.step(-1);
    delay(10);
  }
if (condition == CLOSE){
    myStepper.step(1);
    delay(10);

  }
}
