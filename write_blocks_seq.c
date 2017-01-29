#include "utils.h"

int get_delim_index(char* line) {
	int i = 0;
	int len = strlen(line);
	for (i = 0; i < len; i++) {
		if (line[i] == ',') {
			return i;
		}
	}
	return -1;
}

void line_to_str_array(
		char* line,
		int delim_index,
		char** strings,
		char* str1,
		char* str2
	) {
	strncpy(str1, line, delim_index);
	strcpy(str2, &line[delim_index + 1]);

	strings[0] = str1;
	strings[1] = str2;
}

void str_array_to_record(char** str_array, Record* record) {
	int uid1 = atoi(str_array[0]);
	int uid2 = atoi(str_array[1]);

	if (uid1 == 0 || uid2 == 0) {
		fprintf(stderr, "Error converting string array to record.\n");
		exit(-1);
	}

	record->uid1 = uid1;
	record->uid2 = uid2;
}



void init_result_acc(Result_Acc* acc) {
	acc->max = 0;
	acc->num_friends = 0;
	acc->total_uids = 0;
}

unsigned long calc_avg(Result_Acc* res) {
	return res->num_friends / res->total_uids;
}

void init_temp_acc(Temp_Acc* acc) {
	acc->uid = -1;
	acc->num_friends = 0;
}

void build_result_acc(int uid, Temp_Acc* temp, Result_Acc* res) {
	if (uid != temp->uid) {
		res->total_uids++;
		temp->uid = uid;
		temp->num_friends = 1;
	} else {
		temp->num_friends++;
	}

	unsigned long tnum_friends = temp->num_friends;
	if (res->max < tnum_friends) {
		res->max = tnum_friends;
	}

	res->num_friends++;
}

bool is_record_size_multiple(unsigned long block_size_bytes) {
	if (block_size_bytes % sizeof(Record) == 0) {
		return true;
	}
	return false;
}

int main(int argc, char** argv) {
	validate_args(argc-1, argv);
	
	char* line = "1,2";
	int len = strlen(line);
	int i = get_delim_index(line);
	if (i == -1) {
		return -1;
	}

	char* strings[2];
	char str1[i + 1];
	char str2[len - i + 1];

	str1[i] = '\0';
	str2[len - i + 1] = '\0';
	
	line_to_str_array(line, i, strings, str1, str2);

	printf("%s,%s asdf\n", str1, str2);
	
	Record record = { -1, -1  };
	str_array_to_record(strings, &record);

	printf("%d,%d asdf\n", record.uid1, record.uid2);

	return 0;
}
