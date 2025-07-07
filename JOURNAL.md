
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

![image](https://github.com/user-attachments/assets/43d2f770-c1d1-4707-a493-4a44dd65b1b0)

I started by finalizing the display layout – a 4-digit 7-segment clock showing HH:MM, separated by two dots in the centre. Each digit had 7 LED segments plus a decimal/dot, and each segment was essentially a bar-shaped LED board controlled via a transistor or direct GPIO through multiplexing. This meant a total of 7×4 + 2 = 30 LEDs, each requiring control logic.

![image](https://github.com/user-attachments/assets/00cf3483-2320-4484-8547-2b0d85f35e52)

![image](https://github.com/user-attachments/assets/78fc5e2d-144e-48dc-9aad-2199e6bd4346)



At the heart of the circuit lies the ATmega328PB-AU microcontroller, selected for its Arduino compatibility and ease of programming via UART. The chip was set up on a custom PCB, powered through a clean +5V rail. A pair of 100nF decoupling capacitors stabilized the VCC and AVCC lines, and the AREF pin was also filtered using a capacitor to suppress noise. For timing, I used a 12MHz crystal oscillator with two 22pF capacitors, connected to the XTAL1 and XTAL2 pins. This ensured accurate clock cycles needed for real-time clock polling and multiplexing refreshes.

The reset circuitry involved a 10kΩ pull-up resistor and a 100nF capacitor connected to the DTR line. This allows firmware upload via USB-to-serial converter modules by automatically triggering a reset when flashing code from the Arduino IDE or PlatformIO.



![image](https://github.com/user-attachments/assets/b425dbdf-a511-420e-ab6c-61fd7c232654)




For timekeeping, I interfaced an I2C-based RTC sensor, likely the DS3231 module. The SDA and SCL lines from the RTC were connected to pins PC4 and PC5 on the ATmega328PB. The microcontroller polls the time regularly and updates the display in real time.

Three push buttons were included — one to increment hours, another for minutes, and a third to toggle LED color modes. These buttons connect to PD2, PD3, and PD4, with either internal pull-ups or external resistors as per layout. The input detection was debounced in code to ensure reliable switching.


![image](https://github.com/user-attachments/assets/e869a9ae-2732-4883-960f-e983094ca994)



For the visual aspect, I added a WS2812 RGB LED chain, connected to pin PD7. These addressable LEDs would add ambient underglow or animated effects behind the digits. Since WS2812s need a clean 5V logic signal, I connected them directly to the ATmega’s I/O without level shifting, keeping the track short to avoid signal issues.


![image](https://github.com/user-attachments/assets/76eac9bc-607e-4945-9c55-0e8321224d3c)


Lastly, UART pins (TX/RX) were routed for firmware updates and serial debugging. Everything was built as a standalone system no Arduino boards involved  giving me a compact, powerful, and easily programmable digital clock setup.



![image](https://github.com/user-attachments/assets/666b9f1b-29ea-4d18-9246-350ee95f38ff)



After reviewing the full schematic in EasyEDA and checking all labels, nets, and power filtering, I finalized the design. The combination of robust microcontroller logic and clean power design laid the perfect foundation for the rest of the build.

![image](https://github.com/user-attachments/assets/14312cb9-e571-4a8b-8f48-d56590632244)




By the end of this session, I had a full schematic ready: RTC timekeeper, USB-C interface, and transistor-driven 7-segment LEDs. All symbols, labels, and nets were double-checked.


![image](https://github.com/user-attachments/assets/810e009f-bbb7-470b-977f-47cef854662b)

tried out code given by random yt it kinda kinda worked

