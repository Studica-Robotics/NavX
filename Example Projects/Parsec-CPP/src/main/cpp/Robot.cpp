// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"

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

  // Optional: use the 4x4 grid (up to 60 Hz) instead of the default 8x8 (up to
  // 15 Hz)
  // parsec.SetResolution(studica::ParsecResolution::ZONES_4X4);
  // parsec.SetRangingFrequency(60);

  // Firmware version of the Parsec
  if (auto config = parsec.GetConfig(); config && config->firmware) {
    wpi::util::print("Parsec firmware: {}.{}.{}\n", config->firmware->major,
                     config->firmware->minor, config->firmware->patch);
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
  wpi::telemetry::Log("Parsec/Connected", parsec.IsConnected());

  // Nearest object seen by any zone
  if (auto closest = parsec.GetClosestDistance()) {
    wpi::telemetry::Log("Parsec/Closest (mm)", closest->value());
  }

  // A scan holds one distance per zone; empty until the Parsec sends data
  if (auto scan = parsec.GetScan()) {
    wpi::telemetry::Log("Parsec/Zones", scan->ZoneCount());

    // Distance in the top left zone (row 0, column 0)
    if (auto topLeft = scan->GetDistance(0, 0)) {
      wpi::telemetry::Log("Parsec/Top Left (mm)", topLeft->value());
    }

    // Every zone in millimetres, row by row; negative means no reading
    wpi::telemetry::Log("Parsec/All Zones (mm)", scan->RawMillimeters());
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
