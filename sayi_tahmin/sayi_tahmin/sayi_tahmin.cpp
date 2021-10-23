/****************************************************************************
*  
**                       4 rakamlı sayı tahmin oyunu
* 
****************************************************************************/
#include <iostream>
#include <math.h>
#include <ctime>
#include <iomanip>
#include <locale.h>
#include <string>
#include <math.h>

using namespace std;

int puanHesapla(int toplam_dogru, int toplam_dogru_yersiz, int hak);
void menu();
void sayiUret(int rastgele[], char sayi[], char rakamlar[]);
void tahminAl(string cevap, char tahmin[]);
int karsilastir(char tahmin[], char sayi[], int dogru_yersiz, int dogru);
void kaybettin(char sayi[]);
void kazandin(int toplam_dogru, int toplam_dogru_yersiz, int hak);
void run();

int main()
{
	setlocale(LC_ALL, "turkish");
	
	run();

	system("pause");
	return 0;
}

int puanHesapla(int toplam_dogru, int toplam_dogru_yersiz, int hak)
{
	return 10 * toplam_dogru + 5 * toplam_dogru_yersiz + (1000 / hak) - (toplam_dogru * toplam_dogru_yersiz) / (toplam_dogru + toplam_dogru_yersiz);
}

void menu()
{
	cout << "__________________________________________________" << endl
		<< "|" << setw(49) << "|" << endl
		<< "|" << setw(34) << "SAYI TAHMİN ETME OYUNU" << setw(15) << "|" << endl
		<< "|" << setw(49) << "|" << endl
		<< "--------------------------------------------------" << endl
		<< "| *Bilgilendirme" << setw(34) << "|" << endl
		<< "|" << setw(49) << "|" << endl
		<< "| 1) Sayıyı tahmin etmek için 10 hakkın var" << setw(7) << "|" << endl
		<< "| 2) Her tahmininden sonra sana ipucu verilecek" << setw(3) << "|" << endl
		<< "| İpucu \"-0,+0\" bu formatda olucak" << setw(16) << "|" << endl
		<< "| 3) Sol taraf doğru tahmin ettiğin ama yerleri  |" << endl
		<< "| farklı olan rakamları, sağ taraf doğru tahmin  |" << endl
		<< "| ve yerleri doğru olan rakamları gösterir       |" << endl
		<< "| 4) Örnek tahmin 1234                           |" << endl
		<< "|" << setw(49) << "|" << endl
		<< "--------------------------------------------------" << endl
		<< "|" << setw(49) << "|" << endl
		<< "|" << setw(29) << "OYUN BAŞLADI" << setw(20) << "|" << endl
		<< "|" << setw(49) << "|" << endl
		<< "--------------------------------------------------" << endl
		<< "| 10 hakkın var" << setw(35) << "|" << endl;
}

void sayiUret(int rastgele[], char sayi[], char rakamlar[]) {
	srand(time(0));
	do {
		for (int i = 0; i < 4; i++)
		{
			rastgele[i] = rand() % (9 - 1 + 1) + 1;
			sayi[i] = rakamlar[rastgele[i]];
		}
	} while (rastgele[0] == rastgele[1] || rastgele[0] == rastgele[2] || rastgele[0] == rastgele[3] || rastgele[1] == rastgele[2] || rastgele[1] == rastgele[3] || rastgele[2] == rastgele[3]);
	//tahmin edilecek sayının rakamları bir birine eşit olmayanadek tekrar değer atayan while döngüsü
}

void tahminAl(string cevap, char tahmin[])
{
	string tmp;
	int kosul = 0;//ikinci tekrardan itibaren ekrana yazdırmak için int kosul değişkenini kullandım.
	do {//bu döngü kullanıcı girdiği sayıyı değiştirmek istediğinde değiştirebilmesine olanak sağlar
		if (cevap != "e" && kosul != 0)
		{
			cout << "| Tekrar tahmin edin..." << setw(27) << "|" << endl;
		}

		cout << "|" << setw(49) << "|" << endl << "| Tahminin :" << setw(29) << " "; 
		cin >> tmp; //kullanıcı tahmin ettiği sayıyı girer.
		if (tmp.length() == 4)
		{
			for (int i = 0; i < 4; i++)
			{
				tahmin[i] = tmp[i];
			}
			cout << "| Onaylıyor musun?(e/h)" << setw(18) << " ";
			cin >> cevap; cout << endl << "|" << setw(49) << "|" << endl;//eğer sayı 4 karakterden fazla ise girilen fazla sayılar otomatik olarak string cevap değişkenine atanır.
			kosul++;
		}
		else
		{
			cout << "| Hatalı tahmin tekrar tahmin edin." << setw(15) << "|" << endl << "--------------------------------------------------" << endl;
			continue;
		}
		
	} while (cevap != "e" && cevap != "E");//eğer ki kullanıcı 4 rakamlı bir sayı girdiyse ve string cevap için "e" ve ya "E" girdiyse while döngüsü biter.
}

int karsilastir(char tahmin[],char sayi[],int dogru_yersiz, int dogru)
{

	if ((tahmin[0] == tahmin[1]) && (tahmin[1] == tahmin[2]) && (tahmin[2] == tahmin[3]))
	{
		for (int i = 0; i <= 3; i++)
		{
			if (sayi[i] == tahmin[0])
			{
				dogru++;
			}
		}
	}
	else
	{
		for (int z = 0; z <= 3; z++)//burdaki iç içe for döngüleri tahmin edilen sayı ve gerçek sayıyı karşılaştırmaya yarar
		{
			for (int j = 0; j <= 3; j++)
			{

				if (sayi[z] == tahmin[j])//rastgele sayı ve tahmin edilen sayı aslında 4 elemanlı bir char dizisi olduğundan tek tek tüm dizi elemanlarını karşılaştırılır ve uygun koşullara göre değişkenlere değer atanır.
				{
					if (tahmin[j] != tahmin[j - 1] && j != 0)//bu if döngüsü ve girilen aynı sayıların 2 kez hesaplanmasını önler doğru olduğu halde yeri yanlış olan rakamları bulur.
					{
						dogru_yersiz++;//her tekrarda int doğru_yersiz 1 arttırılır.
					}
					else if (j == 0)
						dogru_yersiz++;
					if (z == j)//doğru_yersiz değişkeninin hesabından sonra eğer dizilerin indexleri de eşitse rakamın yerinin de doğru olduğu kabul edilir
					{
						dogru++;
						dogru_yersiz = dogru_yersiz - 1;//ve doğru yersiz 1 azaltılır
					}
				}
			}
		}
	}
	
	cout << "| Sonuc :" << setw(32) << "-" << dogru_yersiz << ",+" << dogru << setw(5) << "|" << endl << "--------------------------------------------------" << endl;//hesaplanan int doğru ve int doğru_yersiz değişkenlerinin değerleri ekrana yazdırılır
	return dogru;
}

void kaybettin(char sayi[])
{
	cout << "| OYUN BİTTİ KAYBETTİN" << setw(28) << "|" << endl
		<< "|" << setw(49) << "|" << endl
		<< "| sayı 1 :  " << setw(30) << sayi[0] << endl
		<< "| sayı 2 :  " << setw(30) << sayi[1] << endl
		<< "| sayı 3 :  " << setw(30) << sayi[2] << endl
		<< "| sayı 4 :  " << setw(30) << sayi[3] << endl
		<< "|" << setw(49) << "|" << endl
		<< "--------------------------------------------------" << endl;
}

void kazandin(int toplam_dogru, int toplam_dogru_yersiz, int hak) {
	int puan;
	//verilen denkleme uygun puan hesabı
	puan = puanHesapla(toplam_dogru, toplam_dogru_yersiz, hak);
	cout << "|" << setw(33) << "TEBRİKLER KAZANDINIZ" << setw(16) << "|" << endl
		<< "|" << setw(49) << "|" << endl
		<< "| toplam doğru tahmin :" << setw(21) << toplam_dogru << endl
		<< "| kullanılan hak :" << setw(25) << hak << endl
		<< "|" << setw(49) << "|" << endl
		<< "| puanınız :" << setw(33) << puan << endl
		<< "--------------------------------------------------" << endl;
}

void run() {
	//random sayı üretme--------------
	char rakamlar[10] = { '0','1','2','3','4','5','6','7','8','9' };//sayıyı 4 adet char rakamdan üretiyorum
	int rastgele[4];
	char sayi[4];
	char tahmin[4];//kullanıcı tarafından girilecek sayıyı tutan char dizisi
	string cevap;
	int dogru_yersiz = 0, toplam_dogru_yersiz = 0;
	int dogru = 0, toplam_dogru = 0;
	int hak;

	sayiUret(rastgele, sayi, rakamlar);
	menu();
	for (int i = 1; i <= 10; i++)//Kullanıcıya 10 hak tanımak için yanlış yaptığında 10 kez tekrar eden for döngüsü
	{
		tahminAl(cevap, tahmin);
		dogru = karsilastir(tahmin, sayi, dogru_yersiz, dogru);
		if (dogru == 4)//eğer ki doğru 4'e eşitse 10 kez tekrar edicek for döngüsü sonlandırılır.
		{
			hak = i;//döngünün tekrar etme sayı kullanıcının kaçıncı hakta bildiğini tutan hak değişkenine atanır
			i = 11;//ve döngüyü sonlandırmak için i değişkenine değer atanır
		}
		else//kullanıcının kaç hakkı kaldığı yazılır
		{
			cout << "| " << 10 - i << " hakkın kaldı" << setw(34) << "|" << endl
				<< "|" << setw(49) << "|" << endl;
			hak = 0;
		}
		//sıfırlanacak değişkenler puan hesabında kullanılmak için başka değişkenlerde tutlur
		toplam_dogru_yersiz = toplam_dogru_yersiz + dogru_yersiz;
		toplam_dogru = toplam_dogru + dogru;
		dogru_yersiz = 0;
		dogru = 0;
	}
	if (hak == 0)//for döngüsünün bitmesine rağmen hala int hak değişkeni '0'a eşitse ekrana uygun yazı yazdırılır
	{
		kaybettin(sayi);
	}
	//Puan hesaplama------
	if (hak != 0)
	{
		kazandin(toplam_dogru, toplam_dogru_yersiz, hak);
	}
}