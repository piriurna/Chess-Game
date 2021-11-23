#include <SFML/Graphics.hpp>;
#include "Board.h";
#include "Player.h";
#include "Basic Chess Game.h";
#include "TextureManager.h";
#include "Pawn.h";
#include "Knight.h";
#include "Rook.h";
#include "Bishop.h";
#include "Queen.h";
#include "King.h";
using namespace sf;


void readFen(std::string fen, TextureManager& textureManager, std::vector<std::unique_ptr<Piece>>& pieceList, int* playerIndex) {
	std::string delimiter = " ";
	std::string board = fen.substr(0, fen.find(delimiter));
	std::string turn = fen.substr(board.size() + 1, fen.find(delimiter));
	switch (turn.at(0)) {
	case 'w':
		*playerIndex = 0;
		break;
	case 'b':
		*playerIndex = 1;
		break;
	}
	std::vector<std::unique_ptr<Piece>> pieces;
	int fenIndex = 0;
	for (int row = 0; row <= 7; row++) {
		for (int file = 0; file <= 7; file++) {
			if (board.at(fenIndex) == '/') {
				fenIndex++;
			}

			if (isdigit(board.at(fenIndex))) {
				file += int(board.at(fenIndex) - '0');
				fenIndex++;
			}

			if (fenIndex < board.size()) {
				switch (board.at(fenIndex)) {
				case 'p':
					pieceList.push_back(std::make_unique<Pawn>(textureManager.getChessPieceTexture(Piece::Type::PAWN, Team::BLACK), row * 8 + file, Team::BLACK));
					break;
				case 'P':
					pieceList.push_back(std::make_unique<Pawn>(textureManager.getChessPieceTexture(Piece::Type::PAWN, Team::WHITE), row * 8 + file, Team::WHITE));
					break;
				case 'r':
					pieceList.push_back(std::make_unique<Rook>(textureManager.getChessPieceTexture(Piece::Type::ROOK, Team::BLACK), row * 8 + file, Team::BLACK));
					break;
				case 'R':
					pieceList.push_back(std::make_unique<Rook>(textureManager.getChessPieceTexture(Piece::Type::ROOK, Team::WHITE), row * 8 + file, Team::WHITE));
					break;
				case 'n':
					pieceList.push_back(std::make_unique<Knight>(textureManager.getChessPieceTexture(Piece::Type::KNIGHT, Team::BLACK), row * 8 + file, Team::BLACK));
					break;
				case 'N':
					pieceList.push_back(std::make_unique<Knight>(textureManager.getChessPieceTexture(Piece::Type::KNIGHT, Team::WHITE), row * 8 + file, Team::WHITE));
					break;
				case 'b':
					pieceList.push_back(std::make_unique<Bishop>(textureManager.getChessPieceTexture(Piece::Type::BISHOP, Team::BLACK), row * 8 + file, Team::BLACK));
					break;
				case 'B':
					pieceList.push_back(std::make_unique<Bishop>(textureManager.getChessPieceTexture(Piece::Type::BISHOP, Team::WHITE), row * 8 + file, Team::WHITE));
					break;
				case 'q':
					pieceList.push_back(std::make_unique<Queen>(textureManager.getChessPieceTexture(Piece::Type::QUEEN, Team::BLACK), row * 8 + file, Team::BLACK));
					break;
				case 'Q':
					pieceList.push_back(std::make_unique<Queen>(textureManager.getChessPieceTexture(Piece::Type::QUEEN, Team::WHITE), row * 8 + file, Team::WHITE));
					break;
				case 'k':
					pieceList.push_back(std::make_unique<King>(textureManager.getChessPieceTexture(Piece::Type::KING, Team::BLACK), row * 8 + file, Team::BLACK));
					break;
				case 'K':
					pieceList.push_back(std::make_unique<King>(textureManager.getChessPieceTexture(Piece::Type::KING, Team::WHITE), row * 8 + file, Team::WHITE));
					break;
				default:
					break;
				}
				fenIndex++;
			}
			
			
		}
	}
};

//returns if the turn has been completed
bool selectOrMovePiece(int x, int y, std::vector<std::unique_ptr<Piece>>* gamePieces, Player* currentPlayer, Board& board, Piece** selectedPiece) {
	if (*selectedPiece == nullptr) {
		*selectedPiece = board.getPieceInPosition(x, y, *gamePieces);
		if (*selectedPiece == nullptr || (*selectedPiece)->getTeam() != currentPlayer->getTeam()) {
			*selectedPiece = nullptr;
		}
		return false;
	}
	else {
		bool success = (*selectedPiece)->pushMove(board.getTileForCoordinate(x, y), *gamePieces);
		*selectedPiece = nullptr;
		if (success) {
			return true;
		}
		else {
			return false;
		}
	}
}
// This is where our game starts from
int main()
{

	int sw = 800;
	int sh = 800;

	int boardSize = sh;
	// Create a video mode object
	VideoMode vm(sw, sh);

	// Create and open a window for the game
	RenderWindow window(vm, "Chess");
	Board board(8,8, window.getSize().x / 8);

	sf::Color darkColor(50, 50, 0);
	sf::Color lightColor(255,255,255);

	TextureManager textureManager;
	
	std::vector<std::unique_ptr<Piece>> gamePieces;
	Player whitePlayer(Team::WHITE);

	Player blackPlayer(Team::BLACK);

	std::vector<Player*> players;
	players.push_back(&whitePlayer);
	players.push_back(&blackPlayer);
	int currentPlayerIndex = 0;

	readFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 12 55 ", textureManager, gamePieces, &currentPlayerIndex);


	Piece* selectedPiece = nullptr;


	board.printBoard(window, darkColor, lightColor);
	board.printPieces(window, gamePieces);
	window.display();
	Event event;
	static bool lock_left_click;
	while (window.isOpen()) {		
		while (window.waitEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if(event.mouseButton.button == Mouse::Button::Left && !lock_left_click){
				lock_left_click = true;
				window.clear();
				board.printBoard(window, darkColor, lightColor);
				bool isTurnCompleted = selectOrMovePiece(event.mouseButton.x, event.mouseButton.y, &gamePieces, players.at(currentPlayerIndex), board, &selectedPiece);
				if (selectedPiece != nullptr) {
					board.highlightPosibleMoves(*selectedPiece, &gamePieces, &window);
				}
				if (isTurnCompleted) {
					if (currentPlayerIndex >= players.size() - 1) {
						currentPlayerIndex = 0;
					}
					else {
						currentPlayerIndex++;
					}

					selectedPiece = nullptr;
				}

				
				board.printPieces(window, gamePieces);
				window.display();
				
				//TODO: Select the tile or piece. When a piece is already selected move it		
			}
			else if (event.type == Event::MouseButtonReleased) {
				lock_left_click = false;
			}
			else if (event.mouseButton.button == Mouse::Button::Right) {
				selectedPiece = nullptr;
				window.clear();
				board.printBoard(window, darkColor, lightColor);
				board.printPieces(window, gamePieces);
				window.display();

			}
			else if (event.type == Event::Resized) {
				//TODO: recalculate the tile size and sprite sizes
			}
		}
		
	}


	return 0;
};


