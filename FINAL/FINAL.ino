#include <SoftwareSerial.h>

const int tippingPin = 2; // Digital pin to which the tipping bucket sensor is connected
const double tippingBucketFactor = 0.2; // Conversion factor for TR 525I tipping bucket (0.2 mm per tip)
unsigned int totalTipCount = 0; // Stores the total number of tip events
unsigned long previousTime = 0; // Stores the previous timestamp
unsigned long intervalHourly = 60000; // Interval for hourly rainfall calculation in milliseconds
unsigned long intervalDaily = 86400000; // Interval for daily rainfall calculation in milliseconds
unsigned long intervalWeekly = 604800000; // Interval for weekly rainfall calculation in milliseconds
unsigned long intervalMonthly = 2592000000; // Interval for monthly rainfall calculation in milliseconds
unsigned long intervalYearly = 31536000000; // Interval for yearly rainfall calculation in milliseconds

SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins for HC-05 module

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  pinMode(tippingPin, INPUT_PULLUP);
}

void loop() {
  unsigned long currentTime = millis();

  if (digitalRead(tippingPin) == LOW) {
    totalTipCount++; // Increment the total number of tip events

    if (previousTime == 0) {
      previousTime = currentTime;
    }

    if (currentTime - previousTime >= intervalHourly) {
      double rainfallAmountHourly = totalTipCount * tippingBucketFactor;
      double rainfallIntensityHourly = rainfallAmountHourly / ((currentTime - previousTime) / 3600000.0);

      Serial.print("Hourly Rainfall Amount: ");
      Serial.print(rainfallAmountHourly);
      Serial.println(" mm");

      Serial.print("Hourly Rainfall Intensity: ");
      Serial.print(rainfallIntensityHourly);
      Serial.println(" mm/hr");

      // Send data to Bluetooth app-
      bluetoothSerial.print("HRA:"); // Hourly Rainfall Amount
      bluetoothSerial.print(rainfallAmountHourly);
      bluetoothSerial.print(";");
      bluetoothSerial.print("HRI:"); // Hourly Rainfall Intensity
      bluetoothSerial.print(rainfallIntensityHourly);
      bluetoothSerial.print(";");

      // Reset the previous time
      previousTime = currentTime;
    }

    if (currentTime - previousTime >= intervalDaily) {
      double rainfallAmountDaily = totalTipCount * tippingBucketFactor;
      double rainfallIntensityDaily = rainfallAmountDaily / ((currentTime - previousTime) / 3600000.0);

      Serial.print("Daily Rainfall Amount: ");
      Serial.print(rainfallAmountDaily);
      Serial.println(" mm");

      Serial.print("Daily Rainfall Intensity: ");
      Serial.print(rainfallIntensityDaily);
      Serial.println(" mm/hr");

      // Send data to Bluetooth app
      bluetoothSerial.print("DRA:"); // Daily Rainfall Amount
      bluetoothSerial.print(rainfallAmountDaily);
      bluetoothSerial.print(";");
      bluetoothSerial.print("DRI:"); // Daily Rainfall Intensity
      bluetoothSerial.print(rainfallIntensityDaily);
      bluetoothSerial.print(";");

      // Reset the previous time
      previousTime = currentTime;
    }

    if (currentTime - previousTime >= intervalWeekly) {
      double rainfallAmountWeekly = totalTipCount * tippingBucketFactor;
      double rainfallIntensityWeekly = rainfallAmountWeekly / ((currentTime - previousTime) / 3600000.0);

      Serial.print("Weekly Rainfall Amount: ");
      Serial.print(rainfallAmountWeekly);
      Serial.println(" mm");

      Serial.print("Weekly Rainfall Intensity: ");
      Serial.print(rainfallIntensityWeekly);
      Serial.println(" mm/hr");

      // Send data to Bluetooth app
      bluetoothSerial.print("WRA:"); // Weekly Rainfall Amount
      bluetoothSerial.print(rainfallAmountWeekly);
      bluetoothSerial.print(";");
      bluetoothSerial.print("WRI:"); // Weekly Rainfall Intensity
      bluetoothSerial.print(rainfallIntensityWeekly);
      bluetoothSerial.print(";");

      // Reset the previous time
      previousTime = currentTime;
    }

    if (currentTime - previousTime >= intervalMonthly) {
      double rainfallAmountMonthly = totalTipCount * tippingBucketFactor;
      double rainfallIntensityMonthly = rainfallAmountMonthly / ((currentTime - previousTime) / 3600000.0);

      Serial.print("Monthly Rainfall Amount: ");
      Serial.print(rainfallAmountMonthly);
      Serial.println(" mm");

      Serial.print("Monthly Rainfall Intensity: ");
      Serial.print(rainfallIntensityMonthly);
      Serial.println(" mm/hr");

      // Send data to Bluetooth app
      bluetoothSerial.print("MRA:"); // Monthly Rainfall Amount
      bluetoothSerial.print(rainfallAmountMonthly);
      bluetoothSerial.print(";");
      bluetoothSerial.print("MRI:"); // Monthly Rainfall Intensity
      bluetoothSerial.print(rainfallIntensityMonthly);
      bluetoothSerial.print(";");

      // Reset the previous time
      previousTime = currentTime;
    }

    if (currentTime - previousTime >= intervalYearly) {
      double rainfallAmountYearly = totalTipCount * tippingBucketFactor;
      double rainfallIntensityYearly = rainfallAmountYearly / ((currentTime - previousTime) / 3600000.0);

      Serial.print("Yearly Rainfall Amount: ");
      Serial.print(rainfallAmountYearly);
      Serial.println(" mm");

      Serial.print("Yearly Rainfall Intensity: ");
      Serial.print(rainfallIntensityYearly);
      Serial.println(" mm/hr");

      // Send data to Bluetooth app
      bluetoothSerial.print("YRA:"); // Yearly Rainfall Amount
      bluetoothSerial.print(rainfallAmountYearly);
      bluetoothSerial.print(";");
      bluetoothSerial.print("YRI:"); // Yearly Rainfall Intensity
      bluetoothSerial.print(rainfallIntensityYearly);
      bluetoothSerial.print(";");

      // Reset the previous time
      previousTime = currentTime;
    }
  }
  else {
    // No tip event occurred, print 0mm results

    Serial.println("No tip event occurred.");
    
    // Send data to Bluetooth app
    bluetoothSerial.print("HRA:0;");
    bluetoothSerial.print("HRI:0;");
    bluetoothSerial.print("DRA:0;");
    bluetoothSerial.print("DRI:0;");
    bluetoothSerial.print("WRA:0;");
    bluetoothSerial.print("WRI:0;");
    bluetoothSerial.print("MRA:0;");
    bluetoothSerial.print("MRI:0;");
    bluetoothSerial.print("YRA:0;");
    bluetoothSerial.print("YRI:0;");
  }
}