#include <iostream>
#include <fstream>
#include <queue> 
#include <stack> 
#include <string>

using namespace std;
int n = 0;
int cycle = 0;

int in[100];
int start_n = 0;
int out[100];
int stop_n = 0;
int fl = 0;

int start[100];
int stop[100];

int start_v = 0;
int stop_v = 0;

int max_rez = 0;
int crit_rez = 0;
//��������� �������
struct Table
{
	int I;
	int J;
	int TIJ;
	int flag;
	int name = 0;
};
Table table[100];
queue<Table> mytable;
queue<Table> mytableFinal;
Table tableTop;
stack<Table> st;
stack<Table> st1;

//��������� �������
struct Top
{
	int name;
	int flag;
	int tip;
	int tin;
	int pi;
};
Top top[200];
int top_n = 0;

//������� �������� ������� � ������ �� �����
void download()
{
	ifstream File;
	File.open("in.txt", ios::in);
	File >> n;
	for (int i = 0; i < n; i++)
	{
		File >> table[i].I;
		File >> table[i].J;
		File >> table[i].TIJ;
		table[i].flag = 0;
	}

	return;
}

//����� � �������
void dfs(int start, int next, int flag)
{
	if (flag != 0)
	{
		if (start == next)
		{
			cycle = 1;
			return;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (next == table[i].I)
		{
			if (table[i].flag == 0)
			{
				table[i].flag = 1;
				dfs(start, table[i].J, 1);
			}
		}
	}

	return;
}

//������� �������� �� ����� � ���������� ��
int loop()
{
	system("cls");
	cout << "���� ����� ������ � �������..." << endl << endl;
	int flag1 = 0;
	int mass[100];
	for (int i = 0; i < n; i++)
	{
		if (table[i].I == table[i].J)
		{
			flag1 = 1;
			cout<< "������� � ������ " << table[i].I << " " << endl;
		}
	}
	if (flag1 == 1)
	{
		int b = 0;
		cout << endl<< "������� � ������� �������, ������� �����? " << endl << "1 - ��" << endl <<  "����� ����� - ��� � ��������� ������ ���������" << endl << endl;
		cin >> b;
		if (b == 1)
		{
			//�������� ������
			for (int i = 0; i < n; i++)
			{
				if (table[i].I == table[i].J)
				{
					for (int j = i; j < n; j++)
					{
						table[j] = table[j + 1];
					}
					n--;
					i = -1;
				}
			}
			system("cls");
			cout << "����� �������, ����� ���������� ������" << endl << endl;
			system("pause");
			return 0;
		}
		else
		{
			return 1;
		}

	}
	else
	{
		system("cls");
		cout << "����� �� �������, ����� ���������� ������" << endl << endl;
		system("pause");
		return 0;
	}
}

//��������������� ������� ��� ���������� ������ � �������� �����
int cyc_dfs(int mas[], int mas_n, int start, int stop, Table now)
{
	if (start == stop)
	{
		system("cls");
		cout << "���� ������" << endl << endl;
		for (int i = 0; i < mas_n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (mas[i] == table[j].name)
				{
					cout << table[j].I << " " << table[j].J << " " << "����� =" << table[j].name << endl;
				}
			}
		}
		int bb = 0;
		int flagg = 0;
		while (flagg == 0)
		{
			cout <<endl << "����� ������ ���� ����� ������� ����� " << endl << "������� �������� ����� ������� ������ �������" << endl;
			cin >> bb;
			for (int g = 0; g < mas_n; g++)
			{
				if (mas[g] == bb)
				{
					flagg = 1;
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (table[i].name == bb)
			{
				for (int j = i; j < n; j++)
				{
					table[j] = table[j + 1];
				}
				n--;
				i = n;
			}
		}
		system("cls");
		cout << "����� �������, ���� ����� ���������� ������..." << endl << endl;
		system("pause");
		return 1;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (start == table[i].I && table[i].flag == 0)
			{
				mas[mas_n] = table[i].name;
				mas_n++;
				table[i].flag = 1;
				cyc_dfs(mas, mas_n, table[i].J, stop, table[i]);
				table[i].flag = 0;
				mas_n--;
			}
		}
	}
	return 0;
}

//������� ���������� ������ � �������� �����
int cyc()
{
	system("cls");
	cout << "����� �����..." << endl << endl;
	system("pause");
	int mas[100];
	int mas_n = 0;
	int max = 0;

	for (int i = 0; i < n; i++)
	{
		table[i].name = i+1;
	}

	for (int i = 0; i < n; i++)
	{
			mas[mas_n] = table[i].name;
			mas_n++;
			table[i].flag = 1;
			int b = 0;
			b = cyc_dfs(mas, mas_n, table[i].J, table[i].I, table[i]);
			table[i].flag = 0;
			mas_n--;
			if (b == 1)
			{
				i = -1;
				mas_n = 0;
				for (int f = 0; f < n; f++)
				{
					table[f].flag = 0;
				}
			}
	}
	return 0;
}

//������� �������� �� ����� � �����
int cycle_and_loop()
{
	cycle = 0;
	int start = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			table[i].flag = 0;
		}
		start = table[i].I;
		dfs(start, start, 0);
	}

	if (cycle == 1)
	{
		system("cls");
		cout << "� ������ ����� ��������� ����� ��� �����, ���������� �����..." << endl << endl; 
		system("pause");

		//���� ����� � ������� ��
		int g = 0;
		g = loop();
		if (g == 0)
		{
			g = cyc();
			if (g == 0)
			{
				system("cls");
				cout << "� ������ ����� ������ ���� ������ � ������, ����� ���������� ������" << endl << endl;
				system("pause");
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 1;
		}
	}
	else
	{
		system("cls");
		cout << "� ������ ����� ����� �����������, ����� ���������� ������" << endl << endl;
		system("pause");
		return 0;
	}
}

//���������� ��������� � �������� ������ � ���������� ��������� ������ � �����
int start_stop_fikt()
{
	for (int i = 0; i < n; i++)
	{
		in[i] = table[i].I;
		out[i] = table[i].J;
	}

	//���������� ���������
	for (int i = 0; i < n; i++)
	{
		fl = 0;
		for (int j = 0; j < n; j++)
		{
			if (table[i].I == table[j].J)
			{
				fl = 1;
			}
		}
		if (fl == 0)
		{
			start[start_n] = table[i].I;
			start_n++;
		}
	}
	
	//���������� ��������
	for (int i = 0; i < n; i++)
	{
		fl = 0;
		for (int j = 0; j < n; j++)
		{
			if (table[i].J == table[j].I)
			{
				fl = 1;
			}
		}
		if (fl == 0)
		{
			stop[stop_n] = table[i].J;
			stop_n++;
		}
	}

	//������� ���������� �������� �������
	for (int i = 0; i < start_n; i++)
	{
		for (int j = i + 1; j < start_n; j++)
		{
			if (start[i] == start[j])
			{
				for (int g = j; g < start_n; g++)
				{
					start[g] = start[g + 1];
				}
				start_n--;
				j--;
			}
		}
	}

	for (int i = 0; i < stop_n; i++)
	{
		for (int j = i + 1; j < stop_n; j++)
		{
			if (stop[i] == stop[j])
			{
				for (int g = j; g < stop_n; g++)
				{
					stop[g] = stop[g + 1];
				}
				stop_n--;
				j--;
			}
		}

	}

	//���� ����� �� ������ ��������� �������
	if (stop_n != 1 || start_n != 1)
	{
		int a = 0;
		system("cls");
		cout << "���. ��� �����. ������ ������ �����, ������ ��������� ��� ��������� ������ ? " <<endl << "��, ������ - 1 " << endl << "���, ��������� - ����� �����"<< endl << endl;
		cin >> a;
		if (a == 1)
		{
			if (start_n == 1)
			{
				start_v = start[0];
			}
			else
			{
				start_v = -1;
				for (int i = 0; i < start_n; i++)
				{
					table[n].I = start_v;
					table[n].J = start[i];
					table[n].TIJ = 0;
					table[n].flag = 0;
					n++;
				}
			}

			if (stop_n == 1)
			{
				stop_v = stop[0];
			}
			else
			{
				stop_v = -9;
				for (int i = 0; i < stop_n; i++)
				{
					table[n].J = stop_v;
					table[n].I = stop[i];
					table[n].TIJ = 0;
					table[n].flag = 0;
					n++;
				}
			}

			system("cls");
			cout << "��������� ������� ���������, ����� ���������� ������" << endl << endl;
			system("pause");
			return 0;
		}
		else
		{
			system("cls");
			cout << "��������� ������� �� ���������, ����� ������" << endl << endl;
			system("pause");
			return 1;
		}
	}
	else
	{
		system("cls");
		cout << "��������� � �������� ������ �� �����, ����� ���������� ������" << endl << endl;
		start_v = start[0];
		stop_v = stop[0];
		system("pause");
		return 0;
	}
}

//������� ������������ �����
int sort_work()
{
	for (int i = 0; i < n; i++)
	{
		table[i].flag = 0;
	}

	for (int i = 0; i < n; i++)
	{
		if (start_v == table[i].I)
		{
			if (table[i].flag == 0)
			{
				table[i].flag = 1;
				mytable.push(table[i]);
			}
		}
	}

	while (mytable.size() != 0)
	{
		tableTop = mytable.front();
		mytable.pop();
		mytableFinal.push(tableTop);
		for (int i = 0; i < n; i++)
		{
			if (tableTop.J == table[i].I)
			{
				if (table[i].flag == 0)
				{
					table[i].flag = 1;
					mytable.push(table[i]);
				}
			}
		}
	}

	system("cls");
	cout << "���� �������������� �����..." << endl << endl;
	cout << "I  " << "J  " << "TIJ" << endl;
	while (mytableFinal.size() != 0)
	{
		cout << mytableFinal.front().I << "  " << mytableFinal.front().J << "  " << mytableFinal.front().TIJ << "  " << endl;
		mytable.push(mytableFinal.front());
		
		//���������� �� ������� ������
		top[top_n].flag = 0;
		top[top_n].name = mytableFinal.front().I;
		top[top_n].pi = 0;
		top[top_n].tin = 0;
		top[top_n].tip = 0;
		top_n++;

		top[top_n].flag = 0;
		top[top_n].name = mytableFinal.front().J;
		top[top_n].pi = 0;
		top[top_n].tin = 0;
		top[top_n].tip = 0;
		top_n++;

		mytableFinal.pop();
	}

	//�������� ���������� ������
	for (int i = 0; i < top_n; i++)
	{
		for (int j = i + 1; j < top_n; j++)
		{
			if (top[i].name == top[j].name)
			{
				for (int g = j; g < top_n; g++)
				{
					top[g] = top[g + 1];
				}
				top_n--;
				j--;
			}
		}
	}

	cout << endl << endl;
	system("pause");
	return 0;
}

//������� �������� ���������� ������ (������ ��� � �������� ���)
int parametr()
{
	//������
	while (mytable.size() != 0)
	{
		mytableFinal.push(mytable.front());
		st.push(mytable.front());
		
		for (int i = 0; i < top_n; i++)
		{
			if (top[i].name == mytable.front().J)
			{
				int plus;
				for (int j = 0; j < top_n; j++)
				{
					if (top[j].name == mytable.front().I)
					{
						plus = mytable.front().TIJ + top[j].tip;
						if (top[i].tip < plus)
						{
							top[i].tip = plus;
						}
					}
				}
			}
		}

		mytable.pop();
	}

	for (int i = 0; i < top_n; i++)
	{
		if (top[i].name == stop_v)
		{
			top[i].tin = top[i].tip;
		}
	}

	//��������
	while (st.size() != 0)
	{
		for (int i = 0; i < top_n; i++)
		{
			if (top[i].name == st.top().I)
			{
				int plus;
				for (int j = 0; j < top_n; j++)
				{
					if (top[j].name == st.top().J)
					{
						plus = top[j].tin - st.top().TIJ;
						if (top[i].tin > plus)
						{
							top[i].tin = plus;
						}
						if (top[i].tin == 0)
						{
							top[i].tin = plus;
						}
					}
				}
			}
		}

		st.pop();
	}

	//��������� ������
	for (int i = 0; i < top_n; i++)
	{
		top[i].pi = top[i].tin - top[i].tip;
		max_rez = max_rez + top[i].pi;
	}

	//���������� ������������ ���������
	for (int i = 0; i < n; i++)
	{
		if (top[i].name == stop_v)
		{
			crit_rez = top[i].tin;
		}
	}

	system("cls");
	cout << "�������� ���� ������ ����� ������� � ��������� ����" << endl << endl;
	cout << "I   " << "Tip " << "Tin " << "Pi " << endl;
	for (int i = 0; i < top_n; i++)
	{
		cout << top[i].name << "   " << top[i].tip << "   " << top[i].tin << "   " << top[i].pi << endl;
	}

	//cout << endl << endl << "����� ������ = " << max_rez << endl << endl;
	system("pause");
	return 0;
}

//��������������� ������� ��� ���������� ���� �����
void crit_dfs(int mas[], int mas_n, int max, int start, int minus)
{
	if (start == stop_v && max == crit_rez)
	{
		cout << "����������� ���� ������ ( " << max << " )" << endl << endl;
		for (int i = 0; i < mas_n; i++)
		{
			cout << mas[i] << " ";
		}
		cout << stop_v << endl << endl;

		//max = max - minus;
		//mas_n--;
		return;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (start == table[i].I)
			{
				mas[mas_n] = table[i].I;
				mas_n++;
				max = max + table[i].TIJ;
				crit_dfs(mas, mas_n, max, table[i].J, table[i].TIJ);
				mas_n--;
				max = max - table[i].TIJ;
			}
		}
	}
	return;
}

//������� ���������� ����������� �����
int crit()
{
	system("cls");
	cout << "���� ����� ����������� �����..." << endl << endl;
	int mas[100];
	int mas_n = 0;
	int max = 0;

	for (int i = 0; i < n; i++)
	{
		if (start_v == table[i].I)
		{
			mas[mas_n] = table[i].I;
			mas_n++;
			max = max + table[i].TIJ;
			crit_dfs(mas, mas_n, max, table[i].J, table[i].TIJ);
			mas_n--;
			max = max - table[i].TIJ;
		}
		
	}

	system("pause");
	return 0;
}

//������� �������
int main()
{
	setlocale(LC_ALL, "Russian");
	int F = 0;

	download();
	F = cycle_and_loop();
	if (F == 0)
	{
		F = start_stop_fikt();
		if (F == 0)
		{
			F = sort_work();
			if (F == 0)
			{
				F = parametr();
				F = crit();
			}
		}
	}


	system("cls");
	cout << "���������� ��������� ���������" << endl;
	cout << endl;
	system("pause");
	return 0;
}
