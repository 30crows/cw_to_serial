static const uint8_t in_key_pin = 7;    // D7  : interrupt 4 on pin 1
static const uint8_t out_led_pin = 13;  // D13 : Built-in LED on pin 13
static bool key_is_up;
static const unsigned long debounce_millis = 20; // 30 WPM == 40 ms
static unsigned long last_change_millis;

void setup() {
  Serial.begin(115200);
  pinMode(in_key_pin, INPUT_PULLUP);
  pinMode(out_led_pin, OUTPUT);
  key_is_up = digitalRead(in_key_pin);
  Serial.print(!key_is_up);
  last_change_millis = millis();
}

void loop() {
  unsigned long millis_now = millis();
  if (key_is_up == digitalRead(in_key_pin)) {
    return;
  }
  if (last_change_millis + debounce_millis > millis_now) {
    return;
  }
  Serial.print(key_is_up); // inverted
  digitalWrite(out_led_pin, key_is_up); // inverted
  key_is_up = !key_is_up;
  last_change_millis = millis_now;
}
