#include <Adafruit_Fingerprint.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the RX and TX pins for the fingerprint sensor
#define RX_PIN 16
#define TX_PIN 17

// Wi-Fi credentials
const char* ssid = "TP-Link_C090";
const char* password = "30888630";

// Server endpoint (PHP script URL)
const char* serverUrl = "http://192.168.201.145/update_fingerprint.php";

// Initialize HardwareSerial on UART2
HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Initialize the LCD (assuming 16x2 and I2C address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  mySerial.begin(57600, SERIAL_8N1, RX_PIN, TX_PIN); // Initialize fingerprint sensor

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initializing...");

  delay(100);

  Serial.println("\n\nAdafruit Fingerprint Sensor Enrollment");

  finger.begin(57600);
  delay(5);

  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor detected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sensor detected!");
  } else {
    Serial.println("Fingerprint sensor not detected :(");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No Sensor Found!");
    while (1) { delay(1); }
  }

  // Connect to Wi-Fi
  connectToWiFi();
  
  Serial.println("Ready to enroll fingerprints.");
  Serial.println("Type an ID (1-1000) and press Enter.");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ready for ID");
}

void loop() {
  if (Serial.available() > 0) {
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ready for ID");
    
    int id = Serial.parseInt();
    if (id < 1 || id > 1000) {
      Serial.println("Invalid ID. Enter 1-1000.");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Invalid ID!");
      return;
    }
    enrollFingerprint(id);
  }
}

// Function to enroll a new fingerprint
void enrollFingerprint(int id) {
  Serial.print("Enrolling ID #"); Serial.println(id);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enrolling ID:");
  lcd.setCursor(0,1);
  lcd.print(id);

  delay(1000);
  
  int p = -1;
  Serial.println("Place your finger...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Place finger");

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    if (p == FINGERPRINT_NOFINGER) {
      // Just wait
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Communication error");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Comm Error");
    } else if (p == FINGERPRINT_IMAGEFAIL) {
      Serial.println("Imaging error");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Imaging Error");
    } else if (p != FINGERPRINT_OK && p != FINGERPRINT_NOFINGER) {
      Serial.println("Unknown error");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Unknown Error");
    }
    delay(100);
  }

  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) {
    Serial.println("Error converting image");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Convert Err");
    return;
  }

  Serial.println("Remove finger");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Remove finger");
  delay(2000);

  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
    delay(100);
  }

  Serial.println("Place the same finger again...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Again Finger");

  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    if (p == FINGERPRINT_NOFINGER) {
      // waiting
    } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
      Serial.println("Communication error");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Comm Error");
    } else if (p == FINGERPRINT_IMAGEFAIL) {
      Serial.println("Imaging error");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Imaging Error");
    } else if (p != FINGERPRINT_OK && p != FINGERPRINT_NOFINGER) {
      Serial.println("Unknown error");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Unknown Error");
    }
    delay(100);
  }

  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) {
    Serial.println("Error converting image");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Convert Err");
    return;
  }

  Serial.print("Creating model for ID #"); Serial.println(id);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Matching Prints");

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Prints Matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Comm Error");
    return;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No Match");
    return;
  } else {
    Serial.println("Unknown error");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error");
    return;
  }

  Serial.print("Storing model for ID "); Serial.println(id);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Storing Model");

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Fingerprint enrolled successfully!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enroll Success!");
    // Send data to server after successful enrollment
    sendFingerprintDataToServer(id);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Comm Error");
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store at this location");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bad Location");
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash memory");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Flash Error");
  } else {
    Serial.println("Unknown error");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown Error");
  }
}

// Connect to WiFi network
void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting WiFi");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // Optional: show some animation or dots on LCD, but might just leave as is
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP().toString());
}

// Send fingerprint data to server
void sendFingerprintDataToServer(int sr_no) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String postData = "sr_no=" + String(sr_no);

    // Send POST request
    int httpCode = http.POST(postData);

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Server Response:");
      Serial.println(payload);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Server Resp:");
      lcd.setCursor(0,1);
      // If payload fits in 16 chars, print it directly, else truncate
      if (payload.length() > 16) {
        lcd.print(payload.substring(0,16));
      } else {
        lcd.print(payload);
      }

      delay(1000);

    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpCode);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("POST Error");
    }

    http.end();
  } else {
    Serial.println("Not connected to WiFi, cannot send data.");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No WiFi");
  }
}
