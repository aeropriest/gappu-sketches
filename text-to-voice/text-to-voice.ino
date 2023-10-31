#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Audio.h>


#define LED_ORANGE2 0
#define LED_ORANGE1 2
#define LED_GREEN 15

#define BUT_1 13
#define BUT_2 9
#define BUT_3 10
#define BUT_4 11

#define I2S_DOUT      14  // DIN connection
#define I2S_BCLK      27  // Bit clock
#define I2S_LRC       26  // Left Right Clock


const char* ssid = "JaisNet2";
const char* password = "heyheygaga";

ESP32_I2S_Audio audio;

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_ORANGE1, OUTPUT);
  pinMode(LED_ORANGE2, OUTPUT);
  pinMode(BUT_1, INPUT);
  // pinMode(BUT_2, INPUT);
  // pinMode(BUT_3, INPUT);
  // pinMode(BUT_3, INPUT);
  // pinMode(BUT_4, INPUT);

  digitalWrite(LED_GREEN, LOW);
  // digitalWrite(LED_ORANGE1, LOW);
  // digitalWrite(LED_ORANGE2, LOW);
  Serial.begin(115200);

  // / Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(2); // 0...21
  // https://github.com/aeropriest/gappu-nextjs/blob/main/data/world-of-wars.mp3
  // audio.connecttohost("https://coolism-web.cdn.byteark.com/;stream/1");
  // audio.connecttospeech("A quick brown fox jumped over the lazy dog", "en");
        // Define the request payload
      const char* url = "https://gappu-nextjs.vercel.app/api/text-to-speech";
      const char* contentType = "application/json";
      const char* payload = "{\"modelUrl\":\"https://api-inference.huggingface.co/models/facebook/fastspeech2-en-ljspeech\",\"input\":\"a quick brown foxed jumped over the lazy dog and ran very fast to hide behind the tree\"}";
      // / Create an HTTP client object
      HTTPClient http;

      // Specify the request details
      http.begin(url);
      http.addHeader("Content-Type", contentType);

      // Send the POST request
      int httpResponseCode = http.POST(payload);

      Serial.print(httpResponseCode);
      Serial.println();
      // Check for a successful response
      if (httpResponseCode > 0) {
        // Audio.begin(88200, 100); 
        Serial.println("Everything looks good!!!!");
        String response = http.getString();
        Serial.println('Response length is');
        Serial.println(response.length());
        // int volume = 1024;
        const int S = response.length(); // Number of samples to read in block
        Serial.println(response);

        // Audio.prepare((short *)response.c_str(), S, volume);
        // Audio.write((short *)response.c_str(), S);
        Serial.println("playback the string");
        Serial.println(S);
        Serial.println(response);
        audio.sendBytes((uint8_t*)response.c_str(), S);
      } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpResponseCode);
      }
      // End the HTTP client
      http.end();
}

void loop() {
  audio.loop();

  // if (digitalRead(BUT_1) == LOW) {
  //   Serial.println("BUT_1 is high");
  //   digitalWrite(LED_ORANGE1, HIGH);
  //   if( WiFi.status() == WL_CONNECTED ){

      // // Define the request payload
      // const char* url = "https://gappu-nextjs.vercel.app/api/text-to-speech";
      // const char* contentType = "application/json";
      // const char* payload = "{\"modelUrl\":\"https://api-inference.huggingface.co/models/facebook/fastspeech2-en-ljspeech\",\"input\":\"a quick brown foxed jumped over the lazy dog and ran very fast to hide behind the tree\",\"url\":\"https://github.com/aeropriest/gappu-nextjs/blob/main/data/world-of-wars.mp3\"}";
      // // / Create an HTTP client object
      // HTTPClient http;

      // // Specify the request details
      // http.begin(url);
      // http.addHeader("Content-Type", contentType);

      // // Send the POST request
      // int httpResponseCode = http.POST(payload);

      // Serial.print(httpResponseCode);
      // Serial.println();
      // // Check for a successful response
      // if (httpResponseCode > 0) {
      //   // Audio.begin(88200, 100); 
      //   Serial.println("Everything looks good!!!!");
      //   // String response = http.getString();
      //   // Serial.println(response.length());
      //   // int volume = 1024;
      //   // const int S = response.length(); // Number of samples to read in block

      //   // Audio.prepare((short *)response.c_str(), S, volume);
      //   // Audio.write((short *)response.c_str(), S);
      // } else {
      //   Serial.print("Error on HTTP request: ");
      //   Serial.println(httpResponseCode);
      // }
      // // End the HTTP client
      // http.end();

  //   }
  // }

  // if (digitalRead(BUT_1) == HIGH) {
  //   digitalWrite(LED_ORANGE1, LOW);
  //   Serial.println("BUT_1 is low");
  // }

  //   if (digitalRead(BUT_2) == HIGH) {
  //   Serial.println("BUT_2 is high");
  //   digitalWrite(LED_GREEN, HIGH);
  // }
  // if (digitalRead(BUT_2) == LOW) {
  //   digitalWrite(LED_GREEN, LOW);
  //   Serial.println("BUT_2 is low");
  // }

  // // if (digitalRead(BUT_3) == HIGH) {
  // //   Serial.println("BUT_3 is high");
  // //   digitalWrite(LED_ORANGE1, HIGH);
  // // }
  // // if (digitalRead(BUT_3) == LOW) {
  // //   digitalWrite(LED_ORANGE2, LOW);
  // //   Serial.println("BUT_3 is low");
  // // }


  // // if (digitalRead(BUT_4) == HIGH) {
  // //   Serial.println("BUT_4 is high");
  // //   digitalWrite(LED_GREEN, HIGH);
  // // }
  // // if (digitalRead(BUT_4) == LOW) {
  // //   digitalWrite(LED_GREEN, LOW);
  // //   Serial.println("BUT_4 is low");
  // // }

}
