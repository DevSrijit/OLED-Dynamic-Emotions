# RoboEyes Animation Library

RoboEyes is an advanced animation library designed to create lifelike, dynamic eye animations on OLED screens. This library leverages the Adafruit GFX library to render smooth, expressive robot eyes that can convey a range of emotions and behaviors. Ideal for robotics, art installations, and interactive displays, RoboEyes brings a touch of personality and intelligence to your projects.

## Features

- **Smooth Animations**: Utilizes Adafruit GFX primitives for seamless animations.
- **Emotional Expressions**: Supports multiple moods such as happy, angry, tired, and more.
- **Dynamic Positioning**: Eyes can move to predefined positions or follow custom paths.
- **Macro Animations**: Includes complex animations like blinking, laughing, and being confused.
- **Customizable**: Easily adjust eye size, shape, and spacing to fit different screen dimensions.

## Getting Started

### Prerequisites

- **Hardware**: An OLED display compatible with the Adafruit SSD1306 library.
- **Software**: Arduino IDE with the following libraries installed:
  - Adafruit GFX Library
  - Adafruit SSD1306

### Installation

1. Clone the repository to your local machine.
2. Open the `sketch.ino` file in the Arduino IDE.
3. Ensure the required libraries are installed via the Arduino Library Manager.

### Usage

1. **Initialize the Display**: Set up the OLED display using the Adafruit SSD1306 library.
2. **Create a RoboEyes Instance**: Instantiate the `roboEyes` class to manage eye animations.
3. **Configure Settings**: Use the provided methods to set screen dimensions, frame rate, and initial eye states.
4. **Animate**: Call the `update()` method in your main loop to render animations continuously.

### Example

Here's a basic example to get you started:

```
cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RoboEyes.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
roboEyes roboEyes;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    
    roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
    roboEyes.setAutoblinker(ON, 3, 2);
    roboEyes.setIdleMode(ON, 2, 2);
}

void loop() {
    roboEyes.update();
}
```

## Documentation

For detailed documentation on all available methods and configurations, please refer to the source code comments and examples provided in the `RoboEyes.h` file.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your improvements or bug fixes.

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for more details.

## Acknowledgments

- **Dennis Hoelscher**: Original author and creator of the FluxGarage_RoboEyes library.
- **Adafruit**: For their excellent GFX and SSD1306 libraries that make this project possible.

For any questions or support, please contact the author at [srijit.co](https://srijit.co).
