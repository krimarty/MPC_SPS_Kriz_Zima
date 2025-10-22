
#include "include/QMI8658.h"
#include "include/SPI.h"
#include "include/main.h"
static inline void small_wait(void){ __delay_cycles(1); }

uint8_t QMI8658_read_reg(uint8_t reg){
    small_wait();
    uint8_t v = SPI_read_byte(QMI_READ | reg); // kombinuju registr s 0x80 (MSB 1 = read)
    small_wait();
    return v;
}

void QMI8658_read_multiple(uint8_t reg, uint8_t *buffer, uint8_t length){
    small_wait();
    SPI_read_bytes(QMI_READ | reg, buffer, length);
    small_wait(); 
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
    QMI8658_write_reg(REG_QMI_CTRL1, 0x70);
    // Accel ±16g @112 Hz; Gyro ±2048 dps @112 Hz + self test
    QMI8658_write_reg(REG_QMI_CTRL2, 0x36);
    QMI8658_write_reg(REG_QMI_CTRL3, 0x76);
    // LPF enable s 5.39% odr 
    QMI8658_write_reg(REG_QMI_CTRL5, 0x55);
    // Enable aEN|gEN + data ready pin2
    QMI8658_write_reg(REG_QMI_CTRL7, 0x03);
    small_wait();
    IMU_interrupt_init();
}

void QMI8658_read_imu(int16_t* imu_data)
{
    volatile uint8_t status = QMI8658_read_reg(REG_QMI_STATUSINT);
    (void)status;

    uint8_t buffer[12];

    QMI8658_read_multiple(REG_QMI_AX_L, buffer, 12);

    // Akcelerometr
    imu_data[Ax] = (int16_t)((buffer[1] << 8) | buffer[0]);
    imu_data[Ay] = (int16_t)((buffer[3] << 8) | buffer[2]);
    imu_data[Az] = (int16_t)((buffer[5] << 8) | buffer[4]);

    // Gyroskop
    imu_data[Gx] = (int16_t)((buffer[7] << 8) | buffer[6]);
    imu_data[Gy] = (int16_t)((buffer[9] << 8) | buffer[8]);
    imu_data[Gz] = (int16_t)((buffer[11] << 8) | buffer[10]);
}

void QMI8658_read_accel(int16_t* imu_data)
{
    volatile uint8_t s = QMI8658_read_reg(REG_QMI_STATUSINT);
    (void)s;
    uint8_t buffer[6];

    QMI8658_read_multiple(REG_QMI_AX_L, buffer, 6);

    // Akcelerometr
    imu_data[Ax] = (int16_t)((buffer[1] << 8) | buffer[0]);
    imu_data[Ay] = (int16_t)((buffer[3] << 8) | buffer[2]);
    imu_data[Az] = (int16_t)((buffer[5] << 8) | buffer[4]);
}

void QMI8658_read_gyro(int16_t* imu_data)
{
    volatile uint8_t s = QMI8658_read_reg(REG_QMI_STATUSINT);
    (void)s;
    uint8_t buffer[6];

    QMI8658_read_multiple(REG_QMI_GX_L, buffer, 6);

    // Gyro
    imu_data[Gx] = (int16_t)((buffer[1] << 8) | buffer[0]);
    imu_data[Gy] = (int16_t)((buffer[3] << 8) | buffer[2]);
    imu_data[Gz] = (int16_t)((buffer[5] << 8) | buffer[4]);
}

void IMU_interrupt_init(void)
{
    P2DIR &= ~BIT3;      // P2.3 jako vstup
    P2REN |= BIT3;       // povolit pull resistor
    P2OUT |= BIT3;       // pull-up rezistor (protože QMI má open-drain výstup)

    P2IES |= BIT3;       // přerušení na falling edge (HIGH -> LOW)
    P2IFG &= ~BIT3;      // smazat starý interrupt flag
    P2IE  |= BIT3;       // povolit přerušení na P2.3
}



