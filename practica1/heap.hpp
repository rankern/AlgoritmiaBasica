#pragma once
const int MAX = 100000;
template <typename T>
class Heap{
	int tam = 0;
	T elementos[MAX];

	public:
		Heap();
		bool isEmpty();
		int tamanyo();
		void add(T e);
		T pop();
		
};