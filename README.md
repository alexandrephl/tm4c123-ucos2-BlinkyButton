# RTOS Demo on EK-TM4C123GXL (Cortex-M4) — uC/OS-II Active Object

![Board Photo](img/pic_board.jpg)

This project demonstrates a simple real-time system on the EK-TM4C123GXL board using a minimal Active Object (AO) layer on top of **uC/OS-II**.  
It blinks the green LED on a periodic timer and adjusts the blink rate with **SW1** (blue LED indicates button state). The design showcases event-driven AOs, time events, and RTOS tick integration.

---

## Repository Layout


|  
├── Application/                 	# Your application logic (main, bsp, uc_ao...)  
|  
├── ucos2/               		    # µC/OS-II kernel sources  
|  
├── ucos2_ports/               		# µC/OS-II port for Cortex-M4  
|  
├── ek-tm4c123gxl/               	# Board/Microcontroller-specific files  
|  
├── CMSIS/               		    # CMSIS core headers  
|  
├── targetConfig/                	# CCS Target Configurations  

---

## Build & Run Instructions

### Prerequisites

- **Code Composer Studio (CCS)** or GCC ARM toolchain  
- **TivaWare SDK** (not included in repo)  
- **µC/OS-II (V2.93)** included in this repo under ucos2/
- **CMSIS headers** (either from this repo or your local installation)

### To Build:

1. **Import project**:
  - `File → Import CCS Projects` → select this repo’s root folder.
2. **Tivaware path setting**:
	-When prompted, set build variable in Project Properties → C/C++ Build → Build Variables:
		•	Name: TIVAWARE_ROOT
		•	Value: your TivaWare path (e.g. C:/ti/TivaWare_C_Series-2.2.0.295)
3. **Build and flash** — connect the LaunchPad, flash via CCS.
	- Connect the LaunchPad via USB  
	- Click the debug icon or *Run → Debug* to flash and start execution.
   
## License & Credits

	- Main application code: MIT (see `LICENSE.txt`)
	- Third-party components and their licenses: see `THIRD_PARTY_NOTICES.md`

## Author
**Alexandre Panhaleux**  
Embedded Software Engineer  
[GitHub: @alexandrephl](https://github.com/alexandrephl)
