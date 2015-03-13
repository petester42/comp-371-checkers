/**
 *======================================================================
 *  Student#1: Angelo Pulcini		Student ID: 3946703
 *  Student#2: Jonathan Evans		Student ID: 5201713
 *  Course: COMP 472                Section:  Lec F
 *  Instructor: Sabine Bergler
 *  Assignment #2
 *  
 *  Description:
 *  This is the implementation file for the gameLogic class.
 *  
 *======================================================================
 */
#include "stdafx.h"
#include "gameLogic.h"
#include <iomanip>

gameLogic::gameLogic()
{
	blackScore = 0;
	whiteScore = 0;
	turn = 0;

	initializeValues();
	calculateCurrentScore();
}


gameLogic::gameLogic(int firstBlack, int firstWhite, int secondBlack, int secondWhite)
{
	blackScore = 0;
	whiteScore = 0;
	turn = 0;

	initializeValues(firstBlack, firstWhite, secondBlack, secondWhite);
	calculateCurrentScore();
}


gameLogic::gameLogic(const gameLogic &g)
{
	emptyBoard = g.emptyBoard;
	downMask = g.downMask;
	upMask = g.upMask;
	rightMask = g.rightMask;
	leftMask = g.leftMask;
	leftTopMask = g.leftTopMask;
	leftDownMask = g.leftDownMask;
	rightTopMask = g.rightTopMask;
	rightDownMask = g.rightDownMask;
	blackPieces = g.blackPieces;
	whitePieces = g.whitePieces;
	blackScore = g.blackScore;
	whiteScore = g.whiteScore;
	turn = g.turn;
}


gameLogic::~gameLogic()
{

}


gameLogic& gameLogic::operator =(const gameLogic& g)
{
	if(this != &g)
	{
		emptyBoard = g.emptyBoard;
		downMask = g.downMask;
		upMask = g.upMask;
		rightMask = g.rightMask;
		leftMask = g.leftMask;
		leftTopMask = g.leftTopMask;
		leftDownMask = g.leftDownMask;
		rightTopMask = g.rightTopMask;
		rightDownMask = g.rightDownMask;
		blackPieces = g.blackPieces;
		whitePieces = g.whitePieces;
		blackScore = g.blackScore;
		whiteScore = g.whiteScore;
		turn = g.turn;
	}
	return *this;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::generateAcceptedMoves(int player, int index)
{
	bitset<BIT_DEPTH> potentialMoves;
	if(player == 0)
	{
		bitset<BIT_DEPTH> selectedPos, checkDirections;
		selectedPos.set(convertIndex(index), 1);
		checkDirections = selectedPos & blackQueenMask;

		if(checkDirections != emptyBoard)
		{
			potentialMoves |= calculateLeftTop(selectedPos, blackPieces, whitePieces, leftTopMask);
			potentialMoves |= calculateRightUp(selectedPos, blackPieces, whitePieces, rightTopMask);
		}
		else
		{
			potentialMoves |= calculateLeftTop(selectedPos, blackPieces, whitePieces, leftTopMask);
			potentialMoves |= calculateLeftDown(selectedPos, blackPieces, whitePieces, leftDownMask);
			potentialMoves |= calculateRightUp(selectedPos, blackPieces, whitePieces, rightTopMask);
			potentialMoves |= calculateRightDown(selectedPos, blackPieces, whitePieces, rightDownMask);
		}
	}
	else if(player == 1)
	{
		bitset<BIT_DEPTH> selectedPos, checkDirections;
		selectedPos.set(convertIndex(index), 1);
		checkDirections = selectedPos & whiteQueenMask;

		if(checkDirections != emptyBoard)
		{
			potentialMoves |= calculateLeftDown(selectedPos, whitePieces, blackPieces, leftDownMask);
			potentialMoves |= calculateRightDown(selectedPos, whitePieces, blackPieces, rightDownMask);
		}
		else
		{
			potentialMoves |= calculateLeftTop(selectedPos, whitePieces, blackPieces, leftTopMask);
			potentialMoves |= calculateLeftDown(selectedPos, whitePieces, blackPieces, leftDownMask);
			potentialMoves |= calculateRightUp(selectedPos, whitePieces, blackPieces, rightTopMask);
			potentialMoves |= calculateRightDown(selectedPos, whitePieces, blackPieces, rightDownMask);
		}
	}

	return convertBitset(potentialMoves);
}


bitset<gameLogic::BIT_DEPTH> gameLogic::generateAcceptedMoves(int player, bitset<BIT_DEPTH> black, bitset<BIT_DEPTH> white)
{
	bitset<BIT_DEPTH> potentialMoves;

	if(player == 0)
	{
		//potentialMoves |= calculateLeftTop(black, white, leftTopMask);
		//potentialMoves |= calculateLeftDown(black, white, leftDownMask);
		//potentialMoves |= calculateRightUp(black, white, rightTopMask);
		//potentialMoves |= calculateRightDown(black, white, rightDownMask);
	}
	else if(player == 1)
	{
		//potentialMoves |= calculateLeftTop(white, black, leftTopMask);
		//potentialMoves |= calculateLeftDown(white, black, leftDownMask);
		//potentialMoves |= calculateRightUp(white, black, rightTopMask);
		//potentialMoves |= calculateRightDown(white, black, rightDownMask);
	}

	return potentialMoves;
}


void gameLogic::generateChildren(int player, bitset<BIT_DEPTH> black, bitset<BIT_DEPTH> white, vector<element*>& children)
{
	bitset<BIT_DEPTH> moves;

	moves = generateAcceptedMoves(player, black, white);
	for(int counter = 0; counter != BIT_DEPTH; ++counter)
	{
		if(moves[counter] == 1)
		{
			bitset<BIT_DEPTH> temp;
			temp.set(counter);
			bitset<BIT_DEPTH> temp2 = black;
			bitset<BIT_DEPTH> temp3 = white;
			performMove(player, temp, temp2, temp3);
			element* result = new element();
			result->black = temp2;
			result->white = temp3;
			children.push_back(result);
		}
	}
}


void gameLogic::performMove(int player, bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> originalPosition)
{
	bitset<BIT_DEPTH> pointsToCapture;
	bitset<BIT_DEPTH> internalIntended = convertBitset(intendedMove);
	bitset<BIT_DEPTH> internalOriginal = convertBitset(originalPosition);
	int intendedIndex = retrieveIndex(internalIntended);
	int originalIndex = retrieveIndex(internalOriginal);

	if(player == 0)
	{
		if((intendedIndex > originalIndex) && ((intendedIndex % 8) > (originalIndex % 8)))
			pointsToCapture |= captureLeftTop(internalIntended, internalOriginal, blackPieces, whitePieces, leftTopMask);
		else if((intendedIndex > originalIndex)  && ((intendedIndex % 8) < (originalIndex % 8)))
			pointsToCapture |= captureRightTop(internalIntended, internalOriginal, blackPieces, whitePieces, rightTopMask);
		else if((intendedIndex < originalIndex)  && ((intendedIndex % 8) > (originalIndex % 8)))
			pointsToCapture |= captureLeftDown(internalIntended, internalOriginal, blackPieces, whitePieces, leftDownMask);
		else if((intendedIndex < originalIndex)  && ((intendedIndex % 8) < (originalIndex % 8))) 
			pointsToCapture |= captureRightDown(internalIntended, internalOriginal, blackPieces, whitePieces, rightDownMask);

		//blackPieces |= pointsToCapture;
		blackPieces |= internalIntended;
		blackPieces ^= internalOriginal;
		whitePieces ^= pointsToCapture;
	}
	else if(player == 1)
	{
		if((intendedIndex > originalIndex) && ((intendedIndex % 8) > (originalIndex % 8)))
			pointsToCapture |= captureLeftTop(internalIntended, internalOriginal, whitePieces, blackPieces, leftTopMask);
		else if((intendedIndex > originalIndex)  && ((intendedIndex % 8) < (originalIndex % 8)))
			pointsToCapture |= captureRightTop(internalIntended, internalOriginal, whitePieces, blackPieces, rightTopMask);
		else if((intendedIndex < originalIndex)  && ((intendedIndex % 8) > (originalIndex % 8)))
			pointsToCapture |= captureLeftDown(internalIntended, internalOriginal, whitePieces, blackPieces, leftDownMask);
		else if((intendedIndex < originalIndex)  && ((intendedIndex % 8) < (originalIndex % 8)))
			pointsToCapture |= captureRightDown(internalIntended, internalOriginal, whitePieces, blackPieces, rightDownMask);

		//whitePieces |= pointsToCapture;
		whitePieces |= internalIntended;
		whitePieces ^= internalOriginal;
		blackPieces ^= pointsToCapture;
	}

	turn = !turn;
}


void gameLogic::performMove(int player, bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH>& black, bitset<BIT_DEPTH>& white)
{
	bitset<BIT_DEPTH> pointsToCapture;

	if(player == 0)
	{
/*		pointsToCapture |= captureUp(intendedMove, white, black, upMask);
		pointsToCapture |= captureDown(intendedMove, white, black, downMask);
		pointsToCapture |= captureLeft(intendedMove, white, black, leftMask);
		pointsToCapture |= captureRight(intendedMove, white, black, rightMask);
		pointsToCapture |= captureLeftTop(intendedMove, white, black, leftTopMask);
//		pointsToCapture |= captureLeftDown(intendedMove, white, black, leftDownMask);
		pointsToCapture |= captureRightTop(intendedMove, white, black, rightTopMask);
		pointsToCapture |= captureRightDown(intendedMove, white, black, rightDownMask);*/

		black |= pointsToCapture;
		black |= intendedMove;
		white ^= pointsToCapture;
	}
	else if(player == 1)
	{
/*		pointsToCapture |= captureUp(intendedMove, black, white, upMask);
		pointsToCapture |= captureDown(intendedMove, black, white, downMask);
		pointsToCapture |= captureLeft(intendedMove, black, white, leftMask);
		pointsToCapture |= captureRight(intendedMove, black, white, rightMask);
		pointsToCapture |= captureLeftTop(intendedMove, black, white, leftTopMask);
//		pointsToCapture |= captureLeftDown(intendedMove, black, white, leftDownMask);
		pointsToCapture |= captureRightTop(intendedMove, black, white, rightTopMask);
		pointsToCapture |= captureRightDown(intendedMove, black, white, rightDownMask);*/

		white |= pointsToCapture;
		white |= intendedMove;
		black ^= pointsToCapture;
	}
}


bool gameLogic::verifyMove(int player, bitset<BIT_DEPTH> intendedMove)
{
	bitset<BIT_DEPTH> possibleMoves;

	//may be some problem
	if(player == 0)
	{
		possibleMoves = generateAcceptedMoves(1, 1);
		possibleMoves = generateAcceptedMoves(0,intendedMove.at(0));
	}
	else if(player == 1)
	{
		possibleMoves = generateAcceptedMoves(2, 1);

		possibleMoves = generateAcceptedMoves(1,intendedMove.at(0));
	}
	
	return (possibleMoves & intendedMove) != emptyBoard;
}


int gameLogic::getBlackScore()
{
	calculateCurrentScore();
	return blackScore;
}


int gameLogic::getWhiteScore()
{
	calculateCurrentScore();
	return whiteScore;
}

bitset<gameLogic::BIT_DEPTH> gameLogic::getWhiteBoard()
{
	return whitePieces;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::getBlackBoard()
{
	return blackPieces;
}


bool gameLogic::getTurn()
{
	return turn;
}


void gameLogic::switchTurn()
{
	turn = !turn;
}


int gameLogic::checkWinner()
{
	if(!gameCanStillPlay())
	{
		if(getBlackScore() > getWhiteScore())
			return 1;
		else if(getWhiteScore() > getBlackScore())
			return 2;
		else
			return 0;
	}
	return -1;
}


bool gameLogic::gameCanStillPlay()
{
	bool result;
	if(getTurn())
		result = (whiteHasMoves() && boardHasSpaces() && (getBlackScore() != 0) && (getWhiteScore() != 0));
	else
		result = (blackHasMoves() && boardHasSpaces() && (getBlackScore() != 0) && (getWhiteScore() != 0));

	return result;
}


bool gameLogic::boardHasSpaces()
{
	bitset<64> emptyPos = blackPieces | whitePieces;
	emptyPos.flip();

	return (emptyPos != emptyBoard);
}


bool gameLogic::blackHasMoves()
{
	bitset<64> potentialMoves;

	potentialMoves |= calculateDown(blackPieces, whitePieces, downMask);
	potentialMoves |= calculateUp(blackPieces, whitePieces, upMask);
	potentialMoves |= calculateLeft(blackPieces, whitePieces, leftMask);
	potentialMoves |= calculateRight(blackPieces, whitePieces, rightMask);
//	potentialMoves |= calculateLeftTop(blackPieces, whitePieces, leftTopMask);
//	potentialMoves |= calculateLeftDown(blackPieces, whitePieces, leftDownMask);
//	potentialMoves |= calculateRightUp(blackPieces, whitePieces, rightTopMask);
//	potentialMoves |= calculateRightDown(blackPieces, whitePieces, rightDownMask);

	return (!potentialMoves.none());
}

bool gameLogic::whiteHasMoves()
{
	bitset<64> potentialMoves;

	potentialMoves |= calculateDown(whitePieces, blackPieces, downMask);
	potentialMoves |= calculateUp(whitePieces, blackPieces, upMask);
	potentialMoves |= calculateLeft(whitePieces, blackPieces, leftMask);
	potentialMoves |= calculateRight(whitePieces, blackPieces, rightMask);
//	potentialMoves |= calculateLeftTop(whitePieces, blackPieces, leftTopMask);
//	potentialMoves |= calculateLeftDown(whitePieces, blackPieces, leftDownMask);
//	potentialMoves |= calculateRightUp(whitePieces, blackPieces, rightTopMask);
//	potentialMoves |= calculateRightDown(whitePieces, blackPieces, rightDownMask);

	return (!potentialMoves.none());
}


bool gameLogic::isBlack(int index)
{
	return(blackPieces[index] != 0);
}


bool gameLogic::isWhite(int index)
{
	return(whitePieces[index] != 0);
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateDown(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;
	while(temp != emptyBoard)
	{
		temp = (temp >> 8) & mask;
		if(count >= 1)
			positions ^= temp;
		count += 1;
		temp &= secondPlayer;
	}

	positions &= emptyPos;

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateUp(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;
	while(temp != emptyBoard)
	{
		temp = (temp << 8) & mask;
		if(count >= 1)
			positions ^= temp;
		count += 1;
		temp &= secondPlayer;
	}

	positions &= emptyPos;

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateLeft(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;
	while(temp != emptyBoard)
	{
		temp = (temp << 1) & mask;
		if(count >= 1)
			positions ^= temp;
		count += 1;
		temp &= secondPlayer;
	}

	positions &= emptyPos;

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateRight(bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;
	while(temp != emptyBoard)
	{
		temp = (temp >> 1) & mask;
		if(count >= 1)
			positions ^= temp;
		count += 1;
		temp &= secondPlayer;
	}

	positions &= emptyPos;

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateLeftTop(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();
	bitset<64> emptySec = emptyPos | secondPlayer;

	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;

	while(temp != emptyBoard)
	{
		temp = (temp << 1);
		temp = (temp << 8) & mask;
		
		bitset<64> tempCurrent = temp & currentPlayer;
		temp ^= tempCurrent;

		if(count == 0)
			temp &= emptySec;

		count += 1;
		positions ^= (temp ^ secondPlayer);
		temp &= secondPlayer;
	}

	positions &= emptyPos;  //First while loop obtains the empty positions
	bitset<BIT_DEPTH> restriction;
	int counter = 0;

	while(counter < 2)
	{
		targetPiece = (targetPiece << 1);
		targetPiece = (targetPiece << 8) & mask;
		
		if(((targetPiece & currentPlayer) != emptyBoard) && (counter != 1))
		{
			restriction = emptyBoard;
			break;
		}
		restriction |= targetPiece & positions;
		counter += 1;
	}
	//restriction ^= currentPlayer;
	return restriction;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateLeftDown(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();
	bitset<64> emptySec = emptyPos | secondPlayer;


	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;
	while(temp != emptyBoard)
	{
		temp = (temp << 1);
		temp = (temp >> 8) & mask;
		bitset<64> tempCurrent = temp & currentPlayer;
		temp ^= tempCurrent;
		if(count == 0)
			temp &= emptySec;
		count += 1;
		positions ^= (temp ^ secondPlayer);
		temp &= secondPlayer;
	}

	positions &= emptyPos;

	bitset<BIT_DEPTH> restriction;
	int counter = 0;
	while(counter < 2)
	{
		targetPiece = (targetPiece << 1);
		targetPiece = (targetPiece >> 8) & mask;

		if(((targetPiece & currentPlayer) != emptyBoard) && (counter != 1))
		{
			restriction = emptyBoard;
			break;
		}

		restriction |= targetPiece & positions;
		counter += 1;
	}
	//restriction ^= currentPlayer;
	return restriction;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateRightUp(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();
	bitset<64> emptySec = emptyPos | secondPlayer;

	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;
	while(temp != emptyBoard)
	{
		temp = (temp >> 1);
		temp = (temp << 8) & mask;
		bitset<64> tempCurrent = temp & currentPlayer;
		temp ^= tempCurrent;
		if(count == 0)
			temp &= emptySec;
		count += 1;
		positions ^= (temp ^ secondPlayer);
		temp &= secondPlayer;
	}

	positions &= emptyPos;

	bitset<BIT_DEPTH> restriction;
	int counter = 0;
	while(counter < 2)
	{
		targetPiece = (targetPiece >> 1);
		targetPiece = (targetPiece << 8) & mask;
		//targetPiece ^= currentPlayer;

		if(((targetPiece & currentPlayer) != emptyBoard) && (counter != 1))
		{
			restriction = emptyBoard;
			break;
		}

		restriction |= targetPiece & positions;
		counter += 1;
	}
	//restriction ^= currentPlayer;
	return restriction;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::calculateRightDown(bitset<BIT_DEPTH> targetPiece, bitset<BIT_DEPTH> currentPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = currentPlayer | secondPlayer;
	emptyPos.flip();
	bitset<64> emptySec = emptyPos | secondPlayer;

	bitset<64> temp = currentPlayer;
	bitset<64> positions;
	int count = 0;
	while(temp != emptyBoard)
	{
		temp = (temp >> 1);
		temp = (temp >> 8) & mask;
		bitset<64> tempCurrent = temp & currentPlayer;
		temp ^= tempCurrent;
		if(count == 0)
			temp &= emptySec;
		count += 1;
		positions ^= (temp ^ secondPlayer);
		temp &= secondPlayer;
	}

	positions &= emptyPos;

	bitset<BIT_DEPTH> restriction;
	int counter = 0;
	while(counter < 2)
	{
		targetPiece = (targetPiece >> 1);
		targetPiece = (targetPiece >> 8) & mask;
		//targetPiece ^= currentPlayer;

		if(((targetPiece & currentPlayer) != emptyBoard) && (counter != 1))
		{
			restriction = emptyBoard;
			break;
		}

		restriction |= targetPiece & positions;
		counter += 1;
	}
	//restriction ^= currentPlayer;
	return restriction;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureUp(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = intendedMove | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = intendedMove;
	bitset<64> positions;
	
	while(temp != emptyBoard)
	{
		temp = (temp << 8) & mask;
		if((temp & firstPlayer) != emptyBoard)
			break;
		if((temp & secondPlayer) == emptyBoard)
			if((temp & firstPlayer) == emptyBoard)
				return emptyBoard;
		else
			temp &= secondPlayer;

		positions |= temp;
	}

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureDown(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = intendedMove | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = intendedMove;
	bitset<64> positions;

	while(temp != emptyBoard)
	{
		temp = (temp >> 8) & mask;
		if((temp & firstPlayer) != emptyBoard)
			break;
		if((temp & secondPlayer) == emptyBoard)
			if((temp & firstPlayer) == emptyBoard)
				return emptyBoard;
		else
			temp &= secondPlayer;

		positions |= temp;
	}

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureLeft(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = intendedMove | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = intendedMove;
	bitset<64> positions;

	while(temp != emptyBoard)
	{
		temp = (temp << 1) & mask;
		if((temp & firstPlayer) != emptyBoard)
			break;
		if((temp & secondPlayer) == emptyBoard)
			if((temp & firstPlayer) == emptyBoard)
				return emptyBoard;
		else
			temp &= secondPlayer;

		positions |= temp;
	}

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureRight(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> mask)
{
	bitset<64> emptyPos = intendedMove | secondPlayer;
	emptyPos.flip();

	bitset<64> temp = intendedMove;
	bitset<64> positions;

	while(temp != emptyBoard)
	{
		temp = (temp >> 1) & mask;
		if((temp & firstPlayer) != emptyBoard)
			break;
		if((temp & secondPlayer) == emptyBoard)
			if((temp & firstPlayer) == emptyBoard)
				return emptyBoard;
		else
			temp &= secondPlayer;

		positions |= temp;
	}

	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureLeftTop(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	int counter = 0;

	bitset<64> temp = previousPosition;
	bitset<64> positions;
	bitset<BIT_DEPTH> combinedEmpty = firstPlayer | secondPlayer;
	combinedEmpty.flip();

	while((temp != intendedMove) && (counter < 2))
	{
		temp = (temp << 1);
		temp = (temp << 8) & mask;
		
		if(((temp & firstPlayer) != emptyBoard) || (((temp & combinedEmpty) != emptyBoard) && counter == 0))
		{
			positions = emptyBoard;
			break;
		}

		positions |= temp & secondPlayer;
		counter += 1;
	}
	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureLeftDown(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	int counter = 0;

	bitset<64> temp = previousPosition;
	bitset<64> positions;
	bitset<BIT_DEPTH> combinedEmpty = firstPlayer | secondPlayer;
	combinedEmpty.flip();

	while(((temp & firstPlayer) != emptyBoard) || (((temp & combinedEmpty) != emptyBoard) && counter == 0))
	{
		temp = (temp << 1);
		temp = (temp >> 8) & mask;
		
		if((temp & firstPlayer) != emptyBoard)
		{
			positions = emptyBoard;
			break;
		}

		positions |= temp & secondPlayer;
		counter += 1;
	}
	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureRightTop(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	int counter = 0;

	bitset<64> temp = previousPosition;
	bitset<64> positions;
	bitset<BIT_DEPTH> combinedEmpty = firstPlayer | secondPlayer;
	combinedEmpty.flip();

	while(((temp & firstPlayer) != emptyBoard) || (((temp & combinedEmpty) != emptyBoard) && counter == 0))
	{
		temp = (temp >> 1);
		temp = (temp << 8) & mask;
		
		if((temp & firstPlayer) != emptyBoard)
		{
			positions = emptyBoard;
			break;
		}
		
		positions |= temp & secondPlayer;
		counter += 1;
	}
	return positions;
}


bitset<gameLogic::BIT_DEPTH> gameLogic::captureRightDown(bitset<BIT_DEPTH> intendedMove, bitset<BIT_DEPTH> previousPosition, bitset<BIT_DEPTH> firstPlayer, bitset<BIT_DEPTH> secondPlayer, bitset<BIT_DEPTH> mask)
{
	int counter = 0;

	bitset<64> temp = previousPosition;
	bitset<64> positions;
	bitset<BIT_DEPTH> combinedEmpty = firstPlayer | secondPlayer;
	combinedEmpty.flip();

	while(((temp & firstPlayer) != emptyBoard) || (((temp & combinedEmpty) != emptyBoard) && counter == 0))
	{
		temp = (temp >> 1);
		temp = (temp >> 8) & mask;

		if((temp & firstPlayer) != emptyBoard)
		{
			positions = emptyBoard;
			break;
		}

		positions |= temp & secondPlayer;
		counter += 1;
	}
	return positions;
}


ostream& operator<< (ostream& outs, gameLogic& g)
{
	bitset<gameLogic::BIT_DEPTH> temp;
	temp |= g.blackPieces;
	temp |= g.whitePieces;

	outs << setiosflags(ios::right);
	for(int counter = gameLogic::BIT_DEPTH - 1; counter != -1; --counter)
	{
		outs << setw(2) << temp[counter];
		if(counter % 8 == 0)
			outs << endl;
	}

	return outs;
}


void gameLogic::calculateCurrentScore()
{
	blackScore = 0;
	whiteScore = 0;

	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{
		blackScore += blackPieces[counter];
		whiteScore += whitePieces[counter];		
	}
}


void gameLogic::output(ostream& outs, bitset<BIT_DEPTH> board)
{
	for(int counter = BIT_DEPTH - 1; counter != -1; --counter)
	{
		outs << board[counter];
		if(counter % 8 == 0)
			outs << endl;
	}
}


void gameLogic::initializeValues()
{
	blackPieces.set(1);
	blackPieces.set(3);
	blackPieces.set(5);
	blackPieces.set(7);
	blackPieces.set(8);
	blackPieces.set(10);
	blackPieces.set(12);
	blackPieces.set(14);
	blackPieces.set(17);
	blackPieces.set(19);
	blackPieces.set(21);
	blackPieces.set(23);

	whitePieces.set(40);
	whitePieces.set(42);
	whitePieces.set(44);
	whitePieces.set(46);
	whitePieces.set(49);
	whitePieces.set(51);
	whitePieces.set(53);
	whitePieces.set(55);
	whitePieces.set(56);
	whitePieces.set(58);
	whitePieces.set(60);
	whitePieces.set(62);

	downMask.set(63);
	downMask.set(62);
	downMask.set(61);
	downMask.set(60);
	downMask.set(59);
	downMask.set(58);
	downMask.set(57);
	downMask.set(56);
	downMask.flip();

	blackQueenMask.set(63);
	blackQueenMask.set(62);
	blackQueenMask.set(61);
	blackQueenMask.set(60);
	blackQueenMask.set(59);
	blackQueenMask.set(58);
	blackQueenMask.set(57);
	blackQueenMask.set(56);
	blackQueenMask.flip();

	upMask.set(7);
	upMask.set(6);
	upMask.set(5);
	upMask.set(4);
	upMask.set(3);
	upMask.set(2);
	upMask.set(1);
	upMask.set(0);
	upMask.flip();

	whiteQueenMask.set(7);
	whiteQueenMask.set(6);
	whiteQueenMask.set(5);
	whiteQueenMask.set(4);
	whiteQueenMask.set(3);
	whiteQueenMask.set(2);
	whiteQueenMask.set(1);
	whiteQueenMask.set(0);
	whiteQueenMask.flip();

	rightMask.set(63);
	rightMask.set(55);
	rightMask.set(47);
	rightMask.set(39);
	rightMask.set(31);
	rightMask.set(23);
	rightMask.set(15);
	rightMask.set(7);
	rightMask.flip();

	leftMask.set(56);
	leftMask.set(48);
	leftMask.set(40);
	leftMask.set(32);
	leftMask.set(24);
	leftMask.set(16);
	leftMask.set(8);
	leftMask.set(0);
	leftMask.flip();

	leftTopMask = leftMask & upMask;

	leftDownMask = leftMask & downMask;

	rightTopMask = rightMask & upMask;

	rightDownMask = rightMask & downMask;
}


void gameLogic::initializeValues(int firstBlack, int firstWhite, int secondBlack, int secondWhite)
{
	blackPieces.set(35);
	whitePieces.set(36);
	blackPieces.set(28);
	whitePieces.set(27);

/*	blackPieces.set(38);
	blackPieces.set(45);
	blackPieces.set(37);
	blackPieces.set(52);
	blackPieces.set(43);
	blackPieces.set(35);
	blackPieces.set(34);
	whitePieces.set(44);
	whitePieces.set(36);
	whitePieces.set(28);
	whitePieces.set(29);
	whitePieces.set(27);*/

	/*
	whitePieces.set(62);
	whitePieces.set(61);
	whitePieces.set(60);
	whitePieces.set(59);
	whitePieces.set(58);
	whitePieces.set(53);
	whitePieces.set(52);
	whitePieces.set(48);
	whitePieces.set(47);
	whitePieces.set(45);
	whitePieces.set(43);
	whitePieces.set(41);
	whitePieces.set(40);
	whitePieces.set(39);
	whitePieces.set(37);
	whitePieces.set(36);
	whitePieces.set(33);
	whitePieces.set(32);
	whitePieces.set(31);
	whitePieces.set(28);
	whitePieces.set(25);
	whitePieces.set(24);
	whitePieces.set(23);
	whitePieces.set(16);
	whitePieces.set(10);
	whitePieces.set(9);
	whitePieces.set(8);
	whitePieces.set(7);
	whitePieces.set(6);
	whitePieces.set(5);
	whitePieces.set(4);
	whitePieces.set(3);
	whitePieces.set(2);
	whitePieces.set(0);
	
	blackPieces.set(54);
	blackPieces.set(51);
	blackPieces.set(50);
	blackPieces.set(46);
	blackPieces.set(44);
	blackPieces.set(42);
	blackPieces.set(38);
	blackPieces.set(35);
	blackPieces.set(34);
	blackPieces.set(30);
	blackPieces.set(29);
	blackPieces.set(27);
	blackPieces.set(26);
	blackPieces.set(22);
	blackPieces.set(21);
	blackPieces.set(20);
	blackPieces.set(19);
	blackPieces.set(18);
	blackPieces.set(17);
	blackPieces.set(15);
	blackPieces.set(14);
	blackPieces.set(13);
	blackPieces.set(12);
	blackPieces.set(11);
*/



	downMask.set(63);
	downMask.set(62);
	downMask.set(61);
	downMask.set(60);
	downMask.set(59);
	downMask.set(58);
	downMask.set(57);
	downMask.set(56);
	downMask.flip();

	upMask.set(7);
	upMask.set(6);
	upMask.set(5);
	upMask.set(4);
	upMask.set(3);
	upMask.set(2);
	upMask.set(1);
	upMask.set(0);
	upMask.flip();

	rightMask.set(63);
	rightMask.set(55);
	rightMask.set(47);
	rightMask.set(39);
	rightMask.set(31);
	rightMask.set(23);
	rightMask.set(15);
	rightMask.set(7);
	rightMask.flip();

	leftMask.set(56);
	leftMask.set(48);
	leftMask.set(40);
	leftMask.set(32);
	leftMask.set(24);
	leftMask.set(16);
	leftMask.set(8);
	leftMask.set(0);
	leftMask.flip();

	leftTopMask = leftMask & upMask;

	leftDownMask = leftMask & downMask;

	rightTopMask = rightMask & upMask;

	rightDownMask = rightMask & downMask;
}


int gameLogic::convertIndex(int index)
{
	return (63 - index);
}


bitset<gameLogic::BIT_DEPTH> gameLogic::convertBitset(bitset<BIT_DEPTH> input)
{
	int inner = 63;
	bitset<BIT_DEPTH> output;

	for(int outer = 0; outer != BIT_DEPTH; ++outer)
	{
		output[inner] = input[outer];
		inner -= 1;
	}

	return output;
}


int gameLogic::retrieveIndex(bitset<BIT_DEPTH> input)
{
	for(int counter = 0; counter != BIT_DEPTH; ++counter)
	{
		if(input[counter] == 1)
			return counter;
	}
}