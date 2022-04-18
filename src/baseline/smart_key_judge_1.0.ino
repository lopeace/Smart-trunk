#define smart_key 3

void setup() {
  pinMode(smart_key, INPUT);  // D3 switch setup
}

// 스위치가 3초 이상 눌리는 경우 true 아닐 경우 false를 출력하는 함수
bool smart_key_judge() {
  for (int cnt = 0; cnt < 300; ++cnt)
  { 
    if (digitalRead(smart_key) == LOW) 
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
