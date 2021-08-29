#include <SFML/Graphics.hpp>;
#include "Board.h"
#include "Player.h"
using namespace sf;


//TODO:REFACTOR THIS ENTIRELY
std::vector<Piece> readFen(std::string fen) {
	std::string delimiter = " ";
	std::string board = fen.substr(0, fen.find(delimiter));
	std::vector<Piece> pieces;
	int fenIndex = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board.at(fenIndex) == '/') {
				fenIndex++;
				continue;
			}
			if (isdigit(board.at(fenIndex))) {
				j += board.at(fenIndex);
			}
			else {
				//get piece type and create a piece with the position;
			}
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

	sf::Color darkColor(0, 0, 0);
	sf::Color lightColor(255,255,255);
	
	//START FROM FEN
	//rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPPP/RNBQKBNR

	Event event;
	while (window.isOpen()) {
		window.clear();
		board.printBoard(window, darkColor, lightColor);
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if(event.type == Event::MouseButtonPressed){
				//TODO: Select the tile or piece. When a piece is already selected move it		
			}
			else if (event.type == Event::Resized) {
				//TODO: recalculate the tile size and sprite sizes
			}
		}
		
		window.display();
	}


	return 0;
};


