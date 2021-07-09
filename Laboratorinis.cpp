#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

int Sudetis(int a, int b);
int Sandauga(int a, int b);

int main(int argc, char *argv[]) {
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int ats;

	ofstream fout;
	fout.open("rezultatai.csv");
	fout<<"\n,,3 Laboratorinis darbas\n";
	fout<<",,Agniete Margeviciute PRIF-20/3\n\n\n";
	fout<<",Pradiniai duomenys:\n\n";
	fout<<",a = "<<a<<" ir b = "<<b<<endl<<endl;

	///Sekos,
	fout<<"\n,Logines sekos:\n\n";
	
	fout<<",Seka XOR - 1 \n";
	fout<<",(NOT(A) AND B) OR (A AND NOT(B)) \n";
	ats = (~a & b) | (a & ~b);
	fout<<",Rezultatas: "<<ats<<endl<<endl;

	fout<<",Seka XOR - 2 \n";
	fout<<",(A OR B) AND NOT(A AND B) \n";
	ats = (a | b) & ~(a & b);
	fout<<",Rezultatas: "<<ats<<endl<<endl;

	fout<<", Seka XOR - 3 \n";
	fout<<",(A OR B) AND (NOT(A) OR NOT(B)) \n";
	ats = (a | b) & ~(a & b);
	fout<<",Rezultatas: "<<ats<<endl<<endl;

	fout<<",Seka XOR - 4 \n";
	fout<<",NOT(A AND (NOT(A AND B))) AND (B AND (NOT(A AND B))))\n";
	ats = ~(~(a & ~(a&b)) & ~(b & ~(a&b)));
	fout<<",Rezultatas: "<<ats<<endl<<endl;

	///sudetis
	fout<<"\n,Rezultatai:\n\n";
	
	int suma = Sudetis(a,b);
	fout<<",Skaiciu suma:\n,a + b = "<<suma<<endl;

	///daugyba
	int sand = Sandauga(a,b);
	fout<<"\n,Skaiciu sandauga:\n,a * b = "<<sand<<endl;
	
}


int Sudetis(int a, int b) {
	unsigned int max;
	bool liekana = false;
	vector<int> galutinis;

	if(a > b) max = a;
	else max = b;

	int dydis = (int)log2(max)+1;	///Foro pabaigai skirtas skaicius(didesnio dvejetainio skaiciaus dydis)
									///Ar galima butu naudoti : int dydis = (int)log2(a+b)+1; kad rasti tikslu atsakymo dvejetainio skaiciaus kieki.

	for(int i = 0; i < dydis*2; i++) {
		int sk1, sk2;
		sk1 = a & 0b1;
		sk2 = b & 0b1;
		a = a >> 1;
		b = b >> 1;

		if(sk1 == 1 && sk2 == 1) {
			if(liekana) {
				galutinis.insert(galutinis.begin(),1);
				liekana = true;
			} else {
				galutinis.insert(galutinis.begin(),0);
				liekana = true;
			}
		}

		else if((sk1 == 1 && sk2 == 0) || (sk1 == 0 && sk2 == 1)) {
			if(liekana) {
				galutinis.insert(galutinis.begin(),0);
				liekana = true;
			} else {
				galutinis.insert(galutinis.begin(),1);
				liekana = false;
			}
		}

		else if(sk1 == 0 && sk2 == 0) {
			if(liekana) {
				galutinis.insert(galutinis.begin(),1);
				liekana = false;
			} else {
				galutinis.insert(galutinis.begin(),0);
				liekana = false;
			}
		}
	}
	
	string dvejetainisSk;
	for(int i = 0; i < galutinis.size(); i++) {	/// vector to string
		dvejetainisSk = dvejetainisSk + to_string(galutinis[i]);		/// paverciu vector i string, kad galeciau po to naudoti stoi() funkcija
	}
	
	int ats;
	ats = stoi(dvejetainisSk, nullptr, 2); ///string to int pavertimas
	return ats;
}

int Sandauga(int a, int b)
{
	int ats = 0;
	while (b != 0) {				/// Ciklas vyks kol b netaps 0
		if (b & 1) {				/// Perskaitomas bitas ir vykdoma veiksmas tik su vienetu
			ats = Sudetis(a, ats); 
		}
		a <<= 1;    				/// Pajudama i kaire ir padauginama is dvieju 
		b >>= 1;        			/// Pajudama i desine ir padalinama is dvieju iki sveiko skaiciaus
	}
	return ats;
}
