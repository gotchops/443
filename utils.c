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

void validate_block_size(char* bsize_str)
{
	int bsize = atoi(bsize_str);
	if (bsize == 0)
	{
		fprintf(
			stderr,
			"Please provide a valid block size.\n"
		);
		exit(-1);
	}
}

void validate_args(int num_args, char** argv)
{
	int expected = 2;

	validate_arg_num(expected, num_args);
	validate_file_path(argv[1]);
	validate_block_size(argv[2]);
}

void malloc_check(void* ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "Malloc error.\n");
		exit(-1);
	}
}