#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
double Noktalar_Arasi_Uzaklik(double a[],int b[])
{
    return sqrt(pow(a[0]-b[0],2)+pow(a[1]-b[1],2));
}
double Noktalar_Arasi_Uzaklik(int a[],int b[])
{
    return sqrt(pow(a[0]-b[0],2)+pow(a[1]-b[1],2));
}
bool Icinde(double circle[],int point[])
{
    return Noktalar_Arasi_Uzaklik(circle,point)<= circle[2];
}
void Merkez_Degis2(int b[],int c[],double circle[])
{
    double B = b[0]*b[0]+b[1]*b[1];
    double C =  c[0]*c[0]+c[1]*c[1];
    double D = b[0]*c[1]-b[1]*c[0];
    circle[0]= (c[1] * B - b[1] * C) / (2 * D);
    circle[1]=(b[0] * C - c[0] * B) / (2 * D);
}
bool Nokta_icinde_Mi(double circle[],int allX[],int allY[],int N)
{

    for(int i = 0; i<N; i++ )
    {
        int YeniArr[2];
        YeniArr[0] = allX[i];
        YeniArr[1] = allY[i];
        if(!Icinde(circle,YeniArr))
        {
            return false;
        }
    }

    return true;

}

void Merkez_Degis(int a[],int b[],int c[],double circle[], int allX[],int allY[],int N)
{
    double KopyaCircle[3];
    KopyaCircle[0] = circle[0];
    KopyaCircle[1] = circle[1];
    KopyaCircle[2] = circle[2];

    int arr1[2];
    int arr2[2];
    arr1[0] = b[0] - a[0];
    arr1[1] = b[1] - a[1];
    arr2[0] = c[0] - a[0];
    arr2[1] = c[1] - a[1];
    Merkez_Degis2(arr1,arr2,circle);
    circle[0] += a[0];
    circle[1] += a[1];
    circle[2] = Noktalar_Arasi_Uzaklik(circle,a);

    if(!Nokta_icinde_Mi(circle,allX,allY,N) || circle[2] > KopyaCircle[2])
    {
        circle[0] = KopyaCircle[0];
        circle[1] = KopyaCircle[1];
        circle[2] = KopyaCircle[2];

    }
    else
    {

    }

}
void Merkez_Degis(int a[],int b[],double circle[], int allX[],int allY[],int N)
{

    double KopyaCircle[3];
    KopyaCircle[0] = circle[0];
    KopyaCircle[1] = circle[1];
    KopyaCircle[2] = circle[2];

    circle[0] = (a[0] + b[0]) / 2.0;
    circle[1] = (a[1] + b[1]) / 2.0;
    circle[2] = Noktalar_Arasi_Uzaklik(a, b) / 2.0;

    if(!Nokta_icinde_Mi(circle,allX,allY,N) || circle[2] > KopyaCircle[2])
    {
        circle[0] = KopyaCircle[0];
        circle[1] = KopyaCircle[1];
        circle[2] = KopyaCircle[2];

    }
    else
    {

    }
}

void En_Kucuk_Cember(int allX[],int allY[],int N,double circle[])
{



    circle[0] = 0;
    circle[1] = 0;
    circle[2] = 9999999;


    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int Dizi1[2];
            int Dizi2[2];
            Dizi1[0] = allX[i];
            Dizi1[1] = allY[i];

            Dizi2[0] = allX[j];
            Dizi2[1] = allY[j];

            Merkez_Degis(Dizi1, Dizi2,circle,allX,allY,N);


        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            for (int k = j + 1; k < N; k++)
            {

                int Dizi1[2];
                int Dizi2[2];
                int Dizi3[2];
                Dizi1[0] = allX[i];
                Dizi1[1] = allY[i];
                Dizi2[0] = allX[j];
                Dizi2[1] = allY[j];
                Dizi3[0] = allX[k];
                Dizi3[1] = allY[k];
                Merkez_Degis(Dizi1, Dizi2, Dizi3,circle,allX,allY,N);

            }
        }
    }
}
void Spline_Al(double t,double *points1,int points[][2])
{
    int n1, n2, n3, n4;
    n2 = int(t) + 1;
    n3 = n2 + 1;
    n4 = n3 + 1;
    n1 = n2 - 1;
    t = t - int(t);

    double egim1 = -(t*t*t) + (2.0 * (t*t)) - t;
    double  egim2= (3.0 *(t*t*t) ) - (5.0 * (t*t)) + 2.0;
    double  egim3= (-3.0 * (t*t*t)) + (4.0 * (t*t)) + t;
    double egim4 = (t*t*t) - (t*t);

    points1[0] =  0.5 * ((points[n1][0] * egim1) + (points[n2][0] * egim2) + (points[n3][0] * egim3) + (points[n4][0] * egim4));
    points1[1] =  0.5 * ((points[n1][1] * egim1) + (points[n2][1] * egim2) + (points[n3][1] * egim3) + (points[n4][1] * egim4));

}
void Spline_Ciz(int points[][2],int N)
{
    double xnoktasi = points[1][0];
    double ynoktasi = points[1][1];
    for (double t = 0.1; t < double(N)-1.0; t+= 0.1)
    {
        double points1[2];
        Spline_Al(t, points1, points);
        line(xnoktasi, ynoktasi, points1[0], points1[1]);
        xnoktasi = points1[0];
        ynoktasi = points1[1];
    }
}
int main()
{
    //Dosya Açıldı ve Dosyadan Noktalar Alındı
    FILE *dosya=fopen("lab","r");
    char text[100];
    fgets(text,100,dosya);
    printf("%s\n",text);
    int i=0,j,k=0,h,y=1,N;
    printf("Kac Nokraniz Gireceksiniz:");
    scanf("%d",&N);
    int xy[2][N];
    char kordinatdizisi[20][30];
    char *kordinat;
    const char *d="{}, ";
    kordinat = strtok(text,d);
    //Dosyadan alınan string karekterlerin sadece sayı olanlarını aldık gerisini attık
    while(kordinat != NULL)
    {
        strcpy(kordinatdizisi[i],kordinat);
        i++;
        kordinat = strtok(NULL,d);
    }

    //Burada string olan sayıları int a çevirdik
    for(j=0; j<2; j++)
    {
        if(j==0)
        {
            for( h=0; h<N; h++)
            {
                if(k<=i)
                {
                    xy[j][h]=atoi(kordinatdizisi[k]);
                    k=k+2;
                }

            }
        }
        if(j==1)
        {

            for( h=0; h<N; h++)
            {
                if(k<=i)
                {
                    xy[j][h]=atoi(kordinatdizisi[y]);
                    y=y+2;
                }
            }

        }
    }
    //Matriste olan int sayılarımızı xdizisi ve ydizisine attık
    int  xdizisi[N];
    int  ydizisi[N];
    for(j=0; j<N; j++)
    {
        xdizisi[j]=xy[0][j];
    }
    for(j=0; j<N; j++)
    {
        ydizisi[j]=xy[1][j];
    }

    double merkeztut[3];
//Burada fonksiyona matris atmak istedik ama matrisler fonkisyonda matris[2][] şeklinde tanımlanmadıgı için matrisin tam tersini aldık ve matrisimiz matris[][2]oldu
    int xy1[N+1][2];
    int xy2[N+2][2];
    xy2[0][0]=1000+(-20*25);
    xy2[N+1][0]=1000+(20*25);
    xy2[0][1]=500+(0*25);
    xy2[N+1][1]=500+(0*25);
    for(j=0; j<N; j++)
    {
        xy1[j][0]=xy[0][j];
        xy1[j][1]=xy[1][j];
    }
    int g=0;
    for(j=1; j<=N; j++)
    {
        xy2[j][0]=1000+(xy1[g][0]*25);
        xy2[j][1]=500-(xy1[g][1]*25);
        g++;
    }
    //En küçük dairemiz için fonksiyonumuzu çağırdık ve çizdirdik
    En_Kucuk_Cember(xdizisi,ydizisi,N,merkeztut);
    printf("\nMerkezx,Merkezy,Yaricap=>>>>>>>>>>>>>>>>%f,%f,%f\n",merkeztut[0],merkeztut[1],merkeztut[2]);
    initwindow(1920,1250,"windowstext",0,0);
    Spline_Ciz(xy2,N);
    line(500,500,1500,500);
    line(1000,0,1000,1000);
    circle(1000+(merkeztut[0]*25),500-(merkeztut[1]*25),merkeztut[2]*25);
    for(j=0; j<N; j++)
    {
        fillellipse(1000+(xdizisi[j]*25),500-(ydizisi[j]*25),3,3);
    }

    char yaricap[20];
    yaricap[0]='r';
    yaricap[1]='=';
    snprintf(&yaricap[2],18,"%f",merkeztut[2]);
    fillellipse(1000+(merkeztut[0]*25),500-(merkeztut[1]*25),5,5);
    outtextxy(1005+(merkeztut[0]*25),495-(merkeztut[1]*25),yaricap);
    char sayi[3];
    char sayi2[3];
    for(j=0; j<=20; j++)
    {

        outtextxy(996+(j*25),501,itoa(j,sayi,10));
        outtextxy(996+(-j*25),501,itoa(j,sayi,10));
        outtextxy(1001,493-(j*25),itoa(j,sayi2,10));
        outtextxy(1001,493-(-j*25),itoa(j,sayi2,10));
    }
    getch();
    return 0;
}
