#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_PER_LINE 17

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

void validate_args(int, char**, int expected);

void alloc_check(void*);

void validate_mode_on_file(char*, FILE*, char*);

char* get_file_name(char**);

long int get_block_size(char**);

int get_delim_index(char*);

void line_to_str_array(char*, int, char**, char*, char*);

void str_array_to_record(char**, Record*);
