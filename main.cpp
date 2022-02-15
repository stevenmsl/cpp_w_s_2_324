#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include "solution.h"
#include "util.h"

using namespace std;
using namespace sol324;

string toString(vector<int> input)
{
  string result = "[";
  for (auto e : input)
  {
    result += to_string(e);
    result += ",";
  }
  /* remove the last comma */
  if (result.size() > 1)
    result.pop_back();
  result += "]";
  return result;
}

/*
Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].
*/
tuple<vector<int>, vector<int>> testFixture1()
{
  return make_tuple(
      vector<int>{1, 5, 1, 1, 6, 4},
      vector<int>{1, 4, 1, 5, 1, 6});
}

/*
Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].
*/
tuple<vector<int>, vector<int>> testFixture2()
{
  return make_tuple(
      vector<int>{1, 3, 2, 2, 3, 1},
      vector<int>{2, 3, 1, 3, 1, 2});
}

void test1()
{
  auto f = testFixture1();
  cout << "Test 1 - exepct to see " << toString(get<1>(f)) << endl;
  auto result = Solution::wiggleSort(get<0>(f));
  cout << "result: " << toString(result) << endl;
}
void test2()
{
  auto f = testFixture2();
  cout << "Test 2 - exepct to see " << toString(get<1>(f)) << endl;
  auto result = Solution::wiggleSort(get<0>(f));
  cout << "result: " << toString(result) << endl;
}

main()
{
  test1();
  test2();
  return 0;
}