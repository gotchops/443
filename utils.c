#include "utils.h"

void validate_arg_num(int expected, int given)
{
	if (expected != given) 
	{
		fprintf(
			stderr,
			"This program expects %d arguments.\n",
			expected
		);
		exit(-1);
	}
}

void validate_file_path(char* fpath)
{
	if (access(fpath, 0) != 0) 
	{
        	fprintf(
			stderr,
			"The file path is invalid.\n"
		);
		exit(-1);
	}
}

bool is_valid_block_size(long int block_size_in_bytes) {
	if (block_size_in_bytes % sizeof(Record) == 0) {
		return true;
	}
	return false;
}

void validate_block_size(char* bsize_str)
{
	long int bsize = atol(bsize_str);
	if (bsize == 0 || !is_valid_block_size(bsize))
	{
		fprintf(
			stderr,
			"Please provide a valid block size.\n"
		);
		exit(-1);
	}
}

void validate_args(int num_args, char** argv, int expected)
{
	validate_arg_num(expected, num_args);
	validate_file_path(argv[1]);
	if (expected > 1) {
		validate_block_size(argv[2]);
	}
}

void alloc_check(void* ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "Malloc error.\n");
		exit(-1);
	}
}

void validate_mode_on_file(char* file_name, FILE* fp, char* mode) {
	char* mode_str = NULL;
	if (strcmp(mode, "r") == 0 || strcmp(mode, "rb") == 0) {
		mode_str = "reading";
	} else {
		mode_str = "writing";
	}

	if (!(fp = fopen(file_name, mode))) {
		fprintf(
			stderr,
			"Could not open file \"%s\" for %s.\n",
			file_name,
			mode_str
		);
		exit(-1);
	}
}

char* get_file_name(char** argv) {
	return argv[1];
}

long int get_block_size(char** argv) {
	return atol(argv[2]);
}

int get_delim_index(char* line) {
	int i = 0;
	int len = strlen(line);
	for (i = 0; i < len; i++) {
		if (line[i] == ',') {
			return i;
		}
	}
	return -1;
}

void line_to_str_array(
		char* line,
		int delim_index,
		char** strings,
		char* str1,
		char* str2
	) {
	strncpy(str1, line, delim_index);
	strcpy(str2, &line[delim_index + 1]);

	strings[0] = str1;
	strings[1] = str2;
}

void str_array_to_record(char** str_array, Record* record) {
	int uid1 = atoi(str_array[0]);
	int uid2 = atoi(str_array[1]);

	if (uid1 == 0 || uid2 == 0) {
		fprintf(stderr, "Error converting string array to record.\n");
		exit(-1);
	}

	record->uid1 = uid1;
	record->uid2 = uid2;
}
