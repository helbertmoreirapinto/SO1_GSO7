#include <stdbool.h>

int main() {
	int range_start = 5000;
	int range_end   = 30000;
	bool prime_numb;

	for (int i = range_start; i < range_end; i++) {
		prime_numb = true;
		for (int j = 2; j < i; j++) {
			if (!(i % j)) {
				prime_numb = false;
				break;
			}
		}
	}
	return 0;
}
