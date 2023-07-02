const int tippingPin = 2; // Digital pin to which the tipping bucket sensor is connected
const double tippingBucketFactor = 0.2; // Conversion factor for TR 525I tipping bucket (0.2 mm per tip)
unsigned int tipCount = 0; // Stores the count of tip events
unsigned long previousTimeHourly = 0; // Stores the previous timestamp for hourly calculation
unsigned long previousTimeDaily = 0; // Stores the previous timestamp for daily calculation
unsigned long intervalHourly = 5000; // Interval for hourly rainfall calculation in milliseconds (5 seconds)
unsigned long intervalDaily = 10000; // Interval for daily rainfall calculation in milliseconds (10 seconds)
double rainfallAmountHourly = 0.0; // Stores the cumulative rainfall amount for the hourly interval
double rainfallAmountDaily = 0.0; // Stores the cumulative rainfall amount for the daily interval

void setup() {
  Serial.begin(9600);
  pinMode(tippingPin, INPUT_PULLUP);
}

void loop() {
  unsigned long currentTime = millis();

  if (digitalRead(tippingPin) == LOW) {
    tipCount++;

    if (currentTime - previousTimeHourly >= intervalHourly) {
      rainfallAmountHourly += tipCount * tippingBucketFactor;
      double rainfallIntensityHourly = rainfallAmountHourly / (intervalHourly / 3600000.0);

      Serial.print("Hourly Rainfall Amount: ");
      Serial.print(rainfallAmountHourly);
      Serial.println(" mm");

      Serial.print("Hourly Rainfall Intensity: ");
      Serial.print(rainfallIntensityHourly);
      Serial.println(" mm/hr");

      previousTimeHourly = currentTime;
      tipCount = 0;
    }

    if (currentTime - previousTimeDaily >= intervalDaily) {
      rainfallAmountDaily += tipCount * tippingBucketFactor;
      double rainfallIntensityDaily = rainfallAmountDaily / (intervalDaily / 3600000.0);

      Serial.print("Daily Rainfall Amount: ");
      Serial.print(rainfallAmountDaily);
      Serial.println(" mm");

      Serial.print("Daily Rainfall Intensity: ");
      Serial.print(rainfallIntensityDaily);
      Serial.println(" mm/hr");

      previousTimeDaily = currentTime;
      tipCount = 0;
    }
  }
}