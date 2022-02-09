/*Estimació del senyal Isyn a partir de l'estimació del camp vectorial feta anteriorment, juntament amb la trajectoria enregistrada V i w*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
		
int main(void){
		
	double t, Iapp = 39, v, w, dvest, C=20, GL = 2, GCA = 4, GK = 8, minf, Isyn;
	double Vl = -60, Vca= 120, Vk = -84;
	double tan1,v1 = -1.2, v2 = 18;
		
	FILE *volt = fopen("v_w_spl.dat", "r");
	FILE *vf = fopen("est_vf.dat", "r");
	FILE *estIsyn = fopen("Isyn.dat", "w");
		
	while(fscanf(volt, "%le", &t) != EOF){
		/*printf("t = %le\n", t);*/	
		fscanf(volt, "%le", &v);
		fscanf(volt, "%le", &w);
		fscanf(vf, "%le", &dvest);
		
		tan1 = tanh((v-v1)/v2);
              	minf = 0.5*(1+tan1);
       			
		Isyn = C*dvest - Iapp - GL*(Vl - v) - GCA*minf*(Vca - v) - GK*w*(Vk - v);
		
		fprintf(estIsyn, "%le %.20le\n", t, Isyn);
	} 		
	fclose(volt);
	fclose(vf);
	fclose(estIsyn);

	return 0;
}		
