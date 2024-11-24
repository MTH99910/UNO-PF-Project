#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>

using namespace std;


void initializeDeck(int deck[4][15]);
void printBoard(int pl1Deck[106],int  pl2Deck[106],int  discardPile[108], int playerTurn);
void dealCards(int drawAmm, int player[106], int deck[4][15], int deckIndex[2]);
void shuffleDeck(int deck[4][15]);
void handleSpecialCard(int specialCardType);
int numOfCards(int player[106]);
void print(int deck[4][15]);
void print(int player[106]);
void setColor(int bgColor, int textColor=0);
void clearScreen();

int main()
{
	int deck[4][15]={0}, pl1Deck[106]={0}, pl2Deck[106]={0},deckIndex[2]={0}, discardPile[108]={0}, playerTurn=1;
	
	if(cin.fail())
            {
            	cout<<"invalid";
            	cin.clear();
            	cin.ignore(100,'\n');
			}
	
	
	initializeDeck(deck);
	print(deck);
	cout<<endl;
	
	shuffleDeck(deck);
	print(deck);
	cout<<endl;
	
	nigga:
	
	dealCards(1, discardPile, deck, deckIndex);
	dealCards(1, pl1Deck, deck, deckIndex);
	dealCards(1, pl2Deck, deck, deckIndex);
	
	printBoard( pl1Deck, pl2Deck, discardPile, playerTurn);
	
	getch();
	clearScreen();
	goto nigga;
	
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
	for(int i=(numOfCardsPl1/10)+(numOfCardsPl1%10==0?0:1) ; i>=1 ; i-- )
	{
		int k;
		for(int j=1 ; j<=8 ; j++)
		{
			for( k=0 ; k<(i>1?10:numOfCardsPl1-l) ; k++)
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
	for(int i=(numOfCardsPl2/10)+(numOfCardsPl2%10==0?0:1) ; i>=1 ; i-- )
	{
		int k;
		for(int j=1 ; j<=8 ; j++)
		{
			for( k=0 ; k<(i>1?10:numOfCardsPl2-l) ; k++)
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

void handleSpecialCard(int specialCardType)
{
	
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

