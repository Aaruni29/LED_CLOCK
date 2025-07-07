
---
Title: "7 segment LED clock"
Author: "Hewis44"
Description: "A OLD STYLE CLOCK"
created_at: "2025-07-06"
Total time spent: "21"

---

July 5 – Ideation, Schematic Design & Core Logic (7 hours)


![image](https://github.com/user-attachments/assets/d0392ddf-1f4b-45b5-a192-beb6ae33214f)

This whole idea began when I was browsing some retro LED displays online. I saw those large-format wall clocks and thought, "Why not build my own digital clock with bold 7-segment digits?" I didn’t want to use the typical TM1637 or MAX7219 modules – they felt too generic. I wanted to build every segment myself, bit-by-bit, and design the full custom PCB, schematic, and enclosure. This would give me full control over the aesthetics and the logic.


I started by finalizing the display layout – a 4-digit 7-segment clock showing HH:MM, separated by two dots in the centre. Each digit had 7 LED segments plus a decimal/dot, and each segment was essentially a bar-shaped LED board controlled via a transistor or direct GPIO through multiplexing. This meant a total of 7×4 + 2 = 30 LEDs, each requiring control logic.

Once the basic concept was clear, I opened EasyEDA and dropped in the main controller – the RP2040. It’s powerful, dual-core, and perfect for precise timing like that required for clock updates and LED refresh rates. I added basic power filtering – 100nF decoupling caps near every VCC line, a 12MHz crystal oscillator with two 15pF capacitors for stable timing, and a QSPI flash chip (W25Q128) since the RP2040 doesn’t come with onboard flash. The USB-C circuitry followed next – 5.1kΩ pull-downs on the CC lines, ESD diodes for protection, and a 3.3V LDO regulator (AMS1117/LD1117) to power the RP2040 from USB.

The schematic started taking shape. For each segment, I used N-channel MOSFETs for switching, so the RP2040 would only sink current when a segment is ON. I added resistors (220Ω) in series with every segment to limit the current. Every digit had its own common cathode control pin, enabling multiplexing. That way, only one digit is active at a time, but all digits appear to be lit due to persistence of vision.

I also included a basic RTC module (DS3231) in the schematic, communicating via I2C. This way, even if power is cut off, the clock time is maintained thanks to the onboard battery of the RTC module. I finished the schematic by adding an AMS1117 3.3V regulator for the logic side and one more for clean power to LEDs if needed.

By the end of this session, I had a full schematic ready: RTC timekeeper, USB-C interface, and transistor-driven 7-segment LEDs. All symbols, labels, and nets were double-checked.


![image](https://github.com/user-attachments/assets/810e009f-bbb7-470b-977f-47cef854662b)

tried out code given by random yt it kinda kinda worked

