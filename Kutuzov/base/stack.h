#ifndef __STACK_H__
#define __STACK_H__

const size_t MaxStackSize = 100;


template <class T>
class TStack
{
	T* pMem;
	size_t Size;
	int Top;

public:

	// Constructor
	TStack(size_t InSize) : Size(InSize), Top(-1)
	{
		if ((Size < 1) || (Size > MaxStackSize))
			throw std::length_error("Invalid stack size!");

		pMem = new T[Size];
	}

	// Destructor
	~TStack()
	{
		delete[] pMem;
	}

	// Utility functions
	bool empty() { return Top == -1; }
	bool full() { return Top == size() - 1; }
	size_t size() { return Top; }

	// Stack functions
	T& TopElem()
	{
		if (empty())
			throw std::logic_error("Stack empty");

		return pMem[Top];
	}

	void Push(const T& Item)
	{
		if (full())
			throw std::logic_error("Stack overflow ;)");

		pMem[++Top] = Item;
	}

	T Pop()
	{
		if (empty())
			throw std::logic_error("Stack empty");

		return pMem[Top--];
	}

};

#endif
