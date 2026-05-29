#ifndef LAMPADAS_H
#define LAMPADAS_H

#include <ArduinoJson.h>

void verificarHandshakeLampadas(JsonDocument &doc);
void processarComandoLampada(uint32_t estadoPowerLampada);
void enviarComandoLampada(int8_t comandoLampada);

#endif