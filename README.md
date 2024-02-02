# Bilancia SaT

This project uses Arduino and various libraries to create a weighing system using an HX711 load cell amplifier, an LCD display, and a tare button. The program continuously reads the change in weight and displays it on both the Serial Monitor and the LCD screen. We also implemented a tare button to reset the scale to zero when needed.

### Example

<img src="medias/photos/test1.jpg" alt="Example">
<img src="medias/photos/test2.jpg" alt="Example">

### Front View

<img src="medias/photos/front.jpg" alt="Front View">

### Top View

<img src="medias/photos/top.jpg" alt="Top View">

### Bottom View

<img src="medias/photos/bottom.jpg" alt="Bottom View">

### Side View

<img src="medias/photos/side1.jpg" alt="Side View">
<img src="medias/photos/side2.jpg" alt="Side View">

## Components Used

### Battery 9V

<img src="medias/parts/9v_battery.jpg" alt="9V Battery">

The 9V battery is used as a portable power source for the project.

### Touch Button (HW-139)

<img src="medias/parts/touch_sensor.jpg" alt="Touch button">

The HW-139 touch button is a component used for touch detection. It can be used as a tare button for resetting the scale.

### I2C 16x2 LCD Display

<img src="medias/parts/i2c_Screen.jpg" alt="16x2 Screen">

The I2C 16x2 LCD display is used to show information such as the measured weight or other relevant details.

### ON-OFF Switch

<img src="medias/parts/on_off_switch.jpg" alt="Switch">

The ON-OFF switch is used to control the power supply to the circuit.

### ATtiny or Arduino Nano

<img src="medias/parts/board.jpg" alt="Board">

The ATtiny or Arduino Nano is a microcontroller development board used for programming and controlling the scale and its components.

### 5KG Load Cell

<img src="medias/parts/load_cell.jpg" alt="Load Cell">

The 5KG load cell is a weight sensor used to measure the weight of objects placed on the plate.

### HX711

<img src="medias/parts/hx711.jpg" alt="HX711">

The HX711 is used to amplify and convert the analog signal from the load cell into a digital one that can be read by the microcontroller.

### PCB Board

<img src="medias/parts/pcb_board.jpg" alt="PCB board">

The PCB (Printed Circuit Board) is used to connect and organize the electronic components in the project.

### Rubber supports

<img src="medias/parts/rubber_support.jpg" alt="Rubber support">

## Wiring
The components are wired as follows:

<img src="medias/load_cell_schematic_bb.png" alt="Schematic">

HX711 load cell amplifier:
- LOADCELL_DOUT_PIN is connected to pin 3 of the Arduino board.
- LOADCELL_SCK_PIN is connected to pin 2 of the Arduino board.

LCD display (I2C interface):
- Address: 0x27
- Columns: 16
- Rows: 2

Tare button:
- Connect one terminal of the button to a digital input pin of the Arduino board.
- Connect the other terminal of the button to the ground (GND) pin of the Arduino board.
- Optionally, add a pull-up resistor between the digital input pin and the 5V pin of the Arduino board to ensure stable button readings. (We implemented it, if you want to add it, you can modify it in declaration part)

## Variables
The program uses the following variables:

- `calibration_factor`: This variable is used to calibrate the scale. It is a float value that can be adjusted based on the specific characteristics of the load cell and the desired measurement units.
- `units`: This variable stores the measured weight in grams.

## Setup
- Serial Monitor Initialization: The Serial Monitor is initialized with a baud rate of 115200.
- LCD Initialization: The LCD display is initialized using the above mentioned I2C address and the number of columns and rows.
- Button Initialization: The tare button pin is declared as an input, and if needed, a pull-up resistor is enabled.
- Scale Initialization: The HX711 scale is initialized with the specified data output pin and clock input pin.
- Raw Data Reading: The program reads the raw data from the scale using the `scale.read()` and `scale.read_average(20)` methods. This helps to determine the calibration factor.
- Calibration Factor Reading: The calibration factor is set using the `scale.set_scale()` method based on the raw data readings. The calibration factor adjusts the scale to provide accurate weight measurements.
- Tare Reading: The scale is tared using the `scale.tare()` method, which resets the scale to zero. This allows to measure the weight of objects neglecting the container's one.
- Serial and LCD Initialization Messages: Initialization messages are printed to the Serial Monitor and the LCD display to indicate that the setup process is completed.

## Main Loop
- Weight Measurement: The program continuously reads the change in weight using the `scale.get_units(10)` method. The 10 parameter represents the number of samples to average for a stable reading.
- LCD Output: The change in weight is displayed on the LCD screen by setting the cursor position and printing the weight value.
- Tare Functionality: If the tare button is pressed (HIGH state), the scale is tared again using the `scale.tare()` method. This allows for resetting the scale to zero when needed.
- Delay: The program waits for 100 milliseconds before reading the weight again. This delay helps to stabilize and to avoid rapid fluctuations of the measurements.

## Dependencies
The following libraries are required for this program to compile and run:

- Arduino.h: Provides the core Arduino functions and types.
- Wire.h: Enables communication with I2C devices.
- LiquidCrystal_I2C.h: Allows interfacing with I2C-based LCD displays.
- HX711.h: Provides the HX711 load cell amplifier functionality.

## 3D Printed parts

This project involves the creation of a scale using a combination of 3D-printed parts and electronic components. The modular design of the project allows for customization of the 3D-printed parts according to your specific needs.

### Parts Created

We have designed and printed several key parts for the scale, including:

- **Platform**: where the objects to be weighed are placed.

<img src="medias/printed_part/place_load_cell.png" alt="Platform">

- **Load Cell Support**: securely holds the load cell in place.

<img src="medias/printed_part/support_load_cell.png" alt="Support">

- **Body**: provides support to all the components and gives an aesthetically pleasing appearance.

<img src="medias/printed_part/body_load_cell.png" alt="Body">

These 3D-printed parts have been carefully designed to ensure proper functionality and compatibility with the electronic components used in the project.

### Replicating the Project

If you are interested in recreating this scale project at home, you can easily replicate the 3D-printed parts by downloading the provided design files. Simply import the files into your preferred 3D modeling software and adjust them to fit your specific printer and requirements. Once you have the 3D-printed parts, you can follow the instructions in the project documentation to assemble and integrate the electronic components.

## Test



### Calibration

We are trying to calibrate this scale using an iterative method to find the calibration factor and the offset that minimize the error between the actual weight and the measured weight. To do this, you can use the following formula:

$$
\text{Actual weight} = \text{Measured weight} \times \text{Cf} + \text{Offset}
$$

To calculate the error, we can use the following formula:

$$
\text{Error} = \sum_{i=1}^{n} (\text{Actual weight}_i - \text{Measured weight}_i \times \text{Cf} - \text{Offset})^2
$$

Where $n$ is the number of weights used in each iteration.

To find the Cf and the Offset that minimize the error, we use the gradient method, which consists of changing the values of Cf and Offset according to the derivative of the error with respect to them, using the following formulas:

$$
\text{New Cf} = \text{Cf} - \alpha \frac{\partial \text{Error}}{\partial \text{Cf}}
$$

$$
\text{New Offset} = \text{Offset} - \alpha \frac{\partial \text{Error}}{\partial \text{Offset}}
$$

Where $\alpha$ (also called Learning rate) is a parameter that controls the speed of convergence of the method, evaluating a value of $\alpha$ that is small enough to avoid oscillations, but large enough to reach the minimum in a few iterations.

To calculate the partial derivatives of the error, we need to use the following formulas:

$$
\frac{\partial \text{Error}}{\partial \text{Cf}} = -2 \sum_{i=1}^{n} (\text{Actual weight}_i - \text{Measured weight}_i \times \text{Cf} - \text{Offset}) \times \text{Measured weight}_i
$$

$$
\frac{\partial \text{Error}}{\partial \text{Offset}} = -2 \sum_{i=1}^{n} (\text{Actual weight}_i - \text{Measured weight}_i \times \text{Cf} - \text{Offset})
$$

In reality, for the calculation of Cf and offset, we are using an empirical formula, that is, adding the error with a certain weight to the previously calculated values:

$$
\text{New Cf} = \text{Cf} - \beta \times \text{Error}
$$

$$
\text{New Offset} = \text{Offset} - \beta \times \text{Error}
$$

Where $\beta$ is a kind of learning rate, suitably tuned to get progressively better results.

## Procedure

Wanting to go through the entire calibration process in depth:

- We prepared 6 iterations, with gradually smaller ranges, using sample weights:
    - Iteration 0: 0g-100g (10g increment)
    - Iteration 1: 0g-50g (increment of 5g)
    - Iteration 2: 0g-5.5g (0.5g increment)
    - Iteration 3: 0g-2g (0.2g increment)
    - Iteration 4: 0g-0.5g (increment of 0.05g)
    - Iteration 5: 0g-0.2g (increment of 0.02g)

- We placed each weight for 5 points of the plate (center and the four corners)

- Using MATLAB, we used a regression algorithm to fit the collected data The slope of the regression line represents the calibration factor and the intercept represents the offset, using the Euclidean norm (norm 2) to evaluate the error.

- Last we used the data calculated by calibration, using it when compiling the microcontroller program.


### Noise



### Repeatability



### Eccentricity



### Hysteresis



## Further Improvements
- You can modify the calibration factor (`calibration_factor`) to adjust the scale according to your specific load cell and measurement requirements.
- The program can be extended to support different measurement units by adding appropriate conversions and displaying the result in the desired unit on the LCD screen.
- Error handling and validation can be implemented to handle exceptional cases, such as when the load cell is not connected or when the measurements are out of range, making them block the execution of the entire program.
- You can compile this code to run also on other boards that are better for 3D printed cases (actually tested on Arduino Uno, ESP8266)

## License
This project is licensed under the GPLv3 license.