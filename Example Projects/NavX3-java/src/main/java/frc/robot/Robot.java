// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package frc.robot;

import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.simulation.SimDeviceSim;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import edu.wpi.first.math.geometry.Quaternion;
import edu.wpi.first.units.measure.AngularVelocity;
import edu.wpi.first.units.measure.LinearAcceleration;

import static edu.wpi.first.units.Units.Celsius;
import static edu.wpi.first.units.Units.Degrees;
import static edu.wpi.first.units.Units.DegreesPerSecond;
import static edu.wpi.first.units.Units.MetersPerSecondPerSecond;

import com.studica.frc.Navx;

/**
 * The methods in this class are called automatically corresponding to each mode, as described in
 * the TimedRobot documentation. If you change the name of this class or the package after creating
 * this project, you must also update the Main.java file in the project.
 */
public class Robot extends TimedRobot {
  private static final String kDefaultAuto = "Default";
  private static final String kCustomAuto = "My Auto";
  private String m_autoSelected;
  private final SendableChooser<String> m_chooser = new SendableChooser<>();

  private Navx navx;
  private SimDeviceSim device;

  /**
   * This function is run when the robot is first started up and should be used for any
   * initialization code.
   */
  public Robot() {
    m_chooser.setDefaultOption("Default Auto", kDefaultAuto);
    m_chooser.addOption("My Auto", kCustomAuto);
    SmartDashboard.putData("Auto choices", m_chooser);

    // Create NavX Object
    navx = new Navx(0, 100); // CAN
    // navx = new Navx(Navx.Port.kUSB1); // USB 

    // Create Sim Object
    device = new SimDeviceSim("NavX3", 0);
    
    // You can enable which messages the navx sends to prevent bus saturation 
    navx.enableOptionalMessages(true,
                                true,
                                true,
                                true, 
                                true, 
                                true, 
                                true, 
                                true, 
                                true, 
                                true);

    // UUID of the navx if thats something you want
    int[] uuids = new int[3];
    navx.getSensorUUID(uuids);
    SmartDashboard.putNumber("uuid0", uuids[0]);
    SmartDashboard.putNumber("uuid1", uuids[1]);
    SmartDashboard.putNumber("uuid2", uuids[2]);

    // Add reset yaw btn to dashboard
    SmartDashboard.putBoolean("Reset Yaw", false);
  }

  /**
   * This function is called every 20 ms, no matter the mode. Use this for items like diagnostics
   * that you want ran during disabled, autonomous, teleoperated and test.
   *
   * <p>This runs after the mode specific periodic functions, but before LiveWindow and
   * SmartDashboard integrated updating.
   */
  @Override
  public void robotPeriodic() 
  {
    // Yaw, Pitch, Roll, Angle
    SmartDashboard.putNumber("Yaw:",  navx.getYaw().in(Degrees));
    SmartDashboard.putNumber("Pitch:", navx.getPitch().in(Degrees));
    SmartDashboard.putNumber("Roll:", navx.getRoll().in(Degrees));
    SmartDashboard.putNumber("Angle:", navx.getAngle().in(Degrees));

    // 6-axis quaternion
    Quaternion quat = navx.getQuat6D();
    SmartDashboard.putNumber("q6_w:", quat.getW());
    SmartDashboard.putNumber("q6_x:", quat.getX());
    SmartDashboard.putNumber("q6_y:", quat.getY());
    SmartDashboard.putNumber("q6_z:", quat.getZ());

    // Angular Velocity
    AngularVelocity[] omega = navx.getAngularVel();
    SmartDashboard.putNumber("w_x:", omega[0].in(DegreesPerSecond));
    SmartDashboard.putNumber("w_y:", omega[1].in(DegreesPerSecond));
    SmartDashboard.putNumber("w_z:", omega[2].in(DegreesPerSecond)); 

    // 9-axis quaternion 
    Quaternion quat9 = navx.getQuat9D();
    SmartDashboard.putNumber("q9_w:", quat9.getW());
    SmartDashboard.putNumber("q9_x:", quat9.getX());
    SmartDashboard.putNumber("q9_y:", quat9.getY());
    SmartDashboard.putNumber("q9_z:", quat9.getZ());

    // Linear Acceleration
    LinearAcceleration[] accel = navx.getLinearAccel();
    SmartDashboard.putNumber("v_x:", accel[0].in(MetersPerSecondPerSecond));
    SmartDashboard.putNumber("v_y:", accel[1].in(MetersPerSecondPerSecond));
    SmartDashboard.putNumber("v_z:", accel[2].in(MetersPerSecondPerSecond));

    // Get Compass reading from Mag
    float[] mag = new float[4];
    int error = navx.getCompass(mag);
    SmartDashboard.putNumber("mag_1:", mag[0]); 
    SmartDashboard.putNumber("mag_2:", mag[1]);
    SmartDashboard.putNumber("mag_3:", mag[2]);
    SmartDashboard.putNumber("mag_4:", mag[3]);
  
    // Temperature reported by IMU
    SmartDashboard.putNumber("temp:", navx.getTemperature().in(Celsius));

    if (SmartDashboard.getBoolean("Reset Yaw", false))
    {
      navx.resetYaw();
      SmartDashboard.putBoolean("Reset Yaw", false);
    }
  }

  /**
   * This autonomous (along with the chooser code above) shows how to select between different
   * autonomous modes using the dashboard. The sendable chooser code works with the Java
   * SmartDashboard. If you prefer the LabVIEW Dashboard, remove all of the chooser code and
   * uncomment the getString line to get the auto name from the text box below the Gyro
   *
   * <p>You can add additional auto modes by adding additional comparisons to the switch structure
   * below with additional strings. If using the SendableChooser make sure to add them to the
   * chooser code above as well.
   */
  @Override
  public void autonomousInit() {
    m_autoSelected = m_chooser.getSelected();
    // m_autoSelected = SmartDashboard.getString("Auto Selector", kDefaultAuto);
    System.out.println("Auto selected: " + m_autoSelected);
  }

  /** This function is called periodically during autonomous. */
  @Override
  public void autonomousPeriodic() {
    switch (m_autoSelected) {
      case kCustomAuto:
        // Put custom auto code here
        break;
      case kDefaultAuto:
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

  /** This function is called once when test mode is enabled. */
  @Override
  public void testInit() {}

  /** This function is called periodically during test mode. */
  @Override
  public void testPeriodic() {}

  /** This function is called once when the robot is first started up. */
  @Override
  public void simulationInit() {}

  /** This function is called periodically whilst in simulation. */
  @Override
  public void simulationPeriodic() {}
}
