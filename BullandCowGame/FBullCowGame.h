/*
For UE Terminology!
header file has the starting variables and parameters.
*/
#pragma once
#include <string>

using int32 = int;
using FString = std::string;

//initialization is 0
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID_STATUS,
	OK,
	INVALID_SYMBOL,
	WRONG_LEN,
	NOT_ISOGRAM,
	NOT_LOWERCASE
};

class FBullCowGame {
public: 
	
	FBullCowGame(); //Constructor
	int32 GetMaxTries() const;
	bool IsGameWon() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	void Reset(); 
	
	//Provide a method for counting Bulls and Cows, and incrementing term number!
	FBullCowCount SubmitValidGuess(FString);
private:
	
	//See Constructor for initialization.
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsValidSymbol(FString) const;
};
