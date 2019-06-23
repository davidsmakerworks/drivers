/* 
 * File:   ssd1306.h
 * Author: David Rice
 *
 * Created on September 29, 2017, 4:29 PM
 */

#ifndef SSD1306_H
#define	SSD1306_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SSD1306_SET_CONTRAST        0x81 /* Send contrast setting as next command */
#define SSD1306_DISP_FOLLOW_RAM     0xA4
#define SSD1306_DISP_ALL_ON         0xA5
#define SSD1306_DISP_NORMAL         0xA6
#define SSD1306_DISP_INVERSE        0xA7
#define SSD1306_DISP_SLEEP          0xAE
#define SSD1306_DISP_WAKE           0xAF

#define SSD1306_RIGHT_HSCROLL       0x26
#define SSD1306_LEFT_HSCROLL        0x27

#define SSD1306_RIGHT_HVSCROLL      0x29
#define SSD1306_LEFT_HVSCROLL       0x2A

#define SSD1306_STOP_SCROLL         0x2E
#define SSD1306_START_SCROLL        0x2F

#define SSD1306_SET_VSCROLL_AREA    0xA3

#define SSD1306_PAGE0               0b000
#define SSD1306_PAGE1               0b001
#define SSD1306_PAGE2               0b010
#define SSD1306_PAGE3               0b011
#define SSD1306_PAGE4               0b100
#define SSD1306_PAGE5               0b101
#define SSD1306_PAGE6               0b110
#define SSD1306_PAGE7               0b111

#define SSD1306_5_FRAMES            0b000
#define SSD1306_64_FRAMES           0b001
#define SSD1306_128_FRAMES          0b010
#define SSD1306_256_FRAMES          0b011
#define SSD1306_3_FRAMES            0b100
#define SSD1306_4_FRAMES            0b101
#define SSD1306_25_FRAMES           0b110
#define SSD1306_2_FRAMES            0b111

#define SSD1306_SET_START_COL_LOW   0x00 /* OR this command with the lower nibble of start column (4 bits) */
#define SSD1306_SET_START_COL_HIGH  0x10 /* OR this command with the upper nibble of start column (4 bits) */
#define SSD1306_SET_MEM_ADDR_MODE   0x20 /* Send addressing mode as next command */
#define SSD1306_SET_COLUMN_ADDR     0x21 /* Send start and end columns as next two commands */
#define SSD1306_SET_PAGE_ADDR       0x22 /* Send start and end pages as next two commands */
#define SSD1306_SET_PAGE_START      0xB0 /* OR this command with the page start address (3 bits) */

#define SSD1306_ADDR_MODE_HORZ      0b00
#define SSD1306_ADDR_MODE_VERT      0b01
#define SSD1306_ADDR_MODE_PAGE      0b10

#define SSD1306_SET_START_LINE      0x40 /* OR this command with the start line (6 bits) */
#define SSD1306_SET_SEG0_COL0       0xA0
#define SSD1306_SET_SEG0_COL127     0xA1
#define SSD1306_SET_MUX_RATIO       0xA8
#define SSD1306_SET_SCAN_INC        0xC0
#define SSD1306_SET_SCAN_DEC        0xC8
#define SSD1306_SET_DISP_OFFSET     0xD3
#define SSD1306_SET_COM_HW_CONFIG   0xDA
    
/* OR two of the next 4 items together as second byte for SET_COM_HW_CONFIG */
#define SSD1306_SEQ_COM_PIN_CFG     0b00000010
#define SSD1306_ALT_COM_PIN_CFG     0b00010010
#define SSD1306_DISABLE_COM_LR_MAP  0b00000010
#define SSD1306_ENABLE_COM_LR_MAP   0b00100010

#define SSD1306_SET_DISP_CLOCK      0xD5
#define SSD1306_SET_PRECHARGE       0xD9
#define SSD1306_SET_VCOMH_DESELECT  0xDB
#define SSD1306_NOP                 0xE3

#define SSD1306_VCOMH_065_VCC       0b000
#define SSD1306_VCOMH_077_VCC       0b010
#define SSD1306_VCOMH_083_VCC       0b011

#define SSD1306_SET_CHARGE_PUMP     0x8D /* Send charge pump state as next command */

#define SSD1306_CHARGE_PUMP_DISABLE 0b10000
#define SSD1306_CHARGE_PUMP_ENABLE  0b10100

#define SSD1306_COMMAND             0x00
#define SSD1306_DATA                0x40

#ifdef	__cplusplus
}
#endif

#endif	/* SSD1306_H */

