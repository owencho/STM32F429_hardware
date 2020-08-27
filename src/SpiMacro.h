#ifndef SPIMACRO_H
#define SPIMACRO_H

#define SPI_2_LINE_UNIDIRECTION (0ULL<<15)
#define SPI_1_LINE_BIDIRECTION (1ULL<<15)

#define SPI_BIDIRECTION_OUTPUT_DISABLE (0ULL<<14)
#define SPI_BIDIRECTION_OUTPUT_ENABLE (1ULL<<14)

#define SPI_CRC_CAL_DISABLE (0ULL<<13)
#define SPI_CRC_CAL_ENABLE (1ULL<<13)

#define SPI_TRANSFER_NEXT_DATAPHASE (0ULL<<12)
#define SPI_TRANSFER_NEXT_CRC (1ULL<<12)

#define SPI_8BIT_DATA_FRAME (0ULL<<11)
#define SPI_16BIT_DATA_FRAME (1ULL<<11)

#define SPI_TRANSMIT_RECEIVE (0ULL<<10)
#define SPI_RECEIVE_ONLY (1ULL<<10)

#define SPI_SOFTWARE_SLAVE_M_DISABLED (0ULL<<9)
#define SPI_SOFTWARE_SLAVE_M_ENABLED (1ULL<<9)

#define SPI_SOFTWARE_SLAVE_M_DISABLED (0ULL<<9)
#define SPI_SOFTWARE_SLAVE_M_ENABLED (1ULL<<9)

#define SPI_NSS_DISABLED (0ULL<<8)
#define SPI_NSS_ENABLE (1ULL<<8)

#define SPI_MSB_FIRST (0ULL<<7)
#define SPI_LSB_FIRST (1ULL<<7)

#define SPI_DISABLE (0ULL<<6)
#define SPI_ENABLE (1ULL<<6)

#define SPI_BAUD_FCLK_DIV2 (0ULL<<3)
#define SPI_BAUD_FCLK_DIV4 (1ULL<<3)
#define SPI_BAUD_FCLK_DIV8 (2ULL<<3)
#define SPI_BAUD_FCLK_DIV16 (3ULL<<3)
#define SPI_BAUD_FCLK_DIV32 (4ULL<<3)
#define SPI_BAUD_FCLK_DIV64 (5ULL<<3)
#define SPI_BAUD_FCLK_DIV256 (6ULL<<3)
#define SPI_BAUD_FCLK_DIV128 (7ULL<<3)

#define SPI_MASTER_CONFIG (1ULL<<2)
#define SPI_SLAVE_CONFIG (0ULL<<2)

#define SPI_CLK_IDLE0 (0ULL<<1)
#define SPI_CLK_IDLE1 (1ULL<<1)

#define SPI_DATA_CAPTURE_FIRST_CLK_TRANS (0ULL<<0)
#define SPI_DATA_CAPTURE_SECOND_CLK_TRANS (1ULL<<0)

//CR2

#define SPI_TX_EMPTY_INT_DISABLE (0ULL<<(7+16))
#define SPI_TX_EMPTY_INT_ENABLE (1ULL<<(7+16))

#define SPI_RX_EMPTY_INT_DISABLE (0ULL<<(6+16))
#define SPI_RX_EMPTY_INT_ENABLE (1ULL<<(6+16))

#define SPI_ERROR_INT_DISABLE (0ULL<<(5+16))
#define SPI_ERROR_INT_ENABLE (1ULL<<(5+16))

#define SPI_MOTOROLA_MODE (0ULL<<(4+16))
#define SPI_TI_MODE (1ULL<<(4+16))

#define SPI_SS_OUT_DISABLED (0ULL<<(2+16))
#define SPI_SS_OUT_ENABLED (1ULL<<(2+16))

#define SPI_TX_DMA_DISABLED (0ULL<<(1+16))
#define SPI_TX_DMA_ENABLED (1ULL<<(1+16))

#define SPI_RX_DMA_DISABLED (0ULL<<(0+16))
#define SPI_RX_DMA_ENABLED (1ULL<<(0+16))

#endif // SPIMACRO_H
