#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record {
	int uid1;
	int uid2;
} Record;

typedef struct result_acc {
	unsigned int max;
	unsigned long num_friends;
	unsigned long total_uids;
} Result_Acc;

typedef struct temp_acc {
	int uid;
	unsigned long num_friends;
} Temp_Acc;

void validate_args(int, char**);

void malloc_check(void*);


