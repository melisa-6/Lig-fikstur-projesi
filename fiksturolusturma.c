#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int bostakim;

struct takim { //takimlari ve guclerini ayni anda bellekte tutmak icin struct yapisi tanimlanir
    char takimadi[50];
    int guc;
             };

struct mac {
    int evsahibi;
    int rakip;
            };

struct takim takimlar[19];
struct mac eslesmeler[38][9];

 // dosyadaki takimlari okumasi ve diziye kaydetmesi icin fonksiyon olusturur
void takimlarioku() {
    FILE *dosya = fopen("takimlar.txt", "r");
    if (dosya == NULL) {
        printf("HATA: takimlar dosyasi acilamadi!\n");
        exit(1);// Dosya acilmazsa durur
    }
    for (int i = 0; i < 19; i++) {
        fgets(takimlar[i].takimadi, sizeof(takimlar[i].takimadi), dosya);//dosyada okudugu takimlari struct icine atar
        takimlar[i].takimadi[strcspn(takimlar[i].takimadi, "\n")] = '\0'; //\n karakterini  siler
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
        fscanf(dosya, "%d", &takimlar[j].guc); //dosyada okudugu takimlarin guclerini struct icine atar
    }
    fclose(dosya);
}
    // fikstur olusturmak icin fonksiyon baslatir
void fiksturolustur() {
    srand(time(NULL));
    for (int hafta = 0; hafta < 19; hafta++) { //1. haftadan 19. haftaya kadar rastgele ev sahibi rakip ve bos gecen takim secer
        int eslesme[19] = {0}; //tum takimlari eslenmedi isaretler

        bostakim = rand() % 19; //bos gecen takimi rastgele secer
        eslesme[bostakim] = 1; // bos gecen takimi Secildi olarak isaretler

        for (int macsayisi = 0; macsayisi < 9; macsayisi++) {
            int evsahibi, rakip;
            do { 
                evsahibi = rand() % 19; //ev sahibi takimi rastgele secer
            } while (eslesme[evsahibi] == 1);
            eslesme[evsahibi] = 1; // ev sahibi takimi Secildi olarak isaretler

            do {
                rakip = rand() % 19;//rakip  takimi rastgele secer
            } while (eslesme[rakip] == 1);
            eslesme[rakip] = 1; // rakip takimi Secildi olarak isaretler

            // ilk devre için eslesme
            eslesmeler[hafta][macsayisi].evsahibi = evsahibi;
            eslesmeler[hafta][macsayisi].rakip = rakip;

            //ikinci devre icin eslesmeyi ters kaydeder yani 19 mac sonraya kaydeder boylece cift devreli olur
            eslesmeler[hafta + 19][macsayisi].evsahibi = rakip;
            eslesmeler[hafta + 19][macsayisi].rakip = evsahibi;
        }
    }
}
//takimlardaki guc farkin gore skor tahmini yapar
void macskortahmini(int evsahibi, int rakip, FILE *dosya) {
    int fark = takimlar[evsahibi].guc - takimlar[rakip].guc;

    if (fark > 0) {  
        if (fark >= 80) {
            printf("Skor Tahmini: %s 5-6 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 5-6 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
        } else if (fark >= 60) {
            printf("Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
        } else if (fark >= 40) {
            printf("Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
        } else if (fark >= 10) {
            printf("Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[evsahibi].takimadi);
        } else {
            printf("Skor Tahmini: Maç berabere olabilir\n\n");
            fprintf(dosya, "Skor Tahmini: Maç berabere olabilir\n\n");
        }
    } 
    else if (fark == 0) {
        printf("Skor Tahmini: Mac berabere olabilir\n\n");
        fprintf(dosya, "Skor Tahmini: Mac berabere olabilir\n\n");
    } 
    else { 
        fark = -fark;
        if (fark >= 80) {
            printf("Skor Tahmini: %s 5-6 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 5-6 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
        } else if (fark >= 60) {
            printf("Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 3-4 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
        } else if (fark >= 40) {
            printf("Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 2 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
        } else if (fark >= 10) {
            printf("Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Skor Tahmini: %s 1 farkla kazanabilir\n\n", takimlar[rakip].takimadi);
        }
    }
}
   //olusturulan fiksturu yazdirir
void fiksturyazdir() {
    FILE *dosya = fopen("fikstur.txt", "w");

    for (int hafta = 0; hafta < 38; hafta++) {
        printf("\n\n  %d. Hafta\n\n", hafta + 1);
        fprintf(dosya, "\n\n  %d. Hafta\n\n", hafta + 1);
        
        for (int macsayisi = 0; macsayisi < 9; macsayisi++) {
            int evsahibi = eslesmeler[hafta][macsayisi].evsahibi;
            int rakip = eslesmeler[hafta][macsayisi].rakip;

            printf("%s VS %s\n", takimlar[evsahibi].takimadi, takimlar[rakip].takimadi);
            fprintf(dosya, "%s VS %s\n", takimlar[evsahibi].takimadi, takimlar[rakip].takimadi);

            printf("Ev Sahibi: %s\n", takimlar[evsahibi].takimadi);
            fprintf(dosya, "Ev Sahibi: %s\n", takimlar[evsahibi].takimadi);

            printf("Rakip: %s\n", takimlar[rakip].takimadi);
            fprintf(dosya, "Rakip: %s\n", takimlar[rakip].takimadi);

            macskortahmini(evsahibi, rakip, dosya);
        }
    }

    fclose(dosya);
}

int main() {
    takimlarioku();
    takimguclerinioku();
    fiksturolustur();
    fiksturyazdir();
    return 0;
}
