# Cerebellar-Motor-Articulation-Controller-CMAC-

This set includes codes for Continuous CMAC and Discrete CMAC. The results are published for two kinds of expected outputs:
1) Y = X (Equation of a line)
2) Y = sin( 2*pi*X/100) (For a sine function)

We took a sample 100 Points and used 50 samples for training set and 50 samples for testing set. The error metric is the norm2(error data) as compared to the increasing size of the generalization window.

We also checked the number of iterations requred to converge as compared to the increasing size of the generalization window.
