//Taylor Rosby
//CST - 221
//https://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary
//http://scanftree.com/programs/c/c-code-to-convert-decimal-to-hexadecimal/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int decToHex(decimalNumber)
{
  long int remainder, quotient;
  int i = 1, j, temp;
  char hexadecimalNumber[100];
  quotient = decimalNumber;
  //repeats the loop until the quotient = 0
  while (quotient != 0)
  {
    //divides the original number by 16
    temp = quotient % 16;
    //To convert integer into character
    if (temp < 10)
    {
      temp = temp + 48;
    }
    else
    {
      temp = temp + 55;
    }
    //divide the quotient by 16
    hexadecimalNumber[i++] = temp;
    quotient = quotient / 16;
  }
  printf("Equivalent hexadecimal value of decimal number %d: ", decimalNumber);
  for (j = i - 1; j > 0; j--)
  {
    printf("%c", hexadecimalNumber[j]);
  }
  printf("\n");
  return 0;
}

int decToBin(n)
{
  int c, k;

  printf("%d in binary number system is:\n", n);

  //repeats for each bit until it gets to the last one
  for (c = 31; c >= 0; c--)
  {
    //right shifts n with the numbrt of the current loop
    k = n >> c;

    //if the values are the same print 1
    if (k & 1)
      printf("1");
    //else print 0
    else
      printf("0");
  }

  printf("\n");

  return 0;
}

int bitMask(input)
{
  //shifts the inputted number to the left by 16 bits
  int shifted = input << 16;
  printf("%d left shifted by 16 = %d\n", input, shifted);

  //masks the bottom 16 bits
  uint32_t masked = shifted & 0xFFFF0000;

  printf("shifted value masked = %d\n", masked);

  //adds the hex 0x7fff
  uint32_t masked2 = masked | 0x7FFFFFFF;

  printf("masked part 2 = %d\n", masked2);

  //takes the fully masked number and translates it to binary and hexadecimal
  decToBin(masked2);
  decToHex(masked2);
}

int main()
{
  //the number the user imputs
  long int decimalNumber;

  printf("\n");
  //takes the user input and saves it to decimalNumber
  printf("Enter any decimal number: ");
  scanf("%ld", &decimalNumber);
  printf("\n");

  //translates the number to binary, hexidecimal, and masks it
  decToBin(decimalNumber);
  printf("\n");
  decToHex(decimalNumber);
  printf("\n");
  bitMask(decimalNumber);
}
