// Pin-definities
#define TRIG_PIN 22
#define ECHO_PIN 23
#define MOTOR1_PIN 32
#define MOTOR2_PIN 33
#define MOTOR3_PIN 25
#define MOTOR4_PIN 26
#define MOTOR5_PIN 27
#define MOTOR6_PIN 14
#define POT_PIN 13
 
// Variabelen
long duration;
int distance = 0;
int potValue;
int distanceThreshold;
const int MIN_DISTANCE = 20;
String motorStatus;  // Nieuwe variabele voor statusbericht
 
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOTOR1_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);
  pinMode(MOTOR3_PIN, OUTPUT);
  pinMode(MOTOR4_PIN, OUTPUT);
  pinMode(MOTOR5_PIN, OUTPUT);  
  pinMode(MOTOR6_PIN, OUTPUT);
  Serial.begin(115200);
}
 
void loop() {
  // Ultrasone meting
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
 
  duration = pulseIn(ECHO_PIN, HIGH);
  int newDistance = duration * 0.034 / 2;
 
  if (newDistance >= MIN_DISTANCE) {
    distance = newDistance;
  }
 
  // Lees potmeter en schaal
  potValue = analogRead(POT_PIN);
  distanceThreshold = map(potValue, 0, 4095, 200, 400);
 
  // Motorcontrole met statusberichten
  if (distance > (distanceThreshold * 3 / 4) || distance >= 300) {
    digitalWrite(MOTOR1_PIN, LOW);
    digitalWrite(MOTOR2_PIN, LOW);
    digitalWrite(MOTOR3_PIN, LOW);
    digitalWrite(MOTOR4_PIN, LOW);
    digitalWrite(MOTOR5_PIN, LOW);
    digitalWrite(MOTOR6_PIN, LOW);
    motorStatus = "Geen motoren trillen";
  }
  else if (distance > (distanceThreshold * 2 / 4)) {
    digitalWrite(MOTOR1_PIN, HIGH);
    digitalWrite(MOTOR2_PIN, HIGH);
    digitalWrite(MOTOR3_PIN, LOW);
    digitalWrite(MOTOR4_PIN, LOW);
    digitalWrite(MOTOR5_PIN, LOW);
    digitalWrite(MOTOR6_PIN, LOW);
    motorStatus = "Motoren 1+2 trillen";
  }
  else if (distance > (distanceThreshold * 1 / 4)) {
    digitalWrite(MOTOR1_PIN, HIGH);
    digitalWrite(MOTOR2_PIN, HIGH);
    digitalWrite(MOTOR3_PIN, HIGH);
    digitalWrite(MOTOR4_PIN, HIGH);
    digitalWrite(MOTOR5_PIN, LOW);
    digitalWrite(MOTOR6_PIN, LOW);
    motorStatus = "Motoren 1+2+3+4 trillen";
  }
  else {
    digitalWrite(MOTOR1_PIN, HIGH);
    digitalWrite(MOTOR2_PIN, HIGH);
    digitalWrite(MOTOR3_PIN, HIGH);
    digitalWrite(MOTOR4_PIN, HIGH);
    digitalWrite(MOTOR5_PIN, HIGH);
    digitalWrite(MOTOR6_PIN, HIGH);
    motorStatus = "Alle motoren trillen";
  }
 
  // Debugging met motorstatus
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm | Threshold: ");
  Serial.print(distanceThreshold);
  Serial.print("| Status: ");
  Serial.println(motorStatus);  // Toon trilstatus
 
  //delay(100);
}
