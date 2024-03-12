#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "show.h"
#include "oled.h"
#include "sys.h"

/* ANCHOR - 公共函数定义 */

void OLED_Show(void)
{
    /* 第一行: 显示小车运行模式 */
    if (Way_Angle == 1)
        OLED_ShowString(0, 0, "DMP");
    else if (Way_Angle == 2)
        OLED_ShowString(0, 0, "Kalman");
    else if (Way_Angle == 3)
        OLED_ShowString(0, 0, "C F");

    if (Flag_follow == 1)
        OLED_ShowString(70, 0, "Follow");
    else if (Flag_avoid == 1)
        OLED_ShowString(70, 0, "Avoid ");
    else
        OLED_ShowString(70, 0, "Normal");

    /* 第二行: 显示角度 */
    OLED_ShowString(0, 10, "Angle");
    if (MPU6050_Data.pitch < 0)
        OLED_ShowString(48, 10, "-");
    if (MPU6050_Data.pitch >= 0)
        OLED_ShowString(48, 10, "+");
    OLED_ShowNumber(56, 10, abs((int)MPU6050_Data.pitch), 3, 12);

    /* 第三行: 显示角速度和超声波测距的距离 */
    OLED_ShowString(0, 20, "Gyrox");
    if (MPU6050_Data.gyro_y < 0)
        OLED_ShowString(42, 20, "-");
    if (MPU6050_Data.gyro_y >= 0)
        OLED_ShowString(42, 20, "+");
    OLED_ShowNumber(50, 20, abs((int)MPU6050_Data.gyro_y), 4, 12);

    OLED_ShowNumber(82, 20, (u16)Hcsr04Info.distance, 5, 12);
    OLED_ShowString(114, 20, "mm");

    /* 第四行: 显示左编码器读数与左电机速度 (mm/s) */
    OLED_ShowString(00, 30, "L");
    if (Encoder_Data.encoder_count_l < 0)
        OLED_ShowString(16, 30, "-"), OLED_ShowNumber(26, 30, abs((int)Encoder_Data.encoder_count_l), 4, 12);
    if (Encoder_Data.encoder_count_l >= 0)
        OLED_ShowString(16, 30, "+"), OLED_ShowNumber(26, 30, abs((int)Encoder_Data.encoder_count_l), 4, 12);

    if (Motor_Data.Velocity_Left < 0)
        OLED_ShowString(60, 30, "-");
    if (Motor_Data.Velocity_Left >= 0)
        OLED_ShowString(60, 30, "+");
    OLED_ShowNumber(68, 30, abs((int)Motor_Data.Velocity_Left), 4, 12);
    OLED_ShowString(96, 30, "mm/s");

    /* 第五行: 显示右编码器读数与右电机速度 (mm/s) */
    OLED_ShowString(0, 40, "R");
    if (Encoder_Data.encoder_count_r < 0)
    {
        OLED_ShowString(16, 40, "-");
        OLED_ShowNumber(26, 40, abs((int)Encoder_Data.encoder_count_r), 4, 12);
    }
    if (Encoder_Data.encoder_count_r >= 0)
    {
        OLED_ShowString(16, 40, "+");
        OLED_ShowNumber(26, 40, abs((int)Encoder_Data.encoder_count_r), 4, 12);
    }

    if (Motor_Data.Velocity_Right < 0)
        OLED_ShowString(60, 40, "-");
    if (Motor_Data.Velocity_Right >= 0)
        OLED_ShowString(60, 40, "+");
    OLED_ShowNumber(68, 40, abs((int)Motor_Data.Velocity_Right), 4, 12);
    OLED_ShowString(96, 40, "mm/s");

    /* 第六行: 显示电压与电机开关 */
    OLED_ShowString(0, 50, "V");
    OLED_ShowString(30, 50, ".");
    OLED_ShowString(64, 50, "V");
    OLED_ShowNumber(19, 50, Voltage / 100, 2, 12);
    OLED_ShowNumber(42, 50, Voltage / 10 % 10, 1, 12);
    OLED_ShowNumber(50, 50, Voltage % 10, 1, 12);
    if (Flag_Stop)
        OLED_ShowString(95, 50, "OFF");
    if (!Flag_Stop)
        OLED_ShowString(95, 50, "ON ");

    /* 刷新显示 */
    OLED_Refresh_Gram();
}

#ifdef __cplusplus
}
#endif
