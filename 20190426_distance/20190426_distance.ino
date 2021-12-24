const int triggerPin = 12;
const int echoPin = 13;
long duration = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(triggerPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);

  long distance_mm = Distance(duration);

  Serial.print("distance = ");
  Serial.print(distance_mm/10);
  Serial.println(" cm");
  
  delay(1000);
}

long Distance(long time) {
  long distanceCalc;
  distanceCalc = ((time/2.9)/2);
  
  return distanceCalc;
}
