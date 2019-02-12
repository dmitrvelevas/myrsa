#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <math.h>
#include <fstream>
#include <windows.h>
#include <cstdlib> 
#include <time.h>
#include <io.h>

using namespace std;

void error_key();
void file_checker(string);
void start_set();
void key_checker(string);
void menu();
void error();
long long d(long long, long long);
long long crypt(long long, long long, long long);
long long china_theory(long long, long long, long long, long long);
void shifr (string, string);
void deshifr (string, string);
void keygen();
long long read(string);
bool simple_num(long long);
long long generator(long long);

int main() 
{ 
	//кодировка begin
	HANDLE hCon = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
    if ( hCon != INVALID_HANDLE_VALUE ) {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize          = sizeof( CONSOLE_FONT_INFOEX );
        cfi.nFont           = 0;
        cfi.dwFontSize.X    = 0;
        cfi.dwFontSize.Y    = 12;
        cfi.FontFamily      = FF_DONTCARE;
        cfi.FontWeight      = 400;
        wcscpy( cfi.FaceName, L"Lucida Console" );
        SetCurrentConsoleFontEx( hCon, FALSE, &cfi );
    }   hCon = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
    if ( hCon != INVALID_HANDLE_VALUE ) {
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize          = sizeof( CONSOLE_FONT_INFOEX );
        cfi.nFont           = 0;
        cfi.dwFontSize.X    = 0;
        cfi.dwFontSize.Y    = 12;
        cfi.FontFamily      = FF_DONTCARE;
        cfi.FontWeight      = 400;
        wcscpy( cfi.FaceName, L"Lucida Console" );
        SetCurrentConsoleFontEx( hCon, FALSE, &cfi );
    }
	SetConsoleCP(1251);            
	SetConsoleOutputCP(1251) ;  
	//кодировка finish
	
	
	
	
	start_set();	
	menu();
	return 0;
}

void file_checker(string file)
	{
		if (access(file.c_str(), 0))
			{
				start_set();
				system("cls");
				cout << "По какой-то причине файл " << file  << " отсутствует. Он создан заново. Введите в него необходимый ключ и продолжите работу, либо сгенерируйте новую пару." << endl << endl;
				menu();
			}
	}

void start_set()
	{
		if (access("Public_key.txt", 0))
			{
				ofstream key;
				key.open("Public_key.txt");
				key << "000000" << " " << "0000000000" << endl;
				key.close();	
			}
			
		if (access("Private_key.txt", 0))
			{
				ofstream key;
				key.open("Private_key.txt");
				key << "000000000000" << " " << "00000000" << " " << "000000000" <<endl;
				key.close();	
			}		
	}
	

void key_checker(string key)
	{
		int c, size=key.length();
		for(int i=0; i<=size-1; ++i)
			{
				c=int(key[i]);
				if (c<48 || c>57)
					{
						system("cls");
						cout << "Неверный формат ключа! Введите корректный ключ и попробуйте снова." << endl << endl;
						menu();
					}
			}
	}

long long generator(long long a)
	{
		if (a%2!=1)
			{
				a=a+1;
			}
		while (simple_num(a)==false)
			{
				a=a+2;
			}
		return a;
	}

void menu()
	{
		while(2)
			{
			//выбор режима
			cout << "Введите" << endl;  
			cout << "0-для генерации новой пары ключей" << endl;
			cout << "1-для начала шифрования" << endl;
			cout << "2-для начала дешифрования" << endl;
			cout << "3-для завершения работы программы" << endl;
			string n;
			int flag;
			getline(cin, n);
			flag=int(n[0])-48;
			if (flag<4 && flag>-1 && int(n[1])==0)
				{
					6;
				}
			else
				{
					flag=100;
				}
		
			switch (flag)
				{
					case 0:
					keygen();
					break;
					
					case 1:
					{
					//___________________проверка ключа	
					file_checker("Public_key.txt");
					
					string go;
					long long e, n;
					ifstream check;
					check.open("Public_key.txt");
					check >> go; 
					if (check.eof()) {error_key();}
					if (go.length()>7) {error_key();}	
					key_checker(go);
					e=read(go);
					check >> go;
					key_checker(go);
					if (check.eof()) {error_key();}
					if (go.length()>15) {error_key();}		
					check.close();
					n=read(go);
					
					if (e==0 || e==1 || n==0 || n==1)
						{
							error_key();
						}
					//__________________________-______
						
					string in_some, out_some;
					
					system("cls");
					cout << "Режим шифрования" << endl<< endl;
					start:;
							cout << "Для возвращения в основное меню введите 3" << endl;
							vvod:;
							cout << "Укажите путь к исходному файлу:" << endl;
							getline(cin, in_some);
							if (int(in_some[0])-48==3 && in_some.length()==1)
								{
									system("cls");
									menu();
								}
							if (access(in_some.c_str(), 0))
								{										
									cout << "Такого файла не существует. " << endl;
									goto vvod;
								}
							else 
								{
									string word;
									ifstream test;
									test.open(in_some.c_str());
									test >> word;
									if (int(word[0])==0)
										{
											test.close();
											cout << "В исходном файле отсутствует текст. " << endl;
											goto start;
										}
									test.close();
								}	
							vivod:;
							cout << "Укажите путь к файлу, в который хотите записать результат:" << endl;
							getline(cin, out_some);
							if (int(out_some[0])-48==3 && out_some.length()==1)
								{
									system("cls");
									menu();
								}
							if (access(out_some.c_str(), 0))
								{										
									cout << "Такого файла не существует. " << endl;
									goto vivod;
								}
							if (in_some==out_some)
								{
									system("cls");
									cout << "Режим шифрования" << endl<< endl;									
									cout << "Вы указали на один и тот же файл, укажите разные файлы." << endl;
									goto start;
								}
					
					shifr (in_some, out_some);
					break;
					}
					
					case 2:
					{
						//___________________проверка ключа	
						file_checker("Private_key.txt");
					
						long long d, p, q;
						
						ifstream key4;
						key4.open("Private_key.txt");
						
						string go;
						
						key4 >> go; 
						if (key4.eof()) {error_key();}
						if (go.length()>15) {error_key();}	
						key_checker(go);
						d=read(go);
						
						key4 >> go;
						if (key4.eof()) {error_key();}
						if (go.length()>7) {error_key();}		
						key_checker(go);
						p=read(go);
						
						key4 >> go;
						if (key4.eof()) {error_key();}
						if (go.length()>7) {error_key();}		
						key_checker(go);
						q=read(go);
							
						key4.close();
						
						
						if (p==0 || p==1 || q==0 || q==1 || d==0)
							{
								error_key();
							}
						//________________________________
							
						string in_some, out_some;
						
						system("cls");
						cout << "Режим дешифрования" << endl<< endl;
						start1:;
								cout << "Для возвращения в основное меню введите 3" << endl;
								vvod1:;
								cout << "Укажите путь к исходному файлу:" << endl;
								getline(cin, in_some);
								if (int(in_some[0])-48==3 && in_some.length()==1)
									{
										system("cls");
										menu();
									}
								if (access(in_some.c_str(), 0))
									{										
										cout << "Такого файла не существует. " << endl;
										goto vvod1;
									}
								else 
									{
										string word;
										ifstream test;
										test.open(in_some.c_str());
										test >> word;
										if (int(word[0])==0)
											{
												test.close();
												cout << "В исходном файле отсутствует текст. " << endl;
												goto start1;
											}
										test.close();
									}	
								vivod1:;
								cout << "Укажите путь к файлу, в который хотите записать результат:" << endl;
								getline(cin, out_some);
								if (int(out_some[0])-48==3 && out_some.length()==1)
									{
										system("cls");
										menu();
									}
								if (access(out_some.c_str(), 0))
									{										
										cout << "Такого файла не существует. " << endl;
										goto vivod1;
									}
								if (in_some==out_some)
									{
										system("cls");
										cout << "Режим дешифрования" << endl<< endl;									
										cout << "Вы указали на один и тот же файл, укажите разные файлы." << endl;
										goto start1;
									}
										
						deshifr(in_some, out_some);
						break;
					}
					
					case 3:
					exit(1);
					break;
					
					default:
					error();
				}
			}
	}
	

void error()
	{
		system("cls");
		cout << "Ошибка ввода! Попробуйте снова." << endl << endl;
		menu();
	}
	
void error_key()
	{
		system("cls");
		cout << "Неверный формат ключа! Введите корректный ключ и попробуйте снова." << endl << endl;
		menu();
	}

bool simple_num(long long n)
	{
		int t=0, i, m, k, f;
		bool flag=false;
		long long s=n-1, a, x;
		while (s%2!=1)
			{
				s=s/2;
				++t;
			}
		k=int(log10(n)/log10(2));
		for (f=0; f<=k; ++f)   //A
		{
			a=1+rand()%(n-3);
			x=crypt(a, s, n);
			if (x==1 || x==(n-1))
				{
					5>2;
				}
			else
				{
					for(m=0; m<=s-1; ++m)
						{
							x=crypt(x, 2, n);
							if (x==1)
								{
									return false;
								}	
							else if (x==n-1)
								{
									m=s;	
								}	
						}
					return false;
				
				}
		}
		return true;
	}
	

int kod(char a)
	{
		if (int(a)<0)
			{
				return (int(a)+400);
			}	
		else
			{
				return (int(a));
			}
	}
	
int dekod(long long a)
	{
		if (a>300)
			{
				return (a-400);
			}	
		else
			{
				return (a);
			}
	}


long long read(string some)
	{
		int num, u, iter, dec=0;
		long long buf=0;
		num=some.length();
		for(iter=num-1; iter>=0; --iter)
			{	
				buf=buf+(int(some[iter])-48)*pow(10, dec);
				++dec;
			}
		return buf;
	}

void keygen()
	{
		srand((unsigned int)time(0));
		//генерация ключей
		long long a, b, t, n, e;
		int size=0, i, g=0;
		e=100000-rand()%40000;
		a=2121555-rand()%600000;
		b=2021655-rand()%600000;
		//cout << a << " " << b << endl;
		//cin >> a >> b >> e;
		e=generator(e);
		a=generator(a);
		b=generator(b);
		long long f=(a-1)*(b-1);
		t=d(f,e);
		n=a*b;
		//запись открытого ключа
		ofstream pub_key;
		pub_key.open("Public_key.txt");
		pub_key << e << " " << n << endl;
		pub_key.close();
		
		////запись секретного ключа
		ofstream priv_key;
		priv_key.open("Private_key.txt");
		priv_key << t << " " << a << " " << b <<endl;
		priv_key.close();
		
		
		system("cls");
		cout << "Ключи сгенерированы, вы можете найти их в файлах Public_key.txt и Private_key.txt" << endl << endl;
	} 

void shifr(string in, string out)
	{
		//считывание ключа
		int u, w, e;
		long long k, buf=0, n;
		string go;
		
		ifstream key;
		key.open("Public_key.txt");
		key >> go; 
		e=read(go);
		key >> go;		
		n=read(go);
		key.close();
		
		ifstream cho;
		cho.open(in.c_str());
		string st;
		long long stroke=0,  per=0;
		while (!cho.eof())
			{
				getline(cho, st);
				stroke=stroke+st.length();
			}
		cho.close();
		
			
		string line;
		ifstream input;
		input.open(in.c_str());
		
		ofstream output;
		output.open(out.c_str());
			while (!input.eof())
					{
						getline(input, line);
						w=line.length();
													
						for (int u=0; u<=w; u++)
							{
								
								//_________
								++per;
								if ((per-1)*100/stroke<per*100/stroke)
								{
									system("cls");
									cout << "Выполнено " << per*100/stroke << "%";
								}
								
								//_________
								
								buf=kod(line[u]);
								k=crypt(buf, e, n);
								output << k << " ";
							}
					} 
		input.close();
		output.close();
		system("cls");
		cout << "Процесс шифрования окончен, результат вы можете найти в файле " << out << endl << endl;
	}
	
void deshifr (string in, string out)
	{	
		int dec, size, iter;
		long long buf, k, n, d, e, p, q;
		
		string go;
		
		ifstream key;
		key.open("Private_key.txt");
		
		key >> go; 	
		d=read(go);
		
		key >> go;
		p=read(go);
		
		key >> go;
		q=read(go);
			
		key.close();
		
		ifstream cho;
		cho.open(in.c_str());
		string st;
		long long stroke=0,  per=0;
		while (!cho.eof())
			{
				cho>>st;
				stroke=stroke+1;
			}
		cho.close();
		
		string word;
		ifstream input;
		input.open(in.c_str());
		ofstream output;
		output.open(out.c_str());
		while (!input.eof())
				{	
					dec=0;		
					buf=0;					
					input >> word;
				
					++per;
					if ((per-1)*100/stroke<per*100/stroke)
						{
							system("cls");
							cout <<"Выполнено " << per*100/stroke << "%";
						}			
				
					size=word.length();
					for(iter=size-1; iter>=0; --iter)
						{	
							
							if (int(word[iter])>57 || int(word[iter])<48)
							{
								system("cls");
								cout << "В исходном тексте для дешифрования найдены буквенные символы. Процесс прерван. Часть результата сохранена в " << out << endl << endl;
								input.close();
								output.close();
								menu();
								
							}
							buf=buf+(int(word[iter])-48)*(pow(10, dec));
							++dec;
							
							
						}
					//cout << buf << endl;
					//crypt(buf, d, n);
					k=china_theory(buf, d, p, q);
					//cout << char(dekod(k));
					//cout << k;
					output << char(dekod(k));	
				}
		cout << endl;
		input.close();
		output.close();

		system("cls");
		cout << "Процесс дешифрования окончен, результат вы можете найти в файле " << out << endl;
	}	

long long crypt(long long m, long long e, long long n)
	{
		long long c=1;
		for (int not_e=1; not_e<=e; ++not_e)
			{	
				c=(c*m)%n;
			}
		return c;
	}


long long d(long long a, long long b)
	{
		bool flag=1;
		long long z=a;
		long long r, q, a11, a12, a21, a22, x11, x12, x21, x22, zero;
		a11=1;
		a12=0;
		a21=0;
		a22=1;
		zero=0;
		while (flag==1)
		{
			r=a%b;
			q=a/b;
			if (r<=0)
				{
					flag=0;
					return z+a22;
				}
			 else
			 	{
			 		x11=a12;
			 		x21=a22;
			 		x12=a11+a12*(-1)*q;
			 		x22=a21*1+a22*(-1)*q;
			 		
			 		a11=x11;
			 		a12=x12;
			 		a21=x21;
			 		a22=x22;
			 		
			 		a=b;
			 		b=r;
			 		
			}
		}
	}
		
long long china_theory(long long c, long long priv, long long p, long long q)
	{
		long long d_p, d_q, q_inv, m1, m2, h, m;
		d_p=priv%(p-1);
		d_q=priv%(q-1);
		q_inv=d(p, q);
		m1=crypt(c, d_p, p);
		m2=crypt(c, d_q, q);
		h=((m1-m2)*q_inv)%p;
		m=m2+h*q;
		return abs(m);
	}




