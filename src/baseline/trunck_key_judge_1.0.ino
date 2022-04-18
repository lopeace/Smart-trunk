#define trunck_key 2

void setup() {
  pinMode(trunck_key, INPUT); // D2 switch setup
}

// truck_key가 0.01초 이상 눌리는 경우
bool truck_key_judge() {
  for (int cnt = 0; cnt > 10; ++cnt)
  {
    if (digitalRead(trunck_key) == LOW) //스위치가 눌린 경우
    {
      delay(1);                   //출력을 위한 딜레이
      continue;
    }
    else
    { 
      delay(1);                   //출력을 위한 딜레이
      return false;
    }
  }
  return true;
}
