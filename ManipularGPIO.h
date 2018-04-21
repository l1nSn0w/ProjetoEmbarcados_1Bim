#ifndef _MANIPULAR_GPIO_
#define _MANIPULAR_GPIO_

#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

#define BOTAO_1 PF4
#define BOTAO_2 PF0

#define LED_VERMELHO PF1
#define LED_AZUL PF2
#define LED_VERDE PF3

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
#define PORT_E 4
#define PORT_F 5

#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7

#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
#define PC7 7

#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PE0 0
#define PE1 1
#define PE2 2
#define PE3 3
#define PE4 4
#define PE5 5
#define PE6 6
#define PE7 7

#define PF0 0
#define PF1 1
#define PF2 2
#define PF3 3
#define PF4 4
#define PF5 5
#define PF6 6
#define PF7 7

#define Ler_BIT(registrador, bit)  (((registrador) >> (bit)) & 0x01)
#define Setar_BIT(registrador, bit) ((registrador) |= (1 << (bit)))
#define Limpar_BIT(registrador, bit) ((registrador) &= ~(1 << (bit)))
#define Escrever_BIT(registrador, bit, valorBit) (valorBit ? Setar_BIT(registrador, bit) : Limpar_BIT(registrador, bit))


void AtivarPort(int port)
{
    Escrever_BIT(SYSCTL_RCGCGPIO_R, port, 1 );
}

void DesativarPort(int port)
{
   Escrever_BIT(SYSCTL_RCGCGPIO_R, port, 0);
}

void ConfigurarPino(uint32_t *port_dir, uint32_t *port_den, int pino, int modo)
{
   Escrever_BIT(*(port_dir), pino, modo);

   Escrever_BIT(*(port_den), pino, 1);
}

int LerPino(uint32_t *registrador, uint32_t pino)
{
    return Ler_BIT(*(registrador), pino);
}

void SetarPino(uint32_t *registrador, uint32_t pino, uint32_t valor)
{
    Escrever_BIT(*(registrador), pino, valor);
}

uint32_t tempoSystick = 24; //Equivalente a 250us
uint32_t sysTickMillis = 0;
uint32_t sysTickMicros = 0;

void InterrupcaoSystick()
{
    sysTickMicros+=6;

    if ((sysTickMicros/1000) >= ((1*sysTickMillis)+1)) // 1ms
     sysTickMillis++;
}

void ConfigurarSysTick(void)
{
    NVIC_ST_RELOAD_R = tempoSystick;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE;
}

uint64_t millis()
{
    return sysTickMillis;
}


uint32_t micros()
{
    return sysTickMicros;
}

void delay(uint32_t ms)
{
    uint64_t inicio = millis();

    while (millis() - inicio <= ms) ;
}

void delay_ms(uint32_t ms)
{
    uint64_t inicio = micros();

    while (micros() - inicio <= ms) ;
}

#endif
