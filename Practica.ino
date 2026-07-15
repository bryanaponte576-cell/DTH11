#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "DHT.h"



// --- Configuración de Firebase ---
// Ya corregido: va entre comillas y sin "https://" ni "/" al final
const char* FIREBASE_HOST = "esp32-sensor-90474-default-rtdb.firebaseio.com"; 

// --- Configuración del Sensor DHT11 ---
#define DHTPIN 4        // Pin D4 del ESP32 donde conectaste el pin 'S'
#define DHTTYPE DHT11   // Definimos el tipo de sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  
  // Inicializar sensor DHT
  dht.begin();

  // Conexión a la red Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n¡Conectado a la red Wi-Fi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // 1. Leer variables del sensor
    float humedad = dht.readHumidity();
    float temperatura = dht.readTemperature();

    // Comprobar si las lecturas fallaron
    if (isnan(humedad) || isnan(temperatura)) {
      Serial.println("Error al leer el sensor DHT11. Revisa las conexiones.");
      delay(2000);
      return;
    }

    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print("% | Temperatura: ");
    Serial.print(temperatura);
    Serial.println("°C");

    // 2. Configurar cliente seguro para HTTPS REST
    WiFiClientSecure *client = new WiFiClientSecure;
    if(client) {
      client->setInsecure(); // Permite conectar a Firebase en modo de prueba sin verificar certificado SSL

      HTTPClient https;
      
      // Construir la URL del nodo "/ambiente.json"
      String url = "https://" + String(FIREBASE_HOST) + "/ambiente.json";

      if (https.begin(*client, url)) {
        https.addHeader("Content-Type", "application/json");

        // 3. Crear el cuerpo de la petición en formato JSON estructurado
        String jsonPayload = "{\"temperatura\":" + String(temperatura, 1) + 
                             ",\"humedad\":" + String(humedad, 1) + 
                             ",\"timestamp\":{\".sv\":\"timestamp\"}}";

        // Enviar petición PATCH para actualizar dinámicamente los datos
        int httpResponseCode = https.PATCH(jsonPayload);

        if (httpResponseCode > 0) {
          Serial.print("Código HTTPS: ");
          Serial.println(httpResponseCode); // Retorna 200 si todo sale bien
          String response = https.getString();
          Serial.println("Respuesta Firebase: " + response);
        } else {
          Serial.print("Error al enviar petición: ");
          Serial.println(https.errorToString(httpResponseCode).c_str());
        }
        https.end();
      } else {
        Serial.println("No se pudo establecer la conexión con el servidor.");
      }
      delete client;
    }
  } else {
    Serial.println("Wi-Fi desconectado.");
  }

  // Enviar datos cada 5 segundos
  delay(5000); 
}