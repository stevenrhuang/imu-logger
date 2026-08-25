# Build log

---

## 2026-08-21 — Session 1

1. Followed the tutorial (HowToMechatronics MPU6050) past the point my project needed and ended up printing integrated gyro angles instead of acceleration. Values drifted while stationary, which looked like a broken sensor. It wasn't. A gyro measures rate, not angle, so integrating its small stationary bias makes the total wander without bound. Roll and pitch drifted slowly because the accelerometer corrects them; yaw drifted freely because gravity carries no heading information.

## 2026-08-24 — Session 4

1. Believed I was sampling at 100 Hz; was actually at 10.