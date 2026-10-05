#include <stdio.h>

#define ac_red "\x1b[31m"    // - rod is filled out
#define ac_green "\x1b[32m" // -  rod is filled in
#define ac_blue "\x1b[34m" // - rod is selected
#define ac_clear "\x1b[2J"

void  render(void);

int rows = 7;
int col = 7;
int game_grid[7][7] = {
	{'*' , '*' , '*' , 'n' , '*' , '*', '*'},
	{'*' , '*' , 'n' , 'n' , 'n' , '*' , '*'},
	{'*' , 'n' , 'n' , 'n' , 'n' , 'n' , '*'},
	{'*' , 'n' , 'n' , 'n' , 'n' , 'n' , '*'},
	{'*' , '*' , 'n' , 'n' , 'n' , '*' , '*'},
	{'*' , '*' , '*' , 'n' , '*' , '*' , '*'},

};

int main(){
	//render();

	for (int i = 0; i < rows ; i++) {   // Move this for render system (With ASCII escape codes
		for (int j = 0; j < col ; j++) {
			if (game_grid[i][j] == 'n') {
				printf("[%c]" , game_grid[i][j]);
			}
			else {
				printf("   ");
			}
		}
		printf("\n");
	}


	return 0;
}


void render(void){
	printf("\x1b[?25l");
	printf("\x1b[1;1H");
	printf(ac_clear);	

	for (int row = 0; row < 7; row += 1) {
		
		printf("\x1b[%d;5H" , row + 5);

		for (int column = 0;  column < 7; column += 1) {
			printf("# ");
		}

		printf("\n");

	}
	printf("\x1b[?25h");
}

