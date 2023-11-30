#include <WiFi.h>
#include <PubSubClient.h>

const char * ssid = "ASUS_GRAM";
const char * password = "GramLab0rat0ri0";


const char * broker_ip = "192.168.77.106";
const uint16_t mqtt_port = 1883;

WiFiClient esp_client;

PubSubClient mqtt_client(esp_client);

void setup_wifi();
void init_mqtt();
void connect_mqtt();
void handdle_qmtt();
void mqtt_publish(String topic, char * payload);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  setup_wifi();

  init_mqtt();

  connect_mqtt();
  

  Serial.println("\n Ok");



}

void loop() {
  // put your main code here, to run repeatedly:

}

void mqtt_publish(String topic, char * payload){


  mqtt_client.publish(topic.c_str(), payload);



}

void init_mqtt(){

  Serial.print("Connect to MQTT -");
  Serial.print(broker_ip);
  Serial.print("-");
  Serial.println(mqtt_port);

  mqtt_client.setServer(broker_ip, mqtt_port);
}

void connect_mqtt(){

  while(!mqtt_client.connected()){

    Serial.print("Connecting to MQTT");

    if (mqtt_client.connect("ESP32Client"))
           Serial.println("connected");
       
    else{   
           Serial.print("failed with state ");
           Serial.print(mqtt_client.state());
           delay(500);
       }
  }


}

void handdle_qmtt(){

  if(!mqtt_client.connected()){

    connect_mqtt();

  }

  mqtt_client.loop();

}

void setup_wifi(){

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi.");
  while (WiFi.status() != WL_CONNECTED)
       {  delay(500);
          Serial.print(".") ;
       }

  Serial.println("Connected to WiFi");

}