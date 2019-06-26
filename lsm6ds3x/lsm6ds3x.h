/*
 * Constant definitions and function protoypes for 
 * ST Microelectronics LSM6DS3x inertial module driver
 * Copyright (c) 2019 David Rice
 * 
 * Expects to find lsm6ds3x-cfg.h in the project include path
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>

#ifndef LSM6DS3X_H
#define	LSM6DS3X_H

#include "lsm6ds3x-cfg.h"

#ifdef	__cplusplus
//extern "C" {
#endif

/* Dummy data for one-way SPI transfer */
#define LSM6D_DUMMY_DATA          0x00

/* SPI commands (OR with register address) */
#define LSM6D_SPI_READ            0b10000000
#define LSM6D_SPI_WRITE           0b00000000

/* Register addresses */
#define LSM6D_FUNC_CFG_ACCESS     0x01
#define LSM6D_FIFO_CTRL1          0x06
#define LSM6D_FIFO_CTRL2          0x07
#define LSM6D_FIFO_CTRL3          0x08
#define LSM6D_FIFO_CTRL4          0x09
#define LSM6D_FIFO_CTRL5          0x0A
#define LSM6D_ORIENT_CFG_G        0x0B
#define LSM6D_INT1_CTRL           0x0D
#define LSM6D_INT2_CTRL           0x0E
#define LSM6D_WHO_AM_I            0x0F
#define LSM6D_CTRL1_XL            0x10
#define LSM6D_CTRL2_G             0x11
#define LSM6D_CTRL3_C             0x12
#define LSM6D_CTRL4_C             0x13
#define LSM6D_CTRL5_C             0x14
#define LSM6D_CTRL6_C             0x15
#define LSM6D_CTRL7_G             0x16
#define LSM6D_CTRL8_XL            0x17
#define LSM6D_CTRL9_XL            0x18
#define LSM6D_CTRL10_C            0x19
#define LSM6D_WAKE_UP_SRC         0x1B
#define LSM6D_TAP_SRC             0x1C
#define LSM6D_D6D_SRC             0x1D
#define LSM6D_STATUS_REG          0x1E
#define LSM6D_OUT_TEMP_L          0x20
#define LSM6D_OUT_TEMP_H          0x21
#define LSM6D_OUTX_L_G            0x22
#define LSM6D_OUTX_H_G            0x23
#define LSM6D_OUTY_L_G            0x24
#define LSM6D_OUTY_H_G            0x25
#define LSM6D_OUTZ_L_G            0x26
#define LSM6D_OUTZ_H_G            0x27
#define LSM6D_OUTX_L_XL           0x28
#define LSM6D_OUTX_H_XL           0x29
#define LSM6D_OUTY_L_XL           0x2A
#define LSM6D_OUTY_H_XL           0x2B
#define LSM6D_OUTZ_L_XL           0x2C
#define LSM6D_OUTZ_H_XL           0x2D
#define LSM6D_FIFO_STATUS1        0x3A
#define LSM6D_FIFO_STATUS2        0x3B
#define LSM6D_FIFO_STATUS3        0x3C
#define LSM6D_FIFO_STATUS4        0x3D
#define LSM6D_FIFO_DATA_OUT_L     0x3E
#define LSM6D_FIFO_DATA_OUT_H     0x3F
#define LSM6D_TIMESTAMP0_REG      0x40
#define LSM6D_TIMESTAMP1_REG      0x41
#define LSM6D_TIMESTAMP2_REG      0x42
#define LSM6D_STEP_TIMESTAMP_L    0x49
#define LSM6D_STEP_TIMESTAMP_H    0x4A
#define LSM6D_STEP_COUNTER_L      0x4B
#define LSM6D_STEP_COUNTER_H      0x4C
#define LSM6D_FUNC_SRC            0x53
#define LSM6D_TAP_CFG             0x58
#define LSM6D_TAP_THS_6D          0x59
#define LSM6D_INT_DUR2            0x5A
#define LSM6D_WAKE_UP_THS         0x5B
#define LSM6D_WAKE_UP_DUR         0x5C
#define LSM6D_FREE_FALL           0x5D
#define LSM6D_MD1_CFG             0x5E
#define LSM6D_MD2_CFG             0x5F

/* LSM6D_FUNC_CFG_ACCESS */
#define _FUNC_CFG_FUNC_CFG_EN_POSN           7
#define _FUNC_CFG_FUNC_CFG_EN_LEN            1
#define _FUNC_CFG_FUNC_CFG_EN_MASK           0b10000000
    
/* LSM6D_FIFO_CTRL1 */
#define _FIFO_CTRL1_FTH_L_POSN                 0
#define _FIFO_CTRL1_FTH_L_LEN                  8
#define _FIFO_CTRL1_FTH_L_MASK                 0b11111111
    
/* LSM6D_FIFO_CTRL2 */
#define _FIFO_CTRL2_FTH_H_POSN                 0
#define _FIFO_CTRL2_FTH_H_LEN                  4
#define _FIFO_CTRL2_FTH_H_MASK                 0b00001111

#define _FIFO_CTRL2_TIMER_PEDO_FIFO_DRDY_POSN  6
#define _FIFO_CTRL2_TIMER_PEDO_FIFO_DRDY_LEN   1
#define _FIFO_CTRL2_TIMER_PEDO_FIFO_DRDY_MASK  0b01000000

#define _FIFO_CTRL2_TIMER_PEDO_FIFO_EN_POSN    7
#define _FIFO_CTRL2_TIMER_PEDO_FIFO_EN_LEN     1
#define _FIFO_CTRL2_TIMER_PEDO_FIFO_EN_MASK    0b10000000

/* FIFO_CTRL3 */
#define _FIFO_CTRL3_DEC_FIFO_XL_POSN	0
#define _FIFO_CTRL3_DEC_FIFO_XL_LEN	3
#define _FIFO_CTRL3_DEC_FIFO_XL_MASK	0b00000111

#define _FIFO_CTRL3_DEC_FIFO_GYRO_POSN	3
#define _FIFO_CTRL3_DEC_FIFO_GYRO_LEN	3
#define _FIFO_CTRL3_DEC_FIFO_GYRO_MASK	0b00111000

/* FIFO decimation settings */
#define _FIFO_CTRL3_NOT_IN_FIFO             0b000
#define _FIFO_CTRL3_DECIMATION_NONE         0b001
#define _FIFO_CTRL3_DECIMATION_2            0b010
#define _FIFO_CTRL3_DECIMATION_3            0b011
#define _FIFO_CTRL3_DECIMATION_4            0b100
#define _FIFO_CTRL3_DECIMATION_8            0b101
#define _FIFO_CTRL3_DECIMATION_16           0b110
#define _FIFO_CTRL3_DECIMATION_32           0b111

/* FIFO_CTRL4 */
#define _FIFO_CTRL4_TIMER_PEDO_DEC_FIFO_POSN	3
#define _FIFO_CTRL4_TIMER_PEDO_DEC_FIFO_LEN	3
#define _FIFO_CTRL4_TIMER_PEDO_DEC_FIFO_MASK	0b00111000

#define _FIFO_CTRL4_ONLY_HIGH_DATA_POSN	6
#define _FIFO_CTRL4_ONLY_HIGH_DATA_LEN	1
#define _FIFO_CTRL4_ONLY_HIGH_DATA_MASK	0b01000000

/* FIFO_CTRL5 */
#define _FIFO_CTRL5_FIFO_MODE_POSN	0
#define _FIFO_CTRL5_FIFO_MODE_LEN	3
#define _FIFO_CTRL5_FIFO_MODE_MASK	0b00000111

#define _FIFO_CTRL5_ODR_FIFO_POSN	3
#define _FIFO_CTRL5_ODR_FIFO_LEN	4
#define _FIFO_CTRL5_ODR_FIFO_MASK	0b01111000

/* FIFO ODR settings */
#define _FIFO_CTRL5_FIFO_DISABLED           0b0000
#define _FIFO_CTRL5_ODR_FIFO_13HZ           0b0001
#define _FIFO_CTRL5_ODR_FIFO_26HZ           0b0010
#define _FIFO_CTRL5_ODR_FIFO_52HZ           0b0011
#define _FIFO_CTRL5_ODR_FIFO_104HZ          0b0100
#define _FIFO_CTRL5_ODR_FIFO_208HZ          0b0101
#define _FIFO_CTRL5_ODR_FIFO_416HZ          0b0110
#define _FIFO_CTRL5_ODR_FIFO_833HZ          0b0111
#define _FIFO_CTRL5_ODR_FIFO_1_66KHZ        0b1000
#define _FIFO_CTRL5_ODR_FIFO_3_33KHZ        0b1001
#define _FIFO_CTRL5_ODR_FIFO_6_66KHZ        0b1010

/* FIFO mode settings */
#define _FIFO_CTRL5_FIFO_BYPASS             0b000
#define _FIFO_CTRL5_FIFO_UNTIL_FULL         0b001
#define _FIFO_CTRL5_FIFO_CONT_THEN_FIFO     0b011
#define _FIFO_CTRL5_FIFO_BYPASS_THEN_CONT   0b100
#define _FIFO_CTRL5_FIFO_CONTINUOUS         0b110

/* ORIENT_CFG_G */
#define _ORIENT_CFG_G_ORIENT_POSN	0
#define _ORIENT_CFG_G_ORIENT_LEN	3
#define _ORIENT_CFG_G_ORIENT_MASK	0b00000111

#define _ORIENT_CFG_G_SIGNZ_G_POSN	3
#define _ORIENT_CFG_G_SIGNZ_G_LEN	1
#define _ORIENT_CFG_G_SIGNZ_G_MASK	0b00001000

#define _ORIENT_CFG_G_SIGNY_G_POSN	4
#define _ORIENT_CFG_G_SIGNY_G_LEN	1
#define _ORIENT_CFG_G_SIGNY_G_MASK	0b00010000

#define _ORIENT_CFG_G_SIGNX_G_POSN	5
#define _ORIENT_CFG_G_SIGNX_G_LEN	1
#define _ORIENT_CFG_G_SIGNX_G_MASK	0b00100000

/* Orientation settings (order is pitch, roll, yaw) */
#define _ORIENT_CFG_G_ORIENT_XYZ              0b000
#define _ORIENT_CFG_G_ORIENT_XZY              0b001
#define _ORIENT_CFG_G_ORIENT_YXZ              0b010
#define _ORIENT_CFG_G_ORIENT_YZX              0b011
#define _ORIENT_CFG_G_ORIENT_ZXY              0b100
#define _ORIENT_CFG_G_ORIENT_ZYX              0b101

/* INT1_CTRL */
#define _INT1_CTRL_INT1_DRDY_XL_POSN	0
#define _INT1_CTRL_INT1_DRDY_XL_LEN	1
#define _INT1_CTRL_INT1_DRDY_XL_MASK	0b00000001

#define _INT1_CTRL_INT1_DRDY_G_POSN	1
#define _INT1_CTRL_INT1_DRDY_G_LEN	1
#define _INT1_CTRL_INT1_DRDY_G_MASK	0b00000010

#define _INT1_CTRL_INT1_BOOT_POSN	2
#define _INT1_CTRL_INT1_BOOT_LEN	1
#define _INT1_CTRL_INT1_BOOT_MASK	0b00000100

#define _INT1_CTRL_INT1_FTH_POSN	3
#define _INT1_CTRL_INT1_FTH_LEN	1
#define _INT1_CTRL_INT1_FTH_MASK	0b00001000

#define _INT1_CTRL_INT1_FIFO_OVR_POSN	4
#define _INT1_CTRL_INT1_FIFO_OVR_LEN	1
#define _INT1_CTRL_INT1_FIFO_OVR_MASK	0b00010000

#define _INT1_CTRL_INT1_FULL_FLAG_POSN	5
#define _INT1_CTRL_INT1_FULL_FLAG_LEN	1
#define _INT1_CTRL_INT1_FULL_FLAG_MASK	0b00100000

#define _INT1_CTRL_INT1_SIGN_MOT_POSN	6
#define _INT1_CTRL_INT1_SIGN_MOT_LEN	1
#define _INT1_CTRL_INT1_SIGN_MOT_MASK	0b01000000

#define _INT1_CTRL_INT1_STEP_DETECTOR_POSN	7
#define _INT1_CTRL_INT1_STEP_DETECTOR_LEN	1
#define _INT1_CTRL_INT1_STEP_DETECTOR_MASK	0b10000000

/* INT2_CTRL */
#define _INT2_CTRL_INT2_DRDY_XL_POSN	0
#define _INT2_CTRL_INT2_DRDY_XL_LEN	1
#define _INT2_CTRL_INT2_DRDY_XL_MASK	0b00000001

#define _INT2_CTRL_INT2_DRDY_G_POSN	1
#define _INT2_CTRL_INT2_DRDY_G_LEN	1
#define _INT2_CTRL_INT2_DRDY_G_MASK	0b00000010

#define _INT2_CTRL_INT2_DRDY_TEMP_POSN	2
#define _INT2_CTRL_INT2_DRDY_TEMP_LEN	1
#define _INT2_CTRL_INT2_DRDY_TEMP_MASK	0b00000100

#define _INT2_CTRL_INT2_FTH_POSN	3
#define _INT2_CTRL_INT2_FTH_LEN	1
#define _INT2_CTRL_INT2_FTH_MASK	0b00001000

#define _INT2_CTRL_INT2_FIFO_OVR_POSN	4
#define _INT2_CTRL_INT2_FIFO_OVR_LEN	1
#define _INT2_CTRL_INT2_FIFO_OVR_MASK	0b00010000

#define _INT2_CTRL_INT2_FULL_FLAG_POSN	5
#define _INT2_CTRL_INT2_FULL_FLAG_LEN	1
#define _INT2_CTRL_INT2_FULL_FLAG_MASK	0b00100000

#define _INT2_CTRL_INT2_STEP_COUNT_OV_POSN	6
#define _INT2_CTRL_INT2_STEP_COUNT_OV_LEN	1
#define _INT2_CTRL_INT2_STEP_COUNT_OV_MASK	0b01000000

#define _INT2_CTRL_INT2_STEP_DELTA_POSN	7
#define _INT2_CTRL_INT2_STEP_DELTA_LEN	1
#define _INT2_CTRL_INT2_STEP_DELTA_MASK	0b10000000
 
/* CTRL1_XL */
#define _CTRL1_XL_BW_XL_POSN	0
#define _CTRL1_XL_BW_XL_LEN	2
#define _CTRL1_XL_BW_XL_MASK	0b00000011

#define _CTRL1_XL_FS_XL_POSN	2
#define _CTRL1_XL_FS_XL_LEN	2
#define _CTRL1_XL_FS_XL_MASK	0b00001100

#define _CTRL1_XL_ODR_XL_POSN	4
#define _CTRL1_XL_ODR_XL_LEN	4
#define _CTRL1_XL_ODR_XL_MASK	0b11110000

/* Accelerometer ODR settings */
#define _CTRL1_XL_ODR_XL_POWER_DOWN       0b0000
#define _CTRL1_XL_ODR_XL_13HZ             0b0001
#define _CTRL1_XL_ODR_XL_26HZ             0b0010
#define _CTRL1_XL_ODR_XL_52HZ             0b0011
#define _CTRL1_XL_ODR_XL_104HZ            0b0100
#define _CTRL1_XL_ODR_XL_208HZ            0b0101
#define _CTRL1_XL_ODR_XL_416HZ            0b0110
#define _CTRL1_XL_ODR_XL_833HZ            0b0111
#define _CTRL1_XL_ODR_XL_1_66KHZ          0b1000
#define _CTRL1_XL_ODR_XL_3_33KHZ          0b1001
#define _CTRL1_XL_ODR_XL_6_66KHZ          0b1010

/* Accelerometer full-scale settings */
#define _CTRL1_XL_FS_XL_2G                0b00
#define _CTRL1_XL_FS_XL_4G                0b10
#define _CTRL1_XL_FS_XL_8G                0b11
#define _CTRL1_XL_FS_XL_16G               0b01

/* Accelerometer filter bandwidth settings */
#define _CTRL1_XL_BW_XL_400HZ             0b00
#define _CTRL1_XL_BW_XL_200HZ             0b01
#define _CTRL1_XL_BW_XL_100HZ             0b10
#define _CTRL1_XL_BW_XL_50HZ              0b11

/* CTRL2_G */
#define _CTRL2_G_FS_125_POSN	1
#define _CTRL2_G_FS_125_LEN	1
#define _CTRL2_G_FS_125_MASK	0b00000010

#define _CTRL2_G_FS_G_POSN	2
#define _CTRL2_G_FS_G_LEN	2
#define _CTRL2_G_FS_G_MASK	0b00001100

#define _CTRL2_G_ODR_G_POSN	4
#define _CTRL2_G_ODR_G_LEN	4
#define _CTRL2_G_ODR_G_MASK	0b11110000

/* Gyroscope ODR settings */
#define _CTRL2_G_ODR_G_POWER_DOWN        0b0000
#define _CTRL2_G_ODR_G_13HZ              0b0001
#define _CTRL2_G_ODR_G_26HZ              0b0010
#define _CTRL2_G_ODR_G_52HZ              0b0011
#define _CTRL2_G_ODR_G_104HZ             0b0100
#define _CTRL2_G_ODR_G_208HZ             0b0101
#define _CTRL2_G_ODR_G_416HZ             0b0110
#define _CTRL2_G_ODR_G_833HZ             0b0111
#define _CTRL2_G_ODR_G_1_66KHZ           0b1000

/* Gyroscope full-scale settings */
#define _CTRL2_G_FS_G_245DPS             0b00
#define _CTRL2_G_FS_G_500DPS             0b01
#define _CTRL2_G_FS_G_1000DPS            0b10
#define _CTRL2_G_FS_G_2000DPS            0b11

/* CTRL3_C */
#define _CTRL3_C_SW_RESET_POSN	0
#define _CTRL3_C_SW_RESET_LEN	1
#define _CTRL3_C_SW_RESET_MASK	0b00000001

#define _CTRL3_C_BLE_POSN	1
#define _CTRL3_C_BLE_LEN	1
#define _CTRL3_C_BLE_MASK	0b00000010

#define _CTRL3_C_IF_INC_POSN	2
#define _CTRL3_C_IF_INC_LEN	1
#define _CTRL3_C_IF_INC_MASK	0b00000100

#define _CTRL3_C_SIM_POSN	3
#define _CTRL3_C_SIM_LEN	1
#define _CTRL3_C_SIM_MASK	0b00001000

#define _CTRL3_C_PP_OD_POSN	4
#define _CTRL3_C_PP_OD_LEN	1
#define _CTRL3_C_PP_OD_MASK	0b00010000

#define _CTRL3_C_H_LACTIVE_POSN	5
#define _CTRL3_C_H_LACTIVE_LEN	1
#define _CTRL3_C_H_LACTIVE_MASK	0b00100000

#define _CTRL3_C_BDU_POSN	6
#define _CTRL3_C_BDU_LEN	1
#define _CTRL3_C_BDU_MASK	0b01000000

#define _CTRL3_C_BOOT_POSN	7
#define _CTRL3_C_BOOT_LEN	1
#define _CTRL3_C_BOOT_MASK	0b10000000

/* CTRL4_C */
#define _CTRL4_C_STOP_ON_FTH_POSN	0
#define _CTRL4_C_STOP_ON_FTH_LEN	1
#define _CTRL4_C_STOP_ON_FTH_MASK	0b00000001

#define _CTRL4_C_I2C_DISABLE_POSN	2
#define _CTRL4_C_I2C_DISABLE_LEN	1
#define _CTRL4_C_I2C_DISABLE_MASK	0b00000100

#define _CTRL4_C_DRDY_MASK_POSN	3
#define _CTRL4_C_DRDY_MASK_LEN	1
#define _CTRL4_C_DRDY_MASK_MASK	0b00001000

#define _CTRL4_C_FIFO_TEMP_EN_POSN	4
#define _CTRL4_C_FIFO_TEMP_EN_LEN	1
#define _CTRL4_C_FIFO_TEMP_EN_MASK	0b00010000

#define _CTRL4_C_INT2_ON_INT1_POSN	5
#define _CTRL4_C_INT2_ON_INT1_LEN	1
#define _CTRL4_C_INT2_ON_INT1_MASK	0b00100000

#define _CTRL4_C_SLEEP_G_POSN	6
#define _CTRL4_C_SLEEP_G_LEN	1
#define _CTRL4_C_SLEEP_G_MASK	0b01000000

#define _CTRL4_C_XL_BW_SCAL_ODR_POSN	7
#define _CTRL4_C_XL_BW_SCAL_ODR_LEN	1
#define _CTRL4_C_XL_BW_SCAL_ODR_MASK	0b10000000

/* CTRL5_C */
#define _CTRL5_C_ST_XL_POSN	0
#define _CTRL5_C_ST_XL_LEN	2
#define _CTRL5_C_ST_XL_MASK	0b00000011

#define _CTRL5_C_ST_G_POSN	2
#define _CTRL5_C_ST_G_LEN	2
#define _CTRL5_C_ST_G_MASK	0b00001100

#define _CTRL5_C_ROUNDING_POSN	5
#define _CTRL5_C_ROUNDING_LEN	3
#define _CTRL5_C_ROUNDING_MASK	0b11100000

/* Rounding mode settings */
#define _CTRL5_C_ROUND_NONE              0b000
#define _CTRL5_C_ROUND_XL_ONLY           0b001
#define _CTRL5_C_ROUND_G_ONLY            0b010
#define _CTRL5_C_ROUND_G_AND_XL          0b011

/* Gyroscope self-test settings */
#define _CTRL5_C_ST_G_NORMAL             0b00
#define _CTRL5_C_ST_G_POS_SIGN           0b01
#define _CTRL5_C_ST_G_NEG_SIGN           0b11

/* Accelerometer self-test settings */
#define _CTRL5_C_ST_XL_NORMAL            0b00
#define _CTRL5_C_ST_XL_POS_SIGN          0b01
#define _CTRL5_C_ST_XL_NEG_SIGN          0b10

/* CTRL6_C */
#define _CTRL6_C_XL_HM_MODE_POSN	4
#define _CTRL6_C_XL_HM_MODE_LEN	1
#define _CTRL6_C_XL_HM_MODE_MASK	0b00010000

#define _CTRL6_C_LVL2_EN_POSN	5
#define _CTRL6_C_LVL2_EN_LEN	1
#define _CTRL6_C_LVL2_EN_MASK	0b00100000

#define _CTRL6_C_LVLEN_POSN	6
#define _CTRL6_C_LVLEN_LEN	1
#define _CTRL6_C_LVLEN_MASK	0b01000000

#define _CTRL6_C_TRIG_EN_POSN	7
#define _CTRL6_C_TRIG_EN_LEN	1
#define _CTRL6_C_TRIG_EN_MASK	0b10000000

/* CTRL7_G */
#define _CTRL7_G_ROUNDING_STATUS_POSN	2
#define _CTRL7_G_ROUNDING_STATUS_LEN	1
#define _CTRL7_G_ROUNDING_STATUS_MASK	0b00000100

#define _CTRL7_G_HP_G_RST_POSN	3
#define _CTRL7_G_HP_G_RST_LEN	1
#define _CTRL7_G_HP_G_RST_MASK	0b00001000

#define _CTRL7_G_HPCF_G_POSN	4
#define _CTRL7_G_HPCF_G_LEN	2
#define _CTRL7_G_HPCF_G_MASK	0b00110000

#define _CTRL7_G_HP_G_EN_POSN	6
#define _CTRL7_G_HP_G_EN_LEN	1
#define _CTRL7_G_HP_G_EN_MASK	0b01000000

#define _CTRL7_G_G_HM_MODE_POSN	7
#define _CTRL7_G_G_HM_MODE_LEN	1
#define _CTRL7_G_G_HM_MODE_MASK	0b10000000

/* Gyroscope high-pass filter mode settings */
#define _CTRL7_G_HPCF_G_0_0081HZ         0b00
#define _CTRL7_G_HPCF_G_0_0324HZ         0b01
#define _CTRL7_G_HPCF_G_2_07HZ           0b10
#define _CTRL7_G_HPCF_G_16_32HZ          0b11

/* CTRL8_XL */
#define _CTRL8_XL_LOW_PASS_ON_6D_POSN	0
#define _CTRL8_XL_LOW_PASS_ON_6D_LEN	1
#define _CTRL8_XL_LOW_PASS_ON_6D_MASK	0b00000001

#define _CTRL8_XL_HP_SLOPE_XL_EN_POSN	2
#define _CTRL8_XL_HP_SLOPE_XL_EN_LEN	1
#define _CTRL8_XL_HP_SLOPE_XL_EN_MASK	0b00000100

#define _CTRL8_XL_HPCF_XL_POSN	6
#define _CTRL8_XL_HPCF_XL_LEN	2
#define _CTRL8_XL_HPCF_XL_MASK	0b11000000

#define _CTRL8_XL_LPF2_XL_EN_POSN	7
#define _CTRL8_XL_LPF2_XL_EN_LEN	1
#define _CTRL8_XL_LPF2_XL_EN_MASK	0b10000000

/* Accelerometer filter settings */
#define _CTRL8_XL_HPCF_XL_SLOPE_XL_50     0b00
#define _CTRL8_XL_HPCF_XL_HP_XL_100       0b01
#define _CTRL8_XL_HPCF_XL_HP_XL_9         0b10
#define _CTRL8_XL_HPCF_XL_HP_XL_400       0b11

/* CTRL9_XL */
#define _CTRL9_XL_X_EN_XL_POSN	3
#define _CTRL9_XL_X_EN_XL_LEN	1
#define _CTRL9_XL_X_EN_XL_MASK	0b00001000

#define _CTRL9_XL_Y_EN_XL_POSN	4
#define _CTRL9_XL_Y_EN_XL_LEN	1
#define _CTRL9_XL_Y_EN_XL_MASK	0b00010000

#define _CTRL9_XL_Z_EN_XL_POSN	5
#define _CTRL9_XL_Z_EN_XL_LEN	1
#define _CTRL9_XL_Z_EN_XL_MASK	0b00100000

/* CTRL10_C */
#define _CTRL10_C_SIGN_MOTION_EN_POSN	0
#define _CTRL10_C_SIGN_MOTION_EN_LEN	1
#define _CTRL10_C_SIGN_MOTION_EN_MASK	0b00000001

#define _CTRL10_C_PEDO_RST_STEP_POSN	1
#define _CTRL10_C_PEDO_RST_STEP_LEN	1
#define _CTRL10_C_PEDO_RST_STEP_MASK	0b00000010

#define _CTRL10_C_FUNC_EN_POSN	2
#define _CTRL10_C_FUNC_EN_LEN	1
#define _CTRL10_C_FUNC_EN_MASK	0b00000100

#define _CTRL10_C_X_EN_G_POSN	3
#define _CTRL10_C_X_EN_G_LEN	1
#define _CTRL10_C_X_EN_G_MASK	0b00001000

#define _CTRL10_C_Y_EN_G_POSN	4
#define _CTRL10_C_Y_EN_G_LEN	1
#define _CTRL10_C_Y_EN_G_MASK	0b00010000

#define _CTRL10_C_Z_EN_G_POSN	5
#define _CTRL10_C_Z_EN_G_LEN	1
#define _CTRL10_C_Z_EN_G_MASK	0b00100000

/* WAKE_UP_SRC */
#define _WAKE_UP_SRC_Z_WU_POSN	0
#define _WAKE_UP_SRC_Z_WU_LEN	1
#define _WAKE_UP_SRC_Z_WU_MASK	0b00000001

#define _WAKE_UP_SRC_Y_WU_POSN	1
#define _WAKE_UP_SRC_Y_WU_LEN	1
#define _WAKE_UP_SRC_Y_WU_MASK	0b00000010

#define _WAKE_UP_SRC_X_WU_POSN	2
#define _WAKE_UP_SRC_X_WU_LEN	1
#define _WAKE_UP_SRC_X_WU_MASK	0b00000100

#define _WAKE_UP_SRC_WU_IA_POSN	3
#define _WAKE_UP_SRC_WU_IA_LEN	1
#define _WAKE_UP_SRC_WU_IA_MASK	0b00001000

#define _WAKE_UP_SRC_SLEEP_STATE_IA_POSN	4
#define _WAKE_UP_SRC_SLEEP_STATE_IA_LEN	1
#define _WAKE_UP_SRC_SLEEP_STATE_IA_MASK	0b00010000

#define _WAKE_UP_SRC_FF_IA_POSN	5
#define _WAKE_UP_SRC_FF_IA_LEN	1
#define _WAKE_UP_SRC_FF_IA_MASK	0b00100000

/* TAP_SRC */
#define _TAP_SRC_Z_TAP_POSN	0
#define _TAP_SRC_Z_TAP_LEN	1
#define _TAP_SRC_Z_TAP_MASK	0b00000001

#define _TAP_SRC_Y_TAP_POSN	1
#define _TAP_SRC_Y_TAP_LEN	1
#define _TAP_SRC_Y_TAP_MASK	0b00000010

#define _TAP_SRC_X_TAP_POSN	2
#define _TAP_SRC_X_TAP_LEN	1
#define _TAP_SRC_X_TAP_MASK	0b00000100

#define _TAP_SRC_TAP_SIGN_POSN	3
#define _TAP_SRC_TAP_SIGN_LEN	1
#define _TAP_SRC_TAP_SIGN_MASK	0b00001000

#define _TAP_SRC_DOUBLE_TAP_POSN	4
#define _TAP_SRC_DOUBLE_TAP_LEN	1
#define _TAP_SRC_DOUBLE_TAP_MASK	0b00010000

#define _TAP_SRC_SINGLE_TAP_POSN	5
#define _TAP_SRC_SINGLE_TAP_LEN	1
#define _TAP_SRC_SINGLE_TAP_MASK	0b00100000

#define _TAP_SRC_TAP_IA_POSN	6
#define _TAP_SRC_TAP_IA_LEN	1
#define _TAP_SRC_TAP_IA_MASK	0b01000000

/* D6D_SRC */
#define _D6D_SRC_XL_POSN	0
#define _D6D_SRC_XL_LEN	1
#define _D6D_SRC_XL_MASK	0b00000001

#define _D6D_SRC_XH_POSN	1
#define _D6D_SRC_XH_LEN	1
#define _D6D_SRC_XH_MASK	0b00000010

#define _D6D_SRC_YL_POSN	2
#define _D6D_SRC_YL_LEN	1
#define _D6D_SRC_YL_MASK	0b00000100

#define _D6D_SRC_YH_POSN	3
#define _D6D_SRC_YH_LEN	1
#define _D6D_SRC_YH_MASK	0b00001000

#define _D6D_SRC_ZL_POSN	4
#define _D6D_SRC_ZL_LEN	1
#define _D6D_SRC_ZL_MASK	0b00010000

#define _D6D_SRC_ZH_POSN	5
#define _D6D_SRC_ZH_LEN	1
#define _D6D_SRC_ZH_MASK	0b00100000

#define _D6D_SRC_D6D_IA_POSN	6
#define _D6D_SRC_D6D_IA_LEN	1
#define _D6D_SRC_D6D_IA_MASK	0b01000000

/* STATUS_REG */
#define _STATUS_REG_XLDA_POSN	0
#define _STATUS_REG_XLDA_LEN	1
#define _STATUS_REG_XLDA_MASK	0b00000001

#define _STATUS_REG_GDA_POSN	1
#define _STATUS_REG_GDA_LEN	1
#define _STATUS_REG_GDA_MASK	0b00000010

#define _STATUS_REG_TDA_POSN	2
#define _STATUS_REG_TDA_LEN	1
#define _STATUS_REG_TDA_MASK	0b00000100

#define _STATUS_REG_EV_BOOT_POSN	3
#define _STATUS_REG_EV_BOOT_LEN	1
#define _STATUS_REG_EV_BOOT_MASK	0b00001000

/* FIFO_STATUS1 */
#define _FIFO_STATUS1_DIFF_FIFO_L_POSN	0
#define _FIFO_STATUS1_DIFF_FIFO_L_LEN	8
#define _FIFO_STATUS1_DIFF_FIFO_L_MASK	0b11111111

/* FIFO_STATUS2 */
#define _FIFO_STATUS2_DIFF_FIFO_H_POSN	0
#define _FIFO_STATUS2_DIFF_FIFO_H_LEN	4
#define _FIFO_STATUS2_DIFF_FIFO_H_MASK	0b00001111

#define _FIFO_STATUS2_FIFO_EMPTY_POSN	4
#define _FIFO_STATUS2_FIFO_EMPTY_LEN	1
#define _FIFO_STATUS2_FIFO_EMPTY_MASK	0b00010000

#define _FIFO_STATUS2_FIFO_FULL_POSN	5
#define _FIFO_STATUS2_FIFO_FULL_LEN	1
#define _FIFO_STATUS2_FIFO_FULL_MASK	0b00100000

#define _FIFO_STATUS2_FIFO_OVER_RUN_POSN	6
#define _FIFO_STATUS2_FIFO_OVER_RUN_LEN	1
#define _FIFO_STATUS2_FIFO_OVER_RUN_MASK	0b01000000

#define _FIFO_STATUS2_FTH_POSN	7
#define _FIFO_STATUS2_FTH_LEN	1
#define _FIFO_STATUS2_FTH_MASK	0b10000000

/* FIFO_STATUS3 */
#define _FIFO_STATUS3_FIFO_PATTERN_L_POSN	0
#define _FIFO_STATUS3_FIFO_PATTERN_L_LEN	8
#define _FIFO_STATUS3_FIFO_PATTERN_L_MASK	0b11111111

/* FIFO_STATUS4 */
#define _FIFO_STATUS4_FIFO_PATTERN_H_POSN	0
#define _FIFO_STATUS4_FIFO_PATTERN_H_LEN	2
#define _FIFO_STATUS4_FIFO_PATTERN_H_MASK	0b00000011

/* FUNC_SRC */
#define _FUNC_SRC_STEP_OVERFLOW_POSN	3
#define _FUNC_SRC_STEP_OVERFLOW_LEN	1
#define _FUNC_SRC_STEP_OVERFLOW_MASK	0b00001000

#define _FUNC_SRC_STEP_DETECTED_POSN	4
#define _FUNC_SRC_STEP_DETECTED_LEN	1
#define _FUNC_SRC_STEP_DETECTED_MASK	0b00010000

#define _FUNC_SRC_TILT_IA_POSN	5
#define _FUNC_SRC_TILT_IA_LEN	1
#define _FUNC_SRC_TILT_IA_MASK	0b00100000

#define _FUNC_SRC_SIGN_MOTION_IA_POSN	6
#define _FUNC_SRC_SIGN_MOTION_IA_LEN	1
#define _FUNC_SRC_SIGN_MOTION_IA_MASK	0b01000000

#define _FUNC_SRC_STEP_COUNT_DELTA_IA_POSN	7
#define _FUNC_SRC_STEP_COUNT_DELTA_IA_LEN	1
#define _FUNC_SRC_STEP_COUNT_DELTA_IA_MASK	0b10000000

/* TAP_CFG */
#define _TAP_CFG_LIR_POSN	0
#define _TAP_CFG_LIR_LEN	1
#define _TAP_CFG_LIR_MASK	0b00000001

#define _TAP_CFG_TAP_Z_EN_POSN	1
#define _TAP_CFG_TAP_Z_EN_LEN	1
#define _TAP_CFG_TAP_Z_EN_MASK	0b00000010

#define _TAP_CFG_TAP_Y_EN_POSN	2
#define _TAP_CFG_TAP_Y_EN_LEN	1
#define _TAP_CFG_TAP_Y_EN_MASK	0b00000100

#define _TAP_CFG_TAP_X_EN_POSN	3
#define _TAP_CFG_TAP_X_EN_LEN	1
#define _TAP_CFG_TAP_X_EN_MASK	0b00001000

#define _TAP_CFG_SLOPE_FDS_POSN	4
#define _TAP_CFG_SLOPE_FDS_LEN	1
#define _TAP_CFG_SLOPE_FDS_MASK	0b00010000

#define _TAP_CFG_TILT_EN_POSN	5
#define _TAP_CFG_TILT_EN_LEN	1
#define _TAP_CFG_TILT_EN_MASK	0b00100000

#define _TAP_CFG_PEDO_EN_POSN	6
#define _TAP_CFG_PEDO_EN_LEN	1
#define _TAP_CFG_PEDO_EN_MASK	0b01000000

#define _TAP_CFG_TIMER_EN_POSN	7
#define _TAP_CFG_TIMER_EN_LEN	1
#define _TAP_CFG_TIMER_EN_MASK	0b10000000

/* TAP_THS_6D bit values */
#define TAP_THS                 0
#define SIXD_THS                5
#define D4D_EN                  7

/* Threshold values */
#define SIXD_THS_80D            0b00
#define SIXD_THS_70D            0b01
#define SIXD_THS_60D            0b10
#define SIXD_THS_50D            0b11

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} LSM6D_XL_DATA;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} LSM6D_G_DATA;

typedef struct {
    int16_t temp;
    LSM6D_XL_DATA xl;
    LSM6D_G_DATA g;
} LSM6D_SENSOR_DATA;

void lsm6d_set_register_value(uint8_t addr, uint8_t value);
void lsm6d_set_register_bits(uint8_t addr, uint8_t bits);
void lsm6d_clear_register_bits(uint8_t addr, uint8_t bits);

uint8_t lsm6d_get_register_value(uint8_t addr);
void lsm6d_get_register_multi(uint8_t startAddr, uint8_t *buffer, uint8_t num);

int16_t lsm6d_get_temperature();
void lsm6d_get_accel_data(LSM6D_XL_DATA *data);
void lsm6d_get_gyro_data(LSM6D_G_DATA *data);

void lsm6d_get_all_motion_data(LSM6D_SENSOR_DATA *data);
void lsm6d_get_all_sensor_data(LSM6D_SENSOR_DATA *data);

void lsm6d_set_accel_data_rate(uint8_t rate);
void lsm6d_set_gyro_data_rate(uint8_t rate);

void lsm6d_set_accel_scale(uint8_t scale);
void lsm6d_set_gyro_scale(uint8_t scale);

#ifdef	__cplusplus
}
#endif

#endif	/* LSM6DS3X_H */

