# gruppe4proto - RULLBALL
# Arduino IDE 2.3.7

---

## The Team
Dette prosjektet er et sammarbeid av:
* **Signe Hemmersam**
* **Aksel Åkesson**
* **Helle Husby**
* **Elliot Beere**
* **Synne Syrstad**

---

##  Tekniske detaljer
* **Displays:** 4 74HC595 Shift Registere er daisy chained for å kontrollere 4 7-segment displays. Dette er gjort 2 ganger, 1 til hvert display.
* **Actuatorer:** SM-S2309S Servo Motor (Startport), 2 stk js-tgz-u1 lineære aktuatorer (justerer banen opp og ned)
* **Sensor:** Photoresistor (mållinje sensor).
* **Annen hardwear** 2 stk 2 modul releer brukes for å styre hver sin lineære aktuator.
---

##  AI kreditt
Vi har brukt en del AI til assistanse i utviklingen av koden,logiske optimaliseringer, og troubleshooting av projektet
* **Gemini (Google)**
* **ChatGPT (OpenAI)**
* **Claude (Anthropic)**

---

##  Biblioteker
* `<Servo.h>` - Standard Arduino library for PWM motor control.
