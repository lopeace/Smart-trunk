/******** 자동 생성된 코드 *********/

/* LMU uninitialised data */
StartOfUninitialised_LMURam_Variables
/* Put your LMU RAM fast access variables that have no initial values here e.g. uint32 LMU_var; */
EndOfUninitialised_LMURam_Variables

/* LMU uninitialised data */
StartOfInitialised_LMURam_Variables
/* Put your LMU RAM fast access variables that have an initial value here e.g. uint32 LMU_var_init = 1; */
EndOfInitialised_LMURam_Variables

/********** 작성한 코드 *********/

// State condition flag definition 
#define STATE_IDLE 0
#define STATE_BEGIN 1
#define STATE_RUN 2

// System condition definition
#define OFF 0
#define ON 1
#define CLOSE 0
#define OPEN 1

// Pin mapping



// Global variables declaration
int flag_state = STATE_IDLE;            // flag_State = 구동시작, 구동중, 구동완료 구분 플래그    STATE_ILDE(0) = 구동 완료/대기  STATE_BEGIN(1) = 구동 시작    STATE_RUN(2) = 구동 중
int flag_open = CLOSE;                  // flag_Open = 열림 상태 구분 플래그                     CLOSE(0) = 닫힘           OPEN(1) = 열림

// Functions declaration
void event_key_input(void);
void led_off(int pin_num);
void led_on(int pin_num);

bool trunk_key_judge(void);
bool ultrasonic_key_judge(void);
bool smart_key_judge(void);
bool get_light_sensor(void);

int get_ultrasonic_dist(void);
void set_stepper(int condition);
void buzzer_beep(int condition);

void setup() {
  // put your setup code for core 0 here, to run once:

}


void loop() {
  // Key input judgement
  if (trunk_key == HIGH){                // trunck key 눌림
    if (trunk_key_judge() == true)   event_key_input();          // 10ms간 눌림 확인. 조건 미충족시 바로 return FALSE 로 나올 것
  }
  else if (get_ultrasonic_dist() < 20){   // 초음파 거리 20 미만 확인
    if (ultrasonic_key_judge() == true)   event_key_input();      // 초음파 거리 20 미만 0.3s 유지 확인. 조건 미충족시 바로 return FALSE 로 나올 것
  }
  else if (smart_key == HIGH){            // smart key 눌림
    if (smart_key_judge() == true)    event_key_input();          // 3s간 눌림 확인. 조건 미충족시 바로 return FALSE 로 나올 것
  }
  else {                                  // 입력 장치 모두 미작동
    
  }
  
  // State condition
  if (flag_state == STATE_RUN){                       // STATE_RUN      구동 중인 상태
    
    if (flag_open == OPEN){                           // 열리는 상태
      set_stepper(OPEN);                              // 열리는 포지션으로 가는 코드
      if (finish_step() == true)  flag_state = STATE_IDLE;    // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
    else{                                             // 닫히는 상태
      set_stepper(CLOSE);                             // 열리는 포지션으로 가는 코드
      if (finish_step() == true)  flag_state = STATE_IDLE;    // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
    }
     
  }
  else if (flag_state == STATE_BEGIN){                // STATE_BEGIN    구동 시작하는 상태
    
    if (flag_open == OPEN){                           // 열린 상태
      set_stepper(OPEN);                              // 열리는 포지션으로 가는 코드
      buzzer_beep(OPEN);                              // 열릴 때 비프음 출력
      flag_state = STATE_RUN;                         // 구동 상태를 구동 중으로 변경
    }
    else{                                             // 닫힌 상태
      set_stepper(CLOSE);                             // 닫히는 포지션으로 가는 코드
      buzzer_beep(CLOSE);                             // 닫힐 때 비프음 출력
      flag_state = STATE_RUN;                         // 구동 상태를 구동 중으로 변경
    }
  }
  else{                                               // STATE_IDLE     구동 완료 or 대기 상태
    
    if (flage_open == OPEN){                          // 열린 상태
      led_off(RED);
      led_on(BLUE);                                   // 열린 상태면 파란불
      if (get_light_sensor() == true) led_on(GREEN);  // 조도값이 일정 아래면 초록불
      else  led_off(GREEN);                           // 조도값이 일정 이상이면 초록불 off
    }
    else{                                             // 닫힌 상태
      led_off(GREEN);                                 // 닫힌 상태면 초록불 off
      led_off(BLUE);
      led_on(RED);                                    // 닫힌 상태면 빨간불
    }
  }
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

bool trunk_key_judge(void){
  // trunk key 입력을 100ms 간 체크하는 함수. 확인되면 true 반환. 체크 중 입력이 LOW가 되면 바로 false 반환할 것.
  // empty function. please add contents after unit-test.
  return true;
  
}
bool ultrasonic_key_judge(void){
  // 초음파 센서 거리값이 20cm 미만임을 1s 간 체크하는 함수. 확인되면 true 반환. 체크 중 입력이 20 이상이 되면 바로 false 반환할 것.
  // stub function. please add contents after unit-test.
  return true;
}
bool smart_key_judge(void){
  // smart key 입력을 3s 간 체크하는 함수. 확인되면 true 반환. 체크 중 입력이 LOW가 되면 바로 false 반환할 것.
  // stub function. please add contents after unit-test.
  return true;
}
bool get_light_sensor(void){
  // 조도 센서값이 임계값 미만인지 확인하는 함수. 미만이면 true 반환. 이상이면 false 반환.
  // stub function. please add contents after unit-test.
  return true;
}

int get_ultrasonic_dist(void){
  // 초음파 센서로 인식한 거리(cm)를 integer 형으로 반환하는 함수.
  // stub function. please add contents after unit-test.
  return 10;
}
void set_stepper(int condition){
  // stepper motor의 구동을 condition(OPEN/CLOSE)에 따라 제어하는 함수. 정해진 위치까지 loop마다 일정하게 회전하도록 작동할 것.
  // stub function. please add contents after unit-test.
  
}
void buzzer_beep(int condition){
  // buzzer가 입력받은 condition(OPEN/CLOSE)에 따라 정해진 음을 작동시키는 함수. OPEN시 3회 비프음. CLOSE시 1회 장음.
  // stub function. please add contents after unit-test.
  
}

