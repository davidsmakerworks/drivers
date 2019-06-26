/*
 * Maxim DS18B20 1-Wire Temperature Sensor Driver
 * Copyright (c) 2019 David Rice
 * 
 * This driver implements a minimal version of the 1-Wire protocol to communicate with the
 * DS18B20 temperature sensor. Timing specifications are checked based on a 1 ms timer.
 * 
 * CRC checking is not currently implemented.
 * 
 * TODO: Move ds18b20_init_timer and ds18b20_get_timer_value into a seperate
 * architecture-specific file to improve driver portability.
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

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "ds18b20.h"
#include "ds18b20-cfg.h"

/* Initializes Timer0 for use with 1-Wire bus timing */
void ds18b20_init_timer(void) {
    /* Set up Timer0 with 1/8 prescaler and Fosc/4 clock source */
    T0CON1bits.T0CKPS = 0b0011;
    T0CON1bits.T0CS = 0b010;
    
    /* Timer0 operates in 16-bit mode */
    T0CON0bits.T016BIT = 1;
    
    /* Start timer with 1 us resolution when Fosc = 32 MHz */
    T0CON0bits.T0EN = 1;
}

/* Returns 16-bit value from Timer0 */
uint16_t ds18b20_get_timer_value(void) {
    uint16_t val;
    
    val = TMR0L;
    val = val | ((uint16_t)TMR0H << 8);
    
    return val;
}

/* Sends reset pulse on One Wire bus */
void ds18b20_send_reset_pulse(void) {
    DS18B20_PULL_BUS_LOW();
    __delay_us(DS18B20_TX_RESET_TIME);
    DS18B20_RELEASE_BUS();
}

/* Listens for One Wire presence pulse and returns true if presence pulse is valid */
bool ds18b20_get_presence_pulse(void) {
    uint16_t start_time;
    uint16_t valid_time;
    
    bool pulse_started = false; /* Flag to indicate that the presence pulse started */
    bool pulse_valid = false; /* Flag to indicate that the presence pulse was long enough to be valid */
    bool pulse_ended = false; /* Flag to indicate that the presence pulse ended within the allocated time window */
    
    DS18B20_RELEASE_BUS(); /* Release bus just to be safe */
    
    __delay_us(DS18B20_PRESENCE_START_TIME); /* Wait for the minimum amount of time before the pulse can start */
    
    start_time = ds18b20_get_timer_value(); /* Timer value when we started waiting for the presence pulse */
    
    /* Poll for presence pulse until start of pulse is detected or until time expires */
    while (((ds18b20_get_timer_value() - start_time) < DS18B20_PRESENCE_WAIT_TIME) && !pulse_started) {
        pulse_started = !DS18B20_DATA;
    }
    
    /* If the start of the pulse was never detected, return false */
    if (!pulse_started) {
        return false;
    }
    
    start_time = ds18b20_get_timer_value(); /* Timer value when we started waiting for the end of the presence pulse */
    valid_time = start_time + DS18B20_PRESENCE_MIN_TIME; /* Minimum time that the pulse must be detected for it to be valid */
    
    /* Poll for end of presence pulse until pulse ends or time expires */
    while (((ds18b20_get_timer_value() - start_time) < DS18B20_PRESENCE_MAX_TIME) && !pulse_ended) {
        /* If the pulse length equals or exceeds the minimum length, cosider it valid */
        if (!pulse_valid && (!((ds18b20_get_timer_value() - start_time) < DS18B20_PRESENCE_MIN_TIME))) {
            pulse_valid = true;
        }
        pulse_ended = DS18B20_DATA;
    } 
    
    /* Wait for end of time slot */
    while ((ds18b20_get_timer_value() - start_time) < (DS18B20_MIN_PRESENCE_RX - DS18B20_PRESENCE_START_TIME)); 
    
    /* If the pulse is long enough to be valid and ended before the maximum allowable time, return true */
    return (pulse_valid & pulse_ended);
}

/* Transmit a zero bit on the One Wire bus */
void ds18b20_write_bit_zero(void) {
    DS18B20_PULL_BUS_LOW();
    __delay_us(DS18B20_WRITE_0_TIME);
    DS18B20_RELEASE_BUS();
    
    __delay_us(DS18B20_RECOVER_TIME);
}

/* Transmit a one bit on the One Wire Bus */
void ds18b20_write_bit_one(void) {
    DS18B20_PULL_BUS_LOW();   
    __delay_us(DS18B20_WRITE_1_TIME);
    DS18B20_RELEASE_BUS();
    
    __delay_us(DS18B20_WRITE_SLOT_TIME - DS18B20_WRITE_1_TIME);
    __delay_us(DS18B20_RECOVER_TIME);
}

/* Transmit one byte (8 bits) on the One Wire bus */
void ds18b20_write_byte(uint8_t data) {
    uint8_t i;
    
    for (i = 0; i < 8; i++) {
        (data & 1) ? ds18b20_write_bit_one() : ds18b20_write_bit_zero();
        data >>= 1;
    }
}

/* Read one bit from the One Wire bus */
uint8_t ds18b20_read_bit(void) {
    uint8_t data;
    
    DS18B20_PULL_BUS_LOW();
    __delay_us(DS18B20_READ_TIME);
    DS18B20_RELEASE_BUS();
    
    __delay_us(DS18B20_SAMPLE_TIME);
    
    data = DS18B20_DATA;
    
    __delay_us(DS18B20_READ_SLOT_TIME);
    __delay_us(DS18B20_RECOVER_TIME);
    
    return data;
}

/* Read one byte (8 bits) from the One Wire bus */
uint8_t ds18b20_read_byte(void) {
    uint8_t data = 0;
    uint8_t i;
    
    for (i = 0; i < 8; i++) {
        data |= (ds18b20_read_bit() << i);
    }
    
    return data;
}

/* Reads all 9 bytes of the scratchpad - no CRC checking is implemented in this version */
bool ds18b20_read_scratchpad(uint8_t *sp_data) {
    uint8_t i;
    
    ds18b20_send_reset_pulse();
    
    if (ds18b20_get_presence_pulse()) {
        ds18b20_write_byte(DS18B20_SKIP_ROM);
        ds18b20_write_byte(DS18B20_READ_SP);
        
        for (i = 0; i < DS18B20_SP_SIZE; i++) {
            sp_data[i] = ds18b20_read_byte();
        }
        
        return true;
    } else {
        return false;
    }
}

/* Writes the 3 configurable items to the scratchpad (Th, Tl, Config) */
bool ds18b20_write_scratchpad(uint8_t th, uint8_t tl, uint8_t config) {
    ds18b20_send_reset_pulse();
    
    if (ds18b20_get_presence_pulse()) {
        ds18b20_write_byte(DS18B20_SKIP_ROM);
        ds18b20_write_byte(DS18B20_WRITE_SP);
        
        ds18b20_write_byte(th);
        ds18b20_write_byte(tl);
        ds18b20_write_byte(config);
        
        return true;
    } else {
        return false;
    }
}

bool ds18b20_copy_scratchpad(void) {
    ds18b20_send_reset_pulse();
    
    if (ds18b20_get_presence_pulse()) {
        ds18b20_write_byte(DS18B20_SKIP_ROM);
        ds18b20_write_byte(DS18B20_COPY_SP);
        
        __delay_ms(10);
        
        return true;
    } else {
        return false;
    }        
}

bool ds18b20_recall_ee(void) {
    ds18b20_send_reset_pulse();
    
    if (ds18b20_get_presence_pulse()) {
        ds18b20_write_byte(DS18B20_SKIP_ROM);
        ds18b20_write_byte(DS18B20_RECALL_EE);
        
        __delay_ms(1);
        
        return true;
    } else {
        return false;
    }
}

/* 
 * Starts DS18B20 temperature conversion process
 * 
 * Parameter block determines whether this should block until conversion is complete
 * or return immediately
 *  */
bool ds18b20_start_conversion(bool block) {
    uint8_t pollCycles = 0;
    bool convDone = false;
    
    ds18b20_send_reset_pulse();
    
    if (ds18b20_get_presence_pulse()) {
        ds18b20_write_byte(DS18B20_SKIP_ROM);
        ds18b20_write_byte(DS18B20_CONVERT_T);
        
        if (block) {
            while (pollCycles < 100 && !convDone) {
                __delay_ms(10);
                
                convDone = ds18b20_read_bit();
                
                pollCycles++;
            }
            
            return convDone;
        } else {
            return true;
        }
    } else {
        return false;
    }
    
}

/* 
 * Returns the result of the most recent temperature conversion, or DS18B20_INVALID_TEMPERATURE
 * if the attempt to read the value from the scratchpad failed
 */
int16_t ds18b20_get_temperature(void) {
    uint8_t values[DS18B20_SP_SIZE];
    int16_t temperature;
    
    if (ds18b20_read_scratchpad(values)) {
        temperature = values[DS18B20_TEMP_LSB_INDEX] | (values[DS18B20_TEMP_MSB_INDEX] << 8);
    } else {
        temperature = DS18B20_INVALID_TEMPERATURE;
    }
    
    return temperature;
}

bool ds18b20_set_resolution(uint8_t res) {
    uint8_t values[DS18B20_SP_SIZE];
    
    ds18b20_read_scratchpad(values);
    
    return ds18b20_write_scratchpad(values[DS18B20_TH_INDEX], values[DS18B20_TL_INDEX], 0b00011111 | (res << 5));
}
