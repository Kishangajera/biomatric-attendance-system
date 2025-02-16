#include <Adafruit_Fingerprint.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin configuration for fingerprint sensor
#define RX_PIN 16
#define TX_PIN 17

// Wi-Fi credentials
const char* ssid = "TP-Link_C090";
const char* password = "30888630";

// Server URL for storing fingerprint data
const char* serverUrl = "http://192.168.201.236/update_fingerprint.php";

// Hardware Serial for fingerprint sensor (using UART2)
HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// LCD configuration (16x2, I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);
    mySerial.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN); // Initialize fingerprint sensor

    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");

    delay(100);

    // Initialize fingerprint sensor
    finger.begin(57600);
    delay(5);

    if (finger.verifyPassword()) {
        Serial.println("Fingerprint sensor detected!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sensor Found!");
    } else {
        Serial.println("Fingerprint sensor NOT detected!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Sensor!");
        while (1) { delay(1); }  // Halt execution
    }

    // Connect to Wi-Fi
    connectToWiFi();
}

void loop() {
    if (Serial.available() > 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter ID:");

        int id = Serial.parseInt();
        if (id < 1 || id > 1000) {
            Serial.println("Invalid ID. Enter 1-1000.");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Invalid ID!");
            return;
        }

        enrollFingerprint(id);
    }
}

// Function to enroll a fingerprint
void enrollFingerprint(int id) {
    Serial.print("Enrolling ID #"); Serial.println(id);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enrolling ID:");
    lcd.setCursor(0, 1);
    lcd.print(id);

    delay(1000);

    int p = -1;
    Serial.println("Place your finger...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Place finger");

    while (p != FINGERPRINT_OK) {
        p = finger.getImage();
        if (p == FINGERPRINT_NOFINGER) continue;
        if (p == FINGERPRINT_PACKETRECIEVEERR) showError("Comm Error");
        if (p == FINGERPRINT_IMAGEFAIL) showError("Imaging Error");
    }

    p = finger.image2Tz(1);
    if (p != FINGERPRINT_OK) return showError("Convert Err");

    Serial.println("Remove finger");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Remove finger");
    delay(2000);

    while (finger.getImage() != FINGERPRINT_NOFINGER) delay(100);

    Serial.println("Place the same finger again...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Again Finger");

    p = -1;
    while (p != FINGERPRINT_OK) {
        p = finger.getImage();
        if (p == FINGERPRINT_NOFINGER) continue;
        if (p == FINGERPRINT_PACKETRECIEVEERR) showError("Comm Error");
        if (p == FINGERPRINT_IMAGEFAIL) showError("Imaging Error");
    }

    p = finger.image2Tz(2);
    if (p != FINGERPRINT_OK) return showError("Convert Err");

    Serial.println("Matching fingerprints...");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Matching Prints");

    p = finger.createModel();
    if (p == FINGERPRINT_OK) {
        Serial.println("Prints Matched!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Matched!");
    } else {
        return showError("No Match");
    }

    Serial.print("Storing model for ID "); Serial.println(id);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Storing...");

    p = finger.storeModel(id);
    if (p == FINGERPRINT_OK) {
        Serial.println("Enrollment Success!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enroll Success!");

        // Send data to server
        sendFingerprintDataToServer(id);
    } else {
        showError("Store Failed");
    }
}

// Function to connect to Wi-Fi
void connectToWiFi() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Connecting WiFi");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP().toString());
}

// Function to send fingerprint ID to the server
void sendFingerprintDataToServer(int avd_id) {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        Serial.println("Sending data to server...");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sending Data...");

        http.begin(client, serverUrl);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        String postData = "avd_id=" + String(avd_id);

        int httpCode = http.POST(postData);
        if (httpCode > 0) {
            String payload = http.getString();
            Serial.println("Server Response: " + payload);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Server Resp:");
            lcd.setCursor(0, 1);
            lcd.print(payload.length() > 16 ? payload.substring(0,16) : payload);
        } else {
            Serial.print("POST Error: ");
            Serial.println(httpCode);
            showError("POST Failed");
        }

        http.end();
    } else {
        Serial.println("Not connected to WiFi!");
        showError("No WiFi");
    }
}

// Helper function to show errors on LCD
void showError(const char* message) {
    Serial.println(message);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message);
    delay(2000);
    lcd.clear();
}