/**
 * @file esp32_mqtt_fota.cpp
 * @brief ESP32 MQTT Telemetry & Dual-Bank FOTA fail-safe architecture
 * @author DeviceLab Embedded Team (https://devicelab.vn)
 * @reference https://devicelab.vn/phat-trien-firmware/
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <Update.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "mqtt.devicelab.vn";

WiFiClient espClient;
PubSubClient client(espClient);

// Perform Fail-Safe Dual-Bank OTA Update
bool performOTA(const char* firmware_url) {
    HTTPClient http;
    http.begin(firmware_url);
    int httpCode = http.GET();
    if (httpCode != HTTP_CODE_OK) {
        http.end();
        return false;
    }

    int contentLength = http.getSize();
    bool canBegin = Update.begin(contentLength);
    if (!canBegin) {
        http.end();
        return false;
    }

    WiFiClient* stream = http.getStreamPtr();
    size_t written = Update.writeStream(*stream);
    if (written != contentLength) {
        Update.abort();
        http.end();
        return false;
    }

    if (!Update.end()) {
        http.end();
        return false;
    }

    http.end();
    if (Update.isFinished()) {
        ESP.restart();
        return true;
    }
    return false;
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    client.setServer(mqtt_server, 1883);
}

void loop() {
    if (!client.connected()) {
        client.connect("DeviceLab_Gateway_Node");
    }
    client.loop();
    // Publish telemetry to SCADA/Dashboard every 5s
    client.publish("factory/telemetry", "{\"device\":\"DeviceLab-GW\",\"status\":\"OK\"}");
    delay(5000);
}
