#pragma once

#include <string>
using namespace std;

class Node {
public:
	Node();
	~Node();

	static int const LETTERS = 26;
	Node* _children[LETTERS];

};

class PrefTree {
public:
	PrefTree();
	~PrefTree();

	void insert(string const& word);
	Node const* getRoot()const;
	string autoComplete(string const& word)const;

private:
	string _autoComplete(Node const* node, string searchWord, string completeWord = "", int i = 0)const;

	Node _root;

};
