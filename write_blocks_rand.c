#include "utils.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		return -1;
	}

	long int x = atol(argv[1]);
	if (x <= 0) {
		return -1;
	}

	FILE* fp_write = NULL;
	char* file_name = "records.dat";

	validate_mode_on_file(file_name, &fp_write, "r+b");

	off_t size = get_file_size(file_name);
	validate_file_size(size);

	srand(time(NULL));
	long int r;
	long int num_records_in_file = size / sizeof(Record);

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(1, sizeof(Record));
	alloc_check(buffer);

	Record record;
	record.uid1 = 1;
	record.uid2 = 2;

	buffer[0] = record;

	long int i;	
	for(i=0; i<x; i++) {
		r = rand() % num_records_in_file;
		fseek(fp_write, r*sizeof(Record), SEEK_SET);
		fwrite(buffer, sizeof(Record), 1, fp_write);
	}

	fclose(fp_write);
	free(buffer);

	return 0;
}