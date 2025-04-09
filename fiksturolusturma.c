#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int bostakim;

struct takim {
    char takimadi[50];
    int guc;
    int puan;  // Takimlarin puanlari
};

struct mac {
    int evsahibi;
    int rakip;
};

struct takim takimlar[19];
struct mac eslesmeler[38][9];

// Dosyadaki takimlari okuma
void takimlarioku() {
    FILE *dosya = fopen("takimlar.txt", "r");
    if (dosya == NULL) {
        printf("HATA: takimlar dosyasi acilamadi!\n");
        exit(1); // Dosya acilmazsa durur
    }
    for (int i = 0; i < 19; i++) {
        fgets(takimlar[i].takimadi, sizeof(takimlar[i].takimadi), dosya);  // Takimlarin adlarini okur
        takimlar[i].takimadi[strcspn(takimlar[i].takimadi, "\n")] = '\0';  // '\n' karakterini siler
        takimlar[i].puan = 0;  // Baslangicta her takim 0 puanda
    }
    fclose(dosya);
}

void takimguclerinioku() {
    FILE *dosya = fopen("guc.txt", "r");
    if (dosya == NULL) {
        printf("HATA: guc dosyasi acilamadi!\n");
        exit(1); // Dosya acilmazsa durur
    }
    for (int j = 0; j < 19; j++) {    
        fscanf(dosya, "%d", &takimlar[j].guc);  // Her takim gucunu okur
    }
    fclose(dosya);
}

// Fikstur olusturma
void fiksturolustur() {
    srand(time(NULL));
    FILE *dosya = fopen("fikstur.txt", "w");
    if (dosya == NULL) {
        printf("HATA: Fikstur dosyasi acilamadi!\n");
        exit(1);
    } 
    for (int hafta = 0; hafta < 19; hafta++) {  // 19 hafta boyunca eslesme yapilir
        int eslesme[19] = {0};  // Takimlarin eslesip eslesmedigini kontrol eder

        bostakim = rand() % 19;  // Bir takim bos gecilir
        eslesme[bostakim] = 1;  // Bos gecilen takim isaretlenir
        
// Boş geçen takımı ekrana ve dosyaya yazdır
printf("Hafta %d: %s takimı boş geçildi.\n", hafta + 1, takimlar[bostakim].takimadi);
fprintf(dosya,"Hafta %d: %s takimı boş geçildi.\n", hafta + 1, takimlar[bostakim].takimadi);

        for (int macsayisi = 0; macsayisi < 9; macsayisi++) {
            int evsahibi, rakip;
            do { 
                evsahibi = rand() % 19;  // Ev sahibi takim
            } while (eslesme[evsahibi] == 1);
            eslesme[evsahibi] = 1;

            do {
                rakip = rand() % 19;  // Rakip takim
            } while (eslesme[rakip] == 1);
            eslesme[rakip] = 1;

            // Ilk devre icin eslesme
            eslesmeler[hafta][macsayisi].evsahibi = evsahibi;
            eslesmeler[hafta][macsayisi].rakip = rakip;

            // Ikinci devre icin eslesme ters olarak kaydedilir
            eslesmeler[hafta + 19][macsayisi].evsahibi = rakip;
            eslesmeler[hafta + 19][macsayisi].rakip = evsahibi;
        }
    }
}
// takimlardaki guc farkin gore skor tahmini yapar
void macskortahmini(int evsahibi, int rakip, FILE *dosya) {
    int fark = takimlar[evsahibi].guc - takimlar[rakip].guc;

    if (fark > 0) {  // Ev sahibi daha guclu ise
        if (fark >= 60) {  // Buyuk fark
            takimlar[evsahibi].puan += 3;  // Ev sahibi 3 puan kazandı
            printf("Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
                         } 
        else if (fark >= 40) {  // Orta buyuk fark
            printf("Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            takimlar[evsahibi].puan += 3;  // Ev sahibi 3 puan kazandı                 
                             } 
        else if (fark >= 10) {  // Kucuk fark
            printf("Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            takimlar[evsahibi].puan += 3;  // Ev sahibi 3 puan kazandı                        
                            }
     else {
            printf("Skor Tahmini: Mac berabere olabilir\n\n");
            fprintf(dosya, "Skor Tahmini: Mac berabere olabilir\n\n");
            takimlar[evsahibi].puan += 1;
            takimlar[rakip].puan += 1;  // Ev sahibi ve rakip 1 puan kazandı
        }
    } 
    else if (fark == 0) {  // Fark sifir ise
        printf("Skor Tahmini: Mac berabere olabilir\n\n");
        fprintf(dosya, "Skor Tahmini: Mac berabere olabilir\n\n");
        takimlar[evsahibi].puan += 1;
        takimlar[rakip].puan += 1;  // Ev sahibi ve rakip 1 puan kazandı
    } 
    else {  // Rakip daha guclu ise
        fark = -fark;
        if (fark >= 60) {  // Buyuk fark
            printf("Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            takimlar[rakip].puan += 3; // Rakip 3 puan kazandı
                         }
             else if (fark >= 40) {  // Orta buyuk fark
            printf("Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            takimlar[rakip].puan += 3; // Rakip 3 puan kazandı
                                  }
           else if (fark >= 10) {  // Kucuk fark
            printf("Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            takimlar[rakip].puan += 3; // Rakip 3 puan kazandı
                                   }
    }
}

// Takimlari ve puanlari yazdirma
void takimlariyazdir(FILE *dosya) {
    printf("\n\n--- Takimlar ve Puanlar ---\n");
    fprintf(dosya, "\n\n--- Takimlar ve Puanlar ---\n");

    for (int i = 0; i < 19; i++) {
        printf("%s: %d Puan\n", takimlar[i].takimadi, takimlar[i].puan);
        fprintf(dosya, "%s: %d Puan\n", takimlar[i].takimadi, takimlar[i].puan);
    }
}

// Fiksturu yazdirma
void fiksturyazdir(FILE *dosya) {
    for (int hafta = 0; hafta < 38; hafta++) {
        printf("\n\n  %d. Hafta\n\n", hafta + 1);
        fprintf(dosya, "\n\n  %d. Hafta\n\n", hafta + 1);
        
            
        for (int macsayisi = 0; macsayisi < 9; macsayisi++) {
            int evsahibi = eslesmeler[hafta][macsayisi].evsahibi;
            int rakip = eslesmeler[hafta][macsayisi].rakip;

            printf("%s VS %s\n", takimlar[evsahibi].takimadi, takimlar[rakip].takimadi);
            fprintf(dosya, "%s VS %s\n", takimlar[evsahibi].takimadi, takimlar[rakip].takimadi);

            macskortahmini(evsahibi, rakip,dosya);  // Her mac skoru tahmin edilir
        }
    }


int max_puan = takimlar[0].puan; 
int sampiyon_sayac = 0;

for (int i = 1; i < 19; i++) {  // Tum takimlari kontrol et
    if (takimlar[i].puan > max_puan) {
        max_puan = takimlar[i].puan;  // Yeni maksimum puani belirle
        sampiyon_sayac = i;  // Sampiyonun sayacini guncelle
    }
    else if (takimlar[i].puan == max_puan) {  // Puanlar esitse
        if (takimlar[i].guc > takimlar[sampiyon_sayac].guc) {  // Guc karsilastirması
            sampiyon_sayac = i;  // Gucu buyuk olanı guncelle
        }
    }
}

printf("\n\n Olasi Sampiyon: %s -> %d Puan\n", takimlar[sampiyon_sayac].takimadi, takimlar[sampiyon_sayac].puan);  // Sampiyonu ekrana yazdir
fprintf(dosya, "\n\n Olasi Sampiyon: %s %d Puan\n", takimlar[sampiyon_sayac].takimadi, takimlar[sampiyon_sayac].puan);  // Sampiyonu dosyaya yazdir

}

int main() {
    takimlarioku();  // Takimlari oku
    takimguclerinioku();  // Takimlarin guclerini oku
    fiksturolustur();  // Fiksturu olustur
    FILE *dosya = fopen("fikstur.txt", "w");  // Fiksturu dosyaya yaz

    fiksturyazdir(dosya);  // Fiksturu yazdir
    takimlariyazdir(dosya);  // Takimlari ve puanlari yazdir

    fclose(dosya);  // Dosyayi kapat

    return 0;
}

