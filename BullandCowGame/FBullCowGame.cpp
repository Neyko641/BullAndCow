/*The logic of the Game goes here, win conditions, tries, and such.
The game is a simple guess the word game, based on Mastermind.*/


#include "FBullCowGame.h"
#include <map>
#define TMap std::map //make the syntax UE friendly.
#pragma once

using FString = std::string;
using int32 = int;
int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
FBullCowGame::FBullCowGame() {Reset();} //Default Constructor
int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,4}, {5,4}, {6,4}, {7,5}, {8,5}, {9,6}, {10,7} };
	return WordLengthToMaxTries[MyHiddenWord.length()];

}


void FBullCowGame::Reset() //Add more words to the table
{
	
	
	
	
	const FString HIDDEN_WORD = "snake"; //this must be an isogram
	MyHiddenWord = HIDDEN_WORD;

	

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == false)
		{
			LetterSeen[Letter] = true;
		}
		else
		{ 
			return false;
		}
	}
	
	
	
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}


	return true;
}

bool FBullCowGame::IsValidSymbol(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!isalpha(Letter))
		{
			return false;
		}
	}
	return true;
}






EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_isogram;
	}
	else if (!IsValidSymbol(Guess))
	{
		return EGuessStatus::Invalid_Symbol;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}
//Recieves a valid guess, increments turn, and returns count 



FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

	int32 GuessLength = Guess.length();
	int32 WordLength = MyHiddenWord.length();
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	for (int32 GuessChar = 0; GuessChar < GuessLength; GuessChar++) {
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
			if (Guess[GuessChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GuessChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else { bGameIsWon = false; }

	return BullCowCount;
}


