#include "solution.h"
#include "util.h"
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
using namespace sol324;
using namespace std;

/*takeaways
  - nums[0] < nums[1] > nums[2] < nums[3] without the
    equal sign make a big differnce
  - to form a valid answer the input must have
    at least two different values. They can
    have the same numbers or one of the values
    has one more depending on the length of
    the input
    - [1,2,2,1,2]
    - [1,1,2,2,2] sorted
    - break it down to two parts: [1,1] and [2,2,2]
      to form the foundation of the navive solution
  - for the more advanced solution
    - partition is very easy to get wrong if you
      don't consider the edge cases carefully
      - check the comments on the method
    - once you got the partition right, finding
      median should be easier
    - to achieve space O(1), you need to know
      some trickery of re-mapping the index
      - formula: (1 + 2 * i) % (n | 1)
      - re-mapping: [0,1,2,3,4,5] -> [1,3,5,0,2,4]
*/

/* naive solution */
vector<int> Solution::wiggleSort(vector<int> &nums)
{
  const int n = nums.size();
  auto t = vector<int>(n);
  sort(nums.begin(), nums.end());

  /*
    - split the sorted input from the median into
      two parts
    - start with the last position of the first part
      and the last position of the second part
      to avoid tie while assigning them to the
      even index and odd index positions
      separately in temp vector
  */

  /*
     - left should have at least the same or one
       more elements than the right
     - left is filling up the odd positions
       - don't forget this is 0-based so
         t[0] is the odd position!
  */
  int left = n / 2;
  int right = n - 1;

  auto pos = 0;

  while (pos < n)
  {
    if (pos % 2 == 0)
      t[pos++] = nums[left--];
    else
      t[pos++] = nums[right--];
  }

  return t;
}

vector<int> Solution::wiggleSort2(vector<int> &nums)
{
  const int n = nums.size();
  auto median = findMedian(nums).first;

  /*
    - space(1)
    - [0,1,2,3,4,5] -> [1,3,5,0,2,4]
  */
  auto mapIndex = [n](int i)
  {
    /*
      - n | 1 will find the next odd number
        if it's even
      - remains unchanged if it's odd
      - once it's greater than n|1
        the new index will become
        an even number as odd-odd=even
    */
    auto newIndex = (1 + 2 * i) % (n | 1);
    return newIndex;
  };

  int left = 0, right = n - 1;

  while (left < right)
  {
    auto ml = mapIndex(left);
    auto mr = mapIndex(right);

    /*
      - the ml will start with the odd-indexed position
        and mr even-indexed position
      - so as long as we swap the ml and mr until we
        can't we are good
      - this is because we already know that we have
        broken the nums into two parts with the smaller
        numbers on the left of the median larger on
        the right
    */
    if (nums[ml] < median)
      swap(nums[ml], nums[mr]);
    left++;
    right--;
  }

  return nums;
}

/*
  - nums[left] will be moved to a new location
    j where on its left are smaller numbers
    than nums[left] and on its right bigger
  - Those numbers are not sorted
  - there are n-j-1 elements after the new
    location which are all bigger than
    nums[j], so nums[j] is the n-j th
    largest number
*/

int Solution::partition(vector<int> &nums, int left, int right)
{

  auto i = left, j = right + 1;

  while (true)
  {
    /*
      - find a number that is larger
        than nums[left]
    */
    while (++i < right)
    {
      if (nums[i] > nums[left])
        break;
    }

    /* do the opposite - find a number
       than is smaller than nums[left]
       from the right
     */
    while (--j > left)
    {
      if (nums[j] < nums[left])
        break;
    }
    if (i >= j)
      break;

    swap(nums[i], nums[j]);
  }

  if (nums[left] > nums[j])
    /* swaps have happened or left is the largest */
    swap(nums[left], nums[j]);
  else
    /* left is the smallest*/
    return left;

  return j;
}

pair<int, int> Solution::findMedian(vector<int> &nums)
{
  /*
    - there are k-1 numbers after k
    - check comments on parition method
  */
  auto k = nums.size() - nums.size() / 2;
  int lo = 0, hi = nums.size() - 1;
  while (lo < hi)
  {
    auto j = partition(nums, lo, hi);
    /*
      - don't overthink this; j and k are
        just indexes
      - this just means I need fewer
        numbers after than j has
        right now
    */
    if (j < k)
      lo = j + 1;
    else if (j > k)
      hi = j - 1;
    else
      break;
  }
  return make_pair(nums[k], k);
}