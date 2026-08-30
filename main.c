#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "words.h"

int32_t search(int32_t l, int32_t r, char *target) {
	int32_t cmp_val;
	int32_t m;

	while(l <= r) {
		m = l + (r - l) / 2;
		cmp_val = strcmp(target, words[m]);

		if (cmp_val == 0) {
			return m;
		} else if(cmp_val > 0) {
			l = m + 1;
		} else {
			r = m - 1;
		}
	}
	return -1;
}

int main(int argc, char **argv) {

	srand(time(NULL));
	char *buffer = calloc(WORD_SIZE + 1, sizeof(char));
	
	int32_t
		l = 0,
		r = WORDS_SIZE - 1,
		word_idx = ( rand() % (WORDS_SIZE - 2) ) + 1,
		usr_idx = -1;
	// word_idx needs to exclude the intial "AAAAA"
	// and the final "ZZZZZ" placeholders

	double
		dist_top = 0,
		dist_bot = 0;

	printf("%d : %s\n", word_idx, words[word_idx]);
	do {
		system("cls");
		printf("TOP : %s | %2.2lf\n", words[l], dist_top);
		printf("BOT : %s | %2.2lf\n", words[r], dist_bot);
		printf("Enter your guess : ");
		scanf("%5s", buffer);

		usr_idx = search(l, r, buffer);
		if(usr_idx == -1) {
			printf("%s is not in the valid range!\n", buffer);
			continue;
		} else if(usr_idx == l || usr_idx == r) {
			printf("%s is not in the valid range!\n", buffer);
			continue;
		} else if(usr_idx < word_idx) {
			l = usr_idx;
		} else {
			r = usr_idx;
		}

		dist_top = 100.0 * (word_idx - l) / (r - l);
		dist_bot = 100.0 * (r - word_idx) / (r - l);
		
	} while(usr_idx != word_idx);

	printf("The word was %s!\n", words[word_idx]);

	free(buffer);
	return 0;
}
