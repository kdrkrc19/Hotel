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
	ifstream personelOku2;
	ofstream personelYaz2;

	void personelEkle();
	void maasOde();
	void mesaiEkle();
	int mesaiUcretleri[500];
	string personelMesaiDuzenleme[500];
	string personelMaaslari[500];
	string personelMaaslari2[500];
	int maasGiderleri[500];

};

void Personel::personelEkle() {
	string pAd, pSoyad, pYas, pNo;

	cout << "Eklenecek Personel Adi : ";
	cin >> pAd;
	cout << "Eklenecek Personel Soyadi : ";
	cin >> pSoyad;
	cout << "Eklenecek Personel Yasi : ";
	cin >> pYas;
	cout << "Eklenecek Personel No : ";
	cin >> pNo;

	// ------------------------------------------------------------- // Dosya Tanýmlama Ýþlemleri

	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);

	// ------------------------------------------------------------- // Dosyaya Yazma Ýþlemleri

	personelYaz2.open(pAd + pSoyad + ".txt", ios::app);

	personelYaz2 << pAd << " " + pSoyad << endl << "--------------------------" << endl << "PersonelNo:" << pNo << endl 
		         << "PersonelYas:" << pYas << endl << "PersonelMesaiUcreti:" << "0" << endl << "--------------------------" << endl;
	personelYaz <<  pAd << " " + pSoyad << endl;

	personelYaz2.close();
	personelYaz.close();
	personelOku.close();
}


void Personel::mesaiEkle() {
	string pAd, pSoyad, veri, toplamMesaiStr;
	int sayac = 0;
	int index, ucret, mesaiSaati, toplamMesai, mesaiSecim, adSoyadSecim, satirSayisi = 0;


	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);


	// ------------------------------------------------------------- // Personel Ad Soyadlarý Diziye Alýnýyor
	if (personelOku.is_open()) {
		while (!personelOku.eof()) {								// Dosya sonuna ulaþýp ulaþamadýðýný gösterir
			personelOku >> veri;
			personelMesaiDuzenleme[sayac] = veri;
			sayac++;
		}
	}
	sayac--;	// eleman sayýsý ve sayac ayný ama index olarak kullanmak istediðimiz için -- yaptýk

	// ------------------------------------------------------------- // Personel Ad Soyadlarý Ekrana Basýlýyor
	for (int i = 0; i < sayac; i++) {
		if ((i % 2 == 0) && (i != 0))
			cout << endl;
		cout << personelMesaiDuzenleme[i] << " ";
	}
	cout << endl;

	// ------------------------------------------------------------- // Mesai Ekleme Bilgileri
	cout << "Mesai eklemek istedigin kisinin numarasi : ";
	cin >> index;
	--index;
	cout << "Kac saat mesai eklemek istiyorsunuz ? ";
	cin >> mesaiSaati;
	cout << "Mesai saatlik ucreti : ";
	cin >> ucret;

	// ------------------------------------------------------------- // Personel Adý Soyadý indexle diziden çekilip txt dosyasýna ad soyad olarak veriliyor.
	if (index == 0)
		adSoyadSecim = 0;
	else
		adSoyadSecim = (index * 2);

	personelOku2.open(personelMesaiDuzenleme[adSoyadSecim] + personelMesaiDuzenleme[adSoyadSecim+1] + ".txt", ios::in);
	personelYaz2.open(personelMesaiDuzenleme[adSoyadSecim] + personelMesaiDuzenleme[adSoyadSecim+1] + ".txt", ios::in);

	
	// ------------------------------------------------------------- // Mesai Eklenecek Kiþinin Dosyasýndaki Elemanlarý Diziye Alma Ýþlemi
	if (personelOku2.is_open()) {
		sayac = 0;
		while (!personelOku2.eof()) {								// Dosya sonuna ulaþýp ulaþamadýðýný gösterir
			personelOku2 >> veri;									// Dosyadaki elemanlarý teker teker alýp veri deðiþkenine atýyor
			personelMesaiDuzenleme[sayac] = veri;					// Veri deðiþkenindeki dosya elemanlarýný diziye atýyor
			sayac++;
		}
	}

	//if (index == 0)
	//	mesaiSecim = 5;
	//else
	//	mesaiSecim = 5 + (index * 7);

	toplamMesai = (mesaiSaati * ucret);
	
	toplamMesaiStr = to_string(toplamMesai);						// String dizisine atama yapacaðýmýz için mesaiÜcretini stringe çeviriyoruz
	personelMesaiDuzenleme[5] = "PersonelMesaiUcreti:" + toplamMesaiStr;		//Mesai ücretini dosyadaki forma uygun hale getiriyoruz


	// ------------------------------------------------------------- // Mesai Ekleyeceðimiz Kiþinin Verilerini Tekrardan Dosyaya Yazdýrýyoruz

	personelYaz2 << personelMesaiDuzenleme[0] << " " + personelMesaiDuzenleme[1] 
				 << endl << "--------------------------" << endl << personelMesaiDuzenleme[3] << endl
				 << personelMesaiDuzenleme[4] << endl << personelMesaiDuzenleme[5] 
				 << endl << "--------------------------" << endl;


	personelOku2.close();
	personelYaz2.close();
	personelYaz.close();
	personelOku.close();
}




void Personel::maasOde() {
	personelYaz.open("personeller.txt", ios::app);
	personelOku.open("personeller.txt", ios::in);
	int sayac = 0;
	string veri;
	int index, adSoyadSecim;
	bool odensinMi = true;


	if (personelOku.is_open()) {
		while (!personelOku.eof()) {
			//if (sayac % 2 == 0 && sayac != 0) {	// Okurken Alt satýra geçmesi için
			//	cout << endl;
			//}
			//else if ((sayac % 1 == 0 ) && (sayac != 0)) {	// okurken elemanlar arasýnda boþluk býrakmasý için
			//	cout << "  ";
			//}
			personelOku >> veri;
			personelMaaslari[sayac] = veri;
			sayac++;
		}
	}
	sayac--;
	for (int i = 0; i < sayac; i++) {
		if ((i % 2 == 0) && (i != 0))
			cout << endl;
		cout << personelMaaslari[i] << " ";
	}


	


	cout << endl;
	cout << "Maas Odenecek Personel No : ";
	cin >> index;
	index--;
	if (index == 0)
		adSoyadSecim = 0;
	else
		adSoyadSecim = (index * 2);

	personelOku2.open(personelMaaslari[adSoyadSecim] + personelMaaslari[adSoyadSecim + 1] + ".txt", ios::in);
	personelYaz2.open(personelMaaslari[adSoyadSecim] + personelMaaslari[adSoyadSecim + 1] + ".txt", ios::in);


	// ------------------------------------------------------------- // Mesai Eklenecek Kiþinin Dosyasýndaki Elemanlarý Diziye Alma Ýþlemi
	if (personelOku2.is_open()) {
		sayac = 0;
		while (!personelOku2.eof()) {								// Dosya sonuna ulaþýp ulaþamadýðýný gösterir
			personelOku2 >> veri;									// Dosyadaki elemanlarý teker teker alýp veri deðiþkenine atýyor
			personelMaaslari2[sayac] = veri;					// Veri deðiþkenindeki dosya elemanlarýný diziye atýyor
			sayac++;
		}
	}

	cout << personelMaaslari2[5] << endl;
	cout << "Mesai Ucreti Odensin Mi ? // 1 - Evet // 0 - Hayir " << endl;
	cin >> odensinMi;
	if (odensinMi == true)
		personelMaaslari2[5] = "PersonelMesaiUcreti:0";


	// ------------------------------------------------------------- // Mesai Ekleyeceðimiz Kiþinin Verilerini Tekrardan Dosyaya Yazdýrýyoruz

	personelYaz2 << personelMaaslari2[0] << " " + personelMaaslari2[1]
		<< endl << "--------------------------" << endl << personelMaaslari2[3] << endl
		<< personelMaaslari2[4] << endl << personelMaaslari2[5]
		<< endl << "--------------------------" << endl;


	personelYaz2.close();
	personelOku2.close();
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
			p.personelEkle();
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