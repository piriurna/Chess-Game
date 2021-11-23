#include "Piece.h"
#include <iostream>


void Piece::loadSprite(const sf::Texture& texture) {
	this->pieceSprite.setTexture(texture);
};

sf::Sprite Piece::getSprite()
{
	return pieceSprite;
};

int Piece::getPosition() {
	return position;
};

sf::Vector2f Piece::getPositionVector() {
	int y = this->position / 8;
	int x = this->position % 8;

	return sf::Vector2f(x, y);
};

void Piece::setPosition(int newPosition)
{
	this->position = newPosition;
};

bool Piece::equals(Piece& other) {
	return position == other.getPosition() && type == other.type && team == other.team;
};

bool Piece::intersectsWith(Piece* other) {
	return this->getPositionVector().x == other->getPositionVector().x &&
		this->getPositionVector().y == other->getPositionVector().y;
}


std::vector<Piece::PossibleMove> Piece::getPossibleMovesForList(std::vector < Piece::MoveOffset> moveOffsets, std::vector<std::unique_ptr<Piece>>& pieces) {
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
					if (!checkPiece.isAlive) continue;
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
						if (checkPiece.getTeam() != this->getTeam()) {
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
				}

			}
		}

		if (!intersects && (newY < 8 && newY >= 0 && newX < 8 && newX >= 0 && moveOffsets.at(i).moveType == MoveType::CASTLE && !this->hasMoved && this->type == Type::KING)) {
			//FIND THE ROOK TO THE CORRECT SIDE
			for (int rookIndex = 0; rookIndex < pieces.size(); rookIndex++) {
				if (pieces.at(rookIndex)->getTeam() != this->getTeam() || pieces.at(rookIndex)->type != Type::ROOK) continue;

				if (!pieces.at(rookIndex)->getHasMoved() &&(
					(pieces.at(rookIndex)->getPositionVector().x > this->getPositionVector().x && newX > this->getPositionVector().x) ||
					(pieces.at(rookIndex)->getPositionVector().x < this->getPositionVector().x && newX < this->getPositionVector().x))) {
					moves.push_back(
						PossibleMove{
							newX,
							newY,
							MoveType::CASTLE
						}
					);
				}
			}
			
		}

		if (!intersects && newY < 8 && newY >= 0 && newX < 8 && newX >= 0 && moveOffsets.at(i).moveType == MoveType::NORMAL) {
			//check if it's "behind" another piece that is intersecting
			moves.push_back(
				PossibleMove{
					newX,
					newY,
					MoveType::NORMAL
				}
			);
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

			if (intersection.intersectionDirection == Piece::Direction::RIGHT && possibleMove->XCoord > intersection.intersectedPiece->getPositionVector().x && possibleMove->YCoord == intersection.intersectedPiece->getPositionVector().y  ||
				intersection.intersectionDirection == Piece::Direction::LEFT && possibleMove->XCoord < intersection.intersectedPiece->getPositionVector().x && possibleMove->YCoord == intersection.intersectedPiece->getPositionVector().y  ||
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
};


std::vector<Piece::PossibleMove> Piece::getCleanPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) {
	std::vector < Piece::PossibleMove> finalList;
	for (int moveIndex = 0; moveIndex < possibleMoves.size(); moveIndex++) {
		PossibleMove possibleMove = possibleMoves.at(moveIndex);
		bool wasKingHit = false;
		int oldPosition = this->position;

		//We have to pre move so the calculations are made in the new position
		this->position = possibleMove.YCoord * 8 + possibleMove.XCoord;
		for (int lookForPieceI = 0; lookForPieceI < pieces.size(); lookForPieceI++) {
			if (pieces.at(lookForPieceI)->equals(*this)) {
				pieces.at(lookForPieceI)->position = possibleMove.YCoord * 8 + possibleMove.XCoord;
			}
		}
		//for every enemy piece we gotta check if with this move we did up there, our king will be in check
		for (int enemyPieceIndex = 0; enemyPieceIndex < pieces.size(); enemyPieceIndex++) {
			Piece& enemyPiece = *pieces.at(enemyPieceIndex);
			if (enemyPiece.getTeam() == this->getTeam() || !enemyPiece.isAlive) continue;

			//calculate all moves for the enemy piece
			enemyPiece.calcPossibleMoves(pieces);

			if (enemyPiece.getPositionVector().x == this->getPositionVector().x && enemyPiece.getPositionVector().y == this->getPositionVector().y) continue;
			for (int piecePossMoveIndex = 0; piecePossMoveIndex < enemyPiece.getPossibleMoves().size(); piecePossMoveIndex++) {
				for (int pI = 0; pI < pieces.size(); pI++) {
					if (pieces.at(pI).get()->type != Type::KING || pieces.at(pI).get()->team != this->team) continue;

					if (enemyPiece.getPossibleMoves().at(piecePossMoveIndex).XCoord == pieces.at(pI).get()->getPositionVector().x &&
						enemyPiece.getPossibleMoves().at(piecePossMoveIndex).YCoord == pieces.at(pI).get()->getPositionVector().y) {
						//king is hit, move is invalid
						wasKingHit = true;
						break;
					}
				}
			}
		}

		if (!wasKingHit) {
			finalList.push_back(possibleMove);
		}
		for (int lookForPieceI = 0; lookForPieceI < pieces.size(); lookForPieceI++) {
			if (pieces.at(lookForPieceI)->equals(*this)) {
				pieces.at(lookForPieceI)->position = oldPosition;
			}
		}
	}

	return finalList;
};



std::vector<Piece::PossibleMove> Piece::getPossibleMoves() {
	return possibleMoves;
};


bool Piece::pushMove(int newPosition, std::vector<std::unique_ptr<Piece>>& pieces) {
	std::vector<Piece::PossibleMove> cleanPossibleMoves = getCleanPossibleMoves(pieces);
	for (int possibleMovesIndex = 0; possibleMovesIndex < cleanPossibleMoves.size(); possibleMovesIndex++) {
		PossibleMove possibleMove = cleanPossibleMoves.at(possibleMovesIndex);
		int position = possibleMove.YCoord * 8 + possibleMove.XCoord;
		if (newPosition == position) {
			if (possibleMove.moveType == MoveType::CASTLE) {
				for (int rookIndex = 0; rookIndex < pieces.size(); rookIndex++) {
					if (pieces.at(rookIndex)->getTeam() != this->getTeam() || pieces.at(rookIndex)->type != Type::ROOK || (
						(possibleMove.XCoord > this->getPositionVector().x && pieces.at(rookIndex)->getPositionVector().x < this->getPositionVector().x) ||
						(possibleMove.XCoord < this->getPositionVector().x && pieces.at(rookIndex)->getPositionVector().x > this->getPositionVector().x))) continue;

					if (pieces.at(rookIndex)->getPositionVector().x > this->getPositionVector().x) {
						pieces.at(rookIndex)->setPosition(newPosition - 1);
					}
					else if (pieces.at(rookIndex)->getPositionVector().x < this->getPositionVector().x) {
						pieces.at(rookIndex)->setPosition(newPosition + 1);
					}
					pieces.at(rookIndex)->hasMoved = true;
					pieces.at(rookIndex)->movesList.push_back({ this->position, newPosition, Piece::MoveType::NORMAL });
				}
			}
			else if (possibleMove.moveType == MoveType::EN_PASSANT) {
				for (int pieceIndex = 0; pieceIndex < pieces.size(); pieceIndex++) {
					//IF it intersects another piece, kill it;
					if (pieces.at(pieceIndex)->getPositionVector().x == possibleMove.XCoord &&
						pieces.at(pieceIndex)->getLastMove() != nullptr &&
						pieces.at(pieceIndex)->getLastMove()->moveType == Piece::MoveType::INIT
						) {
						pieces.at(pieceIndex)->killPiece();
					}
				}
				
			}
			else {
				
				for (int pieceIndex = 0; pieceIndex < pieces.size(); pieceIndex++) {
					//IF it intersects another piece, kill it;
					if (pieces.at(pieceIndex)->getPosition() == newPosition) {
						pieces.at(pieceIndex)->killPiece();
					}					
				}
			}

			for (int possibleMoveIndex = 0; possibleMoveIndex < cleanPossibleMoves.size(); possibleMoveIndex++) {
				if (cleanPossibleMoves.at(possibleMoveIndex).YCoord * 8 + cleanPossibleMoves.at(possibleMoveIndex).XCoord == newPosition) {
					this->movesList.push_back({ this->position, newPosition, cleanPossibleMoves.at(possibleMoveIndex).moveType });
					this->position = newPosition;
					this->hasMoved = true;
					return true;
				}
			}
		}
	}
	return false;
};

void Piece::setHasMoved(bool moved) {
	this->hasMoved = moved;
};

bool Piece::getHasMoved() const{
	return hasMoved;
};

void Piece::killPiece() {
	this->isAlive = false;
};

bool Piece::getIsAlive() const {
	return isAlive;
};


Team Piece::getTeam() const{
	return team;
};

Piece::Type Piece::getType() const{
	return type;
}

std::vector<Piece::Move> Piece::getMovesList() const{
	return movesList;
}

Piece::Move Piece::getMoveAt(int position) {
	return movesList.at(position);
}

Piece::Move* Piece::getLastMove() {
	if (movesList.size() > 0) {
		return &movesList.at(movesList.size() - 1);
	}
	
	return nullptr;
}
