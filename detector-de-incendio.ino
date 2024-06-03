#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11
#define BUZZER_PIN 19
#define BUTTON_PIN 2
#define LED_PIN 18

DHT dht(DHT_PIN, DHT_TYPE);

const char* ssid = "Ta ligado";
const char* password = "depoiseufalo";

const char* twilioAccountSid = "ACdd78039141002f6a66e643170dcfa726";
const char* twilioAuthToken = "0396c46c84b0e51c4491b62a7aed95fd";
const char* twilioPhoneNumber = "+14238535114";
const char* destinationPhoneNumber = "+5585989321462";

bool alarmTriggered = false;
bool buttonPressed = false;

void sendSMS(const char* message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.twilio.com/2010-04-01/Accounts/" + String(twilioAccountSid) + "/Messages.json";
    String data = "To=" + String(destinationPhoneNumber) + "&From=" + String(twilioPhoneNumber) + "&Body=" + String(message);

    http.begin(url);
    http.setAuthorization(twilioAccountSid, twilioAuthToken);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(data);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Erro ao enviar SMS, código: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Erro na conexão WiFi");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Utilizando resistor pull-up interno
  pinMode(LED_PIN, OUTPUT);

  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");
}

void loop() {
  float temperatureC = dht.readTemperature();

  if (isnan(temperatureC)) {
    Serial.println("Falha na leitura do sensor DHT11!");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperatureC);
  Serial.println(" *C");

  if (temperatureC > 20.0 && !alarmTriggered) {  
    alarmTriggered = true;
    digitalWrite(LED_PIN, HIGH);  
    tone(BUZZER_PIN, 1000);       
    sendSMS("Alerta de Incêndio: Temperatura elevada detectada!");
  }

  if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {  
    buttonPressed = true;
  } 

  if (digitalRead(BUTTON_PIN) == HIGH && buttonPressed) {
    buttonPressed = false;
    alarmTriggered = false;
    digitalWrite(LED_PIN, LOW);  
    noTone(BUZZER_PIN);
    Serial.println("Alarme desativado, voltando ao monitoramento normal.");
  }

  delay(1000); // Ajustado para 1 segundo para permitir leituras mais frequentes
}
