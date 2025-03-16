// это тест, будет ли calloc заполнять всё внутри структур

#include <stdio.h>
#include <stdlib.h>

typedef struct Pet {
	int age;
	char *name;
} Pet;

typedef struct Person {
	int age;
	int height;
	char *name;
	Pet pet;
} Person;

void free_pet(Pet pet)
{
	free(pet.name);
}

void free_person(Person dude)
{
	free(dude.name);
	free_pet(dude.pet); // плак-плак
}

int main()
{
	// Person *group1 = (Person*)malloc(2 * sizeof(Person));
	Person *group2 = (Person*)calloc(2, sizeof(Person));
	int i;
	// printf("Group 1:\n");
	// printf("(сейчас valgrind ругнётся на то, что принтаю не инициализированные значения)\n");
	// for (i = 0; i < 2; i++) {
	//      printf("Person %d:\n\tage:%d\n\theight:%d\n\tname:%s\n\tpet: %d %s\n",
	//              i, group1[i].age, group1[i].height, group1[i].name, group1[i].pet.age, group1[i].pet.name);
	// }
	printf("Group2:\n");
	printf("(а вот тут 0 претензий от валгринда)\n");
	for (i = 0; i < 2; i++) {
		printf("Person %d:\n\tage:%d\n\theight:%d\n\tname:%s\n\tpet:\tage: %d, name:%s\n",
			i, group2[i].age, group2[i].height, group2[i].name, group2[i].pet.age, group2[i].pet.name);
	}

	free(group1);
	free_person(group2[0]);
	free_person(group2[1]);
	free(group2);
	return 0;
}