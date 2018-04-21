#include <inttypes.h>
#include <tm4c123gh6pm.h>
#include <ManipularGPIO.h>
#include <ControlePWM.h>

#define BOTAO_START PA2
#define BOTAO_ROTACAO PA3
#define BOTAO_INCREMENTO PA4
#define BOTAO_DECREMENTO PA5

int LEDS[3];


uint32_t aux = 0;

void configurarRegistradores()
{
    ConfigurarSysTick();

    AtivarPort(PORT_F);
    AtivarPort(PORT_A);

    ConfigurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, BOTAO_START, INPUT);
    ConfigurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, BOTAO_ROTACAO, INPUT);
    ConfigurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, BOTAO_INCREMENTO, INPUT);
    ConfigurarPino(&GPIO_PORTA_DIR_R, &GPIO_PORTA_DEN_R, BOTAO_DECREMENTO, INPUT);

    ConfigurarPino(&GPIO_PORTF_DIR_R, &GPIO_PORTF_DEN_R, LED_AZUL, OUTPUT);
    ConfigurarPino(&GPIO_PORTF_DIR_R, &GPIO_PORTF_DEN_R, LED_VERMELHO, OUTPUT);

    PWM(&GPIO_PORTF_DATA_R, LED_VERMELHO);
}

uint32_t velocidadeMotor = 100, contadorBotaoIncremento = 0, contadorBotaoDecremento = 0;
uint8_t fator = 25;

void BotaoIncremento()
{
    uint32_t currentMillis;
    static uint32_t previousMillis = 0;
    uint32_t millisInterval = 1000; //1 segundo

    currentMillis = millis();

    if (currentMillis - previousMillis >= millisInterval)
    {
      if(LerPino(&GPIO_PORTA_DATA_R, BOTAO_INCREMENTO))
         contadorBotaoIncremento++;
      else
         contadorBotaoIncremento = 0;

      if(contadorBotaoIncremento>=5)
      {
        if(velocidadeMotor<100)
         velocidadeMotor+=fator;
      }
      previousMillis = currentMillis;
    }
}

void BotaoDecremento()
{
    uint32_t currentMillis;
    static uint32_t previousMillis = 0;
    uint32_t millisInterval = 1000; //1 segundo

    currentMillis = millis();

    if (currentMillis - previousMillis >= millisInterval)
    {
      if(LerPino(&GPIO_PORTA_DATA_R, BOTAO_DECREMENTO))
          contadorBotaoDecremento++;
      else
          contadorBotaoDecremento = 0;

      if(contadorBotaoDecremento>=5)
      {
        if(velocidadeMotor>0)
         velocidadeMotor-=fator;
        if (velocidadeMotor==1)
        {
            dutyCicle(0,0);
            handlePWM();
        }
      }
      previousMillis = currentMillis;
    }

}

void BotaoStart(uint32_t *var)
{
    if (LerPino(&GPIO_PORTA_DATA_R, BOTAO_START))
    {
       dutyCicle(0,0);
       handlePWM();
       while (LerPino(&GPIO_PORTA_DATA_R, BOTAO_START));
       *var=!*var;
       delay_ms(200);
    }
}

void AguardarInicio()
{
    while (!LerPino(&GPIO_PORTA_DATA_R, BOTAO_START)); //enquanto o botão não for pressionado
    while (LerPino(&GPIO_PORTA_DATA_R, BOTAO_START)); //enquanto o botão estiver pressionado
    //delay_ms(250);
}

int main(void)
{
  uint8_t rodar = 1;

  configurarRegistradores();
  AguardarInicio();

  while(1)
  {
      if (rodar)
      {
          dutyCicle(0,velocidadeMotor);
          handlePWM();
      }

      BotaoStart(&rodar);
      BotaoIncremento();
      BotaoDecremento();

  }

}



