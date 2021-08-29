#pragma once
#include <vector>
#include "Piece.h"
#include <SFML/Graphics.hpp>
class Player {
	Player();

private:
	std::vector<Piece> pieces;
	sf::Color color;
public:
	std::vector<Piece> getPieces() const;
	void setPieces(std::vector<Piece> pieces);
	void removePiece(Piece& piece);
	void addPiece(Piece& piece);
};