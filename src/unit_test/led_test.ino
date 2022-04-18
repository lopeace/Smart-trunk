/* LED connection test code */
// switch D2의 입력이 발생하면 state를 전환한다. 각 state마다 RED, BLUE, GREEN LED의 작동을 확인할 수 있다.
// LED pin은 digital이나 PWM 사용해야 한다.
// 

#define RED 12
#define BLUE 13
#define GREEN 10
#define SWITCH 2

void setup() {
  // put your setup code here, to run once:
  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(SWITCH,INPUT);
  digitalWrite(GREEN,LOW);
  digitalWrite(BLUE,LOW);
  digitalWrite(RED,LOW);
}

int state = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(2) == LOW)  state++;
  if(state == 3)  state = 0;

  
  switch(state){
    case 0:
      digitalWrite(GREEN,HIGH);
      digitalWrite(BLUE,LOW);
      digitalWrite(RED,LOW);
      break;
    case 1:
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,HIGH);
      digitalWrite(RED,LOW);
      break;
    case 2:
      digitalWrite(GREEN,LOW);
      digitalWrite(BLUE,LOW);
      digitalWrite(RED,HIGH);
      break;
  }

  delay(100);
}
