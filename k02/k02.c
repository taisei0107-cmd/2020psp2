#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _USE_MATH_DEFINES

extern double p_stdnorm(double z);

int main(void)
{
    double val;
    double y;
    double averageA=170.8;
    double averageB=169.7;
    double sigmaA=5.43;
    double sigmaB=5.5;
    double L;
    double max_val;
    double min_val;
    char fname[FILENAME_MAX];
    char buf[256];
    FILE* fp;
    double L1=1,L2=1;

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

        y=(val-averageA)/sigmaA;
        L=p_stdnorm(y);
        L1=L*L1;

        y=(val-averageB)/sigmaB;
        L=p_stdnorm(y);
        L2=L*L2;



    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    min_val=L2;
    max_val=L1;

    printf("L_A: %f\n",max_val);
    printf("L_B: %f\n",min_val);

    return 0;


}

double p_stdnorm(double z)
{
    return 1/sqrt(2*M_PI) * exp(-z*z/2);
}

