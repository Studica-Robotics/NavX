# NavX Releases and Issue Tracker

## Studica Hardware Manager

Used for updating and configuring all Studica electronics.

### Downloads

> [!NOTE]
> The downloads are ~220 MB to ~550 MB

**Windows 64-bit**: [Download](https://dev.studica.com/maven/release/firmware/app/win32/Studica_Hardware_Manager-Setup_1.1.0.exe)

**macOS**: [Download](https://dev.studica.com/maven/release/firmware/app/macOS/Studica_Hardware_Manager-Setup_1.1.0.pkg) 

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

## WPILib StudicaLib Vendordep

> [!NOTE]
> The Vendordeps StudicaLib and Studica cannot be used at the same time!

> [!IMPORTANT]
> Please update your navX3-CAN to a min version of 5.0.4!

### Changelog

**v2026.0.0**
- Added support for NavX3-CAN
- Uses WPILib Units
- Javadoc added for robotpy

## WPILib Studica Vendordep (deprecated for 2027)

> [!NOTE]
> The Vendordeps StudicaLib and Studica cannot be used at the same time!

### Changelog

**v2026.0.0**
- Compiled for 2026

**v2025.0.0**
- Switched to a Driver / JNI setup. This should increase performance for Java teams. 
- Renamed vendordep to Studica.
    Results in new imports:
    ```Java
    import com.studica.frc.AHRS;
    ```
    ```C++
    #include "studica/AHRS.h"
    ```
- Added Enum for Comm Port & Update Rate selection in constructor.
    New Constructors look like this:
    ```Java
    navx = new AHRS(AHRS.NavXComType.kMXP_SPI);
    ```
    ```Java
    navx = new AHRS(AHRS.NavXComType.kMXP_SPI, AHRS.NavXUpdateRate.k50Hz);
    ```
    ```C++
    studica::AHRS navx{studica::AHRS::NavXComType::kMXP_SPI};
    ```
    ```C++
    studica::AHRS navx{studica::AHRS::NavXComType::kMXP_SPI, studica::AHRS::NavXUpdateRate::k50Hz};
    ```
- Fixed GetRate()
- Fixed Setting update rate in Java 
- Updated some print statements
- Applied patches introduced by robotpy [1](https://github.com/robotpy/robotpy-navx/blob/main/navx/src/ahrs.h.patch), [2](https://github.com/robotpy/robotpy-navx/blob/main/navx/src/sources.patch)
- Fixed Simulation not exiting on Linux machines [#1](https://github.com/Studica-Robotics/NavX/issues/1).
- Enhanced simulation in the background. This enables new ways of doing simulation:

    ```java
    import edu.wpi.first.hal.SimDouble;
    import edu.wpi.first.wpilibj.simulation.SimDeviceSim;

    private SimDeviceSim device;
    private SimDouble angle;

    device = new SimDeviceSim("navX-Sensor", navx.getPort());
    angle = device.getDouble("Yaw");
    ```
    getPort() allows the user to not know the exact port #.

- New constructor for using a custom refresh rate outside of the stable enums. [#2](https://github.com/Studica-Robotics/NavX/issues/2). 
    ```java
    navx = new AHRS(AHRS.NavXComType.kMXP_SPI, 100);
    ```
    ```c++
    studica::AHRS navx{studica::AHRS::NavXComType::kMXP_SPI, 100};
    ```
- Fixed fault with GetBoardYawAxis() [#4](https://github.com/Studica-Robotics/NavX/issues/4).
- Added Robot Centric Velocities
    ```java
    navx.getRobotCentricVelocityX();
    navx.getRobotCentricVelocityY();
    navx.getRobotCentricVelocityZ();
    ```
    ```c++
    navx.GetRobotCentricVelocityX();
    navx.GetRobotCentricVelocityY();
    navx.GetRobotCentricVelocityZ();
    ```
    These velocities use the quaternion as a header and should be safe from gimbal lock.
- Added flags for swaping velocity axes.
    ```java
    navx.configureVelocity(boolean swapAxes, boolean invertX, boolean invertY, boolean invertZ);
    ```
    ```c++
    navx.ConfigureVelocity(bool swapAxes, bool invertX, bool invertY, bool invertZ);
    ```

    **swapAxes**, will swap X and Y axes.  
    **invertX**, will invert the X axis.  
    **invertY**, will invert the Y axis.  
    **invertZ**, will invert the Z axis.


### VSCode Install
Starting in (**2025**), Vendordeps can be installed directly from the WPILib VSCode.

1. From VSCode select the **WPILib Vendor Dependencies** extension. 

    <img src='assets/vscodeVendorDep-1.png' width='50%'><br/>

2. Find the Studica Listing and hit Install.

    <img src='assets/vscodeVendorDep-2.png' width='50%'><br/>

3. A pop-up will ask to run a build, hit yes. 

    <img src='assets/vscodeVendorDep-3.png' width='50%'><br/>

### VSCode Update

To update the vendordep, open the **WPILib Vendor Dependencies** find the Studica vendordep select the dropdown and the latest version. Hit the update button to install the update. 

    <img src='assets/vscodeVendorDep-4.png' width='50%'><br/>

### Direct JSON Link

For those that wish to use the old method of importing vendordeps, the JSON is here:

```
https://dev.studica.com/maven/release/2026/json/Studica-2026.0.0.json
```