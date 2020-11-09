#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double horner(int, double*, double);
double *der_pol(int, double*);

/*FUNCIO RECURRENCIA*/

void recurrencia(int k, double *tk){
	int sum=0;
	double ultim[k-1], penultim[k-1];
	int p,i,j;
	tk[0]=1;	tk[1]=0;	tk[2]=1;
	penultim[0]=1;	ultim[0]=0;	ultim[1]=1;
	for(i=3; i>1; i--)
		sum+=i;
	for(p=2; p<=k; p++,sum+=p+1){
		tk[sum]=2*ultim[p-1];
		tk[sum-1]=0;
		for(i=p-3, j=sum-2; i>0; i-=2, j-=2){
			tk[j]=2*ultim[i]-penultim[i+1];
			tk[j-1]=0;
		}
		if(p%2!=0){
			tk[j]=2*ultim[i]-penultim[i+1];
			tk[j-1]=0;
		}else{
			tk[j]=-penultim[0];
		}			
	/*Actualitzem ultim i penultim*/
		for(i=0; i<p; i++)
			penultim[i]=ultim[i];
		for(i=0, j=sum-p; j<=sum; i++, j++)
			ultim[i]=tk[j];
	}
	return;
}

/*FUNCIO NEWPOL*/
int newPol(int k, double *c, double x0, int itMax, double tol, double *zeros){
	int i=0;
	double xn, dif;
	/*Fem Newton*/
	do{
		xn=x0-(horner(k,c,x0)/horner(k-1,der_pol(k,c), x0));
		dif=fabs(xn-x0);
		x0=xn;
		i++;
	}while(dif>tol && i<=itMax && fabs(horner(k-1, der_pol(k,c), xn))>tol);
	*zeros=xn;
	if(i>itMax || fabs(horner(k-1,der_pol(k,c), x0))<=0)
		return -1;
	return 1;
	
}
/*FUNCIO CALZEROS*/
int calZeros(int k, double *c, int itMax, double tol, double *arr_ant, double *zeros){
	int i;
	double puntmig;
	puntmig=(-1+arr_ant[0])/2;
	if(newPol(k,c,puntmig,itMax,tol,zeros)==-1)
		return -1;
	for(i=1;i<k-1;i++){
		puntmig=(arr_ant[i-1]+arr_ant[i])/2;
		if(newPol(k,c,puntmig,itMax,tol,zeros+i)==-1)
			return -1;
 	}
	puntmig=(arr_ant[k-2]+1)/2;
	if(newPol(k,c,puntmig,itMax,tol,zeros+k-1)==-1)
		return -1;
	return 1;
}			
