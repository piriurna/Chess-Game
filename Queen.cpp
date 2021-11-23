#include "Queen.h"


Queen::Queen(const sf::Texture* texture, int position, Team team) {
	loadSprite(*texture);
	this->position = position;
	this->team = team;
	this->type = Type::QUEEN;
};



struct ActualPosition {
	int X, Y;
};

void Queen::calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) {
	MoveOffset initialMove = moveOffsets.at(3);
	if (team == Team::WHITE) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
	else if (team == Team::BLACK) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
};

std::vector<Piece::PossibleMove> Queen::getPossibleMoves() {
	return possibleMoves;
};


void Queen::sayMyName() {
	if (team == Team::BLACK) {
		printf("Black Queen");
	}
	else {
		printf("White Queen");
	}
}
