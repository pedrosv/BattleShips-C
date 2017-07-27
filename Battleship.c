#include<stdio.h>
#include <stdlib.h>

#define SIZE 9

//Global Variables
char Board[SIZE][SIZE];
char ShipsLocations[SIZE][SIZE];
int Ammunition = 30;
int Winner = 0;

//Structs
struct coordinates{
	int x;
	int y;
};


//functions
void printGameRules(void);
void initBoards(void);
void printBoard(void);
void shipsPlacement(void);
void placeShip(int shipSize);
void printGameOver(void);
struct coordinates getPlayerInput(void);
void fire(int x, int y);
int checkIfWon(void);

void printGameRules(void){
	printf("...");
}

void initBoards(void){
	int i,j;
	for(i = 0; i<SIZE; i++){
		for (j = 0; j<SIZE; j++){
			Board[i][j] = '-';
			ShipsLocations[i][j] = '-';
		}
	}
}

void printBoard(void){

	printf("======================================== \n");
	printf("  A B C D E F G H I \n");

	int i,j;
	for( i = 0; i<SIZE; i++){
		for ( j = 0; j<SIZE; j++){

			if (j == 0){
				printf("%i ", i+1);
			}

			printf("%c ", Board[i][j]);
			
			if(j == SIZE-1){
				printf("\n");
			}
		}
	}

	printf("\nLegenda: X = Erros,  @ = Acertos \n");
	printf("Voce tem %i chances \n", Ammunition );
}

void shipsPlacement(void){
	//place Battleships
	placeShip(4);

	//place Cruisers
	placeShip(2);
	placeShip(2);

	//place Minesweepers
	placeShip(1);
	placeShip(1);
	placeShip(1);
	placeShip(1);

}

void placeShip(int shipSize){
	int x, y;
	int done = 0;
	int orientation;
	int i;

	while(!done){
		//choose random start and orientation
		x = rand()%(SIZE - shipSize);
		y = rand()%(SIZE - shipSize);
		orientation = rand()%1; //0=horizontal and 1=vertical
		done = 1;

		//check if is vallid
		if(orientation == 0){
			//horizontal
			for (i = 0; i<shipSize; i++){
				if(ShipsLocations[x+i][y] != '-'){
					done = 0;
				}
			}
		}
		else{
			//vertical
			for (i = 0; i<shipSize; i++){
				if(ShipsLocations[x][y+i] != '-'){
					done = 0;
				}
			}
		}

	}

	//Place ship
	if(orientation == 0){
		//horizontal
		for (i = 0; i<shipSize; i++){
			ShipsLocations[x+i][y] = '1';
			Board[x+i][y] = '1'; //debug line
		}
	}
	else{
		//vertical
		for (i = 0; i<shipSize; i++){
			ShipsLocations[x][y+i] = '1';
			Board[x][y+i] = '1';
			Board[x+i][y] = '1'; //debug line
		}
	}


}

struct coordinates getPlayerInput(void){
	int input1;
	int input2;

	printf( "Choose a column (1 to %i): ", SIZE);
	scanf("%d", &input1);

	printf( "Now choose a line (1 to %i): ", SIZE);
 	scanf("%d", &input2);

 	struct coordinates p;
 	p.x = input1-1;
 	p.y = input2-1;

 	return p;
}

void fire(int x, int y){
	if (ShipsLocations[x][y] != '1'){
		//missed shot
		Board[x][y] = 'X';
	}
	else{
		//hit the shot
		Board[x][y] = '@';
		ShipsLocations[x][y] = '2';
	}

	Ammunition--;
}

int checkIfWon(void){
	int i, j;
	for(i = 0; i<SIZE; i++){
		for (j = 0; j<SIZE; j++){
			if(ShipsLocations[i][j] == '1'){
				return 0;
			}
		}
	}

	return 1;
}

void printGameOver(void){
	if (Winner){
		printf("Congratulations, you win");
	}
	else{
		printf("You lose. Try Again"); 
	}
}



int main(){
	struct coordinates position;
	srand(time(NULL));

	//setup game
	initBoards();
	shipsPlacement();
	printBoard();


	//game loop
	while(1){
		position = getPlayerInput();
		fire(position.x, position.y);

		printBoard();

		if (checkIfWon()){
			//game ends and player win
			break;
		}

		if (Ammunition <= 0){
			printf("%i \n", Ammunition);
			//game ends and player lose
			break;
		}
	}

	printGameOver();

	return 0;
}
