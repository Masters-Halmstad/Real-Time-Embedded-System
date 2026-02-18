# Real Time Embedded System - Assignment

This course assignment covers the fundamentals of Real-Time Embedded Systems to the implementation of a bare-metal preemptive kernel by developing bare-metal applications for the Raspberry Pi 3. It started with the general introduction of bit manipulation in assignment 1 to the advance concept and
implimentation of multitasking using Rate Monotnic Scheduling to Eearliest Deadline First Dynamic scheduling. 

## Assignment Details and Output 
Refer the README file of each assignment. 

## Hardware Requirements
* **Raspberry Pi 3 (RPi3) or Raspberry Pi 3B+**
* **UART connection** for `a1p1` project (115200 baud, 8N1)
* **GPIO access** for LED control in `a1p2`
* **SD card** for image deployment (FAT32 boot partition)
* **Power supply** (5V, minimum 2.5A recommended)
* **Electronic Components:** 270Ω resistor, LED, and breadboard cables

## Build Requirements
* **ARM cross-compilation toolchain** (`gcc-arm-none-eabi`)
* **GNU Make** utility
* **Linux/WSL environment** (recommended for build stability)
* **Hardware-specific definitions** for RPi3 (e.g., `rpi-gpio.h`, `rpi-systimer.h`)

## Toolchain Setup
To install the necessary tools on a Debian-based system (like Ubuntu or WSL), run:
```bash
sudo apt update
sudo apt install gcc-arm-none-eabi make
```
## Running the Applications

### Deployment
1. **Generate the Image:** Run the `make` command in the project directory to create the `.img` file (e.g., `a1p1.img` or `a1p2.img`).
2. **Transfer:** Copy the resulting `.img` file to the boot partition of your SD card.
3. **Configure:** Rename the file to `kernel7.img` (the default for RPi3) or update the `config.txt` file on the SD card by adding the line: `kernel=your_file_name.img`.
4. **Boot:** Insert the SD card into the Raspberry Pi 3 and power on the device.


---