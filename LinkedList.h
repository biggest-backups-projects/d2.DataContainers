#pragma once
#include <iostream>
#include <functional>

using namespace std;

namespace DataContainers {
	template<typename type>
	class LinkedList {
	private:
		class Node
		{
		public:
			Node* Next;
			type Data;

			Node(type elem = type(), Node* pNext = nullptr) {
				this->Data = elem;
				this->Next = pNext;
			}
		};

		Node* head;
		unsigned int size;

		Node* NodeAt(int ind, int curr = 0, Node* elem = nullptr);

	public:
		LinkedList() {
			size = 0;
			head = nullptr;
		}

		LinkedList(const LinkedList<type>& _arr) {
			head = nullptr;
			Node* tmp = _arr.head;
			size = 0;
			for (size_t i = 0; i < _arr.Size(); i++) {
				PushBack(tmp->Data);
				tmp = tmp->Next;
			}
		}

		template<typename type>
		LinkedList(const initializer_list<type> _arr) {
			for (size_t i = 0; i < _arr.size(); i++)
				PushFront(*(_arr.end() - i - 1));
		}

		~LinkedList() {
			Сlear();
		}

		void PushBack(const type& elem);
		void PushFront(const type&);
		void Insert(const type&, unsigned int ind);


		void ForEach(const function<void(type&)>& function);
		LinkedList<type> Filter(const function<bool(type)>& function);

		type& operator[](unsigned int ind);

		type PopBack(Node* elem = nullptr);
		type PopFront();
		type Pop(int ind);
		void Remove();


		LinkedList& operator=(const LinkedList<type>& _arr) {
			Node* tmp = _arr.head;
			size = 0;
			for (size_t i = 0; i < _arr.size(); i++) {
				PushBack(tmp->Data);
				tmp = tmp->Next;
			}
			return *this;
		}
		friend ostream& operator<<(ostream&, const LinkedList<type>&);
		type& At(unsigned int ind, unsigned int curr = 0, Node* elem = nullptr);
		unsigned int Size() const;
		bool Empty() const;
		void Сlear();

	};

	template <typename type>
	typename LinkedList<type>::Node* LinkedList<type>::NodeAt(int ind, int curr, Node* elem)
	{
	#ifdef Recurs_func
			if (ind == 0)
				return head;

			if (ind == curr)
				return elem;

			if (elem == nullptr) elem = head;

			if (ind != curr) {
				curr++;
				NodeAt(ind, curr, elem->pNext);
			}
	#else
		int number = 0;
		Node* current = head;

		while (current != nullptr) {
			if (number == ind)
				return current;

			current = current->Next;
			number++;
		}
		return nullptr;
	#endif
	}



	template<typename type>
	type LinkedList<type>::Pop(int ind) {
#ifdef Recurs_func
		if (ind == 0)
			return PopFront();
		else if (pos == 0) elem = head;

		if (ind == pos - 1 || ind == 1) {
			type data = elem->pNext->data;
			Node* tmp = elem->pNext;

			elem->pNext = elem->pNext->pNext;
			size--;
			delete tmp;
			return data;
		}
		else {
			elem = elem->pNext;
			pos++;
			return popR(ind, elem, pos);
		}
#else 
		if (ind == 0) return PopFront();

		Node* interator = head;

		for (size_t i = 0; i < ind - 1; i++)
			interator = interator->Next;

		type data = interator->Next->Data;
		Node* tmp = interator->Next;

		interator->Next = interator->Next->Next;
		size--;
		delete tmp;
		return data;
#endif 
	}

	template <typename type>
	void LinkedList<type>::Remove() {
	}

	template<typename type>
	void LinkedList<type>::Insert(const type& elem, unsigned int ind) {
		assert(ind <= size && "Index out of range");

		if (ind == 0)
			return PushFront(elem);
		if (ind == size - 1)
			return PushBack(elem);

		auto current = NodeAt(ind-1);
		Node* NewElem = new Node(elem, current->Next);
		current->Next = NewElem;
		size++;
	}

	template<typename type>
	void LinkedList<type>::PushBack(const type& elem) {

		if (size == 0) {
			head = new Node(elem, head);
			size++;
			return;
		}
			
		auto current = NodeAt(size - 1);
		Node* NewElem = new Node(elem, current->Next);
		current->Next = NewElem;
		size++;
	}

	template<typename type>
	type LinkedList<type>::PopBack(Node* elem) {
		Node* current = NodeAt(size - 1);
		type data = current->Data;
		current->Next = nullptr;

		delete current;
		size--;
		return data;		
	}

	template<typename type>
	type LinkedList<type>::PopFront() {
		Node* tmp = head;
		type data = tmp->Data;
		head = tmp->Next;
		delete tmp;
		size--;
		return data;
	}

	template<typename type>
	void LinkedList<type>::PushFront(const type& elem)	{
		head = new Node(elem, head);
		size++;
	}

	template<typename type>
	void LinkedList<type>::ForEach(const function<void(type&)>& function) {
		Node* current = head;
		while (current != nullptr) {
			function(current->Data);
			current = current->Next;
		}
	}

	template<typename type>
	LinkedList<type> LinkedList<type>::Filter(const function<bool(type)>& function) {
		auto result = LinkedList<type>();
		Node* current = head;
		while (current != nullptr) {
			if (function(current->Data))
				result.PushBack(current->Data);
			current = current->Next;
		}
		return result;
	}

	template<typename type>
	type& LinkedList<type>::operator[](unsigned int ind) {
		return At(ind);
	}

	template<typename type>
	ostream& operator<< (ostream& out, const LinkedList<type>& d) {
		auto tmp = d.head;

		for (size_t i = 0; i < d.size; i++) {
			out << tmp->Data << " ";
			tmp = tmp->Next;
		}
		out << endl;
		return out;
	}

	template<typename type>
	type& LinkedList<type>::At(unsigned int ind, unsigned int curr, Node* elem) {
		assert(ind <= size && "Index out of range");
#ifdef Recurs_func
		if (ind == 0)
			return head->data;

		if (ind == curr)
			return elem->data;

		if (elem == nullptr) elem = head;

		if (ind != curr) {
			curr++;
			At(ind, curr, elem->pNext);
		}
#else
		int number = 0;
		Node* current = head;

		while (current != nullptr) {
			if (number == ind)
				return current->Data;

			current = current->Next;
			number++;
		}
#endif
	}

	template<typename type>
	unsigned int LinkedList<type>::Size() const { return size; }

	template<typename type>
	void LinkedList<type>::Сlear() {
		while (size != 0)
			PopFront();
	}

	template <typename type>
	bool LinkedList<type>::Empty() const {
		return size == 0;
	}
}
