#include "Pawn.h"


Pawn::Pawn(const sf::Texture* texture, int position, Team team) {
	loadSprite(*texture);
	this->position = position;
	this->team = team;
	this->type = Type::PAWN;
};


struct ActualPosition {
	int X, Y;
};

void Pawn::calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) {
	MoveOffset initialMove = whiteMovesOffsets.at(3);
	if (team == Team::WHITE) {
		this->possibleMoves = getPossibleMovesForList(whiteMovesOffsets, pieces);
	}
	else if (team == Team::BLACK) {
		this->possibleMoves = getPossibleMovesForList(blackMovesOffsets, pieces);
	}
};


std::vector<Piece::PossibleMove> Pawn::getPossibleMovesForList(std::vector < Piece::MoveOffset> moveOffsets, std::vector<std::unique_ptr<Piece>>& pieces) {
	std::vector<Piece::PossibleMove> moves;
	ActualPosition actualPosition = { position % 8, position / 8 };
	std::vector<Intersection> intersectedPieces;
	for (int i = 0; i < moveOffsets.size(); i++) {
		int newX = actualPosition.X + moveOffsets.at(i).DX;
		int newY = actualPosition.Y + moveOffsets.at(i).DY;
		bool intersects = false;
		//If the move is inside the X coordinates of the board
		if (newX < 8 && newX >= 0) {
			//If the move is inside the Y coordinates of the board
			if (newY < 8 && newY >= 0) {
				//We add the move to the list of possible moves. We don't know which pieces are on the board so the check for Captures or possible obstructions need to be made with the response of this fucntion

				for (int pieceIndex = 0; pieceIndex < pieces.size(); pieceIndex++) {
					Piece& checkPiece = *pieces.at(pieceIndex);
					if (!checkPiece.getIsAlive()) continue;
					if (newX == checkPiece.getPositionVector().x &&
						newY == checkPiece.getPositionVector().y) {
						intersects = true;
						if (actualPosition.X > checkPiece.getPositionVector().x && actualPosition.Y == checkPiece.getPositionVector().y) {
							//if you are here the intersected piece is to the left
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::LEFT });
						}
						else if (actualPosition.X < checkPiece.getPositionVector().x && actualPosition.Y == checkPiece.getPositionVector().y) {
							//if you are here the intersected piece is to the right
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::RIGHT });
						}
						else if (actualPosition.Y > checkPiece.getPositionVector().y && actualPosition.X == checkPiece.getPositionVector().x) {
							//if you are here the intersected piece is to the top
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::UP });
						}
						else if (actualPosition.Y < checkPiece.getPositionVector().y && actualPosition.X == checkPiece.getPositionVector().x) {
							//if you are here the intersected piece is to the bottom
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::DOWN });
						}
						else if (actualPosition.Y > checkPiece.getPositionVector().y && actualPosition.X < checkPiece.getPositionVector().x) {
							//if you are here the intersected piece is to the bottom
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::UP_RIGHT });
						}
						else if (actualPosition.Y > checkPiece.getPositionVector().y && actualPosition.X > checkPiece.getPositionVector().x) {
							//if you are here the intersected piece is to the bottom
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::UP_LEFT });
						}
						else if (actualPosition.Y < checkPiece.getPositionVector().y && actualPosition.X < checkPiece.getPositionVector().x) {
							//if you are here the intersected piece is to the bottom
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::DOWN_RIGHT });
						}
						else if (actualPosition.Y < checkPiece.getPositionVector().y && actualPosition.X > checkPiece.getPositionVector().x) {
							//if you are here the intersected piece is to the bottom
							intersectedPieces.push_back(Intersection{ &checkPiece, Direction::DOWN_LEFT });
						}
						if (checkPiece.getTeam() != this->getTeam() && moveOffsets.at(i).moveType == MoveType::CAPTURE) {
							moves.push_back(
								PossibleMove{
									newX,
									newY,
									MoveType::CAPTURE
								}
							);
						}

						break;
					}
					//CHECK FOR EN_PASSANT
					else if((actualPosition.X + 1 == checkPiece.getPositionVector().x && newX > actualPosition.X ||
						actualPosition.X - 1 == checkPiece.getPositionVector().x && newX < actualPosition.X)  &&
						checkPiece.getLastMove() != nullptr &&
						(*checkPiece.getLastMove()).moveType == Piece::MoveType::INIT &&
						moveOffsets.at(i).moveType == Piece::MoveType::CAPTURE
						) {
						intersects = true;
						moves.push_back(
							PossibleMove{
								newX,
								newY,
								Piece::MoveType::EN_PASSANT
							}
						);
					}
				}

			}
		}
		if (!intersects) {
			if (newY < 8 && newY >= 0 && newX < 8 && newX >= 0) {
				if (moveOffsets.at(i).moveType == MoveType::NORMAL) {
					moves.push_back(
						PossibleMove{
							newX,
							newY,
							moveOffsets.at(i).moveType
						}
					);
				}
				else if (!this->hasMoved && moveOffsets.at(i).moveType == MoveType::INIT) {
					moves.push_back(
						PossibleMove{
							newX,
							newY,
							moveOffsets.at(i).moveType
						}
					);
				}
			}
		}
	}

	//This is confusing af, BUT, i had a list of Possible Moves, in order to have a list of pointers, i had to create m_moves. Now when it's ok i have to add that pointer to the new list but if at some point it was illegal, it will be
	//marked as illegal in the toExcludeMoves list. After we finish iterating over that, we run throught the list of all moves pointers and look if any of them is marked as to exclude. If it was not, we just add it to the final list.
	std::vector<Piece::PossibleMove> actualFinalMoves;
	std::vector<Piece::PossibleMove*> m_moves;
	std::vector<Piece::PossibleMove*> toExcludeMoves;
	for (int j = 0; j < moves.size(); j++) {
		Piece::PossibleMove* possibleMove = &moves.at(j);
		m_moves.push_back(possibleMove);
		for (int ii = 0; ii < intersectedPieces.size(); ii++) {
			Intersection intersection = intersectedPieces.at(ii);

			if (intersection.intersectionDirection == Piece::Direction::RIGHT && possibleMove->XCoord > intersection.intersectedPiece->getPositionVector().x && possibleMove->YCoord == intersection.intersectedPiece->getPositionVector().y ||
				intersection.intersectionDirection == Piece::Direction::LEFT && possibleMove->XCoord < intersection.intersectedPiece->getPositionVector().x && possibleMove->YCoord == intersection.intersectedPiece->getPositionVector().y ||
				intersection.intersectionDirection == Piece::Direction::DOWN && possibleMove->YCoord > intersection.intersectedPiece->getPositionVector().y && possibleMove->XCoord == intersection.intersectedPiece->getPositionVector().x ||
				intersection.intersectionDirection == Piece::Direction::UP && possibleMove->YCoord < intersection.intersectedPiece->getPositionVector().y && possibleMove->XCoord == intersection.intersectedPiece->getPositionVector().x ||
				intersection.intersectionDirection == Piece::Direction::UP_RIGHT && possibleMove->YCoord < intersection.intersectedPiece->getPositionVector().y && possibleMove->XCoord > intersection.intersectedPiece->getPositionVector().x ||
				intersection.intersectionDirection == Piece::Direction::UP_LEFT && possibleMove->YCoord < intersection.intersectedPiece->getPositionVector().y && possibleMove->XCoord < intersection.intersectedPiece->getPositionVector().x ||
				intersection.intersectionDirection == Piece::Direction::DOWN_RIGHT && possibleMove->YCoord > intersection.intersectedPiece->getPositionVector().y && possibleMove->XCoord > intersection.intersectedPiece->getPositionVector().x ||
				intersection.intersectionDirection == Piece::Direction::DOWN_LEFT && possibleMove->YCoord > intersection.intersectedPiece->getPositionVector().y && possibleMove->XCoord < intersection.intersectedPiece->getPositionVector().x
				) {
				toExcludeMoves.push_back(possibleMove);
				continue;
			}
		}
	}

	for (int f = 0; f < m_moves.size(); f++) {
		bool foundToExclude = false;
		for (int e = 0; e < toExcludeMoves.size(); e++) {
			if (m_moves.at(f) == toExcludeMoves.at(e)) {
				foundToExclude = true;
			}
		}
		if (!foundToExclude) {
			actualFinalMoves.push_back(*m_moves.at(f));
		}

	}
	return actualFinalMoves;
}

std::vector<Piece::PossibleMove> Pawn::getPossibleMoves() {
	return possibleMoves;
};


void Pawn::sayMyName() {
	if (team == Team::BLACK) {
		printf("Black Pawn");
	}
	else {
		printf("White Pawn");
	}
}
