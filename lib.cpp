#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

//Classes
class DosyaIslemleri
{
public:
  bool DosyaVarmi(const char* dosya_ismi)
  {
    ifstream okunan(dosya_ismi);
    if(okunan.fail()){
      return false;
    } else {
      return true;
    }
  }

  void Oku(const char* dosya_ismi)
  {
    ifstream okunan(dosya_ismi);
    bool varmi = DosyaVarmi(dosya_ismi);

    if(varmi == false)
    {
      cout << "Dosya yok." << endl;
    } else {
      if(okunan.is_open())
      {
        string satir;
        while(getline(okunan, satir))
        {
          std::cout << satir << std::endl;
        }
        okunan.close();
      }
    }
  }

  void Yaz(const char* dosya_ismi, string yazilacak_satir)
  {
    bool varmi = DosyaVarmi(dosya_ismi);
    if(varmi == false)
    {
      ofstream yazilan(dosya_ismi);
      if(yazilan.is_open())
      {
        yazilan << yazilacak_satir;
        yazilan.close();
      }
    } else {
      cout << "Dosya zaten var." << endl;
    }
  }

  void Ekle(const char* dosya_ismi, string eklenecek_satir)
  {
    std::ifstream eski_dosya(dosya_ismi);
    std::ofstream tmp("tmp.txt");

    bool varmi = DosyaVarmi(dosya_ismi);
    if(varmi == false)
    {
      Yaz(dosya_ismi, eklenecek_satir);
    } else {
      std::string satir;
      if(eski_dosya.is_open())
      {
        do{
          getline(eski_dosya, satir);
          tmp << satir;
          if(!eski_dosya.eof()) {
            tmp << "\n";
          }
        }while(!eski_dosya.eof());

        tmp << eklenecek_satir << endl;

        eski_dosya.close();
        tmp.close();

        int silindi_mi = remove(dosya_ismi);
        int isim_degisti_mi = rename("tmp.txt", dosya_ismi);
        silindi_mi = remove("tmp.txt");

        if(silindi_mi && isim_degisti_mi) {
          cout << "Satir eklendi." << endl;
        }
      }
    }
  }
};

class Kutuphane
{
public:
  const char* dosya_ismi;

  Kutuphane(const char* dosya_ismi_)
  {
    dosya_ismi = dosya_ismi_;
  }

  int MenuYaz()
  {
    int secenek;
    system("clear");
    cout << "1-) Kitap ekle\n";
    cout << "2-) Kitaplari goruntule\n";
    cout << "3-) Kitap sorgulama\n";
    cout << "4-) Cikis\n";
    cout << "========================================\n";
    cout << "Bir Secenek Giriniz = ";
    cin  >> secenek;
    return secenek;
  }

  void KitapEkle()
  {
    DosyaIslemleri dosyalar;
    int    barkod;
    string kitap_adi;
    string yazar_adi;
    string tur;

		cout << "Kitap barkodunu giriniz: ";  cin >> barkod;
		cout << "Kitap adini giriniz: ";      cin >> kitap_adi;
		cout << "Kitabin yazarini giriniz: "; cin >> yazar_adi;
		cout << "Kitabin turunu giriniz: ";   cin >> tur;

    dosyalar.Ekle(dosya_ismi, barkod + ", " + kitap_adi + ", " + yazar_adi + ", " + tur);
  }

  void Sorgula(int barkodno, const char* secenek)
  {
    int index_isim  = 1;
    int index_yazar = 2;
    int index_tur   = 3;
    int sorgulanacak_secenek = 0;

    ifstream dosya(dosya_ismi);
    string satir;

    for(int i = 0; i < barkodno; i++)
    {
      getline(dosya, satir);
    }

    char *p;
    char* yeni_satir = const_cast<char*>(satir.c_str());
    p = strtok(yeni_satir, ", "); // Virgul ve bosluk ayrac olarak kullanildi

    if(strcmp(secenek, "isim") == 0)
    {
      sorgulanacak_secenek = index_isim;
    }
    else if(strcmp(secenek, "tur") == 0)
    {
      sorgulanacak_secenek = index_tur;
    }
    else if(strcmp(secenek, "yazar") == 0)
    {
      sorgulanacak_secenek = index_yazar;
    }

    for(int i = 0; i < sorgulanacak_secenek; i++)
    {
      p = strtok(NULL, ", ");
    }
    cout << p << endl;
  }
};

//Main
int main(int argc, char *argv[]) {
  DosyaIslemleri dosyalar;
  Kutuphane k1("kitaplar.txt");

  /*
   * Testler
   *
   * Kontrol
   * int sonuc = dosyalar.DosyaVarmi("ornek_dosya.txt");
   * cout << sonuc << endl;
   *
   * Yaz
   * dosyalar.Yaz("ornek_dosya.txt");
   *
   * Oku
   * dosyalar.Oku("ornek_dosya.txt");
   *
   * Ekle
   * dosyalar.Ekle("ornek_dosya.txt", "iyiyim");
   *
   */

  int Sec = k1.MenuYaz();
  int cevap;
  char* ozellik;
	switch(Sec)
  {
		case 1:
      k1.KitapEkle();
      break;
    case 2:
      dosyalar.Oku(k1.dosya_ismi);
      break;
    case 3:
      cout << "Barkodu giriniz: "; cin >> cevap;
      cout << "Hangi ozellik: ";   cin >> ozellik;
      k1.Sorgula(cevap, ozellik);
      break;
    case 4:
      system("exit");
      break;
    default:
      cout << "Hatali giris." << endl;
  }
}
