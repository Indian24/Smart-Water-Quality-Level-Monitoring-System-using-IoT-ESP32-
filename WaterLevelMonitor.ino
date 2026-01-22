// ---------- Blynk Credentials ----------
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""

// ---------- WiFi Credentials ----------
char ssid[] = "";
char pass[] = "";

// ---------- Tank Configuration ----------
int emptyTankDistance = 70;   // Distance when tank is empty (cm)
int fullTankDistance  = 30;   // Distance when tank is full (cm)
int triggerPer = 10;          // Alert trigger level (%)

// ---------- Required Libraries ----------
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <AceButton.h>

using namespace ace_button;

// ---------- Pin Definitions ----------
#define TRIGPIN    27     // Ultrasonic trigger pin
#define ECHOPIN    26     // Ultrasonic echo pin
#define wifiLed    2      // WiFi status LED
#define ButtonPin1 12     // Push button for buzzer control
#define BuzzerPin  13     // Buzzer pin
#define GreenLed   14     // Water level alert LED

// ---------- Blynk Virtual Pins ----------
#define VPIN_BUTTON_1 V1  // Water level percentage
#define VPIN_BUTTON_2 V2  // Distance in cm

// ---------- OLED Display Settings ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------- Global Variables ----------
float duration;          // Echo pulse duration
float distance;          // Calculated distance (cm)
int waterLevelPer;       // Water level percentage
bool toggleBuzzer = HIGH; // Controls buzzer ON/OFF state

char auth[] = BLYNK_AUTH_TOKEN;

// ---------- Button Setup ----------
ButtonConfig config1;
AceButton button1(&config1);

// ---------- Timer ----------
BlynkTimer timer;

// ---------- Check Blynk Connection ----------
void checkBlynkStatus() {
  if (Blynk.connected()) {
    digitalWrite(wifiLed, HIGH);  // WiFi connected
  } else {
    digitalWrite(wifiLed, LOW);   // WiFi disconnected
  }
}

// ---------- Sync Blynk Data ----------
BLYNK_CONNECTED() {
  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
}

// ---------- Display Water Level on OLED ----------
void displayData(int value) {
  display.clearDisplay();
  display.setTextSize(4);
  display.setCursor(8, 2);
  display.print(value);
  display.print(" %");
  display.display();
}

// ---------- Measure Water Level ----------
void measureDistance() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIGPIN, LOW);

  // Read echo pulse duration
  duration = pulseIn(ECHOPIN, HIGH);

  // Convert duration to distance (cm)
  distance = ((duration / 2) * 0.343) / 10;

  // Validate distance range
  if (distance > (fullTankDistance - 10) && distance < emptyTankDistance) {

    // Convert distance to percentage
    waterLevelPer = map((int)distance, emptyTankDistance, fullTankDistance, 0, 100);

    // Update OLED display
    displayData(waterLevelPer);

    // Send data to Blynk
    Blynk.virtualWrite(VPIN_BUTTON_1, waterLevelPer);
    Blynk.virtualWrite(VPIN_BUTTON_2, String(distance) + " cm");

    // Low water level alert
    if (waterLevelPer < triggerPer) {
      digitalWrite(GreenLed, HIGH);
      if (toggleBuzzer == HIGH) {
        digitalWrite(BuzzerPin, HIGH);
      }
    }

    // Tank full alert
    if (distance < fullTankDistance) {
      digitalWrite(GreenLed, LOW);
      if (toggleBuzzer == HIGH) {
        digitalWrite(BuzzerPin, HIGH);
      }
    }

    // Reset buzzer when level is normal
    if (distance > (fullTankDistance + 5) && waterLevelPer > (triggerPer + 5)) {
      toggleBuzzer = HIGH;
      digitalWrite(BuzzerPin, LOW);
    }
  }

  delay(100);
}

// ---------- Button Event Handler ----------
void button1Handler(AceButton*, uint8_t eventType, uint8_t) {
  if (eventType == AceButton::kEventReleased) {
    digitalWrite(BuzzerPin, LOW); // Turn off buzzer
    toggleBuzzer = LOW;           // Disable further buzzer alerts
  }
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);

  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(wifiLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ButtonPin1, INPUT_PULLUP);

  digitalWrite(wifiLed, LOW);
  digitalWrite(GreenLed, LOW);
  digitalWrite(BuzzerPin, LOW);

  // Initialize button
  config1.setEventHandler(button1Handler);
  button1.init(ButtonPin1);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();

  // Connect WiFi and Blynk
  WiFi.begin(ssid, pass);
  Blynk.config(auth);

  // Check Blynk connection every 2 seconds
  timer.setInterval(2000L, checkBlynkStatus);
}

// ---------- Main Loop ----------
void loop() {
  measureDistance();
  Blynk.run();
  timer.run();
  button1.check();
}
