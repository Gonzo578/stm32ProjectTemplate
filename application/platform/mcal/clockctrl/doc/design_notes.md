# Clock Control Design Notes

## Responsibilities
MCUs provide a means to control the clock of the system and the various peripherals. This component has the responsibilities:
* Provide a means to initialize the clock tree of the MCU
* Provide certain information about the clock system of the MCU.
* Provide a means to change the configuration of the clocks at runtime (e.g. to optimize MCU power consumption)

As this system can be very MCU specific, the component is hidden behind other interfaces and thus shall *not* be visible to normal application code.