const int Pir= 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(Pir,INPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(Pir) == HIGH)
  {
    Serial.println("There is a movement");
    digitalWrite(5, HIGH);
  }
  if(digitalRead(Pir) == LOW)
  {
    Serial.println("There is no movement");
    digitalWrite(5, LOW);
  }

  delay(1000);
}

