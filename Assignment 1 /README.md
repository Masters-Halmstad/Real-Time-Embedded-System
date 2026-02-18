# ASSIGNMENT 1: Bare-Metal Bit Manipulation and GPIO Control on Raspberry Pi 3

This project covers the fundamentals of Real-Time Embedded Systems by developing bare-metal applications for the Raspberry Pi 3. It is divided into two primary parts: implementing robust bitwise logic for register management and developing firmware to control hardware peripherals (GPIO and UART) without an underlying operating system.

## Key Concepts Learnt
* **Bitwise Operation Encapsulation:** Implementing and documenting functions for setting, clearing, and shifting bits/nibbles within 32-bit registers.
* **Bare-Metal Development:** Writing software that runs directly on the ARM Cortex-A53 hardware, handling initialization and I/O manually.
* **UART Serial Communication:** Managing bidirectional data exchange between the Raspberry Pi and a PC for debugging and user interaction.
* **GPIO Peripheral Control:** Interfacing with BCM2837 hardware registers (Function Select, Set, and Clear) to drive digital outputs like LEDs.
* **Cross-Compilation Workflow:** Using the ARM Embedded Toolchain to build images on a host machine for execution on target hardware.

---

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

### Expected Behavior

#### A1P1 (Register Manipulation)
* **UART Output:** An interactive menu system will appear in your serial terminal at 115200 baud.
* **User Input:** The system will prompt for your name, a 32-bit integer value, specific bit positions, and shift amounts.
* **Display:** The terminal displays the binary representation (as a string) and the decimal values of the registers after manipulation.
* **Operations:** Performs comprehensive testing of bitwise logic functions including `setBit`, `getBit`, `assignNibble`, and bitwise shifts.

#### A1P2 (LED Control)
* **LED Behavior:** The LED will begin blinking continuously at 1-second intervals (0.5s ON, 0.5s OFF).
* **GPIO:** The firmware specifically targets **GPIO16** (Physical Pin 36) for output control.
* **Operation:** The application runs in an infinite loop until the device is powered off.

---

## Connection Requirements

### For A1P1 (UART Communication)
Connect your UART-to-USB adapter to the Raspberry Pi GPIO header using the following pinout:

* **Black (GND):** Pin 6
* **White (TXD):** Pin 8 (GPIO14)
* **Green (RXD):** Pin 10 (GPIO15)

> **⚠️ Important:** DO NOT connect the red VCC cable from the adapter if you are already powering the Raspberry Pi via the micro-USB port.



**Terminal Software Configuration:**
* **Baud rate:** 115200
* **Data bits:** 8
* **Parity:** None
* **Stop bits:** 1
* **Recommended Software:** PuTTY, minicom, or Screen.

---

### For A1P2 (LED Control)
To visualize the output for the second part of the assignment:

* **External LED:** Connect the anode (long leg) to **GPIO16 (Pin 36)** and the cathode (short leg) to **GND (Pin 39)** using a 270Ω current-limiting resistor.
* **Built-in LED:** The firmware is designed to interact with GPIO registers; it can be adapted to use the platform-specific onboard activity LED if an external one is not available.