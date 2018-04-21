#ifndef _ControlePWM_
#define _ControlePWM_


#define ON 1
#define OFF 0
#define MAX_PINOS 5
#define pwmMax 100

typedef struct pinosPWM
{
    uint32_t pino;
    uint32_t valorPWM;
    uint32_t EstadoPino;
    uint32_t contadorPWM;
    uint32_t port;
} sPWM;


sPWM pinoPWM[MAX_PINOS];

uint32_t qntPinos = 0;

// Configura os atributos do PWM
void PWM(uint32_t port, uint32_t pino)
{
    pinoPWM[qntPinos].pino = pino;
    pinoPWM[qntPinos].port = port;
    pinoPWM[qntPinos].valorPWM = 0;
    pinoPWM[qntPinos].EstadoPino = ON;
    pinoPWM[qntPinos].contadorPWM = 0;
    qntPinos++;
}

void handlePWM()
{
   uint8_t aux = 0;

    for(; aux<qntPinos; aux++)
    {
        if(pinoPWM[aux].valorPWM==0)
        {
                 SetarPino(pinoPWM[aux].port, pinoPWM[aux].pino, LOW); //setamos o pino
                 continue;
        }
        else if(pinoPWM[aux].valorPWM==100)
        {
                 SetarPino(pinoPWM[aux].port, pinoPWM[aux].pino, HIGH); //setamos o pino
                 continue;
        }

        pinoPWM[aux].contadorPWM++; //incrementa o contador de quantas vezes o PWM já foi verificado

        if (pinoPWM[aux].EstadoPino == ON)
        {
          if (pinoPWM[aux].contadorPWM >= pinoPWM[aux].valorPWM) //se a quantidade de vezes que o pwm já foi verificado é maior ou igual ao pwm setado
              pinoPWM[aux].EstadoPino = OFF; //desligamos o pino
        }
        else
        {
          if (pinoPWM[aux].contadorPWM >= pwmMax) //se a quantidade de vezes for maior ou igual ao pwm setado
          {
                pinoPWM[aux].EstadoPino = ON; //ligamos o LED para o próximo ciclo
                pinoPWM[aux].contadorPWM = 0; //zeramos o contador do PWM
          }
         }
         SetarPino(&GPIO_PORTF_DATA_R, LED_VERMELHO, pinoPWM[aux].EstadoPino); //setamos o pino
    }
}

void dutyCicle( uint32_t index, uint32_t pwm)
{
  pinoPWM[index].valorPWM = pwm;
}

#endif
