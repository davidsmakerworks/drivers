/* 
 * DS18B20 command and register definitions
 * Copyright (c) 2019 David Rice
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

#ifndef DS18B20_H
#define	DS18B20_H

#ifdef	__cplusplus
extern "C" {
#endif

/* DS18B20 parameters */
#define DS18B20_SP_SIZE         9

/* Scratchpad indices */
#define DS18B20_TEMP_LSB_INDEX  0
#define DS18B20_TEMP_MSB_INDEX  1
#define DS18B20_TH_INDEX        2
#define DS18B20_TL_INDEX        3
#define DS18B20_CONFIG_INDEX    4
#define DS18B20_CRC_INDEX       8

/* DS18B20 command definitions */
 
/* ROM commands */
#define DS18B20_SEARCH_ROM      0xF0
#define DS18B20_READ_ROM        0x33
#define DS18B20_MATCH_ROM       0x55
#define DS18B20_SKIP_ROM        0xCC
#define DS18B20_ALARM_SEARCH    0xEC
 
/* Function commands */      
#define DS18B20_CONVERT_T       0x44
#define DS18B20_WRITE_SP        0x4E
#define DS18B20_READ_SP         0xBE
#define DS18B20_COPY_SP         0x48
#define DS18B20_RECALL_EE       0xB8
#define DS18B20_READ_PWR_SUP    0xB4
    
/* Resolution settings */
#define DS18B20_RES_9BIT        0b00
#define DS18B20_RES_10BIT       0b01
#define DS18B20_RES_11BIT       0b10
#define DS18B20_RES_12BIT       0b11

/* Timing constants (in microseconds) */
#define DS18B20_TX_RESET_TIME       480 // Length of transmitted reset pulse
#define DS18B20_MIN_PRESENCE_RX     480 // Maximum length of presence receive slot
#define DS18B20_PRESENCE_START_TIME 15 // Minimum time after reset pulse when presence pulse can begin
#define DS18B20_PRESENCE_WAIT_TIME  (60 - DS18B20_PRESENCE_START_TIME) // Amount of time to wait for a presence pulse before giving up
#define DS18B20_PRESENCE_MIN_TIME   60 // Minimum length of presence pulse
#define DS18B20_PRESENCE_MAX_TIME   240 // Maximum length of presence pulse
#define DS18B20_WRITE_0_TIME        90 // Halfway between minimum of 60 and maximum of 120
#define DS18B20_WRITE_1_TIME        2 // Data sheet specifies 1-15 us
#define DS18B20_WRITE_SLOT_TIME     DS18B20_WRITE_0_TIME
#define DS18B20_READ_TIME           2 // Read pulse is specified as > 1 us, so use 2 us
#define DS18B20_SAMPLE_TIME         8 // Sample around 10 us after initial read pulse
#define DS18B20_READ_SLOT_TIME      (60 - DS18B20_SAMPLE_TIME - DS18B20_READ_TIME) // In case we change READ or SAMPLE time
#define DS18B20_RECOVER_TIME        2 // Recovery time is minimum 1 us, so use 2 us to be safe
    
/* Additional constants used by driver - not defined in data sheet */
#define DS18B20_INVALID_TEMPERATURE 0x7FFF

void ds18b20_init_timer(void);
uint16_t ds18b20_get_timer_value(void);
void ds18b20_send_reset_pulse(void);
bool ds18b20_get_presence_pulse(void);
void ds18b20_write_bit_zero(void);
void ds18b20_write_bit_one(void);
void ds18b20_write_byte(uint8_t data);
uint8_t ds18b20_read_bit(void);
uint8_t ds18b20_read_byte(void);
bool ds18b20_read_scratchpad(uint8_t *sp_data);
bool ds18b20_write_scratchpad(uint8_t th, uint8_t tl, uint8_t config);
bool ds18b20_recall_ee(void);
bool ds18b20_copy_scratchpad(void);
bool ds18b20_start_conversion(bool block);
int16_t ds18b20_get_temperature(void);
bool ds18b20_set_resolution(uint8_t res);
    
#ifdef	__cplusplus
}
#endif

#endif	/* DS18B20_H */

