#include<stdio.h>
#include<stdlib.h>
/*FUNCIO HORNER*/

double horner(int n, double *p, double z){
	int i;
	double res;
	res=p[n]*z;
	for(i=n; i>1; i--){
		res=(res + p[i-1]) * z;
	}
	res=res+p[0];
	return res;
}

/*FUNCIO *DER_POL*/

double *der_pol(int n, double *p){
	int i;
	double *sol;
	sol=(double*) malloc(n * sizeof(double));
	if(sol==NULL)
		exit (1);
	if(n==0){
		sol=0;
		return sol;
	}
	for(i=0; i<n; i++)
		sol[i]=p[i+1]*(i+1);
	return sol;
}
