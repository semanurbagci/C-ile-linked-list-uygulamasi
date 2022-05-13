#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
struct sehir
{
    int plaka_kodu;
    char sehir_adi[50];
    char cografi_bolge[50];
    int komsu_sayisi;
    struct komsu *komsu_sonraki;
    struct sehir *onceki;
    struct sehir *sonraki;
};
struct komsu
{
    char komsu_adi[50];
    char komsu_cografi_bolge[50];
    int plaka_kodu;
    struct komsu *sonraki;
};

struct sehir* start = NULL;
struct komsu* start2 = NULL;

struct komsu* komsuDugumOlustur(char k_ad[], char c_bolge[], int plaka)
{
    struct komsu* yeniDugum = (struct komsu*)malloc(sizeof(struct komsu));
    strcpy(yeniDugum->komsu_adi,k_ad);
    strcpy(yeniDugum->komsu_cografi_bolge,c_bolge);
    yeniDugum->plaka_kodu=plaka;
    yeniDugum->sonraki=NULL;

    return yeniDugum;

}
void komsuSonaEkle(char k_ad[], char c_bolge[], int plaka)
{
    struct komsu* sonaEklenecek = komsuDugumOlustur(k_ad,c_bolge,plaka);
    if(start2==NULL)
    {
        start2=sonaEklenecek;
    }
    else
    {
        struct komsu* temp=start2;
        while(temp->sonraki!=NULL)
        {
            temp=temp->sonraki;
        }
        temp->sonraki=sonaEklenecek;
    }
}
void komsuBasaEkle(char k_ad[], char c_bolge[], int plaka)
{
    struct komsu* basaEklenecek = komsuDugumOlustur(k_ad,c_bolge,plaka);
    struct komsu* temp=start2;
    basaEklenecek->sonraki=temp;
    start2=basaEklenecek;
}
void komsuArayaEkle(struct komsu* onceki_dugum, char *k_ad, char c_bolge[], int plaka)
{
    if(onceki_dugum==NULL)
    {
        komsuBasaEkle(k_ad,c_bolge,plaka);
    }
    else
    {
        struct komsu* arayaEklenecek = komsuDugumOlustur(k_ad,c_bolge,plaka);
        arayaEklenecek->sonraki=onceki_dugum->sonraki;
        onceki_dugum->sonraki=arayaEklenecek;
    }
}
void komsuBastanSil()
{
    if(start2==NULL)
    {
        printf("zaten hic komsu yok.\n");
        return;
    }
    if(start2->sonraki==NULL)
    {
        free(start2);
        start2=NULL;
        return;
    }
    if(start2->sonraki!=NULL)
    {
        struct komsu* bastanSilinecek = start2;
        start2=start2->sonraki;
        free(bastanSilinecek);
        return;
    }

}
void komsuSondanSil()
{
    if(start2==NULL)
    {
        printf("zaten hic komsu yok.\n");
        return;
    }
    if(start2->sonraki==NULL)
    {
        free(start2);
        start2=NULL;
        return;
    }
    if(start2->sonraki!=NULL)
    {
        struct komsu* temp=start2;
        while(temp->sonraki->sonraki!=NULL)
        {
            temp=temp->sonraki;
        }
        struct komsu* sondanSilinecek=temp->sonraki;
        free(sondanSilinecek);
        temp->sonraki=NULL;
    }
}
void komsuIstenilenSil(int silinecek_plaka)
{
    if(start2->plaka_kodu == silinecek_plaka)
    {
        komsuBastanSil();
    }
    else
    {
        struct komsu* temp = start2;
        while(temp->sonraki->plaka_kodu!=silinecek_plaka)
        {
            temp=temp->sonraki;
        }
        struct komsu* temp1=temp->sonraki->sonraki;
        struct komsu* temp2=temp;
        free(temp->sonraki);
        temp2->sonraki=temp1;
    }
}
struct sehir* dugumOlustur(int plaka, char s_ad[], char c_bolge[], int komsu_sayisi)
{
    struct sehir* yeniDugum = (struct sehir*)malloc(sizeof(struct sehir));
    yeniDugum->plaka_kodu=plaka;
    strcpy(yeniDugum->sehir_adi,s_ad);
    strcpy(yeniDugum->cografi_bolge,c_bolge);
    yeniDugum->komsu_sayisi=komsu_sayisi;
    yeniDugum->onceki=NULL;
    yeniDugum->sonraki=NULL;
    yeniDugum->komsu_sonraki=NULL;

    return yeniDugum;
}

void sonaEkle(int plaka, char s_ad[], char c_bolge[],int komsu_sayisi)
{
    struct sehir* sonaEklenecek = dugumOlustur(plaka,s_ad,c_bolge,komsu_sayisi);
    if (start == NULL)
    {
        start = sonaEklenecek;
    }
    else
    {
        struct sehir* temp=start;
        while (temp->sonraki != NULL)
        {
            temp = temp->sonraki;
        }
        sonaEklenecek->onceki=temp;
        temp->sonraki=sonaEklenecek;
    }
    //printf("sonxxx\n\n");
}

void basaEkle(int plaka, char s_ad[], char c_bolge[],int komsu_sayisi)
{
    struct sehir* basaEklenecek = dugumOlustur(plaka,s_ad,c_bolge,komsu_sayisi);
    if (start == NULL)
    {
        start = basaEklenecek;
    }
    else
    {
        start->onceki=basaEklenecek;
        basaEklenecek->sonraki=start;
        start=basaEklenecek;
    }
    // printf("bas+++\n");
}

void arayaEkle(int kiminOnune_plaka,int plaka, char s_ad[], char c_bolge[],int komsu_sayisi)
{

    struct sehir* temp = start;
    struct sehir* arayaEklenecek = dugumOlustur(plaka,s_ad,c_bolge,komsu_sayisi);
    struct sehir* onceki = NULL;
    if (start == NULL)
    {
        start = arayaEklenecek;
    }
    else
    {
        while(temp->sonraki!=NULL)
        {
            if(temp->plaka_kodu==kiminOnune_plaka)
            {
                onceki=temp->onceki;
                break;
            }
            temp=temp->sonraki;
        }
        temp->onceki=arayaEklenecek;
        arayaEklenecek->sonraki=temp;
        arayaEklenecek->onceki=onceki;
        onceki->sonraki=arayaEklenecek;
    }
    //printf("ara----\n\n");
}

void bastanSil(int plaka, char s_ad[], char c_bolge[],int komsu_sayisi)
{
    if (start == NULL)
    {
        printf("\nHic sehir bulunmamaktadir.");
        return;
    }
    if (start->sonraki == NULL)
    {
        free(start);
        start=NULL;
        return;
    }

    struct sehir* ikinci = start->sonraki;
    free(start);
    ikinci->onceki = NULL;
    start=ikinci;
}

void sondanSil(int plaka, char s_ad[], char c_bolge[],int komsu_sayisi)
{
    if (start == NULL)
    {
        printf("\nHic sehir bulunmamaktadir.");
        return;
    }

    if (start->sonraki == NULL)
    {
        bastanSil(plaka,s_ad,c_bolge,komsu_sayisi);
        return;
    }

    struct sehir* temp = start;
    while (temp->sonraki != NULL)
    {
        temp = temp->sonraki;
    }
    struct sehir* oncekisehir = temp->onceki;
    free(temp);
    oncekisehir->sonraki = NULL;
}

void aradanSil(int silinecek)
{
    struct sehir* temp = start;
    while (temp->sonraki != NULL)
    {
        if (temp->plaka_kodu==silinecek)
            break;
        temp=temp->sonraki;
    }
    struct sehir* sonrakisehir = temp->sonraki;
    struct sehir* oncekisehir = temp->onceki;
    free(temp);
    oncekisehir->sonraki = sonrakisehir;
    sonrakisehir->onceki = oncekisehir;
}


void komsuEkle(char s_ad[], char k_ad[], char c_bolge[], int plaka)
{
    struct sehir* temp=start;

    struct komsu* temp1=komsuDugumOlustur(k_ad,c_bolge,plaka);

    while(temp->sonraki!=NULL)  //baglý listeyi dolas.
    {

        int sonuc=strcmp(temp->sehir_adi,s_ad);
        if(sonuc==0)
        {
            start2=temp->komsu_sonraki;
            if(temp->komsu_sonraki==NULL)  //hic komsu yoksa
            {
                temp->komsu_sonraki=temp1;
            }
            else
            {
                komsuSonaEkle(k_ad,c_bolge,plaka);
            }
        }

        temp=temp->sonraki;
    }

}

void yazdir(int plaka)
{
    struct sehir* temp=start;

    if(plaka==0)
    {
        int sayac=0;
        FILE *output=fopen("output.nkt","w");
        if(output==NULL)
        {
            printf("Dosya acilamadi.");
        }

        while (temp != NULL)
        {
            if(sayac==0)
            {
                printf("    NULL\n");
                printf("      |\n");
                fprintf(output,"    NULL\n");
                fprintf(output,"      |\n");

            }
            printf(" %d %s %s %d", temp->plaka_kodu,temp->sehir_adi,temp->cografi_bolge,temp->komsu_sayisi);
            fprintf(output," %d %s %s %d", temp->plaka_kodu,temp->sehir_adi,temp->cografi_bolge,temp->komsu_sayisi);

            while(temp->komsu_sonraki!=NULL)
            {
                printf(" - %d",temp->komsu_sonraki->plaka_kodu);
                fprintf(output," - %d",temp->komsu_sonraki->plaka_kodu);
                temp->komsu_sonraki=temp->komsu_sonraki->sonraki;
            }
            printf("- NULL");
            printf("\n      ||\n");
            fprintf(output,"- NULL");
            fprintf(output,"\n      ||\n");
            temp = temp->sonraki;
            sayac++;
        }
        printf("     NULL\n");
        fprintf(output,"     NULL\n");

        fclose(output);

    }
    else
    {
        while(temp!=NULL)
        {

            if(temp->plaka_kodu==plaka)
            {
                printf("sehrin adi: %s\n",temp->sehir_adi);
                printf("sehrin bulundugu cografi bolge: %s\n",temp->cografi_bolge);
                printf("sehrin komsu sayisi: %d\n",temp->komsu_sayisi);
                printf("sehrin komsularinin bilgileri:\n");
                while(temp->komsu_sonraki!=NULL)
                {
                    printf("- %d %s %s\n",temp->komsu_sonraki->plaka_kodu,temp->komsu_sonraki->komsu_adi,temp->komsu_sonraki->komsu_cografi_bolge);
                    temp->komsu_sonraki=temp->komsu_sonraki->sonraki;
                }
            }

            temp=temp->sonraki;
        }

    }

}
int main()
{
    FILE *dosya1 = fopen("sehirler.txt","r");
    char birsatir[200];
    const char *ayrac = ",";
    int kelime_sayac=0;
    int komsu_sayisi;
    int plaka;
    char plaka_[2];
    char sehir[50];
    char bolge[50];

    while(!feof(dosya1))
    {
        fgets(birsatir,200,dosya1);

        char *kelime = strtok(birsatir,ayrac);

        while (kelime != NULL)
        {
            if(kelime_sayac==0)
            {
                strcpy(plaka_,kelime);
            }
            else if(kelime_sayac==1)
            {
                strcpy(sehir,kelime);
            }
            else if(kelime_sayac==2)
            {
                strcpy(bolge,kelime);
            }

            kelime = strtok(NULL, ayrac);
            kelime_sayac++;
        }

        komsu_sayisi=(kelime_sayac-3);
        plaka=atoi(plaka_);

        struct sehir* temp=start;

        if(temp==NULL)
        {
            basaEkle(plaka,sehir,bolge,komsu_sayisi);
        }
        else
        {
            while(temp!=NULL)
            {
                if(temp->sonraki==NULL && plaka>temp->plaka_kodu)
                {
                    sonaEkle(plaka,sehir,bolge,komsu_sayisi);
                    break;
                }
                else if(temp->onceki==NULL && plaka < temp->plaka_kodu)
                {
                    basaEkle(plaka,sehir,bolge,komsu_sayisi);
                    //printf("sssss\n\n");
                    break;
                }
                else if(plaka> temp->plaka_kodu && plaka<temp->sonraki->plaka_kodu)
                {
                    // printf("%deeeeeee\n",temp->sonraki->plaka_kodu);
                    arayaEkle(temp->sonraki->plaka_kodu,plaka,sehir,bolge,komsu_sayisi);

                    break;
                }

                temp=temp->sonraki;
            }
        }
        kelime_sayac=0;

    }
    fclose(dosya1);

    FILE *dosya2 = fopen("sehirler.txt","r");


    char birsatir1[200];
    const char *ayrac1 = ",";
    const char *ayrac2 = "\0";
    int kelime_sayac1=-1;
    struct sehir* temp=start;
    char gonderilecek_sehir[50];
    char gecici[50];
    char komsu[50];



    while(!feof(dosya2))
    {
        fgets(birsatir1,200,dosya2);
        char *kelime1 = strtok(birsatir1,ayrac1);


        while(kelime1!=NULL)
        {

            kelime_sayac1++;
            if(kelime_sayac1==1)
            {

                strcpy(gonderilecek_sehir,kelime1);
                //printf("\n<<%s>>\n\n", gonderilecek_sehir);
            }
            if(kelime_sayac1>2)
            {

                while(temp!=NULL)
                {

                    int sonuc=strcmp(temp->sehir_adi,kelime1);
                    if(sonuc==0)
                    {
                        strcpy(komsu,kelime1);
                        komsuEkle(gonderilecek_sehir,komsu,temp->cografi_bolge,temp->plaka_kodu);

                        break;
                    }
                    temp=temp->sonraki;
                }

            }
            temp=start;
            strcpy(gecici,kelime1);
            kelime1 = strtok(NULL, ayrac1);
        }

        kelime_sayac1=-1;
        /*if(kelime1==NULL){
             while(temp!=NULL){
                int sonuc2=strcmp(temp->sehir_adi,gecici);
                if(sonuc2==0){
                    komsuEkle(gonderilecek_sehir,gecici,temp->cografi_bolge,temp->plaka_kodu);
                }
            temp=temp->sonraki;
           }
        }*/

        //printf("+++++%s  %s\n", gecici,gonderilecek_sehir);

    }

    fclose(dosya2);

    int secim;
    char eklenecek_sehir[50];
    int eklenecek_plaka;
    char silinecek_sehir[50];
    int silinecek_plaka;
    int eklesecenek;
    char ekleneceksehir[50];
    int eklenecekplaka;
    char eklenecekbolge[50];
    int onuneplaka;
    int eklenecekkomsusayisi;
    int bilgierisplaka;
    char sehirbulbolge[50];
    int komsusayisisehir;


    while(1)
    {

        printf("\n<--MENU-->");
        //printf("\n0-) bagli liste/dugum yapisi");
        printf("\n1-) Sehir ekleme");
        printf("\n2-) Sehir silme");
        printf("\n3-) Girilen plakadaki sehrin bilgileri");
        printf("\n4-) Herhangi bir bolgede bulunan sehirlerin bilgileri");
        printf("\n5-) Girilen komsu sayisindan fazla komsuya sahip olan sehirler listesi");
        printf("\n6-) Projedeki bagli liste yapisini gormek, ardindan menuden cikis");
        printf("\n\nSeciminizi yapin: ");
        scanf("%d", &secim);

        if(secim==6)
        {
            break;
        }

        struct sehir* temp=start;
        int sayac=0;
        int sayac2=0;
        int sayac3=0;

        switch(secim)
        {

        /*case 0:
            yazdir(0);
            break;*/
        case 1:

            printf("Eklemek istediginiz sehrin plaka kodunu giriniz: ");
            scanf("%d", &eklenecek_plaka);

            while(temp!=NULL)
            {

                if(eklenecek_plaka==temp->plaka_kodu)
                {

                    printf("Sehir zaten listede var. \n");
                    sayac++;
                    break;


                }

                temp=temp->sonraki;
            }

            if(sayac==0)
            {

                printf("Sehir listede yok. Eklemek isterseniz 1'e basiniz.\n\n");
                scanf("%d", &eklesecenek);
                if(eklesecenek==1)
                {
                    //printf("plaka: ");
                    //scanf("%d",&eklenecekplaka);
                    printf("Eklemek istediginiz sehrin bilgilerini bosluklu bir sekilde giriniz: (Onune eklenecegi sehrin plaka kodu-Eklenecek plaka-Sehir adi-Cografi bolge-Komsu sayisi):");
                    scanf("%d %d %s %s %d",&onuneplaka, &eklenecekplaka, ekleneceksehir, eklenecekbolge, &eklenecekkomsusayisi);
                    struct sehir* temp= start;
                    while(temp!=NULL)
                    {


                        if(temp->plaka_kodu==onuneplaka)
                        {

                            sayac2++;
                            if(temp->onceki==NULL)
                            {
                                basaEkle(eklenecekplaka,ekleneceksehir,eklenecekbolge,eklenecekkomsusayisi);
                                sayac3++;
                                printf("%d plakasina sahip olan sehir listeye eklendi.\n", eklenecekplaka);

                                break;

                            }
                        }

                        temp=temp->sonraki;
                    }

                    if(sayac2==0)
                    {
                        sonaEkle(eklenecekplaka,ekleneceksehir,eklenecekbolge,eklenecekkomsusayisi);
                        printf("%d plakasina sahip olan sehir listeye eklendi.\n", eklenecekplaka);

                        break;
                    }
                    if(sayac3==0)
                    {
                        arayaEkle(onuneplaka, eklenecekplaka, ekleneceksehir, eklenecekbolge, eklenecekkomsusayisi);
                        printf("Sehir eklendi.\n");
                        break;
                    }

                }
            }
            break;

        case 2:
            printf("Silmek istediginiz sehrin plaka kodunu giriniz: ");
            scanf("%d", &silinecek_plaka);
            while(temp!=NULL)
            {
                if(temp->plaka_kodu==silinecek_plaka)
                {
                    if(temp->onceki==NULL)
                    {
                        bastanSil(silinecek_plaka,temp->sehir_adi,temp->cografi_bolge,temp->komsu_sayisi);
                        printf("%d plakasina sahip olan sehir listeden silindi.\n", silinecek_plaka);
                        sayac++;
                        break;

                    }
                    if(temp->sonraki==NULL)
                    {
                        sondanSil(silinecek_plaka,temp->sehir_adi,temp->cografi_bolge,temp->komsu_sayisi);
                        printf("%d plakasina sahip olan sehir listeden silindi.\n", silinecek_plaka);
                        sayac++;
                        break;
                    }
                    aradanSil(silinecek_plaka);
                    printf("%d plakasina sahip olan sehir listeden silindi.\n", silinecek_plaka);
                    sayac++;
                    break;
                }
                temp=temp->sonraki;
            }
            if(sayac==0)
            {
                printf("Silmek istediginiz sehir zaten listede bulunmuyor.\n");
            }

            break;

        case 3:

            printf("Bilgilerine erismek istediginiz sehrin plakasini giriniz: ");
            scanf("%d", &bilgierisplaka);
            yazdir(bilgierisplaka);

            break;


        case 4:
            printf("Bulundugu sehirleri gormek istediginiz bolgeyi giriniz: ");
            scanf("%s", sehirbulbolge);
            while(temp!=NULL)
            {
                int sonuc=strcmp(sehirbulbolge,temp->cografi_bolge);
                if(sonuc==0)
                {
                    printf("%d %s %s %d\n",temp->plaka_kodu,temp->sehir_adi,temp->cografi_bolge,temp->komsu_sayisi);
                }
                temp=temp->sonraki;
            }

            break;

        case 5:
            printf("O komsu sayisindan fazla komsuya sahip olan sehirleri gormek icin bir sayi giriniz: ");
            scanf("%d", &komsusayisisehir);
            while(temp!=NULL)
            {
                if(temp->komsu_sayisi>komsusayisisehir)
                {
                    printf("%d %s %s %d\n",temp->plaka_kodu,temp->sehir_adi,temp->cografi_bolge,temp->komsu_sayisi);

                }
                temp=temp->sonraki;
            }

            break;




        }
    }
    printf("\ntum islemler sonucu bagli liste yapisi:\n\n");
    yazdir(0);


    return 0;

}
