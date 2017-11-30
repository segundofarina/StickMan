#include <stdio.h>

void moveAndJump();
int isPar();
void say(char * str);
void checkEndOfScreen();

int main() {

	int repetitions = 0;
	say("hola"!);
	while(repetitions < 15) {
		checkEndOfScreen();

		if(isPar()) {
			moveAndJump();
		} else {
			//man->move;
		}
		repetitions++;
	}

	say("chau!");

	return 0;
}


void moveAndJump() {
	//man->move + man->jump;
}

int isPar() {
	//man.position = getManPosition()
	if(getManPosition()%2 == 0) {
		return 1;
	}
	return 0;
}

void say(char * str) {
	//man->yield str;
}

void checkEndOfScreen() {
	if(getManPosition() == eosR) {
		setManDirection(LEFT);
	} else if(getManPosition() == eosL) {
		setManDirection(RIGHT);
	}
}
