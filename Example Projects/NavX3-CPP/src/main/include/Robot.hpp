// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include "studica/Navx.hpp"
#include "wpi/framework/TimedRobot.hpp"
#include "wpi/simulation/SimDeviceSim.hpp"
#include "wpi/tunables/Selectable.hpp"
#include "wpi/tunables/Tunable.hpp"

class Robot : public wpi::TimedRobot {
 public:
  Robot();
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void UtilityInit() override;
  void UtilityPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:
  wpi::tunables::Selectable<std::string> chooser;
  const std::string AUTO_NAME_DEFAULT = "Default";
  const std::string AUTO_NAME_CUSTOM = "My Auto";
  std::string autoSelected;

  // NavX3 with CAN ID 0 on bus S0, sending data at 100 Hz
  studica::Navx navx{0, wpi::CANPort::CAN_S0, 100};  // CAN
  // studica::Navx navx = studica::Navx::Usb();  // USB, any port

  // Sim Object; edit its values in the Sim GUI under Other Devices
  wpi::sim::SimDeviceSim device{"NavX3", 0};

  // Dashboard button to zero the yaw
  wpi::tunables::Tunable<bool> resetYaw{false};
};
