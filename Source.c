#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable:4996) //scanf warning disable, yea i know unsafe
#pragma warning(disable:4244) //seed generator warning disable, data loss for RNG not important

//dev mode
int dev = 1; //1= enable debug info, 0= normal

/*Created by: Russell Len
  Start date: 11/5/2020
  Finish date:
  Language: C
  Update notes:
  11/5 - 20/6 -  Creation of base engine and initial story of Luna Falls
  21/6-12/7 - Break, busy with college, hiatus
  13/7 - Scraped Luna Falls story line, updated game engine to prepare for new story idea, added RNG generator for dialog, hiatus again
  21/7 - Re-brainstorm for new story, removed maze generator
  */

int start = 1; //display title menu

void newGame();
void menu();
void displayMap();
void save();
void tutorial();
void objectives();

//RNG for dialog (call this to get random number)
int random(int min, int max);
int random(int min, int max) {
	srand(time(0));
	
	return (rand() % (max - min + 1)) + min;
}



//actions
void right();
void left();
void down();
void up();

//worlds (interact)
void world13(); //home
void world1(); 
void world2(); 
void world3();
void world4(); 
void world5();
void world6();
void world7();
void world8();
void world9();
void world10();
void world11();
void world12();
void world14(); 
void world15(); 
void world16(); 
void world17();
void world18(); 
void world19(); 
void world20(); 
void world21();
void world22(); 
void world23(); 
void world24(); 
void world25(); 

//delay
delay(double second) {
	double mil = 1000.00 * second;
	clock_t startTime = clock();
	while (clock() < (startTime + mil));
}

char name[10];

int currentX, currentY; //current coords
char map[5][5] = {
	{'*', '*', '*','*','*'},
	{'*', '*', '*','*','*'},
	{'*', '*', 'i','*','*'},
	{'*', '*', '*','*','*'},
	{'*', '*', '*','*','*'}

};
int world[5][5];

int completionState[25]; //save states

//main
void main() {
	system("color a");
	system("title Game Project"); //window title
	int i;
	char action;

	if (dev == 1) {
		printf("Dev Mode: ON\n");
	}

	//main menu
	if (start == 1) {
		menu();
	}

	//Continue
	if (start == 0) {

		//check save state
		FILE* checkSave;
		checkSave = fopen("save.txt", "r");
		while (!feof(checkSave)) {
			for (i = 0; i < 25; i++) {
				fscanf(checkSave, "%d\n", &completionState[i]);
				if (dev == 1) {
					printf("World %d = %d\n", i + 1, completionState[i]);
				}
			}
		}
		if (dev == 1) {
			printf("\n\n");
		}

		fclose(checkSave);

		FILE* readname;
		readname = fopen("name.txt", "r");
		fscanf(readname, "%s\n", name);
		fclose(readname);

		//new game
		if (completionState[12] == 0) {
			world13();
		}

		printf("\t\tWorld\n\n");


		//draw map
		displayMap();

		printf("\n\tf = explore\n");
		printf("\to = objectives\n");
		printf("\tt = tutorial\n");
		printf("\tx = save and exit to main menu\n");

		printf("\n\tAction: ");
		scanf("%c", &action);
		rewind(stdin);


		if (action != 'o' && action != 'w' && action != 'a' && action != 's' && action != 'd' && action != 'f' && action != 'x' && action != 't') {
			system("cls");
			main();
		}

		switch (action) {
			//objectives
		case 'o':
			printf("\n");
			objectives();
			printf("\n\n\t");
			system("pause");
			system("cls");
			main();

		case 'x':
			//return to main menu
			save();
			system("cls");
			menu();

		case 'f':
			//interact
				//home
			switch (world[currentX][currentY]) {
			case 13:
				world13();
			case 1:
				world1();
			case 2:
				world2();
			case 3:
				world3();
			case 4:
				world4();
			case 5:
				world5();
			case 6:
				world6();
			case 7:
				world7();
			case 8:
				world8();
			case 9:
				world9();
			case 10:
				world10();
			case 11:
				world11();
			case 12:
				world12();
			case 14:
				world14();
			case 15:
				world15();
			case 16:
				world16();
			case 17:
				world17();
			case 18:
				world18();
			case 19:
				world19();
			case 20:
				world20();
			case 21:
				world21();
			case 22:
				world22();
			case 23:
				world23();
			case 24:
				world24();
			case 25:
				world25();
			}

			//right
		case 'd':
			right();
			system("cls");
			main();

			//left
		case 'a':
			left();
			system("cls");
			main();

			//down
		case 's':
			down();
			system("cls");
			main();

			//up
		case 'w':
			up();
			system("cls");
			main();

			//tutorial
		case 't':
			tutorial();

		}
	}

}

//main menu
void  menu() {
	int nc;
	FILE* fptr;
	fptr = fopen("world.txt", "r");
	if (fptr == NULL) {
		printf("1. New Game\n2. Exit\n> ");
		scanf("%d", &nc);
		rewind(stdin);
		switch (nc) {
		case 1:
			newGame();
			system("cls");
			start = 0;
			main();
			break;
		case 2:
			exit(-1);
			break;

		default:
			printf("Invalid option!\n");
			system("pause");
			system("cls");
			menu();

		}
	}
	char yn;

	if (fptr != NULL) {
		printf("1. New Game\n2. Continue\n3. Exit\n> ");
		scanf("%d", &nc);
		rewind(stdin);

		switch (nc) {
		case 1:
			printf("Warning! Creating a new game will overwrite current save file. Proceed(y/n)? > ");
			scanf("%c", &yn);
			rewind(stdin);

			while (yn != 'y' && yn != 'n') {
				printf("Warning! Creating a new game will overwrite current save file. Proceed(y/n)? > ");
				scanf("%c", &yn);
				rewind(stdin);
			}

			if (yn == 'y') {
				newGame();
				system("cls");
				start = 0;
				main();
			}
			if (yn == 'n') {
				system("cls");
				menu();
			}
			break;
		case 2:
			system("cls");
			start = 0;
			main();
			break;
		case 3:
			exit(-1);
			break;
		default:
			printf("Invalid option!\n");
			system("pause");
			system("cls");
			menu();
		}
	}
	fclose(fptr);
}

//display map
void displayMap() {
	int x, y;
	int n[25];
	int i, j;
	int c = 0;

	printf("\t\t   [w] \n");

	printf("\t\t");

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			printf("%c ", map[i][j]);
			if (i == 1 && j == 4) {
				printf("\n\t    [a] ");
			}
			if (i == 2 && j == 4) {
				printf("[d]");
			}
			if (j == 4 && i != 1 && i != 4) {
				printf("\n\t\t");
			}



			if (map[i][j] == 'i') {
				currentX = i;
				currentY = j;
			}
		}
	}
	printf("\n\t\t   [s] \n");

	//"draw" world
	FILE* worldgen;
	worldgen = fopen("world.txt", "r");

	while (!feof(worldgen)) {
		//read from file
		for (x = 0; x < 25; x++) {
			fscanf(worldgen, "%d\n", &n[x]);
			rewind(stdin);
		}
	}

	fclose(worldgen);

	//assign number to world grid
	if (dev == 1) {
		printf("\nWorld generator test (dev)\n");
	}
	for (x = 0; x < 5; x++) {
		for (y = 0; y < 5; y++) {
			world[x][y] = n[c++];
			if (dev == 1) {
				printf("%2d ", world[x][y]);
			}

			if (y == 4) {
				if (dev == 1) {
					printf("\n");
				}
			}
		}
	}



}

//move right
void right() {
	if (currentY + 1 == 5) {
		map[currentX][currentY] = 'i';
	}
	else {
		map[currentX][currentY] = '*';
		map[currentX][currentY + 1] = 'i';
	}

}

//move left
void left() {
	if (currentY - 1 == -1) {
		map[currentX][currentY] = 'i';
	}
	else {
		map[currentX][currentY] = '*';
		map[currentX][currentY - 1] = 'i';
	}

}

//move down
void down() {
	if (currentX + 1 == 5) {
		map[currentX][currentY] = 'i';
	}
	else {
		map[currentX][currentY] = '*';
		map[currentX + 1][currentY] = 'i';
	}

}

//move up
void up() {
	if (currentX - 1 == -1) {
		map[currentX][currentY] = 'i';
	}
	else {
		map[currentX][currentY] = '*';
		map[currentX - 1][currentY] = 'i';
	}

}

//new game aka random map generator
void newGame() {
	system("cls");

	int worldCode[25] = {
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25
	};
	int a, b, c;
	int i;
	char yn;

	srand(time(0));
	if (dev == 1) {
		printf("World generation test(this screen won't be shown in game)\n");
	}
	//shuffle
	for (i = 0; i < 100; i++) {
		a = (rand() % 25);
		b = (rand() % 25);
		//home is center
		if (a != 12 && b != 12) {
			c = worldCode[a];
			worldCode[a] = worldCode[b];
			worldCode[b] = c;
		}
	}

	for (i = 0; i < 25; i++) {
		if (dev == 1) {
			printf("%-3d", worldCode[i]);
		}
		if (i == 4 || i == 9 || i == 14 || i == 19 || i == 24) {
			if (dev == 1) {
				printf("\n");
			}
		}
	}
	//name
	printf("Enter name(max 10 characters)> ");
	scanf("%s", name);
	rewind(stdin);
	FILE* writename;
	writename = fopen("name.txt", "w");
	fprintf(writename, "%s\n", name);
	fclose(writename);

	system("cls");

	printf("Continue? (y/n=change name and generate new map) > ");
	scanf("%c", &yn);
	rewind(stdin);


	while (yn != 'y' && yn != 'n') {
		printf("Invalid input!\n");
		system("pause");
		system("cls");
		newGame();
	}

	//reshuffle
	if (yn == 'n') {
		system("cls");
		newGame();
	}

	//generate world
	if (yn == 'y') {
		FILE* gen;
		gen = fopen("world.txt", "w");
		for (i = 0; i < 25; i++) {
			fprintf(gen, "%d\n", worldCode[i]);
		}

		fclose(gen);
	}

	//generate save game
	FILE* save;
	save = fopen("save.txt", "w");
	int saves[25] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};
	for (i = 0; i < 25; i++) {
		fprintf(save, "%d\n", saves[i]);
	}

	fclose(save);
}

//worlds

//home
void world13() {
	system("cls");

	switch (completionState[12]) {
		//first time
	case 0:
		printf("World 13 First time\n");
		
			system("pause");
			system("cls");
			printf("Objective updated...\n");
			system("pause");
			system("cls");
			completionState[12] = 1;
			save();
			tutorial();
			main();
			break;

	//explored
	case 1:
		printf("World 13 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}
}

void world1() {
	system("cls");

	switch (completionState[0]) {
		//first time
	case 0:
		printf("World 1 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[0] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 1 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world2() {
	system("cls");

	switch (completionState[1]) {
		//first time
	case 0:
		printf("World 2 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[1] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 2 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world3() {
	system("cls");
	
	switch (completionState[2]) {
		//first time
	case 0:
		printf("World 3 First Time\n");


		system("pause");
		system("cls");
		completionState[2] = 1;
		save();
		main();
		break;

		//explored
	case 1:

		printf("World 3 Visited (maze gen)\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world4() {
	system("cls");

	switch (completionState[3]) {
		//first time
	case 0:
		printf("World 4 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[3] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 4 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world5() {
	system("cls");

	switch (completionState[4]) {
		//first time
	case 0:
		printf("World 5 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[4] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 5 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world6() {
	system("cls");

	switch (completionState[5]) {
		//first time
	case 0:
		printf("World 6 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[5] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 6 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world7() {
	system("cls");

	switch (completionState[6]) {
		//first time
	case 0:
		printf("World 7 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[6] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 7 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world8() {
	system("cls");

	switch (completionState[7]) {
		//first time
	case 0:
		printf("World 8 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[7] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 8 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world9() {
	system("cls");

	switch (completionState[8]) {
		//first time
	case 0:
		printf("World 9 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[8] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 9 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world10() {
	system("cls");

	switch (completionState[9]) {
		//first time
	case 0:
		printf("World 10 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[9] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 10 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world11() {
	system("cls");

	switch (completionState[10]) {
		//first time
	case 0:
		printf("World 11 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[10] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 11 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world12() {
	system("cls");

	switch (completionState[11]) {
		//first time
	case 0:
		printf("World 12 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[11] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 12 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world14() {
	system("cls");

	switch (completionState[13]) {
		//first time
	case 0:
		printf("World 14 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[13] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 14 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world15() {
	system("cls");

	switch (completionState[14]) {
		//first time
	case 0:
		printf("World 15 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[14] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 15 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world16() {
	system("cls");

	switch (completionState[15]) {
		//first time
	case 0:
		printf("World 16 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[15] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 16 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world17() {
	system("cls");

	switch (completionState[16]) {
		//first time
	case 0:
		printf("World 17 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[16] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 17 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world18() {
	system("cls");

	switch (completionState[17]) {
		//first time
	case 0:
		printf("World 18 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[17] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 18 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world19() {
	system("cls");

	switch (completionState[18]) {
		//first time
	case 0:
		printf("World 19 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[18] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 19 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world20() {
	system("cls");

	switch (completionState[19]) {
		//first time
	case 0:
		printf("World 20 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[19] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 20 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world21() {
	system("cls");

	switch (completionState[20]) {
		//first time
	case 0:
		printf("World 21 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[20] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 21 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world22() {
	system("cls");

	switch (completionState[21]) {
		//first time
	case 0:
		printf("World 22 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[21] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 22 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world23() {
	system("cls");

	switch (completionState[22]) {
		//first time
	case 0:
		printf("World 23 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[22] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 23 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world24() {
	system("cls");

	switch (completionState[23]) {
		//first time
	case 0:
		printf("World 24 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[23] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 24 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}

void world25() {
	system("cls");

	switch (completionState[24]) {
		//first time
	case 0:
		printf("World 25 First time\n");

		system("pause");
		system("cls");
		printf("Objective updated...\n");
		system("pause");
		system("cls");
		completionState[24] = 1;
		save();
		main();
		break;

		//explored
	case 1:
		printf("World 25 Visited\n");

		system("pause");
		system("cls");
		main();
		break;
	}

}


//save game (called after completion of each world)
void save() {
	int i;
	system("cls");
	printf("Saving game");
	delay(0.25);
	printf(".");
	delay(0.25);
	printf(".");
	delay(0.25);
	printf(".");
	delay(0.25);
	system("cls");
	FILE* save;
	save = fopen("save.txt", "w");
	for (i = 0; i < 25; i++) {
		fprintf(save, "%d\n", completionState[i]);
	}
	fclose(save);
}

//tutorial
void tutorial() {
	system("cls");
	printf("[TUTORIAL]\n");

	printf("Use the WASD keys to move your character 'i' around the map");

	printf("\n\nUse the 'f' key to explore your current position");

	printf("\nUse the 't' key to see this tutorial again");

	printf("\nUse the 'o' key to see current objectives\n");

	printf("\n\nThe map is randomly generated for every new game,");

	printf("\nThe order of progression is always different for an interesting experience");

	printf("\nYour starting home world, is always at the center\n");


	system("pause");
	system("cls");
}

//objectives (use save state to display objectives)
void objectives() {

	//objectives
	printf("\tMain Objectives:\n");



	printf("\n\tOptional Objectives: ");





}
