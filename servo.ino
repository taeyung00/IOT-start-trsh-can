#include <Servo.h>      // 서보 라이브러리 사용

Servo trash;            // trash 라는 이름의 서보 선언
 
int trig = 10;          // 초음파센서 trig핀
int echo = 9;           // 초음파센서 echo핀

bool isOpen = false;    // 뚜껑 상태 확인용 변수

void setup() {
  trash.attach(A0);      // 서보모터 핀 연결 (A0번)
  Serial.begin(9600);    // 시리얼 통신 속도 설정
  pinMode(trig, OUTPUT); // 트리거 핀 출력 모드
  pinMode(echo, INPUT);  // 에코 핀 입력 모드

  trash.write(0);        // 초기 뚜껑 닫힘 상태
}

void loop() {
  long duration, distance;

  // 초음파 거리 측정
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);
  distance = duration / 58;  // cm 변환
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 가까이 접근했을 때 뚜껑 열기
  if (distance > 0 && distance <= 5 && !isOpen) {
    trash.write(80);    // 뚜껑 열기
    isOpen = true;      // 열린 상태로 변경
    delay(1000);        // 안정적인 동작을 위한 딜레이
  }

  // 멀어졌을 때 뚜껑 닫기 (예: 10cm 이상 떨어지면 닫힘)
  if (distance > 10 && isOpen) {
    trash.write(0);     // 뚜껑 닫기
    isOpen = false;     // 닫힌 상태로 변경
    delay(500);         // 딜레이로 중복 감지 방지
  }

  delay(100); // 기본 루프 딜레이 (빠른 감지용)
}
