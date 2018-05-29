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
#include <stack>
#include <istream>
#include <ostream>

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
	 */
	vector<int> ret(2);
	int size = nums.size();
	if (size < 2)
		return ret;
	unordered_multimap<int, int> idxs;
	for (int i = 0; i < (int)nums.size(); ++i)
		idxs.insert(pair<int, int>(nums[i], i));
	sort(nums.begin(), nums.end());
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		if ((nums[left] + nums[right]) > target)
			--right;
		else if ((nums[left] + nums[right]) < target)
			++left;
		else
		{
			if (idxs.find(nums[left])->first == idxs.find(nums[right])->first)
			{
				auto rett = idxs.equal_range(nums[left]);
				//for (auto it = rett.first; it != rett.second; ++it)
				//	std::cout << it->second;
				//cout << endl;
				ret[0] = rett.first->second + 1;
				++rett.first;
				ret[1] = rett.first->second + 1;
			}
			else
			{
				ret[0] = idxs.find(nums[left])->second + 1;
				ret[1] = idxs.find(nums[right])->second + 1;
			}
			break;
		}
	}
	return ret;
}

// 1. Two Sum sorted  https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/
static vector<int> twoSumSorted(vector<int>& nums, int target)
{
	vector<int> ret(2);
	int size = nums.size();
	if (size < 2)
		return ret;

	int left = 0;
	int right = size - 1;
	int sum;
	while (left < right)
	{
		if ((nums[left] + nums[right]) > target)
			--right;
		else if ((nums[left] + nums[right]) < target)
			++left;
		else
		{
			ret[0] = left + 1;
			ret[1] = right + 1;
			break;
		}
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
	//for (size_t i = 0; i < nums.size(); i++)
	//	std::cout << nums[i] << ":" << i <<", ";
	//std::cout << endl;

	int max_num = nums.back();
	if (max_num < 0)
		return ret;
	int min_num = nums.front();
	if (min_num > 0)
		return ret;

	int left, right; 	// defines search range
	size -= 2; // -2 is to stop when less than 3 numbers
	vector<int> triple(size_t(3));
	int sum;

	for (int i = 0; i < size; ++i)
	{
		// 	all numbers after number 1 are greater than 0
		// example: 1(i)  [2(left)] 222222  33333[3(right)]
		if (nums[i] > 0)
			break;

		// bypass duplicate numbers at index of i
		// example:  00 111111111111[1(i)] 222222  33333
		while (i < size - 1 && nums[i] != 0 && nums[i] == nums[i + 1] && nums[i + 1] == nums[i + 2])
		{
			++i;
		}

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
				//for (size_t i = 0; i < 3; i++)
				//	std::cout << triple[i] << " ";
				//std::cout << endl;
				ret.push_back(triple);

				// bypass duplicate numbers in search range defined by left and right only whenthe triple is found
				// example:  0(i) -1-1-1-1-1[-1(left)] 11111 222222 [3(right)] 33333
				// after bypass, lfet is at the rightmost number -1, right is at the leftmost number 3
				while (left < right && nums[left] == nums[left + 1])
				{
					++left;
				}
				while (right > left && nums[right] == nums[right - 1])
				{
					--right;
				}

				// bypass duplicated numbers at index i only whenthe triple is found
				// example:  -1 -1(i) 0(left) 1(right), need to bypass the other -1 0 1
				while (i < left && nums[i] == nums[i + 1])
				{
					i++;
				}

				++left;
				--right;
			}
		}
	}
	return ret;
}

// https://leetcode.com/problems/3sum-closest/description/
static int threeSumClosest(vector<int>& nums, int target)
{
	int size = nums.size();
	int originsize = size;
	int ret;
	if (size <= 3)
	{
		ret = 0;
		for (size_t i = 0; i < nums.size(); i++)
			ret += nums[i];
		return ret;
	}

	int mindiff = 0;
	sort(nums.begin(), nums.end());

	size_t left, right;   // defines search range
	size -= 2; // -2 is to stop when less than 3 numbers
	int sum;

	for (int i = 0; i < size; ++i)
	{
		left = i + 1;
		right = originsize - 1;
		while (left < right)
		{
			sum = nums[i] + nums[left] + nums[right];
			if (sum > target)
				--right;
			else if (sum < target)
				++left;
			else
				return target;

			int dis = abs(sum - target);
			if (mindiff == 0 || mindiff > dis)
			{
				mindiff = dis;
				ret = sum;
			}
		}
	}
	return ret;
}

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
static int removeDuplicates(vector<int>& nums)
{
	size_t size = nums.size();
	if (size == 0)
		return 0;
	size_t pos = 0;
	for (size_t i = 0; i < size - 1; i++)
	{
		if (nums[i] != nums[i + 1])
		{
			pos++;
			nums[pos] = nums[i + 1];
		}
	}
	return pos + 1;
}

// https://leetcode.com/problems/remove-element/description/
static int removeElement(vector<int>& nums, int val)
{
	// 0 1 2 3 4 5  6 7 8 9
	// 0 1 1 1 3 0  4 2 1 1
	// 0 3 0 4 2 0' 4 2
	size_t vsize = nums.size();
	int pos = -1;
	for (size_t i = 0; i < vsize; i++)
	{
		if (pos == -1)
		{
			if (nums[i] == val)
				pos = i;
		}
		else if (nums[i] != val)
		{
			nums[pos] = nums[i];
			pos++;
		}
	}
	return pos == -1 ? vsize : pos;
}

/*
 Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array),
 some elements appear twice and others appear once.
 Find all the elements of [1, n] inclusive that do not appear in this array.
 Could you do it without extra space and in O(n) runtime? You may assume the
 returned list does not count as extra space.

 Example:
 Input:
 [4,3,2,7,8,2,3,1]
 [-1,1,3]
 Output:
 [5,6]
 */
static vector<int> findDisappearedNumbers(vector<int>& nums)
{
	//  sort v1 slow 14.42% beats
	//  vector<int> ret;
	//  nums.push_back(0);
	//  int vsize = nums.size();
	//  nums.push_back(vsize);
	//  vsize++;
	//  int size = vsize -2;
	//  std::sort(nums.begin(), nums.end());
	//  for (int i = 0; i < vsize; ++i)
	//  {
	//    if(nums[i] > vsize)
	//      break;
	//
	//    if (i + 1 < vsize && nums[i+1] - nums[i] > 1)
	//    {
	//      int v = nums[i] + 1;
	//      do
	//      {
	//        if (v >= 1 && v <= size)
	//        {
	//          ret.push_back(v);
	//          v++;
	//        }
	//        else
	//          break;
	//      } while (v < nums[i+1]);
	//    }
	//  }
	//  return ret;

	// v2 notice that there is assuptio that nums is betwwen trnage of vector so use vector to mark existing munbers
	// this is faster than v1 as we save sort(), if n osuch assumption, sort(0 is more stable and faster
	// beats 97.87% 126ms
	int len = nums.size();
	vector<int> res;
	res.reserve(len / 2);
	int i, m;
	for (i = 0; i < len; i++)
	{
		m = abs(nums[i]) - 1; // index start from 0
		if (nums[m] > 0)
			nums[m] = -nums[m]; // must use -nums[m] as we may use it laters
	}
	for (i = 0; i < len; i++)
	{
		if (nums[i] > 0)
			res.push_back(i + 1);
	}
	return res;

}

/**
 Given an integer array nums, find the contiguous subarray
 (containing at least one number) which has the largest sum
 and return its sum.

 Example:
 Input: [-2,1,-3,4,-1,2,1,-5,4],
 Output: 6
 Explanation: [4,-1,2,1] has the largest sum = 6.

 Input: [1,-2,1, 2],
 Output: 6
 Explanation: [4,-1,2] has the largest sum = 5.]
 sum = -2, res = -2, min = -2;
 sum = -1, res = 1,

 Follow up:
 If you have figured out the O(n) solution, try coding
 another solution using the divide and conquer approach, which is more subtle.
 */
int maxSubArray(int A[], int n)
{
	int sum = 0, min = 0, res = A[0];
	for (int i = 0; i < n; i++)
	{
		sum += A[i];
		if (sum - min > res)
			res = sum - min;

		if (sum < min)
			min = sum;
	}
	return res;
}

/**
 https://leetcode.com/problems/rotate-array/description/
 Given an array, rotate the array to the right by k steps, where k is non-negative.

 Example 1:
 Input: [1,2,3,4,5,6,7] and k = 3
 Output: [5,6,7,1,2,3,4]
 Explanation:
 rotate 1 steps to the right: [7,1,2,3,4,5,6]
 rotate 2 steps to the right: [6,7,1,2,3,4,5]
 rotate 3 steps to the right: [5,6,7,1,2,3,4]

 Example 2:
 Input: [-1,-100,3,99] and k = 2
 Output: [3,99,-1,-100]
 Explanation:
 rotate 1 steps to the right: [99,-1,-100,3]
 rotate 2 steps to the right: [3,99,-1,-100]
 */
void array_rotate(vector<int>& nums, int k)
{
	int i, n = nums.size(), offset = 0;
	for (; k = k % n; n -= k)
	{
		// Swap the last k elements with the first k elements.
		// The last k elements will be in the correct positions
		// but we need to rotate the remaining (n - k) elements
		// to the right by k steps.
		for (i = 0; i < k; i++)
			swap(nums[i + offset], nums[n - k + i + offset]);
		offset += i;
	}
}

/*
 4ms 95.45% beats
 Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
 determine if the input string is valid.
 An input string is valid if:
 Open brackets must be closed by the same type of brackets.
 Open brackets must be closed in the correct order.
 Note that an empty string is also considered valid.
 */
bool isValid(string s)
{
	stack<char> vals;
	for (auto c : s)
	{
		if (c == '(' || c == '{' || c == '[')
			vals.push(c);
		else
		{
			if (vals.size() == 0)
				return false;
			char cc = vals.top();
			if ((cc == '(' && c == ')') || (cc == '{' && c == '}') || (cc == '[' && c == ']'))
				vals.pop();
			else
				return false;
		}
	}
	return vals.size() == 0;
}

/*
假设数组为a[N]，max[N] 表示以下标为 i 结尾的子数组乘积最大值，
min[N] 表示以下标为 i 结尾的子数组乘积最小值。
为了处理数组元素为负的问题，必须将最小乘积也保存起来。
很容易想到，若当前元素a[i]为负数，那么a[i]*max[i-1]得到的值并不一定比a[i]*min[i-1]大，
因为min[i-1]可能为负，如果min[i-1]的绝对值大于max[i-1]，
那么a[i]*min[i-1]负负相乘的值是更大的，因此有DP方程:
curmax = MaxinThree(a[i],  a[i]*premax,  a[i]*premin);    //求三者最大
curmin = MininThree(a[i],  a[i]*premax,  a[i]*premin);     //求三者最小
*/
int maxProduct(vector<int>& nums)
{
	int vsize = nums.size();
	if (vsize == 0) return 0;
	int premax = nums[0];
	int premin = nums[0];
	int res = premax;
	int curmax, curmin;
	printf("curmax: %d, curmin: %d, res: %d\n", premax, premin, res);
	for (int i = 1; i < vsize; i++)
	{
		curmax = max(max(premax*nums[i], premin*nums[i]), nums[i]);
		curmin = min(min(premax*nums[i], premin*nums[i]), nums[i]);
		res = max(curmax, res);
		printf("curmax: %d, curmin: %d, res: %d\n", curmax, curmin, res);
		premax = curmax;
		premin = curmin;
	}
	return res;
}

int main()
{
	vector<int> vec_two_sum{ 0, 0, 3, 4 };
	int target_two_sum = 0;
	vector<int> ret_two_sum = twoSum(vec_two_sum, target_two_sum);
	std::cout << "two_sum_ret: ";
	for (size_t i = 0; i < ret_two_sum.size(); i++)
		std::cout << ret_two_sum[i] << " ";
	std::cout << endl;

	vector<int> two_sum_sorted_array{ 0, 0, 3, 4 };
	int two_sum_sorted_target = 0;
	vector<int> two_sum_sorted_ret = twoSumSorted(two_sum_sorted_array, two_sum_sorted_target);
	std::cout << "two_sum_sorted_ret: ";
	for (size_t i = 0; i < two_sum_sorted_ret.size(); i++)
		std::cout << two_sum_sorted_ret[i] << " ";
	std::cout << endl;

	vector<vector<int> > sum3_ret;
	vector<int> sum3_iput{ -2, 0, 1, 1, 2 };  //-2 -2 -2  0000 111  2222
	sum3_ret = threeSum(sum3_iput);
	std::cout << "three_sum_ret: ";
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

	int sum3_closeast_ret;
	vector<int> sum3_closeast_array{ -4, -1, 1, 2 };
	int sum3_closeast_tartget = 1;
	sum3_closeast_ret = threeSumClosest(sum3_closeast_array, sum3_closeast_tartget);
	cout << "\nsum3_closeast_ret: " << sum3_closeast_ret << endl;

	vector<int> remove_duplicates_array{ 1, 1, 2 };
	int remove_duplicates_ret = removeDuplicates(remove_duplicates_array);
	std::cout << "remove_duplicates_ret: " << remove_duplicates_ret << ", array: ";
	for (int i = 0; i < remove_duplicates_ret; i++)
		std::cout << remove_duplicates_array[i] << " ";
	std::cout << endl;

	vector<int> remove_element_array{ 1, 1, 1, 0, 1, 1, 0 };
	int removing_element = 1;
	int remove_element_ret = removeElement(remove_element_array, removing_element);
	std::cout << "remove_element_ret: " << remove_element_ret << ", array: ";
	for (int i = 0; i < remove_element_ret; i++)
		std::cout << remove_element_array[i] << " ";
	std::cout << endl;

	vector<int> findDisappearedNumbers_array{ 4, 3, 2, 7, 8, 2, 3, 1 };
	vector<int> findDisappearedNumbers_ret = findDisappearedNumbers(findDisappearedNumbers_array);
	std::cout << "findDisappearedNumbers_ret: ";
	for (int i = 0; i < (int)findDisappearedNumbers_ret.size(); i++)
		std::cout << findDisappearedNumbers_ret[i] << " ";
	std::cout << endl;

	vector<int> array_rotate_array{ 1, 2, 3, 4, 5, 6, 7 };
	int k = 4;
	array_rotate(array_rotate_array, k);
	std::cout << "array_rotate_array_ret: ";
	for (int i = 0; i < (int)array_rotate_array.size(); i++)
		std::cout << array_rotate_array[i] << " ";
	std::cout << endl;

	string s = "()[]";
	cout << "isValid ret: ";
	cout << isValid(s) << endl;

	vector<int> array_maxProduct{ 2,3,-2,4 };
	std::cout << "maxProduct: ";
	int ret_maxProduct = maxProduct(array_maxProduct);
	std::cout << ret_maxProduct << endl;

	return 0;
}
