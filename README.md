# ESP32 TT电机控制项目

本项目使用ESP32控制带编码器的TT电机，通过L298N驱动模块实现电机的速度和方向控制。项目可以实现电机的速度控制和角度反馈。

## 功能特点

- 电机速度PWM控制（0-255可调）
- 电机正反转控制
- 实时角度反馈（0-360度）
- 编码器计数显示
- 串口监视器实时显示运行状态

## 硬件需求

- ESP32开发板
- TT电机（带编码器，6个引脚）
- L298N电机驱动模块
- 6-12V电源
- 连接线

## 开发环境

- Visual Studio Code
- PlatformIO插件
- Arduino框架
- ESP32开发板支持包

## 详细接线说明

### L298N与ESP32的连接
| L298N引脚 | ESP32引脚 | 说明 |
|-----------|-----------|------|
| ENA       | GPIO13    | PWM速度控制 |
| IN1       | GPIO12    | 方向控制 |
| IN2       | GND       | 固定低电平 |


### L298N与电源的连接
| L298N引脚 | 连接目标 | 说明 |
|-----------|----------|------|
| 12V       | 电源正极 | 6-12V供电 |
| GND       | 电源负极 | 地线 |  

### TT电机与L298N的连接
| 电机引脚 | L298N引脚 | 说明 |
|----------|-----------|------|
| M+       | OUT1      | 电机正极 |
| M-       | OUT2      | 电机负极 |

### TT电机编码器与L298N/ESP32的连接
| 电机引脚 | 连接目标 | 说明 |
|----------|----------|------|
| 5V       | L298N的5V输出 | 编码器供电 |
| GND      | GND      | 地线 |
| A相      | GPIO25   | 编码器A相信号 |
| B相      | GPIO26   | 编码器B相信号 |

## 程序功能说明

1. 速度控制
   - PWM频率：5KHz
   - 速度范围：0-255（8位分辨率）
   - 当前设定：128（50%速度）

2. 角度反馈
   - 范围：0-360度
   - 精度：0.1度
   - 更新频率：10Hz（每100ms更新一次）

3. 运行模式
   - 电机低速运行2秒
   - 实时显示角度和编码器计数
   - 停止1秒
   - 循环执行

## 注意事项

2. L298N模块上的ENA跳线帽需要拔掉，以便使用PWM控制
3. 外部电源要求：
   - 电压：推荐12V（这样可以获得稳定的5V输出）
   - 电流：至少1A
4. L298N模块使用自身的5V为逻辑电平和编码器供电
5. 编码器信号可以直接连接到ESP32的GPIO引脚

## 串口监视器输出说明

程序运行时，串口监视器（波特率115200）将显示：
- 系统启动和初始化信息
- 电机运行状态（正转/停止）
- 实时编码器计数值
- 实时角度值（0-360度）

## 使用说明

1. 按照接线说明完成硬件连接
2. 使用PlatformIO编译并上传程序
3. 打开串口监视器（波特率115200）
4. 观察电机运行状态和角度反馈

## 常见问题

1. 如果电机不转动：
   - 检查电源供电
   - 确认L298N的ENA跳线帽已拔掉
   - 检查所有接线是否正确

2. 如果角度显示异常：
   - 检查编码器A、B相接线是否正确
   - 可能需要调整COUNTS_PER_REVOLUTION参数

3. 如果想改变电机速度：
   - 修改ledcWrite的参数（0-255）