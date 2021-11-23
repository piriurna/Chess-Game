#pragma once
#include "Piece.h"
#include <vector>


class Bishop : public Piece {

	//This is only a problem for Pawns, becase the direction of the movement is dependant on the team the pawn is in, i've made two lists. I could've calculated on the fly but this way is more orginized.
	std::vector<Piece::MoveOffset> moveOffsets =
	{
		Piece::MoveOffset{ 1, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 2, 2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 3, 3, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 4, 4, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 5, 5, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 6, 6, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 7, 7, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -2, -2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -3, -3, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -4, -4, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -5, -5, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -6, -6, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -7, -7, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 1, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 2, -2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 3, -3, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 4, -4, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 5, -5, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 6, -6, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 7, -7, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -2, 2, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -3, 3, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -4, 4, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -5, 5, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -6, 6, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -7, 7, Piece::MoveType::NORMAL },
	};

public:
	Bishop(const sf::Texture* texture, int position, Team team);

	std::vector<Piece::PossibleMove> getPossibleMoves();

	void calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces);

	void sayMyName();
};