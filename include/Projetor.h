#ifndef PROJETOR_H
#define PROJETOR_H

#include <ArduinoJson.h>
#include <Arduino.h>

extern const char *comandoProjetor;
extern const char PINO_BOTAO_BOOT;

void verificarHandshakeProjetor(JsonDocument& doc);
void enviarComandoProjetor(const char* comandoProjetor);
void processarComandoProjetor(uint32_t estadoPowerProjetor);

#endif