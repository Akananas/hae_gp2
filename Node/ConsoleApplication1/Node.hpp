#pragma once
class Node {
public:
	float key = 0.0;
	Node* l = nullptr;
	Node* r = nullptr;

	Node(float val) {
		this->key = val;
	};

	~Node() {
		delete l;
		delete r;
	}

	Node* heapify(float newVal) {
		if (newVal < key) {
			Node* nuNode = new Node(newVal);
			nuNode->l = this;
			return nuNode;
		}
		else {
			if (this->l == nullptr) {
				this->l = new Node(newVal);
			}
			else if (this->r == nullptr) {
				this->r = new Node(newVal);
			}
			else {
				this->l = this->l->heapify(newVal);
			}
			return this;
		}
	}
	bool isOk() {
		if (l == nullptr && r == nullptr)
			return true;
		else if (l == nullptr)
			return (r->key >= key) && r->isOk();
		else if (r == nullptr) {
			return l->key >= key && l->isOk();
		}
		else {
			if (key > this->l->key) return false;
			if (key > this->r->key) return false;

			return l->isOk() && r->isOk();
		}
	}

	Node* remove(float val) {
		/*if (val < this->key) {
			return this;
		}
		else if (val == this->key) {
			return this->deleteMin();
		}
		else if (this->r != nullptr && this->r->key == val) {
			this->r = this->r->remove(val);
		}
		else if (this->l != nullptr && (this->l->key == val || this->l->key < this->r->key)) {
			this->l = this->l->remove(val);
		}
		return this;*/
		Node* cur = this;
		if (cur == nullptr || val < cur->key) {
			return cur;
		}
		if (val == cur->key) {
			return cur->deleteMin();
		}else {
			cur->l = cur->l->remove(val);
			cur->r = cur->r->remove(val);
			return cur;
		}
	}

	float getMin() {
		return this->key;
	}

	Node* deleteMin() {
		/*Node* tmpNode = {};
		if (this->l == nullptr && this->r == nullptr) {
			return tmpNode;
		}
		else if (this->l == nullptr) {
			tmpNode = this->r;
		}
		else if (this->r == nullptr) {
			tmpNode = this->l;
		}
		else if (this->l->key < this->r->key) {
			tmpNode = this->l;
			tmpNode = tmpNode->heapify(this->r->key);
		}
		else {
			tmpNode = this->r;
			tmpNode->l = this->l;
		}
		return tmpNode;*/
		Node* l = this->l;
		Node* r = this->r;

		this->l = this->r = nullptr;

		delete this;

		if (l == nullptr) return r;
		if (r == nullptr) return l;

		return Node::merge(l, r);
	}


	static Node* merge(Node* a0, Node* a1);
	static Node* fromTabRec(float* t, int tLen) {
		if (!tLen) return nullptr;
		Node* cur = new Node(t[0]);
		if (tLen > 1) {
			cur = merge(cur, fromTabRec(t + 1, tLen - 1));
		}
		return cur;
	}

};