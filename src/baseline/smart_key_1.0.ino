#define smart_key 3

void setup() {
  pinMode(smart_key, INPUT);  // D3 switch setup
}

//D3스위치가 눌리는 경우 true 아닐 경우 false를 출력하는 함수
bool smart_key() {

  if (digitalRead(smart_key) == LOW) 
  {  
    return true;
  }
  else
  { 
    return false;
  }
}
