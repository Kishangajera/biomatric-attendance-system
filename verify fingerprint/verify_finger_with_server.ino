// Include necessary libraries
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal_I2C.h>

// Wi-Fi credentials (replace with your actual SSID and password)
const char* ssid = "TP-Link_C090";
const char* password = "30888630";

// Server URL (replace with your actual server URL)
const char* serverURL = "https://192.168.201.236/attendanc.php";

// Initialize serial ports for ESP32
HardwareSerial mySerial(2); // UART2 (GPIO16 - RX2, GPIO17 - TX2)

// Initialize the fingerprint sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Initialize I2C LCD (adjust the address and dimensions as needed)
LiquidCrystal_I2C lcd(0x27, 16, 2); // For a 16x2 LCD at address 0x27

// User database
struct User {
  uint8_t fingerID;
  String name;
};

User users[] = {
  {1, "thumb"},
  {2, "first"},
  {3, "second"},
  {4, "chiragbhai"},
  {5, "jay"},
  // Add more users as needed
};

const int userCount = sizeof(users) / sizeof(users[0]);

void setup() {
  Serial.begin(115200);
  delay(100);

  // Initialize serial communication with the fingerprint sensor
  mySerial.begin(57600, SERIAL_8N1, 16, 17); // RX2, TX2 pins

  // Initialize the LCD
  lcd.init();      
  lcd.backlight(); 
  lcd.clear();

  // Display Wi-Fi connecting status
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  // Initialize Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // You could also add a small animation or flicker on LCD if desired
  }
  Serial.println("\nConnected to Wi-Fi");

  // Update LCD once connected
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
  delay(1000);

  // Initialize the fingerprint sensor
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Checking Sensor");

  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor detected.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor Found!");
  } else {
    Serial.println("Fingerprint sensor not found.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor Not Found");
    while (1) delay(1); // Halt here if no sensor is found
  }

  delay(1000);

  finger.getTemplateCount();
  Serial.print("Sensor contains ");
  Serial.print(finger.templateCount);
  Serial.println(" templates.");
  Serial.println("Waiting for valid finger...");

  // Ready state
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready for scan");
}

void loop() {
  getFingerprintID();
  delay(50);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();

  if (p == FINGERPRINT_NOFINGER) {
    // No finger - just keep showing "Ready for scan"
    return p;
  }

  if (p != FINGERPRINT_OK) {
    Serial.println("Image capture failed.");
    return p;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    Serial.println("Image conversion failed.");
    return p;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    Serial.println("Fingerprint not found.");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Not found");
    delay(1000);
    lcd.clear();
    lcd.print("Ready for scan");
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

      // Display ID and name on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ID:");
      lcd.print(users[i].fingerID);
      lcd.setCursor(0, 1);
      lcd.print(users[i].name);

      // Add a 2-second delay here
      delay(1000);


      // Send data to the server
      sendDataToServer(users[i].fingerID, users[i].name);
      break;
    }
  }
  return p;
}

void sendDataToServer(uint8_t fingerID, String name) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure(); // WARNING: For production, use a proper certificate

    HTTPClient https;
    https.begin(client, serverURL);
    https.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare HTTP POST data
    String httpRequestData = "fingerID=" + String(fingerID)
                             + "&name=" + name;

    int httpResponseCode = https.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = https.getString();
      Serial.print("HTTPS Response code: ");
      Serial.println(httpResponseCode);
      Serial.println("Server response: " + response);

      // Display success on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Data Sent!");
      delay(1000);
      lcd.clear();
      lcd.print("Ready for scan");
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);

      // Display error on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Send Error");
      delay(1000);
      lcd.clear();
      lcd.print("Ready for scan");
    }
    https.end();
  } else {
    Serial.println("Wi-Fi disconnected.");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Lost");
    delay(1000);
    lcd.clear();
    lcd.print("Ready for scan");
  }
}
