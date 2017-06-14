/* 
 Name: Hamdi Allam
 Compiler/IDE: Xcode
 Homework 5
 */

#include "binaryTree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// definitions
#define MAX 256

void readFile(FILE *fp, node **root);
void printTime();
void reprintWithLines(FILE *fp);

// used to hold state when parsing
typedef enum {
    COMMENT,
    QUOTE,
    MULTILINE_COMMENT,
    NORMAL
} parse_state;


int main(int argc, char *argv[]){
    
    node *root = NULL; // empty root 
    FILE *fp;
    
    // validate the command line args
    if(argc <  2 || !(fp = fopen(argv[1], "r"))){
        (argc < 2) ? printf("File Input needed\n") : printf("Error opening file\n");
        exit(100);
    }
    
    // same title as the sample
    printf("%s\n\n", "/************************  Cross Reference Listing  ************************/");
    
    printTime();
    readFile(fp, &root);
    inorder(root); // print the identifiers in order
    
    // some spacing
    printf("\n\n");
    
    //rewind the file pointer
    rewind(fp);
    reprintWithLines(fp);
    
    
    fclose(fp); // close the file
    return 0;
}

/* reprint the C file including line numbers
    - Ignoring single and multiline comments
 */
void reprintWithLines(FILE* fp){
    char ioRes[MAX]; int line = 1;
  
    // go through every line
    while( fgets(ioRes, sizeof(ioRes), fp) ){
        printf("%-6d", line++);
        
        // ioRes already includes newline character
        printf(": %s", ioRes);
    }
}

/* Print the current time */
void printTime(){

    char *str;
    time_t timeval;
    time(&timeval); // get the time

    str = ctime(&timeval); // convert to a string
    
    printf("Cross reference listing made at: %s\n", str);
}

/* Read line by line */
void readFile(FILE *fp, node **root){

    void parseLine(node **root, char *ioRes, int line, parse_state *state);
    
    parse_state state = NORMAL; // used to hold state
    
    char ioRes[MAX];
    int line = 1;
    while( fgets(ioRes, sizeof(ioRes), fp) ){
        parseLine(root,ioRes, line, &state);
        line++;
    }
}


/* Parse one line of C code */
void parseLine(node **root, char *ioRes, int line, parse_state *state){
    char *dilem = "!.+-=;<>()&|?[],:'{}\n\t ";
    char *ptr, *pos; // token pointer and extra one( specific case )
    
    ptr = strtok(ioRes, dilem);
    
    // check if empty line
    if(!ptr)
        return;
   
    // go through all the tokens
    do{
        // check for state
        if(*state == QUOTE){
            // check if quote ends at a new token
            if(!strpbrk(ptr, "\""))
                continue; // parse tokens until the ending is found
            else{
                // end of quote was found but skip this specific token
                *state = NORMAL;
                continue;
            }
            
        } else if(*state == MULTILINE_COMMENT){
            // skip lines until we find the end
            if( strstr(ptr, "*/") ){
                *state = NORMAL;
                continue;
            }
        }
        
        // directives
        if( *ptr == '#'){
            ptr++; // ignore pound symbol
            
            // insert the directive
            *root = insertNode(*root, ptr, line);
            
            //skip header/c files from #inlcude
            if( strcmp(ptr, "include") == 0 )
                break; // Ingore any more tokens and move on
        }
        
        // check for single line comments
        if( *ptr == '/' && *(ptr+1) == '/'){
            break; // skip the rest of this line
        }
        
        // check for paragrah comments
        else if ( *ptr == '/' && *(ptr+1) == '*'){
            
            *state = MULTILINE_COMMENT; // change the state
            
            // We will not skip the  line; paragraph comment could end on the same line
            continue;
        }
        
        // wierd case: Division. I.E "pos/num" --> pos, num
        if( strchr(ptr, '/') ){
            //no worries about '//' -> would be invalid syntax
            *(pos = strchr(ptr, '/')) = '\0'; //used as a seprator
            
            // insert found words
            *root = insertNode(*root, ptr, line);
            *root = insertNode(*root, (pos+1), line);
        }
        
        // check for pointer symobols and skip as many as needed
        if(*ptr == '*'){
            ptr += strspn(ptr, "*");
        }
        
        // identifiers cannot start with numbers
        if( isdigit(*ptr) ) continue;
        
        // quotation?
        if( *ptr == '"' ){
            ptr++;
            
            /* Comment could include spacing
             ending can reside in another token
             */
            if(!strpbrk(ptr, "\"")){
                // change state: all futher tokens are part of the quote
                //               until another '"' is found
                *state = QUOTE;
                continue;
            }
            
            //do not print this token
            continue;
        }
        
        //successful
        if(*state == NORMAL && strlen(ptr) != 0){
            *root = insertNode(*root, ptr, line);
        }
        
    } while( (ptr = strtok(NULL, dilem)));
}


/************************  Cross Reference Listing  ************************/
/* <-- I added this.
 
Cross reference listing made at: Tue Mar 21 22:36:23 2017

FILE                          19  20  21  22  32  55  90
MAXCITIES                     5  18
MAXLINE                       6  58  60
NULL                          40  46  71
argc                          16  20  24  32  34
argv                          16  24
char                          10  16  20  32  58  71
checkArgs                     20  24  32
city                          58  62  63  71  76
count                         12  21  22  25  26  57  63  66  67
68  70  76  80  81  85  90  94  96
define                        5  6
else                          66  78
exit                          37  43  49  74
fgets                         60
fin                           19  20  21  22  24  25  32  40  55
60
first                         57  65
float                         96
fopen                         40  46
for                           94
fout                          19  20  24  26  32  46  90  95
fprintf                       95
highTemp                      57  62  67  80
highTemps                     18  21  25  26  55  63  67  68  70
76  80  81  90  95  96
hightemps                     22
i                             92  94  95  96
if                            34  40  46  63  65  70
include                       1  2  3  4
infile                        20  32  40
int                           11  12  16  20  21  22  32  55  57
90  92
line                          58  60  62
main                          16
malloc                        71
outfile                       20  32  46
perror                        42  48  73
printf                        36
readIntoWeatherStructs        21  25  55
return                        85
sscanf                        62
statecity                     10  63  70  76  95
strcmp                        63
strcpy                        76
strlen                        71
struct                        8  18  21  22  55  90
tempsum                       11  67  80  96
void                          20  22  32  90
weather                       8  18  21  22  55  90
while                         60
writeAveragesToOutput         22  26  90


1     : #include <stdio.h>
2     : #include <stdlib.h>
3     : #include <string.h>
4     : #include <ctype.h>
5     : #define MAXCITIES 100
6     : #define MAXLINE    80
7     :
8     : struct weather
9     : {
10    :     char *statecity;
11    :     int   tempsum;
12    :     int   count;
13    : };
14    :
15    :
16    : int main(int argc, char **argv)
17    : {
18    :     struct weather highTemps[MAXCITIES] = {{"", 0, 0}}; //more comments
19    :     FILE *fin, *fout;
20    :     void checkArgs(int argc,char *infile,char *outfile,FILE **fin,FILE **fout);
21    :     int readIntoWeatherStructs(struct weather *highTemps, FILE *fin), count;
22    :     void writeAveragesToOutput(struct weather *hightemps, int count, FILE *fin);
23    :
24    :     checkArgs(argc, argv[1], argv[2], &fin, &fout);
25    :     count = readIntoWeatherStructs(highTemps, fin);
26    :     writeAveragesToOutput(highTemps, count, fout);
27    : }
28    :
29    :
30    :
31    :
32    : void checkArgs(int argc, char *infile, char *outfile, FILE **fin, FILE **fout)
33    : {
34    :     if (argc != 3)
35    :     {
36    :         printf("Wrong number of arguments on command line!\n");
37    :         exit(1);
38    :     }
39    :
40    :     if ((*fin = fopen(infile, "r")) == NULL)
41    :     {
42    :         perror("Cannot open input file");
43    :         exit(1);
44    :     }
45    :
46    :     if ((*fout = fopen(outfile, "w")) == NULL)
47    :     {
48    :         perror("Cannot open output file");
49    :         exit(1);
50    :     }
51    : }
52    :
53    :
54    :
55    : int readIntoWeatherStructs(struct weather *highTemps, FILE *fin)
56    : {
57    :     int count = 0, first = 1, highTemp;
58    :     char city[MAXLINE], line[MAXLINE];
59    :
60    :     while (fgets(line, MAXLINE, fin))
61    :     {
62    :          sscanf(line, "%s %d", city, &highTemp);
63    :          if (strcmp(city, highTemps[count].statecity) != 0)
64    :          {
65    :               if (first) first = 0;
66    :               else count++;
67    :               highTemps[count].tempsum = highTemp;
68    :               highTemps[count].count = 1;
69    :
70    :               if ((highTemps[count].statecity =
71    :                    (char *) malloc(strlen(city) + 1)) == NULL)
72    :               {
73    :                   perror("Malloc error!");
74    :                   exit(1);
75    :               }
76    :               strcpy(highTemps[count].statecity, city);
77    :          }
78    :          else
79    :          {
80    :               highTemps[count].tempsum += highTemp;
81    :               highTemps[count].count++;
82    :          } 
83    :     }
84    : 
85    :     return count;
86    : }
87    : 
88    : 
89    : 
90    : void writeAveragesToOutput(struct weather *highTemps, int count, FILE *fout)
91    : {
92    :      int i;
93    : 
94    :      for (i = 0; i <= count; i++) 
95    :         fprintf(fout, "%s %-5.1f\n", highTemps[i].statecity,
96    :                  (float) highTemps[i].tempsum/highTemps[i].count);
97    : }
 
*/







