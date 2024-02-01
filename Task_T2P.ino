const int Pir = 2;
volatile bool Movement = false;

void setup() {
  pinMode(Pir, INPUT);
  pinMode(9, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(Pir), WhenInterrupted, RISING);
}

void loop() {
  if (Movement) 
  {
    Serial.println("There is a movement");
    digitalWrite(9, HIGH);
    digitalWrite(5, LOW);
    delay(2000);
    Movement = false;
    
  } 
  
  else 
  {
    Serial.println("There is no movement");
    digitalWrite(5, HIGH);
    digitalWrite(9, LOW);
  }

  delay(1000);
}

void WhenInterrupted() {
  Movement = true;
  
}
