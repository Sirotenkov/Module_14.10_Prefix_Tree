#include <iostream>
#include <conio.h>
#include "preftree.h"
using namespace std;

// ���� ������ ����������, ������� ���������� getch
#define KEY_BACK 8
#define KEY_TAB 9
#define KEY_ENTER 13
#define KEY_ESC 27

void printTree(Node const* node, string word = "") {  // ���������� (���������������) ������� ����������� ������
	auto childCount = 0;

	for (auto i = 0; i < Node::LETTERS; ++i) {
		if (node->_children[i] != nullptr) {
			string next_word = word;
			next_word.push_back('a' + i);

			printTree(node->_children[i], next_word);
			childCount++;
		}
	}

	if (childCount == 0) {
		cout << word << endl;
	}
}

void printTree(PrefTree* tree) {
	printTree(tree->getRoot());
}

int main() {
	PrefTree tree;                          // ������ ������ ���������

	tree.insert("bubble");
	tree.insert("cat");
	tree.insert("camel");
	tree.insert("CAR");
	tree.insert("cMaKe");
	//printTree(&tree);

	string word;                            // ������ � ������� ������
	auto input = 0;                         // ������� �������� ������

	while ((input = _getch()) != KEY_ESC) { // ������� ������ ���� �� esc
		if (input == KEY_TAB) {             // ���� TAB, �� �������� ��������� �����
			string const completeWord = tree.autoComplete(word); // ���� ����� � �������, ���� ������ ��������� ����� �����
			if (!completeWord.empty()) {    // ���� �����
				word = completeWord;        // �� ������� ������ ���������� ����������� �����
				cout << "\33[2K";
				cout << "\r" << word;
			}
		}
		else if (input == KEY_ENTER) {     // ���� ENTER, ��������� � ����� ������ �����
			tree.insert(word);             // ��������� �������� ������ �������
			word.clear();
			cout << endl;
		}
		else {                            // ����� ����� ������ ������
			if (input == KEY_BACK) {      // ���� BACKSPACE, ������� ���� ������
				if (!word.empty()) {
					word.resize(word.size() - 1);
				}
			}
			else {                        // ����� ������ ������ ��������� � ����� �����
				word.push_back(input);
			}
			cout << "\33[2K";             // �������� ������
			cout << "\r" << word;         // ������� ����� ������. ������ ��� � ���. ��������
		}
	}
	return 0;
}

