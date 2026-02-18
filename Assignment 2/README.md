# ASSIGNMENT 2: PiFace Control, Taylor Expansion, and Manual Task Interleaving

This assignment focuses on enhancing Raspberry Pi bare-metal programming skills by interfacing with the PiFace Control and Display hardware, implementing mathematical algorithms (Taylor Expansion), and exploring concurrency through manual task interleaving.

## Key Concepts Learnt
* **Peripheral Interfacing:** Utilizing a C library to control the PiFace Control and Display for visual data output.
* **Algorithm Implementation:** Developing a Taylor Expansion function to calculate exponential values without standard math libraries.
* **Fixed-Point Data Representation:** Using custom structures (`ExpStruct`) to handle integer and fractional parts of calculations in a bare-metal environment.
* **Manual Interleaving:** Designing a mechanism to manage multiple tasks (LED blinking and mathematical computation) to ensure consistent timing without an Operating System.
* **I/O Extension:** Using GPIO headers to simultaneously manage the PiFace display and external components like LEDs.

---

## Hardware Requirements
* **Raspberry Pi 3 (RPi3) or Raspberry Pi 3B+**
* **PiFace Control and Display** module
* **GPIO Extension Header** (required to connect external LED while PiFace is attached)
* **External LED and 270Ω Resistor** (for Part 3)
* **SD card** for image deployment (FAT32 boot partition)
* **Power supply** (5V, minimum 2.5A recommended)

## Build Requirements
* **ARM cross-compilation toolchain** (`gcc-arm-none-eabi`)
* **GNU Make** utility
* **Linux/WSL environment**
* **Project Libraries:** `piface.h`, `expstruct.h`, `led.h`, and `rpi-systimer.h`

## Toolchain Setup
To install the necessary tools, run:
```bash
sudo apt update
sudo apt install gcc-arm-none-eabi make
```
## Running the Applications

### Deployment
1.  **Generate the Image**: Run the `make` command in the project directory to create the `.img` file (e.g., `rteskernel.img`).
2.  **Transfer**: Copy the resulting `.img` file to the boot partition of your SD card.
3.  **Configure**: Update the `config.txt` file on the SD card by adding the line: `kernel=your_file_name.img`.
4.  **Boot**: Insert the SD card into the Raspberry Pi 3 and power on the device.

---

### Expected Behavior

#### A1P1 (Register Manipulation)
* **UART Output**: An interactive menu system will appear in your serial terminal at 115200 baud.
* **User Input**: The system will prompt for your name, 32-bit integer values, bit positions, and shift amounts.
* **Display**: The terminal will display the binary representation (as a string) and the decimal values of the manipulated registers.
* **Operations**: Performs comprehensive testing of bitwise logic functions including `setBit`, `getBit`, `assignNibble`, and bitwise shifts.

#### A1P2 (LED Control)
* **LED Behavior**: Continuous blinking at 1-second intervals (0.5s ON, 0.5s OFF).
* **GPIO**: Specifically uses **GPIO16 (Physical Pin 36)** for output control.
* **Operation**: The firmware runs in an infinite loop until the device is powered off.

---

## Connection Requirements

### For A1P1 (UART Communication)
Connect your UART-to-USB adapter to the following Raspberry Pi GPIO pins:

| Adapter Wire | RPi Pin | Function |
| :--- | :--- | :--- |
| **Black (GND)** | Pin 6 | Ground |
| **White (TXD)** | Pin 8 | GPIO14 (TX) |
| **Green (RXD)** | Pin 10 | GPIO15 (RX) |



> **⚠️ Important**: DO NOT connect the red VCC cable from the adapter if you are already powering the Raspberry Pi via the micro-USB port.

**Terminal Software Configuration**:
* **Baud rate**: 115200
* **Data bits**: 8
* **Parity**: None
* **Stop bits**: 1
* **Software**: PuTTY, minicom, or VS Code Serial Monitor.

### For A1P2 (LED Control)
To visualize the output for the second part of the assignment:

* **External LED**: Connect the anode (longer leg) to **GPIO16 (pin 36)** and the cathode (shorter leg) to **GND (pin 39)** using a 270Ω current-limiting resistor.
* **Built-in LED**: The firmware is designed for GPIO registers and can be adapted to use platform-specific activity LEDs.