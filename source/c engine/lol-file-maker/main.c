#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char *split_char = "-";
char *sep_char = ";";
char *end_header_char = "|";

char *va(char *format, ...)
{
	va_list         argptr;
	char             string[1024];
	
	va_start (argptr, format);
	vsprintf (string, format,argptr);
	va_end (argptr);

	return string;  
}

void addFileToArchiveHeader(char *filename, FILE *f)
{
	static int done = 0;
	FILE *f2 = fopen(filename, "r+b");
	unsigned long size = 0;
	char *val = "";

	fseek(f2, 0, SEEK_END);
	size = ftell(f2);

	if(!done)
	{
		fseek(f2, 0, SEEK_SET);
		done=1;
	}

	val = va("%s%s", filename, split_char);
	fwrite(val, 1, strlen(val), f);
	fwrite(&size, sizeof(int), 1, f);
	fwrite(sep_char, 1, strlen(sep_char), f);

	fclose(f2);
}

void addFileToArchive(char *filename, FILE *f)
{
	FILE *f2 = fopen(filename, "r+b");
	int c = 0;
	char *val = "";
	
	do{
		if(c==59)/* == ';'*/
		{

		}
		else
		{
		
		}	
	}while(c!=EOF);
}

void endArchiveHeader(FILE *f)
{
	fwrite(end_header_char, 1, sizeof(end_header_char), f);
}

int main()
{
	FILE *f = fopen("archive.lol", "w+b");

	addFileToArchiveHeader("test.txt", f);
	addFileToArchiveHeader("test2.txt", f);
	endArchiveHeader(f);

	addFileToArchive("test.txt", f);
	addFileToArchive("test2.txt", f);

	fclose(f);
	
	return 0;
}