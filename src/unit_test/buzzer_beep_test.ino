#define CLOSE 0
#define OPEN 1

int Buzzer_Pin = 5;  // buzzer pin : 5번 

int Tones[8] = {261, 294, 330, 349, 392, 440, 495, 524};

void setup() {
  pinMode(Buzzer_Pin, OUTPUT);
}

void buzzer_beep(int state){
    //OPEN (부저음 한번 출력)
    if(state == OPEN){
        tone(Buzzer_Pin, Tones[2]); // tone(출력 핀 번호, 주파수 값)
        delay(200); // 0.2초 출력
        noTone(Buzzer_Pin);
        delay(100); 
      }
    //CLOSE (부저음 세번 출력)
    else{
      for (int i= 0; i < 3; i++) {
        tone(Buzzer_Pin, Tones[2]); // tone(출력 핀 번호, 주파수 값)
        delay(200);// 0.2초 음 출력
        noTone(Buzzer_Pin);
        delay(100); 
          }
  noTone(Buzzer_Pin);
      }
  }

void loop() {
  noTone(Buzzer_Pin);
  
  buzzer_beep(OPEN);
  delay(1000);
  buzzer_beep(CLOSE);
  delay(300);
    
}
