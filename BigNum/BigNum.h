#ifndef _BIGNUM_H
#define _BIGNUM_H

#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define MAXN 9999
#define MAXSIZE 10
#define DLEN 4

class BigNum
{
private:
    int a[500];
    int len;
public:
    BigNum()
    {
        len=1;
        memset(a,0,sizeof(a));
    }
    BigNum(const int);
    BigNum(const char *);
    BigNum(const BigNum &);
    BigNum& operator = (const BigNum &);

    friend istream&operator >> (istream&, BigNum&);
    friend ostream&operator << (ostream&, BigNum&);

    BigNum operator + (const BigNum &) const;
    BigNum operator - (const BigNum &) const;
    BigNum operator * (const BigNum &) const;
    BigNum operator / (const int &) const;
    BigNum operator ^ (const int &) const;
    int operator % (const int &) const;
    bool operator > (const BigNum &T) const;
    bool operator > (const int &t) const;

    void print();   //输出大数
};

BigNum::BigNum(const int b)
{
    int c,d = b;
    len=0;
    memset(a, 0, sizeof(a));
    while (d > MAXN)
    {
        c = d - (d / (MAXN+1)) * (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}

BigNum::BigNum(const char *s)
{
    int t,k,index,l;
    memset(a,0,sizeof(a));
    l = strlen(s);
    len = l / DLEN;
    if (l % DLEN)
        len++;

    index=0;
    for (int i=l-1; i >= 0; i -= DLEN)
    {
        t=0;
        k = i-DLEN+1;
        if (k < 0)
            k=0;
        for (int j=k; j <= i; j++)
        {
            t = t * 10 + (s[j] - '0');
        }
        a[index++] = t;
    }
}

BigNum::BigNum(const BigNum &T)
    : len(T.len)
{
    memset(a,0,sizeof(a));
    for (int i=0; i < len; i++)
    {
        a[i] = T.a[i];
    }
}

BigNum& BigNum::operator = (const BigNum &n)
{
    len = n.len;
    memset(a,0,sizeof(a));
    for (int i=0; i < len; i++)
        a[i] = n.a[i];
    return *this;
}

istream& operator >> (istream& in, BigNum& b)
{
    char ch[MAXSIZE * 4];
    int i = -1;
    in >> ch;
    int l = strlen(ch);
    int count=0, sum=0;
    for (i = l-1; i >= 0;)
    {
        sum = 0;
        int t = 1;
        for (int j=0; j < 4 && i >= 0; j++,i--,t *= 10)
        {
            sum += (ch[i] - '0') * t;
        }
        b.a[count] = sum;
        count++;
    }
    b.len = count++;
    return in;
}

ostream& operator << (ostream& out, BigNum& b)
{
    cout << b.a[b.len - 1];
    for (int i = b.len - 2; i >= 0; i--)
    {
        cout.widen(DLEN);
        cout.fill('0');
        cout << b.a[i];
    }
    return out;
}

BigNum BigNum::operator + (const BigNum &T) const
{
    BigNum t(*this);
    int big;  //位数
    big = T.len > len ? T.len : len;
    for (int i = 0; i < big; i++)
    {
        t.a[i] += T.a[i];
        if (t.a[i] > MAXN)
        {
            t.a[i + 1]++;
            t.a[i] -= MAXN + 1;
        }
    }
    if (t.a[big] != 0)
        t.len = big + 1;
    else
        t.len = big;
    return t;
}

BigNum BigNum::operator - (const BigNum &T) const
{
    int big;    //位数
    int flag;   //标记结果正负号
    BigNum t1, t2;
    if (*this > T)
    {
        t1 = *this;
        t2 = T;
        flag = 0;
    }
    else
    {
        t1 = T;
        t2 = *this;
        flag = 1;
    }

    big = t1.len;
    for (int i=0; i < big; i++)
    {
        if (t1.a[i] < t2.a[i])
        {
            int j = i + 1;
            while (t1.a[j] == 0)
                j++;
            t1.a[j--]--;

            while (j > i)
                t1.a[j--] += MAXN;
            t1.a[i] += MAXN + 1 - t2.a[i];
        }
        else
        {
            t1.a[i] -= t2.a[i];
        }
    }
    t1.len = big;
    while (t1.a[t1.len - 1] == 0 && t1.len > 1)
    {
        t1.len--;
        big--;
    }
    if (flag)
    {
        t1.a[big - 1] = 0-t1.a[big - 1];
    }

    return t1;
}
BigNum BigNum::operator * (const BigNum &T) const
{
    BigNum ret;
    int up;
    int temp1, temp2;
    int i,j;

    for (i = 0; i < len; i++)
    {
        up = 0;
        for (j = 0; j < T.len; j++)
        {
            temp1 = a[i] * T.a[j] + ret.a[i+j] + up;
            if (temp1 > MAXN)
            {
                temp2 = temp1 - temp1 / (MAXN + 1) * (MAXN + 1);
                up = temp1 / (MAXN + 1);
                ret.a[i + j] = temp1;
            }
            else
            {
                up = 0;
                ret.a[i + j] = temp1;
            }
        }
        if (up != 0)
        {
            ret.a[i + j] = up;
        }
    }
    ret.len = i + j;
    while (ret.a[ret.len - 1] == 0 && ret.len > 1)
        ret.len--;

    return ret;
}

BigNum BigNum::operator / (const int &b) const
{
    BigNum ret;
    int i, down=0;

    for (i = len - 1; i >= 0; i--)
    {
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b;
    }
    ret.len = len;
    while(ret.a[ret.len - 1] == 0 && ret.len > 1)
        ret.len--;

    return ret;
}

int BigNum::operator % (const int &b) const
{
    int i, d=0;
    for (i = len - 1; i >= 0; i--)
    {
        d = ((d * (MAXN+1)) % b + a[i]) % b;
    }
    return d;
}

BigNum BigNum::operator^(const int &n) const
{
    BigNum t, ret(1);
    int i;
    if (n < 0)
        exit(-1);
    if (n == 0)
        return 1;
    if (n == 1)
        return *this;

    int m = n;
    while (m > 1)
    {
        t = *this;
        for (int i = 1; (i << 1) < m; i <<= 1)
        {
            t = t * t;
        }
        m -= 1;
        ret = ret * t;
        if (m == 1)
            ret = ret * (*this);
    }
}

bool BigNum::operator>(const BigNum &T) const
{
    int ln;
    if (len > T.len)
        return true;
    else if (len == T.len)
    {
        ln = len - 1;
        while(a[ln] == T.a[ln] && ln >= 0)
            ln--;
        if (ln >= 0 && a[ln] > T.a[ln])
            return true;
        else
            return false;
    }
    else
        return false;
}

bool BigNum::operator>(const int &t) const
{
    BigNum b(t);
    return *this > b;
}

void BigNum::print()
{
    int i;
    cout << a[len - 1];
    for (i = len - 2; i >= 0; i--)
    {
        cout.width(DLEN);
        cout.fill(0);
        cout << a[i];
    }
    cout << endl;
}

#endif