#include <bits/stdc++.h>
using namespace std;
int randInRange(int low, int high)
{
return rand()%(high-(low+1)) + (low+1) ;
}
int genPrime3mod4()
{
while(true)
{
int num = randInRange(10000,100000);
if(num%4 != 3) continue;
bool prime = true;
for(int i=2; i<=sqrt(num); i++)
{
if(num % i == 0)
{
prime = false;
break;
}
}
if(prime) return num;
}
}
int bbs(int p, int q)
{
long long n = (long long)p*q ;
long long s;
do{ s = rand(); } while(s%p==0 || s%q==0 || s==0);
int B = 0;
long long x = (s*s) % n;
for(int i=0; i<10; i++)
{
x = (x*x) % n;
B = B<<1 | (x & 1);
}
cout<<"Blum Blum Shub"<<endl<<"--------------"<<endl;
cout<<"p = "<< p <<"\nq = "<< q <<"\nn = "<< n <<"\ns = "<< s <<endl;
return B;
}
int powModN(int a, int b, int n)
{
int res=1;
for(int i=0; i<b; i++){
res = (res * a) % n;
}
return res;
}
string rabinMiller(int n)
{
int k = 0;
int q = n-1;
while(q % 2 == 0)
{
q = q/2 ;
k++ ;
}
int a = randInRange(1, n-1);
cout << "\nRabin Miller(" << n << ")\n-----------------" << endl;
cout << n-1 << " = 2^" << k << " * " << q << endl;
cout << "k = " << k << "\nq = " << q << "\na = " << a << endl;
if(powModN(a,q,n) == 1) return "inconclusive";
for(int j=0; j<k ; j++)
{
if(powModN(a, pow(2,j)*q, n) == n-1) return "inconclusive";
}
return "composite";
}
int main()
{
srand(time(NULL));
int p = genPrime3mod4();
int q = genPrime3mod4();
int randNum = bbs(p, q);
cout << "Random number generated by BBS = " << randNum << endl;
cout << rabinMiller(randNum) << endl ;
return 0;
}
