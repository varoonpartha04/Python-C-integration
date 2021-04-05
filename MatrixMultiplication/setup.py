from setuptools import setup, Extension

# Compile *matrixMultiplicaton.cpp* into a shared library
setup(
    #...
    ext_modules=[Extension('matrixMultiplication', ['matrixMultiplication.cpp'],),],
)
