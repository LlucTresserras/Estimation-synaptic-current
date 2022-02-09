# Estimation-synaptic-current
Estimation of the synaptic currrent from a register of the membrane potential.

This code uses as input an experimental regiser of the membrane potential of a neuron (volt_20.dat: a file with 20 values of voltage at each millisecond). With the use of a cúbic spline we finally obtain 500 values of voltage each millisecond (spline_cubic.c using functions from gauss_Piv.c and solTriangSup.c). 

This is important to get a good approximation of the first derivative of the membrane potential from the register of membrane potential using a differentiator (get_derivative.c), and also a good aproximation of the gatting variable w (get_w.c).

Finally, assuming that the registred membrane potential follows the Morris-Lecar equations, from the known data of w, the membrane potential and the first derivative of the membrane potential, we are able to estimate the synaptic current of the neuron (get_Isyn.c). 
