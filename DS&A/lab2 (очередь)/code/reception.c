#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "mylib.h"
#include "queue.h"


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
			if (retry == 0) {
				return 0;
			}
			printf("Введено не целое число! Введено: %s\n", buf);
			continue;
		}
		if (check_for_overflow(buf)) {
		    scanf("%*[^\n]");
		    if (retry == 0) {
		    	return 0;
		    }
		    printf("Слишком большое число! Введено: %s\n", buf);
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
    char *temp = NULL;
    do {
        n = scanf(" %80[^\n/]", buf);
        if (n == EOF) {
        	free(ptr);
        	return NULL;
        }
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
            temp = (char*)realloc(ptr, (len+1)*sizeof(char));
            if (temp == NULL) {
            	printf("Недостаточно свободной памяти!\n");
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
		if ((guard == 0 || guard == EOF) == 0) {
			printf("Введено не положительное число! Введено: %d\n", time_a);
		}
		free(str_id);
		return guard;
	}
	scanf("%*[^-0-9a-zA-Z]");
	guard = safeScanfInt(&time_s, 0);
	if (guard == 0 || time_s < 1 || guard == EOF) {
		if ((guard == 0 || guard == EOF) == 0) {
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
	pass.arr = (Passanger*)calloc(1, sizeof(Passanger));
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


void passInput_sort(Pass_input pass)
{
	qsort(pass.arr, pass.len, sizeof(Passanger), compare);
}


int compare(const void *a, const void *b) {
    Passanger *pass1 = (Passanger *)a;
    Passanger *pass2 = (Passanger *)b;

    if (pass1->ta != pass2->ta) {
        return pass1->ta - pass2->ta;
    } else {
        return pass1->ts - pass2->ts;
    }
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
	// не делаем free(pass->next), т.к он ещё останется в que->head и будет нужен
	pass->next = NULL;
	pass->ta = 0;
	pass->ts = 0;
	pass->tin = 0;
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
	if (reg->arr == NULL) {
		return;
	}
	int i;
	for (i = 0; i < reg->len; i++) {
		free_queue(reg->arr + i);
	}
	free(reg->arr);
	reg->arr = NULL;
	reg->len = 0;
}


Registration create_registration(int amount)
{
	Registration reg = (Registration){0, NULL, NULL};
	reg.arr = (QueuePtr*)malloc(amount * sizeof(QueuePtr));
	if (reg.arr == NULL) {
		printf("Не найдено свободной памяти\n");
		return reg;
	}
	int size = dialog_get_queue_size();
	// size < 1 проверяется именно в create_queue(),
	// потому что на списке это игнорится
	if (size == EOF) {
		free_registration(&reg);
		reg = (Registration){0, NULL, NULL};
		return reg;
	}
	int i;
	for (i = 0; i < amount; i++) {
		reg.arr[i] = NULL;
		reg.arr[i] = create_queue(size);
		if (reg.arr[i] == NULL) {
			// printf() уже был в create_queue()
			free_registration(&reg);
			reg = (Registration){0, NULL, NULL};
			return reg;
		}
		reg.len++;
	}
	reg.que_time = (int*)calloc(amount, sizeof(int));
	if (reg.que_time == NULL) {
		printf("Не найдено свободной памяти\n");
		free_registration(&reg);
		reg = (Registration){0, NULL, NULL};
		return reg;
	}
	return reg;
}


int dialog_get_queue_size()
{
	printf("Введите размер очереди (для списка он не будет учитываться)\n");
	int size;
	scanf("%*[^-0-9a-zA-Z]");
	// size считываю только один раз, потому что на списке это надо игнорить
	int guard = safeScanfInt(&size, 0);
	if (guard == 0 || guard == EOF) {
		return guard;
	}
	return size;
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
}


Passanger passanger_copy(Passanger pass)
{
	// pass_copy.next = NULL, т.к указатель нужен новый,
	// и он будет создан в создании очереди
	Passanger pass_copy = (Passanger){NULL, pass.ta, pass.ts, pass.tin, NULL};
	pass_copy.id = (char*)malloc((strlen(pass.id) + 1) * sizeof(char));
	if (pass_copy.id == NULL) {
		printf("Не найдено свободной памяти!\n");
		pass_copy = (Passanger){NULL, 0, 0, 0, NULL};
		return pass_copy;
	}
	strcpy(pass_copy.id, pass.id);
	return pass_copy;
}
