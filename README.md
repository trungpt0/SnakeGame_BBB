# Snake Game
Snake Game is a classic game where you control a snake to eat food and grow longer. The goal is to achieve the highest score without crashing into walls or the snake's own body. This project is developed on an embedded system with an OLED interface, using BeagleBone Black, I2C communication, and physical buttons for control.
## Technologies Used
- BeagleBone Black: used to run the game.
- SSD1306 OLED: A 128x64 pixel display connected via I2C.
- I2C Protocol: The communication protocol between the BeagleBone Black and the OLED display.
- 4 Buttons: Physical buttons to control the snake's movement (up, down, left, right).
## Features
- Simple Interface: The game is displayed on a 128x64 OLED screen.
- Button Controls: The snake is controlled using four physical buttons to move in different directions.
- Score Display: The current score is displayed in real-time as the snake eats food.
## Installation
### Hardware Requirements:
- BeagleBone Black (x1)
- SSD1306 OLED (x1)
- Button (x4)
### Software Requirements:
- Uart interface software. Such as: minicom, putty or ssh...
- SSD1306 and I2C lib (MIT)
### Setup Instructions:
1. Clone or download my project from GitHub:
```bash
git@github.com:trungpt0/SnakeGame_BBB.git
cd SnakeGame_BBB
```
2. SSH to BeagleBone Black
3. Connect the hardware
4. Comiple
```bash
make
./main
```
### How to Play
- Up Button (GPIO30 - BBB): Moves the snake up.
- Down Button (GPIO48 - BBB): Moves the snake down.
- Left Button (GPIO60 - BBB): Moves the snake left.
- Right Button (GPIO31 - BBB): Moves the snake right.
## Hardware Connection Diagram
### BeagleBone Black to SSD1306 OLED by i2c-2
|SSD1306|BBB|
|----------|----------|
|SDA|GPIO12|
|SCL|GPIO13|
### BeagleBone Black to buttons
|Button|BBB|
|----------|----------|
|Up button|GPIO30|
|Down button|GPIO48|
|Left button|GPIO60|
|Right button|GPIO31|
## Demo
## Contact
trungtrnminh368@gmail.com
## License
- GPL
- SSD1306 and I2C lib (MIT)