# IMU Logger v0

A waist-mounted device that detects footstrikes from accelerometer data
and displays live running cadence in steps per minute.

Arduino Uno · MPU-6050 · SSD1306 OLED · I²C

**Status:** in development, August 2026.

---

## 1. What it measures, and why I cared

_(TBD)_

## 2. The device

_(photo of the real thing on my waistband)_

## 3. The signal

_(serial plot showing my own footsteps)_

## 4. Design decisions

| Decision | Reason |
|---|---|
| ±8 g range, not ±2 g | _(TBD)_ |
| 200 ms refractory window | _(TBD)_ |
| Waist mount, not wrist | _(TBD)_ |
| 2 Hz display refresh | _(TBD)_ |
| `millis()` loop timing | _(TBD — this is a stated limitation, not a defence)_ |

## 5. Validation

| Run | Pace | Hand count | Device count | Error |
|---|---|---|---|---|
| 1 | easy | | | |
| 2 | steady | | | |
| 3 | fast | | | |

## 6. What broke, and how I fixed it

_(see BUGS.md — the good ones get promoted here)_

---

## Known limitations of v0

- Sample interval is not fixed; it drifts when the loop body runs long.
- No raw data logging.
- Validated over three intervals rather than ten.

v1 (November 2026) addresses all three.