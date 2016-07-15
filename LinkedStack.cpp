#include <iostream>
#include <cstddef>
#include <cassert>
template<class ItemType>
class Stack
{
public:
	virtual bool push(const ItemType& data) = 0;
	virtual bool pop() = 0;
	virtual ItemType peek() const = 0;
	virtual bool isEmpty() const = 0;
};
template<class ItemType>
class Node
{
private:
	ItemType item;
	Node<ItemType>* next;
public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
	void setItem(const ItemType& anItem);
	void setNext(Node<ItemType>* nextNodePtr);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
};
/*NODE CPP*/
template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
}
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
}
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
		item(anItem), next(nextNodePtr)
{
}
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
}
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
	next = nextNodePtr;
}
template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
}
template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
}
template<class ItemType>
class LinkedStack : public Stack<ItemType>
{
private:
	Node<ItemType>* topPtr;
public:
	LinkedStack();
	LinkedStack(const LinkedStack<ItemType>& aStack);
	virtual ~LinkedStack();
	bool push(const ItemType& newItem);
	bool pop();
	ItemType peek() const;
	bool isEmpty() const;
};
template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
}
template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
	Node<ItemType>* origChainPtr = aStack->topPtr;
	if (origChainPtr == nullptr)
		topPtr = nullptr;
	else
	{
		topPtr = new Node<ItemType>();
		topPtr->setItem(origChainPtr->getItem());
		Node<ItemType>* newChainPtr = topPtr;
		while (origChainPtr != nullptr)
		{
			origChainPtr = origChainPtr->getNext();
			ItemType nextItem = origChainPtr->getItem();
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}
template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	while (!isEmpty())
		pop();
}
template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;
	return true;
}
template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		Node<ItemType>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		result = true;
	}
	return result;
}
template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
	assert(!isEmpty());
	return topPtr->getItem();
}
template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return topPtr == nullptr;
}

#if 0 // #if 1 to compile as a standalone program, not a library
int main()
{
	LinkedStack<int> numbers;
	int command, key;
	bool more = true;
	while (more)
	{
		std::cout << "1)Add data\n2)Remove data\n"
		<< "3)Check top of stack\n4)Clear stack\n"
		<< "Enter choice (anything else quits): " << std::flush;
		std::cin >> command;
		switch (command)
		{
		case 1:
			std::cout << "Enter key : " << std::flush;
			std::cin >> key;
			numbers.push(key);
			break;
		case 2:
			numbers.pop();
			break;
		case 3:
			if (!numbers.isEmpty()) std::cout << numbers.peek() << std::endl;
			else std::cout << "Stack is empty!" << std::endl;
			break;
		case 4:
			while (numbers.pop());
			break;
		default:
			more = false;
		}
	}
	return 0;
}
#endif
