# ATmega32 driver framework

Bare-metal drivers for the ATmega32A written from the datasheet, without the Arduino core or the avr-libc peripheral helpers. Register maps, interrupt vectors and the `ISR` macro are defined here by hand. Personal project (2023), built with PlatformIO and flashed over USBasp.

## Layers

| Layer | Module | What it does |
|---|---|---|
| MCAL | `DIO` | Pin and port direction, write and toggle |
| MCAL | `TMR0` | Configurable Timer0: a millisecond tick, blocking ms/us delays, PWM duty cycle, frequency setting, overflow and compare callbacks |
| MCAL | `UART` | Init by baud rate, character and string output, `UART_Printf`, and interrupt-driven receive into a circular buffer |
| MCAL | `INT` | Vector names, `SEI`/`CLI` and the `ISR` macro |
| HAL | `LCD` | HD44780 character LCD: init, cursor, `LCD_Printf`, shifting, custom characters |
| LIB | `CircularBuffer`, `string`, `bits`, `datatypes` | Ring buffer used by the UART, a small string library, bit macros and fixed-width types |

`src/main.c` is a demo that uses the timer tick, the UART and the LCD together to run a clock on the display. `test/` holds host-side tests for the circular buffer and string library, and a UART test.

## Build

```
pio run            # build
pio run -t upload  # flash through USBasp
```

The clock is set to 8 MHz in `platformio.ini`.
