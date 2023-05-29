
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

void multiplayer(int playerCount, int targetScore, int pointsPerLetter, int penaltyPoints, int wordChooserRewardPoints, int tries1, vector<int>& players, vector<int>& WordChoosers)
{
	srand(time(0));

	string word, wordProgress;
	vector<char> wrongLetters, usedLetters;
	int tries = tries1;

	for (int i = 0; i < playerCount; i++)
	{
		if (players[i] >= targetScore)
		{
			cout << endl << "THE GAME IS OVER, AND YOU ARE VICTORIOUS! PLAYER " << players[i] << " CONGRATULATIONS!";
			system("pause > nul");
			exit(0);
		}
	}

	//if all players have set a word i reset the wordchoosers so they play again.
	if (WordChoosers.size() == players.size())
		WordChoosers.clear();

	int temp = playerCount - 1;
	do
	{
		WordChoosers.push_back(rand() % temp);
	} while (find(WordChoosers.begin(), WordChoosers.end(), temp) != WordChoosers.end());

	cout << endl << endl << "Now it's" << WordChoosers.back() << "'s turn. Choose a challenging word to make it harder for your ";
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
			cout << "word must have more than or equal to 3 characters.";
		for (int i = 0; i < word.length() - 1; i++)
		{
			if (word[i] > 122 || word[i] < 97)
			{
				cout << "word cannot contain numbers, symbols or uppercase letters.";
				invalidCharacterTemp = true;
			}
		}

	} while (word.length() < 3 || invalidCharacterTemp);
	cout << endl;


	char firstLetter = word[0];
	word[0] = '~';
	wordProgress[0] = '~';

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
		if (playersPlayed.size() == players.size())
			playersPlayed.clear();

		if (!playingAgain)
		{
			do
			{
				tempNumber = rand() % playerCount + 1;
			} while (find(playersPlayed.begin(), playersPlayed.end(), tempNumber) != playersPlayed.end());

			playersPlayed.push_back(tempNumber);
		}

		do
		{
			cout << "Player " << playersPlayed.back() << "is now playing: Please enter a letter : ";
			cin >> input;
			inputLetter = input[0];

			if (inputLetter > 122 || inputLetter < 97) //out of bounds (check ascii table)
				cout << "This character is invalid. Please try something else." << endl;

			else if (find(usedLetters.begin(), usedLetters.end(), inputLetter) != usedLetters.end())
				cout << "This letter has been  tried before. Why don't you attempt a different one?" << endl;

		} while (inputLetter <= 122 || inputLetter >= 97 || find(usedLetters.begin(), usedLetters.end(), inputLetter) == usedLetters.end());

		if (find(word.begin(), word.end(), inputLetter) != word.end())
		{
			cout << "Correct! You get +" << pointsPerLetter << "points!" << endl;
			players[playersPlayed.back()] += pointsPerLetter;
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
			cout << "Incorrect! You lose" << penaltyPoints << "points." << endl;
			players[playersPlayed.back()] -= penaltyPoints;
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
			cout << "Player " << i + 1 << " has " << players[i] << " points" << endl;
		}
		//todo CONTINUE FROM HERE
		if (wordProgress == word)
		{
			cout << "Congratulations! Player " << playersPlayed.back() << " found the word!" << endl << "You get +" << pointsPerLetter;
			players[playersPlayed.back()] += pointsPerLetter;
			multiplayer(playerCount, targetScore, pointsPerLetter, penaltyPoints, tries, wordChooserRewardPoints, players, WordChoosers);
		}

		if (tries == 0)
		{
			word[0] = firstLetter;
			cout << "You are out of tries so, you lost! The word was \"" << word << "\"" << endl;
			cout << " player " << WordChoosers.back() << "wins! Congratulations! You get +" << wordChooserRewardPoints << "points!";
			players[WordChoosers.back()] += wordChooserRewardPoints;
			multiplayer(playerCount, targetScore, pointsPerLetter, penaltyPoints, tries, wordChooserRewardPoints, players, WordChoosers);
		}
		else if (tries == 1)
			cout << "You have 1 attempt remaining." << endl;
		else
			cout << "You have " << tries << " attempts remaining" << endl;
	}
}
int main()
{
//todo vale na exei default options gia multiplayer (otan patane "d")
	while (true)
	{
		cout << "                Hangman" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "The objective is to discover the word by entering one letter at a time. Each correct guess earns you points. The game concludes when a player accumulates a specific number of points." << endl;
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
						cout << "Incorrect choice!" << endl;
						break;
				}
			}
		}
		else if (choice == 2)
		{
			vector<int> players, wordChoosers;
			int playerCount, tries = 0;
			float penaltyPoints, pointsPerLetter, totalScore, wordChooserRewardPoints;
			string tempString;
			while (true)
			{
				do
				{
					cout << "How many players are playing?" << endl;
					cin >> playerCount;

					if (playerCount < 2 || playerCount > 10)
						cout << "Players must be more than or equal to 2 and less than or equal to 10" << endl;

				} while (playerCount < 2 || playerCount > 10);

				do
				{
					do
					{
						cout << "How many points are awarded for each correct letter found? (Enter 'd' to use default)" << endl;
						cin >> tempString;

						if (tempString == "d")
							pointsPerLetter = 2;
						else
							pointsPerLetter = stof(tempString);

						if (pointsPerLetter <= 0)
							cout << "points for correct guesses cannot be 0 or lower." << endl;

					} while (pointsPerLetter <= 0);

					do
					{
						cout << "How many points are deducted for each incorrect guess? (I suggest a value slightly lower than the points awarded for correct guesses. Enter 'd' to use default)" << endl;
						cin >> tempString;

						if (tempString == "d")
							penaltyPoints = 1;
						else
							penaltyPoints = stof(tempString);

						if (penaltyPoints <= 0)
							cout << "points for incorrect guesses cannot be 0 or lower." << endl;

					} while (penaltyPoints <= 0);

					cout << "What's the target score to end the game? (Enter 'd' to use default)" << endl;
					cin >> tempString;

					if (tempString == "d")
						totalScore = 20;
					else
						totalScore = stof(tempString);

					if (totalScore < pointsPerLetter || totalScore < penaltyPoints)
						cout << "The total score points cannot be lower than the points awarded for each correct letter or the penalty points deducted for incorrect guesses." << endl;

				} while (totalScore < pointsPerLetter || totalScore < penaltyPoints);

				do
				{
					cout << "How many points should be assigned to a word chooser who wins? (Enter 'd' to use default)" << endl;
					cin >> tempString;

					if (tempString == "d")
						wordChooserRewardPoints = 4;
					else
						wordChooserRewardPoints = stof(tempString);

					if (wordChooserRewardPoints <= 0)
						cout << "word chooser reward points should not be 0 or lower." << endl;
				} while (wordChooserRewardPoints <= 0);

				do
				{
					cout << "How many attempts do players have for each word? (Usually 6. Enter 'd' to use default)" << endl;
					cin >> tempString;

					if (tempString == "d")
						tries = 6;
					else
						tries = stoi(tempString);


					if (tries < 2)
						cout << "attempts should not be lower than 2" << endl;

				} while (tries < 2);

				for (int i = 0; i < playerCount; i++)
				{
					players.push_back(0);
					cout << "Player " << i + 1 << " has " << players[i] << " points" << endl;
				}

				cout << endl;
				multiplayer(playerCount, totalScore, pointsPerLetter, penaltyPoints, tries, wordChooserRewardPoints, players, wordChoosers);
			}

		}
		else
			cout << "Incorrect choice!" << endl;
	}
}