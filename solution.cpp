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