#include <stdio.h>
#include "mylib.h"
#include "queue.h"


int pass_distribute(Registration reg, Pass_input pass)
{
	printf("0\t\t");
	int q;
	for (q = 0; q < reg.len; q++) {
		printf("№%d\t\t", q+1);
	}
	printf("\n");
	int t, pass_cur = 0;
	int time_max = pass.arr[pass.len - 1].ta;
	// flag - если мы вернулись на тот же момент времени в цикле
	int q_min = -1, kicked = 0, flag = 0;
	int returned;
	for (t = 1; t < time_max+1; t++) {
		// пассажиры закончились, никто больше не приедет
		if (pass_cur >= pass.len) {
			if (flag > 0) {
				printf_task_reg(t, reg);
			}
			break;
		}
		kicked = 0;
		if (flag == 0) {
			kicked = reg_kick_pass(reg, t);
			reg_time_count(reg, t);
		}
		// след приедет позже, т.е никто новый не приедет в этот t
		if (pass.arr[pass_cur].ta > t) {
			if (kicked > 0 || flag > 0) {
				printf_task_reg(t, reg);
			}
			flag = 0;
			continue;
		}
		q_min = reg_least_time(reg);
		pass.arr[pass_cur].tin = queue_get_timein(reg.arr[q_min], pass.arr[pass_cur].ta);
		returned = insert_queue(reg.arr[q_min], pass.arr[pass_cur]);
		if (returned == 0) {
			return 0;
		}
		pass_cur++;
		t--;
		flag = 1;
	}
	return 1;
}


int reg_kick_pass(Registration reg, int time_cur)
{
	int flag = 0;
	int q;
	for (q = 0; q < reg.len; q++) {
		flag += queue_kick_pass(reg.arr[q], time_cur);
	}
	return (flag > 0);
}


int queue_kick_pass(QueuePtr que, int time_cur)
{
	if (queue_is_empty(que) == 1) {
		return 0;
	}
	Passanger pass = get_queue(que, 0);
	if (pass.tin + pass.ts == time_cur) {
		pop_queue(que);
		return 1;
	}
	return 0;
}


void reg_time_count(Registration reg, int time_cur)
{
	int q;
	for (q = 0; q < reg.len; q++) {
		reg.que_time[q] += queue_is_active(reg.arr[q], time_cur);
	}
}


int queue_is_active(QueuePtr que, int time_cur)
{
	if (queue_is_empty(que) == 1) {
		return 0;
	}
	Passanger pass = get_queue(que, 0);
	if (pass.tin < time_cur) {
		return 1;
	}
	return 0;
}


void printf_task_reg(int time_cur, Registration reg)
{
	printf("%d\t\t", time_cur);
	int q;
	for (q = 0; q < reg.len; q++) {
		if (queue_is_empty(reg.arr[q]) == 1) {
			printf("---\t\t");
			continue;
		}
		printf_task_queue(reg.arr[q]);
		printf("\t\t");
	}
	printf("\n");
}


int reg_least_time(Registration reg)
{
	int q;
	for (q = 0; q < reg.len; q++) {
		if (queue_is_empty(reg.arr[q]) == 1) {
			return q;
		}
	}
	int q_min = 0, len_min = queue_length(reg.arr[0]) + 1;
	float time_avg_min = -1;
	int len_cur = -1, time_cur = -1;
	float time_avg_cur = -1;
	for (q = 0; q < reg.len; q++) {
		len_cur = queue_length(reg.arr[q]);
		if (len_cur > len_min) {
			continue;
		}
		time_cur = reg.que_time[q];
		time_avg_cur = (float)time_cur / len_cur;
		if (len_cur < len_min) {
			len_min = len_cur;
			time_avg_min = time_avg_cur;
			q_min = q;
			continue;
		}
		// len_cur == len_min
		if (time_avg_cur < time_avg_min) {
			len_min = len_cur;
			time_avg_min = time_avg_cur;
			q_min = q;
		}
	}
	return q_min;
}


int queue_get_timein(QueuePtr que, int time_arrive)
{
	if (queue_is_empty(que) == 1) {
		return time_arrive;
	}
	Passanger pass = get_queue_last(que);
	int time_free = pass.tin + pass.ts;
	if (time_arrive < time_free) {
		return time_free;
	}
	return time_arrive;
}


void pass_kick_remainings(Registration reg, int time_start)
{
	int t;
	int time_end = get_reg_last_out(reg);
	int kicked;
	for (t = time_start; t < time_end + 1; t++) {
		kicked = reg_kick_pass(reg, t);
		if (kicked > 0) {
			printf_task_reg(t, reg);
		}
	}
}


int get_reg_last_out(Registration reg)
{
	int q;
	int time_max = -1;
	Passanger pass;
	for (q = 0; q < reg.len; q++) {
		if (queue_is_empty(reg.arr[q]) == 1) {
			continue;
		}
		pass = get_queue_last(reg.arr[q]);
		if (time_max < pass.tin + pass.ts) {
			time_max = pass.tin + pass.ts;
		}
	}
	return time_max;
}
