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

// 1. Two Sum https://leetcode.com/problems/two-sum/description/
static vector<int> twoSum(vector<int>& nums, int target)
{
	/*
	int size = nums.size();
	vector<int> ret;
	for (int i = 0; i < size; ++i)
	{
	int find = target - nums[i];
	for (int j = i + 1; j < size; ++j)
	{
	if (find == nums[j])
	{
	ret.push_back(i);
	ret.push_back(j);
	return ret;
	}
	}
	}
	return ret;

	//complexity: o(n power 2)
	//bottle neck: loops
	//improvement:
	//hash table
	//hashtable search b in the left of a : tartget - a = hashed(b)
	//for right wait loop go forwards: tartget - b = hash(a)
	*/

	// use unordered_map o(n)
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

static vector<vector<int> > threeSum(vector<int>& nums)
{
	// my first solution leetcode 800ms all passed using multimap
	// not very fast
	//* input [-1,2,0,1,0,-1,....]
	//* ouput [-1,1,0]
	//* -1,2 seek  -1 in [0, 1]
	//* -1,0 seek   1 in [2, 1]
	//* -1,1 seek   0 in [2, 0]
	//*  2,0 seek  -2 in [-1,1]

	//vector<vector<int> > ret;
	//int size = nums.size();
	//if (size < 3)
	//	return ret;

	//set<int> ss;
	//ss.insert(nums.begin(), nums.end());
	//if (ss.size() == 1)
	//{
	//	if (nums[0] == 0)
	//		ret.push_back(vector<int>(3, 0));
	//	return ret;
	//}

	//set<vector<int>> s;
	//vector<int> triple(size_t(3));
	//unordered_multimap<int, pair<int, int> > hash;
	//sort(nums.begin(), nums.end());
	//bool same_triple = false;

	//for (int i = 0; i < size; ++i)
	//{
	//	int j = i + 1;
	//	while (j < size)
	//	{
	//		if (nums[j] > 0)
	//			break;

	//		if (nums[j - 1] == nums[j] && nums[j] == nums[i])
	//			same_triple = true;
	//		else
	//			same_triple = false;
	//		if (j - i > 1 && ((same_triple && nums[j - 1] != 0) || !same_triple))
	//		{

	//			int find = nums[j];
	//			auto itr = hash.find(find);
	//			if (itr != hash.end())
	//			{
	//				cout << "--> found: " << find << ", " << i << ", " << j << endl;
	//				triple[0] = itr->second.first;
	//				triple[1] = itr->second.second;
	//				triple[2] = find;
	//				//ret.push_back(triple);
	//				s.insert(triple);
	//				same_triple = false;
	//			}
	//		}
	//		// ignore all duplicated values but keys can be duplicated
	//		if (j - i == 1 || nums[j - 1] != nums[j])
	//		{
	//			int add = -(nums[i] + nums[j]);
	//			cout << "add: " << add << ", " << nums[i] << ", " << nums[j] << ", " << endl;
	//			if (hash.find(add) == hash.end())
	//				hash.insert(pair<int, pair<int, int>>(add, pair<int, int>(nums[i], nums[j])));
	//		}
	//		j++;
	//	}
	//	// must clear hash
	//	//    for (auto itr = hash.begin(); itr != hash.end(); ++itr)
	//	//      cout << "add: " << itr->first << ", " << itr->second.first << ", " << itr->second.second << endl;
	//	//    cout << endl;
	//	hash.clear();
	//}

	//ret.assign(s.begin(), s.end());
	//return ret;

	// second solution using sort and two pointers
	vector<vector<int> > ret;
	int size = nums.size();
	int originsize = size;
	if (size < 3)
		return ret;

	sort(nums.begin(), nums.end());
	for (size_t i = 0; i < nums.size(); i++)
		std::cout << nums[i] << ", ";
	std::cout << endl;

	int max_num = nums.back();
	if (max_num < 0)
		return ret;
	int min_num = nums.front();
	if (min_num > 0)
		return ret;

	size_t left, right; 	// defines search range
	size -= 2; // -2 is to stop when less than 3 numbers 
	vector<int> triple(size_t(3));
	int sum;

	for (size_t i = 0; i < size; ++i)
	{
		if (i == 5)
			cout << i << endl;
		// 	all numbers after number 1 are greater than 0 
		// example: 1(i)  [2(left)] 222222  33333[3(right)]
		if (nums[i] > 0)
			break;

		// bypass duplicate numbers at index of i
		// example:  00 111111111111[1(i)] 222222  33333
		while (i < size - 1 && nums[i] == nums[i + 1] && nums[i + 1] == nums[i + 2]) { ++i; }

		left = i + 1;
		right = originsize - 1;

		// all numbers after number 1 are greater than 0 
		// example: 0(i) [1(left)]1111 222222  33333[3(right)]
		if (nums[i] == 0 && nums[left] > 0)
			break;

		// why not use left != right 
		// example:  0(i=0) [-1(left=1)]  [1(right=2)]
		// after left ++ and right --
		// [2 = left] != [right = 1 ]
		// this will cause while loop never ends
		while (left < right)
		{
			// @remember me: should not bypass here
			// example: 
			// -5, -5, -4, -4, -4, -2, -2, -2(i), 0(left), 0, 0, 1, 1, 3(right), 4, 4 -> after bypass =>
			// -5, -5, -4, -4, -4, -2, -2, -2(i=7), 0, 0, 0(left), 1(right=11), 1, 3, 4, 4,
			// -5, -5, -4, -4, -4, -2, -2, -2(i=7), 0, 0, 0, 1(left,right=11), 1, 3, 4, 4,
			// as you see -2, 1 , 1 is missed which is kind of bug.
			// the solution is to move this section of codes to section where sum == 0
			// only in this case we can safely bypass the duplicates
			//while (right - left > 2 && nums[left-1] == nums[left + 1]) { ++left; }
			//while (right - left > 2 && nums[right] == nums[right - 1]) { --right; }

			// example: 
			// -5(i) [-3(left)] -2           -1 0 1 2 3 5 6  7              8             [9(right)] -> sum = -5-3+9=1 > 0, --right =>
			// -5(i) [-3(left)] -2           -1 0 1 2 3 5 6  7             [8(right)]  9  -> found -5-3+8=0, --right, ++left =>
			// -5(i)  -3         [-2(left)]  -1 0 1 2 3 5 6 [7(right)]  8              9
			// ...... comtinue the above procedure and finally =>
			// -5(i)  -3  -2  -1 0 1 [2(right)] [3(left)] 5 6 7  8 9 -> left > right => while loop stops
			sum = nums[i] + nums[left] + nums[right];
			if (sum > 0)
				--right;
			else if (sum < 0)
				++left;
			else
			{
				triple.assign({ nums[i], nums[left], nums[right] });
				ret.push_back(triple);

				for (size_t i = 0; i < 3; i++)
					std::cout << triple[i] << " ";
				std::cout << endl;

				++left;
				--right;

				// bypass duplicate numbers in search range defined by left and right only when it is found
				// example:  0(i) -1-1-1-1-1[-1(left)] 11111 222222 [3(right)] 33333
				// after bypass, lfet is at the rightmost number -1, right is at the leftmost number 3
				// in such way search range is miminized and so search gets faster. 
				while (left < right && nums[left-1] == nums[left + 1]) { ++left; }
				while (left < right && nums[right] == nums[right - 1]) { --right; }

				// bypass duplicated numbers at index i as we already found them 
				while (i < originsize && nums[i] == nums[i + 1]) { i++; }
			}
		}
	}
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
	vector<int> vec_two_sum{ 2, 7, 11, 15 };
	int target_two_sum = 9;
	vector<int> ret_two_sum = twoSum(vec_two_sum, target_two_sum);
	for (size_t i = 0; i < ret_two_sum.size(); i++)
	{
		std::cout << ret_two_sum[i] << endl;
	}

	vector<vector<int> > sum3_ret;
	vector<int> sum3_iput{ -4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0 }; // 0, 0, 0, 0, 0, 1
	sum3_ret = threeSum(sum3_iput);
	cout << "\nsum3_ret: ";
	if (sum3_ret.empty())
		cout << "[]";
	else
		for (int i = 0; i < (int)sum3_ret.size(); i++)
		{
			cout << "[";
			for (int ii = 0; ii < (int)sum3_ret[i].size(); ii++)
			{
				cout << sum3_ret[i][ii] << ", ";
			}
			cout << "], ";
		}
	return 0;
}
