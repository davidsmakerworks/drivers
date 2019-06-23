/*
 * Driver for Nordic Semiconductor nRF24L01+
 * 
 * Designed and implemented by David Rice
 * 
 * Requires definitions for:
 * NRF24_CSN - CSN (active low) pin on nRF24L01+
 * NRF24_CE - Chip Enable pin on nRF24L01+
 * NRF24_IRQ - Interrupt pin (active low) on nRF24L01+
 * NRF24_XFER_SPI(x) - Transfer one byte to/from SPI bus without changing CSN
 * 
 * Configuration is usually located in nRF24L01P-cfg.h in the same folder with the main project
 * 
 */ 

#include <stdint.h>

#include "nRF24L01P.h"

/* Write the specified value to a single-byte register */
void nrf24_write_register(uint8_t reg, uint8_t value)
{
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_W_REGISTER | reg);
    NRF24_XFER_SPI(value);
    
    NRF24_CSN = 1;
}

/* Write values from a buffer to a multi-byte register */
void nrf24_write_register_multi(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_W_REGISTER | reg);
    
    for (i = 0; i < len; i++) {
        NRF24_XFER_SPI(buf[i]);
    }
    
    NRF24_CSN = 1;
}

/* Read the value of a single-byte register */
uint8_t nrf24_read_register(uint8_t reg)
{
    uint8_t value; 
    
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_R_REGISTER | reg);
    value = NRF24_XFER_SPI(NRF24_SPI_NOP);
    
    NRF24_CSN = 1;
    
    return value;
}

/* Read values from a multi-byte register into a buffer */
void nrf24_read_register_multi(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_R_REGISTER | reg);
    
    for (i = 0; i < len; i++) {
        buf[i] = NRF24_XFER_SPI(NRF24_SPI_NOP);
    }
    
    NRF24_CSN = 1;
}

/* Set the specified bits in a single-byte register - performs read/modify/write */
void nrf24_set_register_bits(uint8_t reg, uint8_t bits)
{
    uint8_t currentValue;
    
    currentValue = nrf24_read_register(reg);
    
    currentValue = currentValue | bits;
    
    nrf24_write_register(reg, currentValue);
}

/* Clear the specified bits in a single-byte register - performs read/modify/write */
void nrf24_clear_register_bits(uint8_t reg, uint8_t bits)
{
    uint8_t currentValue;
    
    currentValue = nrf24_read_register(reg);
    
    currentValue = currentValue & ~bits;
    
    nrf24_write_register(reg, currentValue);
}

/* Flush transmit FIFO */
void nrf24_flush_tx(void)
{
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_FLUSH_TX);
    
    NRF24_CSN = 1;
}

/* Flush receive FIFO */
void nrf24_flush_rx(void)
{
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_FLUSH_RX);
    
    NRF24_CSN = 1;
}

/* Set transmit address */
void nrf24_set_tx_address(uint8_t *addr, uint8_t addr_len)
{
    nrf24_write_register_multi(NRF24_TX_ADDR, addr, addr_len);
}

/* Set receive address for specified pipe */
void nrf24_set_rx_address(uint8_t pipe, uint8_t *addr, uint8_t addr_len)
{
    nrf24_write_register_multi(pipe, addr, addr_len);
}

/* Write payload to transmit FIFO - does NOT actually transmit data */
void nrf24_write_payload(uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_W_TX_PAYLOAD);
    
    for (i = 0; i < len; i++) {
        NRF24_XFER_SPI(buffer[i]);
    }
    
    NRF24_CSN = 1;
}

/* Read data from receive FIFO */
void nrf24_read_payload(uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    
    NRF24_CSN = 0;
    
    NRF24_XFER_SPI(NRF24_R_RX_PAYLOAD);
    
    for (i = 0; i < len; i++) {
        buffer[i] = NRF24_XFER_SPI(NRF24_SPI_NOP);
    }
    
    NRF24_CSN = 1;
}
