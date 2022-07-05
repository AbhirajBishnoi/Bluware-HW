#ifndef linearInterpolator_hpp
#define linearInterpolator_hpp

#include <vector>
#include <algorithm>
#include "util.hpp"

using namespace std;


class LinearInterpolate
{

	// Declaring a vector of pairs to hold a list of (x,y) pairs corresponding to each knotPoint, and its respective y value
	vector<pair<double, double>> knotPoints;

	// Variable to store the lower bound of knot points during initialization to optimize performance of "out of range" extrapolation	 
 	double lowerBoundKnotPoint;

        // Variable to store upper bound of knot points  during initialization to optimize performance of "out of range" extrapolation

	double upperBoundKnotPoint;

	public:

	/*
	 * Constructor to initialize interpolation object
	 * Input args:
	 * xData: Vector of knot points (xp), such that xData[i] = xp[i] 
	 * yData: Vector of values, with each element of the vector corresponding to the value of the function at knot point "i" in xData
	 * 	such that yData[i] = f(xp[i]) = y[i]
	 * Size of the vectors implicitly defines the number of knot points
	*/
	
	LinearInterpolate(vector<double> xData, vector<double> yData);

	/*
	 * Function to compute extrapolation out of bounds, performs constant extrapolation
	 * Input args:
	 * interpolationPoint: point at which interpolation is to be performed
	 * extrapolationStateFlag: flag that specifies which bound is closer to the interpolationPoint, the lower bound or the upper bound  
	 * Output value: double value corrsponding to the extrapolated value at the given input point
	*/
	
	double extrapolateOutOfBounds(double interpolationPoint, extrapolationState extrapolationStateFlag);
       
	/*
	 * Function to compute interpolated value at a given point
	 * Input args: interpolationPoint(double): point at which interpolation is to be performed
	 * Output value: double value that corresponds to interpolated value at the given input point, using linear interpolation 
	*/

	double interpolate(double interpolationPoint);

};
	
#endif
