
# Projeto IHM

Firmware para ESP32-S3 que controla os equipamentos de uma sala de aula via touchscreen Nextion e protocolo MQTT — API em português, arquitetura modular por equipamento, roteamento automático de tópicos e suporte a AWS IoT Core.

[![Plataforma](https://img.shields.io/badge/plataforma-ESP32--S3-blue)](https://platformio.org) <br>
[![Framework](https://img.shields.io/badge/framework-Arduino-teal)](https://arduino.cc) <br>
[![Protocolo](https://img.shields.io/badge/protocolo-MQTT-purple)](https://mqtt.org)<br>
[![Licença](https://img.shields.io/badge/licença-MIT-green)](LICENSE)<br>
[![Versão](https://img.shields.io/badge/versão-2.1-orange)](platformio.ini)

---

## Equipamentos controlados

| Módulo | Arquivo | Descrição |
|---|---|---|
| Projetor | `Projetor.cpp` | Controle completo de projetor (power, freeze, mute, zoom, navegação, fontes...) |
| Televisão | `Televisao.cpp` | Controle de TV (power, HDMI, volume, mudo, direcionais) |
| Lâmpadas | `Lampadas.cpp` | Controle de lâmpadas independentes com estado ligado/desligado |
| Ar-condicionado | `ArCondicionado.cpp` | Controle de ares-condicionados — modo, temperatura e velocidade do ventilador |
| Tela de projeção | `Tela.cpp` | Motor de tela (subir, descer, parar) com seleção de qual tela |
| Sensor de temperatura | `Sensor.cpp` | Solicitação de leitura de temperatura ambiente |

---

## Estrutura de arquivos

```
Projeto_IHM/
│
├── include/
│   ├── Enum.h              ← Enums de tópicos e comandos de todos os equipamentos
│   ├── IHM.h               ← Declaração dos componentes Nextion e funções de evento
│   ├── secrets.h           ← Declarações extern das configurações
│   ├── MqttManager.h       ← API de comunicação MQTT
│   ├── WiFiManager.h       ← API de conexão Wi-Fi
│   ├── debugManager.h      ← API de diagnóstico serial
│   ├── Lampadas.h
│   ├── Projetor.h
│   ├── Televisao.h
│   ├── Tela.h
│   ├── ArCondicionado.h
│   └── Sensor.h
│
├── src/
│   ├── main.cpp            ← setup/loop, roteador de mensagens MQTT
│   ├── IHM.cpp             ← Instâncias Nextion, configuração de eventos e botões
│   ├── MqttManager.cpp
│   ├── WiFiManager.cpp
│   ├── debugManager.cpp
│   ├── Lampadas.cpp
│   ├── Projetor.cpp
│   ├── Televisao.cpp
│   ├── Tela.cpp
│   ├── ArCondicionado.cpp
│   ├── Sensor.cpp
│   └── secrets.cpp.example ← Modelo de configuração (não contém credenciais reais)
│
├── platformio.ini
└── README.md
```

---

## Interface Nextion — Páginas

| Página | ID | Equipamento |
|---|---|---|
| Menu principal | 1 | Navegação para todos os módulos |
| Televisão | 2 | Controle completo da TV |
| Lâmpadas | 3 | 4 interruptores independentes |
| Projetor | 4 | Controle principal do projetor |
| Projetor (configs adicionais) | 5 | Navegação, Enter, ESC |
| Ar-condicionado | 6 | Modo, temperatura e ventilador |
| Sensor de temperatura | 7 | Leitura de temperatura |
| Tela de projeção | 8 | Motor da tela (subir/descer/parar) |

### Pinos da serial Nextion (Serial2)

| Parâmetro | Valor |
|---|---|
| Baud rate | 9600 |
| Pino TX (ESP32 → Nextion) | GPIO 17 |
| Pino RX (ESP32 ← Nextion) | GPIO 18 |

---

## Fluxo de execução

```
ESP32 liga
    │
    ▼
setup()
    ├── configurarInicializacaoNextion()  → inicia Serial2 com o display
    ├── configurarEventosNextion()        → registra todos os botões e lambdas
    ├── configurarDebug()                 → abre Serial, define nível de log
    ├── conectarWiFi()                    → conecta ao roteador
    ├── configurarMQTT()                  → define broker, porta e modo TLS/AWS
    ├── registrarCallbackMensagem()       → registra tratarMensagemRecebida()
    └── conectarMQTT()                    → conecta ao broker e faz subscribe

loop() ← repete indefinidamente
    ├── garantirWiFiConectado()           → reconecta Wi-Fi se necessário
    ├── garantirMQTTConectado()           → reconecta MQTT se necessário
    ├── loopMQTT()                        → processa mensagens recebidas
    └── loopNextion()                     → detecta toques na tela

Usuário toca na tela
    └── lambda aoSoltar() dispara
            └── enviarComando___()
                    └── publicarMensagemNoTopico()
                            └── Broker distribui para servidor da sala

Servidor responde
    └── callbackInternoMQTT()
            └── tratarMensagemRecebida()
                    └── switch(tópico) → verificarMensagem___()
```

---

## Dependências

| Biblioteca | Versão | Uso |
|---|---|---|
| [PubSubClient](https://github.com/knolleary/pubsubclient) | ^2.8 | Protocolo MQTT |
| [ArduinoJson](https://arduinojson.org) | ^7.2.2 | Serialização/desserialização JSON |
| [NextionUI](https://github.com/professorThiago/NextionUI) | latest | Interface com display Nextion |

Declaradas em `platformio.ini` — instaladas automaticamente pelo PlatformIO.

---

## Licença

MIT — veja [LICENSE](LICENSE)

## Autores

- **Daniel Barbosa** — [@danielbarbosadev](https://github.com/danielbarbosadev)
- **Kevin Silva** — [@KevinNipinho](https://github.com/KevinNipinho)
- **Marcus Vinicius** — [@Marcus56480](https://github.com/Marcus56480)
- **Pedro Henrique** — [@PedroHs557](https://github.com/PedroHs557)


Desenvolvido no **SENAI Informática** como projeto de automação de sala de aula com ESP32 e MQTT.