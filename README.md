# ButtonFunction Library for Arduino

ButtonFunction is a library for detecting button taps and long presses on Arduino. It provides a simple and easy-to-use API for registering button press events and executing callback functions in response to those events. The library is designed to be lightweight and efficient, and can be used with any Arduino board and development environment.

## Installation

To use the ButtonFunction library, follow these steps:

1. Download the latest release from the [GitHub repository](https://github.com/noumanmhd/button-function-arduino/releases).
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...** and select the downloaded file.
3. The library should now be installed and ready to use.

## Usage
To use the ButtonFunction library in your Arduino sketch, follow these steps:

1. Include the `ButtonFunction.h` header file at the beginning of your sketch:

   ```c++
   #include "ButtonFunction.h"
    ```

2. Create a ButtonFunction object, specifying the pin that the button is connected to:
   ```c++
   ButtonFunction button(2);
   ```

   This will create a ButtonFunction object that is connected to pin 2. The pin should be connected to the button's ground pin. The button should be connected to the pin's 5V pin through a 10kΩ resistor.

3. Register callback functions for button presses:

   ```c++
    button.attachTap(&myTapFunction, 1);
    button.attachLongPress(&myLongPressFunction, 2);
    button.attachTapAndPress(&myTapAndPressFunction, 2, 1);
    ```

    These functions will be called when the button is tapped, long pressed, or tapped and then long pressed, respectively. The first argument is a pointer to the callback function, and the second argument is the number of times the button should be tapped or long pressed for the callback function to be called. The callback functions should be declared as follows:

    ```c++
    void myTapFunction() {
        // Do something
    }

    void myLongPressFunction() {
        // Do something
    }

    void myTapAndPressFunction() {
        // Do something
    }
    ```
    The callback functions should not take any arguments and should not return any values.

4. In your main loop, call the scan() method of the ButtonFunction object:

    ```c++
    void loop() {
        button.scan();
    }
    ```

    This will scan the button for press events and call the appropriate callback functions.


4. You can also set the maximum delay between taps (`setMaxTapDelay()`) and the gap delay between button presses (`setGapDelay()`):

    ```c++
    button.setMaxTapDelay(500);
    button.setGapDelay(1000);
    ```

    These settings can be used to adjust the behavior of the button detection algorithm.

## Example

The following example sketch demonstrates how to use the ButtonFunction library:

```c++
#include "ButtonFunction.h"

ButtonFunction button(2);

void setup() {
  Serial.begin(9600);
  button.attachTap(&tapFunction, 1);
  button.attachLongPress(&longPressFunction, 2);
  button.attachTapAndPress(&tapAndPressFunction, 2, 1);
}

void loop() {
  button.scan();
}

void tapFunction() {
  Serial.println("Button tapped once.");
}

void longPressFunction() {
  Serial.println("Button long pressed twice.");
}

void tapAndPressFunction() {
  Serial.println("Button tapped twice and long pressed once.");
}
```

## Contributing

Contributions are welcome! If you find a bug or have a feature request, please open an issue on the [GitHub repository](https://github.com/noumanmhd/button-function-arduino/issues). If you would like to contribute code, please fork the repository and submit a pull request.

## License

ButtonFunction is released under the [GNU General Public License version 3.0](https://www.gnu.org/licenses/gpl-3.0.en.html). See `LICENSE` for details.
