#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define LOWER_VAL 50                      
#define UPPER_VAL 200                                          
#define TEST_CASES 500

//Primality tests
bool BasicPrimes(int num);
bool MillerRabinTest(int num, int k);
bool FermatTest(int num, int k);

//Utilities
int GCD(int k,int T);
int BigMod(int a, int b, int c);
int PrimeGen();

//Encrytion and Decryption
int Encrypt(int message, int e, int n);
int Decrypt(int cipher, int d, int n);

int main()
{
    clock_t begin = clock();
    srand(time(0));

    int p,q;

    label:
    
    p = PrimeGen();
    q = PrimeGen();
    if(p == q)
        goto label;

    printf("The Prime numbers generated are: %d and %d\n",p,q);

    int n = p*q;
    int t = (p-1)*(q-1);
    int e,d;

    printf("The value of n is : %d\nThe value of totient is : %d\n",n,t);

//public keys
    E_label:
    e = (rand() % (t-2))+2;
    while( GCD(e,t)!=1 )
        e++;
    
    if(e >= t)
        goto E_label;


    printf("The value of public key is(e) : %d\n",e); 

//private keys
    d = 2;
    while( BigMod(d*e,1,t) != BigMod(1,1,t) )
    {
        d++;
    }
    printf("The value of private key is(d) : %d\n\n",d);

//Algorithm is complete here. The keys are generated. Its time for Encryption and Decryption

    char string[] = "Sphinx of Black Quartz, judge my vow!";                        // The message
    int size = sizeof(string)/sizeof(string[0]);
    int num[size];

    fputs("The message to be transmitted is : ",stdout);
    for(int i=0; i<size ;i++)
    {
        printf("%c",string[i]);                                     // print the original string
    }

    for(int i=0; i<size ;i++)
    {
        num[i] = string[i];                                         // Set the string array to a number array
    }
    
    for(int i=0; i<size ;i++)
    {
        num[i] = Encrypt(num[i],e,n);                               // Set the cipher number into  the num array
    }

    fputs("\nThe cipher text generated is : ",stdout);
    for(int i=0; i<size ;i++)
    {
        printf("%d",num[i]);                                        // print the cipher generated
    }

    for(int i=0; i<size ;i++)
    {
        num[i] = Decrypt(num[i],d,n);                               // decrypting the message
    }

    fputs("\nThe regenerated message is : ",stdout);

    for(int i=0; i<size ;i++)
    {
        printf("%c",num[i]);                                        // print the generated message
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n Time needed for execution : %lf",time_spent);
}

int GCD(int k,int T) 
{ 
    if (T == 0) 
        return k; 
    return GCD(T, k % T);  
}

int BigMod(int a, int b,int c )
{
    if( b == 0 )
        return 1;
    else if( b % 2 == 0 )
    {
        int value = BigMod(a,b/2,c);

        return ((value * value) % c);                                                    
    }
    else
    {
        int x,y;

        x = a % c;
        y = BigMod(a,b-1,c);

        return (x * y) % c; 
    }                                                            
}

int Encrypt(int message, int e, int n)
{
    int cipher;
    cipher = BigMod(message,e,n);
    return cipher;
}

int Decrypt(int cipher,int d, int n)
{
    int message;
    message = BigMod(cipher,d,n);
    return message;
}

int PrimeGen()
{
    int num = (rand() % (UPPER_VAL - LOWER_VAL + 1)) + LOWER_VAL;           
    bool res = 0;

    label:
    res = BasicPrimes(num);

    if(res == true)
    {
        res = FermatTest(num,TEST_CASES);

        if(res == true)
        {
            res = MillerRabinTest(num,TEST_CASES);
            if( res == true )
                    return num;                     
        }                           
        else
        {
            num++;
            goto label;
        }  
    }   
    else
    {
        num++;
        goto label;
    } 
}

bool MillerRabinTest(int num, int k)        
{
    long int d = num-1;
    int r = 0;
    int a,x;
    int flag;

    while(d % 2 == 0)
    {
        d = d/2;
        r++;
    }

    for(int i=0; i<k; i++)
    {
        flag = 0;
        a = (rand() % (num - 3)) + 2;
        x = BigMod(a,d,num);

        if( x == 1 || x == num-1)
            continue;
        
        for(int j=0; j<r; j++)
        {
            x = (x*x) % num;
            if( x == num-1 )
            {
                flag = 1;
                break; 
            }    
        }

        if(flag == 1)           
            continue;

        return false;     
    }
    return true;
}

bool FermatTest(int num, int k)
{
    unsigned long a;                        

    for(int i=0; i<k; i++)
    {
        a = (rand() % (num - 3)) + 2; 

        if(BigMod(a,num-1,num) != BigMod(1,1,num))
            return false;
    }

    return true;
}

bool BasicPrimes(int num)
{
    if(num % 2 == 0 && num != 2)                 
        return false;
    if(num % 3 == 0 && num != 3)
        return false;
    if(num % 5 == 0 && num != 5)
        return false;
    if(num % 7 == 0 && num != 7)
        return false;
    if(num % 11 == 0 && num != 11)
        return false;
    if(num % 13 == 0 && num != 11)
        return false;
    if(num % 17 == 0 && num != 11)
        return false;
    if(num % 23 == 0 && num != 11)
        return false;
    
    return true;
}