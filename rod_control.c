#include <stdio.h>

#include "rod_control.h"

#define ac_red "\x1b[31m" // - rod is filled out
#define ac_green "\x1b[32m" // - rod is filled in
#define ac_blue "\x1b[34m" // - rod is selected 

// Functions prototypes
void render(double rod_position);
int rods_control();

int rows = 5;
int col = 4;
int game_grid[5][4] = {
    {'*' , 'n' , 'n' , '*'},
    {'n' , 'n' , 'n' , 'n'},
    {'n' , 'n' , 'n' , 'n'},
    {'n' , 'n' , 'n' , 'n'},
    {'*' , 'n' , 'n' , '*'}
};



int rods_data[5][4] = {
    {0 , 100 , 100 , 0},
  {100 , 100 , 100 , 100},
  {100 , 100 , 100 , 100},
  {100 , 100 , 100 , 100},
    {0 , 100 , 100 , 0}
};

char key; // Holding current key press;
int rodctrl_is_running = 1;
int rods_choose(void);

int choosen_rods[3][2] = {
    {0 , 0},
    {0 , 0},
    {0 , 0}
};

int restart_choosen_rods(int choosen_rods[3][2]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            choosen_rods[i][j] = 0;
        }
    }

    return 0;
}

int rods_choose(void) {
    restart_choosen_rods(choosen_rods);

    
    if ((sizeof(choosen_rods) / sizeof(choosen_rods[0])) == 3) {
        return 1;
    }
    else if ((sizeof(choosen_rods) / sizeof(choosen_rods[0])) == 2) {
        choosen_rods[3][1] = 0;
        choosen_rods[3][2] = 0;
    }
    else if ((sizeof(choosen_rods) / sizeof(choosen_rods[0])) == 1) {
        choosen_rods[3][1] = 0;
        choosen_rods[3][2] = 0;
        choosen_rods[2][1] = 0;
        choosen_rods[2][2] = 0;
    }
    else {
        printf("You haven't choosen any rod!");
    }
}


