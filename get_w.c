#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){

	int npunts;

	double t = 0, pas, v, dw, w0, w1, winf, tan2, cos2, phi = 0.066667, v3=12, v4 = 17.4;

	FILE *est_v = fopen("volt_spline.dat","r");
	FILE *est_w = fopen("v_w_spl.dat","w");

	printf("Introdueix quants punts intermitjos vols entre Tk i Tk+delta\n");
        scanf("%d", &npunts);

	pas = 1.0/npunts;

	w0 = 0.1;

	while(fscanf(est_v,"%le", &v) != EOF){
		
		fprintf(est_w,"%le %.20le %.20le\n",t, v, w0);

		tan2 = tanh((v-v3)/v4);
		cos2 = cosh((v-v3)/(2*v4));
		winf = 0.5*(1+tan2);

		dw = phi*(winf-w0)*cos2;

		w1 = w0 + pas*dw;

		w0 = w1;
		t = t + pas;
	}

	fclose(est_v);
	fclose(est_w);

	return 0;
}
