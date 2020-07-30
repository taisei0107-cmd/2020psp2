#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    int gender;
    double height;
    int ID;
}Data;


int main(void)
{
    Data data[14];
    char fname[FILENAME_MAX];
    FILE* fp;
    char buf[256];
    int i = -1;
    int check_ID;

    printf("Input the filename of sample height:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1]='\0';
    printf("the filename of sample:%s\n",fname);
    fp = fopen(fname,"r");

    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    while(fgets(buf,sizeof(buf),fp) !=NULL){
        if(i== -1){
            i++;
            continue;
        }
        sscanf(buf,"%d,%lf",&data[i].gender,&data[i].height);
        i++;
    }
    if(fclose(fp)==EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("input the filename of sample ID:");
    fgets(fname,sizeof(fname),stdin);
    fname[strlen(fname)-1]='\0';
    printf("the filename of sample: %s\n",fname);
    fp=fopen(fname,"r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        exit(EXIT_FAILURE);
    }

    i=0;
    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d",&data[i].ID);
        i++;
    }
    if(fclose(fp)==EOF){
        fputs("file close error\n",stderr);
        exit(EXIT_FAILURE);
    }

    printf("Which ID's data do you want?:");
    scanf("%d",&check_ID);

    int flag = 0;
    for(i=0;i<14;i++){
        if(data[i].ID == check_ID){
            flag=1;
            printf("ID: %d\n",data[i].ID);
            if(data[i].gender == i){
                printf("gender:male\n");
            }
            else{
                printf("gender:female\n");
            }
            printf("height : %.2lf\n",data[i].height);
        }
    }
    if(flag == 0){
        printf("No data\n");
    }
    return 0;
}

