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
#include <algorithm>
using namespace std;

/*
 * input [-1,2,0,1,0,-1,....]
 * ouput [-1,1,0]
 * -1,2 seek  -1 in [0, 1]
 * -1,0 seek   1 in [2, 1]
 * -1,1 seek   0 in [2, 0]
 *  2,0 seek  -2 in [-1,1]
 *  .....
 *  for each new number
 *  we only need to care right side sequence
 *  as we check left side by find the reqired number
 *  in hash
 *  TLE HELP: 311 / 313 test cases passed.
 *
 */
static vector<vector<int> > threeSum(vector<int>& nums)
{

  vector<vector<int> > ret;
  int size = nums.size();
  vector<int> tmp(3);
  unordered_multimap<int, pair<int, int> > hash;

  for (int i = 0; i < size; ++i)
  {
    int j = i + 1;
    while (j < size)
    {
      if (j - i > 1)
      {
        int find = nums[j];
        auto itr = hash.find(find);
        if (itr != hash.end())
        {
          tmp[0] = itr->second.first;
          tmp[1] = itr->second.second;
          tmp[2] = find;

          if (find >= itr->second.first)
          {
            tmp[1] = find;
            tmp[2] = itr->second.second;
          }
          else
          {
            tmp[0] = find;
            tmp[1] = itr->second.first;
            tmp[2] = itr->second.second;
          }

          if (find >= itr->second.second)
          {
            tmp[2] = find;
            tmp[1] = itr->second.second;
          }

          bool same = false;
          for (int i = 0; i < (int) ret.size(); i++)
          {
            if (ret[i][0] == tmp[0] && ret[i][1] == tmp[1] && ret[i][2] == tmp[2])
            {
              same = true;
              break;
            }
          }
          if (!same)
          {
            //cout << "j=" << j << ", i=" << i << " found sequence:" << itr->second.first << ", " << itr->second.second
            //<< ", " << find << endl;
            ret.push_back(tmp);
          }
        }
      }

      int add = -(nums[i] + nums[j]);
      auto itr = hash.find(add);

      // ignore all duplicated values but keys can be duplicated
      if (nums[i] < nums[j])
      {
        if (itr == hash.end() || (nums[i] != itr->second.first || nums[j] != itr->second.second))
        {
          //cout << "nums[" << i << "]=" << nums[i] << ", nums[j = " << j << "]" << " = " << nums[j] << " insert " << add
          // << endl << endl;
          hash.insert(pair<int, pair<int, int>>(add, pair<int, int>(nums[i], nums[j])));
        }
      }
      else
      {
        if (itr == hash.end() || (nums[j] != itr->second.first || nums[i] != itr->second.second))
        {
          //cout << "nums[" << i << "]=" << nums[i] << ", nums[j = " << j << "]" << " = " << nums[j] << " insert "
          //<< add << endl << endl;
          hash.insert(pair<int, pair<int, int>>(add, pair<int, int>(nums[j], nums[i])));
        }
      }

      j++;
    }
    // must clear hash
    hash.clear();
  }
  //for (auto itr = hash.begin(); itr != hash.end(); ++itr)
  //cout << "add: " << itr->first << ", " << itr->second.first << ", " << itr->second.second << endl;
  return ret;
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
  vector<vector<int> > sum3_ret;
  vector<int> sum3_iput { -4, -2, -2, -2, 0, 1, 2, 2, 2, 3, 3, 4, 4, 6, 6 };
  sum3_ret = threeSum(sum3_iput);
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
