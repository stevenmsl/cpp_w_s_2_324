#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <string>

using namespace std;
namespace sol324
{
  class Solution
  {
  private:
    static pair<int, int> findMedian(vector<int> &nums);
    static int partition(vector<int> &nums, int high, int right);

  public:
    static vector<int> wiggleSort(vector<int> &nums);
    static vector<int> wiggleSort2(vector<int> &nums);
  };

}
#endif