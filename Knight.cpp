#include "Knight.h"


Knight::Knight(const sf::Texture* texture, int position, Team team) {
	loadSprite(*texture);
	this->position = position;
	this->team = team;
	this->type = Type::KNIGHT;
};


struct ActualPosition {
	int X, Y;
};

void Knight::calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) {
	MoveOffset initialMove = moveOffsets.at(3);
	if (team == Team::WHITE) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
	else if (team == Team::BLACK) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
};

std::vector<Piece::PossibleMove> Knight::getPossibleMoves() {
	return possibleMoves;
};


void Knight::sayMyName() {
	if (team == Team::BLACK) {
		printf("Black Knight");
	}
	else {
		printf("White Knight");
	}
}
