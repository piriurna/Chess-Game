#include "King.h"


King::King(const sf::Texture* texture, int position, Team team) {
	loadSprite(*texture);
	this->position = position;
	this->team = team;
	this->type = Type::KING;
};



struct ActualPosition {
	int X, Y;
};

void King::calcPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) {
	MoveOffset initialMove = moveOffsets.at(3);
	if (team == Team::WHITE) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
	else if (team == Team::BLACK) {
		this->possibleMoves = getPossibleMovesForList(moveOffsets, pieces);
	}
};

std::vector<Piece::PossibleMove> King::getCleanPossibleMoves(std::vector<std::unique_ptr<Piece>>& pieces) {
	std::vector < Piece::PossibleMove> finalList;
	for (int moveIndex = 0; moveIndex < possibleMoves.size(); moveIndex++) {
		PossibleMove possibleMove = possibleMoves.at(moveIndex);
		bool wasKingHit = false;
		int oldPosition = this->position;
		this->position = possibleMove.YCoord * 8 + possibleMove.XCoord;
		for (int lookForPieceI = 0; lookForPieceI < pieces.size(); lookForPieceI++) {
			if (pieces.at(lookForPieceI)->equals(*this)) {
				pieces.at(lookForPieceI)->setPosition(possibleMove.YCoord * 8 + possibleMove.XCoord);
			}
		}
		bool canCastle = true;
		for (int enemyPieceIndex = 0; enemyPieceIndex < pieces.size(); enemyPieceIndex++) {
			Piece& enemyPiece = *pieces.at(enemyPieceIndex);
			if (enemyPiece.getTeam() == this->getTeam() || !enemyPiece.getPosition()) continue;

			enemyPiece.calcPossibleMoves(pieces);
			if (enemyPiece.getPositionVector().x == this->getPositionVector().x && enemyPiece.getPositionVector().y == this->getPositionVector().y) continue;	

			for (int piecePossMoveIndex = 0; piecePossMoveIndex < enemyPiece.getPossibleMoves().size(); piecePossMoveIndex++) {

				if (possibleMove.moveType == MoveType::CASTLE) {
					//if king is in check you cant castle
					if (enemyPiece.getPossibleMoves().at(piecePossMoveIndex).XCoord == oldPosition % 8 &&
						enemyPiece.getPossibleMoves().at(piecePossMoveIndex).YCoord == oldPosition / 8) {
						//king is hit, move is invalid
						canCastle = false;
						break;
					}

					//find the rook we are trying to castle with
					for (int findRookIndex = 0; findRookIndex < pieces.size(); findRookIndex++) {
						if (pieces.at(findRookIndex)->getType() == Type::ROOK && pieces.at(findRookIndex)->getTeam() == this->getTeam()) {
							Piece& rook = *pieces.at(findRookIndex);

							//Check if the rook we are trying to castle with has a free path
							for (int rookPathPosition = rook.getPosition(); rookPathPosition != this->getPosition(); ) {
								if (possibleMove.XCoord > oldPosition % 8) {
									//if you are here that means the king is going to the right so we have to move backwards

									//here we are going to see if any of the pieces are in our way
									for (int blockingPieceIndex = 0; blockingPieceIndex < pieces.size(); blockingPieceIndex++) {
										if (pieces.at(blockingPieceIndex)->equals(*this) || pieces.at(blockingPieceIndex)->equals(rook)) continue;
										if (pieces.at(blockingPieceIndex)->getPosition() == rookPathPosition && pieces.at(blockingPieceIndex)->getPositionVector().y == rook.getPositionVector().y) {
											//this means this piece is in our way, so we can't castle
											canCastle = false;
											break;// break the blockingPiece for
										}
									}
									rookPathPosition--;
									if (rookPathPosition <= this->getPosition() || !canCastle) {
										break;
									}
								}
								else if (possibleMove.XCoord < oldPosition % 8) {
									//if you are here that means the rook is to the left of the king, so we have to move forward

									for (int blockingPieceIndex = 0; blockingPieceIndex < pieces.size(); blockingPieceIndex++) {
										if (pieces.at(blockingPieceIndex)->equals(*this) || pieces.at(blockingPieceIndex)->equals(rook)) continue;
										if (pieces.at(blockingPieceIndex)->getPosition() == rookPathPosition && pieces.at(blockingPieceIndex)->getPositionVector().y == rook.getPositionVector().y) {
											//this means this piece is in our way, so we can't castle
											canCastle = false;
											break;// break the blockingPiece for
										}
									}
									rookPathPosition++;
									if (rookPathPosition >= this->getPosition() || !canCastle){
										break;
									}
								}
							}
						}
						if (!canCastle) {
							break;
						}
					}
				}

				if (enemyPiece.getPossibleMoves().at(piecePossMoveIndex).XCoord == this->getPositionVector().x &&
					enemyPiece.getPossibleMoves().at(piecePossMoveIndex).YCoord == this->getPositionVector().y) {
					//king is hit, move is invalid
					wasKingHit = true;
					break;
				}
			}
		}
		if (!wasKingHit && !(possibleMove.moveType == MoveType::CASTLE && !canCastle)) {
			finalList.push_back(possibleMove);
		}
		for (int lookForPieceI = 0; lookForPieceI < pieces.size(); lookForPieceI++) {
			if (pieces.at(lookForPieceI)->equals(*this)) {
				pieces.at(lookForPieceI)->setPosition(oldPosition);
			}
		}
	}

	return finalList;
};

std::vector<Piece::PossibleMove> King::getPossibleMoves() {
	return possibleMoves;
};


void King::sayMyName() {
	if (team == Team::BLACK) {
		printf("Black King");
	}
	else {
		printf("White King");
	}
}
