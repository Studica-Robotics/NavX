# StudicaLib Releases and Issue Tracker

## Studica Hardware Manager

Used for updating and configuring all Studica electronics.

### Downloads

> [!NOTE]
> The downloads are ~120 MB to ~550 MB

> [!IMPORTANT]
> There is a bug in the 1.1.0 version of the software that may cause issues updated for some people. A manual installation is required of the latest below!

**Windows 64-bit**: [Download](https://dev.studica.com/maven/release/firmware/app/win32/Studica_Hardware_Manager-Setup_1.1.5.exe)

**macOS**: [Download](https://dev.studica.com/maven/release/firmware/app/macOS/Studica_Hardware_Manager-Setup_1.1.5.pkg) 

**Linux (arm64)**: [Download](https://dev.studica.com/maven/release/firmware/app/amd64/Studica_Hardware_Manager-Setup_1.1.5.deb)

### Supported Devices
* navX-micro
* navX-mxp
* navX2-micro
* navX2-mxp
* navX3-CAN
* vmx
* vmx2
* Titan
* Servo Manager
* Parsec
* Colore

## WPILib StudicaLib Vendordep

> [!IMPORTANT]
> Please update your devices to:
> - navX3-CAN -> 5.0.7
> - Parsec -> 1.0.4
> - Colore -> 1.0.3

### API Links

**Java**: [API](https://dev.studica.com/maven/release/APIDocs/Java/)

**C++**: [API](https://dev.studica.com/maven/release/APIDocs/CPP/)

### Changelog

**v2027.0.0-alpha-1**
- Rewritten for WPILib 2027 (2027.0.0-alpha-7) and SystemCore
- Added support for Parsec and Colore over CAN, CAN FD and USB
- Added CAN FD for all devices; switch a SystemCore bus with `CanBus.requestMode()`
- USB devices are found on any port and can be moved between ports while running; use `UsbPort` to pick a port
- Any number of each device can be used at once
- NavX3 sample timestamps for pose estimation over CAN FD and USB (`getTimestamp()`)
- Colore colour learning and matching (`learnColor()`, `getMatch()`)
- Simulation support for NavX3, Parsec and Colore
- **Breaking:** new NavX3 API. Getters return an `Optional` that is empty until data arrives, and commands return a `Status`
- **Breaking:** NavX3 angular velocity is now reported correctly in radians per second
- **Breaking:** C++ headers are now `.hpp` (`#include "studica/Navx.hpp"`)

<details>
<summary>NavX3 changes from 2026 (C++ uses the same names in PascalCase)</summary>

| 2026 | 2027 |
|---|---|
| `new Navx(id)`, `new Navx(id, rate)` | `new Navx(canId)`, `new Navx(canId, CANPort.CAN_S0, rate)` |
| `new Navx(Navx.Port.kUSB1)` | `Navx.usb()` or `Navx.usb(UsbPort.USB1)` |
| `destroy()` | `close()` |
| `getQuat6D()`, `getQuat9D()` | `getQuaternion6d()`, `getQuaternion9d()` |
| `getAngularVel()` | `getAngularVelocity()` |
| `getLinearAccel()` | `getLinearAcceleration()` |
| `getCompass(float[])` | `getMagneticField()` (microtesla) |
| `getAlgoStates(float[])` | `getAlgorithmState()` |
| `getSensorUUID(int[])` | `getSensorUuid()` |
| `selfTest(int[])` | `selfTest()` |
| `setODRHz(hz)` | `setOutputRate(hz)` |
| `enableOptionalMessages(...)` | `enableMessages(Navx.Message...)` |
| `enable9DYaw(bool)` | `use9AxisYaw(bool)` |

</details>

<br>

**v2026.0.2**
- Added support for USB comms with NavX3

**v2026.0.1**
- Added support for simulation with NavX3
- Background CAN gets no longer cause crashes with incorrect board firmware's
- Added json conflict check to ensure lib is not used at same time as the other lib

**v2026.0.0**
- Added support for NavX3-CAN
- Uses WPILib Units
- Javadoc added for robotpy

### Direct JSON Link

For those that wish to use the old method of importing vendordeps, the JSON is here:

```
https://dev.studica.com/maven/release/2027/json/StudicaLib.json
```