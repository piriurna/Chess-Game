#include "Player.h"

Player::Player(Team team) {
	this->team = team;
}

std::vector<Piece*> Player::getPieces(std::vector<Piece*> gamePieces) const
{
	std::vector<Piece*> myPieces;
	for (int i = 0; i < gamePieces.size(); i++) {
		if ((*gamePieces.at(i)).getTeam() == this->team) {
			myPieces.push_back(gamePieces.at(i));
		}
	}

	return myPieces;
}

Team Player::getTeam() {
	return this->team;
}

