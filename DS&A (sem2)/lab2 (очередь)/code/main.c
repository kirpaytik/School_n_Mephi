#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int dialog_func(Registration *reg, Pass_input *pass)
{
	int amount = -1;
	printf("Введите количество стоек\n");
	int guard, flag = 0;
	while (amount < 1) {
		if (flag == 1) {
			printf("Введите число большее нуля!\n");
		}
		flag = 1;
		scanf("%*[^-0-9a-zA-Z]");
		guard = safeScanfInt(&amount, 1);
		if (guard == EOF) {
			return 0;
		}
	}
	*reg = (Registration){0, NULL, NULL};
	*reg = create_registration(amount);
	if (reg->len == 0) {
		return 0;
	}

	*pass = (Pass_input){0, NULL};
	printf("Введите информацию о пассажирах через '/'\n");
	*pass = read_passangers();
	if (pass->len == 0) {
		return 0;
	}
	passInput_sort(*pass);
	// printf_passInput(*pass);
	return 1;

}


int task_func_main(Registration reg, Pass_input pass)
{
	int returned;
	returned = pass_distribute(reg, pass);
	// проверку returned устраиваю после pass_kick_remainings,
	// чтобы программа закончила свою работу перед завершением
	int time_start = pass.arr[pass.len - 1].ta;
	pass_kick_remainings(reg, time_start);
	if (returned == 0) {
		return 0;
	}
	return 1;
}


int main()
{
	Registration reg = (Registration){0, NULL, NULL};
	Pass_input pass = (Pass_input){0, NULL};
	int returned;
	returned = dialog_func(&reg, &pass);
	if (returned == 0) {
		printf("Завершение программы\n");
		free_registration(&reg);
		free_passInput(&pass);
		return 0;
	}
	returned = task_func_main(reg, pass);
	if (returned == 0) {
		printf("Завершение программы\n");
		free_registration(&reg);
		free_passInput(&pass);
		return 0;
	}

	printf("Конец программы\n");
	free_registration(&reg);
	free_passInput(&pass);
	return 0;
}
