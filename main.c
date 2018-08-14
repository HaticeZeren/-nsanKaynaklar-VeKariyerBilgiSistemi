#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
struct agac *agac_adresi;//diger fonksiyonlardanda agacin adresine erismek
struct bilgi{
  char adres[30];
  char tel[11];
 char mail[30];
 char dogum_tar[5];
struct bilgi *sonraki;
};
struct dil{
 char dil[20];
struct dil *sonraki;
};
struct ehliyet{
 char ehliyet[10];
struct ehliyet *sonraki;
};
struct egitim{
char okul[50];
 char okul_turu[40];
 char bolum[40];
 char bas_tarih[20];
 char bitis_tarih[20];
 char ortalama[6];
struct egitim *sonraki;
};
struct is_adresi{
char is_adres[50];
struct is_adresi *sonraki;
};
struct is_deneyimi{
char calistigi_yer[50];
struct is_adresi *adres;
char mevki[50];
char sure[10];
struct is_deneyimi *sonraki;
};

struct agac{
 char ad[50];
 int duzey;
struct bilgi *bilgi;
struct dil   *dil;
struct ehliyet *ehliyet;
struct egitim *egitim;
struct is_deneyimi *is_deneyimi;
struct agac *sag;
struct agac *sol;
};
void atama_dil_yap(struct dil **bas,struct dil **son,FILE *dosya);
void atama_bil_yap(struct bilgi **bas,struct bilgi **son,FILE *dosya);
void atama_ehl_yap(struct ehliyet **bas,struct ehliyet **son,FILE *dosya);
void atama_egitim_yap(struct egitim **bas,struct egitim **son,FILE *dosya);
void is_adresi_ekle(struct is_adresi **bas,struct is_adresi **son,FILE *dosya);
void atama_is_yap(struct is_deneyimi **is_bas,struct is_deneyimi **is_son,FILE *dosya);
void agaca_ekle(struct agac **agac,char ad[],struct bilgi *b_bas,struct dil *d_bas,struct ehliyet *ehl_bas,struct egitim *egt_bas,struct is_deneyimi *is_bas);
int veri_girisi_duzelt(char isim[]);
void adres_ekle(FILE *dosya);
void kisi_ekle(FILE *dosya);
void dil_yaz(struct dil *dil);
void ehl_yaz(struct ehliyet *ehl);
void egt_yaz(struct egitim *egt);
void is_adresi_yaz(struct is_adresi *adres);
void is_yaz(struct is_deneyimi *is);
void bilgi_dosya_yaz(struct bilgi *bilgi,FILE *dosya);
void dil_dosya_yaz(struct dil *dil,FILE *dosya);
void ehl_dosya_yaz(struct ehliyet *ehliyet,FILE *dosya);
void egt_dosya_yaz(struct egitim *egitim,FILE *dosya);
void is_adresi_dosya_yaz(struct is_adresi *is_adresi,FILE *dosya);
void is_dosya_deneyimi_yaz(struct is_deneyimi *is,FILE *dosya);
void inorder(struct agac *agac,FILE *dosya);
void dil_filtreleme(struct agac *agac,char dil[],int *sayi,int secim,FILE *coklu_fltr_dos);
void lisans_filtreleme(struct agac *agac,int *sayi,char okul_turu[],int secim,FILE *coklu_fltr_dos);
void dil_sayisi_filtreleme(struct agac *agac,int *sayi,int secim,FILE *coklu_fltr_dos);
void agaci_olustur();
void dosyadan_sil(struct agac *agaci,char isim[],FILE *dosya);
void deneyim_suresi_filtreleme(struct agac *agac,int *sayi,float yil,int secim,FILE *coklu_fltr_dos);
void   deneyimsiz_filtreleme(struct agac *agac,int *sayi,int secim,FILE *coklu_fltr_dos);
void yas_filtreleme(struct agac *agac,int *sayi,int yil,int istenilen_yas,int secim,FILE *coklu_fltr_dos);
void  ehliyet_filtreleme(struct agac *agac,int *sayi,char ehl_tipi[],int secim,FILE *coklu_fltr_dos);
void  ehliyetsiz_filtreleme(struct agac *agac,int *sayi,int secim,FILE *coklu_fltr_dos);
void dosyadan_eleme(int tane,FILE *coklu_fltr_dos,FILE *yeni_dosya);
void duzey_ekle(struct agac *agac,int *sayac,int *adim,struct agac *esol,struct agac *esag,int say,int *derinlik);
void duzeyli_yazdir(struct agac *agac);
void eleman_say(struct agac *agac,int *eleman_sayisi);
void dosya_bilgi(struct bilgi *bilgi,FILE *dosya);
void dosya_dil(struct dil *dili,FILE *dosya);
void dosya_ehliyet(struct ehliyet *ehl,FILE *dosya);
void dosya_egitim(struct egitim *egt,FILE *dosya);
void dosya_is_adres(struct is_adresi *adres,FILE *dosya);
void dosya_is_deneyimi(struct is_deneyimi *isi,FILE *dosya);
void dosyaya_yaz(struct agac *agac,char isim[],FILE *dosya);
void kisi_ara(struct agac *agac,char isim[],int *sayac,FILE *dosya);
void Liste(struct agac *agac,FILE *dosya);
void kisileri_dosyalama(FILE *yeni_dosya,int *sayac);
int main(){
setlocale(LC_ALL,"Turkish");
int secim;
FILE *coklu_fltr_dos=NULL;
FILE *yeni_dosya=NULL;
printf(".......................................................................\n");
printf("IS BASVURUSUNDA BULUNACAK ISENIZ MENU ICIN 1'E BASINIZ:\n");
printf("IS VEREN ISENIZ MENU ICIN 2'E BASINIZ:\n");
printf(".......................................................................\n\n");
scanf("%d",&secim);
if(secim==1){
 printf("MENU:\n");
 printf("sisteme kayit yapmak icin 1'e basiniz\n");
 printf("sistemdeki bilgilerinizi goruntelemek icin 2'ye tuslayiniz\n");
 printf("sistemden kaydinizi silmek icin 3'e tuslayiniz\n");
 printf("sistemdeki mevcut bilgilerinizi guncellemek icin 4'e basiniz\n");
 scanf("%d",&secim);
 printf(".......................................................................\n");
  switch(secim){
   case 1:
       {
         FILE *dosya=fopen("dosyalar.txt","a");
         kisi_ekle(dosya);
         agaci_olustur();
         break;
       }
   case 2:
    {
        char ad_soyad[50];
        int sayac=0;
        agaci_olustur();
        printf("ADINIZ_SOYADINIZ:");
          fflush(stdin);
          gets(ad_soyad);
        while(!veri_girisi_duzelt(ad_soyad)){//veri girisi kontrolu
           printf("ADINIZ_SOYADINIZ:");
           fflush(stdin);
           gets(ad_soyad);
        }
        kisi_ara(agac_adresi,ad_soyad,&sayac,NULL);
        if(sayac==0) printf("Sistemde Kaydiniz Bulunmamaktadir!");
        break;
    }
   case 3:
    {
        char ad_soyad[50];
        printf("Sistemden Bilgisini Silmek Istediginiz Kisi(AD_SOYAD):");
          fflush(stdin);
          gets(ad_soyad);
        while(!veri_girisi_duzelt(ad_soyad)){//veri girisi kontrolu
           printf("Sistemden Bilgisini Silmek Istediginiz Kisi(AD_SOYAD):");
           fflush(stdin);
           gets(ad_soyad);
        }
        FILE *dosya=fopen("silindikten_sonra.txt","w");
        agaci_olustur();
        dosyadan_sil(agac_adresi,ad_soyad,dosya);
        fclose(dosya);
        remove("dosyalar.txt");
        rename("silindikten_sonra.txt","dosyalar.txt");
        printf("\nISTENILEN KISININ KAYDI SILINMISTIR\n");
        break;
    }

   case 4:
    {
        char ad_soyad[50];
        printf("Sistemden Bilgisini Guncellemek Istediginiz Kisi(AD_SOYAD):");
          fflush(stdin);
          gets(ad_soyad);
        while(!veri_girisi_duzelt(ad_soyad)){//veri girisi kontrolu
           printf("Sistemden Bilgisini Guncellemek Istediginiz Kisi(AD_SOYAD):");
           fflush(stdin);
           gets(ad_soyad);
        }
        agaci_olustur();
         FILE *dosya=fopen("silindikten_sonra.txt","w");
        dosyadan_sil(agac_adresi,ad_soyad,dosya);
        fseek(dosya,-3L,SEEK_CUR);//dosyaya arada bosluk(yapýlan satýrbasi geri alindi) býrakmadan yazdýrabilmek icin bir geri aldik
        kisi_ekle(dosya);
        fclose(dosya);
        remove("dosyalar.txt");
        rename("silindikten_sonra.txt","dosyalar.txt");
        break;
    }

  }
}
else if(secim==2){
coklu_fltr_dos=fopen("gecici.txt","w");
fclose(coklu_fltr_dos);
int secim1;
 printf("......................................................................\n");
 printf("MENU:\n");
 printf("Is Basvurusunda bulananlari(duzeyleri ile birlikte)listelemek icin 1'e basiniz\n");
 printf("Aradiginiz Kisinin Bilgilerini goruntelemek icin 2'ye tuslayiniz\n");
 printf("Sistemde  Kayitli Olan Kisilerin Listesini Yazdirmak Icin 3'e basin\n");
 printf("Diger Coklu Ve Tekli filtreleme Menusu için 4'e basiniz:\n");
 scanf("%d",&secim1);
 printf("......................................................................\n");
switch(secim1){
case 1:
    {
     struct agac *esag=NULL;
     struct agac *esol=NULL;
     int sayac=0;
     int adim=0;
     int derinlik=0;
     int eleman_sayisi=0;
     int *ptr=&sayac;
     agaci_olustur();
     duzey_ekle(agac_adresi,ptr,&adim,esol,esag,0,&derinlik);
     duzeyli_yazdir(agac_adresi);
     eleman_say(agac_adresi,&eleman_sayisi);
     printf("\nAGACIN DERINLIGI:%d\n",derinlik);
     printf("KAYITLI KISI SAYISI:%d\n",eleman_sayisi);
     break;
    }
case 2:
    {
      char ad_soyad[50];
       int sayac=0;
        agaci_olustur();
        printf("sistemde aradaginiz kisinin AD_SOYAD:");
        fflush(stdin);
        gets(ad_soyad);
        while(!veri_girisi_duzelt(ad_soyad)){//veri girisi kontrolu
           printf("sistemde aradaginiz kisinin AD_SOYAD:");
           fflush(stdin);
           gets(ad_soyad);
        }
        int j;
         printf("KISI DOSYAYADA YAZDIRILSIN MI?(EVET ICIN:1/HAYIR:2)\n");
        scanf("%d",&j);
        if(j==1){
        printf("kisi bilgileri <Liste.txt> dosyasina kaydedilmistir!\n");
        FILE *dosya1=fopen("Liste.txt","w");
        kisi_ara(agac_adresi,ad_soyad,&sayac,dosya1);
        fclose(dosya1);
        }
        else if(j!=1){
           printf("dosyalama islemi gerceklestirilmedi!\n");
           FILE *dosya1=fopen("Liste.txt","w");
           kisi_ara(agac_adresi,ad_soyad,&sayac,dosya1);
           fclose(dosya1);
           remove("Liste.txt");
        }
        if(sayac==0) printf("Sistemde Kisinin Kaydi Bulunmamaktadir!");

      break;
    }
case 3:
{
     FILE *dosya1=fopen("Liste.txt","w");
     agaci_olustur(agac_adresi);
     Liste(agac_adresi,dosya1);
     fclose(dosya1);
     printf("SISTEMDE KAYITLI KISILAR <Liste.txt> DOSYASINA YAZDIRILMISTIR!\n");
    break;
}

case 4:
    {
    int sayi=0;
    int *ptr=&sayi;
    int filt_sec;
    int sec;
    int tane;
    int tane1;
    char i;
    int say=0;
         printf("........................................................\n");
         printf("MENU:\n");
         printf("Egitim bilgisine gore:\n");
         printf("En az iki dil bilenler\n");
         printf("Ehliyet Bilgisine gore\n");
         printf("girilen yasa gore\n");
         printf("Deneyime gore\n");
         printf("istenilen dile gore filtreleme\n");
         printf("Deneyimsiz Kisilerin Filtrelenmesi\n");
         printf("Ehliyetsiz Kisilerin Filtrelenmesi\n");
         printf("........................................................\n");
    printf("kac tane filtreleme secenegi sececeksiniz:\n");
    printf("(1 tane secerek TEKLI FILTRELEME yapabilirsiniz)\n");
    scanf("%d",&tane);
    printf("Coklu filtrelemede hangi seceneklere gore filtrelensin:\n");
    tane1=tane;
     while(tane>0){
        printf("Egitim bilgisine gore:(1)\n");
        printf("En az iki dil bilenler (2)\n");
        printf("Ehliyet Bilgisine gore(3)\n");
         printf("girilen yasa gore(4)\n");
         printf("Deneyime gore(5)\n");
         printf("istenilen dile gore filtreleme(6)\n");
         printf("Deneyimsiz Kisilerin Filtrelenmesi(7)\n");
        printf("Ehliyetsiz Kisilerin Filtrelenmesi(8)\n");
        scanf("%d",&filt_sec);
        if(filt_sec==1){
         char okul_turu[20];
        do{
        printf("En az lisans mezunlari icin 1'e bas:\n");
        printf("En az Yuksek_lisans mezunlari icin 2'e bas:\n");
        printf("En az Doktora mezunlari icin 3'e bas:\n");
        scanf("%d",&sec);
       if(sec==1) strcpy(okul_turu,"Lisans");
       else if(sec==2) strcpy(okul_turu,"Yuksek_Lisans");
       else if(sec==3) strcpy(okul_turu,"Doktora");
       else printf("yanlis secim!\n");
       }while(sec>3&&sec<1);
       agaci_olustur();
       lisans_filtreleme(agac_adresi,ptr,okul_turu,1,coklu_fltr_dos);
       tane--;
      }
      if(filt_sec==2){
        agaci_olustur();
        dil_sayisi_filtreleme(agac_adresi,ptr,1,coklu_fltr_dos);
        tane--;
      }
     if(filt_sec==3){
        char ehl_tipi[5];
        printf("Elemanin sahip olmasini istediginiz ehliyet tipi:");
        fflush(stdin);
        gets(ehl_tipi);
        while(!veri_girisi_duzelt(ehl_tipi)){
        printf("calisanlarda aradiginiz ehliyet tipi:");
        fflush(stdin);
        gets(ehl_tipi);
      }
        agaci_olustur();
       ehliyet_filtreleme(agac_adresi,ptr,ehl_tipi,1,coklu_fltr_dos);
       tane--;
     }
     if(filt_sec==4){
        int yil;
     int yas;
     printf("Istenilen yas degeri:");scanf("%d",&yas);
     printf("bulundugunuz yil:");scanf("%d",&yil);
     agaci_olustur();
     yas_filtreleme(agac_adresi,ptr,yil,yas,1,coklu_fltr_dos);
     tane--;
     }
     if(filt_sec==5){

      float yil;
      int *ptr=&sayi;
      printf("aradiginiz minimum deneyim suresini giriniz:");
      scanf("%f",&yil);
      agaci_olustur();
      deneyim_suresi_filtreleme(agac_adresi,ptr,yil,1,coklu_fltr_dos);
      tane--;
     }
     if(filt_sec==6){
        int sayi=0;
      char dil[30];
      int *ptr=&sayi;
      agaci_olustur();
      printf("calisanlarda aradiginiz dil:");
      fflush(stdin);
      gets(dil);
      while(!veri_girisi_duzelt(dil)){
        printf("calisanlarda aradiginiz dil:");
        fflush(stdin);
        gets(dil);
      }
      dil_filtreleme(agac_adresi,dil,ptr,1,coklu_fltr_dos);
     if(sayi==0) printf("bu dili bilen kimse bulunmamaktadir!\n");
     tane--;
     }
     if(filt_sec==7){
        int sayi=0;
       int *ptr=&sayi;
       agaci_olustur();
      deneyimsiz_filtreleme(agac_adresi,ptr,1,coklu_fltr_dos);
      if(sayi==0&&tane1==1) printf("Basvuruda bulunanlarda deyimsiz eleman bulunamadi!\n");
      tane--;
     }
     if(filt_sec==8){
          int sayi=0;
          int *ptr=&sayi;
         agaci_olustur();
        ehliyetsiz_filtreleme(agac_adresi,ptr,1,coklu_fltr_dos);
        if(sayi==0&&tane1==1) printf("Istenilen ozellige sahip eleman bulunamadi!\n");
        tane--;
     }
     }
     yeni_dosya=fopen("filtreleme.txt","w");
     fclose(yeni_dosya);
     dosyadan_eleme(tane1,coklu_fltr_dos,yeni_dosya);
     printf("KISI BIGILERI DOSYALANSIN MI?(E/H):");
     do{
     scanf("%c",&i);
     if(i=='E'||i=='e'){
        kisileri_dosyalama(yeni_dosya,&say);
         remove("filtreleme.txt");
        if(say==0) printf("Dosyalama Yapilmistir!\n");
     }
     else if(i=='H'||i=='h'){
         remove("filt_kisiler.txt");
        remove("filtreleme.txt");
        printf("Isteginiz Uzerine Dosyalama Yapilmamistir!\n");
     }
     }while(i!='E'&&i!='e'&&i!='H'&&i!='h');
  break;
    }
}
}

return 0;
}
void atama_bil_yap(struct bilgi **bas,struct bilgi **son,FILE *dosya){
 char karakter[50];
 char adres[30];
 char tel[11];
 char mail[50];
 char dogum_tar[5];
struct bilgi *yeni;
do{
 if(*bas==NULL){
  yeni=malloc(sizeof(struct bilgi));
  fscanf(dosya,"%s",adres);
  strcpy((yeni->adres),adres);
  fscanf(dosya,"%s",tel);
  strcpy((yeni->tel),tel);
  fscanf(dosya,"%s",mail);
  strcpy((yeni->mail),mail);
  fscanf(dosya,"%s",dogum_tar);
  strcpy((yeni->dogum_tar),dogum_tar);
  (*bas)=yeni;
  (*son)=(*bas);
  (*son)->sonraki=NULL;
 }
 else{
yeni=malloc(sizeof(struct bilgi));
  fscanf(dosya,"%s",adres);
  strcpy((yeni->adres),adres);
  fscanf(dosya,"%s",tel);
  strcpy((yeni->tel),tel);
  fscanf(dosya,"%s",mail);
  strcpy((yeni->mail),mail);
  fscanf(dosya,"%s",dogum_tar);
  strcpy((yeni->dogum_tar),dogum_tar);
  (*son)->sonraki=yeni;
  (*son)=yeni;
  (*son)->sonraki=NULL;
 }
 if(!feof(dosya)) fscanf(dosya,"%s",karakter);
 else return;
}while(strcmp(karakter,",")==0);
long sayi=strlen(karakter);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
if(!feof(dosya)) fseek(dosya,(-1*sayi),SEEK_CUR);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
}
void atama_dil_yap(struct dil **bas,struct dil **son,FILE *dosya){
 char dil[20];
char karakter[50];
struct dil *yeni;
do{
 if(*bas==NULL){
  yeni=malloc(sizeof(struct dil));
   fscanf(dosya,"%s",dil);
   strcpy((yeni->dil),dil);
  (*bas)=yeni;
  (*son)=(*bas);
  (*son)->sonraki=NULL;
 }
 else{
yeni=malloc(sizeof(struct dil));
   fscanf(dosya,"%s",dil);
   strcpy((yeni->dil),dil);
  (*son)->sonraki=yeni;
  (*son)=yeni;
  (*son)->sonraki=NULL;
 }
 if(!feof(dosya)) fscanf(dosya,"%s",karakter);
 else return;
}while(strcmp(karakter,",")==0);
long sayi=strlen(karakter);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
if(!feof(dosya)) fseek(dosya,(-1*sayi),SEEK_CUR);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
}
void atama_ehl_yap(struct ehliyet **bas,struct ehliyet **son,FILE *dosya){
 char ehliyet[10];
char karakter[50];
struct ehliyet *yeni;
do{
 if(*bas==NULL){
  yeni=malloc(sizeof(struct ehliyet));
   fscanf(dosya,"%s",ehliyet);
   strcpy((yeni->ehliyet),ehliyet);
  (*bas)=yeni;
  (*son)=(*bas);
  (*son)->sonraki=NULL;
 }
 else{
yeni=malloc(sizeof(struct ehliyet));
   fscanf(dosya,"%s",ehliyet);
   strcpy((yeni->ehliyet),ehliyet);
  (*son)->sonraki=yeni;
  (*son)=yeni;
  (*son)->sonraki=NULL;
 }
 if(!feof(dosya)) fscanf(dosya,"%s",karakter);
 else return;
}while(strcmp(karakter,",")==0);
long sayi=strlen(karakter);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
if(!feof(dosya)) fseek(dosya,(-1*sayi),SEEK_CUR);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
}

void atama_egitim_yap(struct egitim **bas,struct egitim **son,FILE *dosya){
 char okul[50];
 char okul_turu[40];
 char bolum[40];
 char bas_tarih[20];
 char bitis_tarih[20];
 char ortalama[6];
 char karakter[50];
struct egitim *yeni;
do{
 if(*bas==NULL){
  yeni=malloc(sizeof(struct egitim));
   fscanf(dosya,"%s",okul);
   strcpy((yeni->okul),okul);
   fscanf(dosya,"%s",okul_turu);
   strcpy((yeni->okul_turu),okul_turu);
   fscanf(dosya,"%s",bolum);
   strcpy((yeni->bolum),bolum);
   fscanf(dosya,"%s",bas_tarih);
   strcpy((yeni->bas_tarih),bas_tarih);
   fscanf(dosya,"%s",bitis_tarih);
   strcpy((yeni->bitis_tarih),bitis_tarih);
   fscanf(dosya,"%s",ortalama);
   strcpy((yeni->ortalama),ortalama);
  (*bas)=yeni;
  (*son)=(*bas);
  (*son)->sonraki=NULL;
 }
 else{
yeni=malloc(sizeof(struct egitim));
   fscanf(dosya,"%s",okul);
   strcpy((yeni->okul),okul);
   fscanf(dosya,"%s",okul_turu);
   strcpy((yeni->okul_turu),okul_turu);
   fscanf(dosya,"%s",bolum);
   strcpy((yeni->bolum),bolum);
   fscanf(dosya,"%s",bas_tarih);
   strcpy((yeni->bas_tarih),bas_tarih);
   fscanf(dosya,"%s",bitis_tarih);
   strcpy((yeni->bitis_tarih),bitis_tarih);
   fscanf(dosya,"%s",ortalama);
   strcpy((yeni->ortalama),ortalama);
  (*son)->sonraki=yeni;
  (*son)=yeni;
  (*son)->sonraki=NULL;
 }
 if(!feof(dosya)) fscanf(dosya,"%s",karakter);
 else return;
}while(strcmp(karakter,",")==0);
long sayi=strlen(karakter);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
if(!feof(dosya)) fseek(dosya,(-1*sayi),SEEK_CUR);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
}
void is_adresi_ekle(struct is_adresi **bas,struct is_adresi **son,FILE *dosya){
struct is_adresi *yeni;
char is_adres[20];
char karakter[50];
do{
if(*bas==NULL){
  yeni=malloc(sizeof(struct is_adresi));
  fscanf(dosya,"%s",is_adres);
  strcpy((yeni->is_adres),is_adres);
  (*bas)=yeni;
  (*son)=(*bas);
  (*son)->sonraki=NULL;
}
else{
  yeni=malloc(sizeof(struct is_adresi));
  fscanf(dosya,"%s",is_adres);
  strcpy((yeni->is_adres),is_adres);
  (*son)->sonraki=yeni;
  (*son)=yeni;
  (*son)->sonraki=NULL;
}
if(!feof(dosya)) fscanf(dosya,"%s",karakter);
 else return;
}while(strcmp(karakter,",")==0);
long sayi=strlen(karakter);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
if(!feof(dosya)) fseek(dosya,(-1*sayi),SEEK_CUR);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
}
void atama_is_yap(struct is_deneyimi **is_bas,struct is_deneyimi **is_son,FILE *dosya){
struct is_deneyimi *yeni;
char karakter[50];
char calistigi_yer[50];
char mevki[50];
char sure[10];
do{
struct is_adresi *bas=NULL;
struct is_adresi *son=NULL;
if(*is_bas==NULL){
    yeni=malloc(sizeof(struct is_deneyimi));
    fscanf(dosya,"%s",calistigi_yer);
    strcpy((yeni->calistigi_yer),calistigi_yer);
    is_adresi_ekle(&bas,&son,dosya);
    yeni->adres=bas;
    fscanf(dosya,"%s",mevki);
    strcpy((yeni->mevki),mevki);
    fscanf(dosya,"%s",sure);
    strcpy((yeni->sure),sure);
    *is_bas=yeni;
    (*is_son)=(*is_bas);
    (*is_son)->sonraki=NULL;
}
else{
   yeni=malloc(sizeof(struct is_deneyimi));
    fscanf(dosya,"%s",calistigi_yer);
    strcpy((yeni->calistigi_yer),calistigi_yer);
    is_adresi_ekle(&bas,&son,dosya);
    yeni->adres=bas;
    fscanf(dosya,"%s",mevki);
    strcpy((yeni->mevki),mevki);
   fscanf(dosya,"%s",sure);
    strcpy((yeni->sure),sure);
   (*is_son)->sonraki=yeni;
   (*is_son)=yeni;
   (*is_son)->sonraki=NULL;
}
if(!feof(dosya)) fscanf(dosya,"%s",karakter);
 else return;
}while(strcmp(karakter,",")==0);
long sayi=strlen(karakter);
//printf("dosya konumu:%ld byte\n",ftell(dosya));
if(!feof(dosya)) fseek(dosya,(-1*sayi),SEEK_CUR);
//printf("dosya konumu:%ld byte\n",ftell(dosya));

}
void agaca_ekle(struct agac **agac,char ad[],struct bilgi *b_bas,struct dil *d_bas,struct ehliyet *ehl_bas,struct egitim *egt_bas,struct is_deneyimi *is_bas){
if(*agac==NULL){
(*agac)=malloc(sizeof(struct agac));
strcpy(((*agac)->ad),ad);
(*agac)->duzey=0;
(*agac)->bilgi=b_bas;
(*agac)->dil=d_bas;
(*agac)->ehliyet=ehl_bas;
(*agac)->egitim=egt_bas;
(*agac)->is_deneyimi=is_bas;
(*agac)->sag=NULL;
(*agac)->sol=NULL;
}
else{
    if(strcmp(((*agac)->ad),(ad))>0)
        agaca_ekle(&((*agac)->sol),ad,b_bas,d_bas,ehl_bas,egt_bas,is_bas);
    else if(strcmp(((*agac)->ad),(ad))<0)
        agaca_ekle(&((*agac)->sag),ad,b_bas,d_bas,ehl_bas,egt_bas,is_bas);
}
}

int veri_girisi_duzelt(char isim[]){
int i;
for(i=0;isim[i]!='\0';i++){
 if(islower(isim[0])) isim[0]=toupper(isim[0]);
 if(isim[i]==' '){
    isim[i]='_';
    i++;
    if(isim[i]==' '){
        printf("YANLIS VERI GIRISI LUTFEN KELIMELER ARASI BIR BOSLUK BIRAKIN!!\n");
        return 0;
    }
  if(islower(isim[i])) isim[i]=toupper(isim[i]);
  i++;
 }
 if(i!=0&&isupper(isim[i])) isim[i]=tolower(isim[i]);
}
return 1;
}
void adres_ekle(FILE *dosya){
char calistigi_adres[20];
int secim;
printf("calistiginiz yerin bulundugu adres sayisi:\n");
scanf("%d",&secim);
if(1){
    while(secim!=0){
      printf("adres:");
      fflush(stdin);
      gets(calistigi_adres);
      while(!veri_girisi_duzelt(calistigi_adres)){//yanlıs veri girisinin engellenmesi icin kontrol
        printf("adres:");
      fflush(stdin);
      gets(calistigi_adres);
      }
      fprintf(dosya,"%s  ",calistigi_adres);
      secim--;
      if(secim!=0){
        fputc(',',dosya);
      fputc(' ',dosya);
      }
    }
   fprintf(dosya,"%c    ",' ');
}
}
void kisi_ekle(FILE *dosya){
char isim_soyisim[50];
char adres[50];
char tel[20];
char mail[50];
char dogum_tarihi[10];
char dil[30];
char ehliyet[5];
char okul_adi[50];
char okul_turu[50];
char bolum[50];
char baslama_tarihi[20];
char bitirme_tarihi[20];
char ortalama[10];
char calistigi_yer[50];
char mevki[50];
char yil[6];
int secim;

printf("\n");
printf("*********************************************************\n");
printf("NOT:\n");
printf("BILGILERINIZI SISTEME GIRERKEN KELIMELER ARASI BIR BOSLUK KOYUNUZ!\n");
printf("*********************************************************\n");

printf("ISIM_SOYAD :");
fflush(stdin);
gets(isim_soyisim);
while(!veri_girisi_duzelt(isim_soyisim)){//veri girisi kontrolu
 printf("ISIM_SOYAD :");
fflush(stdin);
gets(isim_soyisim);
}
fflush(stdin);
printf("ADRES:");
gets(adres);
while(!veri_girisi_duzelt(adres)){//veri girisi kontrolu
fflush(stdin);
printf("ADRES:");
gets(adres);
}
fflush(stdin);
printf("TELEFON:");
gets(tel);
while(!veri_girisi_duzelt(tel)){
fflush(stdin);
printf("TELEFON:");
gets(tel);
}
printf("MAIL:");
scanf("%49s",mail);
printf("DOGUM TARIHI:\n");
scanf("%9s",dogum_tarihi);
fputc('\n',dosya);
fprintf(dosya,"%s          ",isim_soyisim);
fprintf(dosya,"%s     ",adres);
fprintf(dosya,"%s     ",tel);
fprintf(dosya,"%s     ",mail);
fprintf(dosya,"%s     ",dogum_tarihi);
printf("kac dil biliyorsunuz\n");
scanf("%d",&secim);
if(secim==0) fprintf(dosya,"%s    ","dil_bilmiyor");
else{
    while(secim!=0){
      printf("DIL:");
      fflush(stdin);
      gets(dil);
      fflush(stdin);
      while(!veri_girisi_duzelt(dil)){//veri kontrolu
         printf("DIL:");
         fflush(stdin);
         gets(dil);
      }
      fprintf(dosya,"%s  ",dil);
      secim--;
      if(secim!=0){
      fputc(',',dosya);
      fputc(' ',dosya);
      }
    }
   fprintf(dosya,"%c    ",' ');
}
printf("Kac ehliyetiniz var(ehliyetiniz yoksa 0 giriniz)\n");
scanf("%d",&secim);
if(secim==0) fprintf(dosya,"%s    ","ehliyeti_yok");
else{
    while(secim!=0){
      printf("ehliyet tipi:");
         fflush(stdin);
         gets(ehliyet);
      while(!veri_girisi_duzelt(ehliyet)){//veri girisi konrolu
         printf("ehliyet tipi:");
         fflush(stdin);
         gets(ehliyet);
      }
      fprintf(dosya,"%s  ",ehliyet);
      secim--;
      if(secim!=0){
      fputc(',',dosya);
      fputc(' ',dosya);
      }
    }
   fprintf(dosya,"%c    ",' ');
}
printf("mezun oldugunuz okul sayisi(lise dahil)\n");
scanf("%d",&secim);
   if(1){
    while(secim!=0){
      printf("OKUL_ADI:");
      fflush(stdin);
      gets(okul_adi);
      while(!veri_girisi_duzelt(okul_adi)){//veri girisi konrolu
         printf("OKUL_ADI:");
         fflush(stdin);
         gets(okul_adi);
      }
      fprintf(dosya,"%s  ",okul_adi);
      printf("OKUL_TURU:");
      fflush(stdin);
      gets(okul_turu);
      while(!veri_girisi_duzelt(okul_turu)){
        printf("OKUL_TURU:");
        fflush(stdin);
        gets(okul_turu);
      }
      fprintf(dosya,"%s  ",okul_turu);
      printf("BOLUM:");
      fflush(stdin);
      gets(bolum);
      while(!veri_girisi_duzelt(bolum)){
        printf("BOLUM:");
        fflush(stdin);
        gets(bolum);
      }
      fprintf(dosya,"%s  ",bolum);
      printf("BASLAMA_TARIHI:");
      scanf("%19s",baslama_tarihi);
      fprintf(dosya,"%s  ",baslama_tarihi);
      //printf("BITIRME_TARIHI:");
      //scanf("%19s",bitirme_tarihi);
      printf("BITIRME_TARIHI:");
      fflush(stdin);
      gets(bitirme_tarihi);//devam ediyor yazısı için
      while(!veri_girisi_duzelt(bitirme_tarihi)){
        printf("BITIRME_TARIHI:");
        fflush(stdin);
        gets(bitirme_tarihi);
      }
      fprintf(dosya,"%s  ",bitirme_tarihi);
      printf("ORTALAMA:");
      scanf("%9s",ortalama);
      fprintf(dosya,"%s  ",ortalama);
      secim--;
      if(secim!=0){
      fputc(',',dosya);
      fputc(' ',dosya);
      }
    }
   fprintf(dosya,"%c    ",' ');
}
printf("Daha oncesinde calistiginiz is sayisi\n");
scanf("%d",&secim);
if(secim==0){
fprintf(dosya,"%s  ","deneyimi_yok");
fprintf(dosya,"%s  ","--");
fprintf(dosya,"%s  ","--");
fprintf(dosya,"%s  ","0");
}
else{
    while(secim!=0){
      printf("CALISTIGI YER:");
      fflush(stdin);
      gets(calistigi_yer);
      while(!veri_girisi_duzelt(calistigi_yer)){
        printf("CALISTIGI YER:");
        fflush(stdin);
        gets(calistigi_yer);
      }
      fprintf(dosya,"%s  ",calistigi_yer);
      adres_ekle(dosya);
      printf("CALISTIGINIZ MEVKI:");
      fflush(stdin);
      gets(mevki);
      while(!veri_girisi_duzelt(mevki)){
        printf("CALISTIGINIZ MEVKI:");
        fflush(stdin);
        gets(mevki);
      }
      fprintf(dosya,"%s  ",mevki);
      printf("CALISTIGINIZ SURE:");
      scanf("%5s",yil);
      fprintf(dosya,"%s  ",yil);
      secim--;
      if(secim!=0){
      fputc(',',dosya);
      fputc(' ',dosya);
      }
    }
   fprintf(dosya,"%c    ",' ');
}
fclose(dosya);
}
void dil_yaz(struct dil *dil){
struct dil *e=dil;
while(e!=NULL){
    printf("DIL:%s",e->dil);
    if((e->sonraki)!=NULL) printf(",");
    e=e->sonraki;
}
printf("\n");
}
void ehl_yaz(struct ehliyet *ehl){
struct ehliyet *e=ehl;
while(e!=NULL){
    printf("Ehliyet_Tipi:%s",e->ehliyet);
    if((e->sonraki)!=NULL) printf(",");
    e=e->sonraki;
}
printf("\n");
}
void egt_yaz(struct egitim *egt){
struct egitim *e=egt;
while(e!=NULL){
    printf("................\n");
    printf("Okul_Adi:%s\n",e->okul);
    printf("Okul_Turu:%s\n",e->okul_turu);
    printf("Bolum:%s\n",e->bolum);
    printf("Baslama_Tarihi:%s\n",e->bas_tarih);
    printf("Bitis_Tarihi:%s\n",e->bitis_tarih);
    printf("Ortalama:%s\n",e->ortalama);
    e=e->sonraki;
}
printf("\n");
}
void is_adresi_yaz(struct is_adresi *adres){
struct is_adresi *e=adres;
while(e!=NULL){
   printf("Is_adresi:%s",e->is_adres);
   if((e->sonraki)!=NULL) printf(",");
  e=e->sonraki;
}
printf("\n");
}
void is_yaz(struct is_deneyimi *is){
struct is_deneyimi *e=is;
while(e!=NULL){
    printf("Calistigi_Yerin_Ismi:%s\n",e->calistigi_yer);
    is_adresi_yaz(e->adres);
    printf("Mevki:%s\n",e->mevki);
    printf("Calisilan Sure(yil):%s\n",e->sure);
    if((e->sonraki)!=NULL) printf("\n...................\n");
   e=e->sonraki;
}
printf("\n");
}

void bilgi_dosya_yaz(struct bilgi *bilgi,FILE *dosya){
struct bilgi *e=bilgi;
while(e!=NULL){
    fputc(' ',dosya);
    fputc(' ',dosya);
    fprintf(dosya,"%s     ",(e->adres));
    fputc(' ',dosya);
    fputc(' ',dosya);
    fprintf(dosya,"%s     ",(e->tel));
    fputc(' ',dosya);
    fputc(' ',dosya);
    fprintf(dosya,"%s     ",(e->mail));
    fputc(' ',dosya);
    fputc(' ',dosya);
    fprintf(dosya,"%s     ",(e->dogum_tar));
    e=e->sonraki;
}
fputc(' ',dosya);
fputc(' ',dosya);
}
void dil_dosya_yaz(struct dil *dil,FILE *dosya){
struct dil *e=dil;
fputc(' ',dosya);
fputc(' ',dosya);
while(e!=NULL){
  fprintf(dosya,"%s  ",(e->dil));
  if((e->sonraki!=NULL)){
    fputc(',',dosya);
    fputc(' ',dosya);
  }
  e=e->sonraki;
}
fputc(' ',dosya);
fputc(' ',dosya);
}
void ehl_dosya_yaz(struct ehliyet *ehliyet,FILE *dosya){
struct ehliyet *e=ehliyet;
fputc(' ',dosya);
fputc(' ',dosya);
while(e!=NULL){
  fprintf(dosya,"%s ",(e->ehliyet));
  if((e->sonraki!=NULL)){
    fputc(',',dosya);
    fputc(' ',dosya);
  }
  e=e->sonraki;
}
fputc(' ',dosya);
fputc(' ',dosya);
}

void egt_dosya_yaz(struct egitim *egitim,FILE *dosya){
struct egitim *e=egitim;
while(e!=NULL){
  fprintf(dosya,"%s   ",(e->okul));
  fprintf(dosya,"%s   ",(e->okul_turu));
  fprintf(dosya,"%s   ",(e->bolum));
  fprintf(dosya,"%s   ",(e->bas_tarih));
  fprintf(dosya,"%s   ",(e->bitis_tarih));
  fprintf(dosya,"%s   ",(e->ortalama));
  if((e->sonraki!=NULL)){
    fputc(',',dosya);
    fputc(' ',dosya);
  }
  e=e->sonraki;
}
fputc(' ',dosya);
fputc(' ',dosya);
}
void is_adresi_dosya_yaz(struct is_adresi *is_adresi,FILE *dosya){
struct is_adresi *e=is_adresi;
while(e!=NULL){
  fprintf(dosya,"%s    ",(e->is_adres));
  if((e->sonraki!=NULL)){
    fputc(',',dosya);
    fputc(' ',dosya);
  }
  e=e->sonraki;
}
fputc(' ',dosya);
fputc(' ',dosya);
}
void is_dosya_deneyimi_yaz(struct is_deneyimi *is,FILE *dosya){
struct is_deneyimi *e=is;
while(e!=NULL){
  fprintf(dosya,"%s   ",(e->calistigi_yer));
  is_adresi_dosya_yaz((e->adres),dosya);
  fprintf(dosya,"%s   ",(e->mevki));
  fprintf(dosya,"%s   ",(e->sure));
  if((e->sonraki!=NULL)){
    fputc(',',dosya);
    fputc(' ',dosya);
  }
  e=e->sonraki;
}
char karakter='\n';
fprintf(dosya,"%c",karakter);
}


void inorder(struct agac *agac,FILE *dosya){
if(agac!=NULL){
    inorder((agac->sol),dosya);
    fprintf(dosya,"%s",(agac->ad));
    bilgi_dosya_yaz((agac->bilgi),dosya);
    dil_dosya_yaz((agac->dil),dosya);
    ehl_dosya_yaz((agac->ehliyet),dosya);
    egt_dosya_yaz((agac->egitim),dosya);
    is_dosya_deneyimi_yaz((agac->is_deneyimi),dosya);
    inorder((agac->sag),dosya);
}
}

void dil_filtreleme(struct agac *agac,char dil[],int *sayi,int secim,FILE *coklu_fltr_dos){
int sayac=0;
if(agac!=NULL){
    dil_filtreleme((agac->sol),dil,sayi,secim,coklu_fltr_dos);
    while((agac->dil)!=NULL && sayac==0){
     if(strcmp((agac->dil->dil),(dil))==0){
        sayac++;
        (*sayi)++;
       if(secim==0) printf("%s     \n",agac->ad);
       else if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
             //printf("%s     \n",agac->ad);
            fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
     }
     (agac->dil)=(agac->dil->sonraki);
    }
    dil_filtreleme((agac->sag),dil,sayi,secim,coklu_fltr_dos);
}
}
void lisans_filtreleme(struct agac *agac,int *sayi,char okul_turu[],int secim,FILE *coklu_fltr_dos){
int sayac=0;
if(agac!=NULL){
    lisans_filtreleme((agac->sol),sayi,okul_turu,secim,coklu_fltr_dos);
    while((agac->egitim)!=NULL && sayac==0){
     if(strcmp((agac->egitim->okul_turu),(okul_turu))==0){
        sayac++;
       if(secim==0) printf("%s     \n",agac->ad);
       else if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
             //printf("%s     \n",agac->ad);
            fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
       if(sayac!=0&&(*sayi)==0) (*sayi)++;
     }
     (agac->egitim)=(agac->egitim->sonraki);
    }
    lisans_filtreleme((agac->sag),sayi,okul_turu,secim,coklu_fltr_dos);
}
}
void dil_sayisi_filtreleme(struct agac *agac,int *sayi,int secim,FILE *coklu_fltr_dos){
int sayac=0;
if(agac!=NULL){
    dil_sayisi_filtreleme((agac->sol),sayi,secim,coklu_fltr_dos);
    while((agac->dil)!=NULL && sayac<2){
        sayac++;
      if(sayac==2){
      if(secim==0) printf("%s\n",agac->ad);
      else if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
            fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
      (*sayi)++;
      }
     (agac->dil)=(agac->dil->sonraki);
    }
    dil_sayisi_filtreleme((agac->sag),sayi,secim,coklu_fltr_dos);
}
}
void agaci_olustur(){
struct agac *agac=NULL;
char ad[20];
FILE *dosya=fopen("dosyalar.txt","r");
fseek(dosya,0,SEEK_SET);
if(dosya==NULL) printf("dosya acilamadi");
while(!feof(dosya)){
struct bilgi *b_bas=NULL;
struct bilgi *b_son=NULL;
struct dil *d_bas=NULL;
struct dil *d_son=NULL;
struct ehliyet *ehl_bas=NULL;
struct ehliyet *ehl_son=NULL;
struct egitim *egt_bas=NULL;
struct egitim *egt_son=NULL;
struct is_deneyimi *is_bas=NULL;
struct is_deneyimi *is_son=NULL;
fscanf(dosya,"%s",ad);
atama_bil_yap(&b_bas,&b_son,dosya);
atama_dil_yap(&d_bas,&d_son,dosya);
atama_ehl_yap(&ehl_bas,&ehl_son,dosya);
atama_egitim_yap(&egt_bas,&egt_son,dosya);
atama_is_yap(&is_bas,&is_son,dosya);
agaca_ekle(&agac,ad,b_bas,d_bas,ehl_bas,egt_bas,is_bas);
}
fclose(dosya);
agac_adresi=agac;
}
void dosyadan_sil(struct agac *agaci,char isim[],FILE *dosya){
if(agaci!=NULL){
    dosyadan_sil(agaci->sol,isim,dosya);
    if(strcmp(agaci->ad,isim)!=0){
    fprintf(dosya,"%s",(agaci->ad));
    bilgi_dosya_yaz((agaci->bilgi),dosya);
    dil_dosya_yaz((agaci->dil),dosya);
    ehl_dosya_yaz((agaci->ehliyet),dosya);
    egt_dosya_yaz((agaci->egitim),dosya);
    is_dosya_deneyimi_yaz((agaci->is_deneyimi),dosya);
    }
    dosyadan_sil(agaci->sag,isim,dosya);
}
}
void deneyim_suresi_filtreleme(struct agac *agac,int *sayi,float yil,int secim,FILE *coklu_fltr_dos){
int sayac=0;
float sure;
float toplam=0;
if(agac!=NULL){
    deneyim_suresi_filtreleme((agac->sol),sayi,yil,secim,coklu_fltr_dos);
    while((agac->is_deneyimi)!=NULL&&sayac==0){
        sure=atof(agac->is_deneyimi->sure);
        toplam=sure+toplam;
       (agac->is_deneyimi)=(agac->is_deneyimi->sonraki);
    }
          if(toplam>=yil){
           if(secim==0)  printf("%s,toplam deneyim suresi:%f\n",agac->ad,toplam);
           else if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
             //printf("%s,toplam deneyim suresi:%f\n",agac->ad,toplam);
            fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
            sayac++;
            toplam=0;
            if((*sayi)==0) (*sayi)++;
          }
    deneyim_suresi_filtreleme((agac->sag),sayi,yil,secim,coklu_fltr_dos);
}
}
void   deneyimsiz_filtreleme(struct agac *agac,int *sayi,int secim,FILE *coklu_fltr_dos){
int sayac=0;
float sure;
if(agac!=NULL){
    deneyimsiz_filtreleme((agac->sol),sayi,secim,coklu_fltr_dos);
    while((agac->is_deneyimi)!=NULL&&sayac==0){
        sure=atof(agac->is_deneyimi->sure);
        if(sure==0){
            sayac++;
            if(secim==0) printf("%s\n",agac->ad);
            else if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
             //printf("%s\n",agac->ad);
            fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
            if((*sayi)==0) (*sayi)++;
          }
     (agac->is_deneyimi)=(agac->is_deneyimi->sonraki);
    }

    deneyimsiz_filtreleme((agac->sag),sayi,secim,coklu_fltr_dos);
}
}
void yas_filtreleme(struct agac *agac,int *sayi,int yil,int istenilen_yas,int secim,FILE *coklu_fltr_dos){
int sayac=0;
int yasi;
if(agac!=NULL){
    yas_filtreleme((agac->sol),sayi,yil,istenilen_yas,secim,coklu_fltr_dos);
    while((agac->bilgi)!=NULL&&sayac==0){
          yasi=(yil)-(atoi(agac->bilgi->dogum_tar));
        if(yasi<=istenilen_yas){
            sayac++;
            if(secim==0) printf("%s,yasi:%d\n",agac->ad,yasi);
            else if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
             //printf("%s,yasi:%d\n",agac->ad,yasi);
             fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
            if((*sayi)==0) (*sayi)++;
          }
          (agac->bilgi)=(agac->bilgi->sonraki);
         }

    yas_filtreleme((agac->sag),sayi,yil,istenilen_yas,secim,coklu_fltr_dos);
}
}
void  ehliyet_filtreleme(struct agac *agac,int *sayi,char ehl_tipi[],int secim,FILE *coklu_fltr_dos){
int sayac=0;
if(agac!=NULL){
    ehliyet_filtreleme((agac->sol),sayi,ehl_tipi,secim,coklu_fltr_dos);
    while((agac->ehliyet)!=NULL && sayac==0){
     if(strcmp((agac->ehliyet->ehliyet),(ehl_tipi))==0){
        sayac++;
       if(secim==0)  printf("%s,ehliyet tipi:%s\n",agac->ad,ehl_tipi);
       else if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
             //printf("%s,ehliyet tipi:%s\n",agac->ad,ehl_tipi);
             fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
       if((*sayi)==0) (*sayi)++;
     }
     (agac->ehliyet)=(agac->ehliyet->sonraki);
    ehliyet_filtreleme((agac->sag),sayi,ehl_tipi,secim,coklu_fltr_dos);
    }
}
}
void  ehliyetsiz_filtreleme(struct agac *agac,int *sayi,int secim,FILE *coklu_fltr_dos){
int sayac=0;
if(agac!=NULL){
    ehliyetsiz_filtreleme((agac->sol),sayi,secim,coklu_fltr_dos);
    while((agac->ehliyet)!=NULL && sayac==0){
     if(strcmp((agac->ehliyet->ehliyet),("ehliyeti_yok"))==0){
        sayac++;
       if(secim==0)  printf("%s\n",agac->ad);
       if(secim==1){
           coklu_fltr_dos=fopen("gecici.txt","a");
             fprintf(coklu_fltr_dos,"%s",agac->ad);
             fputc('\n',coklu_fltr_dos);
             fclose(coklu_fltr_dos);
           }
       }
       if((*sayi)==0) (*sayi)++;
     (agac->ehliyet)=(agac->ehliyet->sonraki);
    }

    ehliyetsiz_filtreleme((agac->sag),sayi,secim,coklu_fltr_dos);
}
}
void dosyadan_eleme(int tane,FILE *coklu_fltr_dos,FILE *yeni_dosya){
int sayac=1;
char isim1[50];
char isim2[50];
coklu_fltr_dos=fopen("gecici.txt","r");
while(!feof(coklu_fltr_dos)){
fscanf(coklu_fltr_dos,"%s",isim1);
if(feof(coklu_fltr_dos)) return;
long gosterge1=ftell(coklu_fltr_dos);
 fscanf(coklu_fltr_dos,"%s",isim2);
while(!feof(coklu_fltr_dos)){
 if(strcmp(isim1,isim2)==0){
    sayac++;
}
 fscanf(coklu_fltr_dos,"%s",isim2);

 }
 //long gosterge2=ftell(coklu_fltr_dos);
fseek(coklu_fltr_dos,(gosterge1),SEEK_SET);
 if(sayac==tane){
 printf("%s\n",isim1);
 yeni_dosya=fopen("filtreleme.txt","a");
 fprintf(yeni_dosya,"%s",isim1);
 fputc('\n',yeni_dosya);
 fclose(yeni_dosya);
 }
 sayac=1;
}
fclose(coklu_fltr_dos);
}
void duzey_ekle(struct agac *agac,int *sayac,int *adim,struct agac *esol,struct agac *esag,int say,int *derinlik){
if((agac)!=NULL){

        if(say==0){
       (*adim)++;
         (agac)->duzey=(*sayac);
           if((*sayac)>(*derinlik)) (*derinlik)=(*sayac);
       (*sayac)++;
        }

    esol=(agac)->sol;
    esag=(agac)->sag;
    if(esol!=NULL&&esag!=NULL){
    if(esol->sol==NULL&&(agac)->sag!=NULL){
        (*adim)++;
        esol->duzey=(*sayac);
        esag->duzey=(*sayac);
        if((*sayac)>(*derinlik)) (*derinlik)=(*sayac);
        if(esag->sag==NULL) (*sayac)=(*adim)-(*sayac);
        else (*sayac)++;
        (agac)=esag;
        (*adim)=0;
    }
    }
    if(agac->sag==NULL&&agac->sol!=NULL){
        (*adim)++;
       (agac->sol->duzey)=(*sayac);
        if((*sayac)>(*derinlik)) (*derinlik)=(*sayac);
        agac=agac->sol;
        if(esol->sol==NULL) (*sayac)=(*adim)-(*sayac);
         else  (*sayac)++;
    }
    if(agac->sag!=NULL&&agac->sol==NULL){
        (*adim)++;
         (agac->sag->duzey)=(*sayac);
        if((*sayac)>(*derinlik)) (*derinlik)=(*sayac);
        agac=agac->sag;
        if(esag->sag==NULL)  (*sayac)=(*adim)-(*sayac);
        else  (*sayac)++;
    }

  duzey_ekle(((agac)->sol),sayac,adim,esol,esag,say,derinlik);
  duzey_ekle(((agac)->sag),sayac,adim,esol,esag,say,derinlik);
}
}
void duzeyli_yazdir(struct agac *agac){
if(agac!=NULL){
    printf("%s  duzey:%d \n",agac->ad,agac->duzey);
    duzeyli_yazdir(agac->sol);
    duzeyli_yazdir(agac->sag);
}
}
void eleman_say(struct agac *agac,int *eleman_sayisi){
if(agac!=NULL){
    (*eleman_sayisi)++;
    eleman_say(agac->sol,eleman_sayisi);
    eleman_say(agac->sag,eleman_sayisi);
}
}
void dosya_bilgi(struct bilgi *bilgi,FILE *dosya){
while(bilgi!=NULL){
fprintf(dosya,"%s  %s     ","ADRES:",bilgi->adres);
fprintf(dosya,"%s  %s    ","MAIL:",bilgi->mail);
fprintf(dosya,"%s  %s   ","TELEFON:",bilgi->tel);
fprintf(dosya,"%s  %s   ","DOG.TARIHI:",bilgi->dogum_tar);
bilgi=bilgi->sonraki;
}
//fprintf(dosya,"\n..........................\n");
}
void dosya_dil(struct dil *dili,FILE *dosya){
fprintf(dosya,"\nBILDIGI DILLER:\n");
while(dili!=NULL){
fprintf(dosya,"%s",dili->dil);
dili=dili->sonraki;
if(dili!=NULL) fputc(',',dosya);
}
//fprintf(dosya,"\n..........................\n");
}
void dosya_ehliyet(struct ehliyet *ehl,FILE *dosya){

fprintf(dosya,"\nSAHIP OLDUGU EHLIYET TIPI:\n");
while(ehl!=NULL){
fprintf(dosya,"%s",ehl->ehliyet);
ehl=ehl->sonraki;
if(ehl!=NULL) fputc(',',dosya);
}
//fprintf(dosya,"\n..........................\n");
}
void dosya_egitim(struct egitim *egt,FILE *dosya){
fprintf(dosya,"\nMEZUN OLDUGU OKULLAR:\n");
while(egt!=NULL){
fprintf(dosya,"%s    ",egt->okul);
fprintf(dosya,"%s    ",egt->okul_turu);
fprintf(dosya,"%s    ",egt->bolum);
fprintf(dosya,"%s    ",egt->bas_tarih);
fprintf(dosya,"%s    ",egt->bitis_tarih);
fprintf(dosya,"%s    ",egt->ortalama);
egt=egt->sonraki;
if(egt!=NULL) fputc('\n',dosya);
}
//fprintf(dosya,"\n..........................\n");
}
void dosya_is_adres(struct is_adresi *adres,FILE *dosya){
while(adres!=NULL){
fprintf(dosya,"%s",adres->is_adres);
adres=adres->sonraki;
if(adres!=NULL) fputc(',',dosya);
}
fputc(' ',dosya);
fputc(' ',dosya);
fputc(' ',dosya);
}
void dosya_is_deneyimi(struct is_deneyimi *isi,FILE *dosya){
fprintf(dosya,"\nDENEYIMLERI:\n");
while(isi!=NULL){
fprintf(dosya,"%s    ",isi->calistigi_yer);
dosya_is_adres(isi->adres,dosya);
fprintf(dosya,"%s    ",isi->mevki);
fprintf(dosya,"%s    ",isi->sure);
isi=isi->sonraki;
if(isi!=NULL) fputc('\n',dosya);
}
fprintf(dosya,"\n..........................\n");
}
void dosyaya_yaz(struct agac *agac,char isim[],FILE *dosya){
if(agac!=NULL){
    dosyaya_yaz((agac->sol),isim,dosya);
    if(strcmp((agac->ad),(isim))==0){
      fprintf(dosya,"%s     ",(agac->ad));
      dosya_bilgi(agac->bilgi,dosya);
      dosya_dil(agac->dil,dosya);
      dosya_ehliyet(agac->ehliyet,dosya);
      dosya_egitim(agac->egitim,dosya);
      dosya_is_deneyimi(agac->is_deneyimi,dosya);
      return;
    }

    dosyaya_yaz((agac->sag),isim,dosya);
}

}
void kisi_ara(struct agac *agac,char isim[],int *sayac,FILE *dosya){
if(agac!=NULL){
    kisi_ara((agac->sol),isim,sayac,dosya);
    if(strcmp((agac->ad),(isim))==0){
      printf("\n\n");
      printf("AD_SOYAD:%s\n",(agac->ad));
      fprintf(dosya,"%s \n%s\n",(agac->ad),"KISI BILGILERI");
      printf("ADRES:%s\n",(agac->bilgi->adres));
      printf("TEL:%s\n",(agac->bilgi->tel));
      printf("MAIL:%s\n",(agac->bilgi->mail));
      printf("DOGUM_TARIHI:%s\n",(agac->bilgi->dogum_tar));
      dosya_bilgi(agac->bilgi,dosya);
      dil_yaz(agac->dil);
      dosya_dil(agac->dil,dosya);
      ehl_yaz(agac->ehliyet);
      dosya_ehliyet(agac->ehliyet,dosya);
      egt_yaz(agac->egitim);
      dosya_egitim(agac->egitim,dosya);
      is_yaz(agac->is_deneyimi);
      dosya_is_deneyimi(agac->is_deneyimi,dosya);
      (*sayac)++;
      return;
    }

    kisi_ara((agac->sag),isim,sayac,dosya);
}

}

void Liste(struct agac *agac,FILE *dosya){
if(agac!=NULL){
    Liste((agac->sol),dosya);
    fprintf(dosya,"%s \n%s\n",(agac->ad),"KISI BILGILERI");
      dosya_bilgi(agac->bilgi,dosya);
      dosya_dil(agac->dil,dosya);
      dosya_ehliyet(agac->ehliyet,dosya);
      dosya_egitim(agac->egitim,dosya);
      dosya_is_deneyimi(agac->is_deneyimi,dosya);
    Liste((agac->sag),dosya);
}
}
void kisileri_dosyalama(FILE *yeni_dosya,int *sayac){
yeni_dosya=fopen("filtreleme.txt","r");
FILE *dosyalama=fopen("filt_kisiler.txt","w");
char isim[50];
if(yeni_dosya==NULL){
    printf("dosya acilamadi!");
    return;
}
fscanf(yeni_dosya,"%s",isim);
if(feof(yeni_dosya)){
    printf("////////////////////////////////////////\n");
    printf("SISTEMDE BU OZELLIKLERE SAHIP KISI KAYDI YOKTUR\n");
      printf("////////////////////////////////////////\n");
    (*sayac)++;
}
while(!feof(yeni_dosya)){
   agaci_olustur();
    dosyaya_yaz(agac_adresi,isim,dosyalama);
   fscanf(yeni_dosya,"%s",isim);
}
fclose(yeni_dosya);
fclose(dosyalama);
}
