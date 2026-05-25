#ifndef PROJETOR_H
#define PROJETOR_H

#include <ArduinoJson.h>

extern const char *comandoProjetor;
extern const char PINO_BOTAO_BOOT;

void verificarHandshakeProjetor(JsonDocument& doc);
void configurarPinoBoot();
void enviarComandoProjetor(const char* comandoProjetor);
void processarComandoProjetor();

#endif