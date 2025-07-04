# Strings
```
```
## Find length of the second last word in a string ?
```c
#include<stdio.h>
#include<string.h>
int last(char str[])
{
        char last[100];
        char second[100];
        char *word=strtok(str," ");
        while(word!=NULL)
        {
                strcpy(second,last);
                strcpy(last,word);
                word=strtok(NULL," ");

        }
        return strlen(second);
}
void main()
{
        char str[]="THIS IS VIVEN PK ACADEMY";
        int len=last(str);
        printf("Length of the second last word : %d\n",len);
}
```
## Find the length of the middle word in a string ?
```c
#include<stdio.h>
#include<string.h>

int findit(char str[])
{
        char words[100][100];
        int count=0;
        char *word=strtok(str," ");
        while(word!=NULL)
        {
                strcpy(words[count++],word);
                word=strtok(NULL, " ");
        }
        int middle=count/2;
        printf("The middle word is : %s\n",words[middle]);
        printf("The length of the middle word : %ld\n",strlen(words[middle]));
}
int main()
{
        char str[]="We are hyderabad army";
        printf("%s\n",str);
        findit(str);
        return 0;
}
```
## Find largest and smallest word in a string ?
```c
#include<stdio.h>
#include<string.h>
void find(char *str,char *large,char *small)
{
        char *word;
        word=strtok(str," ");
        strcpy(large,word);
        strcpy(small,word);
        while(word!=NULL)
        {
                if(strlen(word)>strlen(large))
                {
                        strcpy(large,word);
                }
                if(strlen(word)<strlen(small))
                {
                        strcpy(small,word);
                }
                word=strtok(NULL," ");
        }
}
int main()
{
        char str[]="I have two girlwords";
        char large[100],small[100];
        find(str,large,small);
        printf("The largest : %s\n",large);
        printf("The smallest : %s\n",small);
        return 0;
}
```
## Find length of the last word in a string ?
```c
#include<stdio.h>
#include<string.h>
int findword(char str[])
{
        char *word;
        char last[100];
        word=strtok(str," \n");
        while(word!=NULL)
        {
                strcpy(last,word);
                word=strtok(NULL," \n");
        }
        int length=strlen(last);
        return length;
}
int main()
{
        char str[]="VIVEN EMBEDDED ACADEMY";
        int length=findword(str);
        printf("The length of the last word : %d\n",length);
        return 0;
}
```
## Check if a string is palindrome or not ? 
```c
#include<stdio.h>
#include<string.h>
int palindrome(char *str)
{
        int left=0;
        int right=strlen(str)-1;
        while(left<right)
        {
                if(str[left]!=str[right])
                {
                        return 0;
                }
                left++;
                right--;
        }
        return 1;
}
int main(void)
{
        char str[]="MALAYALAM";
        printf("String : %s\n",str);
        if(palindrome(str))
        {
                printf("The string is palindrome\n");
        }
        else
        {
                printf("The string is not palindrome\n");
        }
        return 0;
}
```
## Replace a word in a string with another word ?
```c
#include<stdio.h>
#include<string.h>
void replace(char *str,char *old,char *new)
{
        char result[1000];
        int i=0,j=0;
        int oldlen=strlen(old);
        int newlen=strlen(new);
        while(*str)
        {
                if(strstr(str,old)==str)
                {
                        strcpy(&result[j],new);
                        j+=newlen;
                        str+=oldlen;
                }
                else
                {
                        result[j++]=*str++;
                }
        }
        result[j]='\0';
        printf("Modified string : %s\n",result);
}
int main()
{
        char str[100]="I love Bangalore. Bangalore is a great city!";
        char old[]="Bangalore";
        char new[]="Bengaluru";
        printf("Original string : %s\n",str);
        replace(str,old,new);
        return 0;
}
```
## Reverse a string ? 
```c
#include<stdio.h>
#include<string.h>
void reverse(char str[])
{
        char *word=strtok(str," ");
        int count=0;
        char *words[100];
        while(word!=NULL)
        {
                words[count++]=word;
                word=strtok(NULL," ");
        }
        char temp[100]="";
        for(int i=count-1;i>=0;i--)
        {
                strcat(temp,words[i]);
                if(i>0)
                {
                        strcat(temp," ");
                }
        }
        strcpy(str,temp);
}
int main()
{
        char str[]="RAMA KILLED RAVANA";
        printf("The original string : %s\n",str);
        reverse(str);
        printf("The reversed string : %s\n",str);
        return 0;
}
```
## Sort array of strings ?
```c
#include<stdio.h>
#include<string.h>
int main(void)
{
        char str[5][10]={"RED","WHITE","ORANGE","PINK","BLACK"};
        char temp[10];
        int i,j;
        printf("Before sorting : \n");
        for(i=0;i<5;i++)
        {
                printf("%s   ",str[i]);
        }
        printf("\n");
        for(i=0;i<5;i++)
        {
                for(j=i+1;j<5;j++)
                {
                        if(strcmp(str[i],str[j])>0)
                        {
                                strcpy(temp,str[i]);
                                strcpy(str[i],str[j]);
                                strcpy(str[j],temp);
                        }
                }
        }
        printf("After sorting :\n");
        for(i=0;i<5;i++)
        {
                printf("%s   ",str[i]);
        }
        printf("\n");
        return 0;
}
```
## Convert all uppercase letters to lowercase and all lowercase letters to uppercase in a string?
```c
#include<stdio.h>
#include<string.h>
int main()
{
        char str[100];
        printf("Enter a string : " );
        fgets(str,100,stdin);
        for(int i=0;str[i]!='\0';i++)
        {
                if(str[i]>='a' && str[i]<='z')
                {
                        str[i]=str[i]-32;
                }
                else if(str[i]>='A' && str[i]<='Z')
                {
                        str[i]=str[i]+32;
                }
        }
        printf("Converted string : %s",str);
        return 0;
}
```
