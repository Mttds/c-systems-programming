#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STRING_LEN 20

/*
 @Author: md
 @Date: December 2019
 @Desc: Converts an input hexadecimal number to its binary representation
 Compile it with gcc hex2binary.c -lm -o hex2binary.exe
 this instructs gcc to link the math.h library
*/

int hex_to_binary(char hex[], int binary_number[]) {
	int i, j=0, length, decimal=0;
	//initialize length traversing the hex char array until \0 is found
	for(length=0; hex[length]!='\0'; ++length);

	printf("\nCalculations...\n");	
	//loop until the end of the hex char array 
	for(i=0; hex[i]!='\0'; ++i, --length) {
		printf("Loop number %d\n", i);
		printf("hex[i] is %d\n", hex[i]);
		printf("length is %d\n", length);
		printf("i is %d\n", i);
		printf("decimal is %d\n\n", decimal);
		//use ascii codes to subtract the correct amount times base 16 to the (length of hex - 1), decreasing length in each iter
		if(hex[i]>='0' && hex[i]<='9')
			decimal+=(hex[i]-'0')*pow(16,length-1);
		if(hex[i]>='A' && hex[i]<='F')
			decimal+=(hex[i]-55)*pow(16,length-1);
		if(hex[i]>='a' && hex[i]<='f')
			decimal+=(hex[i]-87)*pow(16,length-1);
	}
	//variable decimal contains the hexadecimal number in decimal format. 
	while (decimal != 0) {
		binary_number[j++] = decimal%2;
		decimal /= 2;
	}
	return j;
}

int main() {
	printf("********* Hex to Binary conversion **********\n");
	char hex[STRING_LEN];
	int binary_number[100];
	printf("Input the hexadecimal number representation: ");
	fgets(hex, STRING_LEN, stdin);

	int result, k;
	result = hex_to_binary(hex, binary_number);

	printf("Binary representation is: ");
	for(k = result-1; k >= 4; k--) { // k greater than 4 since 0 is appendend at the end and we don't want its binary representation to be appended to the result
		printf("%d", binary_number[k]);
	}
	printf("\n\n");
		
	return 0;
}
