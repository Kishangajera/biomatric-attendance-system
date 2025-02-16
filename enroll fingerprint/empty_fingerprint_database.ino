#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>

// Define Serial Port for Fingerprint Sensor
HardwareSerial mySerial(2); // UART2 (GPIO16 - RX, GPIO17 - TX)

// Initialize the fingerprint sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
    Serial.begin(115200);
    Serial.println("Fingerprint Sensor - Empty Database");

    // Properly initialize UART2
    mySerial.begin(57600, SERIAL_8N1, 16, 17);
    delay(1000); // Wait for the sensor to be ready

    // Start the sensor
    finger.begin(57600);
    
    if (finger.verifyPassword()) {
        Serial.println("Fingerprint sensor found!");
    } else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1);
    }

    Serial.println("Deleting all fingerprints...");

    // Delete all fingerprints
    int result = finger.emptyDatabase();

    if (result == FINGERPRINT_OK) {
        Serial.println("All fingerprints deleted successfully!");
    } else {
        Serial.println("Failed to delete fingerprints. Error Code: " + String(result));
    }
}

void loop() {
    // Nothing in the loop
}
