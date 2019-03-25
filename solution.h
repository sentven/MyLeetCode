#ifndef __SOLUTION_HEADDER__
#define __SOLUTION_HEADDER__

#include <vector>
#include <map>
#include <string>

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class TrieNode
{
public:
	static const int R = 26;
public:
	TrieNode();
	~TrieNode() {};

	bool containsKey(char ch) const;
	TrieNode * get(char ch) const;

	void put(char ch, TrieNode *node);

	bool isEnd() const { return isend; }
	void setEnd() { isend = true; }

private:
	TrieNode * links[R];
	bool isend;
};

class Trie
{
public:
	Trie();
	~Trie();

	// Insert a word into the trie
	void insert(const char *word);

	// search a prefix or whole key in trie and returns the node where ends
	TrieNode * searchPrefix(const char *word) const;

	// Returns if the word is in the trie.
	bool search(const char *word) const;

	// Returns if there is any word in the trie that starts with the given prefix.
	bool startsWith(const char *prefix) const;

private:
	void destroy(TrieNode * node);
	TrieNode *root;
};


class Solution {
public:
	// 1. Two Sum
	std::vector<int> twoSum(std::vector<int>& nums, int target);

	// 2. Add Two Numbers
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

	// 3. Longest Substring Without Repeating Characters
	int lengthOfLongestSubstring(const std::string &s);
	int lengthOfLongestSubstringUsingVector(const std::string &s);

	// 4. Median of Two Sorted Arrays
	double findMedianSortedArrays(const std::vector<int>& nums1, const std::vector<int>& nums2);

	// 5. Longest Palindromic Substring
	std::string longestPalindrome(const std::string &s);
	int expandAroundCenter(const std::string &s, int left, int right);

	// 6. ZigZag Conversion
	std::string zigZagConvert(const std::string &s, int numRows);
	int reverse(int x);
	int myAtoi(const std::string &str);

	// 9. Palindrome Number | Easy
	bool isPalindrome(int x);

	// 10. Regular Expression Matching | Hard
	bool isMatch(const std::string &s, const std::string &p);

	// 11. Container With Most Water
	int maxArea(const std::vector<int>& height);

	// 12. Integer to Roman
	std::string intToRoman(int num);

	// 13. Roman to Integer
	int romanToInt(const std::string &s);

	// 14. Longest Common Prefix
	std::string longestCommonPrefix(const std::vector<std::string>& strs);

	std::string longestCommonPrefix(const std::vector<std::string>& strs, int left, int right);

	std::string commonPrefix(const std::string &left, const std::string &right);
};

#endif