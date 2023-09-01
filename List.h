#pragma once
#include <iostream>
#include <functional>

using namespace std;

namespace DataContainers {

	template<typename type>
	class List {
	private:
		class Node {
		public:
			Node* Previous;
			Node* Next;
			type Data;

			Node() {
				Next = nullptr;
				Previous = nullptr;
			}

			Node(type data) : Node() {
				this->Data = data;
			} 

			Node(Node* previous, Node* next) {
				this->Previous = previous;
				this->Next = next;
			}

			Node(Node* previous, Node* next, type data) : Node(previous, next) {
				this->Data = data;
			}

			~Node() { }

		};

		Node* head;
		Node* tail;
		unsigned int size;

		Node* NodeAt(int ind, unsigned int curr = 0, Node* node = nullptr) {

			assert(ind >= 0 && ind <= size - 1 && "Index out of range");

			if (ind == 0)
				return head;
			if (ind == size - 1)
				return tail;

		#ifdef Recurs_func
			if (curr == ind)
				return node;

			if (node == nullptr) {
				if (size / 2 >= ind) {
					node = head;
					curr = 0;
				}
				else {
					node = tail;
					curr = size - 1;
				}
			}


			if (size / 2 >= ind) {
				node = node->Next;
				curr++;
			}
			else {
				node = node->Previous;
				curr--;
			}

			NodeAt(ind, curr, node);
		#else
			Node* current = nullptr;

			if (size / 2 >= ind) {
				current = this->head;
				for (size_t i = 0; i < ind + 1; i++)
					current = current->Next;
				return current;
			}
			
			current = this->tail;
			for (size_t i = ind; ind != i; i--)
				current = current->Previous;
			
			return current;
		#endif
		}
	public:
		List() {
			this->head = nullptr;
			this->tail = nullptr;
			size = 0;
		}

		List(const List<type>& list) {
			for (unsigned int i = 0; i < list.Size(); i++)
				PushBack(list[i]);
		}

		~List() {
			Clear();
		}

	
		void PushBack(const type& elem);
		void PushFront(const type& elem);
		void Insert(const type& elem, unsigned int ind);

		void ForEach(const function<void(type)>& function);
		List<type> Filter(const function<bool(type)>& predicate);

		type PopBack();
		type PopFront();
		type Pop(unsigned int ind);
		void Remove(unsigned int ind);

		type At(unsigned int ind, unsigned int curr = 0, Node* node = nullptr) const;
		type operator[](int ind) const;
		unsigned int Size() const;
		void Clear();
		bool Empty() const;
	};


	template<typename type>
	void List<type>::PushBack(const type& elem) {

		if (head == nullptr) {
			auto node = new Node(elem);
			head = node;
			size++;
			return;
		}


		//if (tail == nullptr) {
		//	this->tail = new Node(this->head, nullptr, elem);
		//	this->head->Next = tail;
		//	size++;
		//	return;
		//}

		Node* current = (tail == nullptr) ?  head : tail;
		Node* newElem = new Node(current, nullptr, elem);
		current->Next = newElem;
		tail = newElem;

		size++;
	}

	template<typename type>
	void List<type>::PushFront(const type& elem) {
		if (head == nullptr) {
			auto node = new Node(elem);
			head = node;
			size++;
			return;
		}

		Node* current = head;
		Node* newElem = new Node(nullptr, current, elem);

		current->Previous = newElem;
		if (tail == nullptr)
			tail = current;
		head = newElem;

		size++;
	}

	template<typename type>
	void List<type>::Insert(const type& elem, unsigned int ind) {
		assert(ind <= size - 1 && "Index out of range");
		Node* current = NodeAt(ind);

		Node* prev = current->Previous;
		Node* newElem = new Node(prev, current, elem);

		prev->Next = newElem;
		current->Previous = newElem;
	}



	template <typename type>
	void List<type>::ForEach(const function<void(type)>& function) {
		Node* current = head;
		do {
			function(current->Data);
			current = current->Next;
		} while (current != nullptr);
	}

	template <typename type>
	List<type> List<type>::Filter(const function<bool(type)>& predicate) {
		auto result = List<type>();
		if (size == 0)
			return result;

		Node* current = head;
		do {
			if (predicate(current->Data))
				result.PushBack(current->Data);
			current = current->Next;
		} while (current != nullptr);
		return result;

	}

	template<typename type>
	type List<type>::PopBack() {
		assert(size > 0 && "List is empty");
		
		if (size == 1) {
			size--;
			type& data = head->Data;
			head = nullptr;
			return data;
		}

		if (size == 2) {
			size--;
			type& data = tail->Data;
			tail = nullptr;
			head->Next = nullptr;
			return data;
		}

		type& data = tail->Data;

		auto current = tail;
		current = current->Previous;
		current->Next = nullptr;
		tail = current;
		size--;
		
		return data;	
	}

	template<typename type>
	type List<type>::PopFront() {
		assert(size > 0 && "List is empty");
		
		if (size == 1) {
			size--;
			type data = head->Data;
			delete head;
			head = nullptr;
			return data;
		}

		type data = head->Data;
		auto current = head->Next;
		delete head;
		current->Previous = nullptr;
		head = current;
		size--;
		return data;
	}

	template<typename type>
	void List<type>::Remove(unsigned int ind) {
		assert(ind < size && ind >= 0 && "Index out of range");

		Node* current = NodeAt(ind);

		Node* prev = current->Previous;
		Node* next = current->Next;
		

		if(prev != nullptr)
			prev->Next = next;

		if (next != nullptr) 
			next->Previous = prev;
	
		if (ind == size - 1) {
			PopBack();
			return;
		}

		if (ind == 0) {
			PopFront();
			return;
		}
			
		delete current;

		if (size == 1)
			head = nullptr;

		size--;
	}

	template<typename type>
	type List<type>::Pop(unsigned int ind) {
		assert(ind >= 0 && ind <= size - 1 && "Index out of range");
		if (ind == 0)
			return PopFront();
		if(ind == size -1)
			return PopBack();


		Node* current = NodeAt(ind);

		Node* prev = current->Previous;
		Node* next = current->Next;

		if(prev != nullptr)
			prev->Next = next;

		if(next != nullptr)
			next->Previous = prev;

		size--;
		type data = current->Data;
		delete current;
		return data;
	}



	template<typename type>
	type List<type>::At(unsigned int ind, unsigned int curr, Node* node) const {
		assert(ind >= 0 && ind <= size - 1 && "Invalid indition to insert");
	#ifdef Recurs_func

		if (ind == 0)
			return head->Data;
		if (ind == size - 1)
			return tail->Data;

		if (curr == ind)
			return node->Data;

		if (node == nullptr) {
			if (size / 2 >= ind) {
				node = head;
				curr = 0;
			}
			else {
				node = tail;
				curr = size - 1;
			}
		}


		if (size / 2 >= ind) {
			curr++;
			At(ind, curr, node->Next);
		}
		else {
			curr--;
			At(ind, curr, node->Previous);
		}


	#else
		Node* current = nullptr;
		if (size / 2 >= ind) {
			current = head;
			for (size_t i = 0; i < ind; i++)
				current = current->Next;
		}
		else {
			current = tail;

			for (size_t i = size - 1; ind != i; i--)
				current = current->Previous;
		}
		return current->Data;
	#endif
	}

	template<typename type>
	type List<type>::operator[](int ind) const {
		return At(ind);
	}

	template<typename type>
	unsigned int List<type>::Size() const {
		return this->size;
	}

	template<typename type>
	void List<type>::Clear() {
		while (size > 0)
			Remove(0);
	}

	template <typename type>
	bool List<type>::Empty() const {
		return size == 0;
	}
}
