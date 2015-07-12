#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define FILENAME argv[1]

void xor_encrypt(char *, char *);

int main(int argc, char *argv[])
{
	char *str;
	FILE *fp;
	char key[] = "SECRET";

	if (argc != 2)
	{
		printf("usage: \n");
		return 1;
	}
	
	if ((fp = fopen(FILENAME, "r")) == NULL)
		printf("Error opening file.\n");
	else
	{
		// Get file size allocate memory.
		struct stat st;
		stat(FILENAME, &st);
		long int filesize = st.st_size;
		str = (char *)(malloc(filesize+1));

		// Store file content in array.
		int i;
		for (i = 0; i < filesize; i++)
			str[i] = getc(fp);
		str[i] = '\0';

		// Encrypt/Decrypt.
		printf("B: %s\n", str);
		xor_encrypt(str, key);
		printf("A: %s\n", str);

		// Write encrypted/decrypted content to file.
		freopen(FILENAME, "w", fp);
		for (i = 0; i < filesize; i++)
			putc(str[i], fp);

		free(str);
	}
	fclose(fp);
	
	return 0;
}

void xor_encrypt(char *string, char *key)
{
	int i;
	int keyLength = strlen(key);
	for(i = 0; i < strlen(string); i++)
	{
		string[i] ^= key[i % keyLength];
	}
}
