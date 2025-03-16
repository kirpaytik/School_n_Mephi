#ifndef MYLIBRARY_H
#define MYLIBRARY_H

typedef struct Passanger {
	char *id;
	int ta;
	int ts;
	int tin;
	struct Passanger *next;
} Passanger;

typedef struct Pass_input {
	int len;
	Passanger *arr;
} Pass_input;

typedef struct Queue *QueuePtr;

typedef struct Registration {
	int len;
	QueuePtr *arr;
	int *que_time;
	int times_change;
	int *time_changes;
} Registration;

// reception.c
int safeScanfInt(int *target, int retry);
int check_for_overflow(char s[13]);
char *readl_until_slash(char *output);
Pass_input read_passangers();
int scanf_passangers(char **string_id, int *time_arrive, int *time_service); // доделать
void free_passInput(Pass_input *pass);
void free_passanger(Passanger *pass);
void printf_passanger(Passanger pass);
void printf_passInput(Pass_input pass);
Registration create_registration(int amount);
void free_registration(Registration *reg);
void printf_registration(Registration reg);

Passanger passanger_copy(Passanger pass);
int pass_distribute(Registration *reg, Pass_input pass);
// возвращает индекс очереди, в которую предпочтительно пихнуть пассажира
int reg_least_time(Registration reg, int time_cur);
void reg_time_count(Registration reg, int time_cur);
int reg_set_time_changes(Registration *reg);
void printf_timed_registration(Registration reg);

int compare(const void* a, const void* b);

// queue-*.c
QueuePtr create_queue();
void free_queue(QueuePtr *que);
void printf_queue(QueuePtr que);

int queue_length(QueuePtr que);
int queue_push_back(QueuePtr que, Passanger pass);
// перерасчитывает время, которое каждая очередь работала с людьми
// до текущего момента, и записывает его в reg.arr[i]
int queue_time_count(QueuePtr que, int time_cur);
int queue_ppl_count(QueuePtr que, int time_cur);
int queue_is_active(QueuePtr que, int time_cur);
int queue_get_timein(QueuePtr que, int time_arrive);
int queue_set_time_changes(QueuePtr que, int **arr, int *len);
void printf_timed_queue(QueuePtr que, int time_cur);

#endif
