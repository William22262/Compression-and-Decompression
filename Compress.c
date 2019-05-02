/*
Filename: Compress.c
Author: Gurjot Singh
Version: 1
Created Date: 3 Feb 2014
Description: File Compression and decompression
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Function to compress the file*/
void Compress(unsigned char *szOut, const char *szMessage) {
	/*Data nBuffer to store the details of the file*/
    unsigned long long nBuffer = 0; 
	char nBitsInBuffer = 0;
	while (*szMessage != 0) {
		nBuffer |= (unsigned long long)(*szMessage++ & 0x7F) << nBitsInBuffer;
		nBitsInBuffer += 7;
		if (nBitsInBuffer == 7 * 8) { 
            /*Removing the bits after use*/
			while (nBitsInBuffer > 0) {
				*szOut++ = nBuffer & 0xFF;
				nBuffer >>= 8;
				nBitsInBuffer -= 8;
			}
			
			nBitsInBuffer = 0;
			nBuffer = 0;
		}
	}
	/*Storing the results*/
	while (nBitsInBuffer > 0) {
		*szOut++ = nBuffer & 0xFF;
		nBuffer >>= 8;
		nBitsInBuffer -= 8;
	}
}

/*Function to decompress the file*/
void Uncompress(char *szOut, const unsigned char *szCompressed, unsigned nCompressedLen) {
	/*Data Type to store data in nBuffer*/
    unsigned long long nBuffer = 0; 
	char nBitsInBuffer = 0;
	while (nCompressedLen) {
		while (nCompressedLen && nBitsInBuffer < 7 * 8) {
			nBuffer |= (unsigned long long)*szCompressed++ << nBitsInBuffer;
			nBitsInBuffer += 8;
			--nCompressedLen;
		}
		while (nBitsInBuffer > 0) {
			*szOut++ = nBuffer & 0x7F;
			nBuffer >>= 7;
			nBitsInBuffer -= 7;
		}
		nBitsInBuffer = 0;
		nBuffer = 0;
	}
}

int main() {

    int  i=0;

	/* Character Array for the Project */
    char szMessage[100];  
    
	/* Creating the file pointer */
    FILE *file;  
	/*Opening the file to be compressed*/
    file = fopen("file.txt", "r"); 
    
	/*Reading the contents of the file*/
    while(fgets(szMessage, sizeof szMessage, file)!=NULL) {      
      continue; 
    }
    fclose(file);
    
	//char szMessage[] = "This file will be first compressed and then decompressed again";
	static const unsigned nCompressedSize = sizeof(szMessage) * 7 / 8; 
	unsigned char pCompressedBytes[nCompressedSize];
	char szUncompressed[sizeof(szMessage)];
	printf("\n------------------------File Compression and Decompression Project------------------------");
	printf("\nAuthor: Gurjot Singh");
	printf("\n");
	printf("\nOriginal File Message: %s\n", szMessage);
	Compress(pCompressedBytes, szMessage);
	printf("------------------------File Compression---------------------------------------------------");
	printf("\n\nCompressed File Details: ");
	for (int nByte = 0; nByte < nCompressedSize; ++nByte) {
		printf("%02X ", pCompressedBytes[nByte]);
	}
	printf("\n");
	printf("File has been compressed to compressed.out file!");
	
	FILE *f = fopen("compressed.out", "wb");
	fwrite(pCompressedBytes, sizeof(char), sizeof(pCompressedBytes), f);
	fclose(f);
	printf("\n\n------------------------File Decompression-------------------------------------------------");
    int  j=0;

	/* Character Array for the Project */
    char szMessage1[100];  
    
	/* Creating the file pointer */
    FILE *file1;  
	/*Opening the file to be compressed*/
    file1 = fopen("compressed.out", "r"); 
    
	/*Reading the contents of the file*/
    while(fgets(szMessage1, sizeof szMessage1, file)!=NULL) {      
      continue; 
    }
    fclose(file1);
//	printf("%s",szMessage1);

	Uncompress(szUncompressed, pCompressedBytes, nCompressedSize);
	szUncompressed[sizeof(szMessage1) - 1] = 0; 
	printf("\n\nDecompressed File Details: %s\n", szUncompressed);


	/*Storing the results in a file*/
	FILE *f2 = fopen("decompressed.txt", "wb");
	fwrite(szUncompressed, sizeof(char), sizeof(szUncompressed), f2);
	fclose(f2);
	printf("File has been decompressed to decompressed.txt file");
		/*Providing Compression Status*/
	if (strcmp(szMessage, szUncompressed) == 0) {
		printf("\n\nCompression and decompression Succeeded!\n");
	} else {
		printf("\n\nCompression and decompression failed!\n");
	}
	return 0;
}