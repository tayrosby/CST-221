//Taylor Rosby
//CST - 221
//https://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary
//http://scanftree.com/programs/c/c-code-to-convert-decimal-to-hexadecimal/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decToHex(decimalNumber)
{
  long int remainder,quotient;
	int i=1,j,temp;
	char hexadecimalNumber[100];
	quotient = decimalNumber;
	while(quotient!=0) {
		temp = quotient % 16;
		//To convert integer into character
		if( temp < 10)
    {
      temp =temp + 48; 
    }
    else
    {
      temp = temp + 55;
    }
    
		hexadecimalNumber[i++]= temp;
		quotient = quotient / 16;
	}
	printf("Equivalent hexadecimal value of decimal number %d: ",decimalNumber);
	for (j = i -1 ;j> 0;j--)
    {
	    printf("%c",hexadecimalNumber[j]);
    }
  printf("\n");
	return 0;
}

int decToBin(n)
{
  int c, k;
 
  printf("%d in binary number system is:\n", n);
 
  for (c = 31; c >= 0; c--)
  {
    k = n >> c;
 
    if (k & 1)
      printf("1");
    else
      printf("0");
  }
 
  printf("\n");
 
  return 0;
}

int bitMask(input)
{
    int shifted = input << 16;
    printf("%d left shifted by 16 = %d\n", input, shifted); 

   uint32_t masked = shifted & 0xFFFF0000;

   printf("shifted value masked = %d\n", masked);

   uint32_t masked2 = masked | 0x7FFFFFFF;

   printf("masked part 2 = %d\n", masked2);

   decToBin(masked2);
   decToHex(masked2);
}

int main()
{
  long int decimalNumber;

  printf("\n");
  printf("Enter any decimal number: ");
  scanf("%ld",&decimalNumber);
  printf("\n");

  decToBin(decimalNumber);
  printf("\n");
  decToHex(decimalNumber);
  printf("\n");
  bitMask(decimalNumber);
}
