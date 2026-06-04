#ifndef IHM_H
#define IHM_H

#include <NextionUI.h>

extern const uint32_t NEXTION_BAUD_RATE;

extern const uint8_t NEXTION_PIN_TX;

extern const uint8_t NEXTION_PIN_RX;

extern NexDisplay display;

extern NexBotao btnMenuTv;
extern NexBotao btnMenuLampada;
extern NexBotao btnMenuArCondicionado;
extern NexBotao btnMenuSensor;
extern NexBotao btnMenuProjetor;
extern NexBotao btnMenuTela;

extern NexBotao BtnInicialTelevisao;
extern NexBotaoDuplo PowerTV;
extern NexBotao HDMITV;
extern NexBotao volTV_UP;
extern NexBarraProgresso volBarTV;
extern NexBotao volTV_DOWN;
extern NexBotaoDuplo muteTV;

extern NexBotao btnMenuInicialLampada;
extern NexBotaoDuplo interruptorLampada1;
extern NexBotaoDuplo interruptorLampada2;
extern NexBotaoDuplo interruptorLampada3;
extern NexBotaoDuplo interruptorLampada4;

extern NexBotao BotaoInicialProjetor;
extern NexBotaoDuplo powerProjetor;
extern NexBotaoDuplo congelarProjetor;
extern NexBotaoDuplo mudoProjetor;
extern NexBotao PT_ZOOMOUT;
extern NexBotao PT_ZOOMIN;
extern NexBotao volProjetorAumentar;
extern NexBotao volProjetorDiminuir;
extern NexBotao configAdicionais;
extern NexBotaoDuplo projetor1;
extern NexBotaoDuplo projetor2;

extern NexBotao BotaoVoltarProjetor;
extern NexBotao setaEsquerda;
extern NexBotao setaDireita;
extern NexBotao setaBaixo;
extern NexBotao setaCima;
extern NexBotao botaoSelect;
extern NexBotao botaoEsc;

extern NexImagem PopUP;
extern NexBotao BotaoInicial;
extern NexBotaoDuplo PowerAC;
extern NexBotao AC_1;
extern NexBotao AC_2;
extern NexBotao AC_3;
extern NexBotao AC_4;
extern NexBotaoDuplo AC_autoMode;
extern NexBotaoDuplo AC_coolMode;
extern NexBotaoDuplo AC_fanMode;
extern NexBotaoDuplo AC_fanMEDIUM;
extern NexBotaoDuplo AC_fanLOW;
extern NexBotaoDuplo AC_fanHIGH;
extern NexBotaoDuplo AC_fanQUIET;
extern NexTexto temp_AC;
extern NexBotao AC_temp_UP;
extern NexBotao AC_temp_DOWN;

extern NexBotao BotaoInicialSensor;

NexBotao btnMenuInicialTela;
NexBotao DescerTela;
NexBotao SubirTela;
NexBotao TelaParar;
NexBotaoDuplo Tela1;
NexBotaoDuplo Tela2;
NexBotaoDuplo todasTelas;

void configurarInicializacaoNextion();
void loopNextion();
void configurarEventosNextion();
void processarLampada(NexBotaoDuplo& interruptor, const char* nomeLampada);

#endif