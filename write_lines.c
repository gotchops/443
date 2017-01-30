#include "utils.h"

int main(int argc, char** argv) {
	validate_args(argc-1, argv, 1);

	FILE* fp_read = NULL;
	FILE* fp_write = NULL;

	char* file_name = get_file_name(argv);

	validate_mode_on_file(file_name, fp_read, "r");
	validate_mode_on_file("write_lines_output.csv", fp_write, "wb");

	char current_line[MAX_CHARS_PER_LINE];

	while(fgets(current_line, MAX_CHARS_PER_LINE, fp_read) != NULL) {
		fputs(current_line, fp_write);
	}

	fclose(fp_read);
	fclose(fp_write);

	return 0;
}