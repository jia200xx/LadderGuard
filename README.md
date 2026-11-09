## LadderGuard

~~ About the Project ~~

For natHacks 2026, we made a program that uses the Arduino Nano 33 BLE's built-in accelerometer to monitor a ladder's angle and sudden movements. The idea is to warn someone if the ladder is positioned at a dangerous angle or moves unexpectedly.

~~ Overview ~~

- Reads acceleration values from the Arduino's built-in sensor.
- Calculates the ladder's angle using those readings.
- Checks whether the angle is between 65° and 85°.
- LED is green when the ladder is safe, LED displays red when the angle is unsafe.
- Detects sudden movements and keeps the warning active for 1.5 seconds.
- Lets us mute the buzzer during setup of the ladder using a switch.
- LEDs are used during setup to ensure ladder is at a safe angle

~~ Running the code ~~

1. Open Arduino IDE.
2. Install Arduino Mbed OS Nano Boards
3. Install the `Arduino_LSM9DS1` library.
4. Open our Arduino code (.ino file).
5. Select Arduino Nano 33 BLE as the board.
6. Connect the Arduino to a laptop/powerbank and upload the code.

~~ Testing ~~

We tested the angle detection by tilting the Arduino and checking whether the LEDs and buzzer responded. We also moved the Arduino suddenly, while in the safety threshold, to test the movement detection. After that, we added the switch and checked that it could mute the buzzer while the rest of the program continued running.

~~ Libraries Used ~~ 

1. `Arduino_LSM9DS1` – Used to read the accelerometer.
2. `math.h` – Used for angle and movement calculations.

~~ Demonstration Link and References ~~

Link: https://canva.link/4dzt289r9sej0tw

References:
[1] https://www.cdc.gov/niosh/falls/ladder/index.html
[2] https://canadasafetycouncil.org/ladder-safety-starts-at-home/
[3] https://www.sciencedirect.com/science/article/pii/0022437592900358

~~ Credits ~~ 

Developed by our team during natHacks 2026.

Team members: Jia Ahuja, Zara Mustafa, Nour Barakat, Haniya Altaf, George Jia, Deetya Kumar

Additional coding assistance and resources: AI (ChatGPT)
