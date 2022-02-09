#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fsmd_vf_30(double *, double *, double);
int main(void){

	FILE *volt = fopen("volt_spline.dat", "r");
	FILE *vf = fopen("est_vf.dat","w");

	int i, npunts;
	double v1, t = 0, pas, *vect, *dx;
	
	vect = (double *)calloc(4,sizeof(double));
	dx = (double *)calloc(4,sizeof(double));
	if(vect == NULL || dx == NULL){
		printf("Error en la memòria\n");
	}
	printf("Introdueix quants punts intermitjos vols entre Tk i Tk+delta\n");
	scanf("%d", &npunts);
	
	pas = 1.0/npunts;

	fscanf(volt, "%le", &v1);
	
	/*INITIAL CONDITIONS fsmd_30*/
	vect[0] = v1;
	vect[1] = 0;
	vect[2] = 0;
	vect[3] = 0;
	
        fprintf(vf, "%.20le\n", vect[1]);
	do{
		fsmd_vf_30(vect, dx, v1);
	
                /*Euler_integration*/
                for(i = 0; i< 4; i++){
                        vect[i] = vect[i] + pas*dx[i];
                }
		t = t + pas;
		fprintf(vf, "%.20le\n", vect[1]);
           		
	}while(fscanf(volt, "%le", &v1) != EOF);
	
	fclose(volt);
	fclose(vf);
	free(vect);
	free(dx);

	return 0;
}

void fsmd_vf_30(double *x, double *dx, double f){

	double ls0=1.1, ls1 = 3.06, ls2 = 4.16, ls3 = 3, L = 10, w1, xsign;

	w1 = x[0] - f;
	if(w1 > 0){
                xsign = 1;
        }
        if(w1 < 0){
                xsign = -1;
        }
        if(w1 == 0){
                xsign = 0;
        }
		
	dx[0] = -ls3*pow(L, 1/4.)*pow(fabs(w1), 3/4.)*xsign + x[1];
	dx[1] = -ls2*pow(L, 2/4.)*pow(fabs(w1), 2/4.)*xsign + x[2];
	dx[2] = -ls1*pow(L, 3/4.)*pow(fabs(w1), 1/4.)*xsign + x[3]; 
	dx[3] = -ls0*L*xsign;

}
