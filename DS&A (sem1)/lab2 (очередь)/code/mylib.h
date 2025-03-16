#ifndef MYLIB_H
#define MYLIB_H

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
} Registration;

// reception.c
int safeScanfInt(int *target, int retry);
int check_for_overflow(char s[13]);
char *readl_until_slash(char *output);
Pass_input read_passangers();
int scanf_passangers(char **string_id, int *time_arrive, int *time_service);
void passInput_sort(Pass_input pass);
int compare(const void *a, const void *b);

void free_passInput(Pass_input *pass);
void free_passanger(Passanger *pass);
void printf_passanger(Passanger pass);
void printf_passInput(Pass_input pass);
Passanger passanger_copy(Passanger pass);

Registration create_registration(int amount);
int dialog_get_queue_size();
void free_registration(Registration *reg);
void printf_registration(Registration reg);

// task.c
int pass_distribute(Registration reg, Pass_input pass);
void pass_kick_remainings(Registration reg, int time_start);

int reg_kick_pass(Registration reg, int time_cur);
int queue_kick_pass(QueuePtr que, int time_cur);
void reg_time_count(Registration reg, int time_cur);
int queue_is_active(QueuePtr que, int time_cur);
void printf_task_reg(int time_cur, Registration reg);
int reg_least_time(Registration reg);
int queue_get_timein(QueuePtr que, int time_arrive);
int get_reg_last_out(Registration reg);

#endif
