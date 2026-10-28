#pragma once
#include <string>
#include <vector>
#include "PlayerProfile.h"

class RegistrationManager {
private:
	std::vector<PlayerProfile> registeredPlayers;

public:
	RegistrationManager();

	PlayerProfile* registerOrLogin(const std::string& playerName);
	PlayerProfile* findPlayer(const std::string& playerName);
	void printAllProfiles() const;
};