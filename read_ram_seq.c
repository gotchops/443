#include "utils.h"

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 1);

	FILE* fp_read = NULL;

	char* file_name = get_file_name(argv);

	validate_mode_on_file(file_name, &fp_read, "rb");

	off_t size = get_file_size(file_name);
	validate_file_size(size);

	off_t records_in_file = size / sizeof(Record);

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(records_in_file, size);
	alloc_check(buffer);

	Result_Acc res;
	init_result_acc(&res);

	Temp_Acc temp;
	init_temp_acc(&temp);

	size_t read = fread(buffer, sizeof(off_t), size, fp_read);
	if (read != size) {
		/* Handle error */
	}

	off_t i;
	for(i = 0; i < records_in_file; i++) {
		Record record = buffer[i];
		int uid = record.uid1;
		build_result_acc(uid, &temp, &res);
	}

	unsigned int max = res.max;
	float avg = calc_avg(&res);

	printf("Max: %u\nAvg: %.2f\n", max, avg);

	fclose(fp_read);
	free(buffer);
	
	return 0;
}