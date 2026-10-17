#include <stdio.h>
#include <unistd.h>

#include "rod_control.h"

#define ac_red "\x1b[31m" // - rod is filled out
#define ac_green "\x1b[32m" // - rod is filled in
#define ac_blue "\x1b[34m" // - rod is selected 
#define ac_clear "\x1b[0m" // - reset color

// Functions prototypes
void rods_render(double rod_position , int mode_select);
int rods_control(void);
int mode_selection_window(void);

int rows = 5;
int col = 4;

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

    int cur_row = 0;
    int cur_col = 0;
    int fill_rod_array = 0;
    
    while (rodctrl_is_running) {
        if (read(STDIN_FILENO, &key, 1) == 1) {
            if (key == 27) {
                char seq[4];
                read(STDIN_FILENO, &seq[0] , 1);
                read(STDIN_FILENO, &seq[1] , 1);
                // read(STDIN_FILENO, &seq[2] , 1);
                //read(STDIN_FILENO, &seq[3] , 1);
               
                if (seq[1] == 'A') {
                   if (cur_row > 0) { cur_row++; }
                   else if (cur_row <= 0) { cur_row = 0; } 
                }
                else if (seq[1] == 'B') {
                    if (cur_row < 5) { cur_row--; }
                    else if (cur_row >= 5) { cur_row = 5; } 
                }
                else if (seq[1] == 'C') {
                    if (cur_col < 4) { cur_col++; }
                    else if (cur_row >= 4) { cur_col = 4; }
                }
                else if (seq[1] == 'D') {
                    if (cur_col > 0) { cur_col--;}
                    else if (cur_row <= 0) { cur_col = 0;}
                }
                else if (seq[1] == '') { // - Here must be "C" ANSI code
                    choosen_rods[fill_rod_array][0] = cur_row;
                    choosen_rods[fill_rod_array][1] = cur_col;
                    fill_rod_array++;
                }

        }
    }

    if ((sizeof(choosen_rods) / sizeof(choosen_rods[0])) == 3) {
        return 0;
    }
    else if ((sizeof(choosen_rods) / sizeof(choosen_rods[0])) == 2) {
        choosen_rods[3][1] = 0;
        choosen_rods[3][2] = 0;
        return 0;
    }
    else if ((sizeof(choosen_rods) / sizeof(choosen_rods[0])) == 1) {
        choosen_rods[3][1] = 0;
        choosen_rods[3][2] = 0;
        choosen_rods[2][1] = 0;
        choosen_rods[2][2] = 0;
        return 0;
    }
    else {
        printf("You haven't choosen any rod!");
        return 1;
    }

}

int mode_select; // 0 - choosing rods ; 1 - moving choosen rods ;

void rods_render(double rod_position , int mode_select) {
    printf("\x1b[?25l");
    printf("\x1b[?1:1H");
    
    if (mode_select == 1) {
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
    else if (mode_select == 0) {
        for (int i = 0; i < rows ; i++) {
            for (int j = 0; j < col; j++) {
               // if (
            }
        }
    }
}

int rods_control(void) {
    rodctrl_is_running = 1;

    printf("Please select rods to move (At least 3 rods by one time\n");
   /* while (rodctrl_is_running) {
        if (read(STDIN_FILENO, &key, 1) == 1) {
            if (key == 27) {
                char seq[3];
                read(STDIN_FILENO, &seq[0] , 1);
                read(STDIN_FILENO, &seq[1] , 1);
            }
        }
    } */  // <- Move this to Choose_rods ( and then call function here to choose rods );
    return 0;
}

int mode_selection_window(void) {
    
    const char  *modes[2] = {"Rods-choosing" , "Rods-moving"};
    int num_sectors = sizeof(modes) / sizeof(modes[0]);
    
    printf("Here is list of aviable modes: \n");

    for (int i = 0; i < num_sectors ; i++) {
        printf("%s" , modes[i]);
    }     
   
    printf("Please select mode: ");
    
    char s;

    while (1) {
        if (read(STDIN_FILENO , &s , 1) ==  1) {
            if (s == 'q') {
                return 0;
            }
            else if (s == '1') {
                mode_select = 0; // Rods-choosing
                return 1; 
            }
            else if (s == '2') {
                mode_select = 1; // Rods-moving
                return 1;
        } 
    }
        usleep(50000);
}
