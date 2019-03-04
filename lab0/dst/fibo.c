#include<stdio.h>

int fibo(int n){
    int a = 1;
    int b = 1;
    int c;
    if (n == 0)
	return 0;
    else if (n == 1)
	printf("%d ",a);
    else {
	printf("%d %d ",a,b);
   	while (n > 2) {
	    c = a + b;
	    a = b;
	    b = c;
	    printf("%d ",c);
	    n--;  
	}
    }
    return 0;
}

int main(){
    int var;
    scanf("%d", &var);
    fibo(var);
    return 0;
}
