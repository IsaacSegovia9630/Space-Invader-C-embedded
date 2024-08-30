/*
 * SPI.h
 *
 *  Created on: 26/10/2022
 *      Author: Isaac Segovia
 */

#ifndef SPI_H_
#define SPI_H_



#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 2 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 3 in a port */
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */

#define FRAME_SIZE 8U
#define TRANSFER_DELAY 1000000000

#define TRANSFER_SIZE     64U     /*! Transfer dataSize */
#define TRANSFER_BAUDRATE 3000000U

void SPI_config(void);

#endif /* SPI_H_ */
