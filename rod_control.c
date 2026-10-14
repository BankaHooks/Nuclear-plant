#include <stdio.h>
#include <unistd.h>

#include "rod_control.h"

#define ac_red "\x1b[31m" // - rod is filled out
#define ac_green "\x1b[32m" // - rod is filled in
#define ac_blue "\x1b[34m" // - rod is selected 
#define ac_clear "\x1b[0m" // - reset color

// Functions prototypes
void rods_render(double rod_position);
int rods_control(void);

int rows = 5;
int col = 4;
int game_grid[5][4] = {
    {'*' , 'n' , 'n' , '*'},
    {'n' , 'n' , 'n' , 'n'},
    {'n' , 'n' , 'n' , 'n'},
    {'n' , 'n' , 'n' , 'n'},
    {'*' , 'n' , 'n' , '*'}
};



double rods_data[5][4] = {
    {-1.0 , 100.00 , 100.00 , -1.0},
  {100.00 , 100.00 , 100.00 , 100.00},
  {100.00 , 100.00 , 100.00 , 100.00},
  {100.00 , 100.00 , 100.00 , 100.00},
    {-1.0 , 100.00 , 100.00 , -1.0}
};

static char key; // Holding current key press;
static int rodctrl_is_running = 1;
int rods_choose(void);

static int choosen_rods[3][2] = {
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

void rods_render(double rod_position) {
    printf("\x1b[?25l");
    printf("\x1b[?1:1H");

    for (int i = 0; i < rows ; i++) {
        for (int j = 0; j < col; j++) {
            if (rods_data[i][j] < 97.00 && rods_data[i][j] > 3) {
                printf(ac_clear  "[%.2f]" , rods_data[i][j]);
            }
            else if (rods_data[i][j] == -1) {
                printf("   ");
            }
            else if (rods_data[i][j] < 3.00) {
                printf(ac_red "[%.2f]" ac_clear , rods_data[i][j]);
            }
            else if (rods_data[i][j] > 97.00) {
                printf(ac_green "[%.2f]" ac_clear , rods_data[i][j]);
            }             
        }
    }
}

int rods_control(void) {
    rodctrl_is_running = 1;
    printf("Please select rods to move (At least 3 rods by one time\n");
    while (rodctrl_is_running) {
        if (read(STDIN_FILENO, &key, 1) == 1) {
            if (key == 27) {
                char seq[3];
                read(STDIN_FILENO, &seq[0] , 1);
                read(STDIN_FILENO, &seq[1] , 1);
            }
        }
    }  // <- Move this to Choose_rods ( and then call function here to choose rods );
    return 0;
}

