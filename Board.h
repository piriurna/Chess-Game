#pragma once

class Board {
private:
	int nRows;
	int nColumns;
	int fileSize;
public:
	Board();

	void printBoard(const RenderWindow& window);

	//todo: change to a vector of pieces when definition is done
	//Maybe print pieces in a PieceManager instead of the actual board
	void printPieces(const RenderWindow& window, std::vector<int>& pieces);


	//--- GETTERS AND SETTERS
	int getNRows();
	void setNRows(int nRows);

	int getNColumns();
	void setNColumns(int nColumns);

	int getFileSize();
	void setFileSize(int fileSize);

};
