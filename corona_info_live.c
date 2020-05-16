#include<stdio.h>
#include<string.h>
#include <stdlib.h>


struct cases{
    char District[20];
    int total_cases;
    int total_active_cases;
    int total_recovered_cases;
};

void sort_cases(struct cases districts[77]);
void display_cases(struct cases districts[77]);
void insert_cases(struct cases districts[77]);
int csv_read();
void csv_write(struct cases districts[77]);


struct cases districts[77] ,temp[2];


int main(){

    char press;

    sort_cases(districts);
    display_cases(districts);
    //read from file and insert to struct here


      while (1)
        {

            printf("\nDate=11 May,2020 \n");
            csv_read();
            sort_cases(districts);
            display_cases(districts);

            printf("\ndo you want to update the information? y/n: ");
            scanf("%c",&press);
            printf("%c",press);

            if(press =='y'){
                insert_cases(districts);
            }
            else{
                printf("district not found");
                break;
            }
            display_cases(districts);   }


    //write from struct to csv here
}

void sort_cases(struct cases districts[77])
{
  struct cases temp[2];
  int i,j;
  for(i=0;i<77;i++){
      for(j=0;j<76-i;j++){
          if(districts[j].total_cases < districts[j+1].total_cases){
              temp[0]=districts[j+1];
              districts[j+1]=districts[j];
              districts[j]=temp[0];
          }
      }
  }
}

void display_cases(struct cases districts[77])
{
  int i;
  printf("District\tTotal Case(s)\tTotal Active Cases\tTotal Recovered Cases");
  for(i=0;i<77;i++){
     printf("\n %-16s \t%d\t%14d\t%18d",districts[i].District,districts[i].total_cases,districts[i].total_active_cases,districts[i].total_recovered_cases);
  }
}

void insert_cases(struct cases districts[77])
{
    int i;
    char location[40];
    printf("\nenter district name: ");
    scanf("%s",location);
    for(i=0;i<77;i++){
        if(strcmp(location,districts[i].District)==0){
            printf("\nEnter total_case,total active case an total recovered cases");
            scanf("%d,%d,%d%*c",&districts[i].total_cases,&districts[i].total_active_cases,&districts[i].total_recovered_cases);
        }
    }
    csv_write(districts);
}

int csv_read()
{

    FILE *fptr;
    fptr = fopen("corona.csv","r");

    if (fptr == NULL)
    {
      printf("File doesn't exist");
      return 0;
    }
      //get to end of the file to determine its filesize
      fseek(fptr,0,2);
      int size = ftell(fptr);
      char *ch = (char *)malloc(sizeof(char)*size);
      fseek(fptr,0,0);
      char token[40];



      int counter=0;
      while (fgets(ch,size,fptr)!= NULL)
      {

            char districtName[40];
            int TotalCases;
            int Recovered;
            int j=0;
            int tokenI=0;
            int tokenCounter=0;
            char token[40];
            while(ch[j]!='\n'){
                if(ch[j]==','){
                    if(tokenCounter == 0){
                        strcpy(districts[counter].District,token);

                    }else if(tokenCounter == 1){
                        districts[counter].total_cases = atoi(token);

                    }
                    else if(tokenCounter == 3){
                        districts[counter].total_recovered_cases = atoi(token);

                    }
                     else if(tokenCounter == 2){

                         districts[counter].total_active_cases =atoi(token);
                    }

                    tokenCounter++;
                    tokenI=0;
                    memset( token, 0x00 , 40); //clears whatever is in token
                }else{
                    token[tokenI]=ch[j];
                    tokenI++;
                }


                j++;
            }

        counter++;
      }



      fclose(fptr);

}

void csv_write(struct cases districts[77])
{
    FILE *fptr = fopen("corona.csv","w");
    for(int i=0;i<77;i++){
        fprintf(fptr,"%s,%d,%d,%d\n",districts[i].District,districts[i].total_cases,districts[i].total_active_cases,districts[i].total_recovered_cases);
    }
    fclose(fptr);


}
