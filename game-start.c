#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// - Preparation for game part
struct termios original_terminal_settings;

// - user-data part
int user_data(char * username ,int game_difficult ,double user_radiation);
char username[50] = "none";
int game_difficult = 1;
double user_radiation = 0.0;
/* int game_is_running = 1; //  1 - true ; 0 - false */

// - Rods control part
int rods_interface();
int rods_control();
double rod_position = 100.0;
char key; // Holding current key press;
int rodctrl_is_running = 1; // 1 - true ; 0 - false

int main(){
	tcgetattr(STDIN_FILENO, &original _terminal_settings);

	if (tcgetattr(STDIN_FILENO, &original_terminal_settings) == -1) {
		perror("Error getting terminal settings");
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
		return 1;
	}
	
	char dummy_c;
	printf("User verification started... ");
	printf("Press any button to continue\n");
	read(STDIN_FILENO, &dummy_c, 1);
	printf("Succes!\n");
	
	tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
	user_data(username , game_difficult , user_radiation);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw_terminal_settings);

	printf("Settings saved successfully!\n");

	return 0;
}

int user_data(char * username ,int game_difficult ,double user_radiation){
	printf("Enter your name: ");
	scanf("%s" , username);
	printf("Enter game difficult: ");
	scanf("%d" , &game_difficult);
	printf("Registration succesfully completed...\n");
	
	printf("Your data: ");
	printf("Name: %s" , username , " Game difficult: %d" , game_difficult , "Your radiation level: %f" , user_radiation , '\n');

	return 0;
}

int rods_control(){
	while (rodctrl_is_running) {
		printf("Please select rods to move (At least 4 rods by one time\n");
		if (read(STDIN_FILENO, &key, 1) == 1) {
			// We will handle the arrow keys here
			if (key == 27) {
				char seq[2];
				read(STDIN_FILENO, &seq[0], 1);
				read(STDIN_FILENO, &seq[1], 1);

				if (seq[1] == 'A') { rod_position += 2.15; }
				
				if (seq[1] == 'B') { rod_position -= 2.15; }
				
				if (seq[1] == 'D') { rodctrl_is_running = 0; }
			
				
				if (rod_position > 100) {  rod_position = 100; }
				if (rod_position < 0) { rod_position = 0; }

				printf("\rRods: %.1f%%  " , rod_position);
				fflush(stdout); // Force the screen to update immediately 

			}
		}

		// Reactor similations will be here

		// A small sleep to prevent CPU meltdown
		usleep(50000); // sleep for 50 milliseconds;
	}

	tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
	printf("\nTerminal restored. Test over.\n");

	return 0;
}

int rods_interface(){
	printf("Current space - Rods interface\n");

	return 0;
}

