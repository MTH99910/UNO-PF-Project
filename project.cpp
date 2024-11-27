#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>

using namespace std;

//Deck, DiscardPile and Hand Manipulation Functions
void initializeDeck(int deck[4][15]);
void shuffleDeck(int deck[4][15]);
int numOfCards(int player[106]);
void UpdateDiscardPile(int playedCard, int discardPile[108]);
void dealCards(int drawAmm, int player[106], int deck[4][15], int deckIndex[2]);
void RemovePlayerCard(int playerDeck[106], int index);

//Printing and Helping Printing Functions
void printBoard(int pl1Deck[106],int  pl2Deck[106],int  discardPile[108], int playerTurn);
void setColor(int bgColor, int textColor=0);
void print(int deck[4][15]);
void print(int player[106]);
void printDiscard(int discardPile[108]);
void clearScreen();

//Player Turn Functions
void playTurn(int discardPile[108], int pl1Deck[106], int pl2Deck[106], int deck[4][15], int deckIndex[2],int &playerTurn);
bool isValidPlay(int playerCard, int topCard);
void handleSpecialCard(int specialCardType);
void ValidateFirstCard(int deck[4][15]);
void SwitchPlayerTurn(int &playerTurn);
void WildCardSetColor();
 
//Nessecary Global Varaibles
int playerTurn = 1, deck[4][15]={0}, pl1Deck[106]={0}, pl2Deck[106]={0}, deckIndex[2]={0}, nextColor = -1;
 
int main()
{
	int discardPile[108]={0};
	
	printDiscard(discardPile);
	initializeDeck(deck);
	shuffleDeck(deck);
	ValidateFirstCard(deck);
	dealCards(1, discardPile, deck, deckIndex);
	dealCards(7, pl1Deck, deck, deckIndex);
	dealCards(7, pl2Deck, deck, deckIndex);
	do
	{
		clearScreen();
		printBoard(pl1Deck, pl2Deck, discardPile, playerTurn);
		playTurn(discardPile, pl1Deck, pl2Deck, deck, deckIndex, playerTurn);
		SwitchPlayerTurn(playerTurn);
		clearScreen();
		
	}while((numOfCards(pl1Deck) - 1) != 0 || (numOfCards(pl2Deck) - 1) != 0);
	return 0;
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
	cout <<"\t\t\t\t\t\t"<<char(201)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(187);
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
	cout <<"\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
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
	cout <<"\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
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
	cout <<"\t\t\t\t\t\t"<<char(186);
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
	cout <<"\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
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
	cout <<"\t\t\t\t\t\t"<<char(186)<< "       " <<char(186);
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
	cout <<"\t\t\t\t\t\t"<<char(200)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(205)<<char(188);
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
			cout << temp;
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
					cout << deck[i][j] << " ";
				}
				cout << endl;
			}
			deck[3][14] = temp;
		}
	}while(secondDigit == 10 || secondDigit == 11 || secondDigit == 12 || secondDigit == 13 || secondDigit == 14);
}

void playTurn(int discardPile[108],int pl1Deck[106],int pl2Deck[106],int deck[4][15], int deckIndex[2],int &playerTurn)
{	
	char choice;
	int choose;
	do
	{
		switch(playerTurn)
		{
			case 1:
				{
					cout << "Player 1" << endl;
					break;
				}
			case 2:
				{
					cout << "Player 2" << endl;
					break;
				}
		}
		cout << "What do you want to do?" << endl;
		cout << "1. Draw Card" << endl;
		cout << "2. Play Card" << endl;
		cout << "Choice: ";
		cin >> choice;
		if(choice != '1' && choice != '2')
		{
			cout << "Invalid Choice! Please Try Again" << endl;
		}
	}while(choice != '1' && choice != '2');
	
	if(playerTurn == 1)
	{
		if(choice == '1')
		{
			dealCards(1, pl1Deck, deck, deckIndex);
		}
		else if(choice == '2')
		{
			Player1input:
			cout << "Which card do you want to put down?" << endl;
			cout << "Choose from 1 to " << numOfCards(pl1Deck) << " from your deck " << endl;
			cin >> choose;
			if(choose > numOfCards(pl1Deck) || choose < 1)
			{
				cout << "Invalid Choice! Please Try Again" << endl;
				goto Player1input;
			}
			else
			{
				choose -= 1;
				if(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1]))
				{
					UpdateDiscardPile(pl1Deck[choose], discardPile);
					handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
					RemovePlayerCard(pl1Deck, choose);
					goto end;
				}
				else if(!isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1]))
				{
					cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
					goto Player1input;
				}
			}
		}
	}
	if(playerTurn == 2)
	{
		if(choice == '1')
		{
			dealCards(1, pl2Deck, deck, deckIndex);
		}
		else if(choice == '2')
		{
			Player2input:
			cout << "Which card do you want to put down?" << endl;
			cout << "Choose from 1 to " << numOfCards(pl2Deck) << " from your deck " << endl;
			cin >> choose;
			if(choose > numOfCards(pl2Deck) || choose < 1)
			{
				cout << "Invalid Choice! Please Try Again" << endl;
				goto Player2input;
			}
			else
			{
				choose -= 1;
				if(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1]))
				{
					UpdateDiscardPile(pl2Deck[choose], discardPile);
					handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
					RemovePlayerCard(pl2Deck, choose);
					goto end;
				}
				else if(!isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1]))
				{
					cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
					goto Player2input;
				}
			}
		}
		end:;
	}
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

bool isValidPlay(int playerCard, int topCard)
{
	int playerCardRefNumber = playerCard, topCardRefNumber = topCard;
	int d1 = 0, d2 = 0;
	int n1 = 0, n2 = 0;
	
	d1 = playerCard/1000;
	n1 = topCard/1000;
	
	playerCardRefNumber = playerCardRefNumber - (d1*1000);
	d2 = playerCardRefNumber/10;;
	
	topCardRefNumber = topCardRefNumber - (n1*1000);
	n2 = topCardRefNumber/10;
	
	getch();
	
	if(d2 == 13 || d2 == 14)
	{
		WildCardSetColor();
		return true;
	}
	else if(n2 == 13 || n2 == 14)
	{
		if(d1 == nextColor)
		{
			return true;
		}
		else
		{
			return false;
		}
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

void WildCardSetColor()
{
	char choice = '0';
	colorInput:
	cout << "Which Color Should The Next Card Be?" << endl;
	cout << "1.Blue\n2.Green\n3.Yellow\n4.Red" << endl;
	cout << "Choice:";
	cin >> choice;
	switch(choice)
	{
		case '1':
			{
				nextColor = 1;
				break;
			}
		case '2':
			{
				nextColor = 2;
				break;
			}
		case '3':
			{
				nextColor = 6;
				break;
			}
		case '4':
			{
				nextColor = 4;
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
