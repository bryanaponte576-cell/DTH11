# Sistema de Monitoreo de Temperatura y Humedad con ESP32 y Firebase

Este repositorio contiene la implementación de un sistema IoT basado en el microcontrolador **ESP32** y el sensor **DHT11**, el cual envía lecturas dinámicas de variables ambientales a **Firebase Realtime Database** mediante peticiones HTTP REST seguras (`PATCH`).

## 🛠️ Materiales Utilizados
* Placa de desarrollo **ESP32 Dev Module**.
* Sensor de temperatura y humedad **DHT11**.
* Cables de conexión (jumpers) y protoboard.
* Cable USB para transmisión de datos y alimentación.

## 🔌 Conexión del Circuito

| Sensor DHT11 | ESP32 Pin |
| :--- | :--- |
| **VCC** (`+`) | 3.3V |
| **GND** (`-`) | GND |
| **DATA** (`Out`) | GPIO 4 |

## 🚀 Funcionalidades
1. **Conexión Wi-Fi:** Configuración en modo *Station* (STA) para conectarse a una red local.
2. **Lectura de Sensores:** Mapeo periódico de temperatura (°C) y humedad (%) desde el sensor DHT11.
3. **Persistencia en la Nube:** Envío seguro del paquete JSON a Firebase Realtime Database mediante protocolo HTTPS REST (`PATCH`).

*Desarrollado como parte de las prácticas técnicas de IoT y Redes.*
