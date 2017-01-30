#include "read_seq.h"

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