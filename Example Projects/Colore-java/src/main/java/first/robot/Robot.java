// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package first.robot;

import com.studica.frc.CanBus;
import com.studica.frc.Colore;
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

  private final Colore colore;
  private final SimDeviceSim device;

  // Dashboard button that learns the colour in front of the sensor
  private final TunableBoolean learnColor = Tunables.addBoolean("Colore/Learn Color", false);

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

    // Create the Colore with CAN ID 0 on bus S0
    colore = new Colore(0, CANPort.CAN_S0); // CAN
    // colore = Colore.usb(); // USB, any port

    // Create Sim Object; edit its values in the Sim GUI under Other Devices
    device = new SimDeviceSim("Colore", 0);

    // Optional: illumination LED brightness, 0-100 %
    // colore.setLedBrightness(50);

    // Optional: add a colour you learned before, so it is known at every start
    // colore.addColor("Red", new Colore.Chromaticity(0.55, 0.33));

    // Firmware version of the Colore
    colore.getFirmwareVersion().ifPresent(v -> System.out.println("Colore firmware: " + v));
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
    Telemetry.log("Colore/Connected", colore.isConnected());

    // Newest reading; empty until the Colore sends data
    colore.getColor().ifPresent(reading -> {
      // Raw CIE XYZ values
      Telemetry.log("Colore/X", reading.x());
      Telemetry.log("Colore/Y", reading.y());
      Telemetry.log("Colore/Z", reading.z());

      // As an RGB colour, e.g. for LEDs or the dashboard
      Telemetry.log("Colore/Color", reading.toColor().toHexString());

      // Colour without brightness: stays the same as the target moves closer or further away
      reading.getChromaticity().ifPresent(c -> {
        Telemetry.log("Colore/Chroma x", c.x());
        Telemetry.log("Colore/Chroma y", c.y());
      });
    });

    // Learn the colour in front of the sensor when the dashboard button is pressed
    if (learnColor.get()) {
      colore.learnColor("Target")
          .ifPresent(c -> System.out.println("Learned Target: " + c));
      learnColor.set(false);
    }

    // The closest learned colour, if any is close enough
    Telemetry.log("Colore/Match", colore.getMatch().map(Colore.Match::name).orElse("None"));
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
