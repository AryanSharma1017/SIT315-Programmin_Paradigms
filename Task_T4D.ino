const int Pir = 2;
const int Bpin = 3;
const int TrigPin = 6; 
const int EchoPin = 7;
const int Pin_PCINT = 4; 
volatile bool Movement = false;
volatile bool Interupted = false;
volatile bool PCINT_CHECK = false;
volatile int count_cycle = 0;

void setup() {
  pinMode(Pir, INPUT);
  pinMode(9, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(Bpin,INPUT_PULLUP);
  pinMode(Pin_PCINT, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(Pir), WhenInterrupted, RISING);
  attachInterrupt(digitalPinToInterrupt(Bpin), WhenInterrupted2, FALLING);
  
  
  PCICR |= (1 << PCIE2); 
  PCMSK2 |= (1 << PCINT20);
  
  
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0; 
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop() {
  
  long Times, Distance;
  
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  Times = pulseIn(EchoPin, HIGH);
  
  
  Distance = Times * 0.034 / 2;
  
  
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
  
  if(PCINT_CHECK)
  {
    Serial.print("The Present Distance is: ");
    Serial.print(Distance);
    Serial.println(" cm");
    delay(1000);
    PCINT_CHECK = false;
    
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

ISR(PCINT2_vect) {
  PCINT_CHECK = true;
}

ISR(TIMER1_COMPA_vect) {
  count_cycle++;
  if (count_cycle == 5) {
    digitalWrite(11, HIGH); 
    delay(1000); 
    digitalWrite(11, LOW);
    count_cycle = 0; 
  }
}



