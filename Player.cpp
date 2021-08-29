#include "Player.h"

Player::Player() {

}

std::vector<Piece> Player::getPieces() const
{
	return pieces;
}

void Player::setPieces(std::vector<Piece> pieces)
{
	this->pieces.clear();
	this->pieces = pieces;
}

void Player::removePiece(Piece& piece)
{
	std::vector<Piece> newVector;
	for (int i = 0; i < pieces.size(); i++) {
		if (pieces.at(i).equals(piece)) continue;
		newVector.push_back(pieces.at(i));
	}
	setPieces(newVector);
}

void Player::addPiece(Piece& piece)
{
	pieces.push_back(piece);
}

