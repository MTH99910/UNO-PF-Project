#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>

using namespace std;

//GameSystem Functions
void StartGame();

//Deck, DiscardPile and Hand Manipulation Functions
void initializeDeck(int deck[4][15]);
void shuffleDeck(int deck[4][15]);
int numOfCards(int player[106]);
void UpdateDiscardPile(int playedCard, int discardPile[108]);
void dealCards(int drawAmm, int player[106], int deck[4][15], int deckIndex[2]);
void RemovePlayerCard(int playerDeck[106], int index);
void RecycleDeck(int discardPile[108], int deck[4][15]);

//Printing and Helping Printing Functions
void printBoard(int pl1Deck[106],int pl2Deck[106],int discardPile[108], int playerTurn);
void setColor(int bgColor, int textColor=0);
void print(int deck[4][15]);
void print(int player[106]);
void printDiscard(int discardPile[108]);
void clearScreen();

//Player Turn Functions
void playTurn(int discardPile[108], int pl1Deck[106], int pl2Deck[106], int deck[4][15], int deckIndex[2],int &playerTurn, bool &unoPl1, bool &unoPl2, char &exitChar);
bool isValidPlay(int &playerCard, int topCard, char &exitChar);
void handleSpecialCard(int specialCardType);
void ValidateFirstCard(int deck[4][15]);
void SwitchPlayerTurn(int &playerTurn);
void WildCardSetColor(int &wildCard, char &exitChar);
bool callUno(bool &unoPl1, bool &unoPl2);
 
//Nessecary Global Varaibles
int playerTurn = 1, deck[4][15]={0}, pl1Deck[106]={0}, pl2Deck[106]={0}, deckIndex[2]={0};
 
int main()
{
//	char choice = '0';
//	menuInput:
//	cout << "========== Welcome to UNO ==========="<< endl;
//	cout << "1. Play" << endl;
//	cout << "2. Load Score" << endl;
//	cout << "3. Exit" << endl;
//	cout << "Choice: ";
//	cin >> choice;
//	switch(choice)
//	{
//		case '1':
//			{
//				StartGame();
//				break;
//			}
//		case '2':
//			{
//				return 0;
//				break;
//			}
//		case '3':
//			{
//				return 0;
//				break;
//			}
//		case 'E':
//			{
//				return 0;
//				break;
//			}
//		default:
//			{
//				cout << "Invalid Input! Please Choose One Of The Menu Options" << endl;
//				goto menuInput;
//			}
//	}
	
	int discardPile[108]={0, 0, };
	initializeDeck(deck);
	char c = '0';
	do
	{
		print(deck);
		print(discardPile);
		dealCards(1, discardPile, deck, deckIndex);
		cin >> c;
	}while(c != 'A');

	RecycleDeck(discardPile, deck);
	print(deck);
	return 0;
}

void StartGame()
{
	int discardPile[108]={0};
	bool unoPl1 = false, unoPl2 = false;
	char exitChar = 'N';
	
	clearScreen();
	initializeDeck(deck);
	shuffleDeck(deck);
	ValidateFirstCard(deck);
	dealCards(1, discardPile, deck, deckIndex);
	dealCards(7, pl1Deck, deck, deckIndex);
	dealCards(7, pl2Deck, deck, deckIndex);
	do
	{
		printBoard(pl1Deck, pl2Deck, discardPile, playerTurn);
		playTurn(discardPile, pl1Deck, pl2Deck, deck, deckIndex, playerTurn, unoPl1, unoPl2, exitChar);
		if(exitChar == 'Y')
		{
			return;
		}
		SwitchPlayerTurn(playerTurn);
		clearScreen();
	}while(numOfCards(pl1Deck) != 0 || numOfCards(pl2Deck) != 0);
}

void initializeDeck(int deck[4][15])
{
	for(int i=0 ; i<4 ; i++)
	{
		for(int j=0 ; j<15 ; j++)
		{
			if(i!=2)
				deck[i][j]=(i+1)*1000;
			else
				deck[i][j]=6000;
			deck[i][j]+=j*10;
			if(j>0&&j<13)
				deck[i][j]+=2;
			else
				deck[i][j]+=1;	
		}
	}
}

void printBoard(int pl1Deck[106],int  pl2Deck[106],int  discardPile[108], int playerTurn)
{
	int numOfCardsPl1=numOfCards(pl1Deck), numOfCardsPl2=numOfCards(pl2Deck), l=0;
	for(int i=(numOfCardsPl1/15)+(numOfCardsPl1%15==0?0:1) ; i>=1 ; i-- )
	{
		int k;
		for(int j=1 ; j<=8 ; j++)
		{
			for( k=0 ; k<(i>1?15:numOfCardsPl1-l) ; k++)
			{
				cout<<"  ";
				int cardType=(pl1Deck[l+k]/10)%100;
				if(playerTurn==1)
				{
					if(cardType==13||cardType==14)
					{
						setColor(7);
					}
					else
					{
						setColor( pl1Deck[l+k]/1000 );
					}
				}
				switch (j)
				{
					case 1:
						cout <<char(201)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(187);
						break;
					case 2:
					case 3:
					case 5:
					case 6:
						cout <<char(186)<< "       " <<char(186);
						break;
					case 4:
						cout <<char(186);
						if(playerTurn!=1)
						{
							cout<<"  UNO  ";
						}
						else
						{
							if(cardType<=9)
							{
								cout<<"   "<<cardType<<"   ";
							}
							else
							{
								switch (cardType)
								{
									case 10:
										cout<<"   S   ";
										break;
									case 11:
										cout<<"   R   ";
										break;
									case 12:
										cout<<"  D 2  ";
										break;
									case 13:
										cout<<" WILD! ";
										break;
									case 14:
										cout<<"WILD"<<char(176)<<"D4";
										break;
								}
							}
						}
						cout <<char(186);
						break;
					case 7:
						cout <<char(200)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(188);
						break;
					case 8:
						setColor(0, 7);
						cout<<"    "<<l+k+1<<"    ";
						if(l+k>=9)
						{
							cout<<"\b";
							if(l+k>=99)
								cout<<"\b";
						}
						break;
				}
				setColor(0, 7);
			}
			setColor(0, 7);
			cout<<endl;
		}
		cout<<endl;
		l=l+k;
	}
	
	cout<<"\n\n\n";
	
	int cardType=(discardPile[numOfCards(discardPile)-1]/10)%100;
	if(cardType==13||cardType==14)
	{
		setColor(7);
	}
	else
	{
		setColor( discardPile[numOfCards(discardPile)-1]/1000 );
	}
	cout <<"\t\t\t\t\t\t\t\t\t"<<char(201)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(187);
	setColor(0, 7);
	cout<<endl;
	if(cardType==13||cardType==14)
	{
		setColor(7);
	}
	else
	{
		setColor( discardPile[numOfCards(discardPile)-1]/1000 );
	}
	cout <<"\t\t\t\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
	setColor(0, 7);
	if(cardType==13||cardType==14)
	{
		cout<<"\t";
		setColor(discardPile[numOfCards(discardPile)-1]/1000);
		cout<<" ";
		setColor(0, 7);
	}
	cout<<endl;
	if(cardType==13||cardType==14)
	{
		setColor(7);
	}
	else
	{
		setColor( discardPile[numOfCards(discardPile)-1]/1000 );
	}
	cout <<"\t\t\t\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
	setColor(0, 7);
	cout<<endl;
	if(cardType==13||cardType==14)
	{
		setColor(7);
	}
	else
	{
		setColor( discardPile[numOfCards(discardPile)-1]/1000 );
	}
	cout <<"\t\t\t\t\t\t\t\t\t"<<char(186);
	if(cardType<=9)
	{
		cout<<"   "<<cardType<<"   ";
	}
	else
	{
		switch (cardType)
		{
			case 10:
				cout<<"   S   ";
				break;
			case 11:
				cout<<"   R   ";
				break;
			case 12:
				cout<<"  D 2  ";
				break;
			case 13:
				cout<<" WILD! ";
				break;
			case 14:
				cout<<"WILD"<<char(176)<<"D4";
				break;
		}
	}
	cout <<char(186);
	setColor(0, 7);
	cout<<endl;
	if(cardType==13||cardType==14)
	{
		setColor(7);
	}
	else
	{
		setColor( discardPile[numOfCards(discardPile)-1]/1000 );
	}
	cout <<"\t\t\t\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
	setColor(0, 7);
	cout<<endl;
	if(cardType==13||cardType==14)
	{
		setColor(7);
	}
	else
	{
		setColor( discardPile[numOfCards(discardPile)-1]/1000 );
	}
	cout <<"\t\t\t\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
	setColor(0, 7);
	cout<<endl;
	if(cardType==13||cardType==14)
	{
		setColor(7);
	}
	else
	{
		setColor( discardPile[numOfCards(discardPile)-1]/1000 );
	}
	cout <<"\t\t\t\t\t\t\t\t\t"<<char(200)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(188);
	setColor(0, 7);
	cout<<endl;
	
	cout<<"\n\n\n";
	
	l=0;
	for(int i=(numOfCardsPl2/15)+(numOfCardsPl2%15==0?0:1) ; i>=1 ; i-- )
	{
		int k;
		for(int j=1 ; j<=8 ; j++)
		{
			for( k=0 ; k<(i>1?15:numOfCardsPl2-l) ; k++)
			{
				cout<<"  ";
				int cardType=(pl2Deck[l+k]/10)%100;
				if(playerTurn==2)
				{
					if(cardType==13||cardType==14)
					{
						setColor(7);
					}
					else
					{
						setColor( pl2Deck[l+k]/1000 );
					}
				}
				switch (j)
				{
					case 1:
						cout <<char(201)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(187);
						break;
					case 2:
					case 3:
					case 5:
					case 6:
						cout <<char(186)<< "       " <<char(186);
						break;
					case 4:
						cout <<char(186);
						if(playerTurn!=2)
						{
							cout<<"  UNO  ";
						}
						else
						{
							if(cardType<=9)
							{
								cout<<"   "<<cardType<<"   ";
							}
							else
							{
								switch (cardType)
								{
									case 10:
										cout<<"   S   ";
										break;
									case 11:
										cout<<"   R   ";
										break;
									case 12:
										cout<<"  D 2  ";
										break;
									case 13:
										cout<<" WILD! ";
										break;
									case 14:
										cout<<"WILD"<<char(176)<<"D4";
										break;
								}
							}
						}
						cout <<char(186);
						break;
					case 7:
						cout <<char(200)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(188);
						break;
					case 8:
						setColor(0, 7);
						cout<<"    "<<l+k+1<<"    ";
						if(l+k>=9)
						{
							cout<<"\b";
							if(l+k>=99)
								cout<<"\b";
						}
						break;
				}
				setColor(0, 7);
			}
			setColor(0, 7);
			cout<<endl;
		}
		cout<<endl;
		l=l+k;
	}
	
}

void dealCards(int drawAmm, int player[106], int deck[4][15], int deckIndex[2])
{
	srand(time(0));
	int startIndex=numOfCards(player),counter=0;
	for(int i=deckIndex[0] ; i<4 ; i++)
	{
		for(int j=deckIndex[1] ; j<15 ; )
		{
			player[startIndex+counter]=deck[i][j];
			counter++;
			deck[i][j]--;
			if(deck[i][j]%10 == 0)
			{
				j++;
			}
			else
			{
				int row , column, temp;
				do
				{
					row = rand()%(4-i)+i;
					if(row == i)
					{
						column = rand()%(15-j)+j;
					}
					else
					{
						column = rand()%15;
					}
				}while((deck[row][column]/10)%100==0||(deck[row][column]/10)%100==13||(deck[row][column]/10)%100==14);
				
				temp=deck[i][j];
				deck[i][j]=deck[row][column];
				deck[row][column]=temp;
			}
			if(counter==drawAmm)
			{
				deckIndex[0]=i;
				deckIndex[1]=j;
				return;
			}
		}
		
		deckIndex[1]=0;
	}
	
	deckIndex[0]=0;
	initializeDeck(deck);
	shuffleDeck(deck);
}

void handleSpecialCard(int specialCardType)
{
	
	int temp = specialCardType;
	int digit1 = temp/1000;
	temp = temp - (digit1*1000);
	int digit2 = temp/10;


	if(digit2 == 10 || digit2 == 11 || digit2 == 12 || digit2 == 14)
	{
		SwitchPlayerTurn(playerTurn);
	}
	
	if(digit2 == 12 && playerTurn == 1)
	{
		dealCards(2, pl1Deck, deck,  deckIndex);
	}
	else if(digit2 == 12 && playerTurn == 2)
	{
		dealCards(2, pl2Deck, deck,  deckIndex);
	}
	
	if(digit2 == 14 && playerTurn == 1)
	{
		dealCards(4, pl1Deck, deck, deckIndex);
	}
	else if(digit2 == 14 && playerTurn == 2)
	{
		dealCards(4, pl2Deck, deck, deckIndex);
	}
}

void SwitchPlayerTurn(int &playerTurn)
{
	if(playerTurn == 1)
	{
		playerTurn = 2;
	}
	else if(playerTurn == 2)
	{
		playerTurn = 1;
	}
}

void shuffleDeck(int deck[4][15])
{
	int temp = 0;
	int row = 0, column = 0;
	
	srand(time(0));
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			row = rand()%4;
			column = rand()%15;
			temp = deck[row][column];
			deck[row][column] = deck[i][j];
			deck[i][j] = temp;
		}
	}
}

int numOfCards(int player[106])
{
	int num=0;
	while(player[num]!=0)
		num++;
	return num;
}

void print(int deck[4][15])
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 15; j++)
		{
			cout << deck[i][j] << " ";
		}
		cout << endl;
	}
}

void printDiscard(int discardPile[108])
{
	for(int i=0 ; i<numOfCards(discardPile) ; i++)
	{
		cout<<discardPile[i]<<" ";
	}
	cout<<endl;
}

void print(int player[106])
{
	for(int i=0 ; i<numOfCards(player) ; i++)
	{
		cout<<player[i]<<" ";
	}
	cout<<endl;
}

void setColor(int bgColor, int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void clearScreen()
{
	system("CLS");
}

void ValidateFirstCard(int deck[4][15])
{
	int number = 0;
	int temp = 0;
	int firstDigit = 0, secondDigit = 0;
	
	do
	{
		number = deck[0][0];
		firstDigit = number/1000;
		number = number - (firstDigit*1000);
		secondDigit = number/10;
		if(secondDigit == 10 || secondDigit == 11 || secondDigit == 12 || secondDigit == 13 || secondDigit == 14)
		{
			temp = deck[0][0];
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 15; j++)
				{
					if(j == 14 && i < 3)
					{
						deck[i][j] = deck[i + 1][0];
					}
					else if(j < 14)
					{
						deck[i][j] = deck[i][j + 1];	
					}
				}
			}
			deck[3][14] = temp;
		}
	}while(secondDigit == 10 || secondDigit == 11 || secondDigit == 12 || secondDigit == 13 || secondDigit == 14);
}

void playTurn(int discardPile[108],int pl1Deck[106],int pl2Deck[106],int deck[4][15], int deckIndex[2],int &playerTurn, bool &unoPl1, bool &unoPl2, char &exitChar)
{	
	char choice;
	int choose;
	do
	{
		switch(playerTurn)
		{
			case 1:
				{
					player1ChoiceInput:
					cout << "Player 1" << endl;
					cout << "Player 1 UNO: " << unoPl1 << " Player 2 UNO: " << unoPl2 << endl; 
					cout << "What do you want to do?" << endl;
					cout << "1. Draw Card" << endl;
					cout << "2. Play Card" << endl;
					if(numOfCards(pl1Deck) == 2 && unoPl1 == false)
					{
						cout << "3. Call Uno" << endl;
						cout << "Choice: ";
						cin >> choice;
					}
					else if(numOfCards(pl2Deck) <= 1 && unoPl2 == false)
					{
						cout << "4. Catch Uno" << endl;
						cout << "Choice: ";
						cin >> choice; 
					}
					else
					{
						cout << "Choice: ";
						cin >> choice;
						if((choice != '1' && choice != '2' && choice != 'E') || choice == '3' || choice == '4')
						{
							cout << "Invalid Choice! Please Try Again" << endl;
							goto player1ChoiceInput;
						}
					}
					break;
				}
			case 2:
				{
					player2ChoiceInput:
					cout << "Player 2" << endl;
					cout << "Player 1 UNO: " << unoPl1 << " Player 2 UNO: " << unoPl2 << endl; 
					cout << "What do you want to do?" << endl;
					cout << "1. Draw Card" << endl;
					cout << "2. Play Card" << endl;
					if(numOfCards(pl2Deck) == 2 && unoPl2 == false)
					{
						cout << "3. Call Uno" << endl;
						cout << "Choice: ";
						cin >> choice;
					}
					else if(numOfCards(pl1Deck) <= 1 && unoPl1 == false)
					{
						cout << "4. Catch Uno" << endl;
						cout << "Choice: ";
						cin >> choice; 
					}
					else
					{
						cout << "Choice: ";
						cin >> choice;
						if((choice != '1' && choice != '2' && choice != 'E') || choice == '3' || choice == '4')
						{
							cout << "Invalid Choice! Please Try Again" << endl;
							goto player2ChoiceInput;
						}
					}
					break;
				}	
		}
	}while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'E');
	
	if(playerTurn == 1)
	{
		if(choice == '3')
		{
			callUno(unoPl1, unoPl2);
			goto player1ChoiceInput;
		}
		if(choice == '4')
		{
			dealCards(2, pl2Deck, deck, deckIndex);
			goto player1ChoiceInput;
		}
		if(choice == 'E')
		{
			do
			{
				cout << "Are You Sure You Want To Exit?" << endl;
				cout << "Enter Y for Yes, N for No" << endl;
				cin >> choice;
				if(choice != 'Y' && choice != 'N')
				{
					cout << "Invalid Choice! Please Try Again" << endl;
				}
			}while(choice != 'Y' && choice != 'N');
			switch(choice)
			{
				case 'Y':
				{
					exitChar = 'Y';
					return;
					break;	
				}
				case 'N':
				{
					exitChar = 'N';
					goto player1ChoiceInput;
					break;
				}
			}
		}
		if(choice == '1')
		{
			dealCards(1, pl1Deck, deck, deckIndex);
			unoPl1 = false;
		}
		else if(choice == '2')
		{
			Player1input:
			cout << "Which card do you want to put down?" << endl;
			cout << "Choose from 1 to " << numOfCards(pl1Deck) << " from your deck  or input 0 to draw a card" << endl;
			cin >> choose;
			if(choose == 0)
			{
				dealCards(1, pl1Deck, deck, deckIndex);
				unoPl1 = false;
				goto endofTurn;
			}
			else if(choose > numOfCards(pl1Deck) || choose < 1)
			{
				cout << "Invalid Choice! Please Try Again" << endl;
				goto Player1input;
			}
			else
			{
				choose -= 1;
				if(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar))
				{
					if(exitChar == 'Y')
					{
						return;
					}
					UpdateDiscardPile(pl1Deck[choose], discardPile);
					handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
					RemovePlayerCard(pl1Deck, choose); 
					goto endofTurn;
				}
				else
				{
					cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
					goto Player1input;
				}
			}
			unoPl1 = false;
		}
	}
	if(playerTurn == 2)
	{
		if(choice == '3')
		{
			callUno(unoPl1, unoPl2);
			goto player2ChoiceInput;
		}
		if(choice == '4')
		{
			dealCards(2, pl1Deck, deck, deckIndex);
			goto player2ChoiceInput;
		}
		if(choice == 'E')
		{
			do
			{
				cout << "Are You Sure You Want To Exit?" << endl;
				cout << "Enter Y for Yes, N for No" << endl;
				cin >> choice;
				if(choice != 'Y' && choice != 'N')
				{
					cout << "Invalid Choice! Please Try Again" << endl;
				}
			}while(choice != 'Y' && choice != 'N');
			switch(choice)
			{
				case 'Y':
				{
					exitChar = 'Y';
					return;
					break;	
				}
				case 'N':
				{
					exitChar = 'N';
					goto player2ChoiceInput;
					break;
				}
			}
		}
		if(choice == '1')
		{
			dealCards(1, pl2Deck, deck, deckIndex);
			unoPl2 = false;
		}
		else if(choice == '2')
		{
			Player2input:
			cout << "Which card do you want to put down?" << endl;
			cout << "Choose from 1 to " << numOfCards(pl2Deck) << " from your deck " << endl;
			cin >> choose;
			if(choose == 0)
			{
				dealCards(1, pl2Deck, deck, deckIndex);
				unoPl2 = false;
				goto endofTurn;
			}
			else if(choose > numOfCards(pl2Deck) || choose < 1)
			{
				cout << "Invalid Choice! Please Try Again" << endl;
				goto Player2input;
			}
			else
			{
				choose -= 1;
				if(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar))
				{
					if(exitChar == 'Y')
					{
						return;
					}
					UpdateDiscardPile(pl2Deck[choose], discardPile);
					handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
					RemovePlayerCard(pl2Deck, choose);
					goto endofTurn;
				}
				else
				{
					cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
					goto Player2input;
				}
			}
			unoPl2 = false;
		}
	}
	endofTurn:
	return;
}

void RemovePlayerCard(int playerDeck[106],int index)
{
	for(int i = index; i < numOfCards(playerDeck); i++)
	{
		if(i < 106)
		{
			playerDeck[i] = playerDeck[i+1];	
		}
		else
		{
			playerDeck[i] = 0;
		}
	}
}

void UpdateDiscardPile(int playedCard, int discardPile[108])
{
	int index = numOfCards(discardPile);
	discardPile[index] = playedCard;
}

bool isValidPlay(int &playerCard, int topCard, char &exitChar)
{
	int playerCardRefNumber = playerCard, topCardRefNumber = topCard;
	int d1 = 0, d2 = 0;
	int n1 = 0, n2 = 0;
	
	d1 = playerCard/1000;
	n1 = topCard/1000;
	
	playerCardRefNumber = playerCardRefNumber - (d1*1000);
	d2 = playerCardRefNumber/10;
	
	topCardRefNumber = topCardRefNumber - (n1*1000);
	n2 = topCardRefNumber/10;
	
	if(d2 == 13 || d2 == 14)
	{
		WildCardSetColor(playerCard, exitChar);
		return true;
	}
	else
	{
		if(d1 == n1 || d2 == n2)
		{
			return true;	
		}
		else
		{
			return false;
		}
	}
}

void WildCardSetColor(int &playerCard, char &exitChar)
{
	int tempNum = playerCard;
	int d1 = 0;
	d1 = tempNum/1000;
	playerCard = playerCard - d1*1000;
	char choice = '0';
	colorInput:
	cout << "Which Color Should The Next Card Be?" << endl;
	cout << "1.Blue\n2.Green\n3.Yellow\n4.Red" << endl;
	cout << "Choice:";
	cin >> choice;
	if(choice == 'E')
	{
		do
		{
			cout << "Are You Sure You Want To Exit?" << endl;
			cout << "Enter Y for Yes, N for No" << endl;
			cin >> choice;
			if(choice != 'Y' && choice != 'N')
			{
				cout << "Invalid Choice! Please Try Again" << endl;
			}
		}while(choice != 'Y' && choice != 'N');
		switch(choice)
		{
			case 'Y':
			{
				exitChar = 'Y';
				return;
				break;	
			}
			case 'N':
			{
				exitChar = 'N';
				break;
			}
		}
	}
	else
	{
		switch(choice)
		{
		case '1':
			{
				playerCard = playerCard + 1000;
				cout << playerCard << endl;
				break;
			}
		case '2':
			{
				playerCard = playerCard + 2000;
				cout << playerCard << endl;
				break;
			}
		case '3':
			{
				playerCard = playerCard + 6000;
				cout << playerCard << endl;
				break;
			}
		case '4':
			{
				playerCard = playerCard + 4000;
				cout << playerCard << endl;
				break;
			}
		default:
			{
				cout << "Invalid Choice! Please Choose A Valid Color" << endl;
				goto colorInput;
				break;
			}
		}
	}
}

bool callUno(bool &unoPl1, bool &unoPl2)
{
	if(playerTurn == 1 && unoPl1 == false)
	{
		unoPl1 = true;
		return unoPl1;
	}
	if(playerTurn == 2 && unoPl2 == false)
	{
		unoPl2 = true;
		return unoPl2;
	}
	return false;
}

void RecycleDeck(int discardPile[108], int deck[4][15])
{
	int discardPileCard = 0, d1 = 0, d2 = 0;
	int deckCard = 0, n1 = 0, n2 = 0;
	
	for(int i = 0; i < numOfCards(discardPile); i++)
	{
		discardPileCard = discardPile[i];
		d1 = discardPileCard/1000;
		discardPileCard = discardPileCard - d1*1000;
		d2 = discardPileCard/10;
		for(int j = 0; j < 4; j++)
		{
			for(int k = 0; k < 15; k++)
			{
				deckCard = deck[j][k];
				n1 = deckCard/1000;
				deckCard = deckCard - n1*1000;
				n2 = discardPileCard/10;
				if(d1 == n1 && d2 == n2)
				{
					deck[j][k]++;
				}
			}
		}
	}
}
