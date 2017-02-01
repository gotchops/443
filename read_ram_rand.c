#include "utils.h"

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 3);

	FILE* fp_read = NULL;
    
	long int block_size = get_block_size(argv);
	int records_per_block = block_size / (long int) sizeof(Record);
	char* file_name = get_file_name(argv);
	long int x = get_x(argv);

	validate_mode_on_file(file_name, &fp_read, "rb");

	off_t size = get_file_size(file_name);
	validate_file_size(size);

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(size, sizeof(off_t));
	alloc_check(buffer);

	Result_Acc res;
	init_result_acc(&res);

	Temp_Acc temp;
	init_temp_acc(&temp);

	size_t read = fread(buffer, sizeof(off_t), size, fp_read);
	if (read != size) {
		/* Handle error */
	}

	srand(time(NULL));
	long int r;
	long int num_blocks_in_file = size / block_size;

	long int i;
	for (i=0; i<x; i++) {
		r = rand() % num_blocks_in_file;

		int j;
		for (j=0; j<records_per_block; j++) {
			Record record = buffer[r + j];
			int uid = record.uid1;
			build_result_acc(uid, &temp, &res);
		}
	}

	unsigned int max = res.max;
	float avg = calc_avg(&res);

	printf("Max: %u\nAvg: %.2f\n", max, avg);

	fclose(fp_read);
	free(buffer);

	return 0;
}