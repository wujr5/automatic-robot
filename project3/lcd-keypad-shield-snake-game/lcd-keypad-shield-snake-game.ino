#include <LiquidCrystal.h>

/*******************************************************

这个程序用来测试LCD液晶显示模块和5个按键。

********************************************************/

// 选择LCD上使用到的引脚
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// 定义各按键
int lcd_key     = 0;
int adc_key_in  = 0;
bool is_complete_movement = false;
int food = 5;
int is_game_over = false;
String LCD[2] = {"                ", "                "};

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SELECT 4
#define NONE   5

#define MAXLEN 16

struct SNAKE {
  int body[MAXLEN];
  int len;
  int dir;
} Snake;

//读取按键值
int read_LCD_buttons() {
 // 从模拟口0读值 
 
 // 直接读到的5个按键值在以下值附近：0,144,329,504,741
 // 通过设定不同的阀值，就可以对应读到相应的按键
 
  if (adc_key_in > 1000) return NONE; 
  if (adc_key_in < 50)   return RIGHT;  
  if (adc_key_in < 250)  return UP; 
  if (adc_key_in < 450)  return DOWN; 
  if (adc_key_in < 650)  return LEFT; 
  if (adc_key_in < 850)  return SELECT;  

  return NONE; 
}

int create_food() {
  int food = random(32);
  int ran = 5;
  while (true) {
    if (LCD[food/16][food%16] == ' ') break;
    else {
      if (food + ran >= 32) {
        food = (food + ran) % 32;
        ran--;
      } else {
        food = (food + ran) % 32;
      }
    }
  }
  return food;
}

bool is_hit_snake_body(int next) {
  for (int i = 1; i < Snake.len; i++) {
    if (next == Snake.body[i]) return true;
  }
  return false;
}

void record_LCD_button() {
  adc_key_in = analogRead(0);
  while(read_LCD_buttons() == NONE && is_complete_movement)  adc_key_in = analogRead(0);
  is_complete_movement = false;
}

void init_snake() {
  for (int i = 0; i < 16; i++)
    Snake.body[i] = 0;

  Snake.body[0] = 0;
  Snake.len = 1;
  Snake.dir = RIGHT;
}

void print_text(String t) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(t);
  delay(500);
  lcd.clear();
  delay(500);
  lcd.print(t);
  delay(500);
  lcd.clear();
}

void print_snake() {
  LCD[0] = "                ";
  LCD[1] = "                ";
  for (int i = 0; i < Snake.len; i++) {
    LCD[Snake.body[i]/16][Snake.body[i]%16] = '#'; 
  }

  int head = Snake.len - 1;

  if (Snake.dir == UP) LCD[Snake.body[head]/16][Snake.body[head]%16] = '^';
  else if (Snake.dir == DOWN) LCD[Snake.body[head]/16][Snake.body[head]%16] = 'v';
  else if (Snake.dir == LEFT) LCD[Snake.body[head]/16][Snake.body[head]%16] = '<';
  else LCD[Snake.body[head]/16][Snake.body[head]%16] = '>';

  LCD[food/16][food%16] = '*';

  lcd.setCursor(0, 0);
  lcd.print(LCD[0]);
  lcd.setCursor(0, 1);
  lcd.print(LCD[1]);
}

void move_up() {
  if (Snake.dir == DOWN && Snake.len > 1) return;
  Snake.dir = UP;

  if (is_hit_snake_body((Snake.body[Snake.len-1] + 16) % 32)) {
    is_game_over = true;
    return;
  }
  
  if ((Snake.body[Snake.len-1] + 16) % 32 == food) {
    Snake.body[Snake.len] = (Snake.body[Snake.len-1] + 16) % 32;
    Snake.len++;
    food = create_food();
  } else {
    int len = Snake.len - 1;
    for (int i = 0; i < len; i++) {
      Snake.body[i] = Snake.body[i+1];
    }
    Snake.body[len] = (Snake.body[len] + 16) % 32;
  }
}

void move_down() {
  if (Snake.dir == UP && Snake.len > 1) return;
  Snake.dir = DOWN;

  if (is_hit_snake_body((Snake.body[Snake.len-1] + 16) % 32)) {
    is_game_over = true;
    return;
  }

  if ((Snake.body[Snake.len-1] + 16) % 32 == food) {
    Snake.body[Snake.len] = (Snake.body[Snake.len-1] + 16) % 32;
    Snake.len++;
    food = create_food();
  } else {
    int len = Snake.len - 1;
    for (int i = 0; i < len; i++) {
      Snake.body[i] = Snake.body[i+1];
    }
    Snake.body[len] = (Snake.body[len] + 16) % 32;
  }
}

void move_left() {
  if (Snake.dir == RIGHT && Snake.len > 1) return;
  Snake.dir = LEFT;

  int next;
  if (Snake.body[Snake.len - 1] / 16 == 0) next = (Snake.body[Snake.len-1] - 1 + 16) % 16;
  else next = (Snake.body[Snake.len-1] - 1 + 16) % 16 + 16;
  
  if (is_hit_snake_body(next)) {
    is_game_over = true;
    return;
  }
  
  if ((Snake.body[Snake.len-1] - 1 + 32) % 32 == food) {
    if (Snake.body[Snake.len - 1] / 16 == 0) Snake.body[Snake.len] = (Snake.body[Snake.len-1] - 1 + 16) % 16;
    else Snake.body[Snake.len] = (Snake.body[Snake.len-1] - 1 + 16) % 16 + 16;
    Snake.len++;
    food = create_food();
  } else {
    int len = Snake.len - 1;
    for (int i = 0; i < len; i++) {
      Snake.body[i] = Snake.body[i+1];
    }
    if (Snake.body[len] / 16 == 0) Snake.body[len] = (Snake.body[len] - 1 + 16) % 16;
    else Snake.body[len] = (Snake.body[len] - 1 + 16) % 16 + 16;
  }
  
}

void move_right() {
  if (Snake.dir == LEFT && Snake.len > 1) return;
  Snake.dir = RIGHT;
  
  int next;
  if (Snake.body[Snake.len - 1] / 16 == 0) next = (Snake.body[Snake.len-1] + 1) % 16;
  else next = (Snake.body[Snake.len-1] + 1) % 16 + 16;
    
  if (is_hit_snake_body(next)) {
    is_game_over = true;
    return;
  }
  
  if ((Snake.body[Snake.len-1] + 1) % 32 == food) {
    if (Snake.body[Snake.len - 1] / 16 == 0) Snake.body[Snake.len] = (Snake.body[Snake.len-1] + 1) % 16;
    else Snake.body[Snake.len] = (Snake.body[Snake.len-1] + 1) % 16 + 16;
    Snake.len++;
    food = create_food();
  } else {
    int len = Snake.len - 1;
    for (int i = 0; i < len; i++) {
      Snake.body[i] = Snake.body[i+1];
    }
    if (Snake.body[len] / 16 == 0) Snake.body[len] = (Snake.body[len] + 1) % 16;
    else Snake.body[len] = (Snake.body[len] + 1) % 16 + 16;
  }
  
}

void move_snake_manually() {
  switch(read_LCD_buttons()) {
    case UP: {
      move_up();
      break;
    }
    case DOWN: {
      move_down();
      break;
    }
    case LEFT: {
      move_left();
      break;
    }
    case RIGHT: {
      move_right();
      break;
    }
  }
}

void setup() {
  lcd.begin(16, 2);     // 初始化16列,2行lcd
  print_text("The Snake Game!");
  init_snake();
  print_snake(); 
//  run_led_code_setup();
}

void loop() {
  if (Snake.len == MAXLEN) {
    print_text("You Win!");
  } else {
    if (is_game_over) {
      print_text("Game Over!");
    } else {
      record_LCD_button();
      move_snake_manually();
      print_snake();
      delay(150);
      is_complete_movement = true;
    }
  }

//  if (digitalRead(21) == HIGH && last_sensor_value == 0) {
//    run_jiyuan_code();
//  }
//  else if (digitalRead(21) == LOW && last_sensor_value == 1) {
//    run_jingtao_code();
//  }
}

