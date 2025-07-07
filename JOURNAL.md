
---
Title: "7 segment LED clock"
Author: "AAruni"
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




July 6 – PCB Layout, Segment Placement & Enclosure Design (9 hours)


![image](https://github.com/user-attachments/assets/cadcaa63-a0ac-43aa-b296-1830bc72a2c5)


With the schematic complete, the next phase was the PCB layout and segment arrangement. I opened the layout editor and placed each of the 7-segment components in a clean 4-digit format, leaving proper space for wiring and dot indicators. I aligned each segment module precisely to maintain consistent digit spacing. Two centre dots were added to separate hours and minutes.




![image](https://github.com/user-attachments/assets/a8f5806a-622e-4162-9f0f-9d017e81ba39)

I began routing the control signals  one pin for each segment per digit, using MOSFETs for current sinking and multiplexing logic. The digit select lines were grouped separately, and every segment had a 220Ω series resistor for current limiting.
![Screenshot 2025-07-07 224607](https://github.com/user-attachments/assets/b64cac68-dfef-4463-b3fe-4677dd74074e)



BRUHH easyeda is baaaad so imported into easyeda pro so i can design case too

Routing the PCB was like solving a puzzle. The top layer handled horizontal signal paths while the bottom managed vertical routes. I used thick traces for power lines and ensured solid ground planes across both layers to minimize noise. GND vias were generously placed to connect planes and stabilize return paths.


![Screenshot 2025-07-07 222436](https://github.com/user-attachments/assets/43cb2654-2dcd-4e64-9175-c60829963159)
![Screenshot 2025-07-07 222512](https://github.com/user-attachments/assets/ab89a64a-54c2-4d50-afba-17df72d48b4e)

![Screenshot 2025-07-07 222519](https://github.com/user-attachments/assets/683002d8-7b4b-496c-bd4d-01975eca4b90)


Once routing was done, I exported the board as a .step file and imported it into Fusion 360. There, I created a custom enclosure — a black PLA case with mounting holes and a faceplate cutout to expose only the segments. The faceplate was designed in white for contrast, with tight tolerances to avoid light bleed. I also left room for USB, buttons, and side vents for future expansion.

![Screenshot 2025-07-07 220132](https://github.com/user-attachments/assets/3b310793-9382-407a-baa5-cde86cd4d76f)



![Screenshot 2025-07-07 221834](https://github.com/user-attachments/assets/fb570ec2-3506-4dd5-939b-26255bfab044)





![Screenshot 2025-07-07 215344](https://github.com/user-attachments/assets/9bb21510-5678-446b-8987-2dc1fa38d2bd)



![Screenshot 2025-07-07 220140](https://github.com/user-attachments/assets/c0d4beb8-f966-4a11-b315-694d4f0d2d21)



![Screenshot 2025-07-07 221844](https://github.com/user-attachments/assets/35a5baa8-6d2f-4704-871a-68eb029f0d86)




To visualize everything together, I created 3D renders — top view, angled views, and even an exploded render showing the layers. The assembly started feeling like a real product, not just a DIY hobby.






![Screenshot 2025-07-07 230028](https://github.com/user-attachments/assets/f956261c-38c7-4c0a-8eef-bad0e8b1c57c)




![Screenshot 2025-07-07 230017](https://github.com/user-attachments/assets/a4c58940-bb1d-4886-8c11-8dddbc09acca)




![Screenshot 2025-07-07 230008](https://github.com/user-attachments/assets/03e09dc3-b5a8-4c07-b4f5-ccae240b9f0f)






## July 7 – BOM, Firmware Setup & Final Touches (5 hours)

Today was mostly focused on wrapping up the project and preparing it for production. I began the day by finalizing the Bill of Materials (BOM).

![Screenshot 2025-07-07 233036](https://github.com/user-attachments/assets/2f9452f9-c269-4075-89e8-7bb451a1e331)


With the BOM ready, I exported the Gerber files from EasyEDA and uploaded them to JLCPCB. I opted for five boards with a black soldermask and HASL finish to match the visual aesthetic I had in mind. For convenience, I selected partial assembly (PCBA) for two of the boards — getting the ATmega328PB, USB port, oscillator, and passive components soldered directly at the factory. This decision saved me from the tedious and error-prone process of hand-soldering fine-pitch QFN parts. The total cost came to around ₹2,000 for the bare PCBs and ₹2,800 for the partially assembled units, excluding shipping. I chose mail  for delivery

 I shifted focus to firmware development. I used the Arduino core for ATmega328PB, which made setting up the code straightforward. The microcontroller was programmed to fetch the current time from the DS3231 real-time clock (RTC) module every second and convert it to HH:MM format. This information was then sent to the display via multiplexing logic. Each digit was refreshed rapidly using a timer interrupt, so that only one digit was active at a time, but all appeared to be constantly illuminated due to persistence of vision.


![image](https://github.com/user-attachments/assets/810e009f-bbb7-470b-977f-47cef854662b)





tried out code given by random yt it kinda kinda worked







For user interaction, I implemented input handling for three buttons. One button incremented the hours, another adjusted the minutes, and the third toggled between RGB color modes for the WS2812 LEDs. All button inputs were debounced in software to ensure smooth performance. The colon LEDs between the hour and minute digits were programmed to blink every second, mimicking the behavior of commercial digital clocks and adding a bit of life to the display. I also integrated simple animations for the WS2812 RGB LEDs, allowing subtle transitions based on the selected color mode.





HOPE IT GETS APPROVED :)
