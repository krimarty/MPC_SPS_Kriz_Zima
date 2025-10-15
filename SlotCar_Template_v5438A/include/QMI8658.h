
#ifndef QMI8658_H_
#define QMI8658_H_

#include <stdint.h>
#include <msp430.h>

// QMI8658A register map
#define REG_WHOAMI      0x00
#define REG_CTRL1       0x02
#define REG_CTRL2       0x03
#define REG_CTRL3       0x04
#define REG_CTRL5       0x06
#define REG_CTRL7       0x08
#define REG_STATUSINT   0x2D

#define REG_AX_L        0x35
#define REG_GX_L        0x3B

#define REG_RESET       0x60

void    QMI8658_init(void);
void    QMI8658_read_accel(int16_t *ax, int16_t *ay, int16_t *az);
void    QMI8658_read_gyro (int16_t *gx, int16_t *gy, int16_t *gz);
uint8_t QMI8658_read_reg(uint8_t reg);   // debug

#endif /* QMI8658_H_ */
