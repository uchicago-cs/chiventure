#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* name;
void wellMet();
void privacyVio();
void homeExpl();

/* 
 * Three functions to print given string in gold, yellow, or red respectively
 */

void pGld(char* str){
	printf("\033[0;33m");
	printf("%s", str);
	printf("\033[0m");
	return;
}

void pYel(char* str){
	printf("\033[1;33m");
	printf("%s", str);
	printf("\033[0m");
	return;
}

void pRed(char* str){
	printf("\033[0;31m");
	printf("%s", str);
	printf("\033[0m");
	return;
}

/*
 * Three functions corresponding to the dialog-end nodes
 */

void leave(){
	printf("As soon as your eyes glance to the doorway, the man's hands are at your back ushering you away.  The door snaps shut and you hear the distinct click of a lock turning.\n\n\nCongrats on finishing the chiventure dialog showcase!\n");
	pYel("Press ENTER to exit.\n");
	getchar();
	exit(0);
}

void fightReg(){
	pRed("As his arm flashes behind his back, the robber raises a knife to you.\n\n\n");
	printf("Congrats on finishing the chiventure dialog showcase!\n");
	pYel("Press ENTER to exit.\n");
	getchar();
	exit(0);
}

void fightFlwr(){
	pRed("The last thing you heard before it all went dark was 'NOO MY PRESSED FLOWER COLLECTION'\n\n\n");
	printf("Congrats on finishing the chiventure dialog showcase!\n");
	pYel("Press ENTER to exit.\n");
	getchar();
	exit(0);
}

void choiceRoot(char* str){
	str = strtok(str, "\n");
	if((strcmp(str, "greet shabby man") == 0) ||
	   (strcmp(str, "talk to shabby man") == 0)){
		printf("\n'Hey, I'm %s from Chiventure.'\n\n", name);
		wellMet();
	}else if(strcmp(str, "leave") == 0){
		printf("\n'Woah wait, this isn't my house!'\n\n");
		leave();
	}else if(strcmp(str, "attack shabby man") == 0){
		printf("\nNot being one for words, you tackle the man down.\n\n");
		fightReg();
	}else{
		printf("\nBefore you can even raise your hand or open your mouth, the shabby man snaps at you.\n\n");
		privacyVio();
	}
	return;
}

/*
 * Four choice functions, one for the start and three for dialog options
 */

void choiceMet(char* str){
	str = strtok(str, "\n");
	if(strcmp(str, "my house") == 0){
		printf("\n'Shoot, from the looks of it I'd thought it was abandoned.'\n\n");
		homeExpl();
	}else if(strcmp(str, "come and go") == 0){
		printf("\n'I'm not trying to take your home, I just thought it would be a place to rest in some shade for a bit.'\n\n");
		homeExpl();
	}else{
		pGld("\nWhatcha sayin?? Talk about what I'm talking about dang it!\n");
		printf("> Talk about: ");
		char* c2 = malloc(30 * sizeof(char));
		fgets(c2, 30, stdin);
		choiceMet(c2);
	}
	return;
}

void choiceVio(char* str){
	str = strtok(str, "\n");
	if(strcmp(str, "who you are") == 0){
		printf("\n'Hey, I'm %s from Chiventure.'\n\n", name);
		wellMet();
	}else if(strcmp(str, "the owner") == 0){
		printf("\n'The owner? With the state of this place, I'd have pegged you for more of a burglar, heh.'\n\n");
		homeExpl();
	}else if(strcmp(str, "poke around") == 0){
		printf("\nUnperturbed by the smelly squatter, you continue rifling for valuables in the piles. As you hum patronizingly, angry footsteps quickly approach your back.\n\n");
		fightFlwr();
	}else{
		pGld("\nWhatcha sayin?? Talk about what I'm talking about dang it!\n");
		printf("> Talk about: ");
		char* c2 = malloc(30 * sizeof(char));
		fgets(c2, 30, stdin);
		choiceVio(c2);
	}
	return;
}

void choiceExpl(char* str){
	str = strtok(str, "\n");
	if(strcmp(str, "door's unlocked") == 0){
		printf("\nYou walk over and pop a squat on the couch. 'You know what they say, open home, open heart!'\n\n");
		fightReg();
	}else if(strcmp(str, "bit messy") == 0){
		printf("\n'Really doesn't smell too good either. In fact, the place is looking a bit ransacked--'\n\n");
		fightReg();
	}else if(strcmp(str, "force") == 0){
		printf("\n'Try it, shabster'\n\n");
		fightReg();
	}else if(strcmp(str, "leave") == 0){
		printf("\n\n");
		leave();
	}else{
		pGld("\nWhatcha sayin?? Talk about what I'm talking about dang it!\n");
		printf("> Talk about: ");
		char* c2 = malloc(30 * sizeof(char));
		fgets(c2, 30, stdin);
		choiceExpl(c2);
	}
	return;
}

/*
 * Three functions representing the NPC's statements
 */

void wellMet(){
	pGld("Mhm fine, nice to meet you ");
	pGld(name);
	pGld(", now please turn around and get outta ");
	pYel("my house");
	pGld(".  You can't ");
	pYel("come and go");
	pGld(" as you wish.\n\n");
	printf("> Talk about: ");
	char* c2 = malloc(30 * sizeof(char));
	fgets(c2, 30, stdin);
	choiceMet(c2);
}

void privacyVio(){
	pGld("Woah, hey, y-you can't just walk in here and ");
	pYel("poke around");
	pGld(" the place without consulting ");
	pYel("the owner");
	pGld("!!  Shouldn't I at least know ");
	pYel("who you are");
	pGld("?!\n\n");
	printf("> Talk about: ");
	char* c3 = malloc(30 * sizeof(char));
	fgets(c3, 30, stdin);
	choiceVio(c3);
}

void homeExpl(){
	pGld("Yes, well, just because the ");
	pYel("door's unlocked");
	pGld(" and I'm a ");
	pYel("bit messy");
	pGld(" don't make it public property. Now take off and ");
	pYel("leave");
	pGld(", or else I'm gonna ");
	pYel("force");
	pGld(" you to.\n\n");
	printf("> Talk about: ");
	char* c4 = malloc(30 * sizeof(char));
	fgets(c4, 30, stdin);
	choiceExpl(c4);
}

/*
 * Takes in a name for your character and introduces the scenario
 */
int main(){
	system("clear");
	pRed("\nWelcome to Chiventure's 'Dialog Prototype' Showcase!\n\n\n");
	pYel("What's your name?");
	printf("\n> ");
	name = malloc(30 * sizeof(char));
	name = strtok(fgets(name, 30, stdin), "\n");
	printf("\n\nAs the door creaks open, a strong musty scent smacks you in the face, filled with tones of mildew and copper.  You step into a disheveled room which, while bare in some areas, seems to have plenty of valuables stacked in others.  You can see an antique clock and a faberge egg, just for starters.  A shabby man quickly rounds the corner into the room, alarmed by the unexpected guest.  He looks upset with you.\n\n Hint-- try to 'talk to' or 'greet' shabby man (that's why you're here after all). Or else, I suppose you could just leave, or 'attack' shabby man instead.\n\n> ");
	char* c1 = malloc(30 * sizeof(char));
	fgets(c1, 30, stdin);
	choiceRoot(c1);
	return 0;
}
