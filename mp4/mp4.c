//in this program we are ask to write a code that will detect and print out the semi prime numbers, first wee need to test is teh two number entered are valid, if they are valid we are testing how many of the number in that range is a product of two prime numbers. And we are able to do that by two seperate functons one checks if the number is prime the other is the loop which make sure we check every number that are in the loop.
#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);
int n;
int k;
int i;
int s = 0;

int main(){
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 )
   {
         printf("Inputs should be positive integers\n");
         return 1;
   }
   if( a > b )
   {
        printf("The first number should be smaller than or equal to the second number\n");
        return 1;
   }

   print_semiprimes(a,b);//call the function
   printf("\n");
   if(s==1){
      return 1; //if there is a semi prime number
          }else{
         return 0; // if there is non semi prime number
              }
}


int is_prime(int number)
{
      for(i=2; i<number; i++){
          if(number%i==0){
              return 0; //number is not prime
          }
      }
      return 1; // number is prime
}


int print_semiprimes(int a, int b)
{
      for(n=a;n<=b;n++){
         for(k=2;k<n-1;k++)
         {
              if (is_prime(k)) //if the first factor is prime
              {
                if(n%k==0)
                {
                  if (is_prime(n/k)) //if the second factor is also prim
                  {
                     printf("%d ",n); // if yes print the number
                     s = 1; //set s to 1 for the final value returned
                     break; //if n is semi prime jump to n+1
                  }
                }
              }
          }
     }
     return 0;
}
