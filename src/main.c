#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <stdbool.h>

#include "common.h"
#include "term.h"
#include "input.h"
#include "color.h"
#include "scene/parse.h"

/*
 * VARIABLES
 */

bool running = true;
const bool isDebug = true;

/*
 * FUNCTIONS
 */

static inline void clear(void) {
	printf(ESC"[H"ESC"[J");
}

void *genericHandler(char c) {
	printf("%c", c);
	return NULL;
}
void *quit(char c) {
	running = false;
	return NULL;
}
void *move(char c) {
	printf("Moved: %c", c);

	return NULL;
}

char inputGetter(void *arg) {
	char ret;
	read(STDIN_FILENO, &ret, 1);
	return ret;
}

int main(int argc, char *argv[]) {
//	termiosInit();
	//clear();
	InputHandler handlers[2] = {
		(InputHandler) {
			.key = "wasd",
			.function = move,
			.attributes = {	.bits = 0 },
		},
		(InputHandler) {
			.key = "q",
			.function = quit,
			.attributes = {.bits = 0}
		}
	};
	printf(RGB_BG(255, 0, 0)"hi"CRESET"\n");
	Input_t inp = inputInit(
		2,
		&*handlers,
		genericHandler
	);

	int i = 0;
	while(running) {
		struct Scene b = sceneParse("foo.dat");
		clear();
	//	inputLoop(inp, inputGetter, NULL, NULL);
		i++;
		//if(i == 100)
			running = false;
		if((i % 2) == 0)
			sceneInterpret(&b);
//		else
//			sceneInterpret(&a);

		sceneDestroy(&b);
	}
	struct Scene a = sceneParse("bar.dat");
	sceneInterpret(&a);
	sceneDestroy(&a);

	inputDestroy(&inp);
	return 0;
}

