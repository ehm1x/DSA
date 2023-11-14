#include <deque>
#include <vector>
#include <iostream>

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::deque<int> dq;

    for (int i = 0; i < nums.size(); i++) {
        // Remove elements out of window from the front.
        if (!dq.empty() && dq.front() == i - k)
            dq.pop_front();

        // Remove all elements smaller than the current from the back.
        while (!dq.empty() && nums[dq.back()] < nums[i])
            dq.pop_back();

        // Push current element to the back.
        dq.push_back(i);

        // The first index in deque is the largest element in the window.
        if (i >= k - 1)
            result.push_back(nums[dq.front()]);
    }

    return result;
}

int main() {
    std::vector<int> nums = { 1, -1 };
    int k = 1;

    std::vector<int> result = maxSlidingWindow(nums, k);
    for (int x : result) {
        std::cout << x << " ";
    }

    return 0;
}