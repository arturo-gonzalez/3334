//Arturo Gonzalez
//CSCI 3334
//Phase2
//3/../2016

void pass1(char*p1);
void readLine(char*, char*, char*, char*, char*,struct symtab symtab1[], int n);
void splitLine2(char*, char*, char*, char*, char*);
void splitLine3(char*, char*, char*, char*, char*);
void splitLine1(char*, char *, char*, char *, char*);
void handleLine1(char*, char *, char*, char *, char*,struct symtab symtab[], int n);

char label[80];
char opcode[80];
char operand[80];
char comment[128];
int LOCCTR = 0;
int startingAddress;
int programLength;

FILE *intermediate;//create intermediate file
//opcode tab
struct optab
{
    char mnemonic[10] ;
    char value[10];

}optab;
//symbol tab
struct symtab
{

    char symbol[10];
    char value[10];
}symtab;
void pass1(char* p1)
{
        //create array of sructs for optab
    struct optab optab1[25];
    strcpy(optab1[1].mnemonic, "ADD");
    strcpy(optab1[1].value, "18");
    strcpy(optab1[2].mnemonic, "AND");
    strcpy(optab1[2].value, "58");
    strcpy(optab1[3].mnemonic, "COMP");
    strcpy(optab1[3].value, "28");
    strcpy(optab1[4].mnemonic, "DIV");
    strcpy(optab1[4].value, "24");
    strcpy(optab1[5].mnemonic, "J");
    strcpy(optab1[5].value, "3C");
    strcpy(optab1[6].mnemonic, "JEQ");
    strcpy(optab1[6].value, "30");
    strcpy(optab1[7].mnemonic, "JGT");
    strcpy(optab1[7].value, "34");
    strcpy(optab1[8].mnemonic, "JLT");
    strcpy(optab1[8].value, "38");
    strcpy(optab1[9].mnemonic, "JSUB");
    strcpy(optab1[9].value, "48");
    strcpy(optab1[10].mnemonic, "LDA");
    strcpy(optab1[10].value, "00");
    strcpy(optab1[11].mnemonic, "LDCH");
    strcpy(optab1[11].value, "50");
    strcpy(optab1[12].mnemonic, "LDL");
    strcpy(optab1[12].value, "08");
    strcpy(optab1[13].mnemonic, "LDX");
    strcpy(optab1[13].value, "04");
    strcpy(optab1[14].mnemonic, "MUL");
    strcpy(optab1[14].value, "20");
    strcpy(optab1[15].mnemonic, "OR");
    strcpy(optab1[15].value, "44");
    strcpy(optab1[16].mnemonic, "RD");
    strcpy(optab1[16].value, "D8");
    strcpy(optab1[17].mnemonic, "RSUB");
    strcpy(optab1[17].value, "4C");
    strcpy(optab1[18].mnemonic, "STA");
    strcpy(optab1[18].value, "0C");
    strcpy(optab1[19].mnemonic, "STCH");
    strcpy(optab1[19].value, "54");
    strcpy(optab1[20].mnemonic, "STL");
    strcpy(optab1[20].value, "14");
    strcpy(optab1[21].mnemonic, "STX");
    strcpy(optab1[21].value, "10");
    strcpy(optab1[22].mnemonic, "SUB");
    strcpy(optab1[22].value, "1C");
    strcpy(optab1[23].mnemonic, "TD");
    strcpy(optab1[23].value, "E0");
    strcpy(optab1[24].mnemonic, "TIX");
    strcpy(optab1[24].value, "2C");
    strcpy(optab1[25].mnemonic, "WD");
    strcpy(optab1[25].value, "DC");

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
    readLine(line,label,opcode,operand,comment, symtab1, 25);
    while(!feof(fp))
    {
        printf("%s\n",line);
        fgets(line,128,fp);
        readLine(line,label,opcode,operand,comment,symtab1, 25);

    }

}

void readLine(char* line, char *label, char*opcode, char *operand, char* comment,struct symtab symtab1[], 25)
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
            fprintf(intermediate, "Counter is %s\n", LOCCTR);//write locctr to intermediate file
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
            handleLine1(line, label, opcode, operand, comment);

        }

    }
    else
    {
        //print comment
        printf("this is a comment");
    }


}

void handleLine1(char* line, char *label, char*opcode, char *operand, char* comment,struct symtab symtab1[],25)
{
    //if there is a symbol in the label field
    int i=0;
    for(;i<symtab1.size;i++)
    {

        //check for label in symtab
        if(!strcmp(symtab1[i],label))
        {
            printf("its in the symtabl");
            //error flag(duplicate label)
        }
        else
        {
            printf("its not  int the symtab");
            //insert(label, locctr) into symtab
        }
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
