void pass1(char*p1);
void readLine(char*, char*, char*, char*, char*);
void splitLine2(char*, char*, char*, char*, char*);
void splitLine3(char*, char*, char*, char*, char*);

char label[80];
char opcode[80];
char operand[80];
char comment[128];

void pass1(char* p1)
{
    char line[128];

    //open the file
    FILE *fp;
    fp= fopen(p1,"r");

    //make sure file exists
    if((fp == NULL))
    {
        printf("cant open file %s\n",p1);
        //return -1;
    }

    fgets(line,128,fp);//get first line
    //break up line
    readLine(line,label,opcode,operand,comment);
    while(!feof(fp))
    {

        printf("%s\n",line);
        fgets(line,128,fp);
        readLine(line,label,opcode,operand,comment);
    }

}

void readLine(char* line, char *label, char*opcode, char *operand, char* comment)
{
    if(isalpha(line[0]))
    {
        splitLine2(line,label,opcode,operand,comment);
        printf("%s \t%s \t%s \t%s\n", label, opcode, operand, comment);
    }
    if(line[0]== ' '|| line[0]=='\t')
    {

        splitLine3(line,label,opcode,operand,comment);
        printf("\t%s \t%s \t%s\n", opcode, operand, comment);
    }
    if(line[0] == '.')
    {
        printf("it is a comment\n");

    }
}

//function to split line
void splitLine2(char* line, char *label, char*opcode, char *operand, char* comment)
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

//split line when there is no label
void splitLine3(char* line, char *label, char*opcode, char *operand, char* comment)
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

