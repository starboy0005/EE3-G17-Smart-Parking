#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

// Initialize the LCD using I2C
Adafruit_LiquidCrystal lcd(0);

// Define ultrasonic sensor pins for 4 parking slots
const int trigPins[4] = {3, 5, 7, 9};
const int echoPins[4] = {2, 4, 6, 8};

// Boolean array to track parking slot availability
bool parking_slots[4] = {true, true, true, true};

// Time tracking for occupancy (stores entry time)
unsigned long occupiedSince[4] = {0, 0, 0, 0};
unsigned long lastChargeTime[4] = {0, 0, 0, 0}; // Track last charge time

// Fee tracking (stores total cost per slot)
float fees[4] = {0, 0, 0, 0};
const float ratePer5Seconds = 0.1; // Fee per 5 seconds for simulation

// Simulated ticket number storage
String ticketNumber[4] = {"", "", "", ""};

void setup() {
    Wire.begin(); // Initialize I2C
    lcd.begin(16, 2); // Initialize LCD with 16 columns & 2 rows
    lcd.setBacklight(1); // Turn on backlight

    Serial.begin(9600); // Start Serial Monitor

    // Set pin modes for all sensors
    for (int i = 0; i < 4; i++) {
        pinMode(trigPins[i], OUTPUT);
        pinMode(echoPins[i], INPUT);
    }
}

float getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    float distance = (duration * 0.0343) / 2;

    return distance;
}

void loop() {
    int available_slots = 0;
    String available_slots_list = "";

    for (int i = 0; i < 4; i++) {
        float distance = getDistance(trigPins[i], echoPins[i]);

        if (distance > 300) { // Slot is empty
            if (parking_slots[i]) { // Car just left
                Serial.print("Car Exited | Ticket: ");
                Serial.print(ticketNumber[i]);
                Serial.print(" | Total Fee: $");
                Serial.println(fees[i], 2);
            }
            parking_slots[i] = false;
            occupiedSince[i] = 0; // Reset time tracking
            lastChargeTime[i] = 0; // Reset charge timer
            fees[i] = 0; // Reset fees
            available_slots++;
            available_slots_list += "P" + String(i + 1) + " ";
        } else { // Slot is occupied
            if (!parking_slots[i]) { // Car just arrived
                occupiedSince[i] = millis();
                lastChargeTime[i] = millis();
                ticketNumber[i] = "NP" + String(random(1000, 9999)); // Generate ticket number
                fees[i] = 0; // Reset fee
                Serial.print("Car Entered | Slot: P");
                Serial.println(i + 1);
            }

            // Charge fee every 5 seconds
            if (millis() - lastChargeTime[i] >= 5000) {
                fees[i] += ratePer5Seconds;
                lastChargeTime[i] = millis(); // Reset last charge time

                Serial.print("Charging P");
                Serial.print(i + 1);
                Serial.print(" | Ticket: ");
                Serial.print(ticketNumber[i]);
                Serial.print(" | Fee: $");
                Serial.println(fees[i], 2);
            }

            parking_slots[i] = true;
        }
    }

    // Display available slots
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slots Available:");
    lcd.setCursor(0, 1);
    lcd.print(available_slots);
    delay(1000);

    lcd.clear();
    if (available_slots > 0) {
        lcd.setCursor(0, 0);
        lcd.print("Free Slots:");
        lcd.setCursor(3, 1);
        lcd.print(available_slots_list);
        delay(1000);
    }
}
