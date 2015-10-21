#include <arduino.h>
// 全局变量：
// pos 超声波传感器转动角度
// Distance 超声波测定的距离

#include "ultrasonic/ultrasonic.h"
// 提供如下函数：
// servo_and_pwm_setup() 舵机和超声波传感器初始化设置
// servo_and_pwm() 舵机和超声波传感器运行

#include "speed-and-direction/speed-and-direction.h"
// 提供如下函数：
// set_speed_setup() 速度初始化设置
// set_speed(int left, int right, int didr) 设置左右轮子速度，大小从0-225，两轮一样。dir控制方向
// 1 前，0 后
// 


void find_wall_setup() {
  Serial.begin(9600);
  // set_speed_setup();
  // servo_and_pwm_setup();
  myservo.attach(10); 
  // set_speed(50, 50, 1);
}

// int pos = 0; 

void update_distance() {
  for(pos = 0; pos <= 180; pos += 1) {                               
    myservo.write(pos);            
    delay(5);
    // if (pos >= 0 && pos <= 5) PWM_Mode();                      
  }

  for(pos = 180; pos >= 0; pos -= 1) {                                
    myservo.write(pos);             
    delay(5);
    // if (pos >= 0 && pos <= 5) PWM_Mode();                       
  } 
  Serial.println("wujiarong");
}

void find_wall() {
  // servo_and_pwm();
  update_distance();
  // updata_distance();

  if (pos >= 0 && pos <= 5) {
    if (Distance > 50) {
      set_speed(50, 40, 1);
    }
    else if (Distance < 30) {
      set_speed(40, 50, 1);
    } else {
      set_speed(50, 50, 1);
    }

  // Serial.println("wu");
  }
}

