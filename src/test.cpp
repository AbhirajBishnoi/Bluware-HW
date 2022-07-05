#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "../include/linearInterpolate.hpp"
#include "../include/util.hpp"


void test_program()
{


	// Regular interpolation with sorted data
	vector<double> xData = { 0, 5, 10, 15, 20, 25 };
	vector<double> yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5};

	LinearInterpolate interpObjSortedInput = LinearInterpolate(xData, yData);

	expect_true(std::abs(interpObjSortedInput.interpolate(1) - 0.2) < EPSILON);

	// Regular interpolation with unsorted data

        xData = { 0, 10, 5, 25, 20, 15 };
        yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5 };

        LinearInterpolate interpObjUnsortedInput = LinearInterpolate(xData, yData);

        expect_true(std::abs(interpObjUnsortedInput.interpolate(1) - 0.24) < EPSILON);

	// Interpolation at left boundary

	xData = { 0, 10, 5, 25, 20, 15 };
        yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5};

        LinearInterpolate interpObjLeftBoundary = LinearInterpolate(xData, yData);

        expect_true(std::abs(interpObjLeftBoundary.interpolate(0) - 0.1) < EPSILON);

	// Interpolation at right boundary

        xData = { 0, 10, 5, 25, 20, 15 };
        yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5};

        LinearInterpolate interpObjRightBoundary = LinearInterpolate(xData, yData);

        expect_true(std::abs(interpObjRightBoundary.interpolate(25) - 0.3) < EPSILON); 

	// Interpolation at boundary of two internal intervals (not lower, upper bound)

        xData = { 0, 10, 5, 25, 20, 15 };
        yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5};

        LinearInterpolate interpObjInternalIntervalBoundary = LinearInterpolate(xData, yData);

        expect_true(std::abs(interpObjInternalIntervalBoundary.interpolate(10) - 0.6) < EPSILON);

	// Interpolation with a single value present in vector inputs

        xData = { 0 };
        yData = { 0.1 };

        LinearInterpolate interpObjSingleInput = LinearInterpolate(xData, yData);

        expect_true(std::abs(interpObjSingleInput.interpolate(0) - 0.1) < EPSILON);
	
	// Interpolation with empty vector inputs

        xData = {};
        yData = {};

	LinearInterpolate interpObjEmptyInput = LinearInterpolate(xData, yData);

	bool exceptionCaught = false;
	try {
               interpObjEmptyInput.interpolate(0); 
        } catch (const std::logic_error& ex) {
        
	cout << "Illegal as expected for empty input" << endl;
        exceptionCaught = true;
	}
        expect_true(exceptionCaught)
        
	// Interpolation for out of bounds value (greater than upper bound)

	xData = { 0, 10, 5, 25, 20, 15 };
        yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5};

        LinearInterpolate interpObjOutOfBoundsRight = LinearInterpolate(xData, yData);

	expect_true(std::abs(interpObjInternalIntervalBoundary.interpolate(35) - 0.3) < EPSILON);

        // Interpolation for out of bounds value (lesser than lower bound)

        xData = { 0, 10, 5, 25, 20, 15 };
        yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5};

        LinearInterpolate interpObjOutOfBoundsLeft = LinearInterpolate(xData, yData);

        expect_true(std::abs(interpObjOutOfBoundsLeft.interpolate(-5) - 0.1) < EPSILON);
	
        // Interpolation with two x values being the same (divide by 0)

	xData = { 0, 10, 5, 15, 20, 15 };
        yData = { 0.1, 0.6, 0.8, 0.3, 0.5, 1.5};

        LinearInterpolate interpObjDivideByZero = LinearInterpolate(xData, yData);

        exceptionCaught = false;
        try {
               interpObjDivideByZero.interpolate(15);
        } catch (const std::range_error& ex) {
        cout << "Illegal as expected for divide by 0" << endl;
        exceptionCaught = true;
        }
        expect_true(exceptionCaught)

	cout << "ALL TESTS PASSED";
 
}


int main(int, char*[])
{

	test_program();
	return 0;
}

