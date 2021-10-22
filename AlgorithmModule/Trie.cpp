#include "Trie.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>

Trie::Trie(const std::vector<std::string>& listOfWords)
	:root_{nullptr, 1, 0, '\0', false} 
{
	for (const auto& word: listOfWords)
		insert(word);
}

void Trie::insert(const std::string& word)
{
	insertRec(word, 0, root_);
}

bool Trie::find(const std::string& word) const
{
	auto node = root();
	for (auto c: word)
	{
		uint32_t pos = node.getChildNum(c);
		if (pos == TrieNode::npos)
			return false;
		
		node = node.childAt(pos);
	}
	return node.endOfWord();
}

TrieNode Trie::root() const
{
	return TrieNode(root_);
}

std::vector<std::string> Trie::getAllWords() const
{
	std::vector<std::string> words;
	std::vector<char> currWord;
	for (size_t i = 0; i < root_.childrenCount; i++)
		getAllWordsRec(words, currWord, root_.children[i]);
	
	return words;
}

static std::string vectorToString(const std::vector<char>& vec) 
{
	std::string str;
	str.resize(vec.size());
	size_t size = vec.size();
	for (size_t i = 0; i < size; i++)
		str[i] = vec[i];
	
	return str;
}

void Trie::getAllWordsRec(std::vector<std::string>& words, std::vector<char>& currWord, const TrieNode& currNode) const
{
	currWord.push_back(currNode.character());
	if (currNode.endOfWord())
		words.push_back(vectorToString(currWord));
	if (currNode.childCount() == 0)
	{
		currWord.pop_back();
		return;
	}

	for (size_t i = 0; i < currNode.childCount(); i++)
		getAllWordsRec(words, currWord, currNode.childAt(i));

	currWord.pop_back();
}

uint32_t Trie::insertRec(const std::string& word, size_t charNum, PrivateNode& currNode)
{
	if (charNum >= word.size())
	{
		currNode.endOfWord = true;
		currNode.subtreeSize = 1;
		return currNode.subtreeSize;
	}
	
	char c = word[charNum];
	uint32_t pos = TrieNode(currNode).getChildNum(c);
	if (pos == TrieNode::npos)
	{
		pos = currNode.childrenCount;
		addChild(currNode, c);
	}
	uint32_t subTreeSize = insertRec(word, charNum+1, currNode.children[pos]);
	currNode.subtreeSize = std::max(currNode.subtreeSize, subTreeSize + 1);
	return currNode.subtreeSize;
}

void Trie::addChild(PrivateNode& parent, char c)
{
	Trie::PrivateNode* tmp = new PrivateNode[parent.childrenCount + 1];
	memcpy(tmp, parent.children, sizeof(PrivateNode) * parent.childrenCount);
	delete[] parent.children;
	parent.children = tmp;
	parent.children[parent.childrenCount] = {nullptr, 1, 0, c, false};
	parent.childrenCount++;
}

TrieNode::TrieNode(const Trie::PrivateNode& node)
	:node_(node) {}

// returns number of children
uint32_t TrieNode::childCount() const
{
	return node_.childrenCount;
}

TrieNode TrieNode::childAt(uint16_t num) const
{
	return node_.children[num];
}

// returns number of child with given character, if none exists, it returns TreeNode::npos
uint16_t TrieNode::getChildNum(char ch) const
{
	uint16_t count = childCount();
	for (uint16_t i = 0; i < count; i++)
		if (node_.children[i].character == ch)
			return i;
	
	return npos;
}

uint32_t TrieNode::subtreeSize() const
{
	return node_.subtreeSize;
} 

char TrieNode::character() const
{
	return node_.character;
}

bool TrieNode::leaf() const
{
	return childCount() == 0;
}

bool TrieNode::endOfWord() const
{
	return node_.endOfWord;
}
