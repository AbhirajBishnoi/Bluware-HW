#ifndef Util_hpp
#define Util_hpp

// This file is for constants and utility functions used project wide

const double EPSILON{1.0E-8};

typedef enum extrapolationState
{
        lessThanLower = 1,
        greaterThanUpper = 2
}extrapolationState;

#define expect_true(arg) \
        do { \
            if(!(arg)) { \
                std::cout << "Unexpected false at " \
                          << __FILE__ << ", " << __LINE__ << ", " << __func__ << ": " \
                          << #arg \
                          << std::endl; } \
        } while(false);

#endif
