#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "../include/linearInterpolate.hpp"
#include "../include/util.hpp"

LinearInterpolate::LinearInterpolate(vector<double> xData, vector<double> yData)
{
	int i = 0;

	// Do some basic sanity checking, the size of the input vectors is assumed to correspond to the number of knot points

	if(xData.size() != yData.size())
	{
		std::string err{"Vectors correspondong to knot points and values at each knot point are not equal in size. Please ensure that each knot point has a corresponding y value."};
		throw std::invalid_argument(err);
	}


	// Initialize the list of knot points with the given input vectors
	for (i = 0; i < xData.size(); i++)
	{
		knotPoints.push_back(std::make_pair(xData[i], yData[i]));
	}

	// Sort the knotPoints such that xp[i] <= xp[i+1], no need to reinvent the wheel so using the standard sort function here

        if(knotPoints.size() != 0)
        {

                std::sort(knotPoints.begin(), knotPoints.end());

                // Store the lower bound and upper bound of knot points so that extrapolation outside the range of knots can be done easily

                lowerBoundKnotPoint = knotPoints.front().first;
                upperBoundKnotPoint = knotPoints.back().first;
        }
	
	/*
	 * Ensure that we don't have divide by 0 problems during interpolation when two knot points are extremely close to each other in value
	 * Exactly how close points are allowed to be is somewhat arbitrarily defined by the constant EPSILON
        */
 
	if (knotPoints.size() > 1) // Condition has the potential to occur only if we have more than one knot point
	{
		for(std::size_t i=1; i<knotPoints.size(); ++i) 
		{
			double delta = std::abs(knotPoints[i].first - knotPoints[i-1].first);
			if(delta < EPSILON )
			{ 
				std::string err{"Potential Divide By Zero: The difference in value between the points " + std::to_string(i-1) + " and " + std::to_string(i)  + " is less than the pre-defined treshold value " + std::to_string(EPSILON)  + ". Please sanitize the input and try again."};
				throw std::range_error(err);
			}

		}
	}

}

double LinearInterpolate::extrapolateOutOfBounds(double interpolationPoint, extrapolationState extrapolationStateFlag) 
{

	if(extrapolationStateFlag == lessThanLower)
        {
		return knotPoints.front().second;
	}
	else if(extrapolationStateFlag == greaterThanUpper)
	{
		return knotPoints.back().second; 
	}
}   

/*
 * If we want the algorithm to be more time-efficient and care less about space,
 * one approach would be to store the dy/dx value for each interval between knot points while initializing the knotPoint data structure
 * If however, we want to be more space-efficient, we will compute these values lazily at runtime
 * The assumption here is that we want to more space-efficient, while maintaining acceptable time-complexity
 * Hence, we compute these values lazily at run-time 
*/

double LinearInterpolate::interpolate(double interpolationPoint)
{

	// Handle awkward cases of knot point vector containing 0/1 elements

	if(knotPoints.size() == 0)
        {
                std::string err{"Knot point vector had size 0, cannot interpolate"};
                throw std::logic_error(err);
        }

        else if(knotPoints.size() == 1)
        {
                return knotPoints.front().second;
        }

	// Check if the value is out of bounds and to the left of the leftmost knot point (lowest value) 
	
	else if(interpolationPoint < lowerBoundKnotPoint)
	{
	 	extrapolationState extrapolationStateFlag = lessThanLower;	
		return extrapolateOutOfBounds(interpolationPoint, extrapolationStateFlag);
	}

	// Check if the value is out of bounds and to the right of the rightmost knot point (highest value)

	else if(interpolationPoint > upperBoundKnotPoint)
	{
		extrapolationState extrapolationStateFlag = greaterThanUpper;
		return extrapolateOutOfBounds(interpolationPoint, extrapolationStateFlag);
	}

	// In the case below, we are dealing with the normal case of interpolating within bounds 
		
	else 
	{
		
	// First need to determine the right interval to compute the interpolated value

	/*
	 * Find the knot point whose value is >= interPolationPoint
 	* std::lower_bound most likely uses binary search internally
 	* The time complexity is log2(last - first) + O(1) comparisons)
 	* Here, (last - first) corresponds to the number of knot points 
 	* Reference: https://en.cppreference.com/w/cpp/algorithm/lower_bound
	*/ 

	auto iter = std::lower_bound(knotPoints.cbegin(), knotPoints.cend(), interpolationPoint,
			        [](const std::pair<double, double>& knotPoint, double interpolationPoint) 
				{return knotPoint.first < interpolationPoint;}
          			);

	/*
	 * Determine the knot points and their respective values corresponding to the selected interval
         * x1 corresponds to a knot point that is just lower in value than the interpolation point
         * x2 corresponds to the knot point that is just greater in value than the interpolation point
	 * y1 corresponds to the value of the knot point x1
	 * y2 corresponds to the value of the knot point x2
	 * Here, dy/dx corresponds to the slope of the linear spline between x1 and x2
	*/

	double x2 = iter->first;
	double y2 = iter->second;
	double x1 = (iter - 1)->first;
	double y1 = (iter - 1)->second;

	// Handle de-generate case of x1 = x2 (occurs when we are dealing with the knot point that has the lowest value, i.e. the left boundary)

	if(x1 == x2)
	{
		return y2;
	}

	double dy = y2 - y1; 
	double dx = x2 - x1;

	return y1 + ((interpolationPoint - x1)/ dx) * dy;

	}

}

