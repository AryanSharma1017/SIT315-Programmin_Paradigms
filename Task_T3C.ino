const int Pir = 2;
const int Bpin = 3;
volatile bool Movement = false;
volatile bool Interupted = false;

void setup() {
  pinMode(Pir, INPUT);
  pinMode(9, OUTPUT);
  pinMode(Bpin,INPUT_PULLUP);
  pinMode(5, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(Pir), WhenInterrupted, RISING);
  attachInterrupt(digitalPinToInterrupt(Bpin), WhenInterrupted2, FALLING);
}

void loop() {
  int flexValue = analogRead(A0);
  if (Movement) 
  {
    Serial.println("There is a movement");
    digitalWrite(9, HIGH);
    digitalWrite(5, LOW);
    delay(2000);
    Movement = false;
    
  } 
  
  if(Interupted)
  {
    Serial.println("Interrupted");
    Serial.print("The value is: ");
    Serial.println(flexValue);
    delay(2000);
    Interupted = false;
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

void WhenInterrupted2()
{
  Interupted = true;
}
