#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
    Reset();
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";

    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries{{3, 5}, {4, 7}, {5, 10}, {6, 15}, {7, 20}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
    return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;

    // loop through all letters in the ghidden word
    int32 WordLength = MyHiddenWord.length();
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        // compare letters against the guess word
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            // if they match then
            if (Guess[GChar] == MyHiddenWord[MHWChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1)
    {
        return true;
    }

    // define a map
    TMap<char, bool> LetterSeen;

    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter])
        {
            return false;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }

    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}