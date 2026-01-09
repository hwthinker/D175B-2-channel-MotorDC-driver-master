#include <EnableInterrupt.h>

/////////////////////////// FINAL CODE - FULL ENABLEINTERRUPT ///////////////////////////
//  Pin Board Arduino ------ Modul AT8236
//        Pin 9         ---        BIN2  (white)
//        Pin 8         ---        BIN1  (black)
//        Pin 7         ---        AIN2  (brown)
//        Pin 6         ---        AIN1  (red)

//        Pin 4         ---        E2A (brown)  - ENCODER KANAN FASE A
//        Pin 5         ---        E2B (red)    - ENCODER KANAN FASE B
//        Pin 3 (INT1)  ---        E1A (orange) - ENCODER KIRI FASE A
//        Pin 2 (INT0)  ---        E1B (yellow) - ENCODER KIRI FASE B
//        Pin A5        ---        ADC (green)
//         GND          ---        GND (blue)
//
//  Compatible: Arduino UNO, MEGA 2560, NANO
//  Method: EnableInterrupt for ALL pins (Pin 2,3,4,5)
//  Library: EnableInterrupt by Mike 'GreyGnome' Schwager

///////// Pin Output PWM ////////
#define BIN1 8
#define BIN2 9
#define AIN1 6
#define AIN2 7
#define Voltage A5

///////// Pin Encoder - FULL ENABLEINTERRUPT! ////////
#define ENCODER_L 3      // EnableInterrupt
#define DIRECTION_L 2    // EnableInterrupt (optional)
#define ENCODER_R 4      // EnableInterrupt
#define DIRECTION_R 5    // EnableInterrupt (optional)

///////// Konstanta ////////
#define ENCODER_PPR 780
#define SAMPLE_TIME 10
#define DISPLAY_INTERVAL 100
#define AUTO_REVERSE_TIME 2000

///////// Variabel Global ////////
volatile long Velocity_L = 0, Velocity_R = 0;
float Velocity_Left = 0, Velocity_Right = 0;

unsigned long currentTime = 0;
unsigned long encoderTime = 0;
unsigned long displayTime = 0;
unsigned long reverseTime = 0;

bool motorDirection = true;
bool autoReverse = true;
int pwmValue = 255;
double V;

unsigned long pulseCount_L = 0;
unsigned long pulseCount_R = 0;

///////// ISR - Interrupt Service Routine ////////

// ISR untuk Encoder Kiri
void ISR_ENCODER_L() {
  if (digitalRead(ENCODER_L) == LOW) {
    if (digitalRead(DIRECTION_L) == LOW) Velocity_L--;
    else Velocity_L++;
  } else {
    if (digitalRead(DIRECTION_L) == LOW) Velocity_L++;
    else Velocity_L--;
  }
  pulseCount_L++;
}

// ISR untuk Encoder Kanan
void ISR_ENCODER_R() {
  if (digitalRead(ENCODER_R) == LOW) {
    if (digitalRead(DIRECTION_R) == LOW) Velocity_R++;
    else Velocity_R--;
  } else {
    if (digitalRead(DIRECTION_R) == LOW) Velocity_R--;
    else Velocity_R++;
  }
  pulseCount_R++;
}

///////// Setup ////////
void setup() {
  // Pin PWM
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(Voltage, INPUT);

  // Pin Encoder
  pinMode(ENCODER_L, INPUT);  
  pinMode(DIRECTION_L, INPUT);
  pinMode(ENCODER_R, INPUT);
  pinMode(DIRECTION_R, INPUT);

  // ========== ENABLEINTERRUPT UNTUK SEMUA ==========
  
  // HANYA pakai enableInterrupt untuk pin 3 dan 4
  // JANGAN pakai attachInterrupt!
  
  enableInterrupt(ENCODER_L, ISR_ENCODER_L, CHANGE);  // Pin 3
  enableInterrupt(ENCODER_R, ISR_ENCODER_R, CHANGE);  // Pin 4
  
  // ==================================================

  // Matikan motor
  analogWrite(AIN1, 0);
  analogWrite(AIN2, 0);
  analogWrite(BIN1, 0);
  analogWrite(BIN2, 0);

  Serial.begin(9600);
  
  #if defined(__AVR_ATmega2560__)
    Serial.println(F("================================"));
    Serial.println(F("Arduino MEGA 2560 Detected"));
  #elif defined(__AVR_ATmega328P__)
    Serial.println(F("================================"));
    Serial.println(F("Arduino UNO/NANO Detected"));
  #else
    Serial.println(F("================================"));
    Serial.println(F("Arduino Board"));
  #endif
  
  Serial.println(F("AT8236 Motor Driver"));
  Serial.println(F("*** FULL INTERRUPT MODE ***"));
  Serial.println(F("Library: EnableInterrupt"));
  Serial.println(F("Both Encoders: Pin Change INT"));
  Serial.println(F("================================"));
  Serial.println(F("Commands:"));
  Serial.println(F("  0-255     : Set forward speed"));
  Serial.println(F("  -1 to -255: Set reverse speed"));
  Serial.println(F("  's'       : Stop motors"));
  Serial.println(F("  'a'       : Toggle auto-reverse"));
  Serial.println(F("  'r'       : Reset pulse counter"));
  Serial.println(F("  'i'       : Show info"));
  Serial.println(F("================================\n"));
  
  delay(1000);
}

///////// Motor Control Functions ////////
void Set_PWMA(int pwm) {
  if(pwm > 0) {
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255 - pwm);
  } else {
    analogWrite(AIN2, 255);
    analogWrite(AIN1, 255 + pwm);
  }
}

void Set_PWMB(int pwm) {
  if(pwm > 0) {
    analogWrite(BIN1, 255);
    analogWrite(BIN2, 255 - pwm);
  } else {
    analogWrite(BIN2, 255);
    analogWrite(BIN1, 255 + pwm);
  }
}

void stopMotors() {
  analogWrite(AIN1, 0);
  analogWrite(AIN2, 0);
  analogWrite(BIN1, 0);
  analogWrite(BIN2, 0);
}

void setMotors(int speed) {
  Set_PWMA(speed);
  Set_PWMB(speed);
}

///////// Serial Command Handler ////////
void handleSerialCommand() {
  if(Serial.available()) {
    char cmd = Serial.peek();
    
    if(cmd == 's' || cmd == 'S') {
      Serial.read();
      pwmValue = 0;
      stopMotors();
      Serial.println(F("\n>>> MOTORS STOPPED <<<\n"));
    }
    else if(cmd == 'a' || cmd == 'A') {
      Serial.read();
      autoReverse = !autoReverse;
      Serial.print(F("\n>>> Auto-Reverse: "));
      Serial.println(autoReverse ? F("ENABLED") : F("DISABLED"));
    }
    else if(cmd == 'r' || cmd == 'R') {
      Serial.read();
      noInterrupts();
      pulseCount_L = 0;
      pulseCount_R = 0;
      Velocity_L = 0;
      Velocity_R = 0;
      interrupts();
      Serial.println(F("\n>>> PULSE COUNTER RESET <<<\n"));
    }
    else if(cmd == 'i' || cmd == 'I') {
      Serial.read();
      Serial.println(F("\n=== SYSTEM INFO ==="));
      Serial.print(F("Board: "));
      #if defined(__AVR_ATmega2560__)
        Serial.println(F("MEGA 2560"));
      #elif defined(__AVR_ATmega328P__)
        Serial.println(F("UNO/NANO"));
      #else
        Serial.println(F("Unknown"));
      #endif
      Serial.print(F("PWM Value: "));
      Serial.println(pwmValue);
      Serial.print(F("Direction: "));
      Serial.println(motorDirection ? F("FORWARD") : F("REVERSE"));
      Serial.print(F("Auto-Reverse: "));
      Serial.println(autoReverse ? F("ON") : F("OFF"));
      Serial.print(F("Total Pulse L: "));
      Serial.println(pulseCount_L);
      Serial.print(F("Total Pulse R: "));
      Serial.println(pulseCount_R);
      Serial.print(F("Current RPM L: "));
      Serial.println(Velocity_Left, 1);
      Serial.print(F("Current RPM R: "));
      Serial.println(Velocity_Right, 1);
      Serial.println(F("==================\n"));
    }
    else {
      int input = Serial.parseInt();
      if(input != 0 || Serial.peek() == '0') {
        if(input >= -255 && input <= 255) {
          pwmValue = abs(input);
          motorDirection = (input >= 0);
          Serial.print(F("\n>>> PWM: "));
          Serial.print(pwmValue);
          Serial.print(F(" | Dir: "));
          Serial.println(motorDirection ? F("FORWARD") : F("REVERSE"));
        }
      }
    }
  }
}

///////// Main Loop ////////
void loop() {
  currentTime = millis();

  handleSerialCommand();

  if(autoReverse && currentTime - reverseTime >= AUTO_REVERSE_TIME) {
    reverseTime = currentTime;
    motorDirection = !motorDirection;
    Serial.print(F("\n>>> AUTO REVERSE: "));
    Serial.println(motorDirection ? F("FORWARD") : F("REVERSE"));
  }

  if(motorDirection) setMotors(pwmValue);
  else setMotors(-pwmValue);

  static unsigned long ledTime = 0;
  static bool ledState = false;
  if(currentTime - ledTime >= 500) {
    ledTime = currentTime;
    ledState = !ledState;
    digitalWrite(13, ledState);
  }

  if(currentTime - encoderTime >= SAMPLE_TIME) {
    encoderTime = currentTime;
    
    noInterrupts();
    long tempL = Velocity_L;
    long tempR = Velocity_R;
    Velocity_L = 0;
    Velocity_R = 0;
    interrupts();
    
    Velocity_Left = (tempL / (float)ENCODER_PPR) * (1000.0 / SAMPLE_TIME) * 60.0;
    Velocity_Right = (tempR / (float)ENCODER_PPR) * (1000.0 / SAMPLE_TIME) * 60.0;
  }

  if(currentTime - displayTime >= DISPLAY_INTERVAL) {
    displayTime = currentTime;
    
    Serial.print(F("L: "));
    Serial.print(Velocity_Left, 1);
    Serial.print(F(" RPM | R: "));
    Serial.print(Velocity_Right, 1);
    Serial.print(F(" RPM | V: "));
    
    V = analogRead(Voltage) * 0.05371;
    Serial.print(V, 2);
    Serial.print(F("V | PWM: "));
    Serial.print(pwmValue);
    Serial.print(F(" | "));
    Serial.println(motorDirection ? F("FWD") : F("REV"));
  }
}