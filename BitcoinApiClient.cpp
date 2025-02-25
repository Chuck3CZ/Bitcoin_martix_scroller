#pragma once
#include "BitcoinApiClient.h"
#include "libs/ArduinoJson/ArduinoJson.h"

BitcoinApiClient::BitcoinApiClient() {
  // Constructor
}

void BitcoinApiClient::updateBitcoinData(String currencyCode) {
  if (currencyCode == "" || currencyCode == "NONE") {
    bpiData.code = "";
    bpiData.rate = "";
    bpiData.description = "";
    bpiData.rate_float = 0;
    return; // nothing to do here
  }

  HTTPClient http;

  String apiGetData = "https://api.coinbase.com/v2/prices/BTC-USD/spot";
  WiFiClientSecure client;  // SSL klient pro zabezpečené připojení

  Serial.println("Getting Bitcoin Data");
  Serial.println(apiGetData);
  client.setInsecure();
  http.begin(apiGetData);
  int httpCode = http.GET();

  String result = "";

  if (httpCode > 0) {  // Kontrola spojení
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      int len = http.getSize();
      char buff[128] = { 0 };
      WiFiClient * stream = http.getStreamPtr();

      Serial.println("Start reading...");
      while (http.connected() && (len > 0 || len == -1)) {
        size_t size = stream->available();
        if (size) {
          int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
          for (int i = 0; i < c; i++) {
            result += buff[i];
          }
          if (len > 0) len -= c;
        }
        delay(1);
      }
    }
    http.end();
  } else {
    Serial.println("Connection for Bitcoin data failed: " + String(apiGetData));
    return;
  }

  result.remove(0, result.indexOf("{"));
  result.remove(result.lastIndexOf("}") + 1);

  Serial.println("Results:");
  Serial.println(result);
  Serial.println("End");

  // Použití StaticJsonBuffer pro ArduinoJson 5.x
  StaticJsonBuffer<1024> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(result);

  if (!root.success()) {
    Serial.println(F("Bitcoin Data Parsing failed!"));
    return;
  }

  // Navigace v JSON struktuře podle API odpovědi
  JsonObject& resultObj = root["data"];
  // Přímo získáme "amount" jako String
  String amountStr = resultObj["amount"].as<String>();

  // Pokud chceš použít cenu jako float, převeď string na float
  float price = amountStr.toFloat();

  // Naplnění struktury bpiData
  bpiData.code = "USD";
  bpiData.rate = amountStr;  // Zde už máme přímo amount jako string
  bpiData.description = "United States Dollar";
  bpiData.rate_float = price;

  // Výpis dat pro ladění
  Serial.println("code: " + bpiData.code);
  Serial.println("rate: " + bpiData.rate);
  Serial.println("description: " + bpiData.description);
  Serial.println("rate_float: " + String(bpiData.rate_float));
}

String BitcoinApiClient::getRate() {
  return bpiData.rate;
}

String BitcoinApiClient::getCode() {
  return bpiData.code;
}

String BitcoinApiClient::getDescription() {
  return bpiData.description;
}

float BitcoinApiClient::getRateFloat() {
  return bpiData.rate_float;
}
