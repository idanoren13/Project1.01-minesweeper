#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MINE '*'
#define SPACE ' '
#define ROWS 22
#define COLS 22
#define MINE_QUANTITY 8

void Menu(int game_size[3]);
void User_Input();
void Game_Func();
void Difficulty(int game_size[3]);
void Map_Printer(char map[ROWS][COLS], int rows, int cols);
void Game_Map_Generator(char game_map[ROWS][COLS], int rows, int cols);
void Random_Map_Generator(char consealed_map[ROWS][COLS], int rows, int cols, int mine_quantity);
void Mines_In_Range(char consealed_map[ROWS][COLS], int rows, int cols);
bool Mine_Checker(char consealed_square);
void Last_Cell_Location(char consealed_map[ROWS][COLS], char game_map[ROWS][COLS], int last_cell[2], int row_size, int col_size);
void Map_revealer(char consealed_map[ROWS][COLS], char game_map[ROWS][COLS], int counter, int last_cell[2], int last_row, int last_col, int row_size, int col_size);
int Space_Printer(char consealed_map[ROWS][COLS], char game_map[ROWS][COLS], int row_input, int col_input, int row_size, int col_size);
bool Space_Checker(char square);
void Print_Headline();
void Print_Game_Over();
void Winner_Printer();
void Scan_Two_numbers(char str_input[], int* Num1, int* Num2);

void main() {
	//char game_map[ROWS][COLS];
	//bool flag = false;
	//bool* flag_pointer = &flag;
	//int row_and_col[2];
	//Game_Map_Generator(game_map, ROWS, COLS);
	//User_Input(row_and_col, flag_pointer);
	//Map_Printer(game_map, 15, 15);
	//printf("\n");
	//if (flag)
	//	game_map[row_and_col[0]][row_and_col[1]] = 'F';
	//Map_Printer(game_map, 15, 15);
	//Print_Game_Over();
	//menu();
	//int counter;
	//char consealed_map[ROWS][COLS];
	//int turns_to_win = (15 * 15) - 15;
	//char game_map[ROWS][COLS];
	//Game_Map_Generator(game_map, 15, 15);
	//Random_Map_Generator(consealed_map, 15, 15, 15);
	//consealed_map[0][0] = ' ';
	//Map_Printer(consealed_map, 15, 15);
	//counter = Space_Printer(consealed_map, game_map, 0, 0, 15, 15);
	//printf("\ncounter: %d\nturns to win:%d", counter, turns_to_win);
	//Map_revealer(consealed_map, game_map, 64);
	//printf("'\\' ");
	Game_Func();
}

void User_Input(int nums[2], bool* flag) {
	char str[8];
	char ch;
	const char s[2] = " ";
	char* p = 0;
	char* token;
	int i = 0;
	//printf("enter the string: \n");
	//scanf("%s");
	//printf("*[^\n");
	//scanf(" %c&d&d", &ch, &nums[0], &nums[1]);
	//if((ch=='f')||(ch=='F'))
	//	*flag = true;
	//else
	//	*flag = false;

	fgets(str, 8, stdin);

	/* get the first token */
	token = strtok(str, s);
	if (strcmp(&token, "f") && strcmp(&token, "F")) {
		flag = true;
		token = strtok(NULL, s);
	}
	else
		*flag = false;
	while (token != NULL) {
		nums[i] = strtol(token, &p, 10);

		//printf(" %d\n", nums[i]);

		token = strtok(NULL, s);
		i += 1;
	}
	//printf("%c", *flag);

}

void Game_Func() {
	//user inputs
	int input[2];
	int column_input, row_input, user_input = 0;

	char flag;
	char* flag_pointer = &flag;

	/*game_size[0] -> rows
	 *game_size[1] -> cols
	 *game_size[3] -> Mines quantity
	 */
	int game_size[3] = { 8,8,8 };

	int turns_to_win, flags_remains;
	//last_cell[0] = last row
	//last_cell[1] = las column
	int last_cell[2] = { 0,0 };
	char consealed_map[ROWS][COLS];
	char game_map[ROWS][COLS];



	Menu(game_size);
	Difficulty(game_size);


	//generates the maps for the game
	turns_to_win = (game_size[0] * game_size[1]) - game_size[2];
	flags_remains = game_size[2];
	Game_Map_Generator(game_map, game_size[0], game_size[1]);
	Random_Map_Generator(consealed_map, game_size[0], game_size[1], game_size[2]);

	while (turns_to_win > 0) {
		system("cls");
		Print_Headline();
		Map_Printer(game_map, game_size[0], game_size[1]);
		printf("\n\nTurns To Win:%d              Flags Remains:%d\n\n", turns_to_win, flags_remains);
		printf("Please Enter a row number and a column number : ");
		//scanf("%s", &input);
		//if(input[0]=='f' || input[0]=='F')

		//scanf(" %c%d%d",&flag, &input[0], &input[1]);
		User_Input(input, flag_pointer);


		if (input[0] == -1 && input[1] > 0) { //reveals a portion of the map

		//if (row_input == -1 && column_input > 0) { //reveals a portion of the map

			turns_to_win -= input[1];
			Last_Cell_Location(consealed_map, game_map, last_cell, game_size[0], game_size[1]);
			Map_revealer(consealed_map, game_map, input[1], last_cell, last_cell[0], last_cell[1], game_size[0], game_size[1]);
		}
		//closes the game
		else if (input[0] == -1 && input[1] == -1) {
			printf("GOOD BYE!");
			system("pause");
			return;
		}
		else if (input[0] < 0 || input[1] < 0 || input[0] >= game_size[0] || input[1] >= game_size[1]) {
			printf("invalid input! number are out of boundries\n");
			system("pause");
		}
		else if (game_map[input[0]][input[1]] == consealed_map[input[0]][input[1]] && game_map[input[0]][input[1]] == 'F') {
			printf("invalid input! You already entered that numbers\n");
			system("pause");
		}
		else {
			// if F was pressed 
			if (((flag == 'f') || (flag == 'F')) && (flags_remains > 0)) {
				if (game_map[input[0]][input[1]] == 'X') {
					game_map[input[0]][input[1]] = 'F';
					--flags_remains;
				}
				else if (game_map[input[0]][input[1]] == 'F') {
					game_map[input[0]][input[1]] = 'X';
					++flags_remains;
				}
			}

			else if (Mine_Checker(consealed_map[input[0]][input[1]])) {//check if the selected sqaure is a mine
				Map_Printer(consealed_map, game_size[0], game_size[1]);
				Print_Game_Over();
				system("pause");
				return;
			}
			else if (Space_Checker(consealed_map[input[0]][input[1]])) {
				turns_to_win -= Space_Printer(consealed_map, game_map, input[0], input[1], game_size[0], game_size[1]);
			}

			else {
				game_map[input[0]][input[1]] = consealed_map[input[0]][input[1]];//reveals the selected cell
				--turns_to_win;
			}
		}


	}
	Map_Printer(game_map, game_size[0], game_size[1]);
	Winner_Printer();
	system("pause");
}

void Menu(int game_size[3]) {
	char str_input[6];
	char* token;
	const char s[2] = " ";
	int user_input;
	int row_input = 8, column_input = 8;
	//Prints a headline "Minesweeper"
	Print_Headline();
	printf("Please choose one of the following options and enter it's number:\n\n");
	printf("1 - for size 8x8\n\n2 - for size 12x12\n\n3 - for size 15x15\n\n4 - for custom size\n\n0 - Exit\n\n");

	user_input = atoi(fgets(str_input, 2, stdin));
	//scanf("%d", &user_input);

	switch (user_input)
	{
	case 1:
		game_size[0] = 8;
		game_size[1] = 8;
		game_size[2] = 8;
		break;
	case 2:
		game_size[0] = 12;
		game_size[1] = 12;
		game_size[2] = (12 * 12) * 0.16;
		break;
	case 3:
		game_size[0] = 15;
		game_size[1] = 15;
		game_size[2] = (15 * 15) * 0.16;
		break;
	case 4:
		printf("Custom size. Please enter rows size up to 22 and then columns size up to 22 :");
		Scan_Two_numbers(str_input, &row_input, &column_input);
		/*fgets(str_input, 6, stdin);
		token = strtok(str_input, s);
		row_input = atoi(token);
		token = strtok(NULL, s);
		column_input = atoi(token);*/
		//scanf("%d%d", &row_input, &column_input);
		while ((row_input < 1) || (column_input < 1) || (row_input > 22) || (column_input > 22)) {
			printf("The size is out of boundries! Please Enter again :");
			Scan_Two_numbers(str_input, &row_input, &column_input);
			//scanf("%d%d", &row_input, &column_input);
		}
		game_size[0] = row_input;
		game_size[1] = column_input;
		game_size[2] = (int)sqrt(row_input * column_input);

		break;
	default:
		printf("Invalid input please enter again");
		//return 0;
	}

	//return 1;
}

void Scan_Two_numbers(char str_input[], int* Num1, int* Num2) {
	char* token;
	const char s[2] = " ";
	fgets(str_input, 6, stdin);
	token = strtok(str_input, s);
	*Num1 = atoi(token);
	token = strtok(NULL, s);
	*Num2 = atoi(token);
}

void Difficulty(int game_size[3]) {
	int difficulty = 0;
	while (difficulty < 1 || difficulty > 3) {
		printf("Please choose your difficulty: \n1 -> easy\n2 -> medium\n3 -> hard\n ");
		scanf("%d", &difficulty);
		if (difficulty < 1 || difficulty > 3) {
			printf("Invalid Choise!\n");
		}
	}

	switch (difficulty)
	{
	case 1:
		game_size[2] = sqrt(game_size[0] * game_size[1]);
		break;
	case 2:
		game_size[2] = (game_size[0] * game_size[1]) * 0.16;
		break;
	case 3:
		game_size[2] = (game_size[0] * game_size[1]) * 0.23;
		break;
	default:
		break;
	}
}

//prints the map
void Map_Printer(char map[ROWS][COLS], int rows, int cols) {
	int col_index = 0, row_index = 0;
	printf("\n");
	printf("       ");
	for (col_index = 0; col_index < cols; col_index++) {
		printf("%6d", col_index);
	}
	printf("\n\n");
	for (row_index = 0; row_index < rows; row_index++) {
		for (col_index = 0; col_index < cols; col_index++) {
			if (col_index == 0 && row_index < 10)
				printf("      %d ", row_index);
			if (col_index == 0 && row_index >= 10)
				printf("     %d ", row_index);
			printf(" |%3c ", map[row_index][col_index]);
		}
		printf(" |\n");
	}
}

//genrate the game map - puts 'X' in every cell
void Game_Map_Generator(char game_map[ROWS][COLS], int rows, int cols) {
	for (int index_row = 0; index_row < rows; index_row++)
		for (int index_col = 0; index_col < cols; index_col++)
			game_map[index_row][index_col] = 'X';

}

//generates a random consealed map
void Random_Map_Generator(char consealed_map[ROWS][COLS], int rows, int cols, int mine_quantity) {

	char temp = mine_quantity; //a temp character, uses in both initializing the consealed map and to random the map
	int random_row, random_col = 0;
	int row_index, col_index;

	srand(time(NULL));

	//Initializing the map, places first the mines and then fills the other cells with '0'
	for (row_index = 0; row_index < rows; row_index++)
		for (col_index = 0; col_index < cols; col_index++) {
			if (temp) {
				consealed_map[row_index][col_index] = MINE;
				--temp;
			}
			else
				consealed_map[row_index][col_index] = '0';
		}

	//Random the map
	for (row_index = 0; row_index < rows; row_index++)
		for (col_index = 0; col_index < cols; col_index++) {
			random_row = rand() % (rows - row_index);
			random_col = rand() % (cols - col_index);
			temp = consealed_map[random_row][random_col];
			consealed_map[random_row][random_col] = consealed_map[row_index][col_index];
			consealed_map[row_index][col_index] = temp;
		}

	Mines_In_Range(consealed_map, rows, cols);

	//converts '0' to ' '
	for (int index_cols = 0; index_cols < cols; index_cols++) {
		for (int index_rows = 0; index_rows < rows; index_rows++) {
			if (consealed_map[index_rows][index_cols] == '0')
				consealed_map[index_rows][index_cols] = SPACE;
		}
	}
}


//Determine the number of neighboring mines to a square
void Mines_In_Range(char consealed_map[ROWS][COLS], int rows, int cols) {
	for (int index_cols = 0; index_cols < cols; index_cols++) {
		for (int index_rows = 0; index_rows < rows; index_rows++) {
			if (!Mine_Checker(consealed_map[index_rows][index_cols])) {
				//NW
				if ((index_rows - 1 >= 0) && (index_cols - 1 >= 0) && Mine_Checker(consealed_map[index_rows - 1][index_cols - 1]))
					consealed_map[index_rows][index_cols]++;
				//N	
				if ((index_rows - 1 >= 0) && Mine_Checker(consealed_map[index_rows - 1][index_cols]))
					consealed_map[index_rows][index_cols]++;
				//NE
				if ((index_rows - 1 >= 0) && (index_cols + 1 < cols) && Mine_Checker(consealed_map[index_rows - 1][index_cols + 1]))
					consealed_map[index_rows][index_cols]++;
				//W
				if ((index_cols - 1 >= 0) && Mine_Checker(consealed_map[index_rows][index_cols - 1]))
					consealed_map[index_rows][index_cols]++;
				//E
				if ((index_cols + 1 < cols) && Mine_Checker(consealed_map[index_rows][index_cols + 1]))
					consealed_map[index_rows][index_cols]++;
				//SW
				if ((index_rows + 1 < rows) && (index_cols - 1 >= 0) && Mine_Checker(consealed_map[index_rows + 1][index_cols - 1]))
					consealed_map[index_rows][index_cols]++;
				//S
				if ((index_rows + 1 < rows) && Mine_Checker(consealed_map[index_rows + 1][index_cols]))
					consealed_map[index_rows][index_cols]++;
				//SE
				if ((index_rows + 1 < rows) && (index_cols + 1 < cols) && Mine_Checker(consealed_map[index_rows + 1][index_cols + 1]))
					consealed_map[index_rows][index_cols]++;
			}
			//printf("%3c", consealed_map[index_rows][index_cols]);
		}
	}
}

bool Mine_Checker(char consealed_square) {
	return (consealed_square == MINE);
}

//Calculates the last cell location and writes it to the 
void Last_Cell_Location(char consealed_map[ROWS][COLS], char game_map[ROWS][COLS], int last_cell[2], int row_size, int col_size) {
	int row_cntr = last_cell[0], col_cntr = last_cell[1];
	while (game_map[row_cntr][col_cntr] == consealed_map[row_cntr][col_cntr] && row_cntr < row_size) {
		col_cntr += 1;
		if (col_cntr == col_size) {
			col_cntr = 0;
			row_cntr += 1;
		}
	}
	last_cell[1] = col_cntr;
	last_cell[0] = row_cntr;
}

//Reveals the the chosen number of squares that does not contain a mine by order
void Map_revealer(char consealed_map[ROWS][COLS], char game_map[ROWS][COLS], int counter, int last_cell[2], int last_row, int last_col, int row_size, int col_size) {
	int row_cntr = last_row, col_cntr = last_col;
	while (row_cntr < col_size && counter>0) {
		for (col_cntr; col_cntr < row_size && counter>0; col_cntr++) {
			if (!Mine_Checker(consealed_map[row_cntr][col_cntr])) {
				game_map[row_cntr][col_cntr] = consealed_map[row_cntr][col_cntr];//updates the game map
				counter -= 1;
			}
		}
		if (col_cntr == col_size) {
			col_cntr = 0;
			row_cntr += 1;
		}
	}
	last_cell[1] = col_cntr;
	last_cell[0] = row_cntr;

}



//prints all the empty spaces
int Space_Printer(char consealed_map[ROWS][COLS], char game_map[ROWS][COLS], int row_input, int col_input, int row_size, int col_size) {
	int output = 0;
	if (!(row_input >= 0 && col_input >= 0 && row_input < row_size && col_input < col_size))
		return 0;
	if (game_map[row_input][col_input] == consealed_map[row_input][col_input])
		return 0;
	else if (!Space_Checker(consealed_map[row_input][col_input]) && game_map[row_input][col_input] != consealed_map[row_input][col_input])
		return 0;
	else {
		game_map[row_input][col_input] = consealed_map[row_input][col_input];
		output++;

		output += Space_Printer(consealed_map, game_map, row_input - 1, col_input, row_size, col_size);//N

		output += Space_Printer(consealed_map, game_map, row_input, col_input - 1, row_size, col_size);//W

		output += Space_Printer(consealed_map, game_map, row_input, col_input + 1, row_size, col_size);//E

		output += Space_Printer(consealed_map, game_map, row_input + 1, col_input, row_size, col_size);//S

		return output;
	}
}

bool Space_Checker(char square) {
	return(square == SPACE);
}

void Print_Headline() {
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("  __  __  _                                                           \n");
	printf(" |  \\/  |(_)                                                          \n");
	printf(" | \\  / | _  _ __    ___  ___ __      __ ___   ___  _ __    ___  _ __ \n");
	printf(" | |\\/| || || '_ \\  / _ \\/ __|\\ \\ /\\ / // _ \\ / _ \\| '_ \\  / _ \\| '__|\n");
	printf(" | |  | || || | | ||  __/\\__ \\ \\ V  V /|  __/|  __/| |_) ||  __/| |   \n");
	printf(" |_|  |_||_||_| |_| \\___||___/  \\_/\\_/  \\___| \\___|| .__/  \\___||_|   \n");
	printf("                                                   | |                \n");
	printf("                                                   |_|                \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

//Prints a headline "Game over"
void Print_Game_Over() {
	printf("   _____                                                  \n");
	printf("  / ____|                                                 \n");
	printf(" | |  __   __ _  _ __ ___    ___     ___ __   __ ___  _ __ \n");
	printf(" | | |_ | / _` || '_ ` _ \\  / _ \\   / _ \\\\ \\ / // _ \\| '__|\n");
	printf(" | |__| || (_| || | | | | ||  __/  | (_) |\\ V /|  __/| |   \n");
	printf("  \\_____| \\__,_||_| |_| |_| \\___|   \\___/  \\_/  \\___||_|   \n");
}

void Winner_Printer() {
	printf(" __     __ ____   _    _    __          __ _____  _   _    _   _   _ \n");
	printf(" \\ \\   / // __ \\ | |  | |   \\ \\        / /|_   _|| \\ | |  | | | | | |\n");
	printf("  \\ \\_/ /| |  | || |  | |    \\ \\  /\\  / /   | |  |  \\| |  | | | | | |\n");
	printf("   \\   / | |  | || |  | |     \\ \\/  \\/ /    | |  | . ` |  | | | | | |\n");
	printf("    | |  | |__| || |__| |      \\  /\\  /    _| |_ | |\\  |  |_| |_| |_|\n");
	printf("    |_|   \\____/  \\____/        \\/  \\/    |_____||_| \\_|  (_) (_) (_)\n\n");
}