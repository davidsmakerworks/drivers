/*
 * Constant definitions and function protoypes for 
 * Nordic Semiconductor nRF24L01+ RF module driver
 * 
 * Expects to find nRF24L01P-cfg.h in the project include path
 *
 */

#ifndef NRF24L01P_H
#define NRF24L01P_H

#include "nRF24L01P-cfg.h"

/* SPI commands for nRF24L01+
 * 
 * R_REGISTER and W_REGISTER are ORed with register address
 * 
 */

#define NRF24_R_REGISTER            0b00000000U
#define NRF24_W_REGISTER            0b00100000U
#define NRF24_R_RX_PAYLOAD          0b01100001U
#define NRF24_W_TX_PAYLOAD          0b10100000U
#define NRF24_FLUSH_TX              0b11100001U
#define NRF24_FLUSH_RX              0b11100010U
#define NRF24_REUSE_TX_PL           0b11100011U
#define NRF24_R_RX_PL_WID           0b01100000U
#define NRF24_W_ACK_PAYLOAD         0b10101000U
#define NRF24_W_TX_PAYLOAD_NOACK    0b10110000U
#define NRF24_SPI_NOP               0b11111111U

/* Register addresses for nRF24L01+ */

#define NRF24_CONFIG        0x00U
#define NRF24_EN_AA         0x01U
#define NRF24_EN_RXADDR     0x02U
#define NRF24_SETUP_AW      0x03U
#define NRF24_SETUP_RETR    0x04U
#define NRF24_RF_CH         0x05U
#define NRF24_RF_SETUP      0x06U
#define NRF24_STATUS        0x07U
#define NRF24_OBSERVE_TX    0x08U
#define NRF24_RPD           0x09U
#define NRF24_RX_ADDR_P0    0x0AU
#define NRF24_RX_ADDR_P1    0x0BU
#define NRF24_RX_ADDR_P2    0x0CU
#define NRF24_RX_ADDR_P3    0x0DU
#define NRF24_RX_ADDR_P4    0x0EU
#define NRF24_RX_ADDR_P5    0x0FU
#define NRF24_TX_ADDR       0x10U
#define NRF24_RX_PW_P0      0x11U
#define NRF24_RX_PW_P1      0x12U
#define NRF24_RX_PW_P2      0x13U
#define NRF24_RX_PW_P3      0x14U
#define NRF24_RX_PW_P4      0x15U
#define NRF24_RX_PW_P5      0x16U
#define NRF24_FIFO_STATUS   0x17U
#define NRF24_DYNPD         0x1CU
#define NRF24_FEATURE       0x1DU

/* Bit positions and directly assigned values for registers */

/* CONFIG register bit positions */

#define NRF24_MASK_RX_DR   (1 << 6)
#define NRF24_MASK_TX_DS   (1 << 5)
#define NRF24_MASK_MAX_RT  (1 << 4)
#define NRF24_EN_CRC       (1 << 3)
#define NRF24_CRCO         (1 << 2)
#define NRF24_PWR_UP       (1 << 1)
#define NRF24_PRIM_RX      (1 << 0)

/* EN_AA register bit positions */

#define NRF24_ENAA_P5      (1 << 5)
#define NRF24_ENAA_P4      (1 << 4)
#define NRF24_ENAA_P3      (1 << 3)
#define NRF24_ENAA_P2      (1 << 2)
#define NRF24_ENAA_P1      (1 << 1)
#define NRF24_ENAA_P0      (1 << 0)

/* EN_RXADDR register bit positions */

#define NRF24_ERX_P5       (1 << 5)
#define NRF24_ERX_P4       (1 << 4)
#define NRF24_ERX_P3       (1 << 3)
#define NRF24_ERX_P2       (1 << 2)
#define NRF24_ERX_P1       (1 << 1)
#define NRF24_ERX_P0       (1 << 0)

/* SETUP_AW register values
 * 
 * Address width is in bytes
 *
 */

#define NRF24_AW_5          0b11
#define NRF24_AW_4          0b10
#define NRF24_AW_3          0b01

/* SETUP_RETR register values
 * 
 * ARD is auto-retransmit delay in usec
 * 
 * ARC is auto-retry count
 * 
 */

#define NRF24_ARD_250      0b0000
#define NRF24_ARD_500      0b0001 << 4
#define NRF24_ARD_750      0b0010 << 4
#define NRF24_ARD_1000     0b0011 << 4
#define NRF24_ARD_1250     0b0100 << 4
#define NRF24_ARD_1500     0b0101 << 4
#define NRF24_ARD_1750     0b0110 << 4
#define NRF24_ARD_2000     0b0111 << 4
#define NRF24_ARD_2250     0b1000 << 4
#define NRF24_ARD_2500     0b1001 << 4
#define NRF24_ARD_2750     0b1010 << 4
#define NRF24_ARD_3000     0b1011 << 4
#define NRF24_ARD_3250     0b1100 << 4
#define NRF24_ARD_3500     0b1101 << 4
#define NRF24_ARD_3750     0b1110 << 4
#define NRF24_ARD_4000     0b1111 << 4

#define NRF24_ARC_DISABLE   0b0000
#define NRF24_ARC_1         0b0001
#define NRF24_ARC_2         0b0010
#define NRF24_ARC_3         0b0011
#define NRF24_ARC_4         0b0100
#define NRF24_ARC_5         0b0101
#define NRF24_ARC_6         0b0110
#define NRF24_ARC_7         0b0111
#define NRF24_ARC_8         0b1000
#define NRF24_ARC_9         0b1001
#define NRF24_ARC_10        0b1010
#define NRF24_ARC_11        0b1011
#define NRF24_ARC_12        0b1100
#define NRF24_ARC_13        0b1101
#define NRF24_ARC_14        0b1110
#define NRF24_ARC_15        0b1111

/* RF_CH value should be passed in directly */

/* RF_SETUP bit positions */

#define NRF24_CONT_WAVE        (1 << 7)
#define NRF24_RF_DR_LOW        (1 << 5)
#define NRF24_PLL_LOCK         (1 << 4)
#define NRF24_RF_DR_HIGH       (1 << 3)

/* RF_SETUP bit values */
#define NRF24_RF_PWR_0DBM      (0b11 << 1)
#define NRF24_RF_PWR_M6DBM     (0b10 << 1)
#define NRF24_RF_PWR_M12DBM    (0b01 << 1)
#define NRF24_RF_PWR_M18DBM    (0b00 << 1)

// STATUS

#define NRF24_RX_DR          (1 << 6)
#define NRF24_TX_DS          (1 << 5)
#define NRF24_MAX_RT         (1 << 4)
#define NRF24_RX_P_NO        (0b111 << 1)
#define NRF24_TX_FULL_BIT    (1 << 0)

// OBSERVE_TX

#define NRF24_PLOS_CNT     0b1111<<4
#define NRF24_ARC_CNT      0b1111

// RPD

#define NRF24_RPD_BIT      0

// RX_ADDR, TX_ADDR, PW should be passed in directly

// FIFO_STATUS

#define NRF24_TX_REUSE     (1 << 6)
#define NRF24_TX_FULL      (1 << 5)
#define NRF24_TX_EMPTY     (1 << 4)
#define NRF24_RX_FULL      (1 << 1)
#define NRF24_RX_EMPTY     (1 << 0)

// DYNPD

#define NRF24_DPL_P5       (1 << 5)
#define NRF24_DPL_P4       (1 << 4)
#define NRF24_DPL_P3       (1 << 3)
#define NRF24_DPL_P2       (1 << 2)
#define NRF24_DPL_P1       (1 << 1)
#define NRF24_DPL_P0       (1 << 0)

// FEATURE

#define NRF24_EN_DPL       (1 << 2)
#define NRF24_EN_ACK_PAY   (1 << 1)
#define NRF24_EN_DYN_ACK   (1 << 0)

/* Write the specified value to a single-byte register */
void nrf24_write_register(uint8_t reg, uint8_t value);

/* Write values from a buffer to a multi-byte register */
void nrf24_write_register_multi(uint8_t reg, uint8_t *buf, uint8_t len);

/* Read the value of a single-byte register */
uint8_t nrf24_read_register(uint8_t reg);

/* Read values from a multi-byte register into a buffer */
void nrf24_read_register_multi(uint8_t reg, uint8_t *buf, uint8_t len);

/* Set the specified bits in a single-byte register - performs read/modify/write */
void nrf24_set_register_bits(uint8_t reg, uint8_t bits);

/* Clear the specified bits in a single-byte register - performs read/modify/write */
void nrf24_clear_register_bits(uint8_t reg, uint8_t bits);

/* Flush transmit FIFO */
void nrf24_flush_tx(void);

/* Flush receive FIFO */
void nrf24_flush_rx(void);

/* Set transmit address */
void nrf24_set_tx_address(uint8_t *addr, uint8_t addr_len);

/* Set receive address for specified pipe */
void nrf24_set_rx_address(uint8_t pipe, uint8_t *addr, uint8_t addr_len);

/* Write payload to transmit FIFO - does NOT actually transmit data */
void nrf24_write_payload(uint8_t *buffer, uint8_t len);

/* Read data from receive FIFO */
void nrf24_read_payload(uint8_t *buffer, uint8_t len);


#endif /* NRF24L01P_H */