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

bool loop() {
  for (int cnt=0;cnt<10;++cnt)
  {
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
      delay(100);
      continue;
    }
    else
    { 
      delay(100);
      SerialASC.println("FALSE"); //20cm 이상인 경우 FALSE를 출력
      return false;
    }
  }
  SerialASC.println("TRUE");      //20cm 이하로 1초 이상인 경우 TRUE를 출력
  return true;
}
