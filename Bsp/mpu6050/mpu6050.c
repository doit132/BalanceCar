#ifdef __cplusplus
extern "C" {
#endif

/* ANCHOR - 头文件包含 */

#include "mpu6050.h"
#include "i2c.h"

/* ANCHOR - 宏定义 */

#define DEV_ADDR 0x68

/* MPU6050 寄存器地址 */
//[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_XG_OFFS_TC 0x00
//[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC 0x01
//[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC     0x02
#define MPU6050_RA_X_FINE_GAIN    0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN    0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN    0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H      0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC   0x07
#define MPU6050_RA_YA_OFFS_H      0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC   0x09
#define MPU6050_RA_ZA_OFFS_H      0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC   0x0B
#define MPU6050_RA_XG_OFFS_USRH   0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL   0x14
#define MPU6050_RA_YG_OFFS_USRH   0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL   0x16
#define MPU6050_RA_ZG_OFFS_USRH   0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL   0x18
#define MPU6050_RA_SMPLRT_DIV     0x19
#define MPU6050_RA_CONFIG         0x1A
#define MPU6050_RA_GYRO_CONFIG    0x1B
#define MPU6050_RA_ACCEL_CONFIG   0x1C
#define MPU6050_RA_FF_THR         0x1D
#define MPU6050_RA_FF_DUR         0x1E
#define MPU6050_RA_MOT_THR        0x1F
#define MPU6050_RA_MOT_DUR        0x20
#define MPU6050_RA_ZRMOT_THR      0x21
#define MPU6050_RA_ZRMOT_DUR      0x22
#define MPU6050_RA_FIFO_EN        0x23
#define MPU6050_RA_I2C_MST_CTRL   0x24
#define MPU6050_RA_I2C_SLV0_ADDR  0x25
#define MPU6050_RA_I2C_SLV0_REG   0x26
#define MPU6050_RA_I2C_SLV0_CTRL  0x27
#define MPU6050_RA_I2C_SLV1_ADDR  0x28
#define MPU6050_RA_I2C_SLV1_REG   0x29
#define MPU6050_RA_I2C_SLV1_CTRL  0x2A
#define MPU6050_RA_I2C_SLV2_ADDR  0x2B
#define MPU6050_RA_I2C_SLV2_REG   0x2C
#define MPU6050_RA_I2C_SLV2_CTRL  0x2D
#define MPU6050_RA_I2C_SLV3_ADDR  0x2E
#define MPU6050_RA_I2C_SLV3_REG   0x2F
#define MPU6050_RA_I2C_SLV3_CTRL  0x30
#define MPU6050_RA_I2C_SLV4_ADDR  0x31
#define MPU6050_RA_I2C_SLV4_REG   0x32
#define MPU6050_RA_I2C_SLV4_DO    0x33
#define MPU6050_RA_I2C_SLV4_CTRL  0x34
#define MPU6050_RA_I2C_SLV4_DI    0x35
#define MPU6050_RA_I2C_MST_STATUS 0x36
#define MPU6050_RA_INT_PIN_CFG    0x37
#define MPU6050_RA_INT_ENABLE     0x38
#define MPU6050_RA_DMP_INT_STATUS 0x39
#define MPU6050_RA_INT_STATUS     0x3A
/* 存储最近的 X 轴, Y 轴, Z 轴加速度感应器的测量值 */
#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40
/* 存储最近的温度感应器的测量值 */
#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42
/* 存储最近的 X 轴, Y 轴, Z 轴陀螺仪感应器的测量值 */
#define MPU6050_RA_GYRO_XOUT_H        0x43
#define MPU6050_RA_GYRO_XOUT_L        0x44
#define MPU6050_RA_GYRO_YOUT_H        0x45
#define MPU6050_RA_GYRO_YOUT_L        0x46
#define MPU6050_RA_GYRO_ZOUT_H        0x47
#define MPU6050_RA_GYRO_ZOUT_L        0x48
#define MPU6050_RA_EXT_SENS_DATA_00   0x49
#define MPU6050_RA_EXT_SENS_DATA_01   0x4A
#define MPU6050_RA_EXT_SENS_DATA_02   0x4B
#define MPU6050_RA_EXT_SENS_DATA_03   0x4C
#define MPU6050_RA_EXT_SENS_DATA_04   0x4D
#define MPU6050_RA_EXT_SENS_DATA_05   0x4E
#define MPU6050_RA_EXT_SENS_DATA_06   0x4F
#define MPU6050_RA_EXT_SENS_DATA_07   0x50
#define MPU6050_RA_EXT_SENS_DATA_08   0x51
#define MPU6050_RA_EXT_SENS_DATA_09   0x52
#define MPU6050_RA_EXT_SENS_DATA_10   0x53
#define MPU6050_RA_EXT_SENS_DATA_11   0x54
#define MPU6050_RA_EXT_SENS_DATA_12   0x55
#define MPU6050_RA_EXT_SENS_DATA_13   0x56
#define MPU6050_RA_EXT_SENS_DATA_14   0x57
#define MPU6050_RA_EXT_SENS_DATA_15   0x58
#define MPU6050_RA_EXT_SENS_DATA_16   0x59
#define MPU6050_RA_EXT_SENS_DATA_17   0x5A
#define MPU6050_RA_EXT_SENS_DATA_18   0x5B
#define MPU6050_RA_EXT_SENS_DATA_19   0x5C
#define MPU6050_RA_EXT_SENS_DATA_20   0x5D
#define MPU6050_RA_EXT_SENS_DATA_21   0x5E
#define MPU6050_RA_EXT_SENS_DATA_22   0x5F
#define MPU6050_RA_EXT_SENS_DATA_23   0x60
#define MPU6050_RA_MOT_DETECT_STATUS  0x61
#define MPU6050_RA_I2C_SLV0_DO        0x63
#define MPU6050_RA_I2C_SLV1_DO        0x64
#define MPU6050_RA_I2C_SLV2_DO        0x65
#define MPU6050_RA_I2C_SLV3_DO        0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU6050_RA_SIGNAL_PATH_RESET  0x68
#define MPU6050_RA_MOT_DETECT_CTRL    0x69
#define MPU6050_RA_USER_CTRL          0x6A
#define MPU6050_RA_PWR_MGMT_1         0x6B
#define MPU6050_RA_PWR_MGMT_2         0x6C
#define MPU6050_RA_BANK_SEL           0x6D
#define MPU6050_RA_MEM_START_ADDR     0x6E
#define MPU6050_RA_MEM_R_W            0x6F
#define MPU6050_RA_DMP_CFG_1          0x70
#define MPU6050_RA_DMP_CFG_2          0x71
#define MPU6050_RA_FIFO_COUNTH        0x72
#define MPU6050_RA_FIFO_COUNTL        0x73
#define MPU6050_RA_FIFO_R_W           0x74
#define MPU6050_RA_WHO_AM_I           0x75

/* MPU6050 时钟源 */
#define MPU6050_CLOCK_INTERNAL   0x00
#define MPU6050_CLOCK_PLL_XGYRO  0x01
#define MPU6050_CLOCK_PLL_YGYRO  0x02
#define MPU6050_CLOCK_PLL_ZGYRO  0x03
#define MPU6050_CLOCK_PLL_EXT32K 0x04
#define MPU6050_CLOCK_PLL_EXT19M 0x05
#define MPU6050_CLOCK_KEEP_RESET 0x07

/* MPU6050 加速度传感器的量程 */
#define MPU6050_ACCEL_FS_2  0x00
#define MPU6050_ACCEL_FS_4  0x01
#define MPU6050_ACCEL_FS_8  0x02
#define MPU6050_ACCEL_FS_16 0x03

/* MPU6050 陀螺仪传感器的量程 */
#define MPU6050_GYRO_FS_250  0x00
#define MPU6050_GYRO_FS_500  0x01
#define MPU6050_GYRO_FS_1000 0x02
#define MPU6050_GYRO_FS_2000 0x03

/* ANCHOR - 私有全局变量定义 */

/* 存储 MPU6050 加速度计和陀螺仪传感器的数据 */
static float ax, ay, az, temperature, gx, gy, gz;
/* 存储最终计算出的欧拉角 */
static float yaw, roll, pitch;

/* ANCHOR - 私有函数定义 */

/**
 * *****************************************************************************
 * @brief MPU6050 IIC 写寄存器数据
 * @param [in] DevAddr MPU6050 设备地址
 * @param [in] RegAddr 要写的寄存器地址
 * @param [in] data 写入的数据
 * @param [in] length 写入的数据长度
 * @return 是否成功
 * *****************************************************************************
 */
static int8_t MPU6050_IIC_Write(u8 DevAddr, u8 RegAddr, u8* data, u8 length)
{
    return HAL_I2C_Mem_Write(&hi2c1, DevAddr, RegAddr, 1, data, length, 1000);
}

/**
 * *****************************************************************************
 * @brief MPU6050 IIC 读寄存器中的内容
 * @param [in] DevAddr MPU6050 设备地址
 * @param [in] RegAddr 要读的寄存器地址
 * @param [in] data 存放读出的数据
 * @param [in] length 要读出的数据长度
 * @return 是否成功
 * *****************************************************************************
 */
static int8_t MPU6050_IIC_Read(u8 DevAddr, u8 RegAddr, u8* data, u8 length)
{
    return HAL_I2C_Mem_Read(&hi2c1, DevAddr, RegAddr, 1, data, length, 1000);
}

/**
 * *****************************************************************************
 * @brief MPU6050 复位
 * *****************************************************************************
 */
static void MPU6050_Reset(void)
{
    u8 temp[2];
    temp[0] = MPU6050_RA_PWR_MGMT_1;
    temp[1] = 0x80;
    MPU6050_IIC_Write(DEV_ADDR, temp[0], &temp[1], 1);
}

/**
 * *****************************************************************************
 * @brief 设置 MPU6050 休眠/唤醒模式
 * @param [in] mode 0: 唤醒 1: 休眠
 * *****************************************************************************
 */
static void MPU6050_Set_SleepMode(u8 mode)
{
    u8 temp[2];
    temp[0] = MPU6050_RA_PWR_MGMT_1;
    temp[1] = mode << 6;
    MPU6050_IIC_Write(DEV_ADDR, temp[0], &temp[1], 1);
}
/**
 * *****************************************************************************
 * @brief Construct a new mpu6050 set clocksource object
 * @param[in] source 时钟源编号                           
 * @note - 0       | Internal oscillator
 * @note - 1       | PLL with X Gyro reference
 * @note - 2       | PLL with Y Gyro reference
 * @note - 3       | PLL with Z Gyro reference
 * @note - 4       | PLL with external 32.768kHz reference
 * @note - 5       | PLL with external 19.2MHz reference
 * @note - 6       | Reserved
 * @note - 7       | Stops the clock and keeps the timing generator in reset
 * *****************************************************************************
 */
static void MPU6050_Set_ClockSource(u8 source)
{
    u8 temp[2];
    temp[0] = MPU6050_RA_PWR_MGMT_1;
    temp[1] = source;
    MPU6050_IIC_Write(DEV_ADDR, temp[0], &temp[1], 1);
}

/**
 * *****************************************************************************
 * @brief 设置 MPU6050 加速度计的最大量程
 * @param[in] range 加速度最大量程编号  
 * @note range 允许的取值
 * @note #define MPU6050_ACCEL_FS_2     0x00    // 最大量程+-2G
 * @note #define MPU6050_ACCEL_FS_4     0x01    // 最大量程+-4G
 * @note #define MPU6050_ACCEL_FS_8     0x02    // 最大量程+-8G
 * @note #define MPU6050_ACCEL_FS_16    0x03    // 最大量程+-16G
 * *****************************************************************************
 */
static void MPU6050_Set_AccelRange(u8 range)
{
    u8 temp[2];
    temp[0] = MPU6050_RA_ACCEL_CONFIG;
    temp[1] = range;
    MPU6050_IIC_Write(DEV_ADDR, temp[0], &temp[1], 1);
}

/**
 * *****************************************************************************
 * @brief 设置 MPU6050 加速度计的最大量程
 * @param[in] range 加速度最大量程编号  
 * @note range 允许的取值
 * @note - #define MPU6050_GYRO_FS_250  0x00
 * @note - #define MPU6050_GYRO_FS_500  0x01
 * @note - #define MPU6050_GYRO_FS_1000 0x02
 * @note - #define MPU6050_GYRO_FS_2000 0x03
 * *****************************************************************************
 */
static void MPU6050_Set_GyroRange(u8 range)
{
    u8 temp[2];
    temp[0] = MPU6050_RA_GYRO_CONFIG;
    temp[1] = range;
    MPU6050_IIC_Write(DEV_ADDR, temp[0], &temp[1], 1);
}

/* ANCHOR - 公共函数定义 */

/**
 * *****************************************************************************
 * @brief 设置 MPU6050 采样率
 * @param [in] rate 采样率
 * @note - 采样率 = 陀螺仪输出频率 / (SMPRT_DIV + 1)
 * @note - 复位后陀螺仪输出频率是 8kHz, 代入计算就是 8000 / (SMPRT_DIV + 1)
 * *****************************************************************************
 */
void MPU6050_Set_SampleRate(u8 rate)
{
    u8 temp[2];
    temp[0] = MPU6050_RA_SMPLRT_DIV;
    temp[1] = rate;
    MPU6050_IIC_Write(DEV_ADDR, temp[0], &temp[1], 1);
}

/**
 * *****************************************************************************
 * @brief 初始化 MPU6050
 * *****************************************************************************
 */
void MPU6050_Init(void)
{
    /* 1. 设备复位 */
    MPU6050_Reset();
    HAL_Delay(100);

    /* 2. 设置时钟源, 唤醒 MPU6050 */
    MPU6050_Set_ClockSource(MPU6050_CLOCK_PLL_YGYRO);
    MPU6050_Set_SleepMode(0);

    /* 3. 设置采样率 1000Hz */
    MPU6050_Set_SampleRate(7);

    /* 4. 设置加速度计和陀螺仪的量程 */
    MPU6050_Set_AccelRange(MPU6050_ACCEL_FS_2);
    MPU6050_Set_GyroRange(MPU6050_GYRO_FS_2000);
}

/**
 * *****************************************************************************
 * @brief 检测 MPU6050 是否已经连接
 * @return 1: 已连接 0: 未连接
 * *****************************************************************************
 */
u8 MPU6050_Check_Connect(void)
{
    u8 DevID;
    DevID = MPU6050_Get_DeviceID();
    if (DevID == 0x68)
    {
        return 1;
    }
    return 0;
}

/**
 * *****************************************************************************
 * @brief 获得 MPU6050 设备 ID
 * @return 值是 0x68 或 0x69 
 * @note - 获取 WHO_AM_I 寄存器的 Bit[6:1]
 * *****************************************************************************
 */
u8 MPU6050_Get_DeviceID(void)
{
    u8 data;
    MPU6050_IIC_Read(DEV_ADDR, MPU6050_RA_WHO_AM_I, &data, 1);
    return data;
}

/**
 * *****************************************************************************
 * @brief 读取 MPU6050 加速度计, 温度传感器, 陀螺仪的数据, 存放在私有全局变量中, 并计算欧拉角
 * *****************************************************************************
 */
void MPU6050_Proc(void)
{
    u8 buffer[14];

    MPU6050_IIC_Read(DEV_ADDR, MPU6050_RA_ACCEL_XOUT_H, buffer, 14);

    ax = (int16_t)((buffer[0] << 8) | buffer[1]) / 16384.0f;
    ay = (int16_t)((buffer[2] << 8) | buffer[3]) / 16384.0f;
    az = (int16_t)((buffer[4] << 8) | buffer[5]) / 16384.0f;

    temperature = (int16_t)((buffer[6] << 8) | buffer[7]) / 340.0f + 36.53f;

    gx = (int16_t)((buffer[8] << 8) | buffer[9]) / 16.4f;
    gy = (int16_t)((buffer[10] << 10) | buffer[11]) / 16.4f;
    gz = (int16_t)((buffer[12] << 12) | buffer[13]) / 16.4f;

    float roll_a = atan2(ay, az) / 3.141593f * 180.0f;
    float pitch_a = -atan2(ax, az) / 3.141593f * 180.0f;

    float yaw_g = yaw + gz * 0.005;
    float roll_g = roll + gx * 0.005;
    float pitch_g = pitch + gy * 0.005;

    const float alpha = 0.95238;

    yaw = yaw_g;
    roll = alpha * roll_g + (1 - alpha) * roll_a;
    pitch = alpha * pitch_g + (1 - alpha) * pitch_a;
}

/**
 * *****************************************************************************
 * @brief 从私有全局变量中获取 MPU6050 加速度计, 温度传感器, 陀螺仪的数据
 * @param [out] pAccelOut 存放加速度计数据
 * @param [out] pTempOut 存放温度传感器数据
 * @param [out] pGyroOut 存放陀螺仪数据
 * @param [out] pEularAngleOut 存放欧拉角
 * @note - 加速度计数据有 3 个
 * @note - 温度传感器数据有 1 个
 * @note - 陀螺仪数据有 3 个
 * @note - 欧拉角有 3 个
 * *****************************************************************************
 */
void MPU6050_GetResult(float* pAccelOut,
                       float* pTempOut,
                       float* pGyroOut,
                       float* pEularAngleOut)
{
    pAccelOut[0] = ax;
    pAccelOut[1] = ay;
    pAccelOut[2] = az;

    *pTempOut = temperature;

    pGyroOut[0] = gx;
    pGyroOut[1] = gy;
    pGyroOut[2] = gz;

    pEularAngleOut[0] = roll;
    pEularAngleOut[1] = pitch;
    pEularAngleOut[2] = yaw;
}
#ifdef __cplusplus
}
#endif
