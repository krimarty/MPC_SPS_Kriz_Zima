#include <msp430.h>
#include "include/I2C.h"
#include "include/SPI.h"
#include "include/LED.h"
#include "include/motor.h"
#include "include/UART.h"
#include "include/ADXL343.h"
#include "include/main.h"
//#include "include/L3GD20H.h"

#define I2C_RX_BUFFER_SIZE 5

void initClockTo16MHz(void);

uint16_t results[5];
// I2C
uint8_t RX_buffer[I2C_RX_BUFFER_SIZE] = {0};
uint8_t RXByteCtr = 0;
uint8_t ReceiveIndex = 0;

// UART
volatile uint8_t UART_rx_state = 0;
volatile uint8_t UART_addr = 0;
volatile uint8_t UART_rx_memory[4];
volatile UART_tx_buffer_t UART_tx_buffer = {0};

// LEDS
volatile uint8_t tmp_counter;
volatile bool tmp_toggle;


uint16_t Y_unsigned = 0;
signed int Y = 0;

int read = 0;

int16_t x;
uint16_t a;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    initClockTo16MHz();
    _BIS_SR(GIE);
    LED_init();

    UART_init();
    motor_init();
    go_forward(30);

    UART_tx_buffer.buffer_empty = true;

    int16_t imu_data[6];
    uint8_t i = 0;
    for (; i < 6; i++) 
    {
      imu_data[i] = 20000+i;
    }
    while(1)
    {
    UART_prepare_buffer_bin(&UART_tx_buffer, imu_data,6);
    }   
}

// Interupt for UART
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV, 4))
    {
        case 0: break;           // No interrupt
        case 2:                  // RXIFG – received
        {
            uint8_t rx_val = UCA1RXBUF;  // byte from buffer
            switch (UART_rx_state) {
              case 0: // Waiting for sync
                if (rx_val == 0xAA) {UART_rx_state = 1;}
                break;

              case 1: // Adress
                UART_addr = rx_val;
                UART_rx_state = 2;
                break;

              case 2: // Data
                UART_rx_memory[UART_addr] = rx_val;
                UART_rx_state = 0;
                break;
            }
            break;
        }
        case 4:   // Ready to send next byte
          if (UART_tx_buffer.index < UART_tx_buffer.length)
          {
            UCA1TXBUF = UART_tx_buffer.data[UART_tx_buffer.index++];
          }
          else { UART_tx_buffer.buffer_empty = true; }
          break;
        default: break;
    }
}

// Timer for UART TX periodic communication
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A_ISR(void)
{
    if (UART_tx_buffer.buffer_empty == false)
    {
      UCA1TXBUF = UART_tx_buffer.data[UART_tx_buffer.index++];
      UCA1IE |= UCTXIE;
    }

    if (tmp_counter > 5)
    {
      tmp_counter = 0;
      tmp_toggle = !tmp_toggle;
      led_toggle(tmp_toggle);
    }
    else { tmp_counter++; }

}



#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
  uint8_t rx_val = 0;

  switch(__even_in_range(UCB0IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6: break;                           // Vector  6: STTIFG
  case  8: break;                           // Vector  8: STPIFG
  case USCI_I2C_UCRXIFG:
        rx_val = UCB0RXBUF;
        if (RXByteCtr)
        {
          RX_buffer[ReceiveIndex++] = rx_val;
          RXByteCtr--;
        }

        if (RXByteCtr == 1)
        {
          UCB0CTL1 |= UCTXSTP;
        }
        else if (RXByteCtr == 0)
        {
          UCB0IE &= ~UCRXIE;
        }
        break;                              // Interrupt Vector: I2C Mode: UCRXIFG
  case 12: break;                           // Vector 12: TXIFG
  default: break;
  }
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6: break;                           // Vector  6:  ADC12IFG0
  case  8: break;                           // Vector  8:  ADC12IFG1
  case 10: break;                           // Vector 10:  ADC12IFG2
  case 12: break;                            // Vector 12:  ADC12IFG3
  case 14: break;                           // Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20:                            // Vector 20:  ADC12IFG7
      RGB_RED_ON();
      ADC12CTL0 &=~ADC12SC;                // For sequence-of-Channels mode, ADC12SC must be cleared by software after each sequence to trigger another sequence
      results[0] = ADC12MEM3;                 // Move results, IFG is cleared
      results[1] = ADC12MEM4;                 // Move results, IFG is cleared
      results[2] = ADC12MEM5;                 // Move results, IFG is cleared
      results[3] = ADC12MEM6;                 // Move results, IFG is cleared
      results[4] = ADC12MEM7;                 // Move results, IFG is cleared
      RGB_RED_OFF();
      ADC12CTL0 |= ADC12SC;                   // Start convn - software trigger
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}

void initClockTo16MHz()
{
    UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
    UCSCTL4 |= SELA_2;                        // Set ACLK = REFO
    __bis_SR_register(SCG0);                  // Disable the FLL control loop
    UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
    UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
    UCSCTL2 = FLLD_0 + 487;                   // Set DCO Multiplier for 16MHz
                                              // (N + 1) * FLLRef = Fdco
                                              // (487 + 1) * 32768 = 16MHz
                                              // Set FLL Div = fDCOCLK
    __bic_SR_register(SCG0);                  // Enable the FLL control loop

    // Worst-case settling time for the DCO when the DCO range bits have been
    // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
    // UG for optimization.
    // 32 x 32 x 16 MHz / 32,768 Hz = 500000 = MCLK cycles for DCO to settle
    __delay_cycles(500000);//
    // Loop until XT1,XT2 & DCO fault flag is cleared
    do
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
        SFRIFG1 &= ~OFIFG;                          // Clear fault flags
    }while (SFRIFG1&OFIFG);                         // Test oscillator fault flag
}

