#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "utils.h"

typedef struct result_acc {
	unsigned int max;
	unsigned long num_friends;
	unsigned long total_uids;
} Result_Acc;

typedef struct temp_acc {
	int uid;
	unsigned long num_friends;
} Temp_Acc;

void init_result_acc(Result_Acc*);

unsigned long calc_avg(Result_Acc*);

void init_temp_acc(Temp_Acc*);

void build_result_acc(int, Temp_Acc*, Result_Acc*);