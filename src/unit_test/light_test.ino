/* Light sensor test code */
// Light sensor의 값을 analog로 받아온다. analog의 resolution을 10, 12, 16 bit으로 변경하여 측정한다.
//  test 결과   밝을 때      어두울 때
//  10 bit     22~25       5~8
//  12 bit     95~104      21~30
//  16 bit     22~25       5~8

// test 결과를 토대로 12-bit resolution을 사용하기로 결정함.

#define LIGHT A1

void setup() {
  // put your setup code here, to run once:
  pinMode(LIGHT, INPUT);
  SerialASC.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
  analogReadResolution(10);
  SerialASC.print(analogRead(LIGHT));
  SerialASC.print("\t");
  analogReadResolution(12);
  SerialASC.print(analogRead(LIGHT));
  SerialASC.print("\t");
  analogReadResolution(16);
  SerialASC.println(analogRead(LIGHT));
  
  delay(100);
}
