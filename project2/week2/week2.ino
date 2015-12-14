
int light[] = {21, 20, 52, 50, 48, 46, 44, 42, 40, 38, 19, 18, 39, 41, 43, 45, 47, 49, 51, 53};
int len = 20;
int LN = 0;

void init_light();
int get_luminance();
void style1();
void style2();
void style3();
void style4();

void setup() {
  // put your setup code here, to run once:
  init_light();
}

void loop() {
  // put your main code here, to run repeatedly:
//  int sensor = analogRead(A0);
//  delay(1000);
//  Serial.print("sensor = " );
//  Serial.print(sensor);
//  Serial.print("\n");
  style1();
}

void init_light() {
  for (int i = 0; i < len; i++) {
    pinMode(light[i], OUTPUT);
  }
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  Serial.begin(9600);
}

int get_luminance() {
  int sensor = analogRead(A0);
  sensor -= 50;
  
  return sensor * sensor / 10;
//  return sensor;
}

int get_light_number() {
  int sensor = analogRead(A0);
  return (10 - sensor % 10);
}

void style1() {
  
  for (int i = 0; i < len; i++) {
    int delay_time = get_luminance();
//    int light_number = get_light_number();
    digitalWrite(light[(i - 2 + len) % len], LOW);
    digitalWrite(light[(i - 1 + len) % len], LOW);
    digitalWrite(light[(i) % len], HIGH);
    digitalWrite(light[(i + 1) % len], HIGH);
    
    delay(delay_time);

  }
}

