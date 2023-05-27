
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
	string randomWord, wordProgress;
	vector<char> wrongLetters, usedLetters;
	vector<char> invalidCharacters{ '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '_', '=', '+', '[', ']', '{', '}', ';', ':', '\'', '\"', '`', '~', ',', '<', '.', '>', '/', '?', '\\', '|', ' ' };

	int randomNumber = (rand() % 300);
	ifstream wordsFile;
	if (difficulty == 3 || difficulty == 4)
		wordsFile.open("difficult_words.doNotOpen");
	else
		wordsFile.open("words.doNotOpen");

	for (int i = 0; i <= randomNumber; i++)
	{
		getline(wordsFile, randomWord);
	}

	//decrypting the word
	for (int i = 0; i < randomWord.length(); i++)
	{
		randomWord[i] -= 1;
		wordProgress += '_';
	}

	char firstLetterOfRandomWord = randomWord[0];
	randomWord[0] = '~';
	wordProgress[0] = '~'; //the first character is known so in "current word" (variable in which i check if the user's letters are correct) i change it into something the user will not use. if i let it as it was and the user tried to use it, the program would think that he found a correct character.

	cout << "Word Progress: ";
	for (int i = 0; i < randomWord.length(); i++)
	{
		if (i == 0)
			cout << firstLetterOfRandomWord;
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

		if (find(invalidCharacters.begin(), invalidCharacters.end(), inputLetter) != invalidCharacters.end())
		{
			cout << "This character is invalid. Please try something else." << endl;
		}
		else if (find(usedLetters.begin(), usedLetters.end(), inputLetter) != usedLetters.end())
		{
			cout << "You have already tried this letter. Why don't you attempt a different one?" << endl;
		}
		else if (find(randomWord.begin(), randomWord.end(), inputLetter) != randomWord.end())
		{
			cout << "Correct!" << endl;
			usedLetters.push_back(inputLetter);

			for (int i = 0; i < randomWord.length(); i++)
			{
				if (inputLetter == randomWord[i])
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
		for (int i = 0; i < randomWord.length(); i++)
		{
			if (i == 0)
				cout << firstLetterOfRandomWord;
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

		if (wordProgress == randomWord)
		{
			wonLonelyMode(difficulty);
			return;
		}

		if (tries == 1)
			cout << "You have 1 attempt remaining." << endl;
		else if (tries == 0)
		{
			randomWord[0] = firstLetterOfRandomWord;
			cout << "You lost! The word was \"" << randomWord << "\"" << endl;
		}
		else
			cout << "You have " << tries << " attempts remaining" << endl;
	}
	wonLonelyMode(-1);
}

void nikh2(bool nikh, int arithmosPaiktwn, int seiraPaikth, int pontoiLekshs, int pontoiMeFilous)
{


	if (nikh)
	{
		cout << "Bravo! You found player" << seiraPaikth << "'s word!" << endl << "You each get" << pontoiLekshs << " points!" << endl;
		for (int i = 0; i < arithmosPaiktwn; i++)
		{

			if (i == seiraPaikth - 1)
			{

			}
			else
			{
				pontoiPaiktwn[i] += pontoiLekshs;
			}
		}

	}
	else
	{
		cout << "Unfortunately, you couldn't find Player " << seiraPaikth << "3's word :( As a result, " << endl << "you lose " << pontoiLekshs;
		if (pontoiLekshs == 1)
			cout << " point." << endl;
		else
			cout << " points." << endl;

		for (int i = 0; i < arithmosPaiktwn; i++)
		{

			if (i == seiraPaikth - 1)
			{

			}
			else
			{
				pontoiPaiktwn[i] -= pontoiLekshs;

				if (pontoiPaiktwn[i] < 0)
					pontoiPaiktwn[i] = 0;
			}
		}
	}
}

void meFilo(int playerCount, int targetScore, int pointsPerLetter, int penaltyPoints, int tries, vector<int>& players, vector<int>& WordChoosers)
{
	srand(time(0));
	//todo vale na mhn mporoyn na valoun perierges times ws leksh
	//todo otan kapoios vriskei gramma paizei ksana kai mono aftos pou vrei to teleftaio gramma pairnei ponto parolo pou synolika exoun sygkekrimeno arithmo prospatheiwn (einai dikaio epeidh o kathenas mporei na xasei mono mia fora ana gyro)
	//todo h seira tou paikth apofasizetai tyxaia kathe fora (aftoi pou epaiksan afto to round tha apothikevontai sto playersPlayed (to eftiaksa twra). mhn ksexaseis na to adeiaseis otan vrethei h leksh)
	//todo vale orio na mhn mporoun na valoun ligotero apo 2 grammata ana leksh
	//todo kane na mhn mporoun na valoun perierges times (katw apo 1, synolikoi pointoi na mhn einai ligorteroi apo toys pontous pou kerdizoun gia kathe leksh)
	//todo aftos pou vazei leksh xanei pontous an thn vroun


	for (int i = 0; i < playerCount; i++)
	{
		players.push_back(0);
		cout << "Player " << i + 1;
		cout << " has " << players[i] << " points";
		if (playerCount - 1 > i)
			cout << ", " << endl;
	}

	for (int i = 0; i < playerCount; i++)
	{
		if (players[i] >= targetScore)
		{
			cout << endl << "Congratulations! Player " << i + 1 << " won";
			break;
		}
	}

	WordChoosers.push_back(rand() % playerCount + 1);

	cout << endl << endl << "Now it's" << WordChoosers.back() << "'s turn. Choose a challenging word to make it harder for your ";
	if (playerCount > 2)
		cout << "opponents to guess: ";
	else if (playerCount == 2)
		cout << "opponent to guess: ";

	string word = "";
	char ch;

	ch = _getch();
	while (ch == _getch())
	{
		if (ch == 13) //ENTER
		{
			break;
		}
		else if (ch == 8) //BACKSPACE
		{
			if (word.length() > 0)
			{
				cout << "\b \b";
			}
		}
		else
		{
			cout << "*";
			lekshXrhsth += ch;
		}
	}
	cout << endl;

	int textLength = lekshXrhsth.length();
	char* randomLekshChar = new char[textLength];
	string randomLeksh = lekshXrhsth;
	int lathosGrammataCounter = 0;
	char* lathosGrammataXrhsth = new char[prospatheies + 1];

	for (int i = 0; i < textLength; i++)
	{
		randomLekshChar[i] = randomLeksh[i]; //metatrepw th random leksh se char[]
	}

	char* lekshPouThaTypwthei = new char[textLength];
	lekshPouThaTypwthei[0] = randomLekshChar[0];
	randomLekshChar[0] = '~';

	cout << "Word progress: ";

	for (int i = 1; i < textLength; i++)
	{
		lekshPouThaTypwthei[i] = '_';
	}

	for (int i = 0; i < textLength; i++)
	{
		cout << lekshPouThaTypwthei[i];
	}
	cout << endl;

	while (prospatheies != 0)
	{

		cout << "Enter a letter: ";

		string keimenoXrhsth;
		cin >> keimenoXrhsth;
		char grammaXrhsth = keimenoXrhsth[0];

		bool grammaCheck = false;
		for (int i = 0; i < textLength; i++)
		{
			if (grammaXrhsth == randomLekshChar[i])
			{
				lekshPouThaTypwthei[i] = grammaXrhsth;
				grammaCheck = true;
			}
		}
		bool checkDoubleWrongInput = false;
		for (int i = 0; i < lathosGrammataCounter; i++)
		{
			if (grammaXrhsth == lathosGrammataXrhsth[i])
			{
				checkDoubleWrongInput = true;
			}
		}

		if (grammaCheck)
		{
			cout << "Correct!" << endl;
		}
		else if (checkDoubleWrongInput == true)
		{

			cout << "You have tried this letter before and it was wrong, why not try something else?" << endl;

		}
		else
		{
			cout << "Wrong!" << endl;
			lathosGrammataXrhsth[lathosGrammataCounter] = grammaXrhsth;
			lathosGrammataCounter++;
			prospatheies--;
		}
		system("timeout 2 > nul");

		cout << endl;
		for (int i = 0; i < textLength; i++)
		{
			cout << lekshPouThaTypwthei[i];
		}
		cout << endl;
		cout << "Incorrect letters: ";
		for (int i = 0; i < lathosGrammataCounter; i++)
		{
			cout << lathosGrammataXrhsth[i];
			if (lathosGrammataCounter - 2 >= i)
			{
				cout << ", ";
			}
		}
		cout << endl;

		bool isothta = (randomLeksh == lekshPouThaTypwthei);

		if (isothta == true)
		{
			nikh2(true, arithmosPaiktwn, seiraPaikth1, pontoiSwsthsLekshs, pontoiMeFilous);
			delete[] randomLekshChar;
			delete[] lathosGrammataXrhsth;
			delete[] lekshPouThaTypwthei;
			return;
		}

		if (prospatheies == 1)
			cout << "You have " << prospatheies << " attempt remaining" << endl;
		else if (prospatheies == 0)
			cout << "You lost! The word was \"" << randomLeksh << "\"" << endl;
		else if (arithmosPaiktwn == 2)
			cout << "You have " << prospatheies << " attempts remaining" << endl;
	}
	delete[] randomLekshChar;
	delete[] lathosGrammataXrhsth;
	delete[] lekshPouThaTypwthei;
	nikh2(false, arithmosPaiktwn, seiraPaikth1, pontoiLathosLekshs, pontoiMeFilous);
}

int main()
{
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
						cout << "Incorrect choice!";
						break;
				}
			}
		}
		else if (choice == 2)
		{//handle space bar input
			vector<int> players;
			int playerCount, pointsPerLetter, totalScore, tries = 0;
			float penaltyPoints;
			while (true)
			{
				do
				{
					cout << "How many players are playing? ";
					cin >> playerCount;

					if (playerCount < 2 || playerCount > 10)
						cout << "Players must be more than or equal to 2 and less than or equal to 10";

				} while (playerCount < 2 || playerCount > 10);

				do
				{
					do
					{
						cout << "How many points are awarded for each correct letter found?";
						cin >> pointsPerLetter;

						if (pointsPerLetter <= 0)
							cout << "points for correct guesses cannot be 0 or lower than 0.";

					} while (pointsPerLetter <= 0);

					do
					{
						cout << "How many points are deducted for each incorrect guess? ";
						cin >> penaltyPoints;

						if (penaltyPoints <= 0)
							cout << "points for incorrect guesses cannot be 0 or lower than 0.";

					} while (penaltyPoints <= 0);

					cout << "What's the target score to end the game? ";
					cin >> totalScore;

					if (totalScore < pointsPerLetter || totalScore < penaltyPoints)
						cout << "total score points cannot be lower than the points awarded for each letter.";

				} while (totalScore < pointsPerLetter || totalScore < penaltyPoints);

				do
				{
					cout << "How many attempts do players have for each word? (Usually 6)";
					cin >> tries;
					if (tries < 2)
						cout << "attempts cannot be lower than 2";
				} while (tries < 2);

				for (int i = 0; i < playerCount; i++)
				{
					players.push_back(0);
				}

				cout << endl;
				while (true)
				{
					meFilo(playerCount, totalScore, pointsPerLetter, penaltyPoints, tries, players);
				}

			}


		}
		else
			cout << "Incorrect choice!";
	}
}