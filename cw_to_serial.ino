static const uint8_t in_key_pin = 7;    // D7  : interrupt 4 on pin 1
static const uint8_t out_led_pin = 13;  // D13 : Built-in LED on pin 13
static volatile bool key_event;
static bool key_is_up;
static const unsigned long debounce_millis = 10; // 30 WPM == 40 ms
static unsigned long last_event_millis;

void setup() {
  pinMode(in_key_pin, INPUT_PULLUP);
  pinMode(out_led_pin, OUTPUT);
  key_is_up = digitalRead(in_key_pin);
  last_event_millis = millis();
  uint8_t irqn = digitalPinToInterrupt(in_key_pin);
  attachInterrupt(irqn, isr_key, CHANGE);
}

void loop() {
  unsigned long now = millis();
  if (!key_event) {
    return;
  }
  key_event = false;
  if (last_event_millis + debounce_millis > now) {
    return;
  }
  key_is_up = digitalRead(in_key_pin);
  digitalWrite(out_led_pin, !key_is_up);
  last_event_millis = now;
}

void isr_key() {
  key_event = true;
}
