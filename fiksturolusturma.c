#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int bostakim;
struct takim{ //takimlari ve guclerini ayni anda bellekte tutmak icin struct yapisi tanimlanir
    char takimadi[50];
    int guc;
      };

      struct takim takimlar[19];
void takimlariOku()
{ // dosyadaki takimlari okumasi ve diziye kaydetmesi icin fonksiyon olusturur
    FILE *dosya = fopen("takimlar.txt", "r");
    if (dosya == NULL)
    {
        printf("HATA: takimlar dosyasi acilamadi!\n");
        exit(1);  // Dosya acilmazsa durur
    }

    
    for (int i = 0; i < 19; i++)
    {   fgets(takimlar[i].takimadi, sizeof(takimlar[i].takimadi), dosya);//dosyada okudugu takimlari struct icine atar
        takimlar[i].takimadi[strcspn(takimlar[i].takimadi, "\n")] = '\0'; // \n karakterini siler
    
    }
    fclose(dosya);
}

void takimguclerinioku()
{
    FILE *dosya = fopen("guc.txt", "r");
    if (dosya == NULL)
    {
        printf("HATA: guc dosyasi acilamadi!\n");
        exit(1);  // Dosya acilmazsa durur
    }
    for (int j = 0; j < 19; j++)
    {    fscanf(dosya, "%d", &takimlar[j].guc);//dosyada okudugu takimlarin guclerini struct icine atar
    
    }
    fclose(dosya);
  
}
void fiksturOlusturveyaz() // fikstur olusturmak icin fonksiyon baslatir
{
    int evsahibi, rakip;
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
        printf("Bu hafta bos gecen takim: %s\n", takimlar[bostakim].takimadi);
        fprintf(dosya, "Bu hafta bos gecen takim: %s\n", takimlar[bostakim].takimadi); // Dosyaya bos gecen takimi yazar

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
            printf(" %s vs %s\n", takimlar[evsahibi].takimadi,takimlar[rakip].takimadi);
            fprintf(dosya, " %s vs %s\n", takimlar[evsahibi].takimadi, takimlar[rakip].takimadi);
        
          // Takımların guc fariına gore tahmin yapmak icin fark degiskeni tanimlanir
int fark = takimlar[evsahibi].guc - takimlar[rakip].guc;

            if (fark > 0) {  // Ev sahibi daha gucluyse kosulu
                 if (fark >= 80) {
                      printf("%s takimi cok gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                      fprintf(dosya, "%s takimi cok gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                                 } 
                 else if (fark >= 60) {
                       printf("%s takimi 3-4 gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                       fprintf(dosya, "%s takimi 3-4 gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                                      }  
                  else if (fark >= 40) {
                      printf("%s takimi 2 gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                      fprintf(dosya, "%s takimi 2 gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                                       }  
                   else if (fark >= 10) {
                      printf("%s takimi 1 gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                      fprintf(dosya, "%s takimi 1 gol farkla kazanabilir\n", takimlar[evsahibi].takimadi);
                                        }
                             } 
             else if (fark == 0) { // İki takımın gücü esitse kosulu
                  printf("Mac berabere kalabilir\n");
                  fprintf(dosya, "Mac berabere kalabilir\n");
                                 } 
      
             else { // Rakip daha gucluyse kosulu
                    fark = -fark; // Fark pozitif hale getirilir ona gore karsilastirir

                    if (fark >= 80)  {
                      printf("%s takimi cok gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                      fprintf(dosya, "%s takimi cok gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                                     } 
                    else if (fark >= 60) {
                       printf("%s takimi 3-4 gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                       fprintf(dosya, "%s takimi 3-4 gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                                        } 
                     else if (fark >= 40) {
                        printf("%s takimi 2 gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                        fprintf(dosya, "%s takimi 2 gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                                          } 
                    else if (fark >= 10) {
                        printf("%s takimi 1 gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                        fprintf(dosya, "%s takimi 1 gol farkla kazanabilir\n", takimlar[rakip].takimadi);
                                        }
                       }
         }
          }  fclose(dosya);
   }
 
int main()
{

    takimlariOku();   // Takimlari okur 
    takimguclerinioku(); //takim guclerini okur
    fiksturOlusturveyaz(); // fiksturu olusturur ve dosyaya yazar
     return 0;
}
