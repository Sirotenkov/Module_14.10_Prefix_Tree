#include <iostream>
#include <conio.h>
#include "preftree.h"
using namespace std;

// коды клавиш управления, которые возвращает getch
#define KEY_BACK 8
#define KEY_TAB 9
#define KEY_ENTER 13
#define KEY_ESC 27

void printTree(Node const* node, string word = "") {  // отладочная (вспомогательная) функция отображения дерева
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
	PrefTree tree;                          // объект дерева префиксов

	tree.insert("bubble");
	tree.insert("cat");
	tree.insert("camel");
	tree.insert("CAR");
	tree.insert("cMaKe");
	//printTree(&tree);

	string word;                            // строка с текущим словом
	auto input = 0;                         // текущий введённый символ

	while ((input = _getch()) != KEY_ESC) { // считать символ пока не esc
		if (input == KEY_TAB) {             // если TAB, то пытаемся завершить слово
			string const completeWord = tree.autoComplete(word); // ищем слово в словаре, имея только начальную часть слова
			if (!completeWord.empty()) {    // если нашли
				word = completeWord;        // то текущим словом становится дополненное слово
				cout << "\33[2K";
				cout << "\r" << word;
			}
		}
		else if (input == KEY_ENTER) {     // если ENTER, переходим к вводу нового слова
			tree.insert(word);             // сохраняем введённое словов словаре
			word.clear();
			cout << endl;
		}
		else {                            // введён любой другой символ
			if (input == KEY_BACK) {      // если BACKSPACE, стираем один символ
				if (!word.empty()) {
					word.resize(word.size() - 1);
				}
			}
			else {                        // любой другой символ добавляем в конец слова
				word.push_back(input);
			}
			cout << "\33[2K";             // очистить строку
			cout << "\r" << word;         // вывести слово заново. Теперь уже с доп. символом
		}
	}
	return 0;
}

