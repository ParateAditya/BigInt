#include <stdio.h>
#include <string.h>
#define SIZE 310

typedef struct BigInteger
{
    int arr[SIZE];
    int size;
    int sign;
} BigInt;

BigInt input()
{
    printf("Enter the number :");
    char s[SIZE];
    scanf("%s", s);
    int length = strlen(s);
    BigInt k;
    int z = 0;
    for (int i = length - 1; i > 0; i--)
    {
        k.arr[z] = s[i] - '0';
        z++;
    }
    if (s[0] == '-')
    {
        k.sign = -1;
    }
    else
    {
        k.arr[z] = s[0] - '0';
        z++;
        k.sign = 1;
    }
    k.size = z;
    return k;
}
void printBigInt(BigInt k)
{
    if (k.sign == -1)
    {
        printf("-");
    }
    for (int i = k.size - 1; i >= 0; i--)
    {
        printf("%d", k.arr[i]);
    }

    printf("\n");
}
BigInt add(BigInt a, BigInt b);
BigInt subtract(BigInt a, BigInt b)
{
    BigInt ans;
    if (a.size < b.size)
    {
        if((b.sign == 1 && 1 == a.sign) ){
            ans = subtract(b , a);
            ans.sign = -1;
        }else if(b.sign == -1 && -1 == a.sign){
            ans = subtract(b , a);
            ans.sign = 1;
        }
        else if( a.sign == 1 && b.sign==-1){
            ans = add(a,b);
            ans.sign =1;
        }else{
            ans = add(a,b);
            ans.sign=-1;
        }
        return ans;
    }
    else if (a.size == b.size)
    {
        int i = a.size - 1;
        while (i >= 0 && a.arr[i] == b.arr[i])
        {
            i--;
        }
        if (i == -1)
        {
            ans.arr[0] = 0;
            ans.size = 1;
            return ans;
        }
        if (a.arr[i] < b.arr[i])
        {
            return subtract(b, a);
        }
    }
    int z = 0;
    int j = 0;
    for (int i = 0; i < b.size; i++)
    {
        if (a.arr[i] - b.arr[i] < 0)
        {
            a.arr[i + 1]--;
            a.arr[i] += 10;
        }
        ans.arr[z] = a.arr[i] - b.arr[i];
        if (ans.arr[z] != 0)
        {
            j = i;
        }
        z++;
    }

    for (int i = b.size; i < a.size; i++)
    {
        if (a.arr[i] != 0)
        {
            j = i;
        }
        if (a.arr[i] < 0)
        {
            a.arr[i + 1]--;
            a.arr[i] += 10;
        }
        ans.arr[z] = a.arr[i];
        z++;
    }
    ans.size = j + 1;
    return ans;
}
int compare(BigInt a, BigInt b)
{
    if (a.size < b.size)
    {
        return -1;
    }

    else if (a.size == b.size)
    {
        int i = a.size - 1;
        while (i >= 0 && a.arr[i] == b.arr[i])
        {
            i--;
        }
        if (i == -1)
        {
            return 0;
        }
        if (a.arr[i] < b.arr[i])
        {
            return -1;
        }
    }

    return 1;
}
BigInt add(BigInt a, BigInt b)
{
    int s1 = 0, s2 = 0;
    BigInt ans;
    if (a.sign == -1)
    {
        a.sign = 1;
        s1 = 1;
    }
    if (b.sign == -1)
    {
        b.sign = 1;
        s2 = 1;
    }
    if (s1 && s2)
    {
        ans = add(a, b);
        ans.sign = -1;
        return ans;
    }
    else if (s1)
    {
        ans = subtract(a, b);
        if (compare(a, b) > 0)
        {
            ans.sign = -1;
        }
        return ans;
    }
    else if (s2)
    {
        ans = subtract(a, b);
        if (compare(a, b) < 0)
        {
            ans.sign = -1;
        }
        return ans;
    }
    if (a.size < b.size)
    {
        return add(b, a);
    }
    int z = 0;
    int c = 0;
    for (int i = 0; i < b.size; i++)
    {
        int temp = a.arr[i] + b.arr[i] + c;
        ans.arr[z] = temp % 10;
        c = temp / 10;
        z++;
    }
    for (int i = b.size; i < a.size; i++)
    {
        int temp = a.arr[i] + c;
        ans.arr[z] = temp % 10;
        c = temp / 10;
        z++;
    }
    if (c > 0)
    {
        ans.arr[z] = c;
        z++;
    }
    ans.size = z;
    return ans;
}

BigInt multiply(BigInt a, BigInt b)
{
    BigInt ans;
    ans.size = 0;
    for (int i = 0; i < a.size; i++)
    {
        int c = 0;
        BigInt t;
        int z = 0;
        for (int j = 0; j < b.size; j++)
        {
            int temp = a.arr[i] * b.arr[j] + c;
            t.arr[z] = temp % 10;
            c = temp / 10;
            z++;
        }
        if (c > 0)
        {
            t.arr[z] = c;
            z++;
        }
        t.size = z;
        BigInt pro1;
        int ind = 0;
        for (int p = 0; p < i; p++)
        {
            pro1.arr[ind] = 0;
            ind++;
        }
        for (int p = 0; p < t.size; p++)
        {
            pro1.arr[ind] = t.arr[p];
            ind++;
        }
        pro1.size = ind;
        ans = add(ans, pro1);
    }
    return ans;
}

BigInt moduloFunc(BigInt a, BigInt b)
{
    int s1 = 0, s2 = 0;
    if (a.sign == -1)
    {
        s1 = 1;
        a.sign = 1;
    }
    if (b.sign == -1)
    {
        s2 = 1;
        b.sign = 1;
    }
    while (a.size >= b.size)
    {
        if (a.size == b.size)
        {
            int i = a.size - 1;
            while (i >= 0 && a.arr[i] == b.arr[i])
            {
                i--;
            }
            if (i == -1)
            {
                a.arr[0] = 0;
                a.size = 1;
                break;
            }
            if (a.arr[i] < b.arr[i])
            {
                break;
            }
        }
        a = subtract(a, b);
    }
    if (s1 == 1 && s2 == 1)
    {
        a.sign = -1;
    }
    else if (s1 == 1)
    {
        a = subtract(b, a);
    }
    else if (s2 == 1)
    {
        a = subtract(b, a);
        a.sign = -1;
    }
    return a;
}
BigInt fact(BigInt a)
{
    BigInt ans;
    ans.arr[0] = 1;
    ans.size = 1;
    while (a.size != 1 || a.arr[0] != 0)
    {
        ans = multiply(ans, a);
        BigInt b;
        b.arr[0] = 1;
        b.size = 1;
        a = subtract(a, b);
    }
    return ans;
}
BigInt power(BigInt a, BigInt b)
{
    BigInt one;
    one.arr[0] = 1;
    one.size = 1;
    int check = 0;
    if (a.sign == -1)
    {
        check = 1;
        a.sign = 1;
    }
    int odd = 0;
    if (b.arr[0] % 2 == 1)
    {
        odd++;
    }
    if (b.size == 1 && b.arr[0] == 0)
    {
        return one;
    }
    BigInt temp = a;
    while (b.size != 1 || b.arr[0] != 1)
    {
        temp = multiply(temp, a);
        b = subtract(b, one);
    }
    if (check && odd)
    {
        temp.sign = -1;
    }
    return temp;
}
BigInt convert(int a)
{
    BigInt ans;
    int z = 0;
    if (a < 0)
    {
        ans.sign = -1;
        a *= -1;
    }
    while (a != 0)
    {
        ans.arr[z] = a % 10;
        a /= 10;
        z++;
    }
    ans.size = z;
    return ans;
}

BigInt squareRoot(BigInt a)
{
    BigInt ans = convert(1);
    int diff = a.size / 2 - ans.size;
    BigInt k1;
    k1.size = 0;

    for (int z = 0; z <= diff; z++)
    {
        k1.arr[z] = 0;
        k1.size++;
    }
    for (int z = 0; z < ans.size; z++)
    {
        k1.arr[k1.size] = ans.arr[z];
        k1.size++;
    }
    ans = k1;
    BigInt result = multiply(ans, ans);
    if (compare(result, a) == 0)
    {
        return ans;
    }
    while (compare(result, a) < 0)
    {
        ans = add(ans, convert(1000000));
        result = multiply(ans, ans);
    }
    while (compare(result, a) > 0)
    {
        ans = subtract(ans, convert(100000));
        result = multiply(ans, ans);
    }

    while (compare(result, a) < 0)
    {
        ans = add(ans, convert(10000));
        result = multiply(ans, ans);
    }
    while (compare(result, a) > 0)
    {
        ans = subtract(ans, convert(1000));
        result = multiply(ans, ans);
    }

    while (compare(result, a) < 0)
    {
        ans = add(ans, convert(100));
        result = multiply(ans, ans);
    }
    while (compare(result, a) > 0)
    {
        ans = subtract(ans, convert(10));
        result = multiply(ans, ans);
    }
    while (compare(result, a) < 0)
    {
        ans = add(ans, convert(1));
        result = multiply(ans, ans);
    }
    return ans;
}

int main()
{
    int a = 0;
    BigInt x;
    BigInt y;
    int x_int;
    do
    {
        printf("Enter 1 for modulo of two bigintegers :\n");
        printf("Enter 2 for square squareRoot of a big int :\n");
        printf("Enter 3 to raise a bigint to power (only positive powers) :\n");
        printf("Enter 4 to convert a int to bigint :\n");
        printf("Enter 5 to calculate factorial :\n");
        printf("Enter 6 to add two bigintegers :\n");
        printf("Enter 7 to subtract two bigintegers :\n");
        printf("Enter 0 to end the program :\n");
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            x = input();
            y = input();

            printf("ans = ");
            printBigInt(moduloFunc(x, y));
            break;

        case 2:
            x = input();
            printf("ans = ");
            printBigInt(squareRoot(x));
            break;
        case 3:
            x = input();
            y = input();
            printf("ans = ");
            printBigInt(power(x, y));
            break;
        case 4:
            scanf("%d", &x_int);
            printBigInt(convert(x_int));
            break;
        case 5:
            x = input();
            printf("ans = ");
            printBigInt(fact(x));
            break;
        case 6:
            x = input();
            y = input();
            printf("ans = ");
            printBigInt(add(x, y));
            break;
        case 7:
            x = input();
            y = input();
            printf("ans = ");
            printBigInt(subtract(x, y));
            break;
        }

        printf("\n");
    } while (a != 0);

    return 0;
}

//  3 % 7 = 3
// -3 % 7 = 4
// -3 % -7 = -3
//  3 % -7 = -4