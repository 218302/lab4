#include <iostream>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;



unsigned long long search_k(int number);
unsigned long long convert_table_to_number(bool* numbers_digits, int number_of_digits);
string write_number(unsigned long long number);



int main (int argc, char* argv[])
{

// Obsluga bledow (error code'y na dole pliku).

	if(argc!=2)
	{
		cout << "Incorrect number of arguments. Exiting..." << endl;
		exit(1);
	}
	int number=atoi(argv[1]);
	if((strcmp(argv[1],"0") && number==0) || (strcmp(argv[1], to_string(number).c_str())))
	{
		cout << "Incorrect argument. Exiting..." << endl;
		exit(2);
	}
	if(number<0 || number>999999)
	{
		cout << "Number out of range. Exiting..." << endl;
		exit(3);
	}

// Wlasciwy program.

	unsigned long long k=search_k(number);
	cout << "The lowest (different than zero) 'k' number matching the conditions is " << k << " (in polish: " << write_number(k) << ") and it's product is " << k*number << " (in polish: " << write_number(k*number) << ")." << endl;



	return 0;
}



unsigned long long search_k(int number)
{
	bool found_solution=false;
	bitset<20> binary_number(1);
	string binary_number_str;
	unsigned long long k;

// Sprawdzanie kolejnych liczb zlozonych z samych zer i jedynek pod katem podzielnosci przez zadana liczbe.

	do
	{
		binary_number_str=binary_number.to_string();
		k=stoull(binary_number_str);
		if(k%number==0)
		{
			found_solution=true;
		}
		else
		{
			for(size_t i=0; i<20; i++)
			{
				if(binary_number[i]==0)
				{
					binary_number[i]=1;
					break;
				}
				binary_number[i]=0;
			}
		}
	} while(!found_solution && k!=11111111111111111111);
	if(!found_solution)
	{
		cout << "Reached minimum 'unsigned long long' variable limit (18'446'744'073'709'551'615) before number's multiple matching the conditions was found. Exiting..." << endl;
		exit(4);
	}
	k=k/number;



	return k;
}

unsigned long long convert_table_to_number(bool* numbers_digits, int number_of_digits)
{
	unsigned long long j=1, number=0;
	for(int i=0; i<number_of_digits; i++)
	{
		number=number+(j*numbers_digits[i]);
		j=j*10;
	}



	return number;
}

string write_number(unsigned long long number)
{
	if(number>999999)
		return "Liczba spoza zakresu dostępnych liczebników";
	string unities[10]={"zero ", "jeden ", "dwa ", "trzy ", "cztery ", "pięć ", "sześć ", "siedem ", "osiem ", "dziewięć "};
	string teens[10]={"dziesięć ", "jedenaście ", "dwanaście ", "trzynaście ", "czternaście ", "piętnaście ", "szesnaście ", "siedemnaście ", "osiemnaście ", "dziewiętnaście "};
	string dozens[8]={"dwadzieścia ", "trzydzieści ", "czterdzieści ", "pięćdziesiąt ", "sześćdziesiąt ", "siedemdziesiąt ", "osiemdziesiąt ", "dziewięćdziesiąt "};
	string hundreds[9]={"sto ", "dwieście ", "trzysta ", "czterysta ", "pięćset ", "sześćset ", "siedemset ", "osiemset ", "dziewięćset "};
	string thousands[3]={"tysiąc ", "tysiące ", "tysięcy "};
	string number_in_words;

// Sprawdzenie ilosci cyfr.

	int digits=1;
	for(int i=10; number/i!=0; i=10*i)
		digits++;

// Wczytywanie kolejnych cyfr do tablicy (od konca).

	int* single_digits=new int[digits];
	for(int i=0; i<digits; i++)
	{
		single_digits[i]=number%10;
		number=number/10;
	}

// Generowanie napisu.

	if(digits==1 && single_digits[0]==0)
		number_in_words=unities[0];
	else
	{
		int move_positions;
		bool skip_unities, loop_done=false;
		do
		{
			move_positions=0;
			skip_unities=false;
			if(digits>3 && number_in_words.empty())
				move_positions=3;
			if((digits%3==0 || loop_done) && single_digits[2+move_positions]!=0)
				number_in_words.append(hundreds[single_digits[2+move_positions]-1]);
			if((digits%3!=1 || loop_done) && single_digits[1+move_positions]!=1 && single_digits[1+move_positions]!=0)
				number_in_words.append(dozens[single_digits[1+move_positions]-2]);
			if((digits%3!=1 || loop_done) && single_digits[1+move_positions]==1)
			{
				number_in_words.append(teens[single_digits[move_positions]]);
				skip_unities=true;
			}
			if(!skip_unities)
				number_in_words.append(unities[single_digits[move_positions]]);
			if((digits>4 && !loop_done) || (digits>3 && !loop_done && single_digits[3]>4))
				number_in_words.append(thousands[2]);
			if(digits>3 && !loop_done && single_digits[3]<4 && single_digits[3]>1)
				number_in_words.append(thousands[1]);
			if(digits==4 && !loop_done && single_digits[3]==1)
				number_in_words.append(thousands[0]);
			loop_done=true;
		} while(move_positions);
	}
	number_in_words=number_in_words.substr(0,number_in_words.length()-1);



	delete[] single_digits;

	return number_in_words;
}

/*
Error codes:
0 - OK
1 - Incorrect number of arguments
2 - Incorrect argument
3 - Number out of range
4 - Reached minimum 'unsigned long long' variable limit (18446744073709551615) before number's multiple matching the conditions was found
*/