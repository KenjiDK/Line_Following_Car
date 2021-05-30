const int enA = A0;
const int enB = A1;

const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;

const int sensorLinks = 6;
int vallinks;

const int sensorRechts = 7;
int valrechts;

const int sensorMidden = 8;
int valmidden;

const int rood = 9;
const int groen = 10;
const int geel = A3;

const int knop = A2;
int knoppie = 0;

const int trig = 11;
const int echo = 12;
long tijd;
int afstand;

void setup() {
  Serial.begin(115200);
  
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  //pinMode(sensorLinks,INPUT);
  //pinMode(sensorRechts,INPUT);

  pinMode(rood,OUTPUT);
  pinMode(geel,OUTPUT);
  pinMode(groen,OUTPUT);

  pinMode(knoppie,INPUT);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}


void rechtdoor() {
  digitalWrite(rood,LOW);
  digitalWrite(geel,LOW);
  digitalWrite(groen,HIGH);
   
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  digitalWrite(enA,255);
  digitalWrite(enB,255);

  Serial.println("Rechtdoor");
}

void links() {
  digitalWrite(rood,LOW);
  digitalWrite(geel,LOW);
  digitalWrite(groen,HIGH);
    
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  digitalWrite(enA,0);
  digitalWrite(enB,255);

  Serial.println("Averechts");
}

void rechts() {
  digitalWrite(rood,LOW);
  digitalWrite(geel,LOW);
  digitalWrite(groen,HIGH);
    
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(enA,255);
  digitalWrite(enB,0);

  Serial.println("rechts");
}

void wachten() {
  digitalWrite(rood,LOW);
  digitalWrite(geel,HIGH);
  digitalWrite(groen,LOW);
    
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(enA,0);
  digitalWrite(enB,0);

  Serial.println("wachten");

  delay(5000);
}

void lijnkwijt() {
  digitalWrite(rood,HIGH);
  digitalWrite(geel,LOW);
  digitalWrite(groen,LOW);
    
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  digitalWrite(enA,0);
  digitalWrite(enB,0);

  Serial.println("Lijn kwijt");
}

void loop() {
  vallinks = digitalRead(sensorLinks);
  valrechts = digitalRead(sensorRechts);
  valmidden = digitalRead(sensorMidden);

  if (vallinks == LOW && valrechts == LOW) {
    digitalWrite(trig,HIGH);
    delay(2);
    digitalWrite(trig,LOW);
    tijd = pulseIn(echo,HIGH);
    afstand = tijd*0.034/2;
    Serial.println(afstand);

    if (afstand >= 5) {
      rechtdoor();
    }
    else {
      digitalWrite(rood,LOW);
      digitalWrite(geel,HIGH);
      digitalWrite(groen,LOW);
    
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      digitalWrite(enA,0);
      digitalWrite(enB,0);
    }
  }

  if (vallinks == HIGH && valrechts == LOW) {
    links();
  }

  if (vallinks == LOW && valrechts == HIGH) {
    rechts();
  }

  while (vallinks == HIGH && valrechts == HIGH) {
    wachten();
    if (knoppie == HIGH) {
      digitalWrite(rood,LOW);
      digitalWrite(geel,LOW);
      digitalWrite(groen,HIGH);
    
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      digitalWrite(enA,255);
      digitalWrite(enB,255);

      break;
    }
  }
  
  if (vallinks == LOW && valrechts == LOW && valmidden == LOW) {
    lijnkwijt();
  }
}
