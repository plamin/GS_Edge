#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* apiKey = "52H8YHQMCVCJAWTJ";
const char* server = "http://api.thingspeak.com";

#define DHTPIN 17
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define BUZZER_PIN 2
#define LED_PIN 4

int pot = 32;

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  dht.begin();

  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
}

void loop() {

  int pote = analogRead(pot);
  int tempoBatimento = map(pote, 0, 4095, 400, 1200); 
  int bpm = tempoBatimento > 0 ? 60000 / tempoBatimento : 0;

  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);

  delay(tempoBatimento);

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  if (temperatura < 18) {
    Serial.println("ALERTA: Temperatura MUITO BAIXA!");
  }
  if (temperatura > 32) {
    Serial.println("ALERTA: Temperatura MUITO ALTA!");
  }

  int estresseBPM  = map(bpm, 60, 160, 0, 60);
  int estresseTemp = map(temperatura, 20, 35, 0, 40);

  int indiceEstresse = estresseBPM + estresseTemp;
  indiceEstresse = constrain(indiceEstresse, 0, 100);


  if (indiceEstresse > 50) {
    Serial.println("ALERTA: ESTRESSE ELEVADO");

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  }

  Serial.printf("BPM: %d\n", bpm);
  Serial.printf("Temp: %.1f°C\n", temperatura);
  Serial.printf("Umidade: %.1f%%\n", umidade);
  Serial.printf("Índice de Estresse: %d/100\n", indiceEstresse);

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    String url =
      String(server) + "/update?api_key=" + apiKey + "&field1=" + String(bpm) + "&field2=" + String(temperatura) + "&field3=" + String(umidade) + "&field4=" + String(indiceEstresse);

    http.begin(url);

    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Dados enviados ao ThingSpeak.");
      Serial.print("Código HTTP: ");
      Serial.println(httpCode);
    } else {
      Serial.print("Erro ao enviar dados. Código: ");
      Serial.println(httpCode);
    }

    http.end();
  }

  delay(500);
}
