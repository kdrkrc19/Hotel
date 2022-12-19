#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

class Personel {
public:
	friend class Muhasebe;
	//Personel();
	ifstream personelOku;
	ofstream personelYaz;
	ifstream mesaiOku;
	ofstream mesaiYaz;
	
	void personelEkle(int);
	void maasOde();
	void mesaiEkle();
	int mesaiUcretleri[50];
	string personeller[50];
	int maasGiderleri[50];

};

void Personel::personelEkle(int i) {
	string pAd, pSoyad;
	string pYas, pNo;
	int pSayac = 0;

	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);

	cout << "Eklenecek Personel Adi : ";
	cin >> pAd;
	cout << "Eklenecek Personel Soyadi : ";
	cin >> pSoyad;
	cout << "Eklenecek Personel Yasi : ";
	cin >> pYas;
	cout << "Eklenecek Personel No : ";
	cin >> pNo;
	personelYaz << "[" << pNo << "] --> " << pAd << " " + pSoyad << " -- " << pYas << endl;
	mesaiUcretleri[i] = 0;
	personelYaz.close();
	personelOku.close();
}


void Personel::mesaiEkle() {
	string pAd, pSoyad, veri;
	int sayac = 0;
	int mesaiSaati;
	int index;
	int ucret;

	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);

	if (personelOku.is_open()) {
		while (!personelOku.eof()) {
			if (sayac % 6 == 0 & sayac != 0) {	// Okurken Alt satýra geçmesi için
				cout << endl;
			}
			else if ((sayac % 1 == 0 || sayac % 2 == 0 || sayac % 3 == 0 || sayac % 4 == 0 || sayac % 5 == 0) & (sayac != 0)) {	// okurken elemanlar arasýnda boþluk býrakmasý için
				cout << "  ";
			}
			personelOku >> veri;
			cout << veri;
			sayac++;
		}
	}
	cout << "Mesai eklemek istedigin kisinin numarasi : ";
	cin >> index;
	--index;
	cout << "Kac saat mesai eklemek istiyorsunuz ? ";
	cin >> mesaiSaati;
	cout << "Mesai saatlik ucreti : ";
	cin >> ucret;
	mesaiUcretleri[index] = (mesaiUcretleri[index] + (mesaiSaati* ucret));

	for (int i = 0; mesaiUcretleri[i] != -858993460; i++)
	{
		cout << (personeller[i]) << " - " << mesaiUcretleri[i] << " tl" << endl;
	}
	personelYaz.close();
	personelOku.close();
}


void Personel::maasOde() {
	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);
	int sayac = 0;
	string veri;
	int pNo;
	double odenenTutar = 0;
	if (personelOku.is_open()) {
		while (!personelOku.eof()) {
			if (sayac % 6 == 0 & sayac != 0) {	// Okurken Alt satýra geçmesi için
				cout << endl;
			}
			else if ((sayac % 1 == 0 || sayac % 2 == 0 || sayac % 3 == 0 || sayac % 4 == 0 || sayac % 5 == 0) & (sayac != 0)) {	// okurken elemanlar arasýnda boþluk býrakmasý için
				cout << "  ";
			}
			personelOku >> veri;
			cout << veri;
			sayac++;
		}
	}
	cout << "Maas Odenecek Personel No : ";
	cin >> pNo;
	cout << "Personelin Mesai Ucreti : "; 
	cout << mesaiUcretleri[pNo - 1] << endl;
	cout << "Ne Kadar Odensin ? ";
	cin >> odenenTutar;
//	maasGiderleri[pNo] = odenenTutar;
	personelYaz.close();
	personelOku.close();
}

class Muhasebe {
public:
	int personelMaas;
	int personelEkMesai;
};


int main() {
	Personel p;
	bool switchDevamMi = true;
	int secim;
	int sayac = 0;


	while (switchDevamMi) {
		cout << "Yapmak Istediginiz Islemi Secin"
			<< endl << "1 - Personel Ekle"
			<< endl << "2 - Personel Mesai Ekle"
			<< endl << "3 - Personel Maas Ode"
			<< endl << "9 - Cikis"
			<< endl;
 
		cin >> secim;

		switch (secim)
		{
		case 1:
			p.personelEkle(sayac);
			sayac++;
			break;
		case 2:
			p.mesaiEkle();
			break;
		case 3:
			p.maasOde();
			break;
		case 9:
			switchDevamMi = false;
			break;
		default:
			cout << "Lutfen gecerli bir islem secin" << endl;
			break;
		}
	}
	
}