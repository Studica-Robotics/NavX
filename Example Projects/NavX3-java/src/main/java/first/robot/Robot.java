// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package first.robot;

import static org.wpilib.units.Units.Celsius;
import static org.wpilib.units.Units.Degrees;
import static org.wpilib.units.Units.MetersPerSecondPerSecond;
import static org.wpilib.units.Units.RadiansPerSecond;

import com.studica.frc.CanBus;
import com.studica.frc.Navx;
import org.wpilib.framework.TimedRobot;
import org.wpilib.hardware.bus.CANPort;
import org.wpilib.simulation.SimDeviceSim;
import org.wpilib.telemetry.Telemetry;
import org.wpilib.tunable.Selectable;
import org.wpilib.tunable.TunableBoolean;
import org.wpilib.tunable.Tunables;

/**
 * The methods in this class are called automatically corresponding to each mode, as described in
 * the TimedRobot documentation. If you change the name of this class or the package after creating
 * this project, you must also update the Main.java file in the project.
 */
public class Robot extends TimedRobot {
  private static final String DEFAULT_AUTO = "Default";
  private static final String CUSTOM_AUTO = "My Auto";
  private String autoSelected;
  private final Selectable<String> chooser = new Selectable<>();

  private final Navx navx;
  private final SimDeviceSim device;

  // Dashboard button to zero the yaw
  private final TunableBoolean resetYaw = Tunables.addBoolean("NavX3/Reset Yaw", false);

  /**
   * This function is run when the robot is first started up and should be used for any
   * initialization code.
   */
  public Robot() {
    chooser.addDefault("Default Auto", DEFAULT_AUTO);
    chooser.add("My Auto", CUSTOM_AUTO);
    Tunables.publish("Auto choices", chooser);

    // Optional: switch bus S0 to CAN FD (every device on the bus must support CAN FD)
    // CanBus.requestMode(CANPort.CAN_S0, CanBus.Mode.FD_5MBPS);

    // Create the NavX3 with CAN ID 0 on bus S0, sending data at 100 Hz
    navx = new Navx(0, CANPort.CAN_S0, 100); // CAN
    // navx = Navx.usb(); // USB, any port

    // Create Sim Object; edit its values in the Sim GUI under Other Devices
    device = new SimDeviceSim("NavX3", 0);

    // Optional: choose which data the NavX3 sends to reduce CAN traffic
    // navx.enableMessages(Navx.Message.YAW, Navx.Message.ANGULAR_VELOCITY);

    // Firmware version and unique ID of the NavX3
    navx.getFirmwareVersion().ifPresent(v -> System.out.println("NavX3 firmware: " + v));
    navx.getSensorUuid().ifPresent(uuid -> Telemetry.log("NavX3/UUID",
        String.format("%08X-%08X-%08X", uuid[0], uuid[1], uuid[2])));
  }

  /**
   * This function is called every 20 ms, no matter the mode. Use this for items like diagnostics
   * that you want ran during disabled, autonomous, teleoperated and utility.
   *
   * <p>This runs after the mode specific periodic functions, but before LiveWindow and
   * SmartDashboard integrated updating.
   */
  @Override
  public void robotPeriodic() {
    // Each getter returns an Optional, which is empty until the NavX3 sends data
    Telemetry.log("NavX3/Connected", navx.isConnected());

    // Yaw, Pitch, Roll, Angle
    navx.getYaw().ifPresent(yaw -> Telemetry.log("NavX3/Yaw (deg)", yaw.in(Degrees)));
    navx.getPitch().ifPresent(pitch -> Telemetry.log("NavX3/Pitch (deg)", pitch.in(Degrees)));
    navx.getRoll().ifPresent(roll -> Telemetry.log("NavX3/Roll (deg)", roll.in(Degrees)));
    navx.getAngle().ifPresent(angle -> Telemetry.log("NavX3/Angle (deg)", angle.in(Degrees)));
    // For drivetrain code, getRotation2d() gives the heading as a Rotation2d

    // 6-axis quaternion
    navx.getQuaternion6d().ifPresent(q -> {
      Telemetry.log("NavX3/Quat6D W", q.getW());
      Telemetry.log("NavX3/Quat6D X", q.getX());
      Telemetry.log("NavX3/Quat6D Y", q.getY());
      Telemetry.log("NavX3/Quat6D Z", q.getZ());
    });

    // 9-axis quaternion (uses the magnetometer)
    navx.getQuaternion9d().ifPresent(q -> {
      Telemetry.log("NavX3/Quat9D W", q.getW());
      Telemetry.log("NavX3/Quat9D X", q.getX());
      Telemetry.log("NavX3/Quat9D Y", q.getY());
      Telemetry.log("NavX3/Quat9D Z", q.getZ());
    });

    // Angular velocity
    navx.getAngularVelocity().ifPresent(w -> {
      Telemetry.log("NavX3/Gyro X (rad per s)", w.x().in(RadiansPerSecond));
      Telemetry.log("NavX3/Gyro Y (rad per s)", w.y().in(RadiansPerSecond));
      Telemetry.log("NavX3/Gyro Z (rad per s)", w.z().in(RadiansPerSecond));
    });

    // Linear acceleration
    navx.getLinearAcceleration().ifPresent(a -> {
      Telemetry.log("NavX3/Accel X (m per s2)", a.x().in(MetersPerSecondPerSecond));
      Telemetry.log("NavX3/Accel Y (m per s2)", a.y().in(MetersPerSecondPerSecond));
      Telemetry.log("NavX3/Accel Z (m per s2)", a.z().in(MetersPerSecondPerSecond));
    });

    // Magnetometer, in microtesla
    navx.getMagneticField().ifPresent(mag -> {
      Telemetry.log("NavX3/Mag X (uT)", mag.x());
      Telemetry.log("NavX3/Mag Y (uT)", mag.y());
      Telemetry.log("NavX3/Mag Z (uT)", mag.z());
      Telemetry.log("NavX3/Mag Norm (uT)", mag.norm());
    });

    // Temperature reported by the IMU
    navx.getTemperature().ifPresent(t -> Telemetry.log("NavX3/Temperature (C)", t.in(Celsius)));

    // Zero the yaw when the dashboard button is pressed
    if (resetYaw.get()) {
      navx.resetYaw();
      resetYaw.set(false);
    }
  }

  /**
   * This autonomous (along with the chooser code above) shows how to select between different
   * autonomous modes using the dashboard. The sendable chooser code works with the Java
   * SmartDashboard. If you prefer the LabVIEW Dashboard, remove all of the chooser code and
   * uncomment the getString line to get the auto name from the text box below the Gyro
   *
   * <p>You can add additional auto modes by adding additional comparisons to the switch structure
   * below with additional strings. If using Selectable make sure to add them to the chooser code
   * above as well.
   */
  @Override
  public void autonomousInit() {
    autoSelected = chooser.getSelected();
    // autoSelected = SmartDashboard.getString("Auto Selector", DEFAULT_AUTO);
    System.out.println("Auto selected: " + autoSelected);
  }

  /** This function is called periodically during autonomous. */
  @Override
  public void autonomousPeriodic() {
    switch (autoSelected) {
      case CUSTOM_AUTO:
        // Put custom auto code here
        break;
      case DEFAULT_AUTO:
      default:
        // Put default auto code here
        break;
    }
  }

  /** This function is called once when teleop is enabled. */
  @Override
  public void teleopInit() {}

  /** This function is called periodically during operator control. */
  @Override
  public void teleopPeriodic() {}

  /** This function is called once when the robot is disabled. */
  @Override
  public void disabledInit() {}

  /** This function is called periodically when disabled. */
  @Override
  public void disabledPeriodic() {}

  /** This function is called once when utility mode is enabled. */
  @Override
  public void utilityInit() {}

  /** This function is called periodically during utility mode. */
  @Override
  public void utilityPeriodic() {}

  /** This function is called once when the robot is first started up. */
  @Override
  public void simulationInit() {}

  /** This function is called periodically whilst in simulation. */
  @Override
  public void simulationPeriodic() {}
}
