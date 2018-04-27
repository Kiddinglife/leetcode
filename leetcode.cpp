//============================================================================
// Name        : leetcode.cpp
// Author      : kiddinglife
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;

// 1. Two Sum
static vector<int> twoSum(vector<int>& nums, int target)
{
  //int size = nums.size();
  //vector<int> ret;
  //for (int i = 0; i < size; ++i)
  //{
  //	int find = target - nums[i];
  //	for (int j = i + 1; j < size; ++j)
  //	{
  //		if (find == nums[j])
  //		{
  //			ret.push_back(i);
  //			ret.push_back(j);
  //			return ret;
  //		}
  //	}
  //}
  //return ret;

  int size = nums.size();
  vector<int> ret;
  unordered_map<int, int> hash;
  for (int i = 0; i < size; ++i)
  {

    int val = target - nums[i];
    auto itr = hash.find(val);
    if (itr != hash.end())
    {
      ret.push_back(itr->second);
      ret.push_back(i);
      return ret;
    }
    hash.insert(pair<int, int>(nums[i], i));
  }
  return ret;
}

/*
 * input [-1,2,0,1,0,-1,....]
 * ouput [-1,1,0]
 * -1,2 seek  -1 in [0, 1]
 * -1,0 seek   1 in [2, 1]
 * -1,1 seek   0 in [2, 0]
 *  2,0 seek  -2 in [-1,1]
 *
 *  -1,-1,2,2,2,2,
 *  .....
 *  for each new number
 *  we only need to care right side sequence
 * for right side, we reply on incrmenting j
 *  TLE HELP: 311 / 313 test cases passed.
 *
 */
static vector<vector<int> > threeSumHashmap(vector<int>& nums)
{
  // hashmap solution leetcode 800ms all passed
  vector<vector<int> > ret;
  int size = nums.size();
  if (size < 3)
    return ret;

  set<int> ss;
  ss.insert(nums.begin(), nums.end());
  if (ss.size() == 1)
  {
    if (nums[0] == 0)
      ret.push_back(vector<int>(3, 0));
    return ret;
  }

  set<vector<int>> s;
  vector<int> triple(size_t(3));
  unordered_multimap<int, pair<int, int> > hash;
  sort(nums.begin(), nums.end());
  bool same_triple = false;

  for (int i = 0; i < size; ++i)
  {
    int j = i + 1;
    while (j < size)
    {
      if (nums[j - 1] == nums[j] && nums[j] == nums[i])
        same_triple = true;
      else
        same_triple = false;
      if (j - i > 1 && ((same_triple && nums[j - 1] != 0) || !same_triple))
      {

        int find = nums[j];
        auto itr = hash.find(find);
        if (itr != hash.end())
        {
          cout << "--> found: " << find << ", " << i << ", " << j <<endl;
          triple[0] = itr->second.first;
          triple[1] = itr->second.second;
          triple[2] = find;
          //ret.push_back(triple);
          s.insert(triple);
          same_triple = false;
        }
      }
      // ignore all duplicated values but keys can be duplicated
      if (j - i == 1 || nums[j - 1] != nums[j])
      {
        int add = -(nums[i] + nums[j]);
        cout << "add: " << add << ", " << nums[i] << ", " << nums[j] << ", " << endl;
        if (hash.find(add) == hash.end())
          hash.insert(pair<int, pair<int, int>>(add, pair<int, int>(nums[i], nums[j])));
      }
      j++;
    }
    // must clear hash
    //    for (auto itr = hash.begin(); itr != hash.end(); ++itr)
    //      cout << "add: " << itr->first << ", " << itr->second.first << ", " << itr->second.second << endl;
    //    cout << endl;
    hash.clear();
  }

  ret.assign(s.begin(), s.end());
  return ret;
}

static vector<vector<int> > threeSumHashmap(vector<int>& nums)
{

}
struct add_2_number_node_t
{
    int val;
    add_2_number_node_t *next;
    add_2_number_node_t(int x) :
        val(x), next(NULL)
    {
    }
};
static add_2_number_node_t* addTwoNumbers(add_2_number_node_t* l1, add_2_number_node_t* l2)
{

}
int main()
{
  vector<int> vec_two_sum { 2, 7, 11, 15 };
  int target_two_sum = 9;
  vector<int> ret_two_sum = twoSum(vec_two_sum, target_two_sum);
  for (size_t i = 0; i < ret_two_sum.size(); i++)
  {
    std::cout << ret_two_sum[i] << endl;
  }

  vector<vector<int> > sum3_ret;
  vector<int> sum3_iput { 1 , 0, 0, 0,0,0};
  sum3_ret = threeSumHashmap(sum3_iput);
  cout << "\nsum3_ret: ";
  if (sum3_ret.empty())
    cout << "[]";
  else
    for (int i = 0; i < (int) sum3_ret.size(); i++)
    {
      cout << "[";
      for (int ii = 0; ii < (int) sum3_ret[i].size(); ii++)
      {
        cout << sum3_ret[i][ii] << ", ";
      }
      cout << "], ";
    }
  return 0;
}
