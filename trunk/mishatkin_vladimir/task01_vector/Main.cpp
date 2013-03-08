//#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#define _DEBUG_CAPACITY_MULTIPLYING
#define _DEBUG_GVECTOR_EXCEPTIONS
#define _TEST_MEMORY_LEAK

using namespace std;


static const string kCExceptionDefaultOperation = "Unknown operation";
static const string kCExceptionDefaultReason = "Unknown reason";

class CException
{
protected:
	string _reason;
	string _operation;
	const void *_source;
public:
	CException()
	{
		_reason = kCExceptionDefaultReason;
		_operation = kCExceptionDefaultOperation;
	}
	CException(string aReason, const void *aSource = NULL, string anOperation = kCExceptionDefaultOperation)
	{
		_reason = aReason;
		_source = aSource;
		_operation = anOperation;
	}
	string reason() const
	{
		return _reason;
	}
	string sourceDescription()
	{
		return _operation;
	}
	const void *source()
	{
		return _source;
	}
};


class COutOfRangeException : public CException
{
private:
	int _lowerBoundIndex;
	int _upperBoundIndex;
	int _errorIndex;
public:
	COutOfRangeException()
	{
		_lowerBoundIndex = _upperBoundIndex = _errorIndex = 0;
	}
	COutOfRangeException(int fromIndex, int toIndex, int calledIndex, const void *aSource = NULL, string performedOperation = kCExceptionDefaultOperation) :
							_lowerBoundIndex(fromIndex), _upperBoundIndex(toIndex), _errorIndex(calledIndex)
	{
		_reason = "Out of range";
		_operation = performedOperation;
		_source = aSource;
	}
	int lowerBoundIndex()
	{
		return _lowerBoundIndex;
	}
	int upperBoundIndex()
	{
		return _upperBoundIndex;
	}
	int errorIndex()
	{
		return _errorIndex;
	}
};


template <typename T>
class CIterator
{
friend class CIterator;
private:
	T *m_pObject;
public:
	CIterator() : m_pObject(NULL) {}

	CIterator(T *mem) : m_pObject(mem) {}
	CIterator(const T *mem) : m_pObject((T*)mem) {}

//	CIterator(CIterator& sample) : m_pObject(sample.m_pObject) {}
//	CIterator(const CIterator& sample) : m_pObject(sample.m_pObject){}

	//	prefix
	CIterator &operator ++()
	{
		++m_pObject;
		return *this;
	}

	CIterator &operator --()
	{
		--m_pObject;
		return *this;
	}

	//	postfix
	CIterator &operator ++(int)
	{
		CIterator retValue = *this;
		m_pObject++;
		return retValue;
	}

	CIterator &operator --(int)
	{
		CIterator retValue = *this;
		m_pObject--;
		return retValue;
	}

	int operator -(const CIterator &target)
	{
		return (int)(m_pObject - target.m_pObject);
	}

	CIterator &operator -(int leftShift)
	{
		CIterator retValue = *this;
		retValue.m_pObject -= leftShift;
		return retValue;
	}

	CIterator &operator +(int rightShift)
	{
		CIterator retValue = *this;
		retValue.m_pObject += rightShift;
		return retValue;
	}

	T& operator *()
	{
		return *m_pObject;
	}

	bool operator ==(CIterator &target)
	{
		return m_pObject == target.m_pObject;
	}

	bool operator !=(CIterator &target)
	{
		return m_pObject != target.m_pObject;
	}

	bool operator <(const CIterator &target)
	{
		return m_pObject < target.m_pObject;
	}
	
	bool operator >(const CIterator &target)
	{
		return m_pObject > target.m_pObject;
	}

};

template <typename T>
class GVector;

template <typename T>
class IVector
{
public:
//	typedef T * iterator;
	typedef CIterator<T> iterator;
	typedef const iterator const_iterator;

	virtual size_t size() const = 0;
	virtual bool empty() const = 0;
	virtual void clear() = 0;
	virtual void swap(GVector<T>& target) = 0;
	virtual void resize(size_t requestedSize) = 0;
	virtual size_t capacity() const = 0;
	virtual void reserve(size_t requestedCapacity) = 0;
	virtual iterator begin() const = 0;
	virtual iterator end() const = 0;
	virtual T& operator [] (size_t index) const = 0;
	virtual T& front() const = 0;
	virtual T& back() const = 0;
	virtual void push_front(const T& object) = 0;
	virtual void push_back(const T& object) = 0;
	virtual void pop_back() = 0;
	virtual void insert(iterator position, iterator fromIterator, iterator toIterator) = 0;
	virtual iterator insert(iterator position, iterator targetIterator) = 0;
	virtual iterator erase(iterator fromIterator, iterator toIterator) = 0;
	virtual iterator erase(iterator targetIterator) = 0;
};


#ifdef _TEST_MEMORY_LEAK
static int gvectorCounter = 0;
#endif

void gvectorWasCreated()
{
#ifdef _TEST_MEMORY_LEAK
	++gvectorCounter;
#endif
}
void gvectorWasDestroyed()
{
#ifdef _TEST_MEMORY_LEAK
	--gvectorCounter;
	assert(gvectorCounter >= 0);
#endif
}

#define self (*this)

template <typename T>
class GVector : public IVector<T>
{
private:
	size_t m_nSize;
	size_t m_nCapacity;
#ifdef _DEBUG_CAPACITY_MULTIPLYING
	double m_fCapacityFactor;
#endif
	T *m_pData;
public:

	GVector() : m_nSize(0), m_nCapacity(1),
#ifdef _DEBUG_CAPACITY_MULTIPLYING
				m_fCapacityFactor(2.0),
#endif
				m_pData(NULL)
	{
		gvectorWasCreated();
	}

	GVector(size_t size) : m_nSize(size), m_nCapacity(m_nSize)
#ifdef _DEBUG_CAPACITY_MULTIPLYING
						,m_fCapacityFactor(2.0)
#endif
	{
		m_pData = new T[m_nCapacity];
		for (iterator it = begin(); it != end(); ++it)
			*it = 0;
		gvectorWasCreated();
	}

	GVector(GVector& const sample) : m_nSize(sample.size()), m_nCapacity(sample.capacity())
#ifdef _DEBUG_CAPACITY_MULTIPLYING
									, m_fCapacityFactor(2.0)
#endif
	{
		m_pData = new T[m_nSize];
		memcpy(m_pData, sample.m_pData, m_nSize * sizeof(T));
		gvectorWasCreated();
	}

	virtual ~GVector()
	{
		if (!m_pData)
			delete[] m_pData;
		gvectorWasDestroyed();
	}

	virtual size_t size() const
	{
		return m_nSize;
	}

	virtual bool empty() const
	{
		return m_nSize == 0;
	}

	virtual void clear()
	{
		m_nSize = 0;
	}

	virtual void swap(GVector& target)
	{
		GVector temporary = *this;
		*this = target;
		target = temporary;
	}

	virtual void resize(size_t requestedSize)
	{
		if (m_nSize == requestedSize)
			return;
		if (m_nSize < requestedSize)
		{
			reserve(requestedSize);
			size_t oldSize = m_nSize;
			m_nSize = requestedSize;
			for (iterator it = m_pData + oldSize; it < m_pData + requestedSize; ++it)
				*it = 0;
		}
		else
			m_nSize = requestedSize;
	}

	virtual size_t capacity() const
	{
		return m_nCapacity;
	}

	virtual void reserve(size_t requestedCapacity)
	{
		if (!m_pData || requestedCapacity > m_nCapacity)
		{
#ifdef _DEBUG_CAPACITY_MULTIPLYING
			while (m_nCapacity < requestedCapacity)
				m_nCapacity = (int)(m_fCapacityFactor * (m_nCapacity) + 1);
#endif
#ifndef _DEBUG_CAPACITY_MULTIPLYING
			m_nCapacity = requestedCapacity;
#endif
			T *newData = new T[m_nCapacity];

			if (m_pData)
			{
				//	what happens here, if the receiver suddenly contains an instanse of a subclass of T that would probbably require more memory to be stored in?
				memcpy(newData, m_pData, sizeof(T) * m_nSize);
				delete[] m_pData;
			}
			m_pData = newData;
		}
	}

	virtual iterator begin() const
	{
		return iterator(m_pData);
	}

	virtual iterator end() const
	{
		return iterator(m_pData + m_nSize);
	}

	virtual T& operator [] (size_t index) const
	{
		if (index >= 0 && index < m_nSize)
			return *(m_pData + index);
#ifdef _DEBUG_GVECTOR_EXCEPTIONS
		throw new COutOfRangeException(0, (m_nSize - 1 > 0 ? m_nSize - 1 : 0), index, this, "Access by index vector operation");
#endif
#ifndef _DEBUG_GVECTOR_EXCEPTIONS
		assert(index >= 0 && index < m_nSize);	//	which would be false
#endif
	}

	virtual T& front() const
	{
#ifndef _DEBUG_GVECTOR_EXCEPTIONS
		if (m_nSize >= 0)
#endif
			return (*begin());
	}

	virtual T& back() const
	{
#ifndef _DEBUG_GVECTOR_EXCEPTIONS
		if (m_nSize > 0)
#endif
			return m_pData[m_nSize - 1];
	}

	virtual void push_front(const T& object)
	{
		if (!m_pData)
			this->reserve((size_t)1);
		
		insert(begin(), iterator(&object));
	}

	virtual void push_back(const T& object)
	{
		if (!m_pData)
			this->reserve((size_t)1);
		insert(end(), (iterator)&object);
	}

	virtual void pop_back()
	{
		if (m_nSize)
			--m_nSize;
	}

//	segment insertion
	virtual void insert(iterator position, iterator fromIterator, iterator toIterator)	//	[from, to)
	{
		if (fromIterator > toIterator)
		{
			insert(position, toIterator, fromIterator);
			return;
		}
#ifdef _DEBUG_GVECTOR_EXCEPTIONS
		if (position < begin() || position > end())
			throw new COutOfRangeException(0, (m_nSize - 1 > 0 ? m_nSize - 1 : 0), position - begin(), this, "Insert at index vector operation");
#endif
		size_t segmentSize = (toIterator - fromIterator);
		size_t indexToInsert = position - begin();
		size_t oldCapacity = m_nCapacity;
		this->resize(m_nSize + segmentSize);
		if (m_nCapacity != oldCapacity)
			position = m_pData + indexToInsert;
		//	shifting
		for (iterator followingIterator = &this->back(); followingIterator > position + segmentSize - 1; --followingIterator)
		{
			*followingIterator = *(followingIterator - segmentSize);
		}
		//	inserting
		size_t iterationNumber = 0;
		for (iterator item = fromIterator; item != toIterator; ++item, ++iterationNumber)
		{
			iterator newIterator = (position + iterationNumber);
			*newIterator = *item;
		}
	}

//	single element insertion
	virtual iterator insert(iterator position, iterator targetIterator)
	{
		insert(position, targetIterator, targetIterator + 1);
		return position;
	}

	virtual iterator erase(iterator fromIterator, iterator toIterator)	//	[from, to)
	{
		if (fromIterator > toIterator)
		{
			return erase(toIterator, fromIterator);
		}
#ifdef _DEBUG_GVECTOR_EXCEPTIONS
		int errorIndex;
		if (fromIterator < begin()	|| toIterator > end())
		{
			errorIndex = (fromIterator < begin()) ? fromIterator - begin() : toIterator - begin();
			throw new COutOfRangeException(0, (m_nSize - 1 > 0 ? m_nSize - 1 : 0), errorIndex, this, "Erase by iterator vector operation");
		}
#endif
		size_t segmentSize = (toIterator - fromIterator);

		for (iterator leftShifted = fromIterator; leftShifted != toIterator; ++leftShifted)
		{
			iterator newIterator = leftShifted + segmentSize;
			*leftShifted = *newIterator;
		}
		m_nSize -= segmentSize;
		return fromIterator;
	}

	virtual iterator erase(iterator targetIterator)
	{
		return erase(targetIterator, targetIterator + 1);
	}

	void printContentTo(ostream *out)
	{
		for (iterator it = begin(); it != end(); ++it)
		{
			if (it != begin())
				*out << " ";
			*out << *it;
		}
		*out << endl;
	}
};

void launchGVectorTests()
{
	GVector<int> items(2);
	cout << "Content: "; items.printContentTo(&cout);
	cout << "Size: " << items.size() << "\n";
	cout << "Empty: " << (items.empty() ? "YES" : "NO") << "\n";
	items.clear();
	cout << "clear() -ed vector\n";
	cout << "Empty: " << (items.empty() ? "YES" : "NO") << "\n";
	GVector<int> secondary;
	items.push_back(1);
	secondary.push_back(2);
	secondary.push_back(3);
	cout << "push_back test:\n\tfirst vector: ";
	items.printContentTo(&cout); cout << "\tsecond vector: "; secondary.printContentTo(&cout);
	cout << "swap:\n\tfirst vector: ";
	items.swap(secondary);
	items.printContentTo(&cout); cout << "\tsecond vector: "; secondary.printContentTo(&cout);
	cout << "resize to 1: "; items.resize(1); items.printContentTo(&cout);
	cout << "resize to 5: "; items.resize(5); items.printContentTo(&cout);
	cout << "capacity(): " << items.capacity() << "\n";
	cout << "reserve 50: "; items.reserve(50); items.printContentTo(&cout);
	cout << "capacity(): " << items.capacity() << "\n";
	cout << "pop_back() once: "; items.pop_back(); items.printContentTo(&cout);
	int a = 202;
	cout << "insert 202 after 2nd element: "; items.insert(&items[2], &a); items.printContentTo(&cout);
	cout << "set 4th element to 7 using operator []: "; items[3] = 7; items.printContentTo(&cout);
	cout << "back(): " << items.back() << "\n";
	cout << "front(): " << items.front() << "\n";
	cout << "erase() the 7: "; items.erase(&items[3]); items.printContentTo(&cout);
	cout << "Assign operator test: "; GVector<int> newVector = items; newVector.printContentTo(&cout);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	launchGVectorTests();
#ifdef _TEST_MEMORY_LEAK
	assert(gvectorCounter == 0);	//	mem leak check
#endif
	return EXIT_SUCCESS;
}
