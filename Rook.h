#pragma once
#include "Piece.h"
#include <vector>


class Rook : public Piece {
	std::vector<Piece::MoveOffset> moveOffsets =
	{
		Piece::MoveOffset{ 0, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, 2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, 3, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, 4, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, 5, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, 6, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, 7, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 1, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 2, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 3, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 4, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 5, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 6, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 7, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -3, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -4, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -5, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -6, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -7, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -2, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -3, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -4, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -5, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -6, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -7, 0, Piece::MoveType::NORMAL },
	};

public:
	Rook(const sf::Texture* texture, int position, Team team);

	std::vector<Piece::PossibleMove> getPossibleMoves();

	void calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces);
	std::vector<Piece::PossibleMove> getPossibleMovesForList(std::vector < Piece::MoveOffset> moveOffsets, std::vector<std::unique_ptr<Piece>>& pieces);

	void sayMyName();
};