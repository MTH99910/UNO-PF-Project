#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

//GameSystem Functions
void StartGame(int &pl1Won, int &pl2Won);
void saveLoadGameResult(int &pl1Won,int &pl2Won, bool saveOrLoad);
void saveLoadGameResult(int &pl1Won,int &pl2Won);

//Deck, DiscardPile and Hand Manipulation Functions
void initializeDeck(int deck[4][15]);
void shuffleDeck(int deck[4][15]);
int numOfCards(int player[106]);
void UpdateDiscardPile(int playedCard, int discardPile[108]);
void dealCards(int drawAmm, int player[106], int deck[4][15], int deckIndex[2]);
void RemovePlayerCard(int playerDeck[106], int index);
void RecycleDeck(int discardPile[108], int deck[4][15], int &drawAmm);

//Printing and Helping Printing Functions
void printBoard(int pl1Deck[106],int pl2Deck[106],int discardPile[108], int playerTurn);
void setColor(int bgColor, int textColor=0);
void clearScreen();
void test();

//Player Turn Functions
void playTurn(int discardPile[108], int pl1Deck[106], int pl2Deck[106], int deck[4][15], int deckIndex[2],int &playerTurn, bool &unoPl1, bool &unoPl2, char &exitChar, bool &cardDrawn);
bool isValidPlay(int &playerCard, int topCard, char &exitChar);
void handleSpecialCard(int specialCardType);
void ValidateFirstCard(int deck[4][15]);
void SwitchPlayerTurn(int &playerTurn);
void SwitchPlayerTurn(int &playerTurn, bool intermidiateStageOverload );
void WildCardSetColor(int &wildCard, char &exitChar);
bool callUno(bool &unoPl1, bool &unoPl2);
 
//Nessecary Global Varaibles
int playerTurn = 1, deck[4][15]={0}, pl1Deck[106]={0}, pl2Deck[106]={0}, deckIndex[2]={0}, discardPile[108]={0};
 
int main()
{
	//CREATING OPENING and READING FILE
	int pl1Won=0, pl2Won=0;
	saveLoadGameResult( pl1Won, pl2Won);
	char choice = '0';
	while(choice != '3')
	{
		clearScreen();
		choice = '0';
		do
		{	
			//MAIN MENU
			cout << "========== Welcome to UNO ==========="<< endl;
			cout << "1. Play" << endl;
			cout << "2. Load Score" << endl;
			cout << "3. Exit" << endl;
			cout << "4. test" << endl;
			cout << "Choice: ";
			cin >> choice;
		
			if(choice != '1' && choice != '2' && choice != '3' && choice != 'E' && choice != '4')
			{
				cout << "Invalid Input! Please Choose One Of The Menu Options" << endl;
			}
		}while(choice != '1' && choice != '2' && choice != '3' && choice != 'E' && choice != '4');
		//MENU OPERATIONS
		switch(choice)
		{
			case '1':
				{
					StartGame( pl1Won, pl2Won);
					break;
				}
			case '2':
				{
					saveLoadGameResult( pl1Won, pl2Won, false);
					cout<<"enter any character to return";
					getch();
					break;
				}
			case '3':
				{
					return 0;
					break;
				}
			case '4':
				{
					//only for the ruberick test cases
					test();
					cout<<"enter any character to return";
					getch();
					break;
				}
			case 'E':
				{
					return 0;
					break;
				}
			default:
				{
					break;
				}
		}
	}
	return 0;
}

void StartGame(int &pl1Won,int &pl2Won)
{
	//THIS FUNCTION HOLDS THE GAME LOOP
	
	//INITIALISING VARIABLES
	bool unoPl1 = false, unoPl2 = false;
	char exitChar = 'N';
	bool cardDrawn = false;
	
	deck[4][15]={0};
	pl1Deck[106]={0};
	pl2Deck[106]={0};
	deckIndex[2]={0};
	
	//PREPAIRING DECK
	clearScreen();
	initializeDeck(deck);
	shuffleDeck(deck);
	ValidateFirstCard(deck);
	
	//DEALING STARTING CARDS
	dealCards(1, discardPile, deck, deckIndex);
	dealCards(7, pl1Deck, deck, deckIndex);
	dealCards(7, pl2Deck, deck, deckIndex);
	
	//GAME LOOP
	while(numOfCards(pl1Deck) > 0 && numOfCards(pl2Deck) > 0)
	{
		printBoard(pl1Deck, pl2Deck, discardPile, playerTurn);
		playTurn(discardPile, pl1Deck, pl2Deck, deck, deckIndex, playerTurn, unoPl1, unoPl2, exitChar, cardDrawn);
		//EXIT SCENARIO
		if(exitChar == 'Y')
		{
			return;
		}
		SwitchPlayerTurn(playerTurn, 0);
		clearScreen();
	}
	
	//WINNING SCENARIO
	if(numOfCards(pl1Deck) == 0)
	{
		cout << "Congratulations! Player 1 Won!" << endl;
		pl1Won++;
	
	}
	else
	{
		cout << "Congratulations! Player 2 Won!" << endl;
		pl2Won++;
	}
	cout<<"                                                .:+%%%%#                          .                                  "<<endl;
	cout<<"                                             :%%%%%%%%%%:                         :------:.                          "<<endl;
	cout<<"                     ....                 .%%%%%%%%%%%%%%                        :-------:             .-:           "<<endl;
	cout<<"                .::::::::               .%%%%%%%%%%%%%%%%#                      :--------.         :=+++++.          "<<endl;
	cout<<"                 -:::::::              =%%%%%%%%%%%%%%%%%%:              .      :-------.     .:+++++++++++          "<<endl;
	cout<<"                 ::::::::             *%%%%%%%%%%%%*-::.....      .:=+++++:      .-----.       :+++++++++++-         "<<endl;
	cout<<"                .::::::::            *%%%%%%%%*.                  .+++++++=        .-.          -+++++++++++.        "<<endl;
	cout<<"                .-::::::.           +%%%%%%%#                      :+++++++.                    .+++++++++++=        "<<endl;
	cout<<"                     .-:           .%%%%%%%#                       .+++++++:                      +++++++++++        "<<endl;
	cout<<"         -                         +%%%%%%%       .=%%%%%%=.        =+++++++                      .++++++++++-       "<<endl;
	cout<<"       :++++:.                     #%%%%%%#    -%%%%%%%%%%%%%+.     .+=-:.                         =++++++++++       "<<endl;
	cout<<"     .++++++++++                   *%%%%%%%  *%%%%%%%%%%%%%%%%%:                                   .++++++++++       "<<endl;
	cout<<"    .++++++++++=                   -%%%%%%%=%%%%%%%%%%%%%%%%%%%%-             ....                  ++++++++++.      "<<endl;
	cout<<"      .=+++++++:                    %%%%%%%%%%%%%%%%%:..-%%%%%%%%         =++++++++++++.            =+++++++++.      "<<endl;
	cout<<"         .-++++.                    .%%%%%%%%%%%%%-      .%%%%%%%:     :++++++++++++++++++:        .++++++++++       "<<endl;
	cout<<"                                     .%%%%%%%%%%%        :%%%%%%%:    -++++++++++++++++++++++:   :++++++++++++       "<<endl;
	cout<<"                       :-:            .%%%%%%%%%%+.  .-*%%%%%%%%#    .+++++++++++++++++++++++++++++++++++++++:       "<<endl;
	cout<<"                      :-----.           #%%%%%%%%%%%%%%%%%%%%%%%.    -+++++++++:  :+++++++++++++++++++++++++=        "<<endl;
	cout<<"                     ---------:.        %%%%%%%%%%%%%%%%%%%%%%*.     =+++++++++.      -++++++++++++++++++++:         "<<endl;
	cout<<"                   .-----------         %%%%%%%%%%%%%%%%%%%%=        .+++++++++=         -+++++++++++++++:           "<<endl;
	cout<<"                     .:-------.         +%%%%%%%*%%%%%%#=.           .++++++++++.           .:-==+==-:.              "<<endl;
	cout<<"                         .---:          :%%%%%%%=                     :+++++++++=        ...=+                       "<<endl;
	cout<<"                            .         .::#%%%%%%%.                    .++++++++++:     -++++++-                      "<<endl;
	cout<<"                                 .:-------%%%%%%%+---:.                 ++++++++++      +++++++.                     "<<endl;
	cout<<"                              .:------=+**%%%%%%%%-------:              ++++++++++      -++++++=                     "<<endl;
	cout<<"                            .:-----+#######%%%%%%%###=------.  ..:=+++++++++++++++       ++++:                       "<<endl;
	cout<<"                           .-----=#########%%%%%%%######+---=++++++++++++++++++++.                                   "<<endl;
	cout<<"                          .------##########%%%%%%%########*++++++++++++++++++++=                        ..:--:.      "<<endl;
	cout<<"                         .------##########%%%%%%%########+++++++++++++++++++-.                      .:::::::::-      "<<endl;
	cout<<"                        .-------##########%%%%%%%######*++++++++++++++=-.            .           .-::::::::::::.     "<<endl;
	cout<<"                        :-------#########%%%%%%%######*+++++++++=---:             .*%%=        .:::::::::::::::.     "<<endl;
	cout<<"                       -------:-#######%%%%%%%%#######++++++++###----:          .*%%%%%%.     .::::::::::::::::.     "<<endl;
	cout<<"                      :+-----:::######%%%%%%%########*++++++*#####----:        #%%%%%%%%%*   .:::::::::::::::::.     "<<endl;
	cout<<"                     .++----::::#######%%%%%########*++++++*######*----.        =%%%%%%%%-   -::::::::::::-.         "<<endl;
	cout<<"                     +++=--:::::-########%##########*+++++#########*----.        .#%%%%:    .:::::::::::             "<<endl;
	cout<<"                    :++++--::::::*##################******##########+---:          :%:      -::::::::::              "<<endl;
	cout<<"                   .-++++-::::::::*#################################*----                   ::::::::::.              "<<endl;
	cout<<"                  .--=+++-:::::::::*###########################*+:::::::::::.              .:::::::::-               "<<endl;
	cout<<"                  :---++--::::::::--+##############*########*-:::::::::::::::::            :::::::::::               "<<endl;
	cout<<"                 .----+=---::::::-----############*::::::::::::::::::::::::::::::.        .::::::::::.               "<<endl;
	cout<<"                .-----:-----::::-------=##########-:::::::::::::::::::::::::::::::::.    :::::::::::-.               "<<endl;
	cout<<"                -----::-----:::----------+#######+-::::::::::::::-=*=---:-:::::::::::::::::::::::::::                "<<endl;
	cout<<"               :+---::::--------------------#########*****+****####*---:  .-:::::::::::::::::::::::-.                "<<endl;
	cout<<"              .++---:::::--=++----------------+###################=----      ::::::::::::::::::::::.                 "<<endl;
	cout<<"              =+++-:::::::=++++=------------------=############+------.        .-::::::::::::::::.                   "<<endl;
	cout<<"             :-+++-:::::::-=+++++-----------------------------------:             .:::::::::::.      -+++++++=-.     "<<endl;
	cout<<"            .--=+---::::-----++++++--------------------------------.                                 -+++++++++.     "<<endl;
	cout<<"            :--------::-------=++++++=--------------------------:.                                   -++++++++=      "<<endl;
	cout<<"           .---::----=----------=++++++++-------------------:.                      :%.              :++++++++.      "<<endl;
	cout<<"          .=--::::--+++------------+++++++++=-----------:.                       .*%%%%:              ......::       "<<endl;
	cout<<"          =+-::::::+++++=-------------=+++++++++++=-:                          .%%%%%%%%.                            "<<endl;
	cout<<"         :++=:::::---+++++=----------------=+++=:.                              :%%%%%%%*                            "<<endl;
	cout<<"        .-++--:::-----=+++++=--------------:                                     -%%%%%%%.              :+.          "<<endl;
	cout<<"        :---------------=++++++=-------:.                                        .%%%%%%%-            .+++++         "<<endl;
	cout<<"       .--::--++=----------+++++++=.                                                  .:=:          .++++++++=.      "<<endl;
	cout<<"       --::::+++++=------------.                                                                    .=+++++++++=.    "<<endl;
	cout<<"      .---::--=+++++=-----:                                                                           .++++++++:     "<<endl;
	cout<<"      :----------+++++-.                                                                                .++++-       "<<endl;
	cout<<"     .------------.                                                                                       :=         "<<endl;
	cout<<"      .-----::.                                                                                                      "<<endl;
	//SAVES THE WIN COUNT
	saveLoadGameResult( pl1Won, pl2Won, true);
	//OUTPUTS WIN COUNT
	saveLoadGameResult( pl1Won, pl2Won, false);
	cout << "Press Enter to return to main menu...." << endl;
	getch();
	
	clearScreen();
	return;
}

void initializeDeck(int deck[4][15])
{
	//INITIAALISES 2D ARRAY OF 4 BY 15 WITH 4 DIGIT INTEGER ENTERIES, FIRST DIGIT IS COLOR (1,2,6 or 4), NEXT TWO ARE THE TYPE, AND LAST IS THE AMOUNT OF CARDS OF THAT TYPE(2 OR 1)
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
	
	int numOfCardsPl1=numOfCards(pl1Deck), numOfCardsPl2=numOfCards(pl2Deck), l=0;//L IS A VARIABLE USED TO HELP IN INDEXING OF ARRAY
	
	//PLAYER 1'S  DECK OUTPUT
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
	
	//DISCARD PILE'S TOP CARD LINE BU LINE PRINT
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
	if(cardType==13||cardType==14)
	{
		cout<<"\t";
		setColor(discardPile[numOfCards(discardPile)-1]/1000);
		cout<<"   ";
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
	if(cardType==13||cardType==14)
	{
		cout<<"\t";
		setColor(discardPile[numOfCards(discardPile)-1]/1000);
		cout<<"   ";
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
	
	//PLAYER 2'S DECK OUTPUT
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
	//DEALS CARDS SEQUENCIALLY 
	srand(time(0));
	int i,j;
	int startIndex=numOfCards(player),counter=0;
	do
	{
		for( i=deckIndex[0] ; i<4 ; i++)
		{
			for( j=deckIndex[1] ; j<15 ; )
			{
				if(deck[i][j]%10!=0)
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
						//SWITCHES PLACE OF CARDS WICH ARE MORE THAN ONE WITH NON POWER CARD SO THAT PROBABILITY IS NORMAL
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
				}
				else
					j++;
				if(counter>=drawAmm)
				{
					deckIndex[0]=i;
					deckIndex[1]=j;
					return;
				}
			}
			
			deckIndex[1]=0;
		}
		RecycleDeck( discardPile, deck, drawAmm);
		shuffleDeck(deck);
		deckIndex[0]=0;
	}while(true);
}

void handleSpecialCard(int specialCardType)
{
	
	//REPEATS PLAYER TURN (EXCEPT FOR WILD), AND ALLOWS TO CHOSE COLOR FOR WILDS, AND DRAWS CARDS IN DRAW 2 AND DRAW 4
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
	//SIMPLY SWITCH PLAYER TURN
	if(playerTurn == 1)
	{
		playerTurn = 2;
	}
	else if(playerTurn == 2)
	{
		playerTurn = 1;
	}
}

void SwitchPlayerTurn(int &playerTurn, bool intermidiateStageOverload )
{
	//OVER LOADED FUNCTION FOR INTERMEDIATE STAGE TO ALLOW ACTUAL GAME BETWEEN OPPONENTS
	if(playerTurn == 1)
	{
		playerTurn=0;
		clearScreen();
		printBoard(pl1Deck, pl2Deck, discardPile, playerTurn);
		cout<<"Switch device or press any button to continue play if it is your turn";
		getch();
		playerTurn = 2;
	}
	else if(playerTurn == 2)
	{
		playerTurn=0;
		clearScreen();
		printBoard(pl1Deck, pl2Deck, discardPile, playerTurn);
		cout<<"Switch device or press any button to continue play if it is your turn";
		getch();
		playerTurn = 1;
	}
}

void shuffleDeck(int deck[4][15])
{
	//SHUFFLES DECK
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
	//HELPING FUNCTION TO SEE HOW MANY CARDS ARE IN A PILE
	int num=0;
	while(player[num]!=0)
		num++;
	return num;
}

void setColor(int bgColor, int textColor)
{
	//SET CONSOLE COLORS 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void clearScreen()
{
	//SIMPLY CLEARS THE SCREEN
	system("CLS");
}

void ValidateFirstCard(int deck[4][15])
{
	//USED TO MAKE SURE FIRST CARD IN DECK IS NOT A SPECIAL CARD SO IT IS NOT PLACED IN DISCARD PILE IN THE BEGINNING OF GAME
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

void playTurn(int discardPile[108],int pl1Deck[106],int pl2Deck[106],int deck[4][15], int deckIndex[2],int &playerTurn, bool &unoPl1, bool &unoPl2, char &exitChar, bool &cardDrawn)
{	
	//HANDELS BOTH PLAYER TURNS
	char choice;
	int choose;
	int numOfCardsPl1 = 0, numOfCardsPl2 = 0;
	
	switch(playerTurn)
	{	
		//PLAYER 1 TURN
		case 1:
			{
				unoPl1 = false;
				numOfCardsPl1 = numOfCards(pl1Deck);
				// WHEN PLAYER HAS ALREADY DRAWN CARD BEFORE IN THE TURN
				if(cardDrawn == true)
				{
					do
					{
						cout << "Which card do you want to put down?" << endl;
						cout << "Choose from 1 to " << numOfCardsPl1 << " from your deck or input 0 to skip your turn" << endl;
						cin >> choose;
						if (cin.fail())
						{
			            cin.clear();
			            cin.ignore(100,'\n');
			            choose=108;
			        	}
						if(choose <= numOfCardsPl1 && choose > 0)
						{
							choose -= 1;
							do
							{
								if(!(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)))
								{
									cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
									cout << "Which card do you want to put down?" << endl;
									cout << "Choose from 1 to " << numOfCardsPl1 << " from your deck or input 0 to skip your turn" << endl;
									cin >> choose;
									if (cin.fail())
									{
						            cin.clear();
						            cin.ignore(100,'\n');
						            choose=108;
						        	}
									if(choose == 0)
									{
										cardDrawn = false;
										unoPl1 = false;
										return;
										break;
									}
									choose -= 1;
									if(choose > numOfCardsPl1-1 || choose < -1)
									{
										break;
									}
								}
							}while(!(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)));	
						}
						else if(choose == 0)
						{
							cardDrawn = false;
							unoPl1 = false;
							return;
						}
						if(choose > numOfCardsPl1 || choose < 0)
						{
							cout << "Invalid Choice! Out Of Bounds Of Your Hand" << endl;
						}
					}while(choose > numOfCardsPl1 || choose < 0);
					
					if(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar))
					{
						UpdateDiscardPile(pl1Deck[choose], discardPile);
						handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
						RemovePlayerCard(pl1Deck, choose);
						if((discardPile[numOfCards(discardPile) - 1]/10)%100 == 13 || (discardPile[numOfCards(discardPile) - 1]/10)%100 == 14)
						{	
							WildCardSetColor(discardPile[numOfCards(discardPile) - 1], exitChar);
						}
					}
					cardDrawn = false;
				}
				// WHEN PLAYER HASN'T ALREADY DRAWN CARD BEFORE IN THE TURN
				else if(cardDrawn == false)
				{
					do
					{
						cout << "Player 1" << endl;
						cout << "Player 1 UNO: " << unoPl1 << " Player 2 UNO: " << unoPl2 << endl; 
						cout << "What do you want to do?" << endl;
						cout << "1. Draw Card" << endl;
						cout << "2. Play Card" << endl;
						cout << "3. Call Uno" << endl;
						cout << "4. Catch Uno" << endl;
						cout << "Choice: ";
						cin >> choice; 
						if(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'E' && choice != 'U')
						{
							cout << "Invalid Choice! Please Try Again" << endl;
						}
						if(choice == '3' || choice == 'U')
						{
						callUno(unoPl1, unoPl2);
						}
						if(choice == '4')
						{
							if(unoPl2 == false && numOfCards(pl2Deck) == 1)
							{
								dealCards(2, pl2Deck, deck, deckIndex);
							}
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
									break;
								}
							}
						}	
					}while(choice != '1' && choice != '2');
				
					if(choice == '1')
					{
						dealCards(1, pl1Deck, deck, deckIndex);
						cardDrawn = true;
						unoPl1 = false;
						SwitchPlayerTurn(playerTurn);
						return;
					}
					else if(choice == '2')
					{
						do
						{
							cout << "Which card do you want to put down?" << endl;
							cout << "Choose from 1 to " << numOfCardsPl1 << " from your deck or input 0 to draw a card" << endl;
							cin >> choose;
							if (cin.fail())
							{
				            cin.clear();
				            cin.ignore(100,'\n');
				            choose=108;
				        	}

							if(choose <= numOfCardsPl1 && choose > 0)
							{
								choose -= 1;
								do
								{
									if(!(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)))
									{
										cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
										cout << "Which card do you want to put down?" << endl;
										cout << "Choose from 1 to " << numOfCardsPl1 << " from your deck or input 0 to draw a card" << endl;
										cin >> choose;
										if (cin.fail())
										{
							            cin.clear();
							            cin.ignore(100,'\n');
							            choose=108;
							        	}
										if(choose == 0)
										{
											dealCards(1, pl1Deck, deck, deckIndex);
											unoPl1 = false;
											cardDrawn = true;
											SwitchPlayerTurn(playerTurn);
											return;
											break;
										}
										choose -= 1;
										if(choose > numOfCardsPl1 || choose < -1)
										{
											break;
										}
									}
								}while(!(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)));	
							}
							else if(choose == 0)
							{
								dealCards(1, pl1Deck, deck, deckIndex);
								cardDrawn = true;
								unoPl1 = false;
								SwitchPlayerTurn(playerTurn);
								return;
							}
							if(choose > numOfCardsPl1 || choose < 0)
							{
								cout << "Invalid Choice! Out Of Bounds Of Your Hand" << endl;
							}
						}while(choose > numOfCardsPl1 || choose < 0);
					
						if(exitChar == 'Y')
						{
							return;
						}
						if(isValidPlay(pl1Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar))
						{
							UpdateDiscardPile(pl1Deck[choose], discardPile);
							handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
							RemovePlayerCard(pl1Deck, choose);
							if((discardPile[numOfCards(discardPile) - 1]/10)%100 == 13 || (discardPile[numOfCards(discardPile) - 1]/10)%100 == 14)
							{
								WildCardSetColor(discardPile[numOfCards(discardPile) - 1], exitChar);
							}
						}
					}
				}	
			break;
		}
		//PLAYER 2 TURN
			case 2:
			{
				numOfCardsPl2 = numOfCards(pl2Deck);
				unoPl2 = false;
				// WHEN PLAYER HAS ALREADY DRAWN CARD BEFORE IN THE TURN
			if(cardDrawn == true)
				{
					do
					{
						cout << "Which card do you want to put down?" << endl;
						cout << "Choose from 1 to " << numOfCardsPl2 << " from your deck  or input 0 to skip your turn" << endl;
						cin >> choose;
						if (cin.fail())
						{
			            cin.clear();
			            cin.ignore(100,'\n');
			            choose=108;
			        	}

						if(choose <= numOfCardsPl2 && choose > 0)
						{
							choose -= 1;
							do
							{
								if(!(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)))
								{
									cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
									cout << "Which card do you want to put down?" << endl;
									cout << "Choose from 1 to " << numOfCardsPl2 << " from your deck  or input 0 to skip your turn" << endl;
									cin >> choose;
									if (cin.fail())
									{
						            cin.clear();
						            cin.ignore(100,'\n');
						            choose=108;
						        	}
									if(choose == 0)
									{
										cardDrawn = false;
										unoPl2 = false;
										return;
										break;
									}
									choose -= 1;
									if(choose > numOfCardsPl2 || choose < -1)
									{
										break;
									}
								}
							}while(!(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)));	
						}
						else if(choose == 0)
						{
							cardDrawn = false;
							unoPl2 = false;
							return;
						}
						if(choose > numOfCardsPl2 || choose < 0)
						{
							cout << "Invalid Choice! Out Of Bounds Of Your Hand" << endl;
						}
					}while(choose > numOfCardsPl2 || choose < 0);
					
					if(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar))
					{
						UpdateDiscardPile(pl2Deck[choose], discardPile);
						handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
						RemovePlayerCard(pl2Deck, choose);
						if((discardPile[numOfCards(discardPile) - 1]/10)%100 == 13 || (discardPile[numOfCards(discardPile) - 1]/10)%100 == 14)
						{	
							WildCardSetColor(discardPile[numOfCards(discardPile) - 1], exitChar);
						}
					}
					cardDrawn = false;
				}
				// WHEN PLAYER HASN'T ALREADY DRAWN CARD BEFORE IN THE TURN
				else if(cardDrawn == false)
				{
					do
					{
						cout << "Player 2" << endl;
						cout << "Player 1 UNO: " << unoPl1 << " Player 2 UNO: " << unoPl2 << endl; 
						cout << "What do you want to do?" << endl;
						cout << "1. Draw Card" << endl;
						cout << "2. Play Card" << endl;
						cout << "3. Call Uno" << endl;
						cout << "4. Catch Uno" << endl;
						cout << "Choice: ";
						cin >> choice; 
						if(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'E' && choice != 'U')
						{
							cout << "Invalid Choice! Please Try Again" << endl;
						}
						if(choice == '3' || choice == 'U')
						{
						callUno(unoPl1, unoPl2);
						}
						if(choice == '4')
						{
							if(unoPl1 == false && numOfCards(pl1Deck) == 1)
							{
								dealCards(2, pl1Deck, deck, deckIndex);
							}
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
									break;
								}
							}
						}	
					}while(choice != '1' && choice != '2');
				
					if(choice == '1')
					{
						dealCards(1, pl2Deck, deck, deckIndex);
						cardDrawn = true;
						unoPl2 = false;
						SwitchPlayerTurn(playerTurn);
						return;
					}
					else if(choice == '2')
					{
						do
						{
							cout << "Which card do you want to put down?" << endl;
							cout << "Choose from 1 to " << numOfCardsPl2 << " from your deck  or input 0 to draw a card" << endl;
							cin >> choose;
							if (cin.fail())
							{
				            cin.clear();
				            cin.ignore(100,'\n');
				            choose=108;
				        	}

							if(choose <= numOfCardsPl2 && choose > 0)
							{
								choose -= 1;
								do
								{
									if(!(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)))
									{
										cout << "Invalid Move, You Cannot Play That Card Right Now!!" << endl;
										cout << "Which card do you want to put down?" << endl;
										cout << "Choose from 1 to " << numOfCardsPl2 << " from your deck  or input 0 to draw a card" << endl;
										cin >> choose;
										if (cin.fail())
										{
							            cin.clear();
							            cin.ignore(100,'\n');
							            choose=108;
							        	}
										if(choose == 0)
										{
											dealCards(1, pl2Deck, deck, deckIndex);
											unoPl2 = false;
											cardDrawn = true;
											SwitchPlayerTurn(playerTurn);
											return;
											break;
										}
										choose -= 1;
										if(choose > numOfCardsPl2 || choose < -1)
										{
											break;
										}
									}
								}while(!(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar)));	
							}
							else if(choose == 0)
							{
								dealCards(1, pl2Deck, deck, deckIndex);
								cardDrawn = true;
								unoPl2 = false;
								SwitchPlayerTurn(playerTurn);
								return;
							}
							if(choose > numOfCardsPl2 || choose < 0)
							{
								cout << "Invalid Choice! Out Of Bounds Of Your Hand" << endl;
							}
						}while(choose > numOfCardsPl2 || choose < 0);
					
						if(exitChar == 'Y')
						{
							return;
						}
						if(isValidPlay(pl2Deck[choose], discardPile[numOfCards(discardPile) - 1], exitChar))
						{
							UpdateDiscardPile(pl2Deck[choose], discardPile);
							handleSpecialCard(discardPile[numOfCards(discardPile) - 1]);
							RemovePlayerCard(pl2Deck, choose);
							if((discardPile[numOfCards(discardPile) - 1]/10)%100 == 13 || (discardPile[numOfCards(discardPile) - 1]/10)%100 == 14)
							{
								WildCardSetColor(discardPile[numOfCards(discardPile) - 1], exitChar);
							}
						}
					}
				}
				break;
			}
	}
	return;
}

void RemovePlayerCard(int playerDeck[106],int index)
{
	//REMOVES CARD FROM SAID INDEX FROM PLAYER TURN THAT IS PUT DOWN AND LEFT SHIFTS THE PLAYER ARRAY UP TO THAT INDEX
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
	//PLACES PLAYED CARD OF PLAYER AT END OF DISCARD PILE
	int index = numOfCards(discardPile);
	discardPile[index] = playedCard;
}

bool isValidPlay(int &playerCard, int topCard, char &exitChar)
{
	//VALIDATES THE PLAYER'S MOVE
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
	//CALLED IF CARD IS WILD AND COLOR IS TO BE SELECTED AND USED
	int tempNum = playerCard;
	int d1 = 0;
	d1 = tempNum/1000;
	playerCard = playerCard - d1*1000;
	char choice = '0';
	do
	{
		cout << "Which Color Should The Next Card Be?" << endl;
		cout << "1.Blue\n2.Green\n3.Yellow\n4.Red" << endl;
		cout << "Choice:";
		cin >> choice;
		if(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'E')
		{
			cout << "Invalid Input! Please Choose One Of The Color Options" << endl;
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
					break;
				}
			}
		}
	}while(choice != '1' && choice != '2' && choice != '3' && choice != '4');
	
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
				break;
			}
	}
}

bool callUno(bool &unoPl1, bool &unoPl2)
{
	//ASSIGNS PLAYER UNO CALLS
	if(playerTurn == 1 && unoPl1 == false && numOfCards(pl1Deck) == 2)
	{
		unoPl1 = true;
		return unoPl1;
	}
	else if(playerTurn == 1 && unoPl1 == false)
	{
		unoPl1 = false;
		dealCards(2, pl1Deck, deck, deckIndex);
	}
	
	if(playerTurn == 2 && unoPl2 == false && numOfCards(pl2Deck) == 2)
	{
		unoPl2 = true;
		return unoPl2;
	}
	else if(playerTurn == 2 && unoPl2 == false)
	{
		unoPl2 = false;
		dealCards(2, pl2Deck, deck, deckIndex);
	}
	return false;
}

void RecycleDeck(int discardPile[108], int deck[4][15], int &drawAmm)
{
	//PLACES CARDS FROM DISCARD PILE BACK IN DECK, LEAVING JUST THE TOP CARD
	int lastCardIndex=numOfCards(discardPile)-1;
	if(lastCardIndex>0)
	{
		int topCard=discardPile[lastCardIndex];
		for(int i=0 ; i<lastCardIndex ; i++)
		{
			for(int j=0 ; j<4 ; j++)
			{
				for(int k=0 ; k<15 ; k++)
				{
					if(discardPile[i]/10==deck[j][k]/10)
					{
						deck[j][k]++;
						discardPile[i]=0;
						break;
					}
				}
			}
		}
		discardPile[lastCardIndex]=0;
		discardPile[0]=topCard;
	}
	//IF THERE IN NO CARD IN DISCARD PILE AND DECK, IGNORES DRAW REQUEST AND CONTINUES PLAY ; EDGE CASE: HAPPENS ONLY IF PLAYERS ARE NOT REALLY PLAYING MUCH BUT ARE COLLECTING CARDS      >:(
	else
	{
		cout<<"                                                     @@@@@@@                                        "<<endl;
		cout<<"                                                  @@@@@@@@@@@@@                                     "<<endl;
		cout<<"                                              @@@@@@@@@@@@@@@@@@@@                                  "<<endl;
		cout<<"                                           @@@@@@@@@@@@@@@@@@@@@@@@@@                               "<<endl;
		cout<<"                                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                            "<<endl;
		cout<<"                                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                         "<<endl;
		cout<<"                                  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                      "<<endl;
		cout<<"                              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                     "<<endl;
		cout<<"                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                        "<<endl;
		cout<<"                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    @@@@                   "<<endl;
		cout<<"                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       @@@@@@@@@@   @@@@@@@@                   "<<endl;
		cout<<"                      @@@@@@@@@@@@@@@@@@@@@@@@@@@@              @@@   @@@@@@@@@@@                   "<<endl;
		cout<<"                         @@@@@@@@@@@@@@@@@@@@@@                    @@@@@@@@@@@@@@                   "<<endl;
		cout<<"                     @@@    @@@@@@@@@@@@@@@@                    @@@@@@@@@@@@@@@@@                   "<<endl;
		cout<<"                     @@@@@@    @@@@@@@@@@                    @@@@@@@@@@@@@@@@@@@@                   "<<endl;
		cout<<"                     @@@@@@@@@    @@@@                   @@@@@@@@@@@@@@@@@@@@@@@@                   "<<endl;
		cout<<"                     @@@@@@@@@@@@                     @@@@@@@@@@@@@@@@@@@@@@@@@@@                   "<<endl;
		cout<<"                     @@@@@@@@@@@@@@@               @@@@@@@@@@@@@@@@@@@@@@@@@@@@@                    "<<endl;
		cout<<"                     @@@@@@@@@@@@@@@@@@         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                      "<<endl;
		cout<<"                     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                          "<<endl;
		cout<<"                     @@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@                             "<<endl;
		cout<<"                      @@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@                                "<<endl;
		cout<<"                         @@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@                                   "<<endl;
		cout<<"                            @@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@                                      "<<endl;
		cout<<"                               @@@@@@@@@@@@@@@@@@@@@@@@@@@                                          "<<endl;
		cout<<"                                  @@@@@@@@@@@@@@@@@@@@@                                             "<<endl;
		cout<<"                                      @@@@@@@@@@@@@@                                                "<<endl;
		cout<<"                                         @@@@@@@@                                                   "<<endl;
		cout<<"                                            @@                                                      "<<endl;
		cout<<"\nDeck is empty";
		drawAmm=0;
	}
}

void saveLoadGameResult(int &pl1Won,int &pl2Won)
{
	//OVERLOADED FUNCTION TO READ FILE AND ASSIGN VALUES TO PL1WON AND PL2WON VARIABLES
	pl1Won=0;
	pl2Won=0;
	
	ifstream SaveFile("saveFile.txt");
	
	bool number=false,pl1=false;
    char value;
    int count=0;
	while (SaveFile.get(value)) 
	{
		if(value==':')
		{
			count=100;
			number=true;
			continue;
		}
		if(count>0 && number)
		{
			if(int(value)!=32)
			{
				if(pl1)
					pl1Won+=count*(int(value)-48);
				else
					pl2Won+=count*(int(value)-48);
			}
			count/=10;
		}
		else if(value=='N')
		{
			pl1=!pl1;
			number=false;
			count=0;
		}
		
    }
	SaveFile.close();
}

void saveLoadGameResult(int &pl1Won,int &pl2Won, bool saveOrLoad)
{
	//WHEN NEEDED TO READ FILE AND SHOW OUTPUT ON SCREEN
	if( saveOrLoad )
	{
	ofstream SaveFile("saveFile.txt");
	SaveFile << "Number of games Player one won:"<<setw(3)<<pl1Won<<"\nNumber of games Player two won:"<<setw(3)<<pl2Won<<"\n";
	}
	//WHEN NEEDED TO WRITE IN FILE THEUPDATED SCORE IN END OF GAME
	else
	{
		string line;
		ifstream SaveFile("saveFile.txt");
		if (!SaveFile)
		{
			cout << "No save data found so file created \n";
			ofstream SaveFile("saveFile.txt");
			SaveFile << "Number of games Player one won:"<<setw(3)<<pl1Won<<"\nNumber of games Player two won:"<<setw(3)<<pl2Won<<"\n";
			SaveFile.close();
	    }
		while (getline (SaveFile, line)) 
		{
		  cout << line << endl;
		}
	}
}

void test()
{
	initializeDeck(deck);
	//shuffleDeck(deck);
	
	int test[60]={0};
	int index=0;
	cout<<endl<<"special cards, one of all color: "<<endl;
	for(int i=0 ; i<4 ; i++)
	{
		for(int j=0 ; j<15 ; j++)
		{
			if((deck[i][j]/10)%100>=10 && (deck[i][j]/10)%100<=14)
			{
				cout<<deck[i][j]<<" ";
			}
		}
		cout<<endl;
	}
	cout<<endl<<"number cards, one of all color: "<<endl;
	for(int i=0 ; i<4 ; i++)
	{
		for(int j=0 ; j<15 ; j++)
		{
			if((deck[i][j]/10)%100>=0 && (deck[i][j]/10)%100<=9)
			{
				cout<<deck[i][j]<<" ";
			}
		}
		cout<<endl;
	}
	
}
