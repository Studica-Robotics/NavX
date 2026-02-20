// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/print.h>

Robot::Robot() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  // You can enable which messages the navx sends to prevent bus saturation 
  navx.EnableOptionalMessages(true, true, true, true, true, true, true, true, true);

  // UUID of the navx if thats something you want
  int uuids[3] = {0};
  navx.GetSensorUUID(uuids);
  frc::SmartDashboard::PutNumber("uuid0", uuids[0]);
  frc::SmartDashboard::PutNumber("uuid1", uuids[1]);
  frc::SmartDashboard::PutNumber("uuid2", uuids[2]);

  // Zero Yaw Btn
  frc::SmartDashboard::PutBoolean("Reset Yaw", false);
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  int error;
  // Yaw, Pitch, Roll, Angle
  frc::SmartDashboard::PutNumber("Yaw:",   navx.GetYaw().value());
  frc::SmartDashboard::PutNumber("Pitch:", navx.GetPitch().value());
  frc::SmartDashboard::PutNumber("Roll:",  navx.GetRoll().value());
  frc::SmartDashboard::PutNumber("Angle:", navx.GetAngle().value());

  // 6-axis quaternion
  frc::Quaternion quat6{};
  error = navx.GetQuat6D(quat6);
  frc::SmartDashboard::PutNumber("q6_w:", quat6.W());
  frc::SmartDashboard::PutNumber("q6_x:", quat6.X());
  frc::SmartDashboard::PutNumber("q6_y:", quat6.Y());
  frc::SmartDashboard::PutNumber("q6_z:", quat6.Z());

  // Angular Velocity
  units::degrees_per_second_t wx{0}, wy{0}, wz{0};
  error = navx.GetAngularVel(wx, wy, wz);
  frc::SmartDashboard::PutNumber("w_x:", wx.value());
  frc::SmartDashboard::PutNumber("w_y:", wy.value());
  frc::SmartDashboard::PutNumber("w_z:", wz.value());

  // 9-axis quaternion 
  frc::Quaternion quat9{};
  error = navx.GetQuat9D(quat9);
  frc::SmartDashboard::PutNumber("q9_w:", quat6.W());
  frc::SmartDashboard::PutNumber("q9_x:", quat6.X());
  frc::SmartDashboard::PutNumber("q9_y:", quat6.Y());
  frc::SmartDashboard::PutNumber("q9_z:", quat6.Z());

  // Linear Acceleration
  units::meters_per_second_squared_t ax{0}, ay{0}, az{0};
  error = navx.GetLinearAccel(ax, ay, az);
  frc::SmartDashboard::PutNumber("a_x:", ax.value());
  frc::SmartDashboard::PutNumber("a_y:", ay.value());
  frc::SmartDashboard::PutNumber("a_z:", az.value());

  // Get Compass reading from Mag
  units::tesla_t mx{0}, my{0}, mz{0}, mnorm{0};
  error = navx.GetCompass(mx, my, mz, mnorm);
  frc::SmartDashboard::PutNumber("mag_x_ut:", mx.value() * 1e-6);
  frc::SmartDashboard::PutNumber("mag_y_ut:", my.value() * 1e-6);
  frc::SmartDashboard::PutNumber("mag_z_ut:", mz.value() * 1e-6);
  frc::SmartDashboard::PutNumber("mag_norm_ut:", mnorm.value() * 1e-6);

  // Temperature reported by IMU
  frc::SmartDashboard::PutNumber("temp:", navx.GetTemperature().value());

  // Zero Yaw if btn pushed
  if (frc::SmartDashboard::GetBoolean("Reset Yaw", false))
  {
    navx.ResetYaw();
    frc::SmartDashboard::PutBoolean("Reset Yaw", false);
  }
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  wpi::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
