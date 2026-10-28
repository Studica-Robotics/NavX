// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.hpp"

#include <string_view>

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

  // Show the learn colour button on the dashboard
  wpi::tunables::Publish("Colore/Learn Color", learnColor);

  // Optional: illumination LED brightness, 0-100 %
  // colore.SetLedBrightness(50);

  // Optional: add a colour you learned before, so it is known at every start
  // colore.AddColor("Red", {0.55, 0.33});

  // Firmware version of the Colore
  if (auto version = colore.GetFirmwareVersion()) {
    wpi::util::print("Colore firmware: {}.{}.{}\n", version->major,
                     version->minor, version->patch);
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
  wpi::telemetry::Log("Colore/Connected", colore.IsConnected());

  // Newest reading; empty until the Colore sends data
  if (auto reading = colore.GetColor()) {
    // Raw CIE XYZ values
    wpi::telemetry::Log("Colore/X", reading->x);
    wpi::telemetry::Log("Colore/Y", reading->y);
    wpi::telemetry::Log("Colore/Z", reading->z);

    // As an RGB colour, e.g. for LEDs or the dashboard
    wpi::telemetry::Log("Colore/Color",
                        std::string_view{reading->ToColor().HexString()});

    // Colour without brightness: stays the same as the target moves closer or
    // further away
    if (auto chroma = reading->GetChromaticity()) {
      wpi::telemetry::Log("Colore/Chroma x", chroma->x);
      wpi::telemetry::Log("Colore/Chroma y", chroma->y);
    }
  }

  // Learn the colour in front of the sensor when the dashboard button is
  // pressed
  if (learnColor.Get()) {
    if (auto chroma = colore.LearnColor("Target")) {
      wpi::util::print("Learned Target: x {}, y {}\n", chroma->x, chroma->y);
    }
    learnColor.Set(false);
  }

  // The closest learned colour, if any is close enough
  auto match = colore.GetMatch();
  wpi::telemetry::Log("Colore/Match",
                      match ? std::string_view{match->name} : "None");
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
