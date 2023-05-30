
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <ctime>
#include <vector>

using namespace std;
//comment the f-ing code

void wonLonelyMode(int difficulty)
{
	static int totalPoints;

	if (difficulty == -1)
		totalPoints--;
	else
	{
		cout << endl << endl << "Bravo! You've discovered the word!" << endl << "Since you completed the ";
		switch (difficulty)
		{
			case 1: cout << "easy"; break; case 2: cout << "medium"; break; case 3: cout << "hard"; break; case 4: cout << "impossible";
		}

		cout << " level, you earn ";
		if (difficulty == 4)
		{
			cout << "20 points, instantly winning the game.";
			system("timeout 2 > nul");
			totalPoints += 20;
		}
		else
		{
			cout << difficulty << " points";
			totalPoints += difficulty;
		}
	}

	if (totalPoints < 0)
		totalPoints = 0;

	if (totalPoints >= 20)
	{
		cout << endl << "THE GAME IS OVER, AND YOU ARE VICTORIOUS! CONGRATULATIONS!";
		system("pause > nul");
		exit(0);
	}
	else
	{
		cout << endl << "You have accumulated " << totalPoints;
		if (totalPoints == 1) cout << " point"; else cout << " points";
		cout << " out of 20." << endl;
	}
	cout << endl << endl << endl << endl;
}

void lonely(int tries, int difficulty)
{
	srand(time(0));
	string word, wordProgress;
	vector<char> wrongLetters, usedLetters;

	int randomNumber = (rand() % 300);
	ifstream wordsFile;
	if (difficulty == 3 || difficulty == 4)
		wordsFile.open("difficult_words.doNotOpen");
	else
		wordsFile.open("words.doNotOpen");

	for (int i = 0; i <= randomNumber; i++)
	{
		getline(wordsFile, word);
	}

	//decrypting the word
	for (int i = 0; i < word.length(); i++)
	{
		word[i] -= 1;
		wordProgress += '_';
	}

	char firstLetter = word[0];
	word[0] = '~';
	wordProgress[0] = '~'; //the first character is known so in "current word" (variable in which i check if the user's letters are correct) i change it into something the user will not use. if i let it as it was and the user tried to use it, the program would think that he found a correct character.

	cout << "Word Progress: ";
	for (int i = 0; i < word.length(); i++)
	{
		if (i == 0)
			cout << firstLetter;
		else
			cout << wordProgress[i];
	}
	cout << endl;

	while (tries != 0)
	{

		cout << "Enter a letter: ";
		string input;
		cin >> input;
		char inputLetter = input[0];

		if (inputLetter > 122 || inputLetter < 97) //out of bounds (check ascii table)
		{
			cout << "This character is invalid. Please try something else." << endl;
		}
		else if (find(usedLetters.begin(), usedLetters.end(), inputLetter) != usedLetters.end())
		{
			cout << "You have already tried this letter. Why don't you attempt a different one?" << endl;
		}
		else if (find(word.begin(), word.end(), inputLetter) != word.end())
		{
			cout << "Correct!" << endl;
			usedLetters.push_back(inputLetter);

			for (int i = 0; i < word.length(); i++)
			{
				if (inputLetter == word[i])
					wordProgress[i] = inputLetter;
			}
		}
		else
		{
			cout << "Incorrect!" << endl;
			wrongLetters.push_back(inputLetter);
			usedLetters.push_back(inputLetter);
			tries--;
		}

		system("timeout 2 > nul");

		cout << endl;
		for (int i = 0; i < word.length(); i++)
		{
			if (i == 0)
				cout << firstLetter;
			else
				cout << wordProgress[i];
		}

		cout << endl << "Incorrect Letters: ";

		for (int i = 0; i < wrongLetters.size(); i++)
		{
			cout << wrongLetters[i];

			if (i != wrongLetters.size() - 1)
				cout << ", ";
		}
		cout << endl;

		if (wordProgress == word)
		{
			wonLonelyMode(difficulty);
			return;
		}

		if (tries == 1)
			cout << "You have 1 attempt remaining." << endl;
		else if (tries == 0)
		{
			word[0] = firstLetter;
			cout << "You lost! The word was \"" << word << "\"" << endl;
		}
		else
			cout << "You have " << tries << " attempts remaining" << endl;
	}
	wonLonelyMode(-1);
}

void multiplayer(int playerCount, float targetScore, float pointsPerLetter, float penaltyPoints, int tries1, vector<int>& players, vector<int>& WordChoosers)
{
	srand(time(0));

	string word, wordProgress;
	vector<char> wrongLetters, usedLetters;
	int tries = tries1;

	for (int i = 0; i < playerCount; i++)
	{
		if (players[i] >= targetScore)
		{
			cout << endl << "THE GAME IS OVER, AND YOU ARE VICTORIOUS! CONGRATULATIONS, PLAYER " << i + 1 << "!";
			system("pause > nul");
			exit(0);
		}
	}

	//if all players have set a word i reset the wordchoosers so they play again.
	if (WordChoosers.size() == players.size())
		WordChoosers.clear();

	int temp;
	do
	{
		temp = rand() % playerCount + 1;
	} while (find(WordChoosers.begin(), WordChoosers.end(), temp) != WordChoosers.end());

	WordChoosers.push_back(temp);

	cout << endl << endl << "Now it's player " << WordChoosers.back() << "'s turn. Choose a challenging word to make it harder for your ";
	if (playerCount > 2)
		cout << "opponents to guess: ";
	else if (playerCount == 2)
		cout << "opponent to guess: ";


	char tempCharacter;
	bool invalidCharacterTemp;
	do
	{
		invalidCharacterTemp = false;
		word = "";

		while (tempCharacter = _getch())
		{
			if (tempCharacter == 13) //ENTER
				break;
			else if (tempCharacter == 8) //BACKSPACE
			{
				if (word.length() > 0)
				{
					cout << "\b \b";
					word.erase(word.length() - 1);
				}
			}
			else
			{
				cout << "*";
				word += tempCharacter;
			}
		}
		if (word.length() < 3)
			cout << endl << "The word must have at least 3 characters.";
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] > 122 || word[i] < 97)
			{
				cout << endl << "word should not contain numbers, symbols, spaces, or uppercase letters.";
				invalidCharacterTemp = true;
			}
		}
	} while (word.length() < 3 || invalidCharacterTemp);
	cout << endl;

	char firstLetter = word[0];
	word[0] = '~';

	wordProgress[0] = '~';
	for (int i = 0; i < word.length(); i++)
	{
		wordProgress += '_';
	}

	cout << "Word progress: ";
	for (int i = 0; i < word.length(); i++)
	{
		if (i == 0)
			cout << firstLetter;
		else
			cout << wordProgress[i];
	}
	cout << endl;

	vector<int> playersPlayed;
	char inputLetter;
	string input;
	bool playingAgain = false;
	int tempNumber;
	while (true)
	{

		if (!playingAgain)
		{
			if (playersPlayed.size() == players.size() - 1) //players.size() - 1 because i don't count the word chooser as a player.
				playersPlayed.clear();
			do
			{

				tempNumber = rand() % playerCount + 1;
			} while ((find(playersPlayed.begin(), playersPlayed.end(), tempNumber) != playersPlayed.end()) || tempNumber == WordChoosers.back());

			playersPlayed.push_back(tempNumber);
		}

		do
		{
			cout << "Player " << playersPlayed.back() << " is now playing. Please enter a letter: ";
			cin >> input;
			inputLetter = input[0];

			if (inputLetter < 97 || inputLetter > 122) //out of bounds (check ascii table)
				cout << endl << "This character is invalid. Please try something else." << endl;

			else if (find(usedLetters.begin(), usedLetters.end(), inputLetter) != usedLetters.end())
				cout << endl << "This letter has been tried before. Why don't you attempt a different one?" << endl;

		} while (inputLetter < 97 || inputLetter > 122 || find(usedLetters.begin(), usedLetters.end(), inputLetter) != usedLetters.end());

		if (find(word.begin(), word.end(), inputLetter) != word.end())
		{
			cout << "Correct! You earn " << pointsPerLetter << " points!" << endl << endl;
			players[playersPlayed.back() - 1] += pointsPerLetter;
			usedLetters.push_back(inputLetter);
			playingAgain = true;
			for (int i = 0; i < word.length(); i++)
			{
				if (inputLetter == word[i])
					wordProgress[i] = inputLetter;
			}
		}
		else
		{
			if (players[playersPlayed.back() - 1] == 0)
				cout << "Incorrect!";
			else
			{
				if (penaltyPoints == 1)
					cout << "Incorrect! You lose 1 point." << endl << endl;
				else
					cout << "Incorrect! You lose " << penaltyPoints << " points." << endl << endl;

				players[playersPlayed.back() - 1] -= penaltyPoints;
			}
			playingAgain = false;
			wrongLetters.push_back(inputLetter);
			usedLetters.push_back(inputLetter);
			tries--;
		}

		system("timeout 2 > nul");

		cout << endl;
		for (int i = 0; i < word.length(); i++)
		{
			if (i == 0)
				cout << firstLetter;
			else
				cout << wordProgress[i];
		}

		cout << endl << "Incorrect Letters: ";

		for (int i = 0; i < wrongLetters.size(); i++)
		{
			cout << wrongLetters[i];

			if (i != wrongLetters.size() - 1)
				cout << ", ";
		}
		cout << endl;

		for (int i = 0; i < playerCount; i++)
		{
			cout << "Player " << i + 1 << ": " << players[i] << " points" << endl;
		}
		cout << endl;

		wordProgress[0] = word[0];
		if (wordProgress == word)
		{
			cout << "Congratulations! Player " << playersPlayed.back() << " has found the word!" << endl << "You earn " << pointsPerLetter << endl;
			players[playersPlayed.back() - 1] += pointsPerLetter;
			multiplayer(playerCount, targetScore, pointsPerLetter, penaltyPoints, tries, players, WordChoosers);
		}
		wordProgress[0] = '~';

		if (tries == 0)
		{
			word[0] = firstLetter;
			cout << "The guessing team is out of tries, so you lose! The word was \"" << word << "\"" << endl;
			cout << "player " << WordChoosers.back() << " Player 5 is the winner! Congratulations! You earn " << word.length() << " points!";
			players[WordChoosers.back() - 1] += word.length();
			multiplayer(playerCount, targetScore, pointsPerLetter, penaltyPoints, tries, players, WordChoosers);
		}
		else if (tries == 1)
			cout << "The guessing team has 1 attempt remaining." << endl << endl;
		else
			cout << "The guessing team has " << tries << " attempts remaining." << endl << endl;
	}
}
int main()
{
	while (true)
	{
		cout << "                Hangman" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "The objective of the game is to find the word by entering one letter at a time until a specific number of points is reached." << endl;
		cout << "\"Solo Play (I-don't-have-friends)\" (1)" << endl;
		cout << "Play with Friends (2)" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			cout << "You need 20 points to win. " << endl << "Winning the easy level grants you 1 point, the medium level awards 2 points, and the hard level grants 3 points. If you manage to conquer the impossible level, you instantly receive 20 points and win the game. Losing at any level deducts 1 point." << endl;
			while (true)
			{
				cout << endl << "Choose the difficulty level: (1) easy | (2) medium | (3) hard | (4) impossible" << endl;
				cin >> choice;
				switch (choice)
				{
					case 1:
						lonely(9, 1);
						break;
					case 2:
						lonely(6, 2);
						break;
					case 3:
						lonely(4, 3);
						break;
					case 4:
						lonely(2, 4);
						break;
					default:
						cout << endl << "Incorrect choice!" << endl;
						break;
				}
			}
		}
		else if (choice == 2)
		{
			cout << endl << "Each round, one player becomes the word chooser, while the others act as players. The aim is to uncover the word by making correct letter guesses. Points are awarded for each successful guess. The game concludes when a player accumulates the predetermined number of points. The word chooser earns points equal to the number of letters in their word if they win." << endl << endl;
			vector<int> players, wordChoosers;
			int playerCount, tries = 0;
			float penaltyPoints, pointsPerLetter, totalScore;
			string tempString;
			while (true)
			{
				do
				{
					cout << "How many players are playing?" << endl;
					cin >> playerCount;

					if (playerCount < 2 || playerCount > 10)
						cout << endl << "The number of players must be between 2 and 10 (inclusive)." << endl;

				} while (playerCount < 2 || playerCount > 10);

				do
				{
					do
					{
						cout << "How many points are awarded for each correct letter found? (Enter 'd' to use default)" << endl;
						cin >> tempString;

						if (tempString == "d")
						{
							pointsPerLetter = 2;
							cout << "using 2" << endl;
						}
						else
							pointsPerLetter = stof(tempString);

						if (pointsPerLetter <= 0)
							cout << endl << "Points awarded for correct guesses cannot be 0 or lower." << endl;

					} while (pointsPerLetter <= 0);

					do
					{
						cout << "How many points are deducted for each incorrect guess? (I suggest a value slightly lower than the points awarded for correct guesses. Enter 'd' to use default)" << endl;
						cin >> tempString;

						if (tempString == "d")
						{
							penaltyPoints = 1;
							cout << "using 1" << endl;
						}
						else
							penaltyPoints = stof(tempString);

						if (penaltyPoints <= 0)
							cout << endl << "points for incorrect guesses cannot be 0 or lower." << endl;

					} while (penaltyPoints <= 0);

					cout << "What's the target score to end the game? (Enter 'd' to use default)" << endl;
					cin >> tempString;

					if (tempString == "d")
					{
						totalScore = 20;
						cout << "using 20" << endl;
					}
					else
						totalScore = stof(tempString);

					if (totalScore < pointsPerLetter || totalScore < penaltyPoints)
						cout << endl << "The total score cannot be lower than the points awarded for each correct letter or the penalty points deducted for incorrect guesses." << endl;

				} while (totalScore < pointsPerLetter || totalScore < penaltyPoints);

				do
				{
					cout << "How many attempts do players have for each word? (Usually 6. Enter 'd' to use default)" << endl;
					cin >> tempString;

					if (tempString == "d")
					{
						tries = 6;
						cout << "using 6" << endl;
					}
					else
						tries = stoi(tempString);


					if (tries < 2)
						cout << endl << "attempts cannot be lower than 2" << endl;

				} while (tries < 2);

				for (int i = 0; i < playerCount; i++)
				{
					players.push_back(0);
					cout << "Player " << i + 1 << " has " << players[i] << " points" << endl;
				}

				cout << endl;
				multiplayer(playerCount, totalScore, pointsPerLetter, penaltyPoints, tries, players, wordChoosers);
			}

		}
		else
			cout << endl << "Incorrect choice!" << endl;
	}
}