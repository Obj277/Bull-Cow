#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game

// the entry point for application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}

void PrintIntro()
{
	// introduce the game
	std::cout << "==========================================================================================" << std::endl;
	std::cout << "   _______  __   __  ___      ___      _______   &   _______  _______  _     _  _______ " << std::endl;
	std::cout << "  |  _    ||  | |  ||   |    |   |    |       |     |       ||       || | _ | ||       |" << std::endl;
	std::cout << "  | |_|   ||  | |  ||   |    |   |    |  _____|     |       ||   _   || || || ||  _____|" << std::endl;
	std::cout << "  |       ||  |_|  ||   |    |   |    | |_____      |       ||  | |  ||       || |_____ " << std::endl;
	std::cout << "  |  _   | |       ||   |___ |   |___ |_____  |     |      _||  |_|  ||       ||_____  |" << std::endl;
	std::cout << "  | |_|   ||       ||       ||       | _____| |     |     |_ |       ||   _   | _____| |" << std::endl;
	std::cout << "  |_______||_______||_______||_______||_______|     |_______||_______||__| |__||_______|\n" << std::endl;
	std::cout << "==========================================================================================" << std::endl;
	std::cout << "\n\nWelcome to Bulls and Cows word game\n";	
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done - YOU WIN!\n";
	}
	else
	{
		std::cout << "Booooooooooooooooooooo!\n";
	}
}