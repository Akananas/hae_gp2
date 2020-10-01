#include "pch.h"
#include "Node.hpp"

inline Node * Node::
merge(Node * a0, Node * a1) {
	/*while (a1) {
	a0 = a0->heapify(a1->getMin());
	a1 = a1->deleteMin();
	}
	return a0;*/

	if (a1 == nullptr) return a0;
	if (a0 == nullptr) return a0;
	float val = a1->getMin();
	Node* cur = a0;
	cur = cur->heapify(val);

	Node* l = a1->l;
	Node* r = a1->r;

	a1->l = nullptr;
	a1->r = nullptr;

	delete a1;

	cur = merge(cur, l);
	cur = merge(cur, r);

	return cur;

	/*if (a1 == nullptr) return a0;
	a0 = a0->heapify(a1->getMin());
	a1 = a1->deleteMin();
	a0 = a0->merge(a0, a1->r);
	a0 = a0->merge(a0, a1->l);
	return a0;
	*/

}
