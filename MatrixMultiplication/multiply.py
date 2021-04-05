import ctypes
import numpy as np
import glob
import sys

'''
Reads the c++ library and returns the library to function
'''
def load_library():
    try:
        # find the shared library, the path depends on the platform and Python version
        libfile = glob.glob('build/*/matrixMultiplication*.so')[0]
        # open the shared library
        matrixLib = ctypes.CDLL(libfile)
        return matrixLib
    except IOError as e:
        print "I/O error({0}): {1}".format(e.errno, e.strerror)
    except RuntimeError as e:
        print "RuntimeError error({0}): {1}".format(e.errno, e.strerror)
    except:
        print "Unexpected error:", sys.exc_info()[0]

'''
Reads the c++ library and returns the library to function
params: Takes in numpy array types as inputs
output: Prints the value of matrix Multiplication
'''
def matrix_multiplication(array1,array2):
    try:
        matrixLib = load_library()
        (row1,col1) = array1.shape
        (row2,col2) = array2.shape
        # 2. tell Python the argument and result types of function
        matrixLib.matrixMultiplication.restype = np.ctypeslib.ndpointer(dtype=ctypes.c_int, shape=(row1*col2,))
        matrixLib.matrixMultiplication.argtypes = [np.ctypeslib.ndpointer(dtype=np.int32, shape=(row1*col1,)), np.ctypeslib.ndpointer(dtype=np.int32, shape=(row2*col2,)),
        ctypes.c_int,ctypes.c_int,ctypes.c_int]
        arr1 = array1.flatten()
        arr2 = array2.flatten()
        if(row2==col1):
            resultMatrix = matrixLib.matrixMultiplication(arr1,arr2,row1,col2,col1)
            print(resultMatrix)
        else:
            print("Matrix Multiplication condition not satisfied")
    except RuntimeError as e:
        print "RuntimeError error({0}): {1}".format(e.errno, e.strerror)
    except ValueError as e:
        print "ValueError error({0}): {1}".format(e.errno, e.strerror)
    except:
        print "Unexpected error during matrixMultiplication", sys.exc_info()[0]

'''
Before calling the function, pass in input parameters array1 and array2 as numpy array types
'''
if __name__ == "__main__":
    matrix_multiplication(n_array1,n_array2)
