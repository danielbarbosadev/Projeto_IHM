#ifndef PROJETOR_H
#define PROJETOR_H

#include <ArduinoJson.h>
#include <Arduino.h>

extern const char *comandoProjetor;

void verificarHandshakeProjetor(JsonDocument& doc);
void enviarComandoProjetor(uint8_t comandoProjetor);
void processarComandoProjetor(uint32_t estadoPowerProjetor);

#endif