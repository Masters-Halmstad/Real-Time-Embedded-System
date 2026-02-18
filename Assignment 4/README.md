# Assignment 4: Preemptive Multitasking, Mutual Exclusion, and Real-Time Scheduling

This documentation covers the implementation of a bare-metal preemptive kernel on the **Raspberry Pi 3**. The project evolves from a basic cooperative switcher into a sophisticated Real-Time Operating System (RTOS) capable of handling mutual exclusion and deterministic scheduling.

---

## 📘 Objective
The primary goal of this assignment is to transition from cooperative multitasking (where threads voluntarily yield) to a **fully preemptive system**. 

**Learning Goals:**
### Real-Time Embedded Systems: Synchronization and Scheduling

In a preemptive embedded system like the one implemented on the Raspberry Pi 3, multiple tasks compete for the processor and shared hardware. This necessitates robust synchronization to prevent data corruption and deterministic scheduling to meet real-time deadlines.

### 1. Synchronization via Mutexes
In a multitasking environment, a **Shared Resource** (like the PiFace Display or a global variable) can only be safely accessed by one thread at a time. If two threads attempt to write to the display simultaneously, the output becomes garbled—a condition known as a **Race Condition**.

#### The Mutex Mechanism
A **Mutex** (Mutual Exclusion object) acts as a digital lock. It consists of:
* **State:** Locked or Unlocked.
* **Owner:** The thread currently holding the lock.
* **Waiting Queue:** A list of threads that tried to acquire the lock while it was busy.

**Implementation Logic:**
1.  **Locking (`lock`):** When a thread calls `lock()`, the system checks the state. If unlocked, the thread takes ownership and continues. If locked, the thread is removed from the `readyQ` and placed in the mutex's `waitingQ`. This blocks the thread, preventing it from wasting CPU cycles while waiting.
2.  **Unlocking (`unlock`):** When the owner calls `unlock()`, the system checks the `waitingQ`. If there are blocked threads, it moves one back to the `readyQ`. If the queue is empty, it simply sets the state to unlocked.



---

### 2. Real-Time Scheduling
Scheduling determines which thread gets the CPU at any given time. In real-time systems, the goal isn't just "fairness" (like Round Robin), but **predictability** and **guaranteeing deadlines**.

#### A. Rate Monotonic (RM) Scheduling
RM is a **Static Priority** algorithm used for periodic tasks. The priority is assigned once at design time and does not change.

* **The Rule:** The shorter the task's period ($T$), the higher its priority.
* **Logic:** A task that must run every 10ms is more "urgent" than a task that runs every 100ms. 
* **Implementation:** In `tinythreads.c`, when a timer interrupt occurs, the scheduler scans the `readyQ` and selects the task with the smallest `Period`.
* **Best For:** Simple, predictable systems where task parameters are known in advance.



#### B. Earliest Deadline First (EDF) Scheduling
EDF is a **Dynamic Priority** algorithm. Unlike RM, priorities change at runtime based on the proximity of a task's deadline.

* **The Rule:** The task with the absolute earliest deadline ($d$) gets the highest priority.
* **Logic:** Even if Task A has a longer period than Task B, if Task A's deadline is only 2ms away while Task B's is 5ms away, Task A is dispatched first.
* **Implementation:** * Each task has a `deadline` value.
    * At every timer tick, the system decrements the `deadline` of all active tasks.
    * The `readyQ` is resorted so that the task with the smallest remaining deadline is at the head.
* **Best For:** High-utilization systems. Theoretically, EDF can reach 100% CPU utilization while still meeting all deadlines, whereas RM is limited to roughly 69% for many tasks.



---

## ⚖️ Comparison Summary

| Feature | Mutex | Rate Monotonic (RM) | Earliest Deadline First (EDF) |
| :--- | :--- | :--- | :--- |
| **Purpose** | Resource Protection | Task Prioritization | Task Prioritization |
| **Priority Type** | N/A | Static (Fixed) | Dynamic (Changes) |
| **Key Metric** | Ownership state | Period ($1/T$) | Absolute Deadline |
| **Overhead** | Low (Queue management) | Low (Sort by fixed period) | High (Continuous recalculation) |
| **System Load** | Prevents race conditions | Works up to ~69% load | Works up to 100% load |

---

## 🏗️ Project Overview
The system utilizes a modified **Tinythreads** library. In this architecture, a hardware timer generates periodic interrupts that invoke the scheduler. The scheduler manages a "Ready Queue" and decides which thread to dispatch based on the active scheduling policy. 

The project is structured into three distinct phases:
1.  **Part 1:** Preemption via Timer Interrupts + Round Robin Scheduling + Mutexes.
2.  **Part 2:** Static Priority Scheduling using the Rate Monotonic (RM) algorithm.
3.  **Part 3:** Dynamic Priority Scheduling using the Earliest Deadline First (EDF) algorithm.

---

## 🧠 Key Concepts Explanation

### 1. Preemptive Multitasking
Preemption is achieved by programming the **ARM Timer** to trigger an Interrupt Request (IRQ) at regular intervals. 
* **Register-level Detail:** The `Load` register is set to `0xF3C` with a 256 prescaler to achieve a ~1-second heartbeat.
* **Context Switching:** When the interrupt occurs, the CPU saves the current thread's state (registers/stack pointer) and jumps to the kernel's dispatcher.

### 2. Mutual Exclusion (Mutex)
Since multiple threads attempt to write to the PiFace Display simultaneously, a **Mutex** is implemented to prevent interleaved or corrupted output.
* **Locking:** If a thread calls `lock()` and the mutex is held, the thread is moved to a `waitingQ` and blocked.
* **Unlocking:** `unlock()` releases the resource and moves the next blocked thread back to the `readyQ`.



### 3. Scheduling Algorithms
* **Round Robin (RR):** A simple circular queue where each task receives an equal time slice.
* **Rate Monotonic (RM):** A static priority algorithm where tasks with shorter periods are assigned higher priorities. 
* **Earliest Deadline First (EDF):** A dynamic algorithm where the task closest to its absolute deadline is moved to the head of the queue.



---

## 💻 Expected Behavior

### 🔹 Part 1 – Round Robin & Mutexes
* **Runtime:** Four threads perform exponential calculations and print to the four segments of the PiFace.
* **Observation:** With the Mutex implemented, the display output is stable. Without it, digits would "flicker" or overwrite each other. The timer interrupt causes the "active" segment to rotate every second.

### 🔹 Part 2 – Rate Monotonic (RM)
* **Runtime:** Tasks are spawned with fixed periods (e.g., 2, 5, and 10 seconds).
* **Observation:** The scheduler ensures the task with the smallest period (highest frequency) runs with the highest priority. The PiFace displays the "ticks" or progress of each task according to its period.

### 🔹 Part 3 – Earliest Deadline First (EDF)
* **Runtime:** Tasks have dynamic deadlines that are updated as time passes.
* **Observation:** The task whose deadline is closest to the current time takes precedence. If the system is overloaded (high utilization), the user will observe tasks missing deadlines on the display.

---

## 🛠️ Hardware Requirements

| Component | Specification / Connection |
| :--- | :--- |
| **Target Board** | Raspberry Pi 3 (Model B/B+) |
| **Processor** | Broadcom BCM2837 (ARMv8) |
| **Display** | PiFace Control and Display (SPI Interface) |
| **Timer** | ARM Side Timer (Integrated BCM2835 peripheral) |
| **Power** | 5V 2.5A Micro-USB Power Supply |

---

## ⚙️ Technical Details

### Memory-Mapped I/O & Registers
The kernel interacts directly with peripheral registers:
* **Interrupt Controller:** `0x3F00B200` (Base) - Used to enable `RPI_BASIC_ARM_TIMER_IRQ`.
* **ARM Timer:** `0x3F00B400` (Base) - Configured via `Control` and `Load` registers.
* **Instruction Set:** Uses `cpsie i` and `cpsid i` for atomic operations during queue manipulation.

### Toolchain & Build
* **Compiler:** `arm-none-eabi-gcc`
* **Flags:** `-O0` (to prevent optimization of timing loops), `-march=armv8-a`, `-nostartfiles`.
* **Boot Process:** The code is compiled into a `kernel8.img` and loaded onto a FAT32 SD card.

---

## 📂 Project Structure
```text
.
├── a4p1.c           # Main application for Round Robin/Mutex testing
├── a4p2.c           # Main application for Rate Monotonic testing
├── a4p3.c           # Main application for EDF testing
├── tinythreads.c    # Kernel core (ReadyQ, Mutex, Scheduler logic)
├── tinythreads.h    # TCB structures and kernel API
├── rpi-armtimer.c   # ARM Timer hardware drivers
├── piface.c         # Display drivers for hardware feedback
└── Makefile         # Build automation
```
## Output
### Output of Rate Monotonic
<div align="center">
  <video src="https://github.com/Masters-Halmstad/Real-Time-Embedded-System/blob/main/Assignment%204/Output/A4P2.mp4" width="400" controls>
  </video>
</div>

### Output of EDF
<div align="center">
  <video src="./Output/A4P3.mp4" width="400" controls>
  </video>
</div>
