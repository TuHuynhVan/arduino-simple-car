int receivedSignal = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0) {
    receivedSignal = Serial.read();

    switch (receivedSignal) {
      case 'g':
        goAhead();
        break;

      case 'l':
        turnLeft();
        break;

      case 'r':
        turnRight();
        break;

      case 'b':
        goBack();
        break;

      case 's':
        stopMoving();
        break;
    }
  }
}

void turnLeft() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(350);
  digitalWrite(6, LOW);
}

void turnRight() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  delay(350);
  digitalWrite(8, LOW);
}

void goAhead() {
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void goBack() {
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
}

void stopMoving() {
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

