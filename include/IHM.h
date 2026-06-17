#ifndef IHM_H
#define IHM_H

#include <NextionUI.h>

extern const uint32_t NEXTION_BAUD_RATE;

extern const uint8_t NEXTION_PIN_TX;

extern const uint8_t NEXTION_PIN_RX;

extern NexDisplay display;

//* BOTÕES MENU PRINCIPAL
extern NexBotao btnMenuTv;
extern NexBotao btnMenuLampada;
extern NexBotao btnMenuArCondicionado;
extern NexBotao btnMenuSensor;
extern NexBotao btnMenuProjetor;
extern NexBotao btnMenuTela;

//* BOTÕES TELEVISÃO
extern NexBotao BtnInicialTelevisao;
extern NexBotaoDuplo PowerTV;
extern NexBotao HDMITV;
extern NexBotao volTV_UP;
extern NexBotao volTV_DOWN;
extern NexBotaoDuplo muteTV;
extern NexBotao TV_setaUP;
extern NexBotao TV_setaESQ;
extern NexBotao TV_setaDIR;
extern NexBotao TV_setaDOWN;
extern NexBotao TV_OK;
extern NexImagem popUpErroTv ;
extern NexTexto txtErroTv;
extern NexBotao btnOkTv;

//* BOTÕES LÂMPADA
extern NexBotao btnMenuInicialLampada;
extern NexBotaoDuplo interruptorLampada1;
extern NexBotaoDuplo interruptorLampada2;
extern NexBotaoDuplo interruptorLampada3;
extern NexBotaoDuplo interruptorLampada4;
extern NexImagem popUpErroLampada ;
extern NexTexto txtErroLampada ;
extern NexBotao btnErroLampada ;

//* BOTÕES PROJETOR
extern NexBotao BotaoInicialProjetor;
extern NexBotaoDuplo congelarProjetor;
extern NexBotaoDuplo mudoProjetor;
extern NexBotao PT_ZOOMOUT;
extern NexBotao PT_ZOOMIN;
extern NexBotao volProjetorAumentar;
extern NexBotao volProjetorDiminuir;
extern NexBotao configAdicionais;
extern NexBotaoDuplo projetor1;
extern NexBotaoDuplo projetor2;
extern NexBotaoDuplo ambosProjetores;
extern NexBotao powerProjetor;
extern NexImagem popUpErroProjetor ;
extern NexTexto txtErroProjetor ;
extern NexBotao btnOkProjetor ;

//* BOTÕES MORE CONFIGS PROJETOR
extern NexBotao botaoVoltarProjetor;
extern NexBotao setaEsquerda;
extern NexBotao setaDireita;
extern NexBotao setaBaixo;
extern NexBotao setaCima;
extern NexBotao botaoSelect;
extern NexBotao botaoEsc;
extern NexImagem popUpErroProjConfig ;
extern NexTexto txtErroProjConfig ;
extern NexBotao btnOkProjConfig ;

//* BOTÕES AR-CONDICIONADO
extern NexImagem PopUP;
extern NexBotao BotaoInicialAC;
extern NexBotaoDuplo AC_1;
extern NexBotaoDuplo AC_2;
extern NexBotaoDuplo AC_3;
extern NexBotaoDuplo AC_4;
extern NexBotaoDuplo AC_autoMode;
extern NexBotaoDuplo AC_coolMode;
extern NexBotaoDuplo AC_fanMode;
extern NexBotaoDuplo AC_fanMEDIUM;
extern NexBotaoDuplo AC_fanLOW;
extern NexBotaoDuplo AC_fanHIGH;
extern NexBotaoDuplo AC_fanQUIET;
extern NexTexto temp_AC;
extern NexBotao AC_temp_DOWN;
extern NexBotao AC_temp_UP;
extern NexBotaoDuplo AC_ALL;
extern NexBotao PowerAC;
extern NexImagem popUpErroAc;
extern NexTexto txtErroAc;
extern NexBotao btnOkAc;

//* BOTÕES TEMPERATURA
extern NexBotao BotaoInicialSensor;
extern NexTexto txtUmidade;
extern NexTexto txtTemperatura;
extern NexTexto txtSom;

//* BOTÕES TELA
extern NexBotao btnMenuInicialTela;
extern NexBotao DescerTela;
extern NexBotao SubirTela;
extern NexBotao TelaParar;
extern NexBotaoDuplo Tela1;
extern NexBotaoDuplo Tela2;
extern NexBotaoDuplo todasTelas;
extern NexImagem popUpErroTela ;
extern NexTexto txtErroTela;
extern NexBotao btnErroTela;

void configurarInicializacaoNextion();
void loopNextion();
void configurarEventosLampadas();
void configurarEventosProjetor();
void configurarEventosTela();
void configurarEventosTv();
void configurarEventosAc();
void configurarEventosSensor();
void configurarEventosNextion();
void processarLampada(NexBotaoDuplo& interruptor, const char* nomeLampada);

#endif