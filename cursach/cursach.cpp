#include<iostream>
#include<cstring>
#include<cctype>
#include<fstream>
#include<ctime>
#include<Windows.h>
using namespace std;

const int SIZEE = 20;
const char* subject[]{ "Математический анализ", "Физика", "Линейная алгебра и аналитическая геометрия", "Языки программирования",
"Основы информационной безопасности", "Анализ сложности алгоритмов", "Физкультура", "Иностранные языки", "Правоведение", "Введение в профессиональную деятельность" };

struct marks {
	int m_1;
	int m_2;
	int m_3;
	int m_4;
	int m_5;
	int m_6;
	int m_7;
	int m_8;
	int m_9;
	int m_10;
	int* m_arr[10]{ &m_1, &m_2, &m_3, &m_4, &m_5, &m_6, &m_7, &m_8, &m_9, &m_10 };
	char sub[10][50];
};

struct student {
	char fname[SIZEE];
	char lname[SIZEE];
	char tname[SIZEE];
	int date_of_birth;
	int month_of_birth;
	int year_of_birth;
	int year_of_receipt;
	char faculty[SIZEE];
	char cathedra[SIZEE];
	char group[SIZEE];
	char number_record_book[SIZEE];
	char gender[SIZEE];
	marks sessions[9];
	bool _3 = false;
	bool _4 = false;
	bool _5 = false;
	int ksem;
	int ksub;
};
ofstream fout("data.dat", ios::binary);
ifstream fin("data.dat", ios::binary);
void fill(int n);
void show();
void add();
void change();
void menu1();
void del();
int n_stu, n_sub, n_sem, kolvo = 0;
int s = sizeof(student);
student* st, * temp;

void menu() {
	cout << "Распечатать всех студентов, у которых за все время обучения нет оценок:\n"
		<< "a) 3   б) 3 и 4   в) 5   г) 3 и 5   д) 4 и 5   е) выход.\n";
}

void menu1() {
	cout << "1.Записать студентов\n2.Добавить студента\n3.Показать студентов\n4.Изменить данные студента\n5.Удалить студента\n6.Выход\n";
}

void menu2() {
	cout << "Изменить:\n1.ФИО\n2.Дату рождения\n3.Факультет и Кафедру\n4.Группу\n5.Номер зачетной книжки\n6.Пол\n7.Год поступления\n8.Оценки";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RU");
	menu1();
	char ch;
	while (cin >> ch && ch != '6') {
		switch (ch)
		{
		case '1':
			cout << "Введите кол-во студентов: ";
			while (!(cin >> n_stu) || n_stu > 1000) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
			}
			fill(n_stu);
			cout << endl;
			menu1();
			break;
		case '2':
			add();
			cout << endl;
			menu1();
			break;
		case '3':
			show();
			cout << endl;
			menu1();
			break;
		case '4':
			change();
			cout << endl;
			menu1();
			break;
		case '5':
			del();
			cout << endl;
			menu1();
			break;
		default:
			cout << "Некорректный ввод, попробуйте снова: ";
			break;
		}
	}
	return 0;
}


void fill(int n) {
	for (int i = 0; i < n; ++i) {
		kolvo++;
		st = new student();
		cout << i + 1 << " Cтудент:\n";
		cout << "ФИО: ";
		cin >> st->fname >> st->lname >> st->tname;
		cout << "ДД.ММ.ГГГГ рождения: ";
		cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
		while (!cin) {
			cin.clear();
			cout << "Некорректный ввод, попробуйте снова: ";
			while (cin.get() != '\n')
				continue;
			cout << "ДД.ММ.ГГГГ рождения: ";
			cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
		}
		cout << "Год поступления: ";
		cin >> st->year_of_receipt;
		while (!cin) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "Некорректный ввод, попробуйте снова: ";
			cin >> st->year_of_receipt;
		}
		cout << "Факультет, кафедра: ";
		cin >> st->faculty >> st->cathedra;
		cout << "Группа: ";
		cin >> st->group;
		cout << "Номер зачетной книжки: ";
		cin >> st->number_record_book;
		while (!cin) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "Некорректный ввод, попробуйте снова: ";
			cin >> st->number_record_book;
		}
		cout << "Пол: ";
		cin >> st->gender;

		cout << "Введите кол-во предметов(1-10) и завершенных семестров(1-9): ";
		while (!(cin >> n_sub >> n_sem) || n_sem < 1 || n_sem > 9 || n_sub < 1 || n_sub > 10) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "Некорректный ввод, попробуйте снова: ";
		}
		st->ksem = n_sem;
		st->ksub = n_sub;
		int* already = new int[n_sub];
		int temp, ch, nch = 0;
		for (int j = 0; j < n_sem; ++j) {
			already = new int[n_sub];
			cout << j + 1 << " семестр:\n";
			for (int z = 0; z < 10; ++z)
				cout << z + 1 << "." << subject[z] << endl;
			cout << "Выберите предметы для семестра: ";
			while (nch != n_sub) {
				bool h = false;
				while (!(cin >> ch) || ch < 1 || ch > 10) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
				}
				for (int u = 0; u < nch; ++u) {
					if (already[u] == ch)
						h = true;
				}
				if (!h) {
					strcpy_s(st->sessions[j].sub[nch], subject[ch - 1]);
					already[nch++] = ch;
				}
				else
					cout << "Этот предмет уже выбран\n";
			}
			nch = 0;
			cin.clear();
			while (cin.get() != '\n')
				continue;
			for (int n = 0; n < n_sub; ++n) {
				cout << "Оценка за " << st->sessions[j].sub[n] << ": ";
				while (!(cin >> *(st->sessions[j].m_arr[n])) || *(st->sessions[j].m_arr[n]) < 2 || *(st->sessions[j].m_arr[n]) > 5) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод попробуйте снова: ";
				}
				if (*(st->sessions[j].m_arr[n]) == 3)
					st->_3 = true;
				else if (*(st->sessions[j].m_arr[n]) == 4)
					st->_4 = true;
				else if (*(st->sessions[j].m_arr[n]) == 5)
					st->_5 = true;
			}
		}
		cout << endl;
		fout.seekp(0, ios::end);
		fout.write((char*)&(*st), sizeof(*st));
		delete st;
		delete[] already;
	}
}

void add() {
	st = new student();
	kolvo++;
	cout << "ФИО: ";
	cin >> st->fname >> st->lname >> st->tname;
	cout << "ДД.ММ.ГГГГ рождения: ";
	cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
	while (!cin) {
		cin.clear();
		cout << "Некорректный ввод, попробуйте снова: ";
		while (cin.get() != '\n')
			continue;
		cout << "ДД.ММ.ГГГГ рождения: ";
		cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
	}
	cout << "Год поступления: ";
	cin >> st->year_of_receipt;
	while (!cin) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Некорректный ввод, попробуйте снова: ";
		cin >> st->year_of_receipt;
	}
	cout << "Факультет, кафедра: ";
	cin >> st->faculty >> st->cathedra;
	cout << "Группа: ";
	cin >> st->group;
	cout << "Номер зачетной книжки: ";
	cin >> st->number_record_book;
	while (!cin) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Некорректный ввод, попробуйте снова: ";
		cin >> st->number_record_book;
	}
	cout << "Пол: ";
	cin >> st->gender;
	cout << "Введите кол-во предметов(1-10) и завершенных семестров(1-9): ";
	while (!(cin >> n_sub >> n_sem) || n_sem < 1 || n_sem > 9 || n_sub < 1 || n_sub > 10) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "Некорректный ввод, попробуйте снова: ";
	}
	st->ksem = n_sem;
	st->ksub = n_sub;
	int* already = new int[n_sub];
	int temp, ch, nch = 0;
	for (int j = 0; j < n_sem; ++j) {
		already = new int[n_sub];
		cout << j + 1 << " семестр:\n";
		for (int z = 0; z < 10; ++z)
			cout << z + 1 << "." << subject[z] << endl;
		cout << "Выберите предметы для семестра: ";
		while (nch != n_sub) {
			bool h = false;
			while (!(cin >> ch) || ch < 1 || ch > 10) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cout << "Некорректный ввод, попробуйте снова: ";
			}
			for (int u = 0; u < nch; ++u) {
				if (already[u] == ch)
					h = true;
			}
			if (!h) {
				strcpy_s(st->sessions[j].sub[nch], subject[ch - 1]);
				already[nch++] = ch;
			}
			else
				cout << "Этот предмет уже выбран\n";
		}
		nch = 0;
		cin.clear();
		while (cin.get() != '\n')
			continue;
		for (int n = 0; n < n_sub; ++n) {
			cout << "Оценка за " << st->sessions[j].sub[n] << ": ";
			while (!(cin >> *(st->sessions[j].m_arr[n])) || *(st->sessions[j].m_arr[n]) < 2 || *(st->sessions[j].m_arr[n]) > 5) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cout << "Некорректный ввод попробуйте снова: ";
			}
			if (*(st->sessions[j].m_arr[n]) == 3)
				st->_3 = true;
			else if (*(st->sessions[j].m_arr[n]) == 4)
				st->_4 = true;
			else if (*(st->sessions[j].m_arr[n]) == 5)
				st->_5 = true;

		}
	}
	fout.seekp(0, ios::end);
	fout.write((char*)&(*st), sizeof(*st));
	cout << endl;
	delete[] already;
	delete st;
}

void change() {
	fin.clear();
	fout.clear();
	fin.seekg(0, ios::beg);
	fout.seekp(0, ios::end);
	menu2();
	cout << endl;
	char ch; cin >> ch;
	int kk = 0;
	cout << "Введите фамилию и имя того, кому нужно поменять данные: ";
	char fn[SIZEE], ln[SIZEE]; cin >> fn >> ln;
	int i = 0;
	bool have = false;
	student* temp = new student();
	switch (ch) {
	case'1':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {

			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "Введите новое ФИО: ";
				//cin >> temp->lname >> temp->fname >> temp->tname;
				cin >> temp->fname >> temp->lname >> temp->tname;
				break;
			}
			kk++;
		}
		if (have) {
			fout.seekp(kk * sizeof(*temp), ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
		}
		else
			cout << "Студент не найден.\n";
		break;
	case '2':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "Введите новые ДД.ММ.ГГГГ: ";
				cin >> temp->date_of_birth >> temp->month_of_birth >> temp->year_of_birth;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
					cin >> temp->date_of_birth >> temp->month_of_birth >> temp->year_of_birth;
				}
				break;
			}
			kk++;
		}
		if (have) {
			fout.seekp(kk * sizeof(*temp), ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
		}
		delete temp;
		break;
	case '3':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "Введите новые Факультет и кафедру: ";
				cin >> temp->faculty >> temp->cathedra;
				break;
			}
			kk++;
		}
		if (have) {
			fout.seekp(kk * sizeof(*temp), ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
		}
		else
			cout << "Студент не найден.\n";
		delete temp;
		break;
	case '4':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "Введите новую Группу: ";
				cin >> temp->group;

				break;
			}
			kk++;
		}
		if (have) {
			fout.seekp(kk * sizeof(*temp), ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
		}
		else
			cout << "Студент не найден.\n";
		delete temp;
		break;
	case '5':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {

			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "Введите новый Номер зачетной книжки: ";
				cin >> temp->number_record_book;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
					cin >> temp->number_record_book;
				}
				break;
			}
			kk++;
		}
		if (have) {
			fout.seekp(kk * sizeof(*temp), ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
		}
		else
			cout << "Студент не найден.\n";
		delete temp;
		break;
	case '6':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "Введите новый Пол: ";
				cin >> temp->gender;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
					cin >> temp->gender;
				}
				break;
			}
			kk++;
		}
		if (have) {
			fout.seekp(kk * sizeof(*temp), ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
		}
		else
			cout << "Студент не найден.\n";
		delete temp;
		break;
	case '7':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "Введите новый Год поступления: ";
				cin >> temp->year_of_receipt;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
					cin >> temp->year_of_receipt;
				}
				break;
			}
			kk++;
		}
		if (have) {
			fout.seekp(kk * sizeof(*temp), ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
		}
		else
			cout << "Студент не найден.\n";
		delete temp;
		break;
	case '8':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(fn, temp->fname) == 0 && strcmp(ln, temp->lname) == 0) {
				have = true;

				break;
			}
			kk++;
		}
		if (have) {
			temp->_3 = false;
			temp->_4 = false;
			temp->_5 = false;
			for (int k = 0; k < temp->ksem; ++k) {
				cout << k + 1 << " семестр:\n";
				for (int n = 0; n < temp->ksub; ++n) {
					cout << "Оценка за " << temp->sessions[k].sub[n] << ": ";
					while (!(cin >> *(temp->sessions[k].m_arr[n]))) {
						cin.clear();
						while (cin.get() != '\n')
							continue;
						cout << "Некорректный ввод попробуйте снова: ";
					}
					if (*(temp->sessions[k].m_arr[n]) == 3)
						temp->_3 = true;
					else if (*(temp->sessions[k].m_arr[n]) == 4)
						temp->_4 = true;
					else if (*(temp->sessions[k].m_arr[n]) == 5)
						temp->_5 = true;
				}
			}
			fout.seekp(sizeof(*temp) * kk, ios::beg);
			fout.write((char*)&(*temp), sizeof(*temp));
			cout << endl;
		}
		else
			cout << "Студент не найден.\n";
		delete temp;
		break;
	default:
		cout << "Некорректный ввод, попробуйте снова: ";
		break;

	}
}
void show() {
	if (kolvo > 0) {
		char ch;
		char g[10];
		int i = 0, t;
		int y1, y2;
		menu();
		while (cin >> ch && ch != 'е') {
			st = new student();
			switch (ch)
			{
			case 'а':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "Введите инервал года рождения: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
				}
				cout << "\nСписок стундентов:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_3 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "ФИО:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\nДата рождения: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\nГод поступления: " << st->year_of_receipt <<
							"\nФакультет, кафедра: " << st->faculty << ", " << st->cathedra <<
							"\nГруппа: " << st->group <<
							"\nНомер зачетной книжки: " << st->number_record_book <<
							"\nПол: " << st->gender <<
							"\nТекущий семестр: " << st->ksem + 1 << endl;
						for (int m = 0; m < st->ksem; ++m) {
							for (int n = 0; n < st->ksub; ++n) {
								cout << st->sessions[m].sub[n] << ": " << *st->sessions[m].m_arr[n] << endl;
							}
						}
					}
					cout << endl;
					delete st;
					st = new student();
				}
				menu();
				delete st;
				break;
			case 'б':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "Введите инервал года рождения: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
				}
				cout << "\nСписок стундентов:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_3 == false && st->_4 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "ФИО:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\nДата рождения: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\nГод поступления: " << st->year_of_receipt <<
							"\nФакультет, кафедра: " << st->faculty << ", " << st->cathedra <<
							"\nГруппа: " << st->group <<
							"\nНомер зачетной книжки: " << st->number_record_book <<
							"\nПол: " << st->gender <<
							"\nТекущий семестр: " << st->ksem + 1 << endl;
						for (int m = 0; m < st->ksem; ++m) {
							for (int n = 0; n < st->ksub; ++n) {
								cout << st->sessions[m].sub[n] << ": " << *st->sessions[m].m_arr[n] << endl;
							}
						}
					}
					cout << endl;
					delete st;
					st = new student();
				}
				menu();
				delete st;
				break;
			case 'в':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "Введите инервал года рождения: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
				}
				cout << "\nСписок стундентов:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_5 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "ФИО:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\nДата рождения: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\nГод поступления: " << st->year_of_receipt <<
							"\nФакультет, кафедра: " << st->faculty << ", " << st->cathedra <<
							"\nГруппа: " << st->group <<
							"\nНомер зачетной книжки: " << st->number_record_book <<
							"\nПол: " << st->gender <<
							"\nТекущий семестр: " << st->ksem + 1 << endl;
						for (int m = 0; m < st->ksem; ++m) {
							for (int n = 0; n < st->ksub; ++n) {
								cout << st->sessions[m].sub[n] << ": " << *st->sessions[m].m_arr[n] << endl;
							}
						}
					}
					cout << endl;
					delete st;
					st = new student();
				}
				menu();
				delete st;
				break;
			case 'г':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "Введите инервал года рождения: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
				}
				cout << "\nСписок стундентов:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_3 == false && st->_5 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "ФИО:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\nДата рождения: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\nГод поступления: " << st->year_of_receipt <<
							"\nФакультет, кафедра: " << st->faculty << ", " << st->cathedra <<
							"\nГруппа: " << st->group <<
							"\nНомер зачетной книжки: " << st->number_record_book <<
							"\nПол: " << st->gender <<
							"\nТекущий семестр: " << st->ksem + 1 << endl;
						for (int m = 0; m < st->ksem; ++m) {
							for (int n = 0; n < st->ksub; ++n) {
								cout << st->sessions[m].sub[n] << ": " << *st->sessions[m].m_arr[n] << endl;
							}
						}
					}
					cout << endl;
					delete st;
					st = new student();
				}
				menu();
				delete st;
				break;
			case 'д':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "Введите инервал года рождения: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "Некорректный ввод, попробуйте снова: ";
				}
				cout << "\nСписок стундентов:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_4 == false && st->_5 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "ФИО:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\nДата рождения: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\nГод поступления: " << st->year_of_receipt <<
							"\nФакультет, кафедра: " << st->faculty << ", " << st->cathedra <<
							"\nГруппа: " << st->group <<
							"\nНомер зачетной книжки: " << st->number_record_book <<
							"\nПол: " << st->gender <<
							"\nТекущий семестр: " << st->ksem + 1 << endl;
						for (int m = 0; m < st->ksem; ++m) {
							for (int n = 0; n < st->ksub; ++n) {
								cout << st->sessions[m].sub[n] << ": " << *st->sessions[m].m_arr[n] << endl;
							}
						}
					}
					cout << endl;
					delete st;
					st = new student();
				}
				menu();
				delete st;
				break;
			default:
				delete st;
				cout << "Некорректный ввод, попробуйте снова: ";
				break;
			}
		}
	}
	else
		cout << "Пусто.\n";

}

void del() {

	temp = new student();
	fin.clear();
	fout.clear();
	fout.seekp(0, ios::beg);
	fin.seekg(0, ios::beg);
	char f[SIZEE], l[SIZEE];
	int kk = 0;
	student empty;
	bool have = false;
	cout << "Введите фамилию и имя студента, которого нужно удалить: ";
	cin >> f >> l;
	while (fin.read((char*)&(*temp), sizeof(*temp))) {
		if (strcmp(f, temp->fname) == 0 && strcmp(l, temp->lname) == 0) {
			have = true;
			break;
		}
		kk++;
	}
	if (have) {
		fin.seekg(0, ios::beg);
		fout.seekp(kk * sizeof(*temp), ios::beg);
		fout.write((char*)&empty, sizeof(empty));
	}
	else
		cout << "Такого студента не найдено.\n";
	delete temp;
}