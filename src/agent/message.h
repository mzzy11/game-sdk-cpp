#pragma once
#ifndef THUAI7_AGENT_MESSAGE_H_
#define THUAI7_AGENT_MESSAGE_H_

// std c++ libraries
#include <string>
// 3rd party libraries
#include <nlohmann/json.hpp>
// project headers
#include "agent/position.h"

namespace thuai7_agent {

enum class SupplyKind {
  S686,
  VECTORY,
  AWM,
  M16,
  BULLET,
  BANDAGE,
  PRIMARY_ARMOR,
  PREMIUM_ARMOR,
  FIRST_AID,
  GRENADE,
};
NLOHMANN_JSON_SERIALIZE_ENUM(SupplyKind,
                             {
                                 {SupplyKind::S686, "S686"},
                                 {SupplyKind::VECTORY, "VECTORY"},
                                 {SupplyKind::AWM, "AWM"},
                                 {SupplyKind::M16, "M16"},
                                 {SupplyKind::BULLET, "BULLET"},
                                 {SupplyKind::BANDAGE, "BANDAGE"},
                                 {SupplyKind::PRIMARY_ARMOR, "PRIMARY_ARMOR"},
                                 {SupplyKind::PREMIUM_ARMOR, "PREMIUM_ARMOR"},
                                 {SupplyKind::FIRST_AID, "FIRST_AID"},
                                 {SupplyKind::GRENADE, "GRENADE"},
                             });

enum class FirearmKind {
  S686,
  VECTORY,
  AWM,
  M16,
};
NLOHMANN_JSON_SERIALIZE_ENUM(FirearmKind, {
                                              {FirearmKind::S686, "S686"},
                                              {FirearmKind::VECTORY, "VECTORY"},
                                              {FirearmKind::AWM, "AWM"},
                                              {FirearmKind::M16, "M16"},
                                          });

enum class MedicineKind {
  BANDAGE,
  FIRST_AID,
};
NLOHMANN_JSON_SERIALIZE_ENUM(MedicineKind,
                             {
                                 {MedicineKind::BANDAGE, "BANDAGE"},
                                 {MedicineKind::FIRST_AID, "FIRST_AID"},
                             });

class Message {
 public:
  explicit Message(std::string json_str)
      : msg(nlohmann::json::parse(json_str)) {}
  Message() = default;

  auto json() -> std::string { return msg.dump(); }

 protected:
  nlohmann::json msg;
};

class PerformAbandonMessage : public Message {
 public:
  PerformAbandonMessage(int numb, const std::string& token,
                        const SupplyKind& target_supply) {
    msg["messageType"] = "PERFORM_ABANDON";
    msg["numb"] = numb;
    msg["token"] = token;
    msg["targetSupply"] = target_supply;
  }
};

class PerformPickUpMessage : public Message {
 public:
  PerformPickUpMessage(const std::string& token,
                       const SupplyKind& target_supply, int num,
                       const Position<float>& target_position) {
    msg["messageType"] = "PERFORM_PICK_UP";
    msg["token"] = token;
    msg["targetSupply"] = target_supply;
    msg["num"] = num;
    msg["targetPosition"] = {{"x", target_position.x},
                             {"y", target_position.y}};
  }
};

class PerformSwitchArmMessage : public Message {
 public:
  PerformSwitchArmMessage(const std::string& token,
                          const FirearmKind& target_firearm) {
    msg["messageType"] = "PERFORM_SWITCH_ARM";
    msg["token"] = token;
    msg["targetFirearm"] = target_firearm;
  }
};

class PerformUseMedicineMessage : public Message {
 public:
  PerformUseMedicineMessage(const std::string& token,
                            const MedicineKind& medicine_name) {
    msg["messageType"] = "PERFORM_USE_MEDICINE";
    msg["token"] = token;
    msg["medicineName"] = medicine_name;
  }
};

class PerformUseGrenadeMessage : public Message {
 public:
  PerformUseGrenadeMessage(const std::string& token,
                           const Position<float>& target_position) {
    msg["messageType"] = "PERFORM_USE_GRENADE";
    msg["token"] = token;
    msg["targetPosition"] = {{"x", target_position.x},
                             {"y", target_position.y}};
  }
};

class PerformMoveMessage : public Message {
 public:
  PerformMoveMessage(const std::string& token,
                     const Position<float>& destination) {
    msg["messageType"] = "PERFORM_MOVE";
    msg["token"] = token;
    msg["destination"] = {{"x", destination.x}, {"y", destination.y}};
  }
};

class PerformStopMessage : public Message {
 public:
  explicit PerformStopMessage(const std::string& token) {
    msg["messageType"] = "PERFORM_STOP";
    msg["token"] = token;
  }
};

class PerformAttackMessage : public Message {
 public:
  PerformAttackMessage(const std::string& token,
                       const Position<float>& target_position) {
    msg["messageType"] = "PERFORM_ATTACK";
    msg["token"] = token;
    msg["targetPosition"] = {{"x", target_position.x},
                             {"y", target_position.y}};
  }
};

class GetPlayerInfoMessage : public Message {
 public:
  explicit GetPlayerInfoMessage(const std::string& token) {
    msg["messageType"] = "GET_PLAYER_INFO";
    msg["token"] = token;
  }
};

class GetMapMessage : public Message {
 public:
  explicit GetMapMessage(const std::string& token) {
    msg["messageType"] = "GET_MAP";
    msg["token"] = token;
  }
};

class ChooseOriginMessage : public Message {
 public:
  ChooseOriginMessage(const std::string& token,
                      const Position<float>& origin_position) {
    msg["messageType"] = "CHOOSE_ORIGIN";
    msg["token"] = token;
    msg["originPosition"] = {{"x", origin_position.x},
                             {"y", origin_position.y}};
  }
};

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_MESSAGE_H_
