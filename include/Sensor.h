#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
void verificarMensagemSensor(const String& mensagem);
void enviarComandoSensor();
void mostrarDadosSensor(const char* mensagemErro, const char* umidade, const char* som);

#endif