#include "utils.h"

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 3);

	FILE* fp_read = NULL;

	long int block_size = get_block_size(argv);
	long int records_per_block = block_size / (long int) sizeof(Record);
	char* file_name = get_file_name(argv);
	long int x = get_x(argv);

	validate_mode_on_file(file_name, &fp_read, "rb");

	off_t size = get_file_size(file_name);
	validate_file_size(size);

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(records_per_block, sizeof(Record));
	alloc_check(buffer);

	Result_Acc res;
	init_result_acc(&res);

	Temp_Acc temp;
	init_temp_acc(&temp);

	srand(time(0));
	long int r;
	long int num_blocks_in_file = size / block_size;
	long int num_records_in_file = size / sizeof(Record);

	long int i;
	for (i=0; i<x; i++) {
		if (num_blocks_in_file != 0) {
			r = rand() % num_blocks_in_file;
			fseek(fp_read, r*block_size, SEEK_SET);
			build_result_by_block(buffer, records_per_block, fp_read, &res, &temp);
		} else {
			build_result_by_block(buffer, num_records_in_file, fp_read, &res, &temp);
		}
	}

	unsigned int max = res.max;
	float avg = calc_avg(&res);

	printf("Max: %u\nAvg: %.2f\n", max, avg);

	fclose(fp_read);
	free(buffer);

	return 0;
}