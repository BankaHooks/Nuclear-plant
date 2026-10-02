#include <stdio.h>

// - user-data part
int user_date();
/* char __username = "none";
int __game_difficult = 1;
double _user_radiation = 0.0; */
 

int main(){
	printf("User verification started... ");
	printf("Press any button to continue\n");
	
	while (getchar != '\n');

	getchar();

	printf("Succes!\n");

	user_data(__username , __game_difficult , _user_radiation);

	return 0;
}

int user_data(__username , __game_difficult , _user_radiation){
	printf("Enter your name: ");
	__username = scanf("%c\n" , &__username);
	printf("Enter game difficult: ");
	__game_difficult = scanf("%c\n" , &__game_difficult);
	printf("Registration succesfully completed...\n");
	
	printf("Your data: ");
	printf("Name: %c" , __username , " Game difficult: %c" , __game_difficult , "Your radiation level: %d" , _user_radiation , '\n');

	return 0;
}

int rods_control(){
	// - here will be rods control
	return 0;
}

