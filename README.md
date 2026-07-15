# Conexión de ESP32 a Firebase mediante HTTPS REST

Este proyecto consiste en la configuración de una base de datos en tiempo real en Firebase y la conexión del microcontrolador ESP32 para realizar la escritura dinámica de variables del sensor DHT11 (Temperatura y Humedad) mediante peticiones HTTPS REST seguras.

## 🛠️ Materiales Utilizados
* Placa de desarrollo ESP32 (NodeMCU).
* Sensor de temperatura y humedad DHT11.
* Protoboard y jumpers de conexión.
* Entorno de desarrollo Arduino IDE.

## 🔌 Conexiones
* **DHT11 VCC** -> ESP32 3V3
* **DHT11 GND** -> ESP32 GND
* **DHT11 Signal** -> ESP32 GPIO 4 (D4)

## 📡 Protocolo de Comunicación
La comunicación con Firebase Realtime Database se realiza de manera segura mediante **HTTPS (puerto 443)** utilizando el método **PATCH** para actualizar los campos `temperatura`, `humedad` y `timestamp` de forma dinámica sin sobrescribir otros nodos de la base de datos.
