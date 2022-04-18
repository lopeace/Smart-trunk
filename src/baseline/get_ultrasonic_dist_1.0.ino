#define trigPin 50
#define echoPin 51
/*Ultrasonic Sensor (HC-SR04)*/
//ultrasonic speed : 340m/s
float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  SerialASC.begin(9600);
}

// 0.01초 간격으로 거리가 20cm이내인 경우 true 아니면 false를 출력하는 함수
bool get_ultrasonic_dist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
  // Echo 핀으로 들어온 펄스 시간 (us) 측정 
  //pulseIn(pin, value, timeout)
  //pin :  the number of the Arduino pin on which you want to read the pulse.
  //value: type of pulse to read: either HIGH or LOW
  //timeout (optional): the number of microseconds to wait for the pulse to start; 
  // --> default is one second, unsigned long
  duration = pulseIn(echoPin, HIGH, 11000); //time[us]
  distance = ((float)(duration)*0.34/10)/2; //time[us]*speed[cm/us]
  if (distance < 20)
  {
    delay(10);
    continue;
  }
  else
  { 
    delay(10);
    return false;
  }
  return true;
}
