import numpy as np
# defining fit function


def parabola(x, a1, b1, c1): 
    par1 = a1*x**2 + b1*x + c1

    return par1


def multi_gauss3(x,c0,c1,m1,s1,c2,m2,s2,c3,m3,s3):
    gauss_1=c1*np.exp(-np.power((x-m1),2.)/(2.*s1**2))
    gauss_2=c2*np.exp(-np.power((x-m2),2.)/(2.*s2**2))
    gauss_3=c3*np.exp(-np.power((x-m3),2.)/(2.*s3**2))
    
    return c0+gauss_1+gauss_2+gauss_3

def multi_gauss2(x,c0,c1,m1,s1,c2,m2,s2):
    gauss_1=c1*np.exp(-np.power((x-m1),2.)/(2.*s1**2))
    gauss_2=c2*np.exp(-np.power((x-m2),2.)/(2.*s2**2))
    
    return c0+gauss_1+gauss_2

def line(x, m, q):
    y = m * x + q

    return y