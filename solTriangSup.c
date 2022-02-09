/*Lluc Tresserras Pujadas 43639312D*/
#include <stdio.h>
#include <stdlib.h>

void substitucio(double **mat, int n){
	int i, j;
	double suma;

	mat[n-1][n] = mat[n-1][n]/mat[n-1][n-1];

	for(i=n-2; i>=0; i=i-1){
		suma = 0;
		for(j=0; j<n-1-i; j++){
			suma = suma + mat[i][n-1-j]*mat[n-1-j][n];
		}
		mat[i][n]= (mat[i][n] - suma)/mat[i][i];
	 }
	return;
}
