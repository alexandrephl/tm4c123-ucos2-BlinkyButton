# RTOS Demo on EK-TM4C123GXL (Cortex-M4) — uC/OS-II Active Object

![Board Photo](img/pic_board.jpg)

This project demonstrates a simple real-time system on the EK-TM4C123GXL board using a minimal Active Object (AO) layer on top of **uC/OS-II**.  
It blinks the green LED on a periodic timer and adjusts the blink rate with **SW1** (blue LED indicates button state). The design showcases event-driven AOs, time events, and RTOS tick integration.

---

## 📂 Repository Layout


|  
├── Application/                 # Your application logic (main, bsp)  
|  
├── ucos2/               		     # CMSIS core headers  
|  
├── ucos2_ports/               		     # CMSIS core headers  
|
├── ek-tm4c123gxl/               # Board/Microcontroller-specific files  
|  
├── targetConfig/                # Target Configurations  

---
