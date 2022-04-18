#define smart_key 3

void setup() {
  pinMode(smart_key, INPUT);  // D3 switch setup
  SerialASC.begin(9600);      // 출력을 위한 설정
}

// 3초 이상 D3 스위치를 누르는 경우 TRUE 출력 아닌 경우 0.1초 간격으로 
bool loop() {
  for (int cnt = 0; cnt < 30; ++cnt)
  { 
    if (digitalRead(smart_key) == LOW) 
    {
      delay(100);                 //0.1초의 딜레이
      continue;
    }
    else
    { 
      delay(100);                 //0.1초의 딜레이
      SerialASC.println("FALSE"); //"FALSE" 출력 
      return false;               //false를 return
    }
  }
  SerialASC.println("TURE");  //"TRUE" 출력 
  return true;                //true를 reture
}
