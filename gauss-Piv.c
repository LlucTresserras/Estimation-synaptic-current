/*Lluc Tresserras Pujadas 43639312D*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gaussPivot(double **, int);
int pivot(double **, int, int);
	
int gaussPivot(double **mat, int n){

	int i, j, r, z;
	double *aux, mult;

	aux = (double *)calloc(n+1,sizeof(double));
	if(aux == NULL){
		printf("Error en la memòria dinàmica.\n");
		exit(2);
	}
	
	for(i=0; i<n-1; i++){
		r = pivot(mat,n,i);
		
		if(r!=i){
			aux = mat[i];
			mat[i] = mat[r];
			mat[r] = aux;
		}
				
		if(fabs(mat[i][i]) < 1e-8){
			return 0;
		}		
		
		for(j=i+1; j<n; j++){
			mult = mat[j][i]/mat[i][i];
			for(z=i; z<n+1; z++){
				mat[j][z] = mat[j][z] - mult*mat[i][z];
			}
		}
		 
		
   		
	}
	if(fabs(mat[n-1][n-1])<10e-20){
			return 0;
	}
	return 1;
}
int pivot(double **mat, int n, int k){

	double max = fabs(mat[k][k]);
	int i, r = k;
	
	for(i=k+1; i<n; i++){
		if(fabs(mat[i][k])>max){
		max = fabs(mat[i][k]);
		r = i;
		}
	}

	return r;
}	
