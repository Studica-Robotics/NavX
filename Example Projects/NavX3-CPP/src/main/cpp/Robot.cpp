// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"

#include <format>

#include "studica/CanBus.hpp"
#include "wpi/telemetry/Telemetry.hpp"
#include "wpi/tunables/Tunables.hpp"
#include "wpi/util/print.hpp"

Robot::Robot() {
  chooser.AddDefault(AUTO_NAME_DEFAULT, AUTO_NAME_DEFAULT);
  chooser.Add(AUTO_NAME_CUSTOM, AUTO_NAME_CUSTOM);
  wpi::tunables::Publish("Auto Modes", chooser);

  // Optional: switch bus S0 to CAN FD (every device on the bus must support CAN
  // FD)
  // studica::CanBus::RequestMode(wpi::CANPort::CAN_S0,
  //                              studica::CanBusMode::FD_5MBPS);

  // Show the reset yaw button on the dashboard
  wpi::tunables::Publish("NavX3/Reset Yaw", resetYaw);

  // Optional: choose which data the NavX3 sends to reduce CAN traffic
  // navx.EnableMessages(studica::NavxMessage::YAW |
  //                     studica::NavxMessage::ANGULAR_VELOCITY);

  // Firmware version and unique ID of the NavX3
  if (auto version = navx.GetFirmwareVersion()) {
    wpi::util::print("NavX3 firmware: {}.{}.{}\n", version->major,
                     version->minor, version->patch);
  }
  if (auto uuid = navx.GetSensorUuid()) {
    wpi::telemetry::Log("NavX3/UUID",
                        std::format("{:08X}-{:08X}-{:08X}", (*uuid)[0],
                                    (*uuid)[1], (*uuid)[2]));
  }
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and utility.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  // Each getter returns a std::optional, which is empty until the NavX3 sends
  // data
  wpi::telemetry::Log("NavX3/Connected", navx.IsConnected());

  // Yaw, Pitch, Roll, Angle
  if (auto yaw = navx.GetYaw()) {
    wpi::telemetry::Log("NavX3/Yaw (deg)", yaw->value());
  }
  if (auto pitch = navx.GetPitch()) {
    wpi::telemetry::Log("NavX3/Pitch (deg)", pitch->value());
  }
  if (auto roll = navx.GetRoll()) {
    wpi::telemetry::Log("NavX3/Roll (deg)", roll->value());
  }
  if (auto angle = navx.GetAngle()) {
    wpi::telemetry::Log("NavX3/Angle (deg)", angle->value());
  }
  // For drivetrain code, GetRotation2d() gives the heading as a Rotation2d

  // 6-axis quaternion
  if (auto q = navx.GetQuaternion6d()) {
    wpi::telemetry::Log("NavX3/Quat6D W", q->W());
    wpi::telemetry::Log("NavX3/Quat6D X", q->X());
    wpi::telemetry::Log("NavX3/Quat6D Y", q->Y());
    wpi::telemetry::Log("NavX3/Quat6D Z", q->Z());
  }

  // 9-axis quaternion (uses the magnetometer)
  if (auto q = navx.GetQuaternion9d()) {
    wpi::telemetry::Log("NavX3/Quat9D W", q->W());
    wpi::telemetry::Log("NavX3/Quat9D X", q->X());
    wpi::telemetry::Log("NavX3/Quat9D Y", q->Y());
    wpi::telemetry::Log("NavX3/Quat9D Z", q->Z());
  }

  // Angular velocity, in radians per second
  if (auto w = navx.GetAngularVelocity()) {
    wpi::telemetry::Log("NavX3/Gyro X (rad per s)", w->x.value());
    wpi::telemetry::Log("NavX3/Gyro Y (rad per s)", w->y.value());
    wpi::telemetry::Log("NavX3/Gyro Z (rad per s)", w->z.value());
  }

  // Linear acceleration, in metres per second squared
  if (auto a = navx.GetLinearAcceleration()) {
    wpi::telemetry::Log("NavX3/Accel X (m per s2)", a->x.value());
    wpi::telemetry::Log("NavX3/Accel Y (m per s2)", a->y.value());
    wpi::telemetry::Log("NavX3/Accel Z (m per s2)", a->z.value());
  }

  // Magnetometer, in microtesla
  if (auto mag = navx.GetMagneticField()) {
    wpi::telemetry::Log("NavX3/Mag X (uT)", mag->x.value());
    wpi::telemetry::Log("NavX3/Mag Y (uT)", mag->y.value());
    wpi::telemetry::Log("NavX3/Mag Z (uT)", mag->z.value());
    wpi::telemetry::Log("NavX3/Mag Norm (uT)", mag->norm.value());
  }

  // Temperature reported by the IMU
  if (auto temp = navx.GetTemperature()) {
    wpi::telemetry::Log("NavX3/Temperature (C)", temp->value());
  }

  // Zero the yaw when the dashboard button is pressed
  if (resetYaw.Get()) {
    navx.ResetYaw();
    resetYaw.Set(false);
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
 * if-else structure below with additional strings. If using
 * wpi::tunables::Selectable make sure to add them to the chooser code above as
 * well.
 */
void Robot::AutonomousInit() {
  autoSelected = chooser.GetSelected();
  // autoSelected = SmartDashboard::GetString("Auto Selector",
  //     AUTO_NAME_DEFAULT);
  wpi::util::print("Auto selected: {}\n", autoSelected);

  if (autoSelected == AUTO_NAME_CUSTOM) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (autoSelected == AUTO_NAME_CUSTOM) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::UtilityInit() {}

void Robot::UtilityPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_WPILIB_TESTS
int main() {
  return wpi::StartRobot<Robot>();
}
#endif
