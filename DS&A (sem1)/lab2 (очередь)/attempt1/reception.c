#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "mylibrary.h"


int safeScanfInt(int *target, int retry)
{
	int guard, flag = 1;
	char buf[13];
	// 13, т.к INT_MIN содержит 10 цифр + '-' + один знак для оценки переполнения + '\0'
	buf[12] = '\0';
	int num;
	while (flag == 1)
	{
		guard = scanf(" %12[^ \t\n/]", buf);
		if (guard == EOF) {
			return guard;
		}
		guard = sscanf(buf, "%d", &num);
		if (guard != 1) {
			scanf("%*[^\n]");
			printf("Введено не целое число! Введено: %s\n", buf);
			if (retry == 0) {
				return 0;
			}
			continue;
		}
		if (check_for_overflow(buf)) {
		    printf("Слишком большое число! Введено: %s\n", buf);
		    scanf("%*[^\n]");
		    if (retry == 0) {
		    	return 0;
		    }
		    continue;
		}
		flag = 0;
	}
	*target = num;
	return 1;
}


int check_for_overflow(char s[13])
{
    char s2[13];
    s2[11] = '\0';
    if (s[0] == '-') {
		sprintf(s2, "%d", INT_MIN);
    }
    else {
		sprintf(s2, "%d", INT_MAX);
		s2[10] = '\0';
    }
    if (strlen(s) < strlen(s2)) {
		return 0;
    }
    if (strlen(s) > strlen(s2)) {
		return 1;
    }
    if (strcmp(s, s2) > 0) {
		return 1;
    }
    return 0;
}


char *readl_until_slash(char *output)
{
    printf("%s", output);

    char *ptr = (char*)malloc(1);
    if (ptr == NULL) {
        printf("Не найдено свободной памяти\n");
        return NULL;
    }
    *ptr = '\0';
    char buf[81];
    int n=0, len=0;
    do {
        n = scanf(" %80[^\n/]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0) {
            scanf("%*c");
        }
        else {
            len += strlen(buf);
            char *temp = (char*)realloc(ptr, (len+1)*sizeof(char));
            if (temp == NULL) {
                free(ptr);
                return "\0";
            }
            ptr = temp;
            strcat(ptr, buf);
        }
    } while (n > 0);

    return ptr;
}


int scanf_passangers(char **string_id, int *time_arrive, int *time_service)
{
	int time_a = -1, time_s = -1;
	int guard;
	char *str_id = readl_until_slash("");
	if (str_id == NULL) {
		return EOF;
	}
	scanf("%*[^-0-9a-zA-Z]");
	guard = safeScanfInt(&time_a, 0);
	if (guard == 0 || time_a < 1 || guard == EOF) {
		if (time_a < 1) {
			printf("Введено не положительное число! Введено: %d\n", time_a);
		}
		free(str_id);
		return guard;
	}
	scanf("%*[^-0-9a-zA-Z]");
	guard = safeScanfInt(&time_s, 0);
	if (guard == 0 || time_s < 1 || guard == EOF) {
		if (time_s < 1) {
			printf("Введено не положительное число! Введено: %d\n", time_s);
		}
		free(str_id);
		return guard;
	}
	*string_id = str_id;
	*time_arrive = time_a;
	*time_service = time_s;
	return 1;
}


Pass_input read_passangers()
{
	// доделать проверки
	Pass_input pass = (Pass_input){0, NULL};
	pass.arr = (Passanger*)malloc(sizeof(Passanger));
	if (pass.arr == NULL) {
		printf("Недостаточно свободной памяти\n");
		return pass;
	}
	pass.arr[0].id = NULL;
	Passanger *temp_passanger;
	char *str_id;
	int time_a, time_s;
	int guard, flag = 1;
	printf("Завершение ввода по ctrl+D\n");
	while (flag == 1) {
		guard = scanf_passangers(&str_id, &time_a, &time_s);
		if (guard == EOF) {
			// конец ввода -  штатная ситуация, если
			// хотя бы один passanger был задан
			if (pass.arr[0].id == NULL) {
				free(pass.arr);
				pass.arr = NULL;
			}
			break;
		}
		if (guard == 0) {
			// неверно введены данные о пассажире - повтор
			continue;
		}
		// проверки ввода и тп - доделать
		temp_passanger = (Passanger*)realloc(pass.arr, (pass.len+1) * sizeof(Passanger));
		if (temp_passanger == NULL) {
			printf("Недостаточно свободной памяти\n");
			free(str_id);
			free_passInput(&pass);
			pass = (Pass_input){0, NULL};
			return pass;
		}
		pass.arr = temp_passanger;
		pass.arr[pass.len] = (Passanger){str_id, time_a, time_s, 0, NULL};
		pass.len++;
	}
	return pass;
}


void free_passInput(Pass_input *pass)
{
	if (pass->arr == NULL) {
		return;
	}
	int i;
	for (i = 0; i < pass->len; i++) {
		free_passanger(pass->arr + i);
	}
	free(pass->arr);
	pass->arr = NULL;
	pass->len = 0;
}


void free_passanger(Passanger *pass)
{
	free(pass->id);
	pass->id = NULL;
	free(pass->next);
	pass->next = NULL;
}


void printf_passInput(Pass_input pass)
{
	printf("Вывод введённых пассажиров:\n");
	int p;
	for (p = 0; p < pass.len; p++) {
		printf_passanger(pass.arr[p]);
		printf(" ");
	}
	printf("\n");
}


void printf_passanger(Passanger pass)
{
	printf("%s/%d/%d-%d", pass.id, pass.ta, pass.ts, pass.tin);
}


void free_registration(Registration *reg)
{
	free(reg->que_time);
	reg->que_time = NULL;
	free(reg->time_changes);
	reg->time_changes = NULL;
	if (reg->arr == NULL) {
		return;
	}
	int i;
	for (i = 0; i < reg->len; i++) {
		free_queue(reg->arr + i);
	}
	free(reg->arr);
	reg->arr = NULL;
}


Registration create_registration(int amount)
{
	Registration reg = (Registration){0, NULL, NULL, 0, NULL};
	reg.arr = (QueuePtr*)malloc(amount * sizeof(QueuePtr));
	if (reg.arr == NULL) {
		printf("Не найдено свободной памяти\n");
		return reg;
	}
	int i;
	for (i = 0; i < amount; i++) {
		reg.arr[i] = NULL;
		reg.arr[i] = create_queue();
		if (reg.arr[i] == NULL) {
			// printf() уже был в create_queuePtr()
			free_registration(&reg);
			reg = (Registration){0, NULL, NULL, 0, NULL};
			return reg;
		}
		reg.len++;
	}
	reg.que_time = (int*)calloc(amount, sizeof(int));
	if (reg.que_time == NULL) {
		printf("Не найдено свободной памяти\n");
		free_registration(&reg);
		reg = (Registration){0, NULL, NULL, 0, NULL};
		return reg;
	}
	return reg;
}


void printf_registration(Registration reg)
{
	printf("Вывод стоек регистрации:\n");
	int q;
	for (q = 0; q < reg.len; q++) {
		printf("Очередь №%d:\n", q+1);
		printf_queue(reg.arr[q]);
		printf("\n");
		// printf("que_time = %d\n", reg.que_time[q]);
	}
	// printf("times_change = %d\n", reg.times_change);
	// int i;
	// for (i = 0; i < reg.times_change; i++) {
	//     printf("%d ", reg.time_changes[i]);
	// }
	// printf("\n");
}


Passanger passanger_copy(Passanger pass)
{
	// pass_copy.next = NULL, т.к указатель нужен новый,
	// и он будет создан в создании очереди
	Passanger pass_copy = (Passanger){NULL, pass.ta, pass.ts, pass.tin, NULL};
	pass_copy.id = (char*)malloc(strlen(pass.id) * sizeof(char));
	strcpy(pass_copy.id, pass.id);
	return pass_copy;
}


int pass_distribute(Registration *reg, Pass_input pass)
{
	int t, pass_cur = 0;
	int time_max = pass.arr[pass.len - 1].ta;
	// flag - если только что добавлен passanger
	// q_min - стойка с мин. avg_wait_time
	int flag = 0, q_min, returned;
	// пробег времени
	for (t = 1; t < time_max+1; t++) {
		if (pass_cur >= pass.len) {
			break;
		}
		if (flag == 1) {
			flag = 0;
			if (pass.arr[pass_cur].ta > t) {
				continue;
			}
		}
		// заполнение reg.que_time
		reg_time_count(*reg, t);
		if (pass.arr[pass_cur].ta > t) {
			continue;
		}
		q_min = reg_least_time(*reg, t);
		pass.arr[pass_cur].tin = queue_get_timein(reg->arr[q_min], pass.arr[pass_cur].ta);
		returned = queue_push_back(reg->arr[q_min], pass.arr[pass_cur]);
		if (returned == 0) {
			return 0;
		}
		pass_cur++;
		flag = 1;
		// возврат на предыдущий момент времени,
		// т.к на нём ещё кто-то мог приехать
		t--;
	}
	returned = reg_set_time_changes(reg);
	if (returned == 0) {
		return 0;
	}
	return 1;
}


int reg_least_time(Registration reg, int time_cur)
{
	int q;
	for (q = 0; q < reg.len; q++) {
		if (queue_length(reg.arr[q]) == 0) {
			return q;
		}
	}
	for (q = 0; q < reg.len; q++) {
		if (queue_is_active(reg.arr[q], time_cur) == 0) {
			return q;
		}
	}
	int q_min=-1, time_, len_active, length;
	float time_avg;
	float time_avg_min = reg.que_time[0] + 1;
	QueuePtr que;
	for (q = 0; q < reg.len; q++) {
		que = reg.arr[q];
		length = queue_length(que);
		if (q_min > -1 && length > queue_length(reg.arr[q_min])) {
			continue;
		}
		time_ = reg.que_time[q];
		len_active = queue_ppl_count(que, time_cur);
		time_avg = (float)time_ / len_active;
		if (q_min > -1 && length < queue_length(reg.arr[q_min])) {
			time_avg_min = time_avg;
			q_min = q;
			continue;
		}
		// length == length_min
		if (time_avg < time_avg_min) {
			time_avg_min = time_avg;
			q_min = q;
			continue;
		}
	}
	return q_min;
}


void reg_time_count(Registration reg, int time_cur)
{
	int q_time;
	int q;
	for (q = 0; q < reg.len; q++) {
		q_time = queue_time_count(reg.arr[q], time_cur);
		reg.que_time[q] = q_time;
	}
}


int reg_set_time_changes(Registration *reg)
{
	reg->time_changes = (int*)malloc(sizeof(int));
	if (reg->time_changes == NULL) {
		printf("Не найдено свободной памяти\n");
		return 0;
	}
	reg->times_change = 0;
	int returned;
	int q;
	for (q = 0; q < reg->len; q++) {
		returned = queue_set_time_changes(reg->arr[q], &reg->time_changes, &reg->times_change);
		if (returned == 0) {
			return 0;
		}
	}
	qsort(reg->time_changes, reg->times_change, sizeof(reg->time_changes[0]), compare);
	return 1;
}


void printf_timed_registration(Registration reg)
{
	printf("Вывод изменений состояния очереди:\n");
	int prev = -1;
	int i;
	int times = reg.times_change;
	int *changes = reg.time_changes;
	// вывод временной шкалы
	printf("\t");
	for (i = 0; i < times; i++) {
		if (changes[i] == prev) {
			continue;
		}
		printf("%d\t", changes[i]);
		prev = changes[i];
	}
	printf("\n");
	// вывод стоек
	int q, t;
	int time_ptr = 0;
	for (q = 0; q < reg.len; q++) {
		printf("№%d\t", q+1);
		time_ptr = 0;
		for (t = 1; t <= changes[times-1]; t++) {
			if (t < changes[time_ptr]) {
				continue;
			}
			printf_timed_queue(reg.arr[q], t);
			printf("\t");
			prev = changes[time_ptr];
			time_ptr++;
			while (prev == changes[time_ptr]) {
				time_ptr++;
			}
		}
		printf("\n");
	}
}


int compare(const void* a, const void* b) {
    if (*(int*)a - *(int*)b > 0) {
        return 1;
    }
    return 0;
}
