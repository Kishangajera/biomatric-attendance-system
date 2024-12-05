// Include necessary libraries
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Adafruit_Fingerprint.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// Wi-Fi credentials (replace with your actual SSID and password)
const char* ssid = "OPPOA52";
const char* password = "12344321";

// Server URL (replace with your actual server URL)
const char* serverURL = "https://192.168.61.130/attendance.php";

// Initialize serial ports for ESP32
HardwareSerial mySerial(2); // UART2 (GPIO16 - RX2, GPIO17 - TX2)

// Initialize the fingerprint sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Initialize NTP client for time synchronization
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // Update every 60 seconds

// User database
struct User {
  uint8_t fingerID;
  String name;
};

User users[] = {
  {1, "thumb"},
  {2, "first"},
  {3, "second"},
  {4,"chiragbhai"},
  {5,"jay"}, 
  // Add more users as needed
};

const int userCount = sizeof(users) / sizeof(users[0]);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Initialize serial communication with the fingerprint sensor
  mySerial.begin(57600, SERIAL_8N1, 16, 17); // RX2, TX2 pins

  // Initialize Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  // Initialize NTP client
  timeClient.begin();

  // Initialize the fingerprint sensor
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor detected.");
  } else {
    Serial.println("Fingerprint sensor not found.");
    while (1) delay(1);
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains ");
  Serial.print(finger.templateCount);
  Serial.println(" templates.");
  Serial.println("Waiting for valid finger...");
}

void loop() {
  getFingerprintID();
  delay(50);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return p;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return p;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.println("Fingerprint not found.");
    return p;
  }

  // Match found
  Serial.print("Fingerprint matched with ID: ");
  Serial.println(finger.fingerID);

  // Compare with user database
  for (int i = 0; i < userCount; i++) {
    if (users[i].fingerID == finger.fingerID) {
      Serial.print("User found: ");
      Serial.println(users[i].name);

      // Get current timestamp
      String timeStamp = getTimeStamp();

      // Send data to the server
      sendDataToServer(users[i].fingerID, users[i].name, timeStamp);
      break;
    }
  }
  return p;
}

String getTimeStamp() {
  timeClient.update();
  // Get formatted time as HH:MM:SS
  String formattedTime = timeClient.getFormattedTime();

  // Get day, month, and year
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime(&rawtime);
  int year = ti->tm_year + 1900;
  int month = ti->tm_mon + 1;
  int day = ti->tm_mday;

  char dateBuffer[20];
  sprintf(dateBuffer, "%04d-%02d-%02d %s", year, month, day, formattedTime.c_str());
  return String(dateBuffer);
}

void sendDataToServer(uint8_t fingerID, String name, String timeStamp) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure(); // WARNING: For production, validate the server's SSL certificate

    HTTPClient https;
    https.begin(client, serverURL);
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare HTTP POST data
    String httpRequestData = "fingerID=" + String(fingerID)
                             + "&name=" + name
                             + "&timestamp=" + timeStamp;

    int httpResponseCode = https.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = https.getString();
      Serial.print("HTTPS Response code: ");
      Serial.println(httpResponseCode);
      Serial.println("Server response: " + response);

      // Parse JSON response
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        const char* status = doc["status"];
        const char* message = doc["message"];

        Serial.print("Status: ");
        Serial.println(status);
        Serial.print("Message: ");
        Serial.println(message);
      } else {
        Serial.println("Failed to parse JSON response.");
      }
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    https.end();
  } else {
    Serial.println("Wi-Fi disconnected.");
  }
}
