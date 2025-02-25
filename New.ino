#define DriverMotorA1 5
#define DriverMotorA2 6
#define DriverMotorB1 10
#define DriverMotorB2 11

#include <NewPing.h>
#define TriggerKanan 2
#define EchoKanan 3
//#define TriggerKiri 13
//#define EchoKiri 12
#define TriggerKiri 7
#define EchoKiri 8
//#define TriggerTengah 9
//#define EchoTengah 8
#define TriggerTengah 12
#define EchoTengah 13
#define JumlahSensor 3
#define JarakMaksimum 300

// Variables for distances
float JarakKanan = 0;
float JarakKiri = 0;
float JarakTengah = 0;
int lms = 220;
int rms=255;

NewPing Ultrasonik[JumlahSensor] = {
    NewPing(TriggerKanan, EchoKanan, JarakMaksimum),
    NewPing(TriggerKiri, EchoKiri, JarakMaksimum),
    NewPing(TriggerTengah, EchoTengah, JarakMaksimum)
};

// Motor control functions
void mundur(int speedA, int speedB) {
    analogWrite(DriverMotorA1, speedA);
    analogWrite(DriverMotorA2, 0);
    analogWrite(DriverMotorB1, speedB);
    analogWrite(DriverMotorB2, 0);
}

void maju(int speedA, int speedB) {
    analogWrite(DriverMotorA1, 0);
    analogWrite(DriverMotorA2, speedA);
    analogWrite(DriverMotorB1, 0);
    analogWrite(DriverMotorB2, speedB);
}

void kiri(int speedA) { //Move the left motor forward
    analogWrite(DriverMotorA1, 0);
    analogWrite(DriverMotorA2, speedA);
    analogWrite(DriverMotorB1, 0);
    analogWrite(DriverMotorB2, 0);
}

void kanan(int speedB) { //Move the right motor forward 
    analogWrite(DriverMotorA1, 0);
    analogWrite(DriverMotorA2, 0);
    analogWrite(DriverMotorB1, 0);
    analogWrite(DriverMotorB2, speedB);
}

void berhenti() {
    digitalWrite(DriverMotorA1, LOW);
    digitalWrite(DriverMotorA2, LOW);
    digitalWrite(DriverMotorB1, LOW);
    digitalWrite(DriverMotorB2, LOW);
}

void StaticKiri(){
    analogWrite(DriverMotorA1, lms);
    analogWrite(DriverMotorA2, 0);
    analogWrite(DriverMotorB1, 0);
    analogWrite(DriverMotorB2, rms);
}
void StaticKanan(){
    analogWrite(DriverMotorA1, 0);
    analogWrite(DriverMotorA2, lms);
    analogWrite(DriverMotorB1, rms);
    analogWrite(DriverMotorB2, 0);
}

void backleft(int speedA) {
    analogWrite(DriverMotorA1, speedA);
    analogWrite(DriverMotorA2, 0);
    analogWrite(DriverMotorB1, 0);
    analogWrite(DriverMotorB2, 0);
}

void backright(int speedB) {
    analogWrite(DriverMotorA1, 0);
    analogWrite(DriverMotorA2, 0);
    analogWrite(DriverMotorB1, speedB);
    analogWrite(DriverMotorB2, 0);
}
int Check180(){
  StaticKiri();
  delay(500);
  berhenti();
  delay(200);
  bacadata();
  return JarakTengah;
  }

int getAveragePing(int sensorIndex) {
  int total = 0;
  for (int i = 0; i < 3; i++) {
    total += Ultrasonik[sensorIndex].ping_cm();
    delay(20); 
  }
  return total / 3;
}
void bacadata(){
  
  JarakKanan = Ultrasonik[0].ping_cm();
  Serial.print("Kanan = ");
  Serial.println(JarakKanan);
  JarakKiri = Ultrasonik[1].ping_cm();
  Serial.print("kiri = ");
  Serial.println(JarakKiri);
  JarakTengah = Ultrasonik[2].ping_cm();
  Serial.print("Tengah = ");
  Serial.println(JarakTengah);

}
void setup() {
  int K;
  bool rightWall,leftWall;
    Serial.begin(9600);
    Serial.println("Mulai");
    pinMode(DriverMotorA1, OUTPUT);
    pinMode(DriverMotorA2, OUTPUT);
    pinMode(DriverMotorB1, OUTPUT);
    pinMode(DriverMotorB2, OUTPUT);
}

//maju should be 50 more ms.
//15cm optimal 
//Stops around 5-10 inaccuracy centimeters from condition ( Example Stop if JarakTengah<=20 ) It'll stop and have 15cm infront of it.
void loop() {
  
  int JTKI,JTKA,JKDKA,JKDKI,JTKa,JTKi,JCL,JCR;
  
    bacadata();
    int lms=240;
    int rms=241;

  int K,JK,AKA,AKI;
  unsigned long startTime = 0;
  bool timerRunning = false;
  bool conditionMet = false;
  float previousDistance = 0;
  const float margin = 10.0; // Allowable difference in distance
  const int timeThreshold = 3000; // Time threshold in milliseconds (3 seconds)


 if (JarakKanan <= 8 && JarakTengah != 0 && JarakKanan != 0) {
        Serial.println("Near right wall, adjusting and entering right wall-following...");
        StaticKiri();  // Adjust from the right wall
        delay(90);
        berhenti();
        delay(250);
  // Ensure it does not follow the left wall if following right
    }

  if (JarakKiri <= 8 && JarakTengah != 0 && JarakKiri != 0) { //You can bank on not moving this in order to avoid it moving to the middle
        Serial.println("Near left wall, adjusting and entering left wall-following...");
        StaticKanan();  // Adjust from the left wall
        delay(90);
        berhenti();
        delay(250);
    }


  if (JarakTengah<=10 && JarakTengah!=0){
      mundur(lms,rms);
      delay(100);
      berhenti();
      delay(200);
      bacadata();

      //Adjusting Perpendicular | Trump card
    if (JarakKiri - JarakKanan >= 5) {
      berhenti();
      delay(100);
      unsigned long startTime = millis(); // Record the start time for the failsafe
      while (getAveragePing(1) - getAveragePing(0) >= 5) { 
        backright(rms);
        delay(60); //Lower for better accuracy
        berhenti();
        delay(400);
          if (millis() - startTime > 2500) {  // 3 sec
            Serial.println("Failsafe ");
            break; // Exit the loop if the time exceeds the limit
      }
  }
}
    if (JarakKanan - JarakKiri >= 5) {
      berhenti();
      delay(100);
      unsigned long startTime = millis(); // Record the start time for the failsafe
        while (getAveragePing(0) - getAveragePing(1) >= 5) {
          backleft(lms);
          delay(60);
          berhenti();
          delay(400);
              if (millis() - startTime > 2500) {  // 3 Sec
                Serial.println("Failsafe ");
                break; // Exit the loop if the time exceeds the limit
    }
  }
}
if (JarakTengah<17){
  berhenti();
  delay(100);
  unsigned long startTime = millis(); // Record the start time for the failsafe
  while (getAveragePing(2)<12){
  mundur(lms,rms);
  delay(100);
  berhenti();
  delay(200);
  if (millis() - startTime > 2500) {  // 3 Sec
      Serial.println("Failsafe ");
      break; // Exit the loop if the time exceeds the limit
    }
  }
}
    berhenti(); //Check if obstacle is too close to turn
    delay(200);
    kiri(lms);
    delay(200);
    berhenti();
    delay(300);
    bacadata();
    JCL=Ultrasonik[0].ping_cm();
    if (JCL<=5){
      mundur(lms,rms);
      delay(100);
      berhenti();
      delay(200);
      backleft(lms);
      delay(200);
      berhenti();
      delay(300);
      }
      else{
        backleft(lms);
        delay(200);
        berhenti();
        delay(300);
        kanan(rms);
        delay(200);
        berhenti();
        delay(300);
        bacadata();
        JCR=Ultrasonik[1].ping_cm();
        if (JCR<=5){
          mundur(lms,rms);
          delay(100);
          berhenti();
          delay(300);
          backright(rms);
          delay(200);
          berhenti();
          delay(300);
        }
        else{
          backright(rms);
          delay(200);
          berhenti();
          delay(300);
        }
      }
      //Change to 90 degree
      StaticKiri();
      delay(175);
      berhenti();
      delay(300);
      bacadata();
      JK=JarakKiri;
      StaticKanan();
      delay(290); 
      berhenti();
      delay(300);
      bacadata();
      if (JarakKanan>JK){
        StaticKanan();
        delay(110);
        berhenti();
        delay(250);
      }
      else{
        StaticKiri();
        delay(430); //Change if too much
        berhenti();
        delay(300);
      }

  }
  else{
  maju(lms,rms);
  
  }
}