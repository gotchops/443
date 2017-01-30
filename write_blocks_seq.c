#include "utils.h"

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 2);

	FILE* fp_read = NULL;
	FILE* fp_write = NULL;

	long int block_size = get_block_size(argv);
	int records_per_block = block_size / (long int) sizeof(Record);
	char* file_name = get_file_name(argv);
	
	validate_mode_on_file(file_name, fp_read, "r");
	validate_mode_on_file("records.dat", fp_write, "wb");

	/* Allocate buffer for one block. */
	Record* buffer = (Record*) calloc(records_per_block, sizeof(Record));
	alloc_check(buffer);

	int buffer_index = 0;
	char current_line[MAX_CHARS_PER_LINE];
	while(fgets(current_line, MAX_CHARS_PER_LINE, fp_read) != NULL) {
		/* Copy line and remove end-of-line characters. */		
		current_line[strcspn(current_line, "\r\n")] = '\0';
		
		int i = get_delim_index(current_line);
		if (i == -1) {
			return -1;
		}
		
		int len = strlen(current_line);		

		char* strings[2];
		char str1[i + 1];
		char str2[len - i + 1];

		str1[i] = '\0';
		str2[len - i + 1] = '\0';
	
		line_to_str_array(current_line, i, strings, str1, str2);

		Record record = { -1, -1  };
		str_array_to_record(strings, &record);

		buffer[buffer_index] = record;
		
		if (buffer_index == records_per_block) {
			fwrite(buffer, sizeof(Record), records_per_block, fp_write);
			fflush(fp_write);
			buffer_index = 0;
		} else {
			buffer_index++;
		}
	}
	fflush(fp_write);

	fclose(fp_read);
	fclose(fp_write);
	free(buffer);

	return 0;
}
