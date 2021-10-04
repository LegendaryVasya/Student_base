#include<iostream>
#include<cstring>
#include<cctype>
#include<fstream>
#include<ctime>
#include<Windows.h>
using namespace std;

const int SIZEE = 20;
const char* subject[]{ "�������������� ������", "������", "�������� ������� � ������������� ���������", "����� ����������������",
"������ �������������� ������������", "������ ��������� ����������", "�����������", "����������� �����", "������������", "�������� � ���������������� ������������" };

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
	cout << "����������� ���� ���������, � ������� �� ��� ����� �������� ��� ������:\n"
		<< "a) 3   �) 3 � 4   �) 5   �) 3 � 5   �) 4 � 5   �) �����.\n";
}

void menu1() {
	cout << "1.�������� ���������\n2.�������� ��������\n3.�������� ���������\n4.�������� ������ ��������\n5.������� ��������\n6.�����\n";
}

void menu2() {
	cout << "��������:\n1.���\n2.���� ��������\n3.��������� � �������\n4.������\n5.����� �������� ������\n6.���\n7.��� �����������\n8.������";
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
			cout << "������� ���-�� ���������: ";
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
			cout << "������������ ����, ���������� �����: ";
			break;
		}
	}
	return 0;
}


void fill(int n) {
	for (int i = 0; i < n; ++i) {
		kolvo++;
		st = new student();
		cout << i + 1 << " C������:\n";
		cout << "���: ";
		cin >> st->fname >> st->lname >> st->tname;
		cout << "��.��.���� ��������: ";
		cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
		while (!cin) {
			cin.clear();
			cout << "������������ ����, ���������� �����: ";
			while (cin.get() != '\n')
				continue;
			cout << "��.��.���� ��������: ";
			cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
		}
		cout << "��� �����������: ";
		cin >> st->year_of_receipt;
		while (!cin) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "������������ ����, ���������� �����: ";
			cin >> st->year_of_receipt;
		}
		cout << "���������, �������: ";
		cin >> st->faculty >> st->cathedra;
		cout << "������: ";
		cin >> st->group;
		cout << "����� �������� ������: ";
		cin >> st->number_record_book;
		while (!cin) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "������������ ����, ���������� �����: ";
			cin >> st->number_record_book;
		}
		cout << "���: ";
		cin >> st->gender;

		cout << "������� ���-�� ���������(1-10) � ����������� ���������(1-9): ";
		while (!(cin >> n_sub >> n_sem) || n_sem < 1 || n_sem > 9 || n_sub < 1 || n_sub > 10) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "������������ ����, ���������� �����: ";
		}
		st->ksem = n_sem;
		st->ksub = n_sub;
		int* already = new int[n_sub];
		int temp, ch, nch = 0;
		for (int j = 0; j < n_sem; ++j) {
			already = new int[n_sub];
			cout << j + 1 << " �������:\n";
			for (int z = 0; z < 10; ++z)
				cout << z + 1 << "." << subject[z] << endl;
			cout << "�������� �������� ��� ��������: ";
			while (nch != n_sub) {
				bool h = false;
				while (!(cin >> ch) || ch < 1 || ch > 10) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
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
					cout << "���� ������� ��� ������\n";
			}
			nch = 0;
			cin.clear();
			while (cin.get() != '\n')
				continue;
			for (int n = 0; n < n_sub; ++n) {
				cout << "������ �� " << st->sessions[j].sub[n] << ": ";
				while (!(cin >> *(st->sessions[j].m_arr[n])) || *(st->sessions[j].m_arr[n]) < 2 || *(st->sessions[j].m_arr[n]) > 5) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ���� ���������� �����: ";
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
	cout << "���: ";
	cin >> st->fname >> st->lname >> st->tname;
	cout << "��.��.���� ��������: ";
	cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
	while (!cin) {
		cin.clear();
		cout << "������������ ����, ���������� �����: ";
		while (cin.get() != '\n')
			continue;
		cout << "��.��.���� ��������: ";
		cin >> st->date_of_birth >> st->month_of_birth >> st->year_of_birth;
	}
	cout << "��� �����������: ";
	cin >> st->year_of_receipt;
	while (!cin) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "������������ ����, ���������� �����: ";
		cin >> st->year_of_receipt;
	}
	cout << "���������, �������: ";
	cin >> st->faculty >> st->cathedra;
	cout << "������: ";
	cin >> st->group;
	cout << "����� �������� ������: ";
	cin >> st->number_record_book;
	while (!cin) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "������������ ����, ���������� �����: ";
		cin >> st->number_record_book;
	}
	cout << "���: ";
	cin >> st->gender;
	cout << "������� ���-�� ���������(1-10) � ����������� ���������(1-9): ";
	while (!(cin >> n_sub >> n_sem) || n_sem < 1 || n_sem > 9 || n_sub < 1 || n_sub > 10) {
		cin.clear();
		while (cin.get() != '\n')
			continue;
		cout << "������������ ����, ���������� �����: ";
	}
	st->ksem = n_sem;
	st->ksub = n_sub;
	int* already = new int[n_sub];
	int temp, ch, nch = 0;
	for (int j = 0; j < n_sem; ++j) {
		already = new int[n_sub];
		cout << j + 1 << " �������:\n";
		for (int z = 0; z < 10; ++z)
			cout << z + 1 << "." << subject[z] << endl;
		cout << "�������� �������� ��� ��������: ";
		while (nch != n_sub) {
			bool h = false;
			while (!(cin >> ch) || ch < 1 || ch > 10) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cout << "������������ ����, ���������� �����: ";
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
				cout << "���� ������� ��� ������\n";
		}
		nch = 0;
		cin.clear();
		while (cin.get() != '\n')
			continue;
		for (int n = 0; n < n_sub; ++n) {
			cout << "������ �� " << st->sessions[j].sub[n] << ": ";
			while (!(cin >> *(st->sessions[j].m_arr[n])) || *(st->sessions[j].m_arr[n]) < 2 || *(st->sessions[j].m_arr[n]) > 5) {
				cin.clear();
				while (cin.get() != '\n')
					continue;
				cout << "������������ ���� ���������� �����: ";
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
	cout << "������� ������� � ��� ����, ���� ����� �������� ������: ";
	char fn[SIZEE], ln[SIZEE]; cin >> fn >> ln;
	int i = 0;
	bool have = false;
	student* temp = new student();
	switch (ch) {
	case'1':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {

			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "������� ����� ���: ";
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
			cout << "������� �� ������.\n";
		break;
	case '2':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "������� ����� ��.��.����: ";
				cin >> temp->date_of_birth >> temp->month_of_birth >> temp->year_of_birth;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
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
				cout << "������� ����� ��������� � �������: ";
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
			cout << "������� �� ������.\n";
		delete temp;
		break;
	case '4':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "������� ����� ������: ";
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
			cout << "������� �� ������.\n";
		delete temp;
		break;
	case '5':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {

			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "������� ����� ����� �������� ������: ";
				cin >> temp->number_record_book;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
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
			cout << "������� �� ������.\n";
		delete temp;
		break;
	case '6':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "������� ����� ���: ";
				cin >> temp->gender;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
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
			cout << "������� �� ������.\n";
		delete temp;
		break;
	case '7':
		while (fin.read((char*)&(*temp), sizeof(*temp))) {
			if (strcmp(temp->fname, fn) == 0 && strcmp(temp->lname, ln) == 0) {
				have = true;
				cout << "������� ����� ��� �����������: ";
				cin >> temp->year_of_receipt;
				while (!cin) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
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
			cout << "������� �� ������.\n";
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
				cout << k + 1 << " �������:\n";
				for (int n = 0; n < temp->ksub; ++n) {
					cout << "������ �� " << temp->sessions[k].sub[n] << ": ";
					while (!(cin >> *(temp->sessions[k].m_arr[n]))) {
						cin.clear();
						while (cin.get() != '\n')
							continue;
						cout << "������������ ���� ���������� �����: ";
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
			cout << "������� �� ������.\n";
		delete temp;
		break;
	default:
		cout << "������������ ����, ���������� �����: ";
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
		while (cin >> ch && ch != '�') {
			st = new student();
			switch (ch)
			{
			case '�':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "������� ������� ���� ��������: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
				}
				cout << "\n������ ����������:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_3 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "���:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\n���� ��������: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\n��� �����������: " << st->year_of_receipt <<
							"\n���������, �������: " << st->faculty << ", " << st->cathedra <<
							"\n������: " << st->group <<
							"\n����� �������� ������: " << st->number_record_book <<
							"\n���: " << st->gender <<
							"\n������� �������: " << st->ksem + 1 << endl;
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
			case '�':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "������� ������� ���� ��������: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
				}
				cout << "\n������ ����������:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_3 == false && st->_4 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "���:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\n���� ��������: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\n��� �����������: " << st->year_of_receipt <<
							"\n���������, �������: " << st->faculty << ", " << st->cathedra <<
							"\n������: " << st->group <<
							"\n����� �������� ������: " << st->number_record_book <<
							"\n���: " << st->gender <<
							"\n������� �������: " << st->ksem + 1 << endl;
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
			case '�':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "������� ������� ���� ��������: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
				}
				cout << "\n������ ����������:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_5 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "���:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\n���� ��������: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\n��� �����������: " << st->year_of_receipt <<
							"\n���������, �������: " << st->faculty << ", " << st->cathedra <<
							"\n������: " << st->group <<
							"\n����� �������� ������: " << st->number_record_book <<
							"\n���: " << st->gender <<
							"\n������� �������: " << st->ksem + 1 << endl;
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
			case '�':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "������� ������� ���� ��������: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
				}
				cout << "\n������ ����������:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_3 == false && st->_5 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "���:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\n���� ��������: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\n��� �����������: " << st->year_of_receipt <<
							"\n���������, �������: " << st->faculty << ", " << st->cathedra <<
							"\n������: " << st->group <<
							"\n����� �������� ������: " << st->number_record_book <<
							"\n���: " << st->gender <<
							"\n������� �������: " << st->ksem + 1 << endl;
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
			case '�':
				cin.get();
				fin.clear();
				fout.clear();
				fout.seekp(0, ios::beg);
				fin.seekg(0, ios::beg);
				i = 0;
				cout << "������� ������� ���� ��������: ";
				while (!(cin >> y1 >> y2)) {
					cin.clear();
					while (cin.get() != '\n')
						continue;
					cout << "������������ ����, ���������� �����: ";
				}
				cout << "\n������ ����������:\n";
				while (fin.read((char*)&(*st), sizeof(*st))) {
					if (st->_4 == false && st->_5 == false && st->year_of_birth >= y1 && st->year_of_birth <= y2) {
						cout << ++i << ": " << endl;
						cout << "���:" << st->fname << ' ' << st->lname << ' ' << st->tname <<
							"\n���� ��������: " << st->date_of_birth << '.' << st->month_of_birth << '.' << st->year_of_birth <<
							"\n��� �����������: " << st->year_of_receipt <<
							"\n���������, �������: " << st->faculty << ", " << st->cathedra <<
							"\n������: " << st->group <<
							"\n����� �������� ������: " << st->number_record_book <<
							"\n���: " << st->gender <<
							"\n������� �������: " << st->ksem + 1 << endl;
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
				cout << "������������ ����, ���������� �����: ";
				break;
			}
		}
	}
	else
		cout << "�����.\n";

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
	cout << "������� ������� � ��� ��������, �������� ����� �������: ";
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
		cout << "������ �������� �� �������.\n";
	delete temp;
}