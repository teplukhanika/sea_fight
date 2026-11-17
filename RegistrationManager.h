#pragma once
#include <string>
#include <vector>
#include "PlayerProfile.h"

class RegistrationManager {
private:
	std::vector<PlayerProfile> players;

public:
	RegistrationManager();

	PlayerProfile* registerPlayer(const std::string& name);

	void sortAndPrintLeaderboard();

	std::string saveAllToMemoryBuffer() const;

	bool saveToFile(const std::string& path) const;
	bool loadFromFile(const std::string& path);
};