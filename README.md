# Bluware-HW
Linear Spline Interpolator

Simple code to evaluate linear splines. Constant extrapolation is used outside bounds.

To compile, simply clone the repository and run the makefile in the folder src.

git clone -n https://github.com/AbhirajBishnoi/Bluware-HW.git
cd src
make

The code runs a bunch of tests from the test driver in test.cpp. To change what is fed as input to the spline interpolator,
please change fill in two vectors corresponding to the knot points, and the value of the function at each know point.

As an example,

vector<double> xData = {5, 10, 25, 15, 0};
vector<double> yData = {1, 2, 3, 4, 5};

This means that the value of the function at the knot point xp = 0 is 5, the value at knot point xp = 5 is 1 and so on.
Note that the knot points have to be monotonically increasing to compute the interpolation, but this is hidden from the user.
The data fed to the constructor need not be sorted, this is performed within the constructor.

Then initialize a new object of the linearInterpolate class as follows

linearInterpolate obj = linearInterpolate(xData, yData); 

to evaluate the spline at a specific point, simply call the interpolate function on the created object with the interpolation point as input.

float interpolationPoint = 5;
obj.interpolate(5);
