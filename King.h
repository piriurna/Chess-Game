#pragma once
#include "Piece.h"
#include <vector>


class King : public Piece {
private:
	//This is only a problem for Pawns, becase the direction of the movement is dependant on the team the pawn is in, i've made two lists. I could've calculated on the fly but this way is more orginized.
	std::vector<Piece::MoveOffset> moveOffsets =
	{
		Piece::MoveOffset{ 0, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 1, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 0, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, 0, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 1, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 1, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, 1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ -1, -1, Piece::MoveType::NORMAL },
		Piece::MoveOffset{ 2, 0, Piece::MoveType::CASTLE },
		Piece::MoveOffset{ -2, 0, Piece::MoveType::CASTLE },
	};
public:
	King(const sf::Texture* texture, int position, Team team);

	std::vector<Piece::PossibleMove> getPossibleMoves();

	void calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces);

	std::vector<Piece::PossibleMove> getCleanPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces);

	void sayMyName();
};