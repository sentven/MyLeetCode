#include "solution.h"
#include <map>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

TrieNode::TrieNode() : isend(false)
{
	for (int i = 0; i < R; i++)
	{
		links[i] = 0;
	}
}

bool TrieNode::containsKey(char ch) const
{
	return links[ch - 'a'] != 0;
}

TrieNode * TrieNode::get(char ch) const
{
	return links[ch - 'a'];
}

void TrieNode::put(char ch, TrieNode *node)
{
	links[ch - 'a'] = node;
}

Trie::Trie()
{
	root = new TrieNode();
}


Trie::~Trie()
{
	destroy(root);
}

void Trie::insert(const char *word)
{
	if (!word)
	{
		return;
	}
	TrieNode *node = root;
	const char *p = word;
	while (*p)
	{
		if (!node->containsKey(*p))
		{
			node->put(*p, new TrieNode());
		}
		node = node->get(*p);
		++p;
	}
	node->setEnd();
}

TrieNode * Trie::searchPrefix(const char *word) const
{
	TrieNode *node = root;
	const char *p = word;
	while (*p)
	{
		if (node->containsKey(*p))
		{
			node = node->get(*p);
		}
		else
		{
			return nullptr;
		}
		++p;
	}
	return node;
}

bool Trie::search(const char *word) const
{
	TrieNode *node = searchPrefix(word);
	return node != nullptr && node->isEnd();
}

bool Trie::startsWith(const char *prefix) const
{
	TrieNode *node = searchPrefix(prefix);
	return node != nullptr;
}

void Trie::destroy(TrieNode * node)
{
	for (int i = 0; i < TrieNode::R; ++i)
	{
		destroy(node->get(i + 'a'));
	}
	delete node;
}

vector<int> Solution::twoSum(vector<int>& nums, int target)
{
	vector<int> ret;
	map<int, int> m;
	for (size_t i = 0; i != nums.size(); ++i) {
		int k = target - nums[i];
		if (m.find(k) != m.end()) {
			if (i != m[k])
			{
				ret.push_back(m[k]);
				ret.push_back(i);
			}
		}
		m[nums[i]] = i;
	}
	return ret;
}

ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2)
{
	if (!l1)
	{
		return l2;
	}
	if (!l2)
	{
		return l1;
	}
	int sum = 0, carry = 0;
	ListNode *head = new ListNode(0);
	ListNode *tail = head;
	while (l1 || l2 || carry)
	{
		sum = carry;
		if (l1)
		{
			sum += l1->val;
			l1 = l1->next;
		}
		if (l2)
		{
			sum += l2->val;
			l2 = l2->next;
		}
		tail = tail->next = new ListNode(sum % 10);
		carry = sum / 10;
	}
	tail = head;
	head = head->next;
	delete tail;
	return head;
}

int Solution::lengthOfLongestSubstring(const string &s)
{
	if (s.empty())
	{
		return 0;
	}
	int maxlen = 0;
	map<char, int> m;
	const int slen = s.length();
	for (int j = 0, i = 0; j < slen; ++j)
	{
		char ch = s[j];
		if (m.find(ch) != m.end())
		{
			int last = m[ch];
			if (last > i)
			{
				i = last;
			}
		}
		int len = j - i + 1;
		if (len > maxlen)
		{
			maxlen = len;
		}
		m[ch] = j + 1;
	}
	return maxlen;
}

int Solution::lengthOfLongestSubstringUsingVector(const string &s)
{
	int maxlen = 0;
	short vec[256];
	for (int i = 0; i < 256; ++i)
	{
		vec[i] = -1;
	}
	const int slen = s.length();
	for (int i = 0, j = 0; j < slen; ++j)
	{
		char ch = s[j];
		if (vec[ch] > i)
		{
			i = vec[ch];
		}
		int len = j - i + 1;
		if (len > maxlen)
		{
			maxlen = len;
		}
		vec[ch] = j + 1;
	}
	return maxlen;
}

double Solution::findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2)
{
	int m = nums1.size();
	int n = nums2.size();
	if (m > n)
	{
		return findMedianSortedArrays(nums2, nums1);
	}
	int mean = (m + n + 1) / 2;
	int left = 0, right = m;
	while (left <= right)
	{
		int i = (left + right) / 2;
		int j = mean - i;
		if (i < right && nums2[j - 1] > nums1[i])
		{
			left = i + 1;
		}
		else if (i > left && nums1[i - 1] > nums2[j])
		{
			right = i - 1;
		}
		else {
			int maxleft = 0;
			if (i == 0) {
				maxleft = nums2[j - 1];
			}
			else if (j == 0) {
				maxleft = nums1[i - 1];
			}
			else {
				maxleft = max(nums1[i - 1], nums2[j - 1]);
			}
			if ((m + n) % 2 == 1) {
				return maxleft;
			}
			int minright = 0;
			if (i == m) {
				minright = nums2[j];
			}
			else if (j == n) {
				minright = nums1[i];
			}
			else {
				minright = min(nums1[i], nums2[j]);
			}
			return (maxleft + minright) / 2.0;
		}
	}
	return 0.0;
}

string Solution::longestPalindrome(const string &s)
{
	int n = s.length();
	if (n <= 1) {
		return s;
	}
	int maxlen = 0, start = -1, len = 0, len1 = 0;
	for (int i = 0; i != s.length(); ++i)
	{
		len = expandAroundCenter(s, i, i);
		len1 = expandAroundCenter(s, i, i + 1);
		if (len < len1)
		{
			len = len1;
		}
		if (len > maxlen)
		{
			maxlen = len;
			start = i - (len - 1) / 2;
		}
	}
	return s.substr(start, maxlen);
}

int Solution::expandAroundCenter(const string &s, int left, int right)
{
	int i = left, j = right;
	while (i >= 0 && j != s.length() && s[i] == s[j])
	{
		--i;
		++j;
	}
	return j - i - 1;
}

string Solution::zigZagConvert(const string &s, int numRows)
{
	if (numRows <= 1)
	{
		return s;
	}
	vector<string> rows(min(numRows, int(s.length())));
	int down = -1;
	int curRow = 1;
	for (int i = 0; i != s.length(); ++i)
	{
		rows[curRow] += s[i];
		if (curRow == 0 || curRow == numRows - 1)
		{
			down = -down;
		}
		curRow += down;
	}
	string ret;
	for (size_t i = 0; i < rows.size(); i++)
	{
		ret += rows[i];
	}
	return ret;
}

int Solution::reverse(int x)
{
	if (x == INT_MIN)
	{
		return 0;
	}
	if (x < 0)
	{
		return -reverse(-x);
	}

	int rev = 0;
	int pop = 0;
	while (x)
	{
		pop = x % 10;
		if (rev * 10.0 > INT_MAX)
		{
			return 0;
		}
		rev = rev * 10 + pop;
	}

	return rev;
}

int Solution::myAtoi(const string &str)
{
	string::size_type i = 0;
	while (i < str.length() && str[i] == ' ') ++i;
	if (i == str.length())
	{
		return 0;
	}
	int sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		++i;
	}
	else if (str[i] == '+') 
	{
		++i;
	}
	else if (!isdigit(str[i]))
	{
		return 0;
	}
	long long ll = 0;
	while (i < str.length() && isdigit(str[i]))
	{
		ll = ll * 10 + str[i++] - '0';
		if (sign == 1)
		{
			if (ll > INT_MAX)
			{
				return INT_MAX;
			}
		}
		else
		{
			if (-ll <= INT_MIN)
			{
				return INT_MIN;
			}
		}
	}
	return (int)ll;
}

// 9. Revert half of the number
bool Solution::isPalindrome(int x)
{
	if (x < 0 || x % 10 == 0 && x != 0)
	{
		return false;
	}
	
	int rev = 0;
	while (rev < x)
	{
		rev = rev * 10 + x % 10;
		x /= 10;
	}
	if (rev == x || rev / 10 == x)
	{
		return true;
	}
	return false;
}

bool Solution::isMatch(const string &s, const string &p)
{
	int i = 0, m = s.length();
	int j = 0, n = p.length();
	while (i < m && j < n)
	{
		if (s[i] == p[j])
		{
			++i;
			++j;
		}
		else if (p[j] == '.' && i > 0 && j > 0 && s[i - 1] == p[j - 1])
		{
			++i;
			++j;
		}
		else if (p[j] == '*')
		{
		}
	}
	return false;
}

// 11. Container With Most Water
// Two Pointer Approach
int Solution::maxArea(const vector<int>& height)
{
	int i = 0, j = height.size() - 1;
	int maxArea = 0, area = 0;
	while (i < j)
	{
		area = (j - i) * min(height[i], height[j]);
		if (area > maxArea)
		{
			maxArea = area;
		}
		if (height[i] < height[j])
		{
			++i;
		}
		else
		{
			--j;
		}
	}
	return maxArea;
}

string Solution::intToRoman(int num)
{
	if (num <= 0)
	{
		return "0";
	}
	if (num	>= 10000)
	{
		return "0";
	}
	string roman;
	int digit = num / 1000;
	for (int i = 0; i < digit; ++i)
	{
		roman += 'M';
	}
	digit = num % 1000 / 100;
	if (digit == 4)
	{
		roman += "CD";
	}
	else if (digit == 9)
	{
		roman += "CM";
	}
	else
	{
		if (digit >= 5)
		{
			roman += "D";
			digit -= 5;
		}
		for (int i = 0; i < digit; ++i)
		{
			roman += 'C';
		}
	}
	digit = num % 100 / 10;
	if (digit == 4)
	{
		roman += "XL";
	}
	else if (digit == 9)
	{
		roman += "XC";
	}
	else
	{
		if (digit >= 5)
		{
			roman += 'L';
			digit -= 5;
		}
		for (int i = 0; i < digit; ++i)
		{
			roman += 'X';
		}
	}
	digit = num % 10;
	if (digit == 4)
	{
		roman += "IV";
	}
	else if (digit == 9)
	{
		roman += "IX";
	}
	else
	{
		if (digit >= 5)
		{
			roman += 'V';
			digit -= 5;
		}
		for (int i = 0; i < digit; ++i)
		{
			roman += 'I';
		}
	}
	return roman;
}

int Solution::romanToInt(const string &s)
{
	const size_t n = s.length();
	if (n == 0)
	{
		return 0;
	}
	int num = 0;

#if 0
	vector<string> romans = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
	vector<int> vals = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	map<string, int> m;
	for (size_t i = 0; i < romans.size(); i++)
	{
		m[romans[i]] = vals[i];
	}
	string sub;
	size_t i = 0;
	while (i < n)
	{
		if (i + 1 < n)
		{
			sub = s.substr(i, 2);
			if (m.find(sub) != m.end())
			{
				num += m[sub];
				i += 2;
				continue;
			}
		}
		sub = s.substr(i, 1);
		if (m.find(sub) != m.end())
		{
			num += m[sub];
			++i;
		}
		else
		{
			break;
		}
	}
#endif
	map<char, int> dict = { { 'I', 1 }, { 'V', 5 }, { 'X', 10 }, { 'L', 50 }, { 'C', 100 }, { 'D', 500 }, { 'M', 1000 } };
	for (size_t i = 0; i < n; i++)
	{
		char ch = s[i];
		if (dict.find(ch) == dict.end())
		{
			break;
		}
		int k = dict[ch];
		if (i + 1 < n)
		{
			ch = s[i + 1];
			if (dict.find(ch) == dict.end())
			{
				break;
			}
			int nk = dict[ch];
			if (k < nk)
			{
				num -= k;
				continue;
			}
		}
		num += k;
	}
	return num;
}


string Solution::longestCommonPrefix(const vector<string>& strs)
{
	if (strs.empty())
	{
		return "";
	}
#if 0
	string prefix;
	size_t k = 0;
	while (true)
	{
		if (k == strs[0].length())
		{
			break;
		}
		char ch = strs[0][k];
		bool same = true;
		for (size_t i = 1; i < strs.size(); i++)
		{
			if (k == strs[i].length())
			{
				same = false;
				break;
			}
			if (ch != strs[i][k])
			{
				same = false;
				break;
			}
		}
		if (same)
		{
			prefix += ch;
			++k;
		}
		else
		{
			break;
		}
	}
#endif
	string prefix = longestCommonPrefix(strs, 0, strs.size() - 1);
	return prefix;
}

string Solution::longestCommonPrefix(const vector<string>& strs, int left, int right)
{
	if (left == right)
	{
		return strs[left];
	}
	int mid = (left + right) / 2;
	string lcpLeft = longestCommonPrefix(strs, left, mid);
	string lcpRight = longestCommonPrefix(strs, mid + 1, right);

	return commonPrefix(lcpLeft, lcpRight);
}

string Solution::commonPrefix(const string &left, const string &right)
{
	int minLen = min(left.length(), right.length());
	for (int i = 0; i < minLen; ++i)
	{
		if (left[i] != right[i])
		{
			return left.substr(0, i);
		}
	}
	if (left.length() < right.length())
	{
		return left;
	}
	return right;
}
