#ifndef LAMPADAS_H
#define LAMPADAS_H



void verificarHandshakeLampadas(const String& mensagem);
void processarComandoLampada(uint32_t estadoPowerLampada);
void enviarComandoLampada(int8_t comandoLampada);

#endif