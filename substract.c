#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct _Lambda {
	int head;
	char *state;
	bool halt;
} Lambda;

#define LENGTH 48
unsigned char tape[LENGTH];

void print_result() {
	unsigned int result = 0;
	for (int i = 0; i < LENGTH; i++) {
		if (tape[i] == '0') {
			result += 1;
		}
	}
	printf("%d\n", result);
}

void init_tape(unsigned char *input_tape) {
	int len = strlen(input_tape);
	for (int i = 0; i < LENGTH; i++) {
		if (i < len) {
			tape[i] = input_tape[i];
		} else {
			tape[i] = 'B';
		}
	}
}

Lambda next(Lambda l) {
	if (strcmp(l.state, "q0") == 0 && tape[l.head] == '0') {
		tape[l.head] = 'B';
		l.head += 1;
		l.state = "q1";
	} else if (strcmp(l.state, "q1") == 0 && tape[l.head] == '0') {
		l.head += 1;
	} else if (strcmp(l.state, "q1") == 0 && tape[l.head] == '1') {
		l.state = "q2";
		l.head += 1;
	} else if (strcmp(l.state, "q2") == 0 && tape[l.head] == 'B') {
		l.state = "q4";
	} else if (strcmp(l.state, "q2") == 0 && tape[l.head] == '1') {
		l.head += 1;
	} else if (strcmp(l.state, "q2") == 0 && tape[l.head] == '0') {
		l.state = "q3";
		tape[l.head] = '1';
	} else if (strcmp(l.state, "q3") == 0 && tape[l.head] == '1') {
		l.head -= 1;
	} else if (strcmp(l.state, "q3") == 0 && tape[l.head] == '0') {
		l.head -= 1;
	} else if (strcmp(l.state, "q3") == 0 && tape[l.head] == 'B') {
		l.state = "q0";
		l.head += 1;
	} else if (strcmp(l.state, "q4") == 0) {
		l.state = "q5";
		l.head -= 1;
	} else if (strcmp(l.state, "q5") == 0 && tape[l.head] == '1') {
		tape[l.head] = 'B';
		l.head -= 1;
	} else if (strcmp(l.state, "q5") == 0 && tape[l.head] == '0') {
		l.head -= 1;
	} else if (strcmp(l.state, "q5") == 0 && tape[l.head] == 'B') {
		tape[l.head] = '0';
		l.halt = true;
		printf("%s\n", tape);
	}
	return l;
}

void substract_tm(unsigned char *input_tape) {
	init_tape(input_tape);
	char *q0 = "q0";
	Lambda l = {0, q0, false};
	while(!l.halt) {
		l = next(l);
	}
	printf("Input: %s = ", input_tape);
	print_result();
}

int main() {
	printf("Substract turing machine...\n");
	printf("This TM calculate m - n, if n < m\n");
	substract_tm("0010"); // 2 - 1
	substract_tm("000010"); // 4 - 1
	substract_tm("000000001000"); // 8 - 3
}

