#include "TextureManager.h";

void TextureManager::initialize() {
	whitePawnTexture.loadFromFile("graphics/WhitePawn.png");
	whiteBishopTexture.loadFromFile("graphics/WhiteBishop.png");
	whiteKnightTexture.loadFromFile("graphics/WhiteKnight.png");
	whiteRookTexture.loadFromFile("graphics/WhiteRook.png");
	whiteQueenTexture.loadFromFile("graphics/WhiteQueen.png");
	whiteKingTexture.loadFromFile("graphics/WhiteKing.png");

	blackPawnTexture.loadFromFile("graphics/BlackPawn.png");
	blackBishopTexture.loadFromFile("graphics/BlackBishop.png");
	blackKnightTexture.loadFromFile("graphics/BlackKnight.png");
	blackRookTexture.loadFromFile("graphics/BlackRook.png");
	blackQueenTexture.loadFromFile("graphics/BlackQueen.png");
	blackKingTexture.loadFromFile("graphics/BlackKing.png");

	imageList[int(Piece::Type::PAWN)][int(Team::WHITE)] = &whitePawnTexture;
	imageList[int(Piece::Type::BISHOP)][int(Team::WHITE)] = &whiteBishopTexture;
	imageList[int(Piece::Type::KNIGHT)][int(Team::WHITE)] = &whiteKnightTexture;
	imageList[int(Piece::Type::ROOK)][int(Team::WHITE)] = &whiteRookTexture;
	imageList[int(Piece::Type::QUEEN)][int(Team::WHITE)] = &whiteQueenTexture;
	imageList[int(Piece::Type::KING)][int(Team::WHITE)] = &whiteKingTexture;

	imageList[int(Piece::Type::PAWN)][int(Team::BLACK)] = &blackPawnTexture;
	imageList[int(Piece::Type::BISHOP)][int(Team::BLACK)] = &blackBishopTexture;
	imageList[int(Piece::Type::KNIGHT)][int(Team::BLACK)] = &blackKnightTexture;
	imageList[int(Piece::Type::ROOK)][int(Team::BLACK)] = &blackRookTexture;
	imageList[int(Piece::Type::QUEEN)][int(Team::BLACK)] = &blackQueenTexture;
	imageList[int(Piece::Type::KING)][int(Team::BLACK)] = &blackKingTexture;
};

const sf::Texture* TextureManager::getChessPieceTexture(Piece::Type type, Team color) {
	return imageList[int(type)][int(color)];
};


TextureManager::TextureManager() {
	initialize();
}


