## Write a C program to check if a number is even or odd using bitwise operators.
```C
#include<stdio.h>

int main()
{
        int n;
        printf("Enter a number : ");
        scanf("%d",&n);

        if(n & 1)
        {
                printf("Number %d is odd\n",n);
        }
        else
        {
                printf("Number %d is even\n",n);
        }
        return 0;
}
```
## Check if a number is a power of two using bitwise operators.
```c
#include<stdio.h>

int main()
{
        unsigned int n,x=1;

        printf("Enter a number : ");
        scanf("%u",&n);

        while(x < n)
        {
                x = x << 1;
        }
        if(x == n && n != 0)
        {
                printf("%u is power of 2\n",n);
        }
        else
        {
                printf("%u is not power of 2\n",n);
        }
        return 0;
}
```
### Logic 2
```c
#include<stdio.h>

int main()
{
        unsigned int n;
        printf("Enter a number : ");
        scanf("%u",&n);

        if(n != 0 && (n & (n-1)) == 0)
        {
                printf("%u is power of 2\n",n);
        }
        else
        {
                printf("%u is not power of 2\n",n);
        }
        return 0;
}
```
## Find the position of the first set bit (LSB).
```c
#include<stdio.h>

int main()
{
        unsigned int n;
        printf("Enter a number : ");
        scanf("%d",&n);

        for(int i=0;i<=31;i++)
        {
                if((n >> i) & 1)
                {
                        printf("LSB : First set bit is at %d position\n",i+1);
                        break;
                }
        }
        return 0;
}
```
## Find the position of the highest set bit (MSB).
```c
#include<stdio.h>

int main()
{
        unsigned int n;
        printf("Enter a number : ");
        scanf("%u",&n);

        for(int i=31;i>=0;i--)
        {
                if((n >> i) & 1)
                {
                        printf("MSB : First set bit at %u position\n",i+1);
                        break;
                }
        }
        return 0;
}
```
