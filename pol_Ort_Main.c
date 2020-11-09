#include<stdio.h>
#include<stdlib.h>
double horner (int, double*, double);
double *der_pol(int, double*);
void recurrencia(int, double*);
int newPol(int, double*, double, int, double, double*);
int calZeros(int, double*, int, double, double*, double*);


int main(void){
	int n, j, i, itMax;
	char nom[30];
	double tol;
	double *tk, *zeros;
	FILE *fitxer;
	/*FITXER D'ENTRADA*/
	printf("Doni el nom del fitxer d'entrada.\n");
	scanf ("%s", nom);
	fitxer=fopen(nom, "r");
	if(fitxer==NULL){
		printf("Error en el fitxer.\n");
		exit(1);
	}
	fscanf(fitxer, "%d %d %le", &n, &itMax, &tol);
	fclose(fitxer);
	/*RESERVEM MEMORIA PELS PUNTERS*/
	tk=(double*)malloc(((n+1)*(n+2)/2)*sizeof(double));
	if(tk==NULL){
		printf("Error de memoria.\n");
		exit(1);
	}
	zeros=(double*)malloc((n*(n+1)/2)*sizeof(double));
	if(zeros==NULL){
		printf("Error de memoria.\n");
		exit(1);
	}
	/*FITXER DE SORTIDA*/
	printf("Doni el nom del fitxer de sortida.\n");
	scanf("%s", nom);
	fitxer=fopen(nom, "w");
	/*ESCRIVIM EL PROBLEMA*/
	recurrencia(n, tk);
	zeros[0]=0;
	for(i=2; i<=n; i++)
		if(calZeros(i,tk+(i*(i+1)/2),itMax,tol,zeros+((i-2)*(i-1)/2),zeros+(i-1)*i/2)==-1)
			exit(-1);
	for(i=0; i<=n; i++){
		fprintf(fitxer,"Polinomi de grau %d\n", i);	
		for(j=i*(i+1)/2; j<(i+1)*(i+2)/2; j++)
			fprintf(fitxer,"T%d[%d] %le.\n",i, j-i*(i+1)/2, tk[j]);
		fprintf(fitxer,"\n");
		for(j=(i-1)*i/2; j<i*(i+1)/2; j++)
			fprintf(fitxer,"TZ%d[%d] %le.\n",i, j-i*(i-1)/2+1, zeros[j]);
		fprintf(fitxer,"\n===================\n");
	}
	return 0;
} 

