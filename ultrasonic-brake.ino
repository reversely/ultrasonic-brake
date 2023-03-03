#include <Servo.h>

const int TRIG_PIN  = 6; const int ECHO_PIN  = 7;  const int SERVO_PIN = 9;
const double DISTANCE_THRESHOLD = 20.0; //cm
const int pulseDuration = 10;

Servo servo;

double duration_us, distance_cm;

void setup() {
  Serial.begin (9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN);
  servo.write(0);
}

//Arduino will be responsible for both the breaking and the release of the lander. Break it into different fucntions.
void breakMechanism(double &dist);
void releaseMechanism(double &dist);

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(pulseDuration);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance

  distance_cm = 0.017 * duration_us;

  if(distance_cm > DISTANCE_THRESHOLD)
    servo.write(90); // rotate servo motor to 90 degrees
  else
    servo.write(0);  // rotate servo motor to 0 degrees

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}
