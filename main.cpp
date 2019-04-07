/*
   This is the console executable, that makes use of the BullCow class
   This acts as the view in a MVC patter, and is responsiblte for all
   user interaction. For game logic see the the GBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instaniatiate a new game

// entry point for the application
int main()
{
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);
    return 0; // Exit the application
}

// introduce the game
void PrintIntro()
{
    std::cout << "\n\nWelcome to the word game Bulls and Cows\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n\n";
    return;
}

// Main game loop
void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    // loop until a valid guess while the game is NOT won
    // and there are still tries remaining
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();

        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    PrintGameSummary();
    return;
}

// Get a guess from the player
FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do
    {
        int32 CurrentTry = BCGame.GetCurrentTry();

        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        std::getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lowercase letters\n\n";
            break;
        default:
            // assuming the guess is valid
            break;
        }
    } while (Status != EGuessStatus::OK);
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same word (y/n)? ";
    FText Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n";
    }
    else
    {
        std::cout << "Better luck next time!\n";
    }
}