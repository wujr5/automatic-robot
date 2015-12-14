
int LED[] = {51, 53, 52, 50,
             47, 49, 48, 46,
             43, 45, 44, 42,
             39, 41, 40, 38,
             35, 37, 36, 34};
             
int light[4] = {0};

int num = 4;
void flash() {
    int tmp = 0;
    for (int i = 0; i < num * num; i++) {
        if (light[tmp / 4] != i % 4) {
            digitalWrite(LED[i], LOW);
        } else {
            digitalWrite(LED[i], HIGH);
        }
        tmp ++;
    }
    delay(200);
    return;
}

bool place(int k) {
    for (int j = 0; j < k; j++) {
        if (abs(light[k] - light[j]) == abs(k - j) || light[k] == light[j]) {
            return false;
        }
    }
    return true;
}

void blinkLED() {
    for (int i = 0; i < num * num; i++) {
        digitalWrite(LED[i], LOW);
    }
    delay(100);
    flash();
    return;
}

void backTrack(int t) {
    if (t >= num) {
        blinkLED();
        return;
    } else {
        for (int i = 0; i < num; i++) {
            light[t] = i;
            flash();
            if (place(t)) {
                backTrack(t + 1);
            }
        }
    }
}

void run_jiyuan_code() {
  for (int i = 0; i < num; i++) {
        light[i] = -1;
    }
    backTrack(0);
}

void run_jingtao_code() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED[i*4+3], HIGH);
    delay(100);
  }
  for (int i = 15; i >12; i--) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 3; i > 0; i--) {
    digitalWrite(LED[i*4], HIGH);
    delay(100);
  }
  for (int i = 5; i < 7; i++) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 10; i > 8; i--) {
    digitalWrite(LED[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < 16; i++) {
    digitalWrite(LED[i], LOW);
    delay(200);
  }
}

void setup() {
  pinMode(21, INPUT);
  pinMode(20, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(50, OUTPUT);

  digitalWrite(20, HIGH);
  for (int i = 0; i < 16; i++) {
    pinMode(LED[i], OUTPUT);
  }
}

void loop() {
  if (digitalRead(21) == HIGH) {
    run_jiyuan_code();
  } else {
    run_jingtao_code();
  }
}
