# Build log

Four lines per session, written at the end of the session, not reconstructed later.

1. What I was trying to get working.
2. What actually happened instead.
3. What I changed, and what made me think of it.
4. What I'd tell someone who hit this.

---

## 2026-08-21 — Session 1

1. Followed the tutorial (HowToMechatronics MPU6050) past the point my project needed and ended up printing integrated gyro angles instead of acceleration. Values drifted while stationary, which looked like a broken sensor. It wasn't. A gyro measures rate, not angle, so integrating its small stationary bias makes the total wander without bound. Roll and pitch drifted slowly because the accelerometer corrects them; yaw drifted freely because gravity carries no heading information.
2.
3.
4.