#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include <ArduinoJson.h>

void verificarHandshakeTemperatura(JsonDocument &doc);
void enviarComandoTemperatura();

#endif