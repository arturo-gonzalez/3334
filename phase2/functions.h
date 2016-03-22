//Arturo Gonzalez
//CSCI 3334
//Phase2
//3/30/2016
#include <stdbool.h>

//opcode tab
struct optab
{
    char mnemonic[10] ;
    unsigned int value;

}optab;
//symbol tab
struct symtab
{

    char symbol[10];
    char value[10];
}symtab;

void pass1(char*p1);
void readLine(char*, char*, char*, char*, char*, struct symtab symtab1[25]);
void splitLine1(char*, char *, char*, char *, char*);
void handleLine1(char*, char *, char*, char *, char*,struct symtab symtab1[25]);

char label[80];
char opcode[80];
char operand[80];
char comment[128];
unsigned int LOCCTR = 0x0;
int startingAddress;
int programLength;
int symindex = 0;

FILE *intermediate;//create intermediate file


void pass1(char* p1)
{
        //create array of sructs for optab
    struct optab optab1[25];
    strcpy(optab1[0].mnemonic, "WD");
    optab1[0].value = 0xDC;
    strcpy(optab1[1].mnemonic, "ADD");
    optab1[1].value = 0x18;
    strcpy(optab1[2].mnemonic, "AND");
    optab1[2].value = 0x58;
    strcpy(optab1[3].mnemonic, "COMP");
    optab1[3].value = 0x28;
    strcpy(optab1[4].mnemonic, "DIV");
    optab1[4].value = 0x24;
    strcpy(optab1[5].mnemonic, "J");
    optab1[5].value = 0x3C;
    strcpy(optab1[6].mnemonic, "JEQ");
    optab1[6].value = 0x30;
    strcpy(optab1[7].mnemonic, "JGT");
    optab1[7].value = 0x34;
    strcpy(optab1[8].mnemonic, "JLT");
    optab1[8].value = 0x38;
    strcpy(optab1[9].mnemonic, "JSUB");
    optab1[9].value = 0x48;
    strcpy(optab1[10].mnemonic, "LDA");
    optab1[10].value = 00;
    strcpy(optab1[11].mnemonic, "LDCH");
    optab1[11].value = 0x50;
    strcpy(optab1[12].mnemonic, "LDL");
    optab1[12].value = 0x08;
    strcpy(optab1[13].mnemonic, "LDX");
    optab1[13].value = 0x04;
    strcpy(optab1[14].mnemonic, "MUL");
    optab1[14].value = 0x20;
    strcpy(optab1[15].mnemonic, "OR");
    optab1[15].value = 0x44;
    strcpy(optab1[16].mnemonic, "RD");
    optab1[16].value = 0xD8;
    strcpy(optab1[17].mnemonic, "RSUB");
    optab1[17].value = 0x4C;
    strcpy(optab1[18].mnemonic, "STA");
    optab1[18].value = 0x0C;
    strcpy(optab1[19].mnemonic, "STCH");
    optab1[19].value = 0x54;
    strcpy(optab1[20].mnemonic, "STL");
    optab1[20].value = 0x14;
    strcpy(optab1[21].mnemonic, "STX");
    optab1[21].value = 0x10;
    strcpy(optab1[22].mnemonic, "SUB");
    optab1[22].value = 0x1C;
    strcpy(optab1[23].mnemonic, "TD");
    optab1[23].value = 0xE0;
    strcpy(optab1[24].mnemonic, "TIX");
    optab1[24].value = 0x2C;

    int count = 0;
    for(;count<25; count++)
    {
            printf("Mnemonic = %s\n", optab1[count].mnemonic);
            printf("Value = %x\n", optab1[count].value);

    }



    //symbol table
    struct symtab symtab1[25];

    char line[128];
    //open the file
    FILE *fp;
    fp= fopen(p1,"r");

    //make sure file exists
    if((fp == NULL))
    {
        printf("cant open file %s\n",p1);
        exit(-1);
    }


    intermediate = fopen("intermediate.txt", "w");//clear the file
    fclose(intermediate);//close it
    fgets(line,128,fp);//get first line
    //break up line
    readLine(line,label,opcode,operand,comment,symtab1);
    while(!feof(fp))
    {
        printf("%s\n",line);
        fgets(line,128,fp);
        readLine(line,label,opcode,operand,comment,symtab1);

    }

}

void readLine(char* line, char *label, char*opcode, char *operand, char* comment, struct symtab symtab1[25])
{
    if(line[0]!='.')
    {
        //split the line
        splitLine1(line, label, opcode, operand, comment);
        //if opcode == start
        if(!strcmp(opcode, "START"))
        {
            LOCCTR += operand;
            startingAddress = operand;
            intermediate = fopen("intermediate.txt", "a");//open for apend
            fprintf(intermediate, "%s\n", line);//write line to intermediate file
            fprintf(intermediate, "Counter is %x\n", LOCCTR);//write locctr to intermediate file
            fprintf(intermediate, "this is the start line\n");
            fclose(intermediate); //close intermediate file


        }
        //if opcode is not END
        else if(strcmp(opcode, "END"))
        {
            intermediate = fopen("intermediate.txt", "a");//open for apend
            fprintf(intermediate, "%s\n", line);//write line to intermediate file
            //fprintf(intermediate, "Counter is %s\n", LOCCTR);//write locctr to intermediate file

            fprintf(intermediate, "this is not the end line\n");
            fclose(intermediate); //close intermediate file
            printf("this is not the end line");

            //hanlde line 1
            handleLine1(line, label, opcode, operand, comment, symtab1);

        }

    }
    else
    {
        //print comment
        printf("this is a comment");
    }


}

void handleLine1(char* line, char *label, char*opcode, char *operand, char* comment, struct symtab symtab1[25])
{
    //if there is a symbol in the label field
    int i=0;
    int j=0;
    bool inserttoSymtab = false;
    for(;i<sizeof(symtab1);i++)
    {
        if(label[0]!='\0')//if label is not empty
        {

            //check for label in symtab
            if(!strcmp(symtab1[i].symbol,label))
            {
                printf("its in the symtab\n");
                //error flag(duplicate label)
                inserttoSymtab = false;
            }
            else
            {
                printf("its not  int the symtab\n");
                inserttoSymtab = true;


            }
        }


    }
    if(inserttoSymtab)
    {
            //insert(label, locctr) into symtab
            printf("here I would insert into symtab\n");
            for(;j<sizeof(label);j++)
            {
                symtab1[symindex].symbol[j] = label[j];

            }

            printf(symtab1[symindex].symbol);



    }

}

void splitLine1(char* line, char *label, char*opcode, char *operand, char* comment)
{
    if(isalpha(line[0]))
    {
        label[0] = opcode[0] = operand[0] = comment[0]= '\0';
        int i = 0;
        int j = 0;
        int k = 0;
        int l = 0;
        int m = 0;
        int length = strlen(line)-1;

        while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;
        for(; i<=length;i++,l++)
        {
            if(line[i] != ' '&& line[i] !='\t')
            {
                label[l] = line[i];
            }
            else
            {

                break;
            }

        }
        label[l] = '\0';
        while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;
        for(; i<=length;i++,j++)
        {
            if(line[i] != ' '&& line[i] !='\t')
            {
                opcode[j] = line[i];
            }
            else
            {
                break;
            }

        }
        opcode[j] = '\0';
        while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;

        for(; i<=length;i++,k++)
        {
            if(line[i] != ' '&& line[i] !='\t')
            {
                operand[k] = line[i];
            }
            else
            {
                break;
            }

        }
        operand[k] = '\0';
        while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;

        for(; i<=length;i++,m++)
        {
            comment[m] = line[i];
        }
        comment[m] = '\0';
    }
    if(line[0]== ' '|| line[0]=='\t')
        {

            label[0] = opcode[0] = operand[0] = comment[0]= '\0';
            int i = 0;
            int j = 0;
            int k = 0;
            int l = 0;
            int length = strlen(line)-1;

            while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;
            for(; i<=length;i++,l++)
            {
                if(line[i] != ' '&& line[i] !='\t')
                {
                    opcode[l] = line[i];
                }
                else
                {

                    break;
                }

            }
            opcode[l] = '\0';
            while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;
            for(; i<=length;i++,j++)
            {
                if(line[i] != ' '&& line[i] !='\t')
                {
                    operand[j] = line[i];
                }
                else
                {
                    break;
                }

            }
            operand[j] = '\0';
            while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;

            for(; i<=length;i++,k++)
            {
                if(line[i] != ' '&& line[i] !='\t')
                {
                    comment[k] = line[i];
                }
                else
                {
                    break;
                }

            }
            comment[k] = '\0';
        }
    if(line[0]== '.')
    {
        label[0] = opcode[0] = operand[0] = comment[0]= '\0';
            int i = 0;
            int j = 0;
            int k = 0;
            int l = 0;
            int length = strlen(line)-1;
        while(line[i] == ' '|| line[i]=='\n' || line[i] =='\t')i++;

            for(; i<=length;i++,k++)
            {
                if(line[i] != ' '&& line[i] !='\t')
                {
                    comment[k] = line[i];
                }
                else
                {
                    break;
                }

            }
            comment[k] = '\0';
    }
}
