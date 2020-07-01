#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern double ave_online(int N,double val,double ave)
extern double var_online(int N,double val,double ave,double square_ave)
double val;
double ave;
double var;
double square_ave;
int N;
double variarance;

int main(void)
{
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;

    printf("input the filename of sample:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1] = '\0';
    printf("the filename of sample: %s\n",fname);

    fp = fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%lf",&val);
        ave = ave_online(N,val,ave);
        var = var_online(N,val,ave,square_ave);
    

    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }
    variarance = ((N-1)/N)*var;
    printf("sample mean:%lf\n",ave);
    printf("sample variarance:%lf\n",var);
    printf("population mean:%lf\n",ave);
    printf("population variarance:%lf\n",variarance);

    return 0;


}

extern double ave_online(int N,double val,double ave)
{
    return ((N-1)/N)*ave+(1/N)*val;
}

extern double var_online(int N,double val,double ave,double square_ave)
{
    return (((N-1)/N)*square_ave+(1/N)*ave)-(((N-1)/N)*ave+(1/N)*val);
}