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
	ofstream mesaiYaz2;
	
	void personelEkle(int);
	void maasOde();
	void mesaiEkle();
	int mesaiUcretleri[50];
	string personelMesaiDuzenleme[50];
	int maasGiderleri[50];

};

void Personel::personelEkle(int i) {
	string pAd, pSoyad;
	string pYas, pNo;
	int pSayac = 0;

	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);
	mesaiYaz.open("personelMesai.txt", ios::app);

	cout << "Eklenecek Personel Adi : ";
	cin >> pAd;
	cout << "Eklenecek Personel Soyadi : ";
	cin >> pSoyad;
	cout << "Eklenecek Personel Yasi : ";
	cin >> pYas;
	cout << "Eklenecek Personel No : ";
	cin >> pNo;

	personelYaz << "[" << pNo << "] --> " << pAd << " " + pSoyad << " -- " << pYas << endl;
	mesaiYaz << "[" << pNo << "] --> " << pAd << " " + pSoyad << " -- " << pYas << " -- 0" << endl;

	personelYaz.close();
	personelOku.close();
	mesaiYaz.close();
}


void Personel::mesaiEkle() {
	string pAd, pSoyad, veri;
	int sayac = 0;
	int index, ucret, mesaiSaati, toplamMesai, mesai1, mesaiSecim, satirSayisi = 0;
	string toplamMesaiStr;

	mesaiYaz2.open("personelMesai2.txt", ios::app);
	mesaiYaz.open("personelMesai.txt", ios::app);
	mesaiOku.open("personelMesai.txt", ios::in);
	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);

	if (mesaiOku.is_open()) {
		while (!mesaiOku.eof()) {				// Dosya sonuna ulaþýp ulaþamadýðýný gösteren
			if (sayac % 8 == 0 && sayac != 0) {	// Okurken Alt satýra geçmesi için
				cout << endl;
				satirSayisi++;
			}
			else if ((sayac % 1 == 0 || sayac % 2 == 0 || sayac % 3 == 0 || sayac % 4 == 0 || sayac % 5 == 0 
				|| sayac % 6 == 0 || sayac % 7 == 0) && (sayac != 0)) {									// okurken elemanlar arasýnda boþluk býrakmasý için
				cout << "  ";
			}
			mesaiOku >> veri;
			personelMesaiDuzenleme[sayac] = veri;
			cout << veri;
			sayac++;
		}
	}
	for (int i = 0; i < 10; i++) {
		cout << personelMesaiDuzenleme[i] << endl; //7-15-23-31-39 mesai ücreti yani 7+8xIndis
	}
	cout << "Mesai eklemek istedigin kisinin numarasi : ";
	cin >> index;
	--index;
	cout << "Kac saat mesai eklemek istiyorsunuz ? ";
	cin >> mesaiSaati;
	cout << "Mesai saatlik ucreti : ";
	cin >> ucret;
	
	if (index == 0)
		mesaiSecim = 7;
	else
		mesaiSecim = 7 + (index * 8);

	string strMesai1 = personelMesaiDuzenleme[mesaiSecim];
	mesai1 = stoi(strMesai1);								// String to int
	
	toplamMesai = (mesai1 + (mesaiSaati * ucret));
	
	toplamMesaiStr = to_string(toplamMesai);
	//cout << "Toplam Mesai : " << toplamMesai << endl;
	personelMesaiDuzenleme[mesaiSecim] = toplamMesaiStr;

	/*cout << "strMesai1 : " << strMesai1 << endl;
	cout << "personelMesaiDuzenleme[mesaiSecim] : " << personelMesaiDuzenleme[mesaiSecim] << endl;
	cout << "Mesai1 : " << mesai1 << endl;*/
	for (int i = 0; i < 30; i++) {
		cout << personelMesaiDuzenleme[i] << endl; //7-15-23-31-39 mesai ücreti yani 7+8xIndis
	}
	int satirIndis = 0;
	while (satirIndis < satirSayisi) {
		int diziIndis = 0;

		if (satirIndis == 0)
			diziIndis = 0;
		else if (satirIndis == 1)
			diziIndis = 8;
		else 
			diziIndis = 7 + (satirIndis * 8);
		mesaiYaz2 << personelMesaiDuzenleme[diziIndis] << " " << personelMesaiDuzenleme[diziIndis + 1] << " " << personelMesaiDuzenleme[diziIndis + 2] << " "
				 << personelMesaiDuzenleme[diziIndis + 3] << " " << personelMesaiDuzenleme[diziIndis + 4] << " " << personelMesaiDuzenleme[diziIndis + 5] << " "
			     << personelMesaiDuzenleme[diziIndis + 6] << " " << personelMesaiDuzenleme[diziIndis + 7] << endl;
		satirIndis++;
	}

	
	mesaiYaz2.close();
	mesaiOku.close();
	mesaiYaz.close();
	personelYaz.close();
	personelOku.close();
	remove("personelMesai.txt");
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
			if (sayac % 6 == 0 && sayac != 0) {	// Okurken Alt satýra geçmesi için
				cout << endl;
			}
			else if ((sayac % 1 == 0 || sayac % 2 == 0 || sayac % 3 == 0 || sayac % 4 == 0 || sayac % 5 == 0) && (sayac != 0)) {	// okurken elemanlar arasýnda boþluk býrakmasý için
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