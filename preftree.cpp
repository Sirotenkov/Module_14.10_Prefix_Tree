#include "preftree.h"

Node::Node() {
	for (auto i = 0; i < LETTERS; ++i) {
		_children[i] = nullptr; // в начале детей нет поэтому всё ноль
	}
}

Node::~Node() {
	// todo: возможно реализовать удаление детей
}

PrefTree::PrefTree() {

}

PrefTree::~PrefTree() {

}

void PrefTree::insert(string const& word) {
	Node* node = &_root;                      // начинаем с корня (корень просто начало, не буква)

	for (auto ch : word) {                    // пробегаем слово посимвольно
		auto const i = tolower(ch) - 'a';     // находим индекс ребёнка соответствующего символу

		if (node->_children[i] != nullptr) {  // ребёнок уже существует, переходим к нему
			node = node->_children[i];
		}
		else {                                // ребёнок не существует, создаём и переходим к нему
			node->_children[i] = new Node(); 
			node = node->_children[i];
		}
	}
}

Node const* PrefTree::getRoot()const {
	return &_root;
}

string PrefTree::_autoComplete(Node const* node, string searchWord, string completeWord, int depth)const {
	// node текущий узел, depth глубина рекурсии (уровень погружения дерева)
	// searchWord - то, что хотим дополнить, completeWord - то, чем дополняем (результат)

	if (searchWord.size() > depth) { // начинаем здесь (начиная с нулевого уровня)
		// погружаемся вниз по дереву (посимвольно переходим от ребёнка к
		// ребёнку) по той ветке дерева, которая польностью соответствует
		// введённому слову. Если такой ветки нет, возвращается пустая строка.
		// Если ветка совпадает только частично, возвращается совпадающая часть.
		// Если ветка совпадает полностью, тогда переходим в else.
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
		// Опустились на уровень, соответствующий размеру введённой строки.
		// Дальше опускаемся в сторону первого встречного ребёнка.
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
