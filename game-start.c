#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "rod_control.h" 

#define ac_red "\x1b[31m" // - rod is filled out
#define ac_green "\x1b[32m" // - rod is filled in 
#define ac_blue "\x1b[34m" // - rod is selected (not sure for 0.1v)

// - Preparation for game part
struct termios original_terminal_settings;
void restore_terminal(void);
void game_end(void);

// - user-data part
int user_data();
char username[50] = "none";
int game_difficult = 1;
double user_radiation = 0.0;

int game_is_running = 1; //  1 - true ; 0 - false
int CURRENT_STATE = 0; // 0 - Menu ; 1 - Rods; 2 - Turbine; 3 - Daerator; 4 - ECCS; 5 - Breakers; 6 - Pumps; 7 - Phone;

// - Rods control part
int rods_interface();
int rods_control();
double rod_position = 100.0;
char key; // Holding current key press;
int rodctrl_is_running = 1; // 1 - true ; 0 - false

int sector_choose(void);

int main(){
	tcgetattr(STDIN_FILENO, &original_terminal_settings);

	if (tcgetattr(STDIN_FILENO, &original_terminal_settings) == -1) {
		perror("Error getting terminal settings");
		restore_terminal(); 
		return 1;
 	
	}

	struct termios raw_terminal_settings = original_terminal_settings;
	raw_terminal_settings.c_lflag &= ~ICANON;
	raw_terminal_settings.c_lflag &= ~ECHO;  //Turning off "Waiting for ENTER and showing what we type"
	raw_terminal_settings.c_cc[VMIN] = 0;
	raw_terminal_settings.c_cc[VTIME] = 0;

	tcsetattr(STDIN_FILENO, TCSANOW, &raw_terminal_settings);

	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw_terminal_settings) == -1) {
		perror("Error setting raw mode");
		restore_terminal();
		return 1;
	}

	char dummy_c;
	printf("User verification started... ");
	printf("Press any button to continue\n");
	read(STDIN_FILENO, &dummy_c, 1);
	printf("Succes!\n");
	
	tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
	user_data();
	tcsetattr(STDIN_FILENO, TCSANOW, &raw_terminal_settings);

	printf("Settings saved successfully!\n");
	    
    //Preparation stage success -> starting game stage
    while(game_is_running) {
        if (CURRENT_STATE == 0) {
            sector_choose();
        }
        else if (CURRENT_STATE == 1) {
            rods_control();
        }
    }

	restore_terminal();
	return 0;
}

int user_data(void){
	printf("Enter your name: ");
	scanf("%s" , username);
	printf("Enter game difficult: ");
	scanf("%d" , &game_difficult);
	printf("Registration succesfully completed...\n");
	
	printf("Your data: ");
	printf("Name: %s" , username , " Game difficult: %d" , game_difficult , "Your radiation level: %f\n" , user_radiation);
	
	restore_terminal();
	return 0;
}

int sector_choose(void) {
    printf("\x1b[2J");
    printf("\x1b[1;1H");

    const char *sectors[8] = {"Rods-control" , "Turbine-control" , "Daerator-control" , "ECCS-control" , "Breakers-control" , "Pumps-control" , "Phone" , "End_shift"};
    int num_sectors = sizeof(sectors) / sizeof(sectors[0]);
    
    printf("\n Here is a list of aviable sectors: \n");
    for (int i = 0; i < num_sectors; i++) {
        printf("%d |  %s\n", i+1 , sectors[i]);
    }
    printf("Select one, please: ");
    char s;
    
    while (1) {
        if (read(STDIN_FILENO , &s , 1) == 1) {
            if (s == 'q') {
                return 0;
            }
            else if (s == '1') { 
                CURRENT_STATE = 1; 
                return 1;
            }
            else if (s == '2') { 
                printf("No aviable in current version"); 
                return 1;
            }
            else if (s == '3') { 
                printf("No aviable in current version"); 
                return 1;
            }
            else if (s == '4') { 
                printf("No aviable in current version"); 
                return 1;
            }
            else if (s == '5') { 
                printf("No aviable in current version"); 
                return 1;
            }
            else if (s == '6') { 
                printf("No aviable in current version"); 
                return 1;
            }
            else if (s == '7') { 
                printf("No aviable in current version"); 
                return 1;
            }
            else if (s == '8') {
                game_end(); // Then add a results of current session;    
            }
        }
        
        usleep(50000);
    }
}

int selected_row , selected_col;

int rods_control(void){
    rodctrl_is_running = 1;
	printf("Please select rods to move (At least 4 rods by one time\n");
	while (rodctrl_is_running) {
        render(rod_position);
		if (read(STDIN_FILENO, &key, 1) == 1) {
			if (key == 27) {
				char seq[2];
				read(STDIN_FILENO, &seq[0], 1);
				read(STDIN_FILENO, &seq[1], 1);

				if (seq[1] == 'A') { rod_position += 0.08; }
				
				if (seq[1] == 'B') { rod_position -= 0.08; }
				
				if (seq[1] == 'D') { 
                    rodctrl_is_running = 0;
                    CURRENT_STATE = 0;
                }
			
				
				if (rod_position > 100) {  rod_position = 100; }
				if (rod_position < 0) { rod_position = 0; }

				printf("\rRods: %.2f%%  " , rod_position);
				fflush(stdout); // Force the screen to update immediately */ 

        // - Here should be rods choosing. And only then we can move them;

			}
		}

		// Reactor similations will be here

		// A small sleep to prevent CPU meltdown
		usleep(50000); // sleep for 50 milliseconds;
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
	printf("\nAverage rods positions : %.1f%% " , rod_position , '\n');
	
	restore_terminal();
	return 0;
}

void game_end(void) {
    restore_terminal();
    printf("\x1b[2J");
    printf("\x1b[1;1H");
    printf("\x1b[?25h");
    printf("Thanks for playing");
}

void restore_terminal(void) {
	tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
}

