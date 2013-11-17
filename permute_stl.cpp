#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

using namespace std;

#define COUNT(a) (sizeof(a) / sizeof(a[0]))

struct Incr : public unary_function<void, int>
{
	static int base;
	int operator()(void)
	{
		return base++;
	}
};

int Incr::base = 0;

struct Visitor
{
	virtual void Visit(int *a, int size) const = 0;
};

struct PrintVisitor : public Visitor
{
	PrintVisitor(int *originData) : m_originData(originData)
	{
	}

	void Visit(int *a, int size) const
	{
		for_each(a, a + size, bind1st(TransData(), this));
		cout << endl;
	}

private:
	struct TransData 
		: public binary_function<const PrintVisitor *, int, void>
	{
		void operator()(const PrintVisitor *ptr, int a) const
		{
			if (NULL == ptr)
				return;
			cout << ptr->m_originData[a] << " ";
		}
	};
	int *m_originData;
};


void permute(int size, const Visitor& visitor)
{
	if (size <= 0)
		return;

	int *index = new int[size];
	generate(index, index + size, Incr());

	do
	{
		visitor.Visit(index, size);
	}
	while(next_permutation(index, index + size));

	delete[] index;
}

int main()
{
	int a[] = {2, 2, 6, 7};
	permute(COUNT(a), PrintVisitor(a));
}
