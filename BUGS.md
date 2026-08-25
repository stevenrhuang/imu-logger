# Build log

---

## 2026-08-21 — Session 1

1. Followed the tutorial (HowToMechatronics MPU6050) past the point my project needed and ended up printing integrated gyro angles instead of acceleration. Values drifted while stationary, which looked like a broken sensor. It wasn't. A gyro measures rate, not angle, so integrating its small stationary bias makes the total wander without bound. Roll and pitch drifted slowly because the accelerometer corrects them; yaw drifted freely because gravity carries no heading information.

## 2026-08-24 — Session 4

1. Believed I was sampling at 100 Hz; was actually at 10.
2. The line (Wire.read() << 8 | Wire.read()) / 4096.0 had two defects that happen to cancel out on an Uno. The two Wire.read() calls sat on opposite sides of |, and C++ doesn't sequence those, so which byte became the high byte was not in my control. And the result never passed through a 16-bit signed type, so negatives only came out right because int on AVR is 16 bits wide and the shift overflowed into the sign bit. On a 32-bit target that second one reports +15 g where the answer is -1 g.

Fixed by reading the six bytes into six uint8_t variables in six separate statements, so queue order is fixed by declared variables rather than by the compiler, and combining each pair into a named int16_t before dividing by 4096, so signedness is declared rather than at random from whatever width the platform gives int.