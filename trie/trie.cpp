#include "trie.h"
#include <iostream>

Trie::Trie()
{
	root = new TrieNode();
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	return new TrieNode();
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	TrieNode* tmp=root;
	for(char c:key){
		if(tmp->children[c-'a']==NULL){
			tmp->children[c-'a']=new TrieNode();
		}
		tmp=tmp->children[c-'a'];
	}
	tmp->isWordEnd=true;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	for(char c:key){
		if(root->children[c-'a']==NULL)return false;
		root=root->children[c-'a'];
	}
	return root->isWordEnd;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < 26; i++) {
		if (root->children[i] != NULL) {
			return false;
		}
	}
	return root->isWordEnd;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
	if(root->isWordEnd){
		std::cout<<currPrefix<<std::endl;
	}
	for(int i=0;i<26;i++){
		if(root->children[i]!=NULL)Trie::suggestionsRec(root->children[i],(currPrefix+(char)('a'+i)));
	}
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	TrieNode* tmp=root;
	for(char c:query){
		if(tmp->children[c-'a']==NULL)return 0;
		tmp=tmp->children[c-'a'];
	}
	suggestionsRec(tmp,query);
	return 1;
}
