#include "preftree.h"

Node::Node() {
	for (auto i = 0; i < LETTERS; ++i) {
		_children[i] = nullptr; // � ������ ����� ��� ������� �� ����
	}
}

Node::~Node() {
	// todo: �������� ����������� �������� �����
}

PrefTree::PrefTree() {

}

PrefTree::~PrefTree() {

}

void PrefTree::insert(string const& word) {
	Node* node = &_root;                      // �������� � ����� (������ ������ ������, �� �����)

	for (auto ch : word) {                    // ��������� ����� �����������
		auto const i = tolower(ch) - 'a';     // ������� ������ ������ ���������������� �������

		if (node->_children[i] != nullptr) {  // ������ ��� ����������, ��������� � ����
			node = node->_children[i];
		}
		else {                                // ������ �� ����������, ������ � ��������� � ����
			node->_children[i] = new Node(); 
			node = node->_children[i];
		}
	}
}

Node const* PrefTree::getRoot()const {
	return &_root;
}

string PrefTree::_autoComplete(Node const* node, string searchWord, string completeWord, int depth)const {
	// node ������� ����, depth ������� �������� (������� ���������� ������)
	// searchWord - ��, ��� ����� ���������, completeWord - ��, ��� ��������� (���������)

	if (searchWord.size() > depth) { // �������� ����� (������� � �������� ������)
		// ����������� ���� �� ������ (����������� ��������� �� ������ �
		// ������) �� ��� ����� ������, ������� ���������� �������������
		// ��������� �����. ���� ����� ����� ���, ������������ ������ ������.
		// ���� ����� ��������� ������ ��������, ������������ ����������� �����.
		// ���� ����� ��������� ���������, ����� ��������� � else.
		auto i = tolower(searchWord[depth]) - 'a';
		
		if (node->_children[i] != nullptr) {
			string nextWord = completeWord;
			nextWord.push_back('a' + i);

			return _autoComplete(node->_children[i], searchWord, nextWord, depth + 1);
		}
		else {
			return completeWord;
		}
	}
	else { 
		// ���������� �� �������, ��������������� ������� �������� ������.
		// ������ ���������� � ������� ������� ���������� ������.
		for (auto i = 0; i < Node::LETTERS; ++i) {
			if (node->_children[i] != nullptr) {
				string nextWord = completeWord;
				nextWord.push_back('a' + i);

				return _autoComplete(node->_children[i], searchWord, nextWord, depth + 1);
			}
		}
	}

	return completeWord;
}

string PrefTree::autoComplete(string const& word)const {
	return _autoComplete(&_root, word);
}
