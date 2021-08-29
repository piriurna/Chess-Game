#include "TextureManager.h"

void PieceManager::initialize(){
	whitePawnTexture.loadFromFile("graphics/WhitePawn.png");
	whiteBishopTexture.loadFromFile("graphics/WhiteBishop.png");
	whiteKnightTexture.loadFromFile("graphics/WhiteKnight.png");
	whiteRookTexture.loadFromFile("graphics/WhiteRook.png");
	whiteQueenTexture.loadFromFile("graphics/WhiteQueen.png");
	whiteKingTexture.loadFromFile("graphics/WhiteKing.png");

	imageList[PieceType::PAWN][PieceColor::WHITE_PIECE_ID] = sf::Sprite(whitePawnTexture);
	imageList[PieceType::BISHOP][PieceColor::WHITE_PIECE_ID] = sf::Sprite(whiteBishopTexture);
	imageList[PieceType::KNIGHT][PieceColor::WHITE_PIECE_ID] = sf::Sprite(whiteKnightTexture);
	imageList[PieceType::ROOK][PieceColor::WHITE_PIECE_ID] = sf::Sprite(whiteRookTexture);
	imageList[PieceType::QUEEN][PieceColor::WHITE_PIECE_ID] = sf::Sprite(whiteQueenTexture);
	imageList[PieceType::KING][PieceColor::WHITE_PIECE_ID] = sf::Sprite(whiteKingTexture);

	imageList[PieceType::PAWN][PieceColor::BLACK_PIECE_ID] = sf::Sprite(whitePawnTexture);
	imageList[PieceType::BISHOP][PieceColor::BLACK_PIECE_ID] = sf::Sprite(whiteBishopTexture);
	imageList[PieceType::KNIGHT][PieceColor::BLACK_PIECE_ID] = sf::Sprite(whiteKnightTexture);
	imageList[PieceType::ROOK][PieceColor::BLACK_PIECE_ID] = sf::Sprite(whiteRookTexture);
	imageList[PieceType::QUEEN][PieceColor::BLACK_PIECE_ID] = sf::Sprite(whiteQueenTexture);
	imageList[PieceType::KING][PieceColor::BLACK_PIECE_ID] = sf::Sprite(whiteKingTexture);
}

const sf::Sprite& PieceManager::getChessPieceImage(PieceType type, PieceColor color)
{
	return imageList[type][color];
}


