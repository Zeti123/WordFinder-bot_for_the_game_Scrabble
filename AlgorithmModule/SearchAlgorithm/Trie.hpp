#pragma once

#include <vector>
#include <string>
#include <cstdint>

class TrieNode;

/* Implements Trie data structure in very memory-efficient way (16 bytes per node), structure heavily 
   specialized to be searched by algoytms like bfs or dfs, adding more words to structure is not time-efficient */
class Trie
{
friend class TrieNode;

public:
	Trie(const std::vector<std::string>& listOfWords);
	void insert(const std::string& word);
	bool find(const std::string& word) const;
	TrieNode root() const;
	std::vector<std::string> getAllWords() const;
	
private:
	struct PrivateNode
	{
		PrivateNode* children;
		uint32_t subtreeSize;
		uint16_t childrenCount;
		char character;
		bool endOfWord;
	};
	void getAllWordsRec(std::vector<std::string>& words, std::vector<char>& currWord, const TrieNode& currNode) const;
	// returns new subtreeSize of currNode
	uint32_t insertRec(const std::string& word, size_t charNum, PrivateNode& currNode);
	void addChild(PrivateNode& parent, char c);
	
	PrivateNode root_;
};

class TrieNode
{
public:
	static constexpr uint16_t npos = UINT16_MAX;
	TrieNode(const TrieNode&) = default;
	TrieNode(const Trie::PrivateNode& node);
	// returns number of children
	uint32_t childCount() const;
	TrieNode childAt(uint16_t num) const;
	// returns number of child with given character, if none exists, it returns TreeNode::npos
	uint16_t getChildNum(char ch) const;
	uint32_t subtreeSize() const;
	char character() const;
	bool leaf() const;
	bool endOfWord() const;
	
private:
	Trie::PrivateNode node_;
};
