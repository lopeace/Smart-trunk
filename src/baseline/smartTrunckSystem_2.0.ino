#include <Stepper.h>

// State condition flag definition 
#define STATE_IDLE 0
#define STATE_BEGIN 1
#define STATE_RUN 2

// System condition definition
#define OFF 0
#define ON 1
#define CLOSE 0
#define OPEN 1
#define NIGHT 40
#define ANGLE_MAX 50
#define ANGLE_MIN 0

// Pin mapping
#define RED 22
#define BLUE 24
#define GREEN 26
#define LIGHT A1
#define TRUNK_KEY 48
#define SMART_KEY 49
#define TRIGPIN 50
#define ECHOPIN 51

#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13
#define PUSH_SW  2

/*Ultrasonic Sensor (HC-SR04)*/
//ultrasonic speed : 340m/s
float duration, distance;

// Global variables declaration
int flag_state = STATE_IDLE;            // flag_State = 구동시작, 구동중, 구동완료 구분 플래그    STATE_ILDE(0) = 구동 완료/대기  STATE_BEGIN(1) = 구동 시작    STATE_RUN(2) = 구동 중
int flag_open = CLOSE;                  // flag_Open = 열림 상태 구분 플래그                     CLOSE(0) = 닫힘           OPEN(1) = 열림
int stepper_cnt = 0;

// Define number of steps per revolution:
const int stepsPerRevolution = 200;

// Functions declaration
void event_key_input(void);
void led_off(int pin_num);
void led_on(int pin_num);

bool trunk_key(void);
bool smart_key(void);
bool trunk_key_judge(void);
bool ultrasonic_key_judge(void);
bool smart_key_judge(void);
bool get_light_sensor(void);

bool get_ultrasonic_dist(void);
void set_stepper(int condition);
void buzzer_beep(int condition);
void state_led(int state);

Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);

void setup() {
  // put your setup code for core 0 here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(LIGHT,INPUT);
  pinMode(TRUNK_KEY,INPUT);
  pinMode(SMART_KEY,INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  SerialASC.begin(9600);
  analogReadResolution(12);

  // Stepper motor pin mode setup
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
  
}


void loop() {
  // Key input judgement
  if (trunk_key() == true){                // trunck key 눌림
    SerialASC.println("trunk key");
    if (trunk_key_judge() == true)   event_key_input();          // 10ms간 눌림 확인. 조건 미충족시 바로 return FALSE 로 나올 것
  }
  else if (get_ultrasonic_dist() == true){   // 초음파 거리 20 미만 확인
    SerialASC.println("ultrasonic");
    if (ultrasonic_key_judge() == true)   event_key_input();      // 초음파 거리 20 미만 0.3s 유지 확인. 조건 미충족시 바로 return FALSE 로 나올 것
  }
  else if (smart_key() == true){            // smart key 눌림
    SerialASC.println("smart key");
    if (smart_key_judge() == true)    event_key_input();          // 3s간 눌림 확인. 조건 미충족시 바로 return FALSE 로 나올 것
  }
  else {                                  // 입력 장치 모두 미작동
    
  }
  
  // State condition
  if (flag_state == STATE_RUN){                       // STATE_RUN      구동 중인 상태
    SerialASC.println("State run");
    if (flag_open == OPEN){                           // 열리는 상태
      set_stepper(OPEN);                              // 열리는 포지션으로 가는 코드
      stepper_cnt++;
      if(stepper_cnt == ANGLE_MAX) {flag_state = STATE_IDLE; flag_open = OPEN;}     // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
    else{                                             // 닫히는 상태
      set_stepper(CLOSE);                             // 열리는 포지션으로 가는 코드
      stepper_cnt--;
      if(stepper_cnt == ANGLE_MIN) {flag_state = STATE_IDLE; flag_open = CLOSE;}    // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
     
  }
  else if (flag_state == STATE_BEGIN){                // STATE_BEGIN    구동 시작하는 상태
    SerialASC.println("State begin");
    if (flag_open == OPEN){                           // 열린 상태
      SerialASC.println("open");
      set_stepper(OPEN);                              // 열리는 포지션으로 가는 코드
      stepper_cnt++;
      buzzer_beep(OPEN);                              // 열릴 때 비프음 출력
      
      flag_state = STATE_RUN;                         // 구동 상태를 구동 중으로 변경
    }
    else{                                             // 닫힌 상태
      SerialASC.println("close");
      set_stepper(CLOSE);                             // 닫히는 포지션으로 가는 코드
      stepper_cnt--;
      buzzer_beep(CLOSE);                             // 닫힐 때 비프음 출력
      
      flag_state = STATE_RUN;                         // 구동 상태를 구동 중으로 변경
    }
  }
  else{                                               // STATE_IDLE     구동 완료 or 대기 상태
    SerialASC.println("State idle");
    state_led(flag_open);
  }

  delay(100);
}

void event_key_input(void){
  // key input 발생시 open flag를 토글하고 state를 구동 시작으로 변경하는 함수
  
  // toggle flag_open
  if (flag_open == OPEN)  flag_open = CLOSE;
  else  flag_open = OPEN;

  if (flag_state != STATE_BEGIN)  flag_state = STATE_BEGIN; // 구동 상태가 시작이 아니면 시작으로 변경
}
void led_off(int pin_num){
  // 입력받은 핀과 연결된 led를 off하는 함수. digital signal LOW.
  digitalWrite(pin_num, LOW);
}
void led_on(int pin_num){
  // 입력받은 핀과 연결된 led를 off하는 함수. digital signal LOW.
  digitalWrite(pin_num, HIGH);
}


bool trunk_key(void){
  if (digitalRead(TRUNK_KEY) == LOW) 
  {  
    return true;
  }
  else
  { 
    return false;
  }
}
bool smart_key(void){
  if (digitalRead(SMART_KEY) == LOW) 
  {  
    return true;
  }
  else
  { 
    return false;
  }
}
bool trunk_key_judge(void){
  // trunk key 입력을 10ms 간 체크하는 함수. 확인되면 true 반환. 체크 중 입력이 LOW가 되면 바로 false 반환할 것.
  for (int cnt = 0; cnt < 10; ++cnt)
  {
    if (trunk_key() == true) //스위치가 눌린 경우
    {
      delay(10);                   //출력을 위한 딜레이
      continue;
    }
    else
    { 
      delay(10);                   //출력을 위한 딜레이
      return false;
    }
  }
  return true;
}
bool smart_key_judge(void){
  // smart key 입력을 3s 간 체크하는 함수. 확인되면 true 반환. 체크 중 입력이 LOW가 되면 바로 false 반환할 것.
    for (int cnt = 0; cnt < 300; ++cnt)
  { 
    if (smart_key() == true) 
    {
      delay(10);                 
      continue;
    }
    else
    { 
      delay(10);                 
      return false;
    }
  }
  return true;
}
bool ultrasonic_key_judge(void){
  // 초음파 센서 거리값이 20cm 미만임을 1s 간 체크하는 함수. 확인되면 true 반환. 체크 중 입력이 20 이상이 되면 바로 false 반환할 것.
  for (int cnt=0;cnt<30;++cnt)
  {
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW); 
    // Echo 핀으로 들어온 펄스 시간 (us) 측정 
    //pulseIn(pin, value, timeout)
    //pin :  the number of the Arduino pin on which you want to read the pulse.
    //value: type of pulse to read: either HIGH or LOW
    //timeout (optional): the number of microseconds to wait for the pulse to start; 
    // --> default is one second, unsigned long
    duration = pulseIn(ECHOPIN, HIGH, 11000); //time[us]
    distance = ((float)(duration)*0.34/10)/2; //time[us]*speed[cm/us]
    if (distance < 20 && distance > 1)
    {
      delay(10);
      continue;
    }
    else
    { 
      delay(10);
      return false;
    }
  }
  return true;
}
bool get_light_sensor(int pinnum){
  // 조도 센서값이 임계값 미만인지 확인하는 함수. 미만이면 true 반환. 이상이면 false 반환.
  int light_data = analogRead(pinnum);
  if (light_data < NIGHT)  return true;
  else  return false;
}


bool get_ultrasonic_dist(void) {
  // 0.01초 간격으로 거리가 20cm이내인 경우 true 아니면 false를 출력하는 함수
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW); 
  // Echo 핀으로 들어온 펄스 시간 (us) 측정 
  //pulseIn(pin, value, timeout)
  //pin :  the number of the Arduino pin on which you want to read the pulse.
  //value: type of pulse to read: either HIGH or LOW
  //timeout (optional): the number of microseconds to wait for the pulse to start; 
  // --> default is one second, unsigned long
  duration = pulseIn(ECHOPIN, HIGH, 11000); //time[us]
  distance = ((float)(duration)*0.34/10)/2; //time[us]*speed[cm/us]
  if (distance < 20 && distance > 1)
  {
    delay(10);
  }
  else
  { 
    delay(10);
    return false;
  }
  return true;
}
void set_stepper(int condition){
  // stepper motor의 구동을 condition(OPEN/CLOSE)에 따라 제어하는 함수. 정해진 위치까지 loop마다 일정하게 회전하도록 작동할 것.
  
  if (condition == OPEN){
    myStepper.step(-1);
    delay(10);
  }
  if (condition == CLOSE){
    myStepper.step(1);
    delay(10);

  }
}
void buzzer_beep(int condition){
  // buzzer가 입력받은 condition(OPEN/CLOSE)에 따라 정해진 음을 작동시키는 함수. OPEN시 3회 비프음. CLOSE시 1회 장음.
  // stub function. please add contents after unit-test.
  
}

void state_led(int state){
  if (state == OPEN){
    led_off(RED);
    led_on(BLUE);                                   // 열린 상태면 파란불
    if (get_light_sensor(LIGHT) == true) led_on(GREEN);  // 조도값이 일정 아래면 초록불
    else  led_off(GREEN);                           // 조도값이 일정 이상이면 초록불 off
  }
  else{
    led_off(GREEN);                                 // 닫힌 상태면 초록불 off
    led_off(BLUE);
    led_on(RED);                                    // 닫힌 상태면 빨간불
  }
}
