
#include "include/QMI8658.h"
#include "include/SPI.h"
#include "include/main.h"
static inline void small_wait(void){ __delay_cycles(16); }

uint8_t QMI8658_read_reg(uint8_t reg){
    small_wait();
    uint8_t v = SPI_read_byte(QMI_READ | reg); // kombinuju registr s 0x80 (MSB 1 = read)
    //uint8_t v = SPI_read_byte(reg);
    small_wait();
    return v;

}

static void QMI8658_write_reg(uint8_t reg, uint8_t val){
    small_wait();
    SPI_write_byte(reg, val);
    small_wait();
}

void QMI8658_init(void){
    SENSOR_POWER_ON();
    SPI_init();
    
    // debug;
    uint8_t id = QMI8658_read_reg(REG_QMI_WHOAMI);
    if(id != 0x05) {
        while(1){}  // debug
    }

    // Enable auto-increment
    QMI8658_write_reg(REG_QMI_CTRL1, 0x20);
    // Accel ±16g @112 Hz; Gyro ±2048 dps @112 Hz + self test
    QMI8658_write_reg(REG_QMI_CTRL2, 0x36);
    QMI8658_write_reg(REG_QMI_CTRL3, 0x76);
    // LPF enable s 5.39% odr 
    QMI8658_write_reg(REG_QMI_CTRL5, 0x55);
    // Enable aEN|gEN + data ready pin2
    QMI8658_write_reg(REG_QMI_CTRL7, 0x23);
    small_wait();
}

void QMI8658_read_accel(int16_t *ax, int16_t *ay, int16_t *az)
{
    volatile uint8_t s = QMI8658_read_reg(REG_QMI_STATUSINT);
    (void)s;
    uint8_t d0 = QMI8658_read_reg(REG_QMI_AX_L + 0);
    uint8_t d1 = QMI8658_read_reg(REG_QMI_AX_L + 1);
    uint8_t d2 = QMI8658_read_reg(REG_QMI_AX_L + 2);
    uint8_t d3 = QMI8658_read_reg(REG_QMI_AX_L + 3);
    uint8_t d4 = QMI8658_read_reg(REG_QMI_AX_L + 4);
    uint8_t d5 = QMI8658_read_reg(REG_QMI_AX_L + 5);

    *ax = (int16_t)((d1<<8)|d0);
    *ay = (int16_t)((d3<<8)|d2);
    *az = (int16_t)((d5<<8)|d4);
}

void QMI8658_read_gyro(int16_t *gx, int16_t *gy, int16_t *gz)
{
    volatile uint8_t s = QMI8658_read_reg(REG_QMI_STATUSINT);
    (void)s;
    uint8_t d0 = QMI8658_read_reg(REG_QMI_GX_L + 0);
    uint8_t d1 = QMI8658_read_reg(REG_QMI_GX_L + 1);
    uint8_t d2 = QMI8658_read_reg(REG_QMI_GX_L + 2);
    uint8_t d3 = QMI8658_read_reg(REG_QMI_GX_L + 3);
    uint8_t d4 = QMI8658_read_reg(REG_QMI_GX_L + 4);
    uint8_t d5 = QMI8658_read_reg(REG_QMI_GX_L + 5);

    *gx = (int16_t)((d1<<8)|d0);
    *gy = (int16_t)((d3<<8)|d2);
    *gz = (int16_t)((d5<<8)|d4);
}
