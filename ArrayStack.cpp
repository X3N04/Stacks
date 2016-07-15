#include <iostream>
template<class ItemType>
class Stack
{
public:
	virtual bool push(const ItemType& data) = 0;
	virtual bool pop() = 0;
	virtual ItemType peek() const = 0;
	virtual bool isEmpty() const = 0;
};
const int MAX_SIZE = 17;
template<class ItemType>
class ArrayStack : public Stack<ItemType>
{
private:
	ItemType items[MAX_SIZE];
	int top;
public:
	ArrayStack();
	bool push(const ItemType& data);
	bool pop();
	ItemType peek() const;
	bool isEmpty() const;
};
template<class ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1)
{
}
// Adds data to top of stack
template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& data)
{
	bool result = false;
	if (top < MAX_SIZE - 1)
	{
		top++;
		items[top] = data;
		result = true;
	}
	return result;
}
// Removes the top of the stack
template<class ItemType>
bool ArrayStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		top--;
		result = true;
	}
	return result;
}
// Returns the top of the stack
template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
	// Up to user to make sure there is data on stack
	return items[top];
}
// Sees if the stack is empty
template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
	return top < 0;
}
int main()
{
	ArrayStack<int> numbers;
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

