/*	
	Напишите модуль, реализующий двусвязный список элементов типа string в стиле
	модуля Stack из 2.4. Проверьте его на списке названий языков программирования.
	Реализуйте функцию sort() для этого списка и функцию, изменяющую порядок
	элементов списка на обратный.
*/

// TODO 
// sort function


#include <iostream>
#include <string>
#include <algorithm>

#define EVER ;;

namespace List {
	void add(const std::string&);

	void sort();
	void reverse();

	void print();
	void destroy();
}

void init() {
	List::add("Python");
	List::add("C++");
	List::add("PHP");
	List::add("Assembler");
	List::add("Pascal");
}


int main() {
	init();
	List::print();
	std::cout << "_______reverse______\n";
	List::reverse();
	List::print();
	std::cout << "________sort________\n";
	List::sort();
	List::print();
	List::destroy();
	return 0;
}

namespace List {

	struct Node {
	public:
		Node(const std::string& name, Node* p = 0, Node* n = 0) : v(name), prv(p), nxt(n) {}
		~Node() {
			if (nxt) delete nxt;
		}
		void add(const std::string& name) {
			if (nxt) nxt->add(name);
			else nxt = new Node(name, this);
		}
		std::string v;
		Node* prv;
		Node* nxt;
	};

	Node * root = 0;

	void add(const std::string& name) {
		if (root) root->add(name);
		else root = new Node(name);
	}


	void print() {
		for (Node* cur = root; cur != 0; cur = cur->nxt) {
			std::cout << cur->v << "\n";
		}
	}

	void reverse() {
		for (Node *cur = root, *tmp = 0; cur != 0; root = cur, cur = cur->prv ) {
			tmp = cur->prv;
			cur->prv = cur->nxt;
			cur->nxt = tmp;
		}
	}

	void sort() {
		Node * left;
		Node * rigth;
		std::string min = (root) ? root->v : "";
		for (Node* cur = root; cur != 0; cur = rigth) {
			rigth = cur->nxt;
			if (cur->nxt != 0) {
				if ( cur->v > cur->nxt->v ) {
					rigth->prv = cur->prv;
					cur->prv = rigth;
					cur->nxt = rigth->nxt;
					rigth->nxt = cur;
				}
			}
			left = cur->prv;
			if (cur->prv != 0) {
				if (cur->v < cur->prv->v) {
					cur->prv = left->prv;
					left->prv = cur; 
					left->nxt = cur->nxt;
					cur->nxt = left;
				}
			}
			if (cur->v < min) {
				root = cur;
			}
		}
	}

	void destroy() {
		if (root) delete root;
	}
}