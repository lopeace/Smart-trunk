/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-melody-repeat-example
   Library References: https://arduinogetstarted.com/tutorials/arduino-buzzer-library

   This example uses a piezo buzzer:
   + play a melody on background
   + repeat the melody when it is ended
   + without using delay() function, this is a non-blocking example
*/
#define OPEN 1
#define CLOSE 0

#include <ezBuzzer.h> // ezBuzzer library

const int BUZZER_PIN = 5;

ezBuzzer buzzer(BUZZER_PIN); // create ezBuzzer object that attach to a pin;

int melody1[] = {
  NOTE_G5, NOTE_C5, NOTE_D5,
};
int melody2[] = {
  NOTE_E5, NOTE_E5, NOTE_E5
};
int noteDurations1[] = {
  8, 8, 4,
};
int noteDurations2[] = {
  8, 8, 4,
};
int noteLength1,noteLength2;

void setup() {
  SerialASC.begin(9600);
  noteLength1 = sizeof(noteDurations1) / sizeof(int);
  noteLength2 = sizeof(noteDurations2) / sizeof(int);
}

void buzzer_beep(int condition){
  if(condition == 1){
      if (buzzer.getState() == BUZZER_IDLE) {
      SerialASC.println("open");
      buzzer.playMelody(melody1, noteDurations1, noteLength1); // playing
      SerialASC.println("open stop");
    }
    }
  else if(condition == 0){
      if (buzzer.getState() == BUZZER_IDLE) {
        SerialASC.println("close");
      buzzer.playMelody(melody2, noteDurations2, noteLength2); // playing
      SerialASC.println("close stop");
    }
    }
  }
int cnt = 0;
void loop() {

  buzzer.loop(); // MUST call the buzzer.loop() function in loop()

  buzzer_beep(1);

  buzzer_beep(0);

}

