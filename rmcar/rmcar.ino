const int motor1DirectionPin = 2; //모터 1 방향 핀
const int motor1SpeedPin = 3; // 모터 1 속도 제어 핀
const int motor2DirectionPin = 8; //모터 2 방향 핀
const int motor2SpeedPin = 9; // 모터 2 속도 제어 핀

void setup() {
  Serial.begin(9600);
  pinMode(motor1DirectionPin, OUTPUT); // 모터 1 방향 핀을 출력으로 설정
  pinMode(motor1SpeedPin, OUTPUT); // 모터 1 속도 제어 핀을 출력으로 설정
  pinMode(motor2DirectionPin, OUTPUT); // 모터 2 방향 핀을 출력으로 설정
  pinMode(motor2SpeedPin, OUTPUT); // 모터 2 속도 제어 핀을 출력으로 설정
}
`
void loop() {
  if (Serial.available() > 0) {  // 캐릭터가 하나 이상 있는지 확인
    String input = Serial.readStringUntil('\n');  // 개행 문자를 받을 때까지 입력을 읽음

    // 양쪽 공백 제거
    input.trim();

    // 공백으로 입력 분할
    int spaceIndex = input.indexOf(' ');
    if (spaceIndex != -1) {
      String number1String = input.substring(0, spaceIndex);
      String number2String = input.substring(spaceIndex + 1);

      int number1 = number1String.toInt();
      int number2 = number2String.toInt();

      if (number1 < 0) {
        backward(abs(number1), 1);  // 모터 1에 대한 음수는 후진을 나타냄
      } else {
        forward(number1, 1);  // 모터 1에 대한 양수는 전진을 나타냄
      }

      if (number2 < 0) {
        backward(abs(number2), 2);  // 모터 2에 대한 음수는 후진을 나타냄
      } else {
        forward(number2, 2);  // 모터 2에 대한 양수는 전진을 나타냄
      }
    }
  }
}

void forward(int speed, int motorNumber) {
  // 속도가 허용 범위에 있는지 확인
  if(speed < 0 || speed > 255){
    Serial.println("에러: 속도는 0과 255 사이여야 합니다");
    return; // 함수 종료
  }

  if (motorNumber == 1) {
    Serial.println("모터 1: 전진 중");
    Serial.print("속도: ");
    Serial.println(speed);
    digitalWrite(motor1DirectionPin, HIGH); // 모터 1 방향 핀을 HIGH로 설정하여 전진 방향 설정
    analogWrite(motor1SpeedPin, speed); // 모터 1 속도 제어 핀에 속도 값을 적용
  } else if (motorNumber == 2) {
    Serial.println("모터 2: 전진 중");
    Serial.print("속도: ");
    Serial.println(speed);
    digitalWrite(motor2DirectionPin, HIGH); // 모터 2 방향 핀을 HIGH로 설정하여 전진 방향 설정
    analogWrite(motor2SpeedPin, speed); // 모터 2 속도 제어 핀에 속도 값을 적용
  }
}

void backward(int speed, int motorNumber) {
  // 속도가 허용 범위에 있는지 확인
  if(speed < 0 || speed > 255){
    Serial.println("에러: 속도는 0과 255 사이여야 합니다");
    return; // 함수 종료
  }

  if (motorNumber == 1) {
    Serial.println("모터 1: 후진 중");
    Serial.print("속도: ");
    Serial.println(speed);
    digitalWrite(motor1DirectionPin, LOW); // 모터 1 방향 핀을 LOW로 설정하여 후진 방향 설정
    analogWrite(motor1SpeedPin, speed); // 모터 1 속도 제어 핀에 속도 값을 적용
  } else if (motorNumber == 2) {
    Serial.println("모터 2: 후진 중");
    Serial.print("속도: ");
    Serial.println(speed);
    digitalWrite(motor2DirectionPin, LOW); // 모터 2 방향 핀을 LOW로 설정하여 후진 방향 설정
    analogWrite(motor2SpeedPin, speed); // 모터 2 속도 제어 핀에 속도 값을 적용
  }
}
