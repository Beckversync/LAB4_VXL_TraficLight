# ⏱️ STM32 Timer Driver Test Suite 🚀

Welcome to the **STM32 Timer Driver Test Suite**! 🛠️ This project showcases a robust and efficient timer driver for the STM32 microcontroller, featuring multiple concurrent timeouts and accurate callback scheduling. Let’s dive in! 🌊

---

## 🎯 Objectives

- 🕒 **10ms Timer Tick:** Ensure a regular 10ms timer tick for accurate scheduling.
- 🔁 **Callback Registration:**
  - Register a timeout to fire a callback **every 10ms**.
  - Print the timestamp from `get_time()` **every time the callback triggers**.
  - Ensure timestamps are accurate to at least **10ms precision**.
- 🧑‍🤝‍🧑 **Multiple Concurrent Timeouts:** Register another timeout at a **different interval (e.g., 500ms)** and run both timeouts concurrently.
- ⏳ **Delayed Task Scheduling:**
  - Use `SCH_Add_Task()` to schedule several callbacks.
  - Ensure delays are long enough so the **main loop enters before wake-ups occur**.
  - Print the **current timestamp when each delay expires**.

---

## ❌ Unsatisfactory Designs

Avoid the following issues in your implementation:

- ❌ Supporting **only one registered timeout** at a time.
- ❌ **Out-of-order callback delivery**.
- ❌ Inefficient **O(n) searches** in `SCH_Update()`.
- ❌ **Interrupt frequencies over 10Hz** with a regularly ticking timer.

---

## 📝 Test Plan

1. **Set Up Timer:** Initialize a **10ms periodic timer interrupt**.
2. **Register Callbacks:**
   - Callback 1: Fires **every 10ms**, prints timestamp.
   - Callback 2: Fires **every 500ms**, prints timestamp.
3. **Add Scheduled Tasks:**
   - Use `SCH_Add_Task()` to add several delayed callbacks.
   - Ensure tasks wake up in the **correct order**.
4. **Verify Output:** Ensure timestamps are **accurate** and **callbacks fire on time**.

---

## 🚀 How to Run

1. **Clone this repository** 📥
2. **Flash the STM32 code** onto your development board ⚡
3. **Observe the console output** and validate timestamps 🖥️

---

👥 **Contributors:**
- Your Name Beckversync

📝 **License:**
HCMUT
