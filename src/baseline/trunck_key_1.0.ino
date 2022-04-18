#define trunck_key 2

void setup() {
  pinMode(trunck_key, INPUT); // D2 switch setup
}

// truck_key가 눌리는 경우 true를 출력
bool truck_key() {

  if (digitalRead(trunck_key) == LOW) //스위치가 눌린 경우
  {  
    return true;
  }
  else
  { 
    return false;
  }
}
