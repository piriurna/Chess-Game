#pragma once
#include "Piece.h"
#include <vector>


class Pawn : public Piece {

	//This is only a problem for Pawns, becase the direction of the movement is dependant on the team the pawn is in, i've made two lists. I could've calculated on the fly but this way is more orginized.
	std::vector<Piece::MoveOffset> blackMovesOffsets =
	{
		Piece::MoveOffset{ 0, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, 1, Piece::MoveType::CAPTURE },
		Piece::MoveOffset{ 1, 1, Piece::MoveType::CAPTURE },
		Piece::MoveOffset{ 0, 2, Piece::MoveType::INIT },
	};

	std::vector<Piece::MoveOffset> whiteMovesOffsets =
	{

		Piece::MoveOffset{ 0, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, -1, Piece::MoveType::CAPTURE },
		Piece::MoveOffset{ 1, -1, Piece::MoveType::CAPTURE },
		Piece::MoveOffset{ 0, -2, Piece::MoveType::INIT },
	};
public:
	Pawn(const sf::Texture* texture, int position, Team team);

	std::vector<Piece::PossibleMove> getPossibleMoves();

	std::vector<Piece::PossibleMove> getPossibleMovesForList(std::vector < Piece::MoveOffset> moveOffsets, std::vector<std::unique_ptr<Piece>>& pieces);

	void calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces);

	void sayMyName();
};
