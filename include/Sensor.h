#ifndef SENSOR_H
#define SENSOR_H

static bool leituraComErro(float valor);
void verificarMensagemSensor(const String& mensagem);
void enviarComandoSensor();
void mostrarMensagemErro();

#endif