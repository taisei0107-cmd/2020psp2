#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(int N,double val,double ave);
extern double var_online(int N,double val,double ave,double square_ave);

int main(void)
{
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    int N;
    double val;
    double ave, ave_new;
    double square_ave, square_ave_new;
    double var;
    double variarance;

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    N=1;
    ave=square_ave=0.0;
    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%lf",&val);

        ave_new = ave_online(N,val,ave);
        square_ave_new = ave_online(N,val*val,square_ave);
        var = var_online(N,val,ave,square_ave);
        
        /* update */
        N++;
        ave = ave_new;
        square_ave = square_ave_new;
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    variarance = N*var/(N-1);
    printf("sample mean:%lf\n",ave);
    printf("sample variarance:%lf\n",var);
    printf("population mean:%lf\n",ave);
    printf("population variarance:%lf\n",variarance);

    return 0;


}

double ave_online(int N,double val,double ave)
{
    return (N-1)*ave/N+val/N;
}

double var_online(int N,double val,double ave,double square_ave)
{
    return ((N-1)*square_ave/N+val*val/N)-pow(((N-1)*ave/N+val/N),2.0);
}