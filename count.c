#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFFSIZE 100

int matchChecking(const char* str1, const char* str2);

int  main(int argc, char *argv[])
{  
   //checking the number of input parameters  
   if(argc!=4)
   {
       printf("please make sure we have three parameters: input file name, searching string and ouput file name\n ");
       exit(1);
   }
   //open file to read 
   FILE *inFile = fopen(argv[1], "r"); 
   //checking wheather file is opened correctly
   if(inFile==NULL) 
   {
       printf("cannot open the input file\n");
       exit(1);
   }

   char buf[BUFFSIZE];
   int matches = 0;
   int sz = 0;
   // calculating the file size with fseek
   fseek(inFile, 0, SEEK_END);
   sz = ftell(inFile);
   fseek(inFile, 0, SEEK_SET);

   printf("the file size is: %d\n", sz);
   char *origin = argv[2];
   int originLen = strlen(origin);

   //starting to find matches
   while(1)
   {
          int num = fread(buf, 1, BUFFSIZE, inFile);
          for(int i=0;i<num-originLen+1;i++)
          {
             //string matching is processed at matchChecking function
             matches  = matches +  matchChecking(origin, &buf[i]);
          }
          if(feof(inFile)) break;
          fseek(inFile, -(originLen-1), SEEK_CUR); //since we read BUFFSIZE data from the file, we need deal with overlaps
   }

   printf("number of matches is:%d\n", matches); 
   //open a file to write the result
   FILE* outFile = fopen(argv[3], "w");
   //checking wheather the file is opened correctly 
   if(outFile==NULL)
   {
       printf("cannot open the output file\n");
       exit(1);
   }
   //writing results to the file
   fprintf(outFile,"the file size is: %d\n", sz);
   fprintf(outFile, "number of matches is: %d\n", matches);
   //closing two files 
   if(fclose(inFile))  printf("closing input file is not successful\n"); 
   if(fclose(outFile)) printf("closing output file is not successful\n");
   return 0;
}

//function to check matches
int matchChecking(const char* str1, const char* str2)
{
      int length = strlen(str1); 
      for(int i=0;i<length;i++)
      {
        if(str1[i]!=str2[i]) return 0;
      }
      return 1;
}
 
