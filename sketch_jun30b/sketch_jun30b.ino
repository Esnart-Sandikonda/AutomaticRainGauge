#include <SoftwareSerial.h>

const int tippingPin = 2; // Digital pin to which the tipping bucket sensor is connected
const double tippingBucketFactor = 0.2; // Conversion factor for TR 525I tipping bucket (0.2 mm per tip)
unsigned int tipCount = 0; // Stores the count of tip events
unsigned long previousTime = 0; // Stores the previous timestamp
unsigned long intervalHourly = 3600000; // Interval for hourly rainfall calculation in milliseconds
unsigned long intervalDaily = 86400000; // Interval for daily rainfall calculation in milliseconds
unsigned long intervalWeekly = 604800000; // Interval for weekly rainfall calculation in milliseconds

SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins for HC-05 module

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  pinMode(tippingPin, INPUT_PULLUP);
}

void loop() {
  unsigned long currentTime = millis();

  if (digitalRead(tippingPin) == LOW && currentTime - previousTime >= intervalHourly) {
    tipCount++;
    previousTime = currentTime;

    double rainfallAmountHourly = tipCount * tippingBucketFactor;
    double rainfallIntensityHourly = rainfallAmountHourly / (intervalHourly / 3600000.0);

    // Send hourly rainfall data to the Android app via Bluetooth
    bluetoothSerial.print("Hourly Rainfall Amount: ");
    bluetoothSerial.print(rainfallAmountHourly);
    bluetoothSerial.println(" mm");

    bluetoothSerial.print("Hourly Rainfall Intensity: ");
    bluetoothSerial.print(rainfallIntensityHourly);
    bluetoothSerial.println(" mm/hr");

    // Print hourly rainfall data to the Serial monitor for debugging
    Serial.print("Hourly Rainfall Amount: ");
    Serial.print(rainfallAmountHourly);
    Serial.println(" mm");

    Serial.print("Hourly Rainfall Intensity: ");
    Serial.print(rainfallIntensityHourly);
    Serial.println(" mm/hr");

    // Reset the tip count after printing the data
    tipCount = 0;
  }

  // Calculate and print other rainfall data (daily and weekly)
  if (currentTime - previousTime >= intervalDaily) {
    double rainfallAmountDaily = tipCount * tippingBucketFactor;
    double rainfallIntensityDaily = rainfallAmountDaily / (intervalDaily / 3600000.0);

    // Send daily rainfall data to the Android app via Bluetooth
    bluetoothSerial.print("Daily Rainfall Amount: ");
    bluetoothSerial.print(rainfallAmountDaily);
    bluetoothSerial.println(" mm");

    bluetoothSerial.print("Daily Rainfall Intensity: ");
    bluetoothSerial.print(rainfallIntensityDaily);
    bluetoothSerial.println(" mm/hr");

    // Print daily rainfall data to the Serial monitor for debugging
    Serial.print("Daily Rainfall Amount: ");
    Serial.print(rainfallAmountDaily);
    Serial.println(" mm");

    Serial.print("Daily Rainfall Intensity: ");
    Serial.print(rainfallIntensityDaily);
    Serial.println(" mm/hr");

    // Reset the tip count after printing the data
    tipCount = 0;
  }

  if (currentTime - previousTime >= intervalWeekly) {
    double rainfallAmountWeekly = tipCount * tippingBucketFactor;
    double rainfallIntensityWeekly = rainfallAmountWeekly / (intervalWeekly / 3600000.0);

    // Send weekly rainfall data to the Android app via Bluetooth
    bluetoothSerial.print("Weekly Rainfall Amount: ");
    bluetoothSerial.print(rainfallAmountWeekly);
    bluetoothSerial.println(" mm");

    bluetoothSerial.print("Weekly Rainfall Intensity: ");
    bluetoothSerial.print(rainfallIntensityWeekly);
    bluetoothSerial.println(" mm/hr");

    // Print weekly rainfall data to the Serial monitor for debugging
    Serial.print("Weekly Rainfall Amount: ");
    Serial.print(rainfallAmountWeekly);
    Serial.println(" mm");

    Serial.print("Weekly Rainfall Intensity: ");
    Serial.print(rainfallIntensityWeekly);
    Serial.println(" mm/hr");

    // Reset the tip count after printing the data
    tipCount = 0;
  }
}
