#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int bostakim;
char takimlar[19][50]; // 19 terimlik her bir terim max 50 karakterden olusabilecek dizi olusturur
void takimlariOku()
{ // dosyadaki takimlari okumasi ve diziye kaydetmesi icin fonksiyon olusturur
    FILE *dosya = fopen("takimlar.txt", "r");
    if (dosya == NULL)
    {
        printf("HATA: takimlar dosyasi acilamadi!\n");
        exit(1);  // Dosya acilmazsa durur
    }
    for (int i = 0; i < 19; i++)
    {
        fgets(takimlar[i], 50, dosya); // takimlar dosyasinin ilk satirindan son satirina kadar okur ve takimlar dizisinin i. terimine kaydeder
      takimlar[i][strcspn(takimlar[i], "\n")] = 0;//dosyadaki bilgiler okunurken alt satira gecmesini onlemek icin
    }
    fclose(dosya);
}
void fiksturOlusturveyaz() // fikstur olusturmak icin fonksiyon baslatir
{
    int evsahibi, rakip;
    int eslesme[19] = {0};
    srand(time(NULL));                       // Rastgele takim secmeye baslar
    FILE *dosya = fopen("fikstur.txt", "w"); // olusan fiksturu kaydetmek icin fikstur adli dosyayi acar
    if (dosya == NULL)
    {
        printf("HATA: fikstur dosyasi acilamadi!\n");
        exit(1);// Dosya acilmazsa durur
            }
    for (int hafta = 1; hafta <= 38; hafta++) // 1. haftadan 38. haftaya kadar donguyu baslatır
    {    int eslesme[19] = {0};
        printf("\n  %d. Hafta \n", hafta);
        fprintf(dosya, "\n  %d. Hafta \n", hafta); // Dosyaya kacinci hafta oldugunu yazar

        bostakim = rand() % 19; // Rastgele bir takimin bos gecmesini saglar
        printf("Bu hafta bos gecen takim: %s\n", takimlar[bostakim]);
        fprintf(dosya, "Bu hafta bos gecen takim: %s\n", takimlar[bostakim]); // Dosyaya bos gecen takimi yazar

        eslesme[bostakim] = 1; // Bos gecen takimi daha sonra tekrar kullanmamak icn isaretler

        for (int macsayisi = 0; macsayisi < 9; macsayisi++) // bos kalan takim haricinde kalan 18 takimla 9 mac olusturur
        {  
            do
            { 
                evsahibi = rand() % 19; // ev sahibi takimi rastgele secer
            } 
           while (eslesme[evsahibi] == 1); // ev sahibi takim eslesmisse onun secilmemesini saglar

            eslesme[evsahibi] = 1; // ve secilmeen ev sahibi takimi secilmis olarak isaretler

            do
            {
                rakip = rand() % 19; //rastgele rakip takimi secer
            } while (eslesme[rakip] == 1); // secilen takim eslesmisse tekrar rastgele deger almasini saglar

            eslesme[rakip] = 1; // rakip takimi Secildi olarak isaretler

            // rastgele cikantakimlari ekrana ve dosyaya yazdır
            printf(" %s vs %s\n", takimlar[evsahibi], takimlar[rakip]);
            fprintf(dosya, " %s vs %s\n", takimlar[evsahibi], takimlar[rakip]);
        }
    }
    fclose(dosya);
}

int main()
{

    takimlariOku();   // Takimlari okur 
    fiksturOlusturveyaz(); // fiksturu olusturur ve dosyaya yazar
    return 0;
}
   