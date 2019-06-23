/*
 * Driver for ST Microelectronics LSM6DS3x
 * Designed and implemented by David Rice
 * 
 * Requires definitions for:
 * LSM6D_SPI_ACTIVE() - Code to set CSN pin low
 * LSM6D_SPI_IDLE() - Code to set CSN pin high
 * LSM6D_INT1 - Bit value for I/O pin input for INT1
 * LSM6D_INT2 - Bit value for I/O pin input for INT2
 * LSM6D_SPI_TRANSFER(x) - Transfer one byte to/from SPI bus without changing CSN
 * 
 * Configuration is usually located in lsm6ds3x-cfg.h in the same folder with the main project
 * 
 */ 

#include "lsm6ds3x.h"
#include "lsm6ds3x-cfg.h"

void lsm6d_set_register_value(uint8_t addr, uint8_t value)
{
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_WRITE | addr);
    LSM6D_SPI_TRANSFER(value);
    LSM6D_SPI_IDLE();
}

void lsm6d_set_register_bits(uint8_t addr, uint8_t bits) {
    uint8_t temp;
 
    temp = lsm6d_get_register_value(addr);
    
    temp = temp | bits;
    
    lsm6d_set_register_value(addr, temp);
}

void lsm6d_clear_register_bits(uint8_t addr, uint8_t bits) {
    uint8_t temp;
    
    temp = lsm6d_get_register_value(addr);
    
    temp = temp & ~bits;
    
    lsm6d_set_register_value(addr, temp);
}

void lsm6d_set_accel_data_rate(uint8_t rate) {
    uint8_t temp;
    
    temp = lsm6d_get_register_value(LSM6D_CTRL1_XL);
    
    temp &= ~_CTRL1_XL_ODR_XL_MASK;
    temp |= rate << _CTRL1_XL_ODR_XL_POSN;
            
    lsm6d_set_register_value(LSM6D_CTRL1_XL, temp);
}

void lsm6d_set_gyro_data_rate(uint8_t rate) {
    uint8_t temp;
    
    temp = lsm6d_get_register_value(LSM6D_CTRL2_G);
    
    temp &= ~_CTRL2_G_ODR_G_MASK;
    temp |= rate << _CTRL2_G_ODR_G_POSN;
            
    lsm6d_set_register_value(LSM6D_CTRL2_G, temp);
}

void lsm6d_set_accel_scale(uint8_t scale) {
    uint8_t temp;
    
    temp = lsm6d_get_register_value(LSM6D_CTRL1_XL);
    
    temp &= ~_CTRL1_XL_FS_XL_MASK;
    temp |= scale << _CTRL1_XL_FS_XL_POSN;
            
    lsm6d_set_register_value(LSM6D_CTRL1_XL, temp);
}

void lsm6d_set_gyro_scale(uint8_t scale) {
    uint8_t temp;
    
    temp = lsm6d_get_register_value(LSM6D_CTRL2_G);
    
    temp &= ~_CTRL2_G_FS_G_MASK;
    temp |= scale << _CTRL2_G_FS_G_POSN;
            
    lsm6d_set_register_value(LSM6D_CTRL2_G, temp);
}

uint8_t lsm6d_get_register_value(uint8_t addr)
{
    uint8_t temp;
    
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_READ | addr);
    temp = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    LSM6D_SPI_IDLE();
    
    return temp;
}

void lsm6d_get_register_multi(uint8_t start_addr, uint8_t *buffer, uint8_t num)
{
    uint8_t count;
    
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_READ | start_addr);
    
    for (count = 0; count < num; count++) {
        buffer[count] = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    }
    
    LSM6D_SPI_IDLE();
}

int16_t lsm6d_get_temperature(void)
{
    uint8_t val;
    uint16_t temperature;
    
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_READ | LSM6D_OUT_TEMP_L);
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    temperature = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    temperature |= val << 8;
    LSM6D_SPI_IDLE();
    
    return temperature;
}

void lsm6d_get_accel_data(LSM6D_XL_DATA *data)
{
    uint8_t val;
    
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_READ | LSM6D_OUTX_L_XL);
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->x = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->x |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->y = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->y |= val << 8; 
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->z = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->z |= val << 8;
    LSM6D_SPI_IDLE();
}

void lsm6d_get_gyro_data(LSM6D_G_DATA *data)
{
    uint8_t val;
    
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_READ | LSM6D_OUTX_L_G);
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->x = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->x |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->y = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->y |= val << 8; 
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->z = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->z |= val << 8;
    LSM6D_SPI_IDLE();
}

void lsm6d_get_all_motion_data(LSM6D_SENSOR_DATA *data)
{
    uint8_t val;
    
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_READ | LSM6D_OUTX_L_G);
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.x = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.x |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.y = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.y |= val << 8; 
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.z = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.z |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.x = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.x |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.y = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.y |= val << 8; 
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.z = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.z |= val << 8;
    LSM6D_SPI_IDLE();
}

void lsm6d_get_all_sensor_data(LSM6D_SENSOR_DATA *data)
{
    uint8_t val;
    
    LSM6D_SPI_ACTIVE();
    LSM6D_SPI_TRANSFER(LSM6D_SPI_READ | LSM6D_OUT_TEMP_L);
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->temp = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->temp |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.x = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.x |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.y = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.y |= val << 8; 
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.z = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->g.z |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.x = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.x |= val << 8;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.y = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.y |= val << 8; 
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.z = val;
    val = LSM6D_SPI_TRANSFER(LSM6D_DUMMY_DATA);
    data->xl.z |= val << 8;
    LSM6D_SPI_IDLE();
}