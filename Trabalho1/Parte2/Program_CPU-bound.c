#include <stdbool.h>

int main() {
	int range_start = 5000;
	int range_end   = 30000;
	int prime_count = 0;
	bool prime_numb;

	for (int i = range_start; i < range_end; i++) {
		prime_numb = true;
		for (int j = 2; j < i; j++) {
			if (!(i % j)) {
				prime_numb = false;
				break;
			}
		}
		if(prime_numb) prime_count++;
	}
	printf("Prime count = %d", prime_count);
	return 0;
}
