# Bluware-HW
Linear Spline Interpolator

Simple code to evaluate linear splines. Constant extrapolation is used outside bounds.<br />

To compile, simply clone the repository and run the makefile in the folder src. <br />

<br /> git clone -n https://github.com/AbhirajBishnoi/Bluware-HW.git <br />
cd src <br />
make <br />

The code runs a bunch of tests from the test driver in test.cpp. To change what is fed as input to the spline interpolator,
please change fill in two vectors corresponding to the knot points, and the value of the function at each knot point. <br />

As an example, <br />

vector<double> xData = {5, 10, 25, 15, 0}; <br />
vector<double> yData = {1, 2, 3, 4, 5};

This means that the value of the function at the knot point xp = 0 is 5, the value at knot point xp = 5 is 1 and so on. <br />
Note that the knot points have to be monotonically increasing to compute the interpolation, but this is hidden from the user. <br />
The data fed to the constructor need not be sorted, this is performed within the constructor. <br />

<br /> Then initialize a new object of the linearInterpolate class as follows <br />

linearInterpolate obj = linearInterpolate(xData, yData); <br />

to evaluate the spline at a specific point, simply call the interpolate function on the created object with the interpolation point as input. <br />

<br /> float interpolationPoint = 5; <br />
obj.interpolate(5); <br />
