// CSC 325 - Fall 2014 - Homework 1

// This program partially implements the O(n lg n) solution to the
// maximum-subarray problem in section 4.1 of CLRS. This program only
// computes the maximum sum, not the location of the corresponding
// subarray. You must complete the maxCrossingSum function. The
// parameter 'high' is an inclusive upper bound as in the book.
// Vectors are origin zero instead of origin one.

// DO NOT CHANGE ANYTHING OTHER THAN maxCrossingSum!

// I will compile this with the command: g++ --std=c++11 -o h1 h1.cpp


#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

using sum_t = int64_t;


sum_t maxCrossingSum(const vector<int>& A, int low, int mid, int high) {
    /*// returns the largest sum that crosses the midpoint, i.e., the
    // largest sum of a contiguous subarray that includes at least one
    // element from A[low..mid] and at least one element from
    // A[mid+1..high]; thus both A[mid] and A[mid+1] must be included

    // this must run in O(n) time, where n = high - low + 1
    // see CLRS p.71

    // IMPLEMENT ME!

    return -123456789;          // this is wrong, obviously*/
	
	auto leftSum = -999999, rightSum = -999999;
	auto sum = 0;
	int maxLeft, maxRight;
	for(int i = mid; i > low; --i)
	{
		sum += A[i];
		if (sum > leftSum)
		{
			leftSum = sum; 
			maxLeft = i
		}
	}
	for (unsigned j = mid +1; j < high; ++j)
	{
		sum += A[j];
		if (sum > rightSum)
		{
			rightSum = sum;
			maxRight = j;
		}
	}
	return (maxLeft, maxRight, leftSum + rightSum)
}


sum_t maxSum(const vector<int>& A, int low, int high) {
    if (low > high) {
        return 0;
    } else if (low == high) {
        return A[low];
    } else {
        int mid = (low + high)/2;
        auto left = maxSum(A, low, mid);
        auto cross = maxCrossingSum(A, low, mid, high);
        auto right = maxSum(A, mid + 1, high);
        return max(left, max(cross, right));
    }
}


sum_t maxSum(const vector<int>& A) {
    return maxSum(A, 0, A.size() - 1);
}


int main() {
    // some small tests; the last is from CLRS p.70
    // the answers are -1 0 1 ... 14 43

    vector<vector<int>> tests {
        {-1}, {}, {1,-2}, {-1,2}, {1,2},
        {4,-5,-6}, {-4,5,-6}, {-4,-5,6}, {3,4,-5}, {-3,4,4}, {3,2,4},
        {7,3,-9,7}, {3,-4,6,5}, {-3,8,4,-4}, {5,4,4,-2}, {-6,3,7,4},
        {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7}
    };

    for (const auto& test : tests) {
        cout << maxSum(test) << endl;
    }

    vector<int> big_test(1000 * 1000);
    auto rng = minstd_rand(417);
    uniform_int_distribution<> next(-100, 100);

    // this will produce a "random" vector, but it will always produce
    // the *same* random vector because it always uses the same random
    // number generator (minstd_rand) and the same seed (417)

    for (auto& x : big_test) {
        x = next(rng);
    }

    // should run in less than one second, even on a slow computer
    // the answer is 32355

    cout << maxSum(big_test) << endl;
}