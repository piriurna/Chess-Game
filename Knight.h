#pragma once
#include "Piece.h"
#include <vector>


class Knight : public Piece {
private:
	std::vector<Piece::MoveOffset> moveOffsets =
	{
		Piece::MoveOffset{ 2, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 2, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -2, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -2, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 1, 2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 1, -2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, 2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, -2, Piece::MoveType::NORMAL }
	};
public:
	Knight(const sf::Texture* texture, int position, Team team);

	std::vector<Piece::PossibleMove> getPossibleMoves();

	void calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces);

	void sayMyName();
};