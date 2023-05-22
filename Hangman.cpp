
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <ctime>
#include <vector>

using namespace std;
//comment the f-ing code

int pontoi = 0;
int pontoiPaiktwn[100] = {};
int seiraPaikth1 = 0;

void nikh1(int vathmoiDyskolias)
{
	if (vathmoiDyskolias != 0)
	{
		cout << endl << endl << "Bravo! You found the word!" << endl << "Because you completed the ";
		if (vathmoiDyskolias == 1)
		{
			cout << "easy level, you get 1 point";
			pontoi++;
		}
		else if (vathmoiDyskolias == 2)
		{
			cout << "medium level, you get 2 points";
			pontoi += 2;
		}
		else if (vathmoiDyskolias == 3)
		{
			cout << "hard level, you get 3 points";
			pontoi += 3;
		}
		else if (vathmoiDyskolias == 20)
		{
			cout << "impossible level, you get 20 points and you instantly...";
			system("timeout 2 > nul");
			pontoi += 20;
		}
	}
	else
	{
		pontoi--;
	}

	if (pontoi < 0)
	{
		pontoi = 0;
	}

	if (pontoi >= 20)
	{
		cout << endl << "THE GAME IS OVER AND YOU WON! CONGRATULATIONS!";
		exit(0);
	}
	else
	{
		cout << endl << "You have " << pontoi;
		if (pontoi == 1)
		{
			cout << " point";
		}
		else
		{
			cout << " points";
		}
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

void lonely1(int trials, int pointsForWin)
{
	srand(time(0));
	string randomWord, currentWord;
	vector<char> wrongLetters, usedLetters;

	int randomNumber = (rand() % 300);
	ifstream wordsFile("words.doNotOpen");
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

	while (trials != 0)
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
			trials--;
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
			nikh1(pointsForWin);
			return;
		}

		if (trials == 1)
			cout << "You have 1 try left" << endl;
		else if (trials == 0)
		{
			randomWord[0] = firstLetterOfRandomWord;
			cout << "You lost! The word was \"" << randomWord << "\"" << endl;
		}
		else
			cout << "You have " << trials << " tries left" << endl;
	}
	nikh1(0);
}

void lonely2(int arithmosProspatheiwn, int pontoiPouKerdise)
{
	srand(time(0));
	string randomLeksh;
	int prospatheies = arithmosProspatheiwn;
	ifstream periexomenoArxeiou("difficult_words.doNotOpen");
	int randomArithmos = (rand() % 253);
	int lathosGrammataCounter = 0;

	for (int i = 0; i <= randomArithmos; i++)
	{
		getline(periexomenoArxeiou, randomLeksh); //pairnw thn random leksh apo to arxeio me tis 253 lekseis
	}

	int textLength = randomLeksh.length(); //arithmos grammatwn ths random lekshs

	char* randomLekshChar = new char[textLength];
	char* randomLekshChar2 = new char[textLength];
	char lathosGrammataXrhsth[24]{};

	for (int i = 0; i < textLength; i++)
	{
		randomLeksh[i] -= 1; //apokryptografw th leksh
	}

	for (int i = 0; i < textLength; i++)
	{
		randomLekshChar[i] = randomLeksh[i]; //metatrepw th random leksh se char[]
		randomLekshChar2[i] = randomLeksh[i];
	}

	char* lekshPouThaTypwthei = new char[textLength];
	lekshPouThaTypwthei[0] = randomLekshChar[0];
	randomLekshChar[0] = '~'; //auto to kanw se periptwsh pou o xrhsths eisagei enan xarakthra o opoios einai idios me auton tou prwtou grammatos ths tyxaias lekshs tha bgazei oti to petyxe swsta. Opote, egw metatrepw ton prwto xarakthra se enan xarakthhra ton opoio den tha eisagei gia na mhn yparxei problhma

	cout << "Find the word by writing 1 character each time: " << endl;
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

		int swstaGrammataCounter = 0;
		for (int i = 0; i < textLength; i++)
		{
			if (randomLekshChar2[i] == lekshPouThaTypwthei[i])
			{
				swstaGrammataCounter++;
			}
		}

		if (swstaGrammataCounter == textLength)
		{
			nikh1(pontoiPouKerdise);
			delete[] randomLekshChar;
			delete[] lekshPouThaTypwthei;
			delete[] randomLekshChar2;
			return;
		}

		if (prospatheies == 1)
		{
			cout << "you still have " << prospatheies << " try left" << endl;
		}
		else if (prospatheies == 0)
		{
			cout << "You lost! The word was \"" << randomLeksh << "\"" << endl;
		}
		else
		{
			cout << "you still have " << prospatheies << " tries left" << endl;
		}
	}
	delete[] randomLekshChar;
	delete[] lekshPouThaTypwthei;
	delete[] randomLekshChar2;
	nikh1(0);
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
			if (choice == 1)
			{
				lonely1(9, 1);
			}
			else if (choice == 2)
			{
				lonely1(6, 2);
			}
			else if (choice == 3)
			{
				lonely2(4, 3);
			}
			else if (choice == 4)
			{
				lonely2(2, 20);
			}
			else
			{
				cout << "wrong choice";
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
