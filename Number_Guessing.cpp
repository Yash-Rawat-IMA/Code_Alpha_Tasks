#include <iostream>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()
#include <limits>    // For numeric_limits

using namespace std;

// Function to play the game
void numberGuessingGame(int maxNumber, int maxAttempts) {
    srand(static_cast<unsigned int>(time(0)));
    int targetNumber = rand() % maxNumber + 1;
    int guess = 0, attempts = 0, score = 100;

    cout << "I have chosen a number between 1 and " << maxNumber << "." << endl;
    cout << "You have " << maxAttempts << " attempts to guess it. Let's go!" << endl;

    while (attempts < maxAttempts) {
        cout << "Enter your guess: ";
        cin >> guess;

        // Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        attempts++;

        if (guess < targetNumber) {
            cout << "Too low! Try again." << endl;
        } else if (guess > targetNumber) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << "Congratulations! You've guessed the number " << targetNumber << " correctly in " << attempts << " attempts." << endl;
            score += (maxAttempts - attempts) * 10;  // Reward based on remaining attempts
            cout << "Your score: " << score << endl;
            return;
        }
    }

    // If the player runs out of attempts
    cout << "Sorry, you've run out of attempts. The correct number was " << targetNumber << "." << endl;
    cout << "Your score: " << score << endl;
}

int main() {
    int choice, maxNumber, maxAttempts;

    cout << "Welcome to the Enhanced Number Guessing Game!" << endl;
    cout << "Choose a difficulty level:" << endl;
    cout << "1. Easy (1-50, 10 attempts)" << endl;
    cout << "2. Medium (1-100, 7 attempts)" << endl;
    cout << "3. Hard (1-200, 5 attempts)" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            maxNumber = 50;
            maxAttempts = 10;
            break;
        case 2:
            maxNumber = 100;
            maxAttempts = 7;
            break;
        case 3:
            maxNumber = 200;
            maxAttempts = 5;
            break;
        default:
            cout << "Invalid choice. Setting to Easy mode." << endl;
            maxNumber = 50;
            maxAttempts = 10;
            break;
    }

    char playAgain;
    do {
        numberGuessingGame(maxNumber, maxAttempts);
        cout << "Would you like to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing! Goodbye!" << endl;
    return 0;
}