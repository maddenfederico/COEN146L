/*Name: Federico Madden
Date: 4/7/2020
Title: Lab1 - Steps 6 and 7
Description: This program computes various metrics 
related to circuit and packet switching scenarios
*/
#include <math.h> 
#include <stdio.h> 
#include <stdlib.h> 

long factorial(int n)
{
    if(n == 0){
        return 1;
    }
    else{
        return (long) n * factorial(n - 1);
    }
}

double binomial_dist(int x, int y)
{
    return (double) (factorial(x) / (factorial(y) * factorial(x - y)));
}



int main()
{
    int linkBandwidth = 200;
    int userBandwidth = 20;

    double tPSuser = 0.1;
    int nPSusers = 19;


    int nCSusers = linkBandwidth / userBandwidth;
    printf("nCSusers: %d\n", nCSusers);


    double pPSusers = tPSuser;
    printf("pPSusers: %lf\n", pPSusers);

    double pPSusersNotBusy = 1 - pPSusers;
    printf("pPSusersNotBusy: %lf\n", pPSusersNotBusy);

    double allOthers = pow(1 - pPSusers, nPSusers - 1);
    printf("p of all other users: %e\n", allOthers);

    double notActive = pPSusers * pow(pPSusersNotBusy, nPSusers - 1);
    printf("p that one specific user is active and remaining users are not: %e\n", notActive);

    double One = nPSusers * notActive;
    printf("p that exactly one user is busy: %e\n", One);

    double Ten = pow(pPSusers,10) * pow(pPSusersNotBusy, nPSusers - 10);
    printf("p that a certain 10 users are active: %e\n", Ten);

    double coef = binomial_dist(nPSusers, 10);
    double anyTen = coef * pow(pPSusers, 10) * pow(pPSusersNotBusy, nPSusers - 10);
    printf("p that any 10 users are active: %e\n", anyTen);

    double _sum = 0;

    for(int i = 11; i <= nPSusers; ++i){

        _sum += binomial_dist(nPSusers, i) * pow(pPSusers, i) * pow(pPSusersNotBusy, nPSusers - i);

    }
    printf("p that more than 10 users are active: %e\n", _sum);

  return 0;
}