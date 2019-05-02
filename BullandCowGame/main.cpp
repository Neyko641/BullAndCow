/* This is the Console that makes use of BullCow Class
This is for interaction, Logic in FBullCowGame.
FText instead of std::string use of UE4 Terminology!

*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
//UE friendly syntax
using int32 = int;
using FText = std::string;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame; // function prototypes as outside a class
void PrintGameSummary();



// entry point for the application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());
	return 0; //exit the application

}





void PrintIntro()
{
	
	
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;
	return;
}
//plays a single session until completion
void PlayGame()
{

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//loop for the Number of turns asking for guesses while the game is won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		// repeat the guess back to them		
		FText Guess = GetValidGuess(); 
		//submit valid guess and recieve a count
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << " Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
		
		}
	}




//loop till user gives valid guess
FText GetValidGuess()
{
	FText Guess;
	EGuessStatus Status = EGuessStatus::Invalid_Status;
		do {
			int32 CurrentTry = BCGame.GetCurrentTry();
			
			std::cout << " Try " << CurrentTry << " of " << BCGame.GetMaxTries();
			std::cout<< ". Enter your Guess: ";
			// get a guess from the player
			std::getline(std::cin, Guess);

			EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
			switch (Status)
			{
			case EGuessStatus::OK:
				
				return Guess;
			case EGuessStatus::Not_isogram:
				std::cout << "This is not an isogram!\n\n";
				break;
			case EGuessStatus::Invalid_Symbol:
				std::cout << "The word contains invalid symbols!\n\n";
				break;
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter Lowercase Words!\n\n";
				break;
			default:
				break; //assume it's true


			}
			
		}while (Status != EGuessStatus::OK); //keep looping until we get no errors.
		return Guess;
} 


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) " << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		return true;
	}
	else
		if (Response[0] == 'n' || Response[0] == 'N')
		{

			return false;
		}
		else std::cout << "Invalid  response!" << std::endl;
         return AskToPlayAgain();
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations, You Win!" << std::endl;

	}
	else
		std::cout << " Too Bad, better luck next time." << std::endl;
}
