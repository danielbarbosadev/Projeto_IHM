#ifndef MODULOPROJETOR_H
#define MODULOPROJETOR_H

enum modulos
{
  PROJETOR,
  TELA,
  TELEVISAO,
  LAMPADAS,
  AR_CONDICIONADO,
  TOPICO_INVALIDO
};

const char PINO_BOTAO_BOOT = 0;

void configurarPinoBoot();
void enviarComandoProjetor();
void definirComandoProjetor();

#endif