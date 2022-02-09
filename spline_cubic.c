#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss-Piv.h"
#include "solTriangSup.h"

int main(void){
	
	FILE *volt = fopen("volt_20.dat", "r");
	FILE *volt_spl = fopen("volt_spline.dat","w");
	
	int N, npunts = 20, i, j, k, solucio, npunts_spline = 25;
 	double h, Tmax  = 250, h_spline, v0, v1, v2, a, b, c, d, y_spl, x_spl, aux_x, aux_y;

	double **m, *x, *y, *n;
	
	/*Increment original*/
        h = 1.0/npunts;
	
	N = npunts + 1;

	/*Increment spline cúbic*/
	h_spline = h/npunts_spline;

	m = (double **)calloc(N, sizeof(double *));
	x = (double *)calloc(N, sizeof(double));
	y = (double *)calloc(N, sizeof(double));
	n = (double *)calloc(N, sizeof(double));
	if(m == NULL || x == NULL || y == NULL || n == NULL){
		printf("Error en la memòria\n");	
		exit(1);
	}
	for(i=0; i<N; i++){
		m[i]=(double *)calloc(N+1,sizeof(double));
		if(m[i] == NULL){
			printf("Error en la memòria dinàmica.\n");
			exit(1);
		}
	}

	fscanf(volt, "%le", &x[0]);
	fscanf(volt, "%le", &y[0]);

	for(k=0;  k<Tmax; k++){	
		m[0][0] = 1;
		m[N-1][N-1] = 1;		
		v0 = y[0];
		fscanf(volt, "%le", &x[1]);
		fscanf(volt, "%le", &y[1]);
		v1 = y[1];

		for(i = 1; i < N-1; i++){
			
			fscanf(volt, "%le", &x[i+1]);
			fscanf(volt, "%le", &y[i+1]);
			v2 = y[i+1];
			
			for(j = 0; j < N+1; j++){
				if(j == i - 1){
					m[i][j] = h;
				}
				if(j == i){
					m[i][j] = 4*h;
				}
				if(j == i+1){
					m[i][j] = h;
				}
				if(j == N){
					m[i][j] = 6*(v2 - 2*v1 + v0)/h;
				}	
			}
			v0 = v1;
			v1 = v2;
		}

		/*Passem a solucionar el sistema d'equacions*/
		solucio = gaussPivot(m,N);
        	if(solucio == 0){
        	        printf("The system can't be solved.\n");
        	        exit(1);
        	}
	
	        substitucio(m,N);
	        for(i=0; i<N; i++){
	                n[i] = m[i][N];
		}
	
		for(i = 0; i<N-1; i++){
			a = y[i];
			b = (y[i+1] - y[i])/h - h*n[i]/2 - (h/6)*(n[i+1] - n[i]);
			c = n[i]/2;
			d = (n[i+1] - n[i])/(6*h);
	
			x_spl = x[i];
	
			for(j=0; j<npunts_spline; j++){
				
				y_spl = a + b*(x_spl - x[i]) + c*(x_spl - x[i])*(x_spl - x[i]) + d*(x_spl - x[i])*(x_spl - x[i])*(x_spl - x[i]);
		
				fprintf(volt_spl, "%.20le\n", y_spl);		
				x_spl = x_spl + h_spline;
			}
		
		}
		aux_x = x[N-1];
		aux_y = y[N-1];
		for(i = 0; i<N; i++){
			x[i] = 0;
			y[i] = 0;
			for(j = 0; j<N+1; j++){	
				m[i][j] = 0;
			}
		}

		x[0] = aux_x;
		y[0] = aux_y;
	}


      	return 0;
}	
