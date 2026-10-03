#include <stdio.h>
#include <termios.h>
#include <unistd.h>


// - user-data part
int user_data(char * username ,int game_difficult ,double user_radiation);
char username[50] = "none";
int game_difficult = 1;
double user_radiation = 0.0; 

 
int rods_interface();
int rods_control();

int main(){
	struct termios original_terminal_settings;
	tcgetattr(STDIN_FILENO, &original_terminal_settings);

	if (tcgetattr(STDIN_FILENO, &original_terminal_settings) == -1) {
			perror("Error getting terminal settings");
			return 1;
	
	}

	printf("User verification started... ");
	printf("Press any button to continue\n");
	
	while (getchar() != '\n');

	getchar();

	printf("Succes!\n");

	//user_data(username , game_difficult , user_radiation);

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
	// - here will be rods control
	printf("Please select rods to move (At least 4 rods by one time\n");

	return 0;
}

int rods_interface(){
	printf("Current space - Rods interface\n");

	return 0;
}

