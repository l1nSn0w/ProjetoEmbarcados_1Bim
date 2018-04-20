#ifndef _ControlePWM_
#define _ControlePWM_

#define ON 1
#define OFF 0

typedef struct pinosPWM
{
  uint32_t pino;
  uint32_t valorPWM;
  uint32_t EstadoPino;
  uint32_t contadorPWM;
  uint32_t port;
} sPWM;

sPWM pinoPWM;

/*uint32_t microsAnterior;
uint32_t microsAtual;
int32_t intervaloMicros = 1;
uint32_t index=0;*/
uint32_t pwmMax = 100;

// Configura os atributos do PWM
void PWM(uint32_t port, uint8_t pino)
{
    pinoPWM.pino = pino;
    pinoPWM.port = port;
    pinoPWM.valorPWM = 50;
    pinoPWM.EstadoPino = ON;
    pinoPWM.contadorPWM = 0;
}

void handlePWM()
{
        pinoPWM.contadorPWM++; //incrementa o contador de quantas vezes o PWM já foi verificado

          if (pinoPWM.EstadoPino == ON)
          {
            if (pinoPWM.contadorPWM >= pinoPWM.valorPWM) //se a quantidade de vezes que o pwm já foi verificado é maior ou igual ao pwm setado
                pinoPWM.EstadoPino = OFF; //desligamos o pino
          }
          else
          {
            if (pinoPWM.contadorPWM >= pwmMax) //se a quantidade de vezes for maior ou igual ao pwm setado
            {
                pinoPWM.EstadoPino = ON; //ligamos o LED para o próximo ciclo
                pinoPWM.contadorPWM = 0; //zeramos o contador do PWM
            }
          }
          SetarPino(pinoPWM.port, pinoPWM.pino, pinoPWM.EstadoPino); //setamos o pino
 }

void dutyCicle( uint32_t pwm)
{
  pinoPWM.valorPWM = pwm;
  handlePWM();
}

#endif
