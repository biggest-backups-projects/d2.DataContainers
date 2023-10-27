#pragma once
#include <type_traits>
#include <iostream>
#include <queue>
#include <format>
#include "Vector.h"
#include <functional>
using namespace std;
namespace DataContainers {
	template<typename keyType, typename valueType, typename = std::enable_if_t<std::is_arithmetic_v<keyType>>>
	class Pair
	{
	public:
		keyType Key;
		valueType Value;

		Pair(const keyType& key, const valueType& value) {
			this->Key = key;	
			this->Value = value;
		}

		Pair() { }
	};

	template<typename keyType, typename valueType>
	class Dictionary {
	private:
		class Node {
		public:
			Node* Left;
			Node* Right;
			Node* Parent;
			uint32_t Height;
			Pair<keyType, valueType> Data;

			Node() {
				Left = nullptr;
				Right = nullptr;
				Parent = nullptr;
				Height = 0;
			}

			Node(Pair<keyType, valueType> data, Node* parent = nullptr) : Node() {
				Data = data;
				Parent = parent;
			}

			void UpdateHeight(Node* node = nullptr) {
				if (node == nullptr)
					node = this;

				int leftHeight = GetHeight(node->Left);
				int rightHeight = GetHeight(node->Right);

				if (leftHeight > rightHeight)
					node->Height = leftHeight + 1;
				else
					node->Height = rightHeight + 1;

				if (node->Parent != nullptr)
					UpdateHeight(node->Parent);
	
				Balance(node);
			}

			int GetHeight(Node* node) {
				return node == nullptr ? -1 : node->Height;
			}

			int GetBalance() {
				int leftHeight = GetHeight(Left);
				int rightHeight = GetHeight(Right);

				return  rightHeight - leftHeight;
			}

			static void Swap(Node* first, Node*second) {
				std::swap(first->Data, second->Data);
				std::swap(first->Height, second->Height);
			}

			void RightRotate(Node* node = nullptr) {
				if (!node)
					node = this;

				Node::Swap(node, node->Left);
				auto nodeRight = node->Right;

				node->Right = node->Left;
				node->Right->Parent = node;

				node->Left = node->Right->Left;
				if (node->Left != nullptr)
					node->Left->Parent = node;

				node->Right->Left = node->Right->Right;
				node->Right->Right = nodeRight;

				if (node->Right->Right != nullptr)
					node->Right->Right->Parent = node->Right;

			/*	if(node->Right->Right != nullptr)
					node->Right->Right->UpdateHeight();*/

				if (node->Right != nullptr)
					node->Right->UpdateHeight();

				/*if(node->Right->Left != nullptr)
					node->Right->Left->UpdateHeight();*/
	
				
			}

			void LeftRotate(Node* node = nullptr) {
				if (!node)
					node = this;

				Node::Swap(node, node->Right);
				auto nodeRight = node->Left;

				node->Left = node->Right;
				node->Left->Parent = node;

				node->Right = node->Left->Right;
				if(node->Right != nullptr)
					node->Right->Parent = node;
				 
				node->Left->Right = node->Left->Left;
				node->Left->Left = nodeRight;

				if (node->Left->Left != nullptr)
					node->Left->Left->Parent = node->Left;

				if (node->Left != nullptr)
					node->Left->UpdateHeight();
			}

			void Balance(Node* node = nullptr) {
				if (!node)
					node = this;
				const int balance = node->GetBalance();
				if(balance <= -2) {
					if (node->Left->GetBalance() == 1)
						node->Left->LeftRotate();
					node->RightRotate();
					
				}else if(balance >= 2) {
					if (node->Right->GetBalance() == -1)
						node->Right->RightRotate();

					node->LeftRotate();
				}
				
			}

			
		};

		Node* root;
		uint32_t size;
	
		Node* GetMin(Node* node = nullptr) {
			if (!node)
				node = root;
			if (!node->Left)
				return node;
			return GetMin(node->Left);
		}

		Node* GetMax(Node* node = nullptr) {
			if (!node)
				node = root;
			if (!node->Right)
				return node;
			return GetMax(node->Right);
		}

		void filter(Vector<Pair<keyType, valueType>>& vector,
					const function<bool(Pair<keyType, valueType>)>& predicate,
					Node* node = nullptr) {
			if (!node)
				node = root;

			if (node->Left)
				filter(vector, predicate, node->Left);

			if (predicate(node->Data))
				vector.PushBack(node->Data);

			if (node->Right)
				filter(vector, predicate, node->Right);
		}

		void forEach(Vector<keyType>& vector, Node* node = nullptr) const {
			if (!node)
				node = root;

			if (node->Left)
				forEach(vector, node->Left);

			vector.PushBack(node->Data.Key);

			if (node->Right)
				forEach(vector, node->Right);
		}
	public:
		class DictionaryIterator {
		private:
			Vector<Node*> nodes;

			void searchNodes(Vector<Node*>& vector, Node* node) const {
				if(node == nullptr)
					return;

				if (node->Left)
					searchNodes(vector, node->Left);

				vector.PushBack(node);

				if (node->Right)
					searchNodes(vector, node->Right);
			}

		public:
			uint32_t position;

			DictionaryIterator(Node* head) {
				searchNodes(nodes, head);
				position = 0;
			}

			DictionaryIterator(uint32_t size) {
				position = size;
			}

			void operator++() {
				position += 1;
			}

			bool operator!=(const DictionaryIterator& iterator) const {
				return position != iterator.position;
			}

			Pair<keyType, valueType>& operator*() {
				return nodes[position]->Data;
			}
		};

		Dictionary() {
			root = nullptr;
			size = 0;
		}
		~Dictionary() {
			Clear();
		}

		void Insert(keyType key, valueType value, Node* node = nullptr) {
			if(!root) {
				Node* newNode = new Node(Pair<keyType, valueType>(key, value));
				root = newNode;
				size++;
				return;
			}

			if (node == nullptr)
				node = root;

			if(key < node->Data.Key) {
				if (node->Left == nullptr) {
					node->Left = new Node(Pair<keyType, valueType>(key, value), node);
					node->Left->UpdateHeight();
					size++;
				}
				else
					return Insert(key, value, node->Left);
			}
			else {
				if (node->Right == nullptr) {
					node->Right = new Node(Pair<keyType, valueType>(key, value), node);
					node->Right->UpdateHeight();
					size++;


				}
				else
					return Insert(key, value, node->Right);
			}
		}

		void Delete(const keyType& key, Node* node = nullptr) {
			if (!node)
				node = root;

			if (key < node->Data.Key)
				Delete(key, node->Left);
			else if (key > node->Data.Key)
				Delete(key, node->Right);
			else {
				if (node->Left != nullptr && node->Right != nullptr) {
					Node* maxLeft = GetMax(node->Left);

					auto parent = maxLeft->Parent;
	
					if (parent->Left == node || parent->Left == maxLeft)
						parent->Left = nullptr;
					else
						node->Left->Parent = maxLeft;

					if (parent->Right == node || parent->Right == maxLeft)
						parent->Right = nullptr;
					else
						node->Right->Parent = maxLeft;

					maxLeft->Parent = node->Parent;
					maxLeft->Right = node->Right;
					maxLeft->Left = node->Left;
					maxLeft->Height = node->Height;

					if (node == root)
						return;

					if(node->Parent->Left == node)
						node->Parent->Left = maxLeft;
					else
						node->Parent->Right = maxLeft;

					if(parent != node)
						parent->UpdateHeight();

					delete node;

				}
				else {
					auto child
							= (node->Left == nullptr) ? node->Right : node->Left;

					if(child == nullptr) {
						if(node->Parent == nullptr) {
							delete node;
							return;
						}

						if(node->Parent->Right == node)
							node->Parent->Right = nullptr;
						else
							node->Parent->Left = nullptr;

						node->Parent->UpdateHeight();
						delete node;
						node = nullptr;
					}
					else {
						child->Parent = node->Parent;
						child->Height = node->Height;
						if(node->Parent != nullptr) {
							if (node->Parent->Right == node)
								node->Parent->Right = child;
							else
								node->Parent->Left = child;
						}
						if(node == root)
							root = child;

						child->UpdateHeight();
						delete node;
					}
				}
				size--;
			}
			
		}

		void Clear(Node* node = nullptr) {
			if (!node)
				node = root;

			if(node->Left != nullptr)
				Clear(node->Left);

			if(node->Right != nullptr)
				Clear(node->Right);

			Delete(node->Data.Key, node);
		}

		void PrintFormat(const Node* node = nullptr) {
			if (!node)
				node = this->root;

			uint32_t spacing = 3;
			std::queue<Node*> treeLevel, temp;
			treeLevel.push(node);
			int counter = 0;
			int height = node->Height+1;

			//double elementsCount = pow(2, (height + 1)) - 1;
			int elementsCount = this->size+spacing;

			while (counter <= height) {
				Node* removed = treeLevel.front();
				treeLevel.pop();

				if (temp.empty()) {
					printSpace(elementsCount / pow(2, counter + 1),
						removed);
				}
				else {
					printSpace(elementsCount / pow(2, counter),
						removed);
				}

				if (removed == nullptr) {
					temp.push(nullptr);
					temp.push(nullptr);
				}
				else {
					temp.push(removed->Left);
					temp.push(removed->Right);
				}

				if (treeLevel.empty()) {
					std::cout << std::endl << std::endl;
					treeLevel = temp;
					while (!temp.empty())
						temp.pop();
					
					counter++;
				}
			}
		}

		void ForEach(const std::function<void(valueType& i)>& function, Node* node = nullptr) {
			if (!node)
				node = root;

			if(node->Left != nullptr)
				ForEach(function, node->Left);

			function(node->Data.Value);

			if(node->Right != nullptr)
				ForEach(function, node->Right);
		}

		Vector<Pair<keyType, valueType>> Filter(const std::function<bool(Pair<keyType, valueType>)>& predicate) const {
			auto result = Vector<Pair<keyType, valueType>>(size);
			filter(result, predicate, root);
			return result;
		}

		uint32_t len() const {
			return size;
		}

		Vector<keyType> Keys() const {
			auto result = Vector<keyType>(size);
			forEach(result, root);
			return result;
			
		}

		bool Contains(const keyType& key, Node* node = nullptr) const {
			if (!node)
				node = root;

			if(key == node->Data.Key)
				return true;

			if (node->Left && Contains(key, node->Left))
				return true;

			if (node->Right && Contains(key, node->Right))
				return true;

			return false;

		}

		valueType& At(const keyType& key, Node* node = nullptr) {
			if (node == nullptr)
				node = root;
			if (key == node->Data.Key)
				return node->Data.Value;
	
			if (key < node->Data.Key)
				return At(key, node->Left);
			if (node->Right)
				return At(key, node->Right);
			throw std::invalid_argument("invalid key");
		

		}

		valueType& operator[](keyType key) {
			return At(key);
		}   

		DictionaryIterator begin() const {
			return root;
		}

		DictionaryIterator end() const {
			return size;
		}
	};
}

		