#include <stdio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <malloc.h>
#include <fstream>
#include <vector>

class Dishes
{
private:
	char* dishes;
	int costDishes;
	int caloriesDishes;
	int numberDishes;
public:
	Dishes() {
		dishes = nullptr;
		costDishes = 0;
		caloriesDishes = 0;
		numberDishes = 0;
	}
	~Dishes() {
		free(dishes);
	}
	void Setter(int numberDishes) {
		this->numberDishes = numberDishes;
	}
	void SetDishes() {
		static int count = 0;
		if (count == numberDishes) {
			count = 0;
		}
		std::string temp;
		printf("%i) Введите блюдо: ", count + 1);
		std::cin >> temp;

		dishes = (char*)malloc(temp.length() * sizeof(char) + 1);

		for (int i = 0; i < temp.length(); i++)
		{
			dishes[i] = temp[i];
		}

		dishes[temp.length()] = '\0';

		std::cout << "Стоимость блюда: ";
		std::cin >> costDishes;

		std::cout << "Калории блюда: ";
		std::cin >> caloriesDishes;

		count++;
	}
	void GetMaxCostDishes(int& max) {
		max += costDishes;
	}
	void GetMinCostDishes(int& min) {
		min += costDishes;
	}
	void GetMaxCaloriesDishes(int& maxCalories) {
		maxCalories = caloriesDishes;
	}
	std::string CaloriesDish() {
		return dishes;
	}
	void WriteFile(std::ofstream& fout)
	{
		fout.write((char*)&dishes, sizeof(dishes));
		fout.write((char*)&costDishes, sizeof(costDishes));
		fout.write((char*)&caloriesDishes, sizeof(caloriesDishes));
	}
	void WriteChangeFile(std::vector<char*>& myVector, std::vector<int>& myVectorInt)
	{
		myVector.push_back(dishes);
		myVectorInt.push_back(costDishes);
		myVectorInt.push_back(caloriesDishes);
	}
};

class Lunches
{
private:
	int numberLunches;
	int numberDishes;
	char** lunches;
	Dishes** dishes;
public:
	Lunches(int numberLunches, int numberDishes) {
		this->numberLunches = numberLunches;
		this->numberDishes = numberDishes;
		lunches = (char**)malloc(this->numberLunches * sizeof(char*));
		dishes = (Dishes**)malloc(this->numberLunches * sizeof(Dishes*));
	}
	~Lunches() {
		for (int i = 0; i < numberLunches; i++)
		{
			free(lunches[i]);
			free(dishes[i]);
		}
		free(lunches);
		free(dishes);
	}
	void SetLunches() {
		for (int i = 0; i < numberLunches; i++)
		{
			std::string temp;
			printf("%i. Введите обед: ", i + 1);
			std::cin >> temp;

			lunches[i] = (char*)malloc(temp.length() * sizeof(char) + 1);

			for (int j = 0; j < temp.length(); j++)
			{
				lunches[i][j] = temp[j];
			}

			lunches[i][temp.length()] = '\0';

			dishes[i] = (Dishes*)malloc(this->numberDishes * sizeof(Dishes));

			for (int j = 0; j < numberDishes; j++)
			{
				dishes[i][j].Setter(numberDishes);
				dishes[i][j].SetDishes();
			}
			std::cout << "\n";
		}
	}
	void WriteFile(std::ofstream& fout)
	{
		for (int i = 0; i < numberLunches; i++)
		{
			char* str = new char[strlen(lunches[i]) + 1];
			for (int j = 0; j < strlen(lunches[i]); j++)
			{
				str[j] = lunches[i][j];
			}
			str[strlen(lunches[i])] = '\0';
			fout.write((char*)&str, sizeof(str));
			for (int j = 0; j < numberDishes; j++)
			{
				dishes[i][j].WriteFile(fout);
			}
		}
	}
};

void ReadFile(std::ifstream& fin, int st, int numberOfDishes)
{
	if (!fin.is_open())
	{
		std::cout << "Ошибка открытия файла\n";
	}
	else
	{
		char* temp;
		int num;
		int count = 0;
		while (count != st)
		{
			fin.read((char*)&temp, sizeof(temp));
			printf("%i. Обед: ", count + 1);
			std::cout << temp << "\n";

			for (int i = 0; i < numberOfDishes; i++)
			{
				fin.read((char*)&temp, sizeof(temp));
				std::cout << "Блюдо: ";
				std::cout << temp << "\n";
				fin.read((char*)&num, sizeof(num));
				std::cout << "Стоимость блюда: ";
				std::cout << num << "\n";
				fin.read((char*)&num, sizeof(num));
				std::cout << "Калории блюда: ";
				std::cout << num << "\n";
				std::cout << "\n";
			}
			count++;
		}
	}
}

void ReadFileWithChecking(std::ifstream& fin, int st, int numberOfDishes)
{
	if (!fin.is_open())
	{
		std::cout << "Ошибка открытия файла\n";
	}
	else
	{
		int n;
		std::cout << "Введите номер записи, которую нужно найти: ";
		std::cin >> n;

		char* temp;
		int num;
		int count = 0;
		while (count != st)
		{
			fin.read((char*)&temp, sizeof(temp));
			if ((n - 1) == count)
			{
				printf("%i. Обед: ", count + 1);
				std::cout << temp << "\n";

				for (int i = 0; i < numberOfDishes; i++)
				{
					fin.read((char*)&temp, sizeof(temp));
					std::cout << "Блюдо: ";
					std::cout << temp << "\n";
					fin.read((char*)&num, sizeof(num));
					std::cout << "Стоимость блюда: ";
					std::cout << num << "\n";
					fin.read((char*)&num, sizeof(num));
					std::cout << "Калории блюда: ";
					std::cout << num << "\n";
				}
			}
			for (int i = 0; i < numberOfDishes; i++)
			{
				fin.read((char*)&temp, sizeof(temp));
				fin.read((char*)&num, sizeof(num));
				fin.read((char*)&num, sizeof(num));
			}
			count++;
		}
	}
}

void Add(int& st, int& numberOfDishes)
{
	int N, Q;

	std::cout << "Введите кол-во комплексных обедов: ";
	std::cin >> N;
	std::cout << "Введите кол-во блюд: ";
	std::cin >> Q;
	numberOfDishes = Q;

	Lunches lunches(N, Q);
	lunches.SetLunches();

	std::ofstream fout;
	fout.open("C:\\Users\\Виталий\\source\\repos\\ConsoleApplication1\\FILE.bin",
		(std::ofstream::app | std::ios::binary));
	if (!fout.is_open())
	{
		throw "Ошибка при открытии файла\n";
	}
	else
	{
		lunches.WriteFile(fout);
	}
	fout.close();
	st += N;
}

void Remove(int& st, int numberOfDishes)
{
	int temp;
	std::cout << "Введите номер записи, которую нужно удалить: ";
	std::cin >> temp;
	char* str;
	int number;
	std::vector<char*> myVectorLunches;
	std::vector<char*> myVectorDishes;
	std::vector<int> myVectorCost;
	std::vector<int> myVectorCalories;
	std::ifstream fin;
	fin.open("C:\\Users\\Виталий\\source\\repos\\ConsoleApplication1\\FILE.bin", std::ios::binary);
	int count = 0;
	int q = 0;
	while (q != st)
	{
		if (q != temp - 1)
		{
			fin.read((char*)&str, sizeof(str));
			myVectorLunches.push_back(str);
			for (int i = 0; i < numberOfDishes; i++)
			{
				fin.read((char*)&str, sizeof(str));
				myVectorDishes.push_back(str);
				fin.read((char*)&number, sizeof(number));
				myVectorCost.push_back(number);
				fin.read((char*)&number, sizeof(number));
				myVectorCalories.push_back(number);
			}
		}
		else if (q == temp - 1)
		{
			fin.read((char*)&str, sizeof(str));
			for (int i = 0; i < numberOfDishes; i++)
			{
				fin.read((char*)&str, sizeof(str));
				fin.read((char*)&number, sizeof(number));
				fin.read((char*)&number, sizeof(number));
			}
			count++;
		}
		q++;
	}
	st -= count;
	fin.clear();
	fin.close();

	std::ofstream fout;
	fout.open("C:\\Users\\Виталий\\source\\repos\\ConsoleApplication1\\FILE.bin", std::ios::binary);
	if (!fout.is_open())
	{
		throw "Ошибка при открытии файла\n";
	}
	else
	{
		for (int i = 0; i < myVectorLunches.size(); i++)
		{
			fout.write((char*)&myVectorLunches[i], sizeof(myVectorLunches[i]));
			for (int j = 0; j < numberOfDishes; j++)
			{
				fout.write((char*)&myVectorDishes[j], sizeof(myVectorDishes[j]));
				fout.write((char*)&myVectorCost[j], sizeof(myVectorCost[j]));
				fout.write((char*)&myVectorCalories[j], sizeof(myVectorCalories[j]));
			}
		}
	}
	fout.close();
}

void Change(int& st, int numberOfDishes)
{
	int temp;
	std::cout << "Введите номер записи, которую нужно изменить: ";
	std::cin >> temp;
	char* str;
	int number;
	std::vector<char*> myVectorLunches;
	std::vector<char*> myVectorDishes;
	std::vector<int> myVectorCost;
	std::vector<int> myVectorCalories;
	std::ifstream fin;
	fin.open("C:\\Users\\Виталий\\source\\repos\\ConsoleApplication1\\FILE.bin", std::ios::binary);
	if (!fin.is_open())
	{
		throw "Ошибка при открытии файла\n";
	}
	else
	{
		int count = 0;
		int q = 0;
		while (q != st)
		{
			if (q != temp - 1)
			{
				fin.read((char*)&str, sizeof(str));
				myVectorLunches.push_back(str);
				for (int i = 0; i < numberOfDishes; i++)
				{
					fin.read((char*)&str, sizeof(str));
					myVectorDishes.push_back(str);
					fin.read((char*)&number, sizeof(number));
					myVectorCost.push_back(number);
					fin.read((char*)&number, sizeof(number));
					myVectorCalories.push_back(number);
				}
			}
			else if (q == temp - 1)
			{
				fin.read((char*)&str, sizeof(str));
				for (int i = 0; i < numberOfDishes; i++)
				{
					fin.read((char*)&str, sizeof(str));
					fin.read((char*)&number, sizeof(number));
					fin.read((char*)&number, sizeof(number));
				}
				count++;

				std::string str;
				std::cout << "Введите обед: ";
				std::cin >> str;

				char* lunches = new char[str.length() + 1];
				for (int i = 0; i < str.length(); i++)
				{
					lunches[i] = str[i];
				}
				lunches[str.length()] = '\0';

				char** dishes = new char* [numberOfDishes];
				int* cost = new int[numberOfDishes];
				int* calories = new int[numberOfDishes];
				for (int i = 0; i < numberOfDishes; i++)
				{
					std::string str2;
					std::cout << "Введите блюдо: ";
					std::cin >> str2;

					dishes[i] = new char[str2.length() + 1];
					for (int j = 0; j < str2.length(); j++)
					{
						dishes[i][j] = str2[j];
					}
					dishes[i][str.length()] = '\0';

					std::cout << "Введите стоимость блюда: ";
					std::cin >> cost[i];

					std::cout << "Введите калории блюда: ";
					std::cin >> calories[i];
				}

				myVectorLunches.push_back(lunches);
				for (int i = 0; i < numberOfDishes; i++)
				{
					myVectorDishes.push_back(dishes[i]);
					myVectorCost.push_back(cost[i]);
					myVectorCalories.push_back(calories[i]);
				}
				/*for (int i = 0; i < numberOfDishes; i++)
				{
					delete[] dishes[i];
				}
				delete[] lunches;
				delete[] dishes;
				delete[] cost;
				delete[] calories;*/
			}
			q++;
		}
		fin.clear();
	}
	fin.close();

	std::ofstream fout;
	fout.open("C:\\Users\\Виталий\\source\\repos\\ConsoleApplication1\\FILE.bin", std::ios::binary);
	if (!fout.is_open())
	{
		throw "Ошибка при открытии файла\n";
	}
	else
	{
		for (int i = 0; i < myVectorLunches.size(); i++)
		{
			fout.write((char*)&myVectorLunches[i], sizeof(myVectorLunches[i]));
			for (int j = 0; j < numberOfDishes; j++)
			{
				fout.write((char*)&myVectorDishes[j], sizeof(myVectorDishes[j]));
				fout.write((char*)&myVectorCost[j], sizeof(myVectorCost[j]));
				fout.write((char*)&myVectorCalories[j], sizeof(myVectorCalories[j]));
			}
		}
	}
	fout.close();
}

void Output(int& st, int numberOfDishes)
{
	std::ifstream fin;
	fin.open("C:\\Users\\Виталий\\source\\repos\\ConsoleApplication1\\FILE.bin", std::ios::binary);
	if (!fin.is_open())
	{
		throw "Ошибка при открытии файла\n";
	}
	else
	{
		ReadFile(fin, st, numberOfDishes);
	}
	fin.close();
}

void SelectOfOutput(int& st, int numberOfDishes)
{
	std::ifstream fin;
	fin.open("C:\\Users\\Виталий\\source\\repos\\ConsoleApplication1\\FILE.bin", std::ios::binary);
	if (!fin.is_open())
	{
		throw "Ошибка при открытии файла\n";
	}
	else
	{
		ReadFileWithChecking(fin, st, numberOfDishes);
	}
	fin.close();
}

int main()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int st = 0;
	int numberOfDishes;

	while (true)
	{
		std::cout << "1. Добавить к файлу следующую запись.\n";
		std::cout << "2. Удалить с файла указанную запись.\n";
		std::cout << "3. Изменить в файле указанную запись.\n";
		std::cout << "4. Вывести на экран последовательно содержание всех записей.\n";
		std::cout << "5. Вывести на экран последовательно содержание всех записей, \
которые отвечают указанным условиям.\n";
		std::cout << "6. Закончить работу программы.\n\n";

		int num;
		std::cout << "Введите номер задачи: ";
		std::cin >> num;

		if (num == 1) {
			try
			{
				Add(st, numberOfDishes);
				system("cls");
			}
			catch (const char* ex)
			{
				std::cout << ex << "\n";
			}
			catch (...)
			{
				std::cout << "Неизвестная ошибка...\n";
			}
		}
		else if (num == 2) {
			try
			{
				Remove(st, numberOfDishes);
				system("cls");
			}
			catch (const char* ex)
			{
				std::cout << ex << "\n";
			}
			catch (...)
			{
				std::cout << "Неизвестная ошибка...\n";
			}
		}
		else if (num == 3) {
			try
			{
				Change(st, numberOfDishes);
				system("cls");
			}
			catch (const char* ex)
			{
				std::cout << ex << "\n";
			}
			catch (...)
			{
				std::cout << "Неизвестная ошибка...\n";
			}
		}
		else if (num == 4) {
			try
			{
				system("cls");
				Output(st, numberOfDishes);
			}
			catch (const char* ex)
			{
				std::cout << ex << "\n";
			}
			catch (...)
			{
				std::cout << "Неизвестная ошибка...\n";
			}
		}
		else if (num == 5) {
			try
			{
				system("cls");
				SelectOfOutput(st, numberOfDishes);
			}
			catch (const char* ex)
			{
				std::cout << ex << "\n";
			}
			catch (...)
			{
				std::cout << "Неизвестная ошибка...\n";
			}
		}
		else if (num == 6) { break; }
		else { system("cls"); }
	}

	return 0;
}