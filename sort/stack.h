#pragma once
#include <iostream>
using namespace std;

struct Node {
	int l, r;
	Node* next;
	Node* operator = (Node* x) {
		l = x->l;
		r = x->r;
		next = x->next;
		return this;
	}
};

struct Stack {
	Node* Top;

	void Init() {
		Top = nullptr;
	}

	bool isEmpty() {
		return Top == nullptr;
	}

	bool Push(int l, int r) {
		Node* x = new Node();
		x->l = l; x->r = r;

		if (this->isEmpty()) {
			Top = x;
			Top->next = nullptr;
			return true;
		}
		x->next = Top;
		Top = x;
		return true;
	}

	Node* Pop() {
		if (this->isEmpty())
			return nullptr;

		Node* result = Top;
		Top = Top->next;
		return result;
	}

	int Length() {

		int cnt = 0;

		if (this->isEmpty()) {
			return 0;
		}
		Node* t = this->Top;
		while (t != nullptr) {
			cnt++;
			t = t->next;
		}
		return cnt;
	}

	void PrintStack() {
		if (this->isEmpty()) {
			cout << "Empty\n";
			return;
		}
		Node* t = this->Top;
		while (t != nullptr) {
			cout << t->l << " " << t->r << endl;
			t = t->next;
		}
	}

	void Free() {
		while (Top != nullptr) {
			Node* t = Top;
			*Top = Top->next;
			free(t);
		}
	}
};
