#include  <iostream>
#include  <fstream>
#include  <cstdlib>
#include  <string>
#include  <iomanip>
#include  <conio.h>
#include  <Windows.h>
#include  <sstream>

using namespace std;
class masB;
class masC;
struct record {
	int price;
	int kol;
};
struct comp
{
	string marka;
	string type;
	int ntype;
	int gerz;
	int ram;
	int hdd;
	int vga;
	record pers;
};
struct marki {
	string marka;
	int count;
	string type;
	int ntype;
	int kol;
	int hdd;
	int vga;
};
int operator>(record v, record w);
int operator>(comp v, comp w);
ostream& operator<<(ostream& out, comp& px)
{
	out << "|" << setw(7) << px.marka << "|" << setw(8) << px.type << " " << setw(4) << px.ntype << "|" << setw(18) << px.gerz << "|" << setw(13) << px.ram << "|" << setw(12) << px.hdd << "|" << setw(21) << px.vga << "|" << setw(9) << px.pers.price << "|" << setw(10) << px.pers.kol << "| \n";
	return out;
};
ostream& operator<<(ostream& out, marki& z) //Определение перегруженной операции вывода на экран структуры типа PLATA
{
	out << "|" << setw(8) << std::left << z.marka << "|" << setw(12) << std::left << z.count << "|" << endl;
	return out;
}
class masA
{
protected:
	comp* px;
	int n;
public:
	masA() :px(NULL), n(0) {};
	masA(masA& z);
	//Деструктор
	~masA() { if (px != NULL) delete[]px; }

	masA& operator=(masA& z);
	void inputFile();
	void adddan();
	void deletedan();
	void outputMas();
	void outputFile();
	void sorttype();
	void sortmarka();
	void sortprice();

	friend ostream& operator<<(ostream& out, masA& z);
};//Определение методов класса masA
masA::masA(masA& z) //Конструктор копирования класса masA
{
	int i;
	n = z.n;
	if (n == 0) px = NULL;
	else {
		px = new comp[n];
		if (px == NULL) {
			cout << "нет памяти.\n";
			cout << "Конструктор копирования.\n";
			system("pause"); exit(1);
		}
		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
} // конец конструктора копирования
masA& masA :: operator=(masA& z) //Определение перегруженной операции присваивания класса masA
{
	int i;
	if (this == &z) return *this;
	if (px != NULL) delete[]px;
	n = z.n;
	if (z.px == NULL) px = NULL;
	else {
		px = new comp[n];
		if (px == NULL) {
			cout << "нет памяти.\n";
			cout << "операция присваивания.\n";
			system("pause"); return z;
		}
		for (i = 0; i < n; i++)
			px[i] = z.px[i];
	}
	return *this;
}

void masA::inputFile()   //  ввод исходного массива структур из файла
{
	ifstream fin;
	string file;
	string iniz;
	comp t;
	cout << "Имя входного файла:";
	cin >> file;
	fin.open(file.c_str()); //открытие текстового файла

	//  Защита от неправильного ввода имени файла
	if (fin.fail()) {
		cout << file << " не открывается\n";
		system("pause"); return;
	}

	n = 0;
	if (px != NULL) { delete[] px; px = NULL; }  // очистка массива

	while (1)
	{
		fin >> t.marka >> t.type >> t.ntype >> t.gerz >> t.ram >> t.hdd >> t.vga >> t.pers.price >> t.pers.kol;
		if (fin.fail()) break;	n++;
	}

	fin.close();
	px = new comp[n];

	if (px == NULL) {
		cout << "Нет памяти.\n"; fin.close();
		cout << "Ввести фаил не удается.\n";
		system("pause"); n = 0; return;
	}
	fin.close();
	fin.open(file.c_str()); //открытие текстового файла
	if (fin.fail()) {
		cout << file << "повторно не открывается\n";
		system("pause"); n = 0; return;
	}
	for (int i = 0; i < n; i++)
	{
		fin >> px[i].marka >> px[i].type >> px[i].ntype >> px[i].gerz >> px[i].ram >> px[i].hdd >> px[i].vga >> px[i].pers.price >> px[i].pers.kol;
	}

	fin.close();
	cout << "Файл введен " << endl;
	system("pause");
}
void masA::outputMas()
{
	int i;

	// Вывод заголовка таблицы (массива структур) 
	cout << "__________________________________________________________________________________________________________________\n";
	cout << "|  |       |             |                  |             |            |                     |         |          |\n";
	cout << "|№ | Марка | Тип проц-ра |Такт. частота, ГГц|Объем ОЗУ, Гб|Объем ЖД, Гб|Объем видеопамяти, Гб|Цена, руб|Кол-во, шт|\n";
	cout << "|__|_______|_____________|__________________|_____________|____________|_____________________|_________|__________|" << "\n";
	cout << left;
	// Вывод строк таблицы
	for (i = 0; i < n; i++)
		cout << "|" << setw(2) << i + 1 << "|" << setw(7) << px[i].marka << "|" << setw(10) << px[i].type << setw(3) << px[i].ntype << "|" << setw(18) << px[i].gerz << "|" << setw(13) << px[i].ram << "|" << setw(12) << px[i].hdd << "|" << setw(21) << px[i].vga << "|" << setw(9) << px[i].pers.price << "|" << setw(10) << px[i].pers.kol << "| \n";
	cout << "|_________________________________________________________________________________________________________________|\n";
	system("pause");

}
void masA::outputFile()
{
	ofstream fout;
	string file;
	int i;
	cout << "Имя выходного файла:";   cin >> file;
	fout.open(file.c_str());

	//  Защита от неправильного ввода имени файла
	if (fout.fail()) {
		cout << file << "не создается.\n";
		system("pause"); return;
	}
	// Вывод заголовка 
	fout << "__________________________________________________________________________________________________________________\n";
	fout << "|  |       |             |                  |             |            |                     |         |          |\n";
	fout << "|№ | Марка | Тип проц-ра |Такт. частота, ГГц|Объем ОЗУ, Гб|Объем ЖД, Гб|Объем видеопамяти, Гб|Цена, руб|Кол-во, шт|\n";
	fout << "|__|_______|_____________|__________________|_____________|____________|_____________________|_________|__________|" << "\n";
	fout << left;
	// Вывод строк таблицы
	for (i = 0; i < n; i++)
		fout << "|" << setw(2) << i + 1 << "|" << setw(7) << px[i].marka << "|" << setw(10) << px[i].type << setw(3) << px[i].ntype << "|" << setw(18) << px[i].gerz << "|" << setw(13) << px[i].ram << "|" << setw(12) << px[i].hdd << "|" << setw(21) << px[i].vga << "|" << setw(9) << px[i].pers.price << "|" << setw(10) << px[i].pers.kol << "| \n";
	fout << "|_________________________________________________________________________________________________________________|\n";

	fout.close();
	cout << "Массив структур сохранен в фаил\n";
	system("pause");
}
void masA::adddan()
{
	int i;
	comp t, * p;
	string iniz;
	p = new comp[n + 1];  // выделение памяти для нового массива
	if (p == NULL) {
		cout << "нет памяти.\n";
		cout << "Добавить не удается.\n";
		system("pause"); return;
	}

	cout << "Марка:"; cin >> t.marka;
	cout << "Тип процессора:";   cin >> t.type; cin >> t.ntype;
	cout << "Тактовая частота:"; cin >> t.gerz;
	cout << "Объем ОЗУ, Гб:";      cin >> t.ram;
	cout << "Объем ЖД, Гб:"; cin >> t.hdd;
	cout << "Объем видеопамяти, Гб:"; cin >> t.vga;
	cout << "Цена, руб:"; cin >> t.pers.price;
	cout << "Кол-во, шт:"; cin >> t.pers.kol;

	for (i = 0; i < n; i++)
		p[i] = px[i];   // копирования старого массива в новый
	p[n] = t; // добавление новой записи в массив структур
	n++;   // увеличение счетчика количества записей

	if (px != NULL) delete[] px; // удаление старого массива
	px = p;    // адрес нового массива заносится в px

	cout << "Запись добавлена.\n";
	system("pause");
}
void masA::sortprice()               // по цене
{
	int i, fl, nn;
	comp t;
	nn = n;                                       // вводим копию размера массива
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (px[i].pers.price > px[i + 1].pers.price)
			{
				fl = 1;  t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].pers.price == px[i + 1].pers.price) && (px[i].pers.kol > px[i + 1].pers.kol))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по цене\n";
	system("pause");
}
void masA::deletedan()
{
	int j, i;
	comp* p = NULL;
	string iniz;
	char ch;

	outputMas();  //  вызов на экран массива структур
	cout << "Номер удаленой стороки:";
	cin >> j;
	if (cin.fail())
	{
		string s;
		cin.clear();
		cin >> s;
		cout << "Это не номер строки \n";
		system("pause");
		return;
	}

	if (j < 1 || j > n) {
		cout << "Ошибка: нет такой строки.\n";
		system("pause"); return;
	}
	j--; //  переход от номера удаленной строки к ее индексу
	cout << j + 1 << "-я строка:\n";
	cout << px[j].marka << "\n" << px[j].type << " " << px[j].ntype << "\n" << px[j].gerz << "\n" << px[j].ram << "\n" << px[j].hdd << "\n" << px[j].vga << "\n" << px[j].pers.price << "\n" << px[j].pers.kol << endl;

	cout << "Удалить?(y/n):"; cin >> ch;
	if (ch == 'n') return;   // отказ удаления строки
	if (ch != 'y') { cout << "Ошибка ответа на вопрос. \n";  system("pause"); return; }

	//  Выполнение удаления строки     
	if (n == 1) { delete[] px; px = NULL; n = 0; }
	else
	{
		p = new comp[n - 1];
		if (p == NULL)
		{
			cout << "Нет памяти.\n ";
			cout << "Удалить не удается.\n";
			system("pause"); return;
		}
		for (i = 0; i < j; i++)
			p[i] = px[i];
		for (i = j + 1; i < n; i++)
			p[i - 1] = px[i];
		delete[] px; // удаление старого массива
		px = p;    // адрес нового массива заносится в поле px
		n--;//  уменьшение счетчика количества записей
	}
	cout << "Запись удалена.\n";
	system("pause");
}
void masA::sortmarka()
{
	int i, fl, nn;
	comp t;
	nn = n;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (px[i].marka > px[i + 1].marka)
			{
				fl = 1;  t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type > px[i + 1].type))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type == px[i + 1].type) && (px[i].ntype > px[i + 1].ntype))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz > px[i + 1].gerz))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram > px[i + 1].ram))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd > px[i + 1].hdd))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd == px[i + 1].hdd) && (px[i].vga > px[i + 1].vga))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd == px[i + 1].hdd) && (px[i].vga == px[i + 1].vga) && (px[i].pers.price > px[i + 1].pers.price))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].marka == px[i + 1].marka) && (px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd == px[i + 1].hdd) && (px[i].vga == px[i + 1].vga) && (px[i].pers.price == px[i + 1].pers.price) && (px[i].pers.kol > px[i + 1].pers.kol))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по марке\n";
	system("pause");
}
void masA::sorttype()
{
	int i, fl, nn;
	comp t;
	nn = n;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (px[i].type > px[i + 1].type)
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].type == px[i + 1].type) && (px[i].ntype > px[i + 1].ntype))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz > px[i + 1].gerz))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram > px[i + 1].ram))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd > px[i + 1].hdd))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd == px[i + 1].hdd) && (px[i].vga > px[i + 1].vga))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd == px[i + 1].hdd) && (px[i].vga == px[i + 1].vga) && (px[i].pers.price > px[i + 1].pers.price))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
			else if ((px[i].type == px[i + 1].type) && (px[i].ntype == px[i + 1].ntype) && (px[i].gerz == px[i + 1].gerz) && (px[i].ram == px[i + 1].ram) && (px[i].hdd == px[i + 1].hdd) && (px[i].vga == px[i + 1].vga) && (px[i].pers.price == px[i + 1].pers.price) && (px[i].pers.kol > px[i + 1].pers.kol))
			{
				fl = 1;
				t = px[i];
				px[i] = px[i + 1];
				px[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по типу процессора и тактовой частоте\n";
	system("pause");
}
ostream& operator<<(ostream& out, masA& z)
{
	int i;
	// Вывод заголовка таблицы (массива структур)
	cout << "__________________________________________________________________________________________________________________\n";
	cout << "|  |       |             |                  |             |            |                     |         |          |\n";
	cout << "|№ | Марка | Тип проц-ра |Такт. частота, ГГц|Объем ОЗУ, Гб|Объем ЖД, Гб|Объем видеопамяти, Гб|Цена, руб|Кол-во, шт|\n";
	cout << "|__|_______|_____________|__________________|_____________|____________|_____________________|_________|__________|" << "\n";
	// Вывод строк таблицы
	for (i = 0; i < z.n; i++)
		out << "|" << setw(2) << i + 1 << z.px[i];
	out << "_________________________________________________________________________________________________________________________\n";
	system("pause");
	return out;
}
class masB : public masA
{
protected:
	marki* mas;
	int k;
public:
	masB() :mas(NULL), k(0) {};
	masB(masB& z);

	~masB() { if (mas != NULL) delete[]mas; }
	masB& operator=(masB& z);

	// Методы класса masB:
	void outputFile();
	void outputtype();
	void sortmarka();
	void sortCount();
	void makePerech();
	void makePerechtype();
	void makePerechvga();
	void sortKol();
	void sortvga();
	void sorthdd();
	void outputvga();
	void outputhdd();
	void makePerechhdd();
	friend ostream& operator<<(ostream& out, masB& z);

};
masB::masB(masB& z) : masA(z) //конструктор копирования класса masB
{
	int i;
	k = z.k;
	if (z.mas == NULL) mas = NULL;
	else {
		mas = new marki[k];
		if (mas == NULL) {
			cout << "Нет памяти.\n";
			cout << "Конструктор копирования.\n";
			system("pause"); exit(1);
		}

		for (i = 0; i < k; i++)
			mas[i] = z.mas[i];
	}
}
masB& masB :: operator=(masB& z) //перегруженная операция присваивания класса masB
{
	int i;
	if (this == &z) return *this;
	// Вызов перегруженной операции присваивания класса masА для 
	masA :: operator= (z);  // присваивания родительской части объекта z
	if (mas != NULL) delete[] mas;
	k = z.k;
	if (z.mas == NULL) mas = NULL;
	else {
		mas = new marki[k];
		if (mas == NULL) {
			cout << "Нет памяти при присваивании. \n";
			system("pause"); return z;
		}
		for (i = 0; i < k; i++)
			mas[i] = z.mas[i];
	}
	return *this;
}
ostream& operator<<(ostream& out, masB& z)
{
	int i;
	out << "______________________\n";
	out << "| Марка  | Количество |\n";
	out << "|________|____________|\n";

	for (i = 0; i < z.k; i++)
	{
		out << z.mas[i];
		out << "|________|____________|\n";
	}
	system("pause");
	return out;
}
void masB::sortmarka()
{
	int fl, i, kk;
	marki t;

	kk = k;
	do {
		fl = 0; kk--;
		for (i = 0; i < kk; i++)
			if (mas[i].marka > mas[i + 1].marka)
			{
				fl = 1; t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Перечень упорядочен по каждой марке.\n";
	system("pause");
}
void masB::sortCount()
{
	int i, fl, kk;
	marki t;
	kk = k;
	do {
		fl = 0; kk--;
		for (i = 0; i < kk; i++)
			if (mas[i].count > mas[i + 1].count)
			{
				fl = 1; t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Перечень упорядочен по количеству компьютеров. \n";
	system("pause");
}
void masB::sortKol()
{
	int i, fl, kk;
	marki t;
	kk = k;
	do {
		fl = 0; kk--;
		for (i = 0; i < kk; i++)
			if (mas[i].kol > mas[i + 1].kol)
			{
				fl = 1; t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Перечень упорядочен по количеству компьютеров. \n";
}
void masB::sortvga()
{
	int i, fl, kk;
	marki t;
	kk = k;
	do {
		fl = 0; kk--;
		for (i = 0; i < kk; i++)
			if (mas[i].vga > mas[i + 1].vga)
			{
				fl = 1; t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Перечень упорядочен по количеству компьютеров. \n";
}
void masB::sorthdd()
{
	int i, fl, kk;
	marki t;
	kk = k;
	do {
		fl = 0; kk--;
		for (i = 0; i < kk; i++)
			if (mas[i].kol > mas[i + 1].kol)
			{
				fl = 1; t = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Перечень упорядочен по количеству компьютеров. \n";
}
void masB::outputFile()
{
	ofstream fout;
	string file;
	int i;
	cout << "Имя выходного файла\n"; cin >> file;
	fout.open(file.c_str());
	//  Защита от неправильного ввода имени файла
	if (fout.fail()) {
		cout << file << "Не создан.Неверный ввод имени файла\n";
		system("pause");
		return;
	}
	fout << "______________________\n";
	fout << "| Марка  | Количество |\n";
	fout << "|________|____________|\n";
	for (i = 0; i < k; i++)
		fout << "| " << setw(7) << mas[i].marka << "|" << setw(12) << mas[i].count << "|\n";
	fout << "|_____________________|\n";
	fout.close();
	cout << "Перечень сохранен в файле.\n";
	system("pause");
}
void masB::makePerech()
{
	int i, j, fl;
	marki* y;
	y = new marki[n];
	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause");
		return;
	}
	k = 0;
	if (mas != NULL) delete[] mas;

	for (i = 0; i < n; i++)
	{
		fl = 0;
		for (j = 0; j < k; j++)
			if (px[i].marka == y[j].marka)
			{
				fl = 1; y[j].count += px[i].pers.kol;
			}

		if (fl == 0) {
			y[k].marka = px[i].marka;
			y[k].count = px[i].pers.kol;
			k++;
		}
	}
	mas = new marki[k];
	if (mas == NULL) {
		cout << "Нет памяти для перечня.\n";
		system("pause"); k = 0; delete[] y; return;
	}
	for (j = 0; j < k; j++)
		mas[j] = y[j];
	delete[] y;

	cout << "Перечень сформирован.\n";
}
void masB::makePerechtype()
{
	int i, j, fl;
	marki* y;
	y = new marki[n];
	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause");
		return;
	}
	k = 0;
	if (mas != NULL) delete[] mas;

	for (i = 0; i < n; i++)
	{
		fl = 0;
		for (j = 0; j < k; j++)
			if ((px[i].type == y[j].type) && (px[i].ntype == y[j].ntype))
			{
				fl = 1; y[j].kol += px[i].pers.kol;
			}

		if (fl == 0) {
			y[k].type = px[i].type;
			y[k].ntype = px[i].ntype;
			y[k].kol = px[i].pers.kol;
			k++;
		}
	}
	mas = new marki[k];
	if (mas == NULL) {
		cout << "Нет памяти для перечня.\n";
		system("pause"); k = 0; delete[] y; return;
	}
	for (j = 0; j < k; j++)
		mas[j] = y[j];
	delete[] y;

	cout << "Перечень сформирован.\n";
}
void masB::makePerechvga()
{
	int i, j, fl;
	marki* y;
	y = new marki[n];
	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause");
		return;
	}
	k = 0;
	if (mas != NULL) delete[] mas;

	for (i = 0; i < n; i++)
	{
		fl = 0;
		for (j = 0; j < k; j++)
			if (px[i].vga == y[j].vga)
			{
				fl = 1; y[j].kol += px[i].pers.kol;
			}

		if (fl == 0) {
			y[k].vga = px[i].vga;
			y[k].kol = px[i].pers.kol;
			k++;
		}
	}
	mas = new marki[k];
	if (mas == NULL) {
		cout << "Нет памяти для перечня.\n";
		system("pause"); k = 0; delete[] y; return;
	}
	for (j = 0; j < k; j++)
		mas[j] = y[j];
	delete[] y;

	cout << "Перечень сформирован.\n";
}
void masB::makePerechhdd()
{
	int i, j, fl;
	marki* y;
	y = new marki[n];
	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause");
		return;
	}
	k = 0;
	if (mas != NULL) delete[] mas;

	for (i = 0; i < n; i++)
	{
		fl = 0;
		for (j = 0; j < k; j++)
			if (px[i].hdd == y[j].hdd)
			{
				fl = 1; y[j].kol += px[i].pers.kol;
			}

		if (fl == 0) {
			y[k].hdd = px[i].hdd;
			y[k].kol = px[i].pers.kol;
			k++;
		}
	}
	mas = new marki[k];
	if (mas == NULL) {
		cout << "Нет памяти для перечня.\n";
		system("pause"); k = 0; delete[] y; return;
	}
	for (j = 0; j < k; j++)
		mas[j] = y[j];
	delete[] y;

	cout << "Перечень сформирован.\n";
}

void masB::outputtype()
{
	int i;
	cout << "_________________________\n";
	cout << "|   Тип      |Количество |\n";
	cout << "|____________|___________|\n";

	for (i = 0; i < k; i++)
	{
		cout << "|" << setw(8) << mas[i].type << setw(4) << mas[i].ntype << "|" << setw(11) << mas[i].kol << "| \n";
		cout << "|____________|___________|\n";
	}
	system("pause");
}
void masB::outputvga()
{
	int i;
	cout << "_________________________\n";
	cout << "| Объем(Гб)  |Количество |\n";
	cout << "|____________|___________|\n";

	for (i = 0; i < k; i++)
	{
		cout << "|" << setw(8) << mas[i].vga << setw(5) << "|" << setw(11) << mas[i].kol << "| \n";
		cout << "|____________|___________|\n";
	}
	system("pause");
}
void masB::outputhdd()
{
	int i;
	cout << "_________________________\n";
	cout << "|Объем ЖД(Гб)| Количество|\n";
	cout << "|____________|___________|\n";

	for (i = 0; i < k; i++)
	{
		cout << "|" << setw(8) << mas[i].hdd << setw(5) << "|" << setw(11) << mas[i].kol << "| \n";
		cout << "|____________|___________|\n";
	}
	system("pause");
}
class masC : public masB
{
protected:
	comp* pz;
	int l;
public:
	masC() :pz(NULL), l(0) {};
	masC(masC& z);
	~masC() { if (pz != NULL) delete[]pz; }
	masC& operator=(masC& z);

	//  Методы класса masC:
	void outputFile();
	void sortmarka();
	void sortram();
	void sorttype();
	void findhdd();
	void findprice();
	void findall();
	//  Дружественные функции класса masC:

	friend ostream& operator<<(ostream& out, masC& z);
};
masC::masC(masC& z) : masB(z)
{
	int i;
	l = z.l;
	if (z.pz == NULL) pz = NULL;
	else {
		pz = new comp[l];
		if (pz == NULL) {
			cout << "Нет памяти.\n";
			cout << "Конструктор копирования.\n";
			system("pause"); exit(1);
		}
		for (i = 0; i < l; i++)
			pz[i] = z.pz[i];
	}
}
masC& masC::operator=(masC& z)
{
	int i;
	if (this == &z) return *this;
	// Вызов перегруженной операции присваивания класса masB для 
	masB :: operator=(z);  // присваивания родительской части объекта z
	if (pz != NULL) delete[] pz;
	l = z.l;
	if (z.pz == NULL) pz = NULL;
	else {
		pz = new comp[l];
		if (pz == NULL) {
			cout << "Нет памяти при присваивании. \n";
			system("pause"); return z;
		}
		for (i = 0; i < l; i++)
			pz[i] = z.pz[i];
	}
	return *this;
}
ostream& operator<<(ostream& out, masC& z)
{
	int i;
	cout << "__________________________________________________________________________________________________________________\n";
	cout << "|  |       |             |                  |             |            |                     |         |          |\n";
	cout << "|№ | Марка | Тип проц-ра |Такт. частота, ГГц|Объем ОЗУ, Гб|Объем ЖД, Гб|Объем видеопамяти, Гб|Цена, руб|Кол-во, шт|\n";
	cout << "|__|_______|_____________|__________________|_____________|____________|_____________________|_________|__________|" << "\n";
	cout << left;
	// Вывод строк таблицы
	for (i = 0; i < z.l; i++)
		cout << "|" << setw(2) << i + 1 << "|" << setw(7) << z.pz[i].marka << "|" << setw(10) << z.pz[i].type << setw(3) << z.pz[i].ntype << "|" << setw(18) << z.pz[i].gerz << "|" << setw(13) << z.pz[i].ram << "|" << setw(12) << z.pz[i].hdd << "|" << setw(21) << z.pz[i].vga << "|" << setw(9) << z.pz[i].pers.price << "|" << setw(10) << z.pz[i].pers.kol << "| \n";
	cout << "|_________________________________________________________________________________________________________________|\n";
	system("pause");
	return out;
}
void masC::findhdd()
{
	int i, j;
	int mem;
	comp* y;
	y = new comp[n];
	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause"); return;
	}
	cout << "Количество Гб : ";
	cin >> mem;
	l = 0;
	for (i = 0; i < n; i++)
		if (px[i].hdd == mem) { y[l] = px[i];  l++; }
	if (pz != NULL) delete[] pz;
	pz = new comp[l];
	if (pz == NULL) {
		cout << "Нет памяти! \n";
		system("pause"); l = 0; delete[] y; return;
	}
	for (j = 0; j < l; j++)
		pz[j] = y[j];
	delete[] y;
	cout << "Данные по поиску выстроены. \n";
	system("pause");
}
void masC::findprice()
{
	int i, j;
	int mem;
	comp* y;
	y = new comp[n];
	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause"); return;
	}
	cout << "Цена: ";
	cin >> mem;
	l = 0;
	for (i = 0; i < n; i++)
		if (px[i].pers.price == mem) { y[l] = px[i];  l++; }
	if (pz != NULL) delete[] pz;
	pz = new comp[l];
	if (pz == NULL) {
		cout << "Нет памяти! \n";
		system("pause"); l = 0; delete[] y; return;
	}
	for (j = 0; j < l; j++)
		pz[j] = y[j];
	delete[] y;
	cout << "Данные по поиску выстроены. \n";
	system("pause");
}
void masC::findall()
{
	int i, j;
	string mar, typee;
	int ozu, hd, video;
	comp* y;
	y = new comp[n];
	if (y == NULL) {
		cout << "Нет памяти.\n";
		system("pause"); return;
	}
	cout << "Марка: ";
	cin >> mar;
	cout << "Тип процессора: ";
	cin >> typee;
	cout << "Объем ОЗУ: ";
	cin >> ozu;
	cout << "Объем ЖД: ";
	cin >> hd;
	cout << "Объем видеопамяти: ";
	cin >> video;
	l = 0;
	//если нужно в принципе поиск по любому параметру (главное чтоб нашел) то меняем && на ||
	for (i = 0; i < n; i++)
		if ((px[i].marka == mar) && (px[i].type == typee) && (px[i].ram == ozu) && (px[i].hdd == hd) && (px[i].vga == video)) { y[l] = px[i];  l++; }
	if (pz != NULL) delete[] pz;
	pz = new comp[l];
	if (pz == NULL) {
		cout << "Нет памяти! \n";
		system("pause"); l = 0; delete[] y; return;
	}
	for (j = 0; j < l; j++)
		pz[j] = y[j];
	delete[] y;
	cout << "Данные по поиску выстроены. \n";
	system("pause");
}
void masC::outputFile()
{
	ofstream fout;
	string file;
	int i;
	cout << "Имя выходного файла:";   cin >> file;
	fout.open(file.c_str());
	//  Защита от неправильного ввода имени файла
	if (fout.fail()) {
		cout << file << "Файл не создается. Неправильный ввод имени.\n";
		system("pause"); return;
	}
	fout << "__________________________________________________________________________________________________________________\n";
	fout << "|  |       |             |                  |             |            |                     |         |          |\n";
	fout << "|№ | Марка | Тип проц-ра |Такт. частота, ГГц|Объем ОЗУ, Гб|Объем ЖД, Гб|Объем видеопамяти, Гб|Цена, руб|Кол-во, шт|\n";
	fout << "|__|_______|_____________|__________________|_____________|____________|_____________________|_________|__________|" << "\n";
	fout << left;
	// Вывод строк таблицы
	for (i = 0; i < l; i++)
		fout << "|" << setw(2) << i + 1 << "|" << setw(7) << pz[i].marka << "|" << setw(10) << pz[i].type << setw(3) << pz[i].ntype << "|" << setw(18) << pz[i].gerz << "|" << setw(13) << pz[i].ram << "|" << setw(12) << pz[i].hdd << "|" << setw(21) << pz[i].vga << "|" << setw(9) << pz[i].pers.price << "|" << setw(10) << pz[i].pers.kol << "| \n";
	fout << "|_________________________________________________________________________________________________________________|\n";

	fout.close();
	cout << "Массив структур сохранен в фаил\n";
	system("pause");
}
void masC::sortmarka()
{
	int i, fl, nn;
	comp t;

	nn = l;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (pz[i].marka > pz[i + 1].marka)
			{
				fl = 1;  t = pz[i];
				pz[i] = pz[i + 1];
				pz[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по названию марки\n";
	system("pause");
}
void masC::sortram() // сортировка по дате заключения
{
	int fl, i, nn;
	comp t;

	nn = l;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (pz[i].ram > pz[i + 1].ram)
			{
				fl = 1; t = pz[i];
				pz[i] = pz[i + 1];
				pz[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по объему озу\n";
	system("pause");
}
void masC::sorttype() // сортировка по дате заключения
{
	int fl, i, nn;
	comp t;

	nn = l;
	do {
		fl = 0; nn--;
		for (i = 0; i < nn; i++)
			if (pz[i].type > pz[i + 1].type)
			{
				fl = 1; t = pz[i];
				pz[i] = pz[i + 1];
				pz[i + 1] = t;
			}
	} while (fl == 1);
	cout << "Массив структур упорядочен по типу процессора\n";
	system("pause");
}

void main()
{
	setlocale(LC_ALL, "Russian");
	masC a;
	int j;

	while (1)
	{
		system("cls"); //clrscr(); очистка экрана
		cout << "1. Загрузка из файла\n";
		cout << "2. Вывод на экран дисплея данных \n";
		cout << "3. Сохранение результатов обработки в файлах\n";
		cout << "4. Добавление записи\n";
		cout << "5. Удаление записи\n";
		cout << "6. Сортировка по типу процессора и тактовой частоте\n";
		cout << "7. Сортировка по марке\n";
		cout << "8. Числовая сортировка по цене\n";
		cout << "9. Проверка конструктора копирования\n";
		cout << "10.Проверка перегруженной операции присваивания\n";
		cout << "11.Формирование перечня количества компьютеров (сортировка по маркам)\n";
		cout << "12.Вывод перечня марок компьютеров на экран\n";
		cout << "13.Вывод перечня марок компьютеров в файл\n";
		cout << "14.Сортировка перечня по марке\n";
		cout << "15.Сортировка перечня по числу\n";
		cout << "16.Поиск компьютеров по объему жесткого диска\n";
		cout << "17.Вывод компьютеров по объему жесткого диска на экран\n";
		cout << "18.Вывод компьютеров по объему жесткого диска в файл\n";
		cout << "19.Сортировка поисковых данных по объему озу\n";
		cout << "20.Сортировка поисковых данных по названию марки\n";
		cout << "21.Выход из программы\n\n";
		cout << "22.Формирование перечня типов процессора и их количество (сортировка по количеству)\n";
		cout << "23.Формирование перечня объемов памяти видеокарты и их количество (сортировка по объему)\n";
		cout << "24.Формирование перечня объемов жесткого диска и их количество (сортировка по количеству)\n";
		cout << "25.Поиск компьютеров по цене(сортировка по процессору)\n";
		cout << "26.Поиск глобальный\n";
		cout << "Ваш выбор (1-21): ";
		cin >> j;
		//    Защита от неправильного ввода пункта меню
		if (cin.fail())
		{
			string s;
			cin.clear();
			cin >> s;
			cout << "Это не пункт меню\n";
			system("pause");
			continue;          //   K следующей итерации
		}


		//    Реализация выбранного пункта меню
		switch (j)
		{
		case 1: a.inputFile(); break;
		case 2: cout << (masA&)a; break;
		case 3: a.masA::outputFile(); break;
		case 4: a.adddan(); break;
		case 5: a.deletedan(); break;
		case 6: a.masA::sorttype(); break;
		case 7: a.masA::sortmarka(); break;
		case 8: a.sortprice(); break;
		case 9: { masC b(a);
			cout << (masA&)b << (masA&)a;
			cout << (masB&)b << (masB&)a;
			cout << b << a; }  break;
		case 10: { masC b, c; c = b = a;
			cout << (masA&)c << (masA&)b << (masA&)a;
			cout << (masB&)c << (masB&)b << (masB&)a;
			cout << c << b << a; } break;

		case 11: a.makePerech(); a.masB::sortmarka(); break;
		case 12: cout << (masB&)a;  break;
		case 13: a.masB::outputFile(); break;
		case 14: a.masB::sortmarka(); break;
		case 15: a.sortCount(); break;
		case 16: a.findhdd(); a.sortram(); break;
		case 17: cout << a;  break;
		case 18: a.outputFile(); break;
		case 19: a.sortram(); break;
		case 20: a.sortmarka(); break;
		case 21: cout << "Конец работы\n";  system("pause"); return;
		case 22: a.makePerechtype(); a.masB::sortKol(); a.masB::outputtype(); break;
		case 23: a.makePerechvga(); a.masB::sortvga(); a.masB::outputvga(); break;
		case 24: a.makePerechhdd(); a.masB::sorthdd(); a.masB::outputhdd(); break;
		case 25: a.findprice(); a.masC::sorttype(); cout << a; break;
		case 26: a.findall(); cout << a; break;
		default: cout << "Нет такого пункта в меню\n";  system("pause");
		}
	}

}
