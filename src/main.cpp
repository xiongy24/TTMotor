#include <Arduino.h>

// 定义引脚
const int MOTOR_PIN_A = 25;  // 电机A相编码器输入
const int MOTOR_PIN_B = 26;  // 电机B相编码器输入
const int MOTOR_PWM = 13;    // 电机PWM控制引脚
const int MOTOR_DIR = 12;    // 电机方向控制引脚

// 编码器相关参数
volatile long encoderCount = 0;
const float COUNTS_PER_REVOLUTION = 360.0;  // TT电机一圈的编码器计数（可能需要根据实际电机调整）

// 编码器中断处理函数
void IRAM_ATTR encoderISR() {
  if (digitalRead(MOTOR_PIN_B)) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}

// 计算角度的函数（返回0-360度）
float getAngle() {
  float angle = (encoderCount * 360.0) / COUNTS_PER_REVOLUTION;
  // 将角度转换到0-360度范围内
  angle = fmod(angle, 360.0);
  if (angle < 0) {
    angle += 360.0;
  }
  return angle;
}

void setup() {
  Serial.begin(115200);
  Serial.println("系统启动");
  
  pinMode(MOTOR_PIN_A, INPUT_PULLUP);
  pinMode(MOTOR_PIN_B, INPUT_PULLUP);
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_DIR, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(MOTOR_PIN_A), encoderISR, RISING);
  
  ledcSetup(0, 5000, 8);
  ledcAttachPin(MOTOR_PWM, 0);
  
  Serial.println("初始化完成");
}

void loop() {
  // 电机转动测试
  Serial.println("正转 - 低速");
  digitalWrite(MOTOR_DIR, HIGH);
  ledcWrite(0, 128);  // 50%占空比
  
  // 持续2秒，每100ms打印一次角度
  for(int i = 0; i < 20; i++) {
    Serial.print("编码器计数: ");
    Serial.print(encoderCount);
    Serial.print("\t角度: ");
    Serial.print(getAngle(), 1); // 保留一位小数
    Serial.println("°");
    delay(100);
  }
  
  Serial.println("停止");
  ledcWrite(0, 0);
  delay(1000);
  
  // 打印最终位置
  Serial.print("最终角度: ");
  Serial.print(getAngle(), 1);
  Serial.println("°");
  delay(1000);
}