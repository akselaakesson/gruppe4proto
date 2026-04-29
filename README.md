# gruppe4proto
# Arduino Race Timer & Servo Gate Project

An integrated timing system featuring dual 7-segment displays (for elapsed and ideal time), a photoresistor-based finish line, and a servo-actuated starting gate.

---

## 👥 The Team
This project was a collaborative effort by:
* **AP**
* **SH**
* **EP**
* **SS**
* **HH**

---

## 🛠️ Technical Details
* **Displays:** 74HC595 Shift Register control for 7-segment LEDs.
* **Actuator:** SM-S2309S Servo Motor (Starting Gate).
* **Sensor:** Photoresistor (Finish Line trigger).
* **Logic:** Real-time millisecond tracking with random "Ideal Tid" generation.

---

## 🤖 AI Attribution & Credits
We utilized several AI tools to assist in the development, logic optimization, and troubleshooting of this project:

* **Gemini (Google):** Assisted with the final code integration, resolving hardware pin conflicts (specifically moving the Servo to Pin 11 to avoid Shift Register interference), and hardware safety guidance (resistors and power management).
* **ChatGPT (OpenAI):** Aided in the initial logical framework and the development of the timing sequences.
* **Claude (Anthropic):** Assisted with code refinement, debugging the state-machine logic, and documentation.

---

## 📜 Libraries Used
* `<Servo.h>` - Standard Arduino library for PWM motor control.

---

## 🚀 How it Works
1. **Reset:** The system waits for the Start Button.
2. **Start:** The Servo moves to the "Open" position, and the timer begins.
3. **Run:** The display updates in real-time while the photoresistor monitors the finish line.
4. **Stop:** Once the light threshold is broken on the sensor, the timer stops and "freezes" the final time.
