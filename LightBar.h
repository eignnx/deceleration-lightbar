#define dt 1

class LightBar
{
private:
  LED* leds;
  
  int n_leds;
  mutable float theta;
  float frequency;

  const float FASTEST_FREQ = 100.0;
  const float MAX_LEVEL = 1024.0;
  const float DT = 1/30.0;

  unsigned f(float x, float t) {
    return 255*sq(sin(x - t/500.0));
  }

public:
  // Default Constructor
  LightBar() { theta = 0.0; frequency = 1.0; }

  // Constructor
  LightBar(const int pins[], int n_pins) {
    n_leds = n_pins;
    leds = new LED[n_leds];
    for (int i = 0; i < n_leds; i++)
      leds[i] = LED(pins[i]);

    theta = 0.0;
    frequency = 1.0;
  }

  // Destructor
  ~LightBar() {
    delete [] leds;
  }

  void update(int level) {

    frequency = map(level, 0, 1024, 0, FASTEST_FREQ);
    
    // Increment state variable.
    theta += frequency * dt;
    //theta %= frequency;

    float x;
    float brightness = sq(level / MAX_LEVEL);

    for (int i = 0; i < n_leds; i++) {
      x = static_cast<float>(i) / n_leds * PI;
      leds[i].update( brightness * f(x, theta) );
    }
  }

  void display() {
    for (int i = 0; i < n_leds; i++)
      leds[i].display();
  }
};
