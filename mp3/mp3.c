//parentrs: sz31 soohar2
// in this code i wrote two for loop and a couple if statements. where the for loop will deal with the k and the i that are in the equation and the if statement mainly take contol of the row number, where when the row number is 0 it sould print 1.
#include <stdio.h>
#include <stdlib.h>

int main()
{
   
    int row;
    unsigned long coefficient=1;
    int k;
    int i =1;
    unsigned long n=1;

  printf("Enter a row index: ");
  scanf("%d",&row);

    if(row == 0){
      printf("1");//special row number
    }else{
        
        for(k=0;k<row+1;k++){
            
            if(k==0 || k==row){
	      printf("1 ");//as k starts counting from 0, but can't fit into the for loop, so i careated it's own if statement
            }else if(k >= i){
                
                for(i=1;i<=k;i++){
		  //onto the regular loop, where i will keep adding until it reach the value of k, and than do the calculation
		            n=n*(row+1-i)/i;
        	            coefficient = n;
                        }
		printf("%lu ",coefficient);//print the answer
	                n = 1;
                        i = 1;
                    }
                }
            }
	printf("\n");
	return 0;
}
