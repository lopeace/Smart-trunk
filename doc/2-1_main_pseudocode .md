# 메인 함수에서 사용한 전역 변수
`flag_State` = 구동시작, 구동중, 구동완료 구분 플래그
`0 = 구동 완료(대기), 1 = 구동 시작, 2 = 구동 중`
`flag_Open` = 열림 상태 구분 플래그
`ON(1) = 열림, OFF(0) = 닫힘`

```c
Main Loop()

   // key_input_judgement
   if trunk_key = ON      // trunck key 눌림
      if trunk_key_judge();   // 10ms간 눌림 확인. 조건 미충족시 바로 return FALSE 로 나올 것
         toggle_flag_Open();
         if flag_State != 1 : flag_State = 1   // 구동 상태가 시작이 아니면 시작으로 변경

   else if get_ultrasonic_dist < 20   // 초음파 거리 20 미만 확인
      if ultrasonic_key_judge();   // 초음파 거리 20 미만 0.3s 유지 확인. 조건 미충족시 바로 return FALSE 로 나올 것
         toggle_flag_Open();
         if flag_State != 1 : flag_State = 1   // 구동 상태가 시작이 아니면 시작으로 변경

   else if smart_key = ON      // smart key 눌림
      if smart_key_judge();   // 3s간 눌림 확인. 조건 미충족시 바로 return FALSE 로 나올 것
         toggle_flag_Open();
         if flag_State != 1 : flag_State = 1   // 구동 상태가 시작이 아니면 시작으로 변경
   else
      무시

   // State 구분
   if flag_State = 2      // 구동 중인 상태
      if flag_Open = ON
         set_stepper(OPEN);         // 열리는 포지션으로 가는 코드
         if finish_step() : flag_State = 0   // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경
      else      
         set_stepper(CLOSE);         // 닫히는 포지션으로 가는 코드   
         if finish_step() : flag_State = 0   // 스텝모터가 목표위치 도달하면 구동 완료 상태로 변경

   else if flag_State = 1      // 구동 시작하는 상태
      if flag_Open = ON
         set_stepper(OPEN);         // 열리는 포지션으로 가는 코드
         buzzer_beep(OPEN);         // 열릴 때 비프음 출력
         flag_State = 2            // 구동 상태를 구동 중으로 변경
      else
         set_stepper(CLOSE);         // 닫히는 포지션으로 가는 코드   
         buzzer_beep(CLOSE);         // 닫힐 때 비프음 출력
         flag_State = 2            // 구동 상태를 구동 중으로 변경

   else            // 구동 완료한 상태
      if flag_Open = ON               // 열린 상태
         LED_off(RED);
         LED_on(BLUE);               // 열린 상태면 파란불
         if get_light_sensor() = ON : LED_ON(GREEN);   // 조도값이 일정 아래면 초록불
         else
            LED_OFF(GREEN);
      else
         LED_off(GREEN);
         LED_off(BLUE);
         LED_on(RED);

```