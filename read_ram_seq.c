#include "read_seq.h"

off_t get_file_size(char* file_name) {
	struct stat st;
	
	int stat_err = stat(file_name, &st);
	if (stat_err == -1) {
		/* Handle error */
	}

	return st.st_size;
}

void validate_file_size(off_t size) {
	if (size % sizeof(Record) != 0) {
		/* Handle error */
	}
}

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 1);

	FILE* fp_read = NULL;

	char* file_name = get_file_name(argv);

	validate_mode_on_file(file_name, fp_read, "rb");

	off_t size = get_file_size(file_name);
	validate_file_size(size);

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(size, sizeof(char));
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
	for(i = 0; i < size; i++) {
		Record record = buffer[(i*sizeof(Record))];
		int uid = record.uid1;
		build_result_acc(uid, &temp, &res);
	}

	unsigned int max = res.max;
	unsigned long avg = calc_avg(&res);

	printf("Max: %u\nAvg: %lu", max, avg);

	fclose(fp_read);
	free(buffer);
	
	return 0;
}