#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>


const char* ssid = "INFINIX SMART 8";
const char* password = "95120447";

const char* mqtt_server = "192.168.18.183";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);


#define DHTPIN 23
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Intervalle de lecture
unsigned long lastMsg = 0;
const long interval = 3000;

#define LED_VERTE 5
#define LED_ROUGE 18
#define LED_BLANCHE 19

// Met à jour l'état des LED selon connexion
void updateStatusLEDs() {
  if (WiFi.status() == WL_CONNECTED && client.connected()) {
    digitalWrite(LED_VERTE, HIGH);
    digitalWrite(LED_ROUGE, LOW);
  } else {
    digitalWrite(LED_VERTE, LOW);
    digitalWrite(LED_ROUGE, HIGH);
  }
}


void setup_wifi() {
  Serial.print("Connexion WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    updateStatusLEDs();
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connecté !");
  Serial.print("IP ESP32 : ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion au broker...");
    if (client.connect("ESP32_DHT11")) {
      Serial.println("OK !");
    } else {
      Serial.print("Échec MQTT, rc=");
      Serial.println(client.state());
      Serial.println("Nouvelle tentative dans 2s...");
      delay(2000);
    }
    updateStatusLEDs();
  }
}


void setup() {
  Serial.begin(115200);

  // LEDs
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_BLANCHE, OUTPUT);

  digitalWrite(LED_VERTE, LOW);
  digitalWrite(LED_ROUGE, HIGH);  // Rouge allumée au démarrage
  digitalWrite(LED_BLANCHE, LOW);

  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  updateStatusLEDs();
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
  
  updateStatusLEDs();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    // Clignotement LED blanche (envoi)
    digitalWrite(LED_BLANCHE, HIGH);

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Erreur lecture DHT11 !");
      digitalWrite(LED_BLANCHE, LOW);
      return;
    }

    Serial.print("Temp : ");
    Serial.print(t);
    Serial.print(" °C | Humidité : ");
    Serial.print(h);
    Serial.println(" %");

    char tempString[8];
    dtostrf(t, 1, 2, tempString);

    char humString[8];
    dtostrf(h, 1, 2, humString);

    client.publish("esp32/dht11/temperature", tempString);
    client.publish("esp32/dht11/humidity", humString);

    Serial.println("Données envoyées !");

    delay(150);                    // LED blanche visible
    digitalWrite(LED_BLANCHE, LOW);
  }
}
