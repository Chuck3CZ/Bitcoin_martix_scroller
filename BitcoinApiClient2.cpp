#pragma once
#include "BitcoinApiClient.h"
#include "ArduinoJson.h"

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
  WiFiClient client;

  Serial.println("Getting Bitcoin Data");
  Serial.println(apiGetData);

  http.begin(client, apiGetData);
  int httpCode = http.GET();

  String result = "";

  if (httpCode > 0) {  // Kontrola spojení
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      result = http.getString();
    }
    http.end();
  } else {
    Serial.println("Connection for Bitcoin data failed: " + String(apiGetData));
    return;
  }

  Serial.println("Results:");
  Serial.println(result);
  Serial.println("End");

  // Použití DynamicJsonDocument pro ArduinoJson 6.x
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, result);

  if (error) {
    Serial.println(F("Bitcoin Data Parsing failed!"));
    return;
  }

  // Navigace v JSON struktuře podle API odpovědi
  JsonObject data = doc["data"];

  // Naplnění struktury bpiData
  bpiData.code = "USD";
  bpiData.rate = data["amount"].as<String>();
  bpiData.description = "United States Dollar";
  bpiData.rate_float = data["amount"].as<float>();

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
