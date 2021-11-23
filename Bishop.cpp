#include "Bishop.h"


Bishop::Bishop(const sf::Texture* texture, int position, Team team) {
	loadSprite(*texture);
	this->position = position;
	this->team = team;
	this->type = Type::BISHOP;
};


struct ActualPosition {
	int X, Y;
};

void Bishop::calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) {
	MoveOffset initialMove = moveOffsets.at(3);
	if (team == Team::WHITE) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
	else if (team == Team::BLACK) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
};

std::vector<Piece::PossibleMove> Bishop::getPossibleMoves() {
	return possibleMoves;
};


void Bishop::sayMyName() {
	if (team == Team::BLACK) {
		printf("Black Bishop");
	}
	else {
		printf("White Bishop");
	}
}


