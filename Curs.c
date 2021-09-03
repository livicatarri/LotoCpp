//Составить базу данных о квартирах дома (от 6 до 12). Для каждой квартиры указать
номер, жилую площадь, общую площадь, количество жильцов, количество детей.
Упорядочить квартиры по общей площади или по количеству жильцов или по
метражу на одного жильца.

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

//описание структуры для одной квартиры
struct Apartment
{
	//номер квартиры
	int number;
	//жилая площадь
	float living_area;
	//общая площадь
	float total_area;
	// кол-во живущих человек
	int living_person;
	//кол-во детей
	int living_children;
	//площадь на 1 человека
	float area_per_person;
};

//Кол-во квартир
int number_of_apartments = 9;

//прообразы всех функций
void printToScreen(Apartment*[]);
void createFromFile(Apartment*[]);
void createFromKeyboard(Apartment*[]);
void saveToFile(Apartment*[]);
void sortByTotalArea(Apartment*[]);
void sortByLivingPerson(Apartment*[]);
void sortByAreaPerPerson(Apartment*[]);

int main()
{
	//модель "дома" - массив указателей на квартиры
	Apartment *House[12];

	//переменная для выбора из меню
	int chosen;

	//вывод меню на экран
	printf("Where to get info about DB?\n1 - Keyboard, 2 - Text file\n");
	//считывание выбора
	scanf("%d", &chosen);

	//ветвление вариантов выбора
	switch (chosen)
	{
		//если введено "1"
	case 1:
		//вызов функции считывания с клавиатуры
		createFromKeyboard(House);
		break;

		//если введено "2"
	case 2:
		//вызов функции считывания с файла
		createFromFile(House);
		break;

		//если введено другое число
	default:
		//завершить с ошибкой
		printf("ERROR");
		return 1;
	}

	//метка для goto
enterSwitch:

	//Вывод меню
	printf("what to do now?\n1 - sort by total area,  2 - sort by living persons, 3 - sort by area per person, 4 - print to screen, 5 - save to file\n");
	//считывание выбора
	scanf("%d", &chosen);

	//ветвление вариантов выбора
	switch (chosen)
	{
		//если введено "1"
	case 1:
		//вызов функции сортировки по общ площади
		sortByTotalArea(House);
		break;
		//Если введено "2"
	case 2:
		//вызов функции сортировки по количеству живущих людей
		sortByLivingPerson(House);
		break;
		//если введено "3"
	case 3:
		//вызов функции сортировки по площади на человека
		sortByAreaPerPerson(House);
		break;
		//если введено 4
	case 4:
		//вызов функции вывода на экран
		printToScreen(House);
		break;
		//если введено 5
	case 5:
		//вызов функции сохранения в файл
		saveToFile(House);
		break;

	default:
		printf("ERROR");
		return 1;
	}

	goto enterSwitch;
}

//вывод на экран
void printToScreen(Apartment*House[])
{
	//информационная строка
	printf("|number\t|liv. area\t|tot. area\t|liv. persons\t|liv. children\t|\n");
	//цикл от 0 до макс. кол-ва квартир
	for (int i = 0; i < number_of_apartments; i++)
	{
		//вывод параметров квартир
		printf("|%d\t|%f\t|%f\t|%d\t\t|%d\t\t|\n", House[i]->number, House[i]->living_area, House[i]->total_area, House[i]->living_person, House[i]->living_children);
	}
}

//ввод с клавиатуры
void createFromKeyboard(Apartment*House[])
{
	//запрос количества квартир
	printf("Enter number of apts\n");
	//считывание колва квартир
	scanf("%d", &number_of_apartments);
	//информационное сообщение
	printf("Enter line by line parameters of apartments: number, living area, total area, living persons and living children\n");
	//цикл от 0 до макс. кол-ва квартир
	for (int i = 0; i < number_of_apartments; i++)
	{
		//выделение памяти под квартиру
		House[i] = (Apartment*)malloc(sizeof(Apartment));
		//чтение из одной строки параметров квартиры
		scanf("%d %f %f %d %d", &House[i]->number, &House[i]->living_area, &House[i]->total_area, &House[i]->living_person, &House[i]->living_children);
		//если в квартире проживает ненулевое кол-во человек, то площадь на человека = общая площадь/колво людей, иначе просто = общая площадь
		if (House[i]->living_person != 0) House[i]->area_per_person = House[i]->total_area / House[i]->living_person; else House[i]->area_per_person = House[i]->total_area;
	}
}

//чтение из файла
void createFromFile(Apartment*House[])
{
	//переменная для хранения ути-пути
	char path[512];
	//запрос пути
	printf("Enter path\n");
	//чтение пути
	scanf("%s", &path);
	//открытие файлового потока на чтение
	FILE *input = fopen(path, "r+");
	//чтение кол-ва квартир из файла
	fscanf(input, "%d", &number_of_apartments);
	//цикл от 0 до макс. кол-ва квартир
	for (int i = 0; i < number_of_apartments; i++)
	{
		//выделение памяти под квартиру
		House[i] = (Apartment*)malloc(sizeof(Apartment));
		//чтение из файла параметров квартиры
		fscanf(input, "%d %f %f %d %d", &House[i]->number, &House[i]->living_area, &House[i]->total_area, &House[i]->living_person, &House[i]->living_children);
		//если в квартире проживает ненулевое кол-во человек, то площадь на человека = общая площадь/колво людей, иначе просто = общая площадь
		if (House[i]->living_person != 0) House[i]->area_per_person = House[i]->total_area / House[i]->living_person; else House[i]->area_per_person = House[i]->total_area;
	}
}

//функция сохранения в файл
void saveToFile(Apartment*House[])
{
	//переменная для хранения ути-пути
	char path[512];
	//запрос пути
	printf("Enter path\n");
	//чтение пути
	scanf("%s", &path);
	//открытие файлового потока на запись
	FILE *output = fopen(path, "w+");
	//запись в файл кол-ва квартир с переносом в строку
	fprintf(output, "%d\n", number_of_apartments);
	//цикл от 0 до макс. кол-ва квартир
	for (int i = 0; i < number_of_apartments; i++)
	{
		//запись в файл параметров квартиры с последующим переносом строки
		fprintf(output, "%d %f %f %d %d\n", House[i]->number, House[i]->living_area, House[i]->total_area, House[i]->living_person, House[i]->living_children);
	}
}

void sortByTotalArea(Apartment*House[])
{
	for (int i = 0; i < number_of_apartments; i++)
	{
		for (int j = 0; j < number_of_apartments - 1; j++)
		{
			//если общая площадь квартиры j меньше чем j+1
			if (House[j]->total_area < House[j + 1]->total_area)
			{
				//то создаем временный указатель на квартиру и приравниваем его к указателю на квартиру j
				Apartment *temp = House[j];
				//указатель же на кв. j заменяем на указатель на кв j+1
				House[j] = House[j + 1];
				//указатель кв j+1 заменяем на временный, т.е. на указатель на кв j
				House[j + 1] = temp;
			}
		}
	}
}

void sortByLivingPerson(Apartment*House[])
{
	for (int i = 0; i < number_of_apartments; i++)
	{
		for (int j = 0; j < number_of_apartments - 1; j++)
		{
			//если кол-во людей квартиры j меньше чем j+1
			if (House[j]->living_person < House[j + 1]->living_person)
			{
				//то создаем временный указатель на квартиру и приравниваем его к указателю на квартиру j
				Apartment *temp = House[j];
				//указатель же на кв. j заменяем на указатель на кв j+1
				House[j] = House[j + 1];
				//указатель кв j+1 заменяем на временный, т.е. на указатель на кв j
				House[j + 1] = temp;
			}
		}
	}
}

void sortByAreaPerPerson(Apartment*House[])
{
	for (int i = 0; i < number_of_apartments; i++)
	{
		for (int j = 0; j < number_of_apartments - 1; j++)
		{
			//если площадь на чел. квартиры j меньше чем j+1
			if (House[j]->area_per_person < House[j + 1]->area_per_person)
			{
				//то создаем временный указатель на квартиру и приравниваем его к указателю на квартиру j
				Apartment *temp = House[j];
				//указатель же на кв. j заменяем на указатель на кв j+1
				House[j] = House[j + 1];
				//указатель кв j+1 заменяем на временный, т.е. на указатель на кв j
				House[j + 1] = temp;
			}
		}
	}
}