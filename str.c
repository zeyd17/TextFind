#include <stdio.h>
#include <string.h>

#define N 300

struct Kayit{
	char satir[N];
};

int satirSay(char *dosyayolu);
void DosyaOku(struct Kayit *kayit,char *dosyayolu,char *new,char *old);

int main(int argc,char *argv[])
{
	struct Kayit *kayit;
	FILE *file;
	
	char *old=(char *)malloc(sizeof(char)*strlen(argv[1]));
	char *new=(char *)malloc(sizeof(char)*strlen(argv[2]));
	char *satir[N];
	strcpy(old,argv[1]);//aranan ifade
	strcpy(new,argv[2]);//yeni ifade
	int i=0,j,satirSayisi=0;
	
	satirSayisi=satirSay(argv[3]);
	
	printf("satir sayısı %d\n",satirSayisi);
	kayit =(struct Kayit *)malloc(sizeof(struct Kayit)*satirSayisi);
	
	DosyaOku(kayit,argv[3],new,old);
	
	//dosya ya yazma
	file=fopen("deneme.txt","w");
	for(i=0;i<satirSayisi-1;i++)
	{	
		for(j=0;j<N;j++)
		{
			if(kayit[i].satir[j] =='\0')
			{
			break;
			}
			fputc(kayit[i].satir[j],file);
		}
	}
	fclose(file);
}

int satirSay(char *dosyayolu)
{	FILE *file;
	file=fopen(dosyayolu,"r");
	int satirSayisi=0;
	char *satir[N];
	while(!feof(file))
	{
		fgets(satir,N,file);
		satirSayisi++;
	}
	fclose(file);
	return satirSayisi;
}

/******************arama değiştirme algoritması*********************************/
int strCmp(char *cumle,char *arama,int index)
{
	int i=0;
	do
	{
		if(*(cumle +index + i) != *(arama +i) )
		return 1;
		
		i++;
	}while(*(cumle +index + i)!= '\0' && *(arama +i ) != '\0' && i< strlen(arama));
	if(i == strlen(arama))
	{
		return 0;
	}
	return 1;
}

void KelimeDegistir(char *cumle,char *yKelime,int index)
{
	int i=0;
	while(i < strlen(yKelime))
	{
		*(cumle + index +i)=*(yKelime +i);
		i++;
	}
}

solaKaydir(char *cumle ,int kaydirma,int index)
{
	while(1)
	{
		if(*(cumle +index) =='\0')
		{
			break;
		}
		*(cumle +index) =*(cumle +index + kaydirma);
		index++;
	}
}

void sagaKaydir(char *cumle,int kaydirma,int index)
{
	int uzunluk =N-1;
	while(uzunluk > index)
	{
		*(cumle +uzunluk) =*(cumle +uzunluk - kaydirma);
		uzunluk--;
	}
	
}

void aramaYap(char *cumle,char *arama,char *yeniKelime,int satir)
{
	int i=0,sonuc=-1;
	for(;i<N-strlen(arama);i++)
	{
		 sonuc=strCmp(cumle,arama,i);
		 if(sonuc ==0)
		 {	
		 	printf("%d. satir %d. sutun da bulundu \n",satir+1,i+1);
		 	//aranan kelime yeni kelime ile aynı uzunlukta değilse kaydırma yap
		 	if(strlen(arama) > strlen(yeniKelime))
		 	{
		 		solaKaydir(cumle,strlen(arama) - strlen(yeniKelime),i+strlen(yeniKelime)-1);
		 	}else if(strlen(arama) < strlen(yeniKelime))
		 	{	 
		 		sagaKaydir(cumle,strlen(yeniKelime) -  strlen(arama),i+strlen(arama));
		 	}
		 	KelimeDegistir(cumle,yeniKelime,i);
		 	sonuc=-1;
		 }
	}
}
/*******************************************************************************/

void DosyaOku(struct Kayit *kayit,char *dosyayolu,char *new , char*old)
{
	FILE *file;
	file=fopen(dosyayolu,"r");
	int i=0;
	char *satir[N];
	while(!feof(file))
	{
		fgets(satir,N,file);
		//arama ve değiştirme fonksiyunu
		aramaYap(satir,old,new,i);
		strcpy(kayit[i].satir,satir);
		i++;
	}
	fclose(file);
}
