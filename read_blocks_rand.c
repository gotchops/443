#include "utils.h"

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 3);

	FILE* fp_read = NULL;

	long int block_size = get_block_size(argv);
	int records_per_block = block_size / (long int) sizeof(Record);
	char* file_name = get_file_name(argv);
	long int x = get_x(argv);

	validate_mode_on_file(file_name, fp_read, "rb");

	off_t size = get_file_size(file_name);
	validate_file_size(size);

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(records_per_block, sizeof(Record));
	alloc_check(buffer);

	Result_Acc res;
	init_result_acc(&res);

	Temp_Acc temp;
	init_temp_acc(&temp);

	srand(time(NULL));
	long int r;
	long int num_blocks_in_file = size / block_size;

	long int i;
	for (i=0; i<x; i++) {
		r = rand() % num_blocks_in_file;
		fseek(fp_read, r, SEEK_SET);
		build_result_by_block(buffer, records_per_block, fp_read, &res, &temp);
	}

	unsigned int max = res.max;
	unsigned long avg = calc_avg(&res);

	printf("Max: %u\nAvg: %lu", max, avg);

	fclose(fp_read);
	free(buffer);

	return 0;
}