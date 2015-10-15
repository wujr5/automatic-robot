//首先启用定时器库和信号量库，下面会用到

#define PT_USE_TIMER
#define PT_USE_SEM

//引用库
#include "pt.h"

static struct pt thread1,thread2; //创建两个任务
static struct pt_sem sem_LED; //来个LED的信号量，同一时间只能一个任务占用
unsigned char i; //循环变量，写在这里其实不合适

void setup() {
  //初始化13口和串口
  pinMode(13,OUTPUT);
  Serial.begin(115200);

  PT_SEM_INIT(&sem_LED,1); //初始化信号量为1，即没人用
  //初始化任务记录变量
  PT_INIT(&thread1);
  PT_INIT(&thread2);
}
//这是LED慢速闪烁的任务
static int thread1_entry(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_SEM_WAIT(pt,&sem_LED); //LED有在用吗？
    //没有
    digitalWrite(13,!digitalRead(13));
    PT_TIMER_DELAY(pt,1000);//留一秒
    PT_SEM_SIGNAL(pt,&sem_LED);//用完了。
    PT_YIELD(pt); //看看别人要用么？
  }
  PT_END(pt);
}


//这是LED快速闪烁的任务，如果有串口消息，快速闪5次
static int thread2_entry(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    PT_WAIT_UNTIL(pt, Serial.available()); //等到有串口消息再继续
    PT_SEM_WAIT(pt,&sem_LED);//我要用LED啊！
    //抢到使用权了，虐5次
    for (i=0;i<5;i++) {
      digitalWrite(13,HIGH);
      PT_TIMER_DELAY(pt,200);
      digitalWrite(13,LOW);
      PT_TIMER_DELAY(pt,200);
    }
    while (Serial.available())
    Serial.read();
    //清空串口数据，防止又来
    PT_SEM_SIGNAL(pt,&sem_LED); //归还LED使用权了
  }
  PT_END(pt);
}

void loop() {
  //依次调用即可
  thread1_entry(&thread1);
  thread2_entry(&thread2);
}

