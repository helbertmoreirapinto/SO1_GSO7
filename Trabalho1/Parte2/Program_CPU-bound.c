#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
	FILE* input = fopen("input.in", "r");
	if (!input) {
		input = stdin;
	}

	int range_start, range_end;
	bool prime_numb;

	fscanf(input, "%d %d", &range_start, &range_end);

	for (int i = range_start; i < range_end; i++) {
		prime_numb = true;
		for (int j = 2; j < i; j++) {
			if (!(i % j)) {
				prime_numb = false;
				break;
			}
		}

		if (prime_numb)
			printf("%d\n", i);
	}
	return EXIT_SUCCESS;
}
