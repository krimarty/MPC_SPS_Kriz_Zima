
#ifndef QMI8658_H_
#define QMI8658_H_

#include <stdint.h>
#include <msp430.h>

// QMI8658A register map
#define QMI_READ            0x80 // pro cteni adres je MSB adresy 1, pro write 0

#define REG_QMI_WHOAMI      0x00
#define REG_QMI_REVISIONID  0x01

#define REG_QMI_CTRL1        0x02 

#define REG_QMI_CTRL2       0x03 // Accelerometer: Output Data Rate, Full Scale, Self-Test
#define REG_QMI_CTRL3       0x04 // Gyroscope: Output Data Rate, Full Scale, Self-Test
#define REG_QMI_CTRL5       0x06 // Low pass filter setting
#define REG_QMI_CTRL7       0x08 // Enable Sensors
#define REG_QMI_CTRL8       0x09 // Motion Detection Control
#define REG_QMI_CTRL9       0x0A // Host Commands

// pripadne misto pro kalibracni registry

// FIFO
#define REG_QMI_FIFO_WTM_TH     0x13 // watermark in odrs
#define REG_QMI_FIFO_CTRL       0x14 // setup
#define REG_QMI_FIFO_SMPL_CNT   0x15 // Sample count LSB
#define REG_QMI_FIFO_STATUS     0x16
#define REG_QMI_FIFO_DATA       0x17

// STATUS
#define REG_QMI_STATUSINT   0x2D    
#define REG_QMI_STATUS0     0x2E
#define REG_QMI_STATUS1     0x2F

// timestamp


// Data Output Reg
#define REG_QMI_AX_L        0x35
#define REG_QMI_GX_L        0x3B

#define REG_QMI_RESET       0x60

void    QMI8658_init(void);
void    QMI8658_read_accel(int16_t *ax, int16_t *ay, int16_t *az);
void    QMI8658_read_gyro (int16_t *gx, int16_t *gy, int16_t *gz);
uint8_t QMI8658_read_reg(uint8_t reg);

#endif /* QMI8658_H_ */
