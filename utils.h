#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

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

long int get_x(char**);

int get_delim_index(char*);

void line_to_str_array(char*, int, char**, char*, char*);

void str_array_to_record(char**, Record*);

off_t get_file_size(char*);

void validate_file_size(off_t size);

void build_result_by_block(Record*, int, FILE*, Result_Acc*, Temp_Acc*);

void init_result_acc(Result_Acc*);

unsigned long calc_avg(Result_Acc*);

void init_temp_acc(Temp_Acc*);

void build_result_acc(int, Temp_Acc*, Result_Acc*);
