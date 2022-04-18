#define trunck_key 2

void setup() {
  pinMode(trunck_key, INPUT); // D2 switch setup
  SerialASC.begin(9600);      // 출력을 위한 설정
}

bool loop() {
  for (int cnt = 0; cnt < 300; ++cnt)
  {
    if (digitalRead(trunck_key) == LOW) //스위치가 눌린 경우
    {
      delay(100);                 //출력을 위한 딜레이
      SerialASC.println("TURE");  //"TRUE" 출력 
      continue;
    }
    else
    { 
      delay(100);                 //출력을 위한 딜레이
      SerialASC.println("FALSE"); //"FALSE" 출력 
      return false;
    }
  }
  return true;
}
