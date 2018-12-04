#ifndef T_H
#define T_H

/// The necessary libraries for the program to execute correctly
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int u32;

char *ctable = "0123456789ABCDEF";

int BASE_TEN = 10;
int BASE_EIGHT = 8;
int BASE_SIXTEEN = 16;

/// An interger pointer
int *FP;
int *FU;
/// The function prototype for the program
int A(int x, int y);
int B(int x, int y);
int C(int x, int y);
int rpu(u32 x);
int printu(u32 x);
int print_integer(int signed_integer);
void my_print_f(char * sentence_string, ...);
void hex(u32 hex);
int print_x(u32 hex);
int print_oct(u32 oct);
void oct(u32 oct);
void print_string(char *tempString);
////////////////////////////////////////////////////////////////////////////////
/// This function is the main function of the program
/// @param[in] argc: the number of arguments passed in on the command line
/// @param[in] argv: the arguments passed in on the command line
/// @param[in] env: the enviroment that the program is running on
int main(int argc, char *argv[ ], char *env[ ])
{
   int a,b,c;
   my_print_f("---enter main---\n");

   my_print_f("&argc=%x argv=%x env=%x\n", &argc, argv, env);
   my_print_f("&a=%x &b=%x &c=%x\n", &a, &b, &c);

   /// Write C code to print values of argc and argv[] entries
   ///my_print_f("Hellow: " + argc + "/n");

   /// A for loop that itterates through the argv[] 
   for(auto index = 1; index<argc; index++)
   {
      my_print_f( argv[index]);
      my_print_f("\n");

   }

   a=1; b=2; c=3;
   getchar();
   /// @see A()
   A(a,b);

   my_print_f("---exit main---\n");
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///This function shows the address of certain variables
/// @param[in] x an interger
/// @param[in] y an interger
int A(int x, int y)
{
   int d,e,f;
   my_print_f("===enter A===\n");

   /// Prints the address of the variable d, e, and f
   my_print_f("&d=%x &e=%x &f=%x \n", &d, &e, &f);

   d=4; e=5; f=6;

   getchar();
   /// @see B()
   B(d,e);

   my_print_f("===exit A===\n");
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// This function shows the address of certain variables
/// @param[in] x an integer
/// @param[in] y an integer
int B(int x, int y)
{
   int g,h,i;
   my_print_f("---enter B---\n");

   /// Prints the address of the variable g, h, and i
   my_print_f("&g=%x &h=%x &i=%x \n", &g, &h, &i); 

   g=7; h=8; i=9;

   getchar();
   /// @see C()
   C(g,h);

   my_print_f("---exit B--- \n");
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// This function shows the address of certain variables
/// @param[in] x an integer
/// @param[in] y an integer
int C(int x, int y)
{
   int u, v, w, i, *p;

   my_print_f("===enter C===\n");
   /// Prints the address of the variable u, v, w, i, p
   my_print_f("&u=%x &v=%x &w=%x &i=%x &p=%x\n", &u, &v, &w, &i, p);

   u= -10; v=11; w=12; i=13;

   FP = (int *)getebp();

   getchar();
   /// Prints the stack frame link list
   while(FP != 0)
   {

      my_print_f("Address: %x Value: %x \n", FP, *FP);
      FP= (int*)*FP;
   }

   /// Print the first 128 stack content from p to the frame 
   getchar();
   p = (int *)&p;
   for( int index= 0; index<128; index++, p++)
   {
      my_print_f("%x     %x\n",p, *p);
   }
   getchar();
   my_print_f("hello world %d \n", u);
   /*    (4). On a hard copy of the print out, identify the stack contents
         as LOCAL VARIABLES, PARAMETERS, stack frame pointer of each function.
    */
}

int rpu(u32 x)
{
   char c;
   if (x){
      c = ctable[x % BASE_TEN];
      rpu(x / BASE_TEN);
      putchar(c);
   }
}

int printu(u32 x)
{
   (x==0)? putchar('0') : rpu(x);
   putchar(' ');
}

int print_integer(int signed_integer)
{
   /// creates a placeholder for the integer character later on
   char covert_int_to_char;
   /// x is negative
   if (signed_integer<0)
   {
      /// Shows the negativety of a number
      print_string("-");

      // Making the negative number positive
      signed_integer = signed_integer * (-1);

   }
   /// No longer negative
   if(signed_integer>=0)
   {
      if(signed_integer == 0)
      {
         covert_int_to_char = '0';
      }
      if(signed_integer != 0)
      {
      covert_int_to_char = ctable[signed_integer % BASE_TEN];
      print_integer(signed_integer / BASE_TEN);
      }
      putchar(covert_int_to_char);
   }
}

void my_print_f(char * sentence_string, ...)
{
   char * char_pointer;
   int *integer_pointer;
   asm("movl %ebp, FU");
   integer_pointer = FU +3;

   for (char_pointer = sentence_string; *char_pointer != '\0'; char_pointer++)
   {
      if (*char_pointer != '%')
      {
         putchar(*char_pointer);
         if (*char_pointer == '\n')
         {
            putchar('\r');
         }
         if ( *char_pointer == '\t')
         {
            putchar('\t');
         }
      }
      if ( *char_pointer == '%')
      {
         char_pointer++;
         switch(*char_pointer)
         {
            case 'd':
               print_integer(*integer_pointer);
               break;
            case 'c':
               putchar((char)(*integer_pointer));
               break;
            case 's':
               print_string((char *)(*integer_pointer));
               break;
            case 'o': 
               oct(*integer_pointer);
               break;
            case 'x':
               hex(*integer_pointer);
               break;
            default:
               my_print_f("Invalid input");
               break;
         }
         integer_pointer++;
      }
   }
}


void print_string(char *tempString)
{
   while( *tempString)
   {
      putchar(*tempString);
      tempString++;
   }
}

void oct(u32 tempOct)
{
   print_string("0");
   print_oct(tempOct);
}

int print_oct(u32 tempOct)
{
   char convert_oct_to_char;
   if(tempOct)
   {
      convert_oct_to_char = ctable[tempOct%BASE_EIGHT];
      print_oct (tempOct/BASE_EIGHT);
      putchar(convert_oct_to_char);
   }
}

void hex(u32 hexagon)
{
   print_x(hexagon);
}

int print_x(u32 hexadecimal)
{
   char convert_hex_to_char;
   if(hexadecimal)
   {
      convert_hex_to_char= ctable[hexadecimal % BASE_SIXTEEN];
      print_x( hexadecimal / BASE_SIXTEEN);
      putchar(convert_hex_to_char);
   }
}
#endif /// T_H
