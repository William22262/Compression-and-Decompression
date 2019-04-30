/*
Filename: Compress.c
Author: Gurjot Singh
Version: 1
Created Date: 3 Feb 2014
Description: File Compression and decompression
*/
#include <stdio.h>
#include <string.h>

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
	
	char szMessage[] = "This file will be first compressed and then decompressed again";
	static const unsigned nCompressedSize = sizeof(szMessage) * 7 / 8; 
	unsigned char pCompressedBytes[nCompressedSize];
	char szUncompressed[sizeof(szMessage)];
	printf("Original File Message: %s\n", szMessage);
	Compress(pCompressedBytes, szMessage);
	printf("Compressed File Details: ");
	for (int nByte = 0; nByte < nCompressedSize; ++nByte) {
		printf("%02X ", pCompressedBytes[nByte]);
	}
	printf("\n");
	Uncompress(szUncompressed, pCompressedBytes, nCompressedSize);
	szUncompressed[sizeof(szMessage) - 1] = 0; 
	printf("Decompressed File Details: %s\n", szUncompressed);
	/*Providing Compression Status*/
	if (strcmp(szMessage, szUncompressed) == 0) {
		printf("Compression Succeeded!\n");
	} else {
		printf("Compression failed!\n");
	}
	return 0;
}