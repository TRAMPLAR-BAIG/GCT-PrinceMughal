#include<stdio.h>
#include<string.h> /* strncmp()*/
#include<getopt.h> /* getopt()*/
#include<stdlib.h> /* exit()*/
#include<sys/stat.h> /*int mkdir(const char *path, mode_t mode);*/
#define BLOCK_SIZE      512
#define NAME_SIZE       10
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1
#define HEADER_SIZE     4
#define READ_ONE_BYTE   1
#define ZERO            0
#define MATCH_FOUR_CHAR 4
#define ONE             1
#define NEWLINE         "\n"




void USAGE(FILE*,unsigned int);
char PROG_NAME[NAME_SIZE];


int main(int argc, char* argv[]){
strncpy(PROG_NAME, argv[ZERO], NAME_SIZE);



FILE*         READER=NULL;
FILE*         WRITTER=NULL;
unsigned char HEADER_SIGN_ONE[HEADER_SIZE]={0xff,0xd8,0xff,0xe0};
unsigned char HEADER_SIGN_TWO[HEADER_SIZE]={0xff,0xd8,0xff,0xe1};
unsigned char BUFFER[BLOCK_SIZE]={0};
unsigned int  BUFFET;
const   char* short_options="ho:i:";
char          OUTPUT_DIR[NAME_SIZE];
char          OUTPUT_FILE_NAME[NAME_SIZE]={0};
char          INPUT_FILE_NAME[NAME_SIZE]={0};
char          TEMP[NAME_SIZE];
int           CHECK_ONE;
int           CHECK_TWO;
int           NEXT_OPTION;



BUFFET      = 1;
CHECK_ONE   = 0;
CHECK_TWO   = 0;
NEXT_OPTION = 0;
strcpy(PROG_NAME,argv[ZERO]);
do{

NEXT_OPTION=getopt(argc,argv,short_options);

switch(NEXT_OPTION){
 case 'i':
 strcpy(INPUT_FILE_NAME, optarg);
 break;
 case 'o':
 strcpy(OUTPUT_DIR, optarg);
 mkdir(OUTPUT_DIR,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
 break;
 case 'h':
 USAGE(stdout,ZERO);
 break;
 default:
   USAGE(stderr,-1);
   abort();}
}while(NEXT_OPTION != -ONE);

printf("Carving in Process...%s", NEWLINE);
READER = fopen(INPUT_FILE_NAME,"r");
strcat(OUTPUT_DIR,"/");

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
        strncpy(TEMP,OUTPUT_DIR,NAME_SIZE);
        sprintf(OUTPUT_FILE_NAME,"%05d.jpg",BUFFET);
        strcat(OUTPUT_DIR,OUTPUT_FILE_NAME);
        WRITTER = fopen(OUTPUT_DIR,"w");
        strncpy(OUTPUT_DIR,TEMP, NAME_SIZE);
        if(ferror(WRITTER) != ZERO) 
            {perror("Error(3): Output File couldn't be Opened.");
            return EXIT_FAILURE;}
        BUFFET = BUFFET+1;
        }
    if(WRITTER != NULL)
        fwrite(BUFFER,BLOCK_SIZE,READ_ONE_BYTE, WRITTER);

 
}

printf("Credit: PRINCE MUGHAL @GCT-GREEN_HAT %s", NEWLINE);
fclose(READER);
fclose(WRITTER);

return EXIT_SUCCESS;}


void USAGE(FILE* STREAM, unsigned int EXIT_CODE)
{
  fprintf(STREAM," %s MADE BY PRINCE MUGHAL @GCT-GREEN_HAT%s", PROG_NAME, NEWLINE);
  fprintf(STREAM," %s [-i <INPUT_FILE_NAME>] [-o <OUTPUT_DIR_NAME>]%s", PROG_NAME, NEWLINE);
  fprintf(STREAM,"   -h -> FOR HELP%s",NEWLINE);
  fprintf(STREAM,"   -i -> INPUT IMAGE FILE%s",NEWLINE);
  fprintf(STREAM,"   -o -> OUTPUT DIRECTORY NAME%s",NEWLINE);
  exit(EXIT_CODE);

}

