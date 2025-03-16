#include <stdio.h>
#include <stdlib.h>
#include "mylibrary.h"

int main()
{
	int amount = -1;
	printf("Введите количество стоек\n");
	int guard, flag = 0;
	while (amount < 1) {
		if (flag == 1) {
			printf("Введите число большее 0!\n");
		}
		flag = 1;
		guard = safeScanfInt(&amount, 1);
		scanf("%*[^-0-9a-zA-Z\n]");
		if (guard == EOF) {
			printf("Завершение программы\n");
			return 0;
		}
	}
	Registration reg = (Registration){0, NULL, NULL, 0, NULL};
	reg = create_registration(amount);
	if (reg.len == 0) {
		printf("Завершение программы\n");
		return 0;
	}
	Pass_input pass = (Pass_input){0, NULL};
	printf("Введите информацию о пассажирах через '/'\n");
	pass = read_passangers();
	if (pass.len == 0) {
		printf("Завершение программы\n");
		free_registration(&reg);
		return 0;
	}
	// printf_passInput(pass);

	int returned;
	returned = pass_distribute(&reg, pass);
	if (returned == 0) {
		printf("Завершение программы\n");
		free_registration(&reg);
		free(pass.arr);
		return 0;
	}
	// printf_registration(reg);

	printf_timed_registration(reg);

	printf("Конец программы\n");
	free_registration(&reg);
	// все внутренности pass_input фришить не нужно, т.к. из него
	// все значения попали в reg и там уже были зафришены
	// free_passInput(&pass);
	free(pass.arr);
	return 0;
}
