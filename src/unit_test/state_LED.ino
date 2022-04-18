/* LED state test code */
// OPEN / CLOSE state 별로 LED 제어하는 함수.
// OPEN 시에는 Light sensor가 40보다 낮으면 GREEN LED 작동함.

// System condition definition
#define OFF 0
#define ON 1
#define CLOSE 0
#define OPEN 1

#define RED 12
#define BLUE 13
#define GREEN 10
#define SWITCH 2
#define LIGHT A1
#define NIGHT 40

int flag_open = CLOSE;                  // flag_Open = 열림 상태 구분 플래그                     CLOSE(0) = 닫힘           OPEN(1) = 열림

void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(SWITCH,INPUT);
  digitalWrite(GREEN,LOW);
  digitalWrite(BLUE,LOW);
  digitalWrite(RED,LOW);
  analogReadResolution(12);
  pinMode(LIGHT,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(2) == LOW)  flag_open++;
  if(flag_open == 2)  flag_open = 0;
  
  state_led(flag_open);
  delay(100);
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

void led_off(int pin_num){
  // 입력받은 핀과 연결된 led를 off하는 함수. digital signal LOW.
  digitalWrite(pin_num, LOW);
}
void led_on(int pin_num){
  // 입력받은 핀과 연결된 led를 off하는 함수. digital signal LOW.
  digitalWrite(pin_num, HIGH);
}

int get_light_sensor(int pinnum){
  int light_data = analogRead(pinnum);
  if (light_data < NIGHT)  return true;
  else  return false;
}
