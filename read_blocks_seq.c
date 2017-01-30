#include "read_seq.h"

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 2);

	FILE* fp_read = NULL;

	long int block_size = get_block_size(argv);
	int records_per_block = block_size / (long int) sizeof(Record);
	char* file_name = get_file_name(argv);

	validate_mode_on_file(file_name, fp_read, "rb");

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(records_per_block, sizeof(Record));
	alloc_check(buffer);

	Result_Acc res;
	init_result_acc(&res);

	Temp_Acc temp;
	init_temp_acc(&temp);

	int records_read = 0;
	while((records_read = fread(buffer, sizeof(Record), records_per_block, fp_read)) > 0) {
		int i;
		for(i = 0; i < records_read; i++) {
			Record record = buffer[(i*sizeof(Record))];
			int uid = record.uid1;
			build_result_acc(uid, &temp, &res);
		}
	}

	unsigned int max = res.max;
	unsigned long avg = calc_avg(&res);

	printf("Max: %u\nAvg: %lu", max, avg);

	fclose(fp_read);
	free(buffer);
	
	return 0;
}