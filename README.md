# 1 创建工程

使用 STM32CubeMx 创建 STM32F103C8T6 HAL 库工程, 配置时钟树最大时钟频率 72Mhz

分配 IO 资源, 如下所示

| IO 编号    | 外设     |
| ---------- | -------- |
| PA4        | LED 灯   |
| PA5        | 用户按键 |
| PA9, PA10  | 串口     |
| PA13, PA14 | SWD 接口 |

配置串口参数: 波特率 115200, 数据位 8, 停止位 1, 无校验, 暂不开启中断

## 1.1 添加文件夹和辅助文件

* 添加 build.sh 脚本文件, 用来编译下载 (使用 openocd)
* 添加 .gitignore 文件, 忽略某些文件的 git 版本管理
* 添加 STM32F103.svd 文件, 用来调试时查看寄存器的值
* 添加 .clang-format 文件, 统一文件格式化规范
* 添加 clang-format.py 脚本文件, 使用 clang-format 批量格式化指定文件夹下的源文件
* 添加 .vscode 文件夹, 在此文件夹下创建 launch.json, tasks.json, settings.json

ctrl+shift+p 打开命令搜索窗口, 配置 C/C++ 插件, 在 .vscode 文件夹下新增 c_cpp_properties.json 文件

> 使用  C/C++ 补全, 因为 clangd 对宏的补全不完美, 并且对 doxygen 注释显示的很差劲

# 2 编写外设驱动

led 驱动, oled 驱动, mpu6050 驱动

## 2.1 oled 驱动编写

驱动 IC: SSD1306, 屏幕分辨率 128*64, 通信方式: 3 线 SPI

IO 资源分配: 

| IO 编号 | oled 引脚名称 |
| ------- | ------------- |
| PA15    | DC            |
| PB3     | RST           |
| PB4     | SDA           |
| PB5     | SCL           |
