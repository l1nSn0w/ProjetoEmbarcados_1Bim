#include <inttypes.h>
#include <tm4c123gh6pm.h>
#include <ManipularGPIO.h>
#include <ControlePWM.h>

#define BOTAO_START PA2
#define BOTAO_ROTACAO PA3
#define BOTAO_INCREMENTO PA4
#define BOTAO_DECREMENTO PA5

int LEDS[3];

uint32_t currentMillis;
uint32_t previousMillis = 0;
uint32_t millisInterval = 20;
uint32_t cont = 0, aux = 0;

void configurarRegistradores()
{
    ConfigurarSysTick();

    AtivarPort(PORT_F);
    ConfigurarPino(&GPIO_PORTF_DIR_R, &GPIO_PORTF_DEN_R, LED_AZUL, OUTPUT);

    PWM(&GPIO_PORTF_DATA_R, LED_AZUL);
}


int main(void)
{
  configurarRegistradores();

  uint8_t cont;

  while(1)
  {
      currentMillis = millis();

       if (currentMillis - previousMillis >= millisInterval)
        {
            cont+=2;

            if(cont>99)
               cont = 0;

            previousMillis = currentMillis; // setup clock for next tick
        }

      dutyCicle(cont); //chamar essa função sempre que algum calculo extenso for executado
  }

}
