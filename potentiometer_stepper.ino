void setup() {
  // establish motor direction toggle pins
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void quarterStep(bool enableA, bool channelUp, int delayLength) {
  digitalWrite(8, enableA ? HIGH : LOW);
  digitalWrite(9, enableA ? LOW : HIGH);
  digitalWrite(enableA ? 12 : 13, channelUp ? HIGH : LOW);
  digitalWrite(enableA ?  3 : 11, 255);
  delay(delayLength);
}

void fullSteps(int count, int delayLength) {
  bool clockwise = count > 0;
  if (count < 0) count = - count;
  while (count-- > 0) {
    quarterStep(true, true, delayLength);
    quarterStep(false, not clockwise, delayLength);
    quarterStep(true, false, delayLength);
    quarterStep(false, clockwise, delayLength);
  }
}

void loop() {
  // the potentiometer gives a value from 0 - 1023
  // this gets translated into a direction and speed
  int mapped = map(analogRead(2), 0, 1023, -512, 512);
  int signum = mapped / abs(mapped);
  // central values are clipped to avoid hysteresis
  // extremal values are clipped for safety
  if (abs(mapped) > 75 and abs(mapped) < 500) {
      fullSteps(signum, map(abs(mapped), 75, 500, 200, 8));
  }
//  Serial.println(mapped);
}
