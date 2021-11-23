#pragma once
#include <vector>
#include "Piece.h"
#include <SFML/Graphics.hpp>
class Player {
public:
	Player(Team team);

	std::vector<Piece*> getPieces(std::vector<Piece*> gamePieces) const;

	Team getTeam();

private:
	Team team;

};