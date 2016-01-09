#include<stdio.h>
#include<string.h> /* strncmp()*/
#define BLOCK_SIZE      512
#define NAME_SIZE       10
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1
#define HEADER_SIZE     4
#define READ_ONE_BYTE   1
#define ZERO            0
#define MATCH_FOUR_CHAR 4
#define ONE             1


int main(int argc, char* argv[]){



if(argc!=2){
printf("Error(1): Improper Argument(s). \n");
printf("Syntax: FILE_NAME.EXE INPUT_FILE_NAME.EXTENT\n");
return EXIT_FAILURE;
}




FILE*         READER=NULL;
FILE*         WRITTER=NULL;
unsigned char HEADER_SIGN_ONE[HEADER_SIZE]={0xff,0xd8,0xff,0xe0};
unsigned char HEADER_SIGN_TWO[HEADER_SIZE]={0xff,0xd8,0xff,0xe1};
unsigned char BUFFER[BLOCK_SIZE]={0};
unsigned int  BUFFET;
char          OUTPUT_FILE_NAME[NAME_SIZE]={0};
char          INPUT_FILE_NAME[NAME_SIZE]={0};
int           CHECK_ONE;
int           CHECK_TWO;



BUFFET    = 1;
CHECK_ONE = 0;
CHECK_TWO = 0;

printf("Carving in Process...\n");
sprintf(INPUT_FILE_NAME,"%s",argv[1]);
READER = fopen(INPUT_FILE_NAME,"r");

if(ferror(READER) != ZERO) 
    {perror("Error(2): Input File couldn't be Opened.");
    return EXIT_FAILURE;}

while(feof(READER) == ZERO){
    fread(BUFFER,BLOCK_SIZE,READ_ONE_BYTE, READER);
    CHECK_ONE = strncmp(BUFFER,HEADER_SIGN_ONE,MATCH_FOUR_CHAR);
    CHECK_TWO = strncmp(BUFFER,HEADER_SIGN_TWO,MATCH_FOUR_CHAR);
    
    if ((CHECK_ONE == ZERO) || (CHECK_TWO == ZERO) ){ 
        if(WRITTER != NULL)
            fclose(WRITTER);
        sprintf(OUTPUT_FILE_NAME,"%05d.jpg",BUFFET);
        WRITTER = fopen(OUTPUT_FILE_NAME,"w");
        if(ferror(WRITTER) != ZERO) 
            {perror("Error(3): Output File couldn't be Opened.");
            return EXIT_FAILURE;}
        BUFFET = BUFFET+1;
        }
    if(WRITTER != NULL)
        fwrite(BUFFER,BLOCK_SIZE,READ_ONE_BYTE, WRITTER);

 
}
printf("%d JPG File(s) Recovered \n",BUFFET-ONE);
printf("Successfully   Undeleted \n");
printf("Credit: GCT@PrinceMughal \n");
fclose(READER);
fclose(WRITTER);

return EXIT_SUCCESS;}
