
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <ctime>
#include <vector>

using namespace std;
//comment the f-ing code

int pontoiPaiktwn[100] = {};
int seiraPaikth1 = 0;

void wonLonelyMode(int difficulty)
{
	static int totalPoints;

	if (difficulty == -1)
		totalPoints--;
	else
	{
		cout << endl << endl << "Bravo! You found the word!" << endl << "Because you completed the ";
		switch (difficulty)
		{
			case 1: cout << "easy"; break; case 2: cout << "medium"; break; case 3: cout << "hard"; break; case 4: cout << "impossible";
		}

		cout << " level, you get ";
		if (difficulty == 4)
		{
			cout << "20 points and you win instantly";
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
		cout << endl << "THE GAME IS OVER AND YOU WON! CONGRATULATIONS!";
		system("pause > nul");
		exit(0);
	}
	else
	{
		cout << endl << "You have " << totalPoints;
		if (totalPoints == 1) cout << " point"; else cout << " points";
		cout << " out of 20" << endl;
	}
	cout << endl << endl << endl << endl;
}

void nikh2(bool nikh, int arithmosPaiktwn, int seiraPaikth, int pontoiLekshs, int pontoiMeFilous)
{


	if (nikh)
	{
		cout << "Bravo! Brhkate th leksh tou paikth " << seiraPaikth << "." << endl << "Pairnete " << pontoiLekshs << " pontous!" << endl;
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
		cout << "Den brhkate th leksh tou paikth " << seiraPaikth << "." << endl << "Xanete " << pontoiLekshs << " pontous!" << endl;
		for (int i = 0; i < arithmosPaiktwn; i++)
		{

			if (i == seiraPaikth - 1)
			{

			}
			else
			{
				pontoiPaiktwn[i] -= pontoiLekshs;

				if (pontoiPaiktwn[i] < 0)
				{
					pontoiPaiktwn[i] = 0;
				}
			}
		}
	}
}

void lonely(int tries, int difficulty)
{
	srand(time(0));
	string randomWord, currentWord;
	vector<char> wrongLetters, usedLetters;

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
		currentWord += '_';
	}
	cout << randomWord; //todo DELETE AFTER TESTING

	char firstLetterOfRandomWord = randomWord[0];
	randomWord[0] = '~';
	currentWord[0] = '~'; //the first character is known so in "current word" (variable in which i check if the user's letters are correct) i change it into something the user will not use. if i let it as it was and the user tried to use it, the program would think that he found a correct character.

	cout << "find the word by writing 1 character each time: " << endl;
	for (int i = 0; i < randomWord.length(); i++)
	{
		if (i == 0)
			cout << firstLetterOfRandomWord;
		else
			cout << currentWord[i];
	}
	cout << endl;

	while (tries != 0)
	{

		cout << "Choose letter: ";
		string input;
		cin >> input;
		char inputLetter = input[0];

		if (find(usedLetters.begin(), usedLetters.end(), inputLetter) != usedLetters.end())
		{
			cout << "You have tried this letter before, why don't you try something else?" << endl;
		}
		else if (find(randomWord.begin(), randomWord.end(), inputLetter) != randomWord.end())
		{
			cout << "Correct!" << endl;

			for (int i = 0; i < randomWord.length(); i++)
			{
				if (inputLetter == randomWord[i])
				{
					currentWord[i] = inputLetter;
				}
			}
		}
		else
		{
			cout << "Wrong!" << endl;
			wrongLetters.push_back(inputLetter);
			tries--;
		}

		usedLetters.push_back(inputLetter);

		system("timeout 2 > nul");

		cout << endl;
		for (int i = 0; i < randomWord.length(); i++)
		{
			if (i == 0)
				cout << firstLetterOfRandomWord;
			else
				cout << currentWord[i];
		}

		cout << endl << "Wrong Letters: ";

		for (int i = 0; i < wrongLetters.size(); i++)
		{
			cout << wrongLetters[i];

			if (i != wrongLetters.size() - 1)
				cout << ", ";
		}
		cout << endl;

		if (currentWord == randomWord)
		{
			wonLonelyMode(difficulty);
			return;
		}

		if (tries == 1)
			cout << "You have 1 try left" << endl;
		else if (tries == 0)
		{
			randomWord[0] = firstLetterOfRandomWord;
			cout << "You lost! The word was \"" << randomWord << "\"" << endl;
		}
		else
			cout << "You have " << tries << " tries left" << endl;
	}
	wonLonelyMode(-1);
}

void meFilo(int arithmosPaiktwn, int pontoiMeFilous, int pontoiSwsthsLekshs, int pontoiLathosLekshs, int prospatheies)
{
	cout << "players (p) and points (v): " << endl;
	int* paiktes = new int[arithmosPaiktwn + 1]
	{};
	int paiktesCounter = 0;
	for (int i = 0; i < arithmosPaiktwn; i++)
	{
		paiktesCounter += 1;
		paiktes[i] = paiktesCounter;
		cout << "p: " << paiktes[i];
		cout << " v: " << pontoiPaiktwn[i];
		if (arithmosPaiktwn - 1 > i)
		{
			cout << ", " << endl;
		}
	}

	for (int i = 0; i < arithmosPaiktwn; i++)
	{
		if (pontoiPaiktwn[i] >= pontoiMeFilous)
		{
			cout << endl << "Congratulations! Player " << i + 1 << " won";
			exit(0);
		}
	}

	seiraPaikth1 += 1;
	if (seiraPaikth1 > arithmosPaiktwn)
	{
		seiraPaikth1 = 1;
	}

	cout << endl << endl << "Now playing player " << seiraPaikth1 << ". Try a hard-to-find word";
	if (arithmosPaiktwn > 2)
	{
		cout << " so that your opponents cannot find it easily: ";
	}
	else if (arithmosPaiktwn == 2)
	{
		cout << " so that your opponent cannot find it easily: ";
	}
	string lekshXrhsth = "";
	char ch;

	ch = _getch();
	while (ch = _getch())
	{
		if (ch == 13)
		{
			break;
		}
		else if (ch == 8)
		{
			if (lekshXrhsth.length() > 0)
			{
				cout << "\b \b";
				lekshXrhsth.erase(lekshXrhsth.length() - 1);
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

	cout << "find the word, by typing 1 letters each time: " << endl;

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

		cout << "Choose letter: ";

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
		cout << "Wrong letters: ";
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
			delete[] paiktes;
			delete[] randomLekshChar;
			delete[] lathosGrammataXrhsth;
			delete[] lekshPouThaTypwthei;
			return;
		}

		if (prospatheies == 1)
		{

			cout << "You still have " << prospatheies << " try left" << endl;

		}
		else if (prospatheies == 0)
		{

			cout << "You lost! The word was \"" << randomLeksh << "\"" << endl;

		}
		else
		{
			if (arithmosPaiktwn == 2)
			{
				cout << "You still have " << prospatheies << " tries left" << endl;
			}
		}
	}
	delete[] paiktes;
	delete[] randomLekshChar;
	delete[] lathosGrammataXrhsth;
	delete[] lekshPouThaTypwthei;
	nikh2(false, arithmosPaiktwn, seiraPaikth1, pontoiLathosLekshs, pontoiMeFilous);
}

int main()
{
	cout << "                Hangman" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "\"I-don't-have-friends option\" (1)" << endl;
	cout << "play with friend(s) (2)" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		cout << "You need 20 points to win. " << endl << "You get 1 point by winning the easy level, 2 points by winning the medium level and 3 points by winning the hard level. By winning the impossible level, you get 20 points so you win instantly. By losing in any level, you lose 1 point." << endl;
		while (true)
		{
			cout << endl << "Choose difficulty level: (1) easy | (2) medium | (3) hard | (4) impossible" << endl;
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
					cout << "wrong choice";
					break;
			}
		}
	}
	else if (choice == 2)
	{
		cout << "How many players are playing? ";
		int arithmosPaiktwn;
		cin >> arithmosPaiktwn;

		if (arithmosPaiktwn < 2 || arithmosPaiktwn > 100)
		{
			cout << "please enter a valid number";
			exit(0);
		}

		cout << "How many points do you want the game to end at? ";
		int pontoiMeFilous;
		cin >> pontoiMeFilous;

		cout << "How many points do you want to get for every correct word? ";
		int pontoiSwsthsLekshs;
		cin >> pontoiSwsthsLekshs;

		cout << "How many points do you want to lose for every wrong word? ";
		int pontoiLathosLekshs;
		cin >> pontoiLathosLekshs;

		cout << "How many tries do you want each player to have? (usual is 6)";
		int prospatheies = 0;
		cin >> prospatheies;

		for (int i = 0; i < 100; i++)
		{
			pontoiPaiktwn[i] = 0;
		}

		cout << endl;
		while (true)
		{
			meFilo(arithmosPaiktwn, pontoiMeFilous, pontoiSwsthsLekshs, pontoiLathosLekshs, prospatheies);
		}
	}
	else
	{
		cout << "wrong choice!";
	}
}