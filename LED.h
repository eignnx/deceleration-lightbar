class LED
{
  int pin;
  unsigned int brightness;

public:

  LED() { pin = 0; brightness = 0; }
  LED(int pin) {
    pinMode(pin, OUTPUT);
    this->pin = pin;
    brightness = 0;
  }

  void update(unsigned int new_brightness) {
    brightness = new_brightness;
  }

  void display() {
    analogWrite(pin, brightness);
  }
};
