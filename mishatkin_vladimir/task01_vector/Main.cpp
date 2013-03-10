//#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <iostream>
#include <string>
#include <stdlib.h>

#define _DEBUG_CAPACITY_MULTIPLYING
#define _DEBUG_GVECTOR_EXCEPTIONS
#define _TEST_MEMORY_LEAK

using namespace std;

#define self (*this)
#define YES 1
#define NO 0

static const string kCExceptionDefaultOperation = "Unknown operation";
static const string kCExceptionDefaultReason = "Unknown reason";

class Object
{
protected:
	virtual string _internalDescription()
	{
		char *c_strDescription = (char *)malloc(1000);
		sprintf(c_strDescription, "0x%x: %s", (unsigned int)this, getClassName().c_str());
		string retValue = string(c_strDescription);
		free(c_strDescription);
		return retValue;
	}

public:
	virtual string getClassName()
	{
		return "Object";
	}
	string description()
	{
		return "<" + _internalDescription() + ">\n";
	}
};

class CException : public Object
{
private:
        string _reason;
        string _operation;
        Object *_source;

protected:
	virtual string _internalDescription()
	{
		char *c_strDescription = (char *)malloc(2000);
		sprintf(c_strDescription, "\n\treason = %s\n\toperation = %s\n\tsource = %s",
									reason().c_str(), operation().c_str(), source()->description().c_str());
		string retValue = Object::_internalDescription() + string(c_strDescription);
		free(c_strDescription);
		return retValue;
	}

public:
	virtual string getClassName()
	{
		return "CException";
	}
        CException()
        {
			
                _reason = kCExceptionDefaultReason;
                _operation = kCExceptionDefaultOperation;
        }
        CException(string aReason, Object *aSource = NULL, string anOperation = kCExceptionDefaultOperation)
        {
                _reason = aReason;
                _source = aSource;
                _operation = anOperation;
        }
		virtual ~CException() {}
        string reason() const
        {
                return _reason;
        }
		void setReason(string aReason)
		{
			_reason = aReason;
		}
        string operation() const
        {
                return _operation;
        }
		void setOperation(string anOperation)
		{
			_operation = anOperation;
		}
        Object *source() const
        {
			return _source;
        }
		void setSource(Object *aSource)
		{
			_source = aSource;
		}
};


class COutOfRangeException : public CException
{
private:
        int _lowerBoundIndex;
        int _upperBoundIndex;
        int _errorIndex;

protected:
	virtual string _internalDescription()
	{
		char *c_strDescription = (char *)malloc(2000);
		sprintf(c_strDescription, "\n\trange = [%d, %d]\n\trequested index = %d",
									lowerBoundIndex(), upperBoundIndex(), errorIndex());
		string retValue = CException::_internalDescription() + string(c_strDescription);
		free(c_strDescription);
		return retValue;
	}

public:
	virtual string getClassName()
	{
		return "COutOfRangeException";
	}
        COutOfRangeException()
        {
                _lowerBoundIndex = _upperBoundIndex = _errorIndex = 0;
        }
        COutOfRangeException(int fromIndex, int toIndex, int calledIndex, Object *aSource = NULL, string performedOperation = kCExceptionDefaultOperation) :
                                                        _lowerBoundIndex(fromIndex), _upperBoundIndex(toIndex), _errorIndex(calledIndex)
        {
                setReason("Out of range");
                setOperation(performedOperation);
                setSource(aSource);
        }

		virtual ~COutOfRangeException() {}

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

template <typename T>
class CIterator : public Object
{
private:
        T *m_pObject;

protected:
	virtual string _internalDescription()
	{
		char *c_strDescription = (char *)malloc(2000);
		sprintf(c_strDescription, "\n\twrapped object: 0x%x",
									(unsigned int)m_pObject);
		string retValue = Object::_internalDescription() + string(c_strDescription);
		free(c_strDescription);
		return retValue;
	}

public:
	virtual string getClassName()
	{
		return "CIterator";
	}

        CIterator() : m_pObject(NULL) {}

        CIterator(T *mem) : m_pObject(mem) {}
        CIterator(const T *mem) : m_pObject((T*)mem) {}

        //      prefix
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

        //      postfix
        CIterator operator ++(int)
        {
                CIterator retValue = *this;
                m_pObject++;
                return retValue;
        }

        CIterator operator --(int)
        {
                CIterator retValue = *this;
                m_pObject--;
                return retValue;
        }

        int operator -(const CIterator &target)
        {
                return (int)(m_pObject - target.m_pObject);
        }

        CIterator operator -(int leftShift)
        {
                CIterator retValue = *this;
                retValue.m_pObject -= leftShift;
                return retValue;
        }

        CIterator operator +(int rightShift)
        {
                CIterator retValue = *this;
                retValue.m_pObject += rightShift;
                return retValue;
        }

        T& operator *()
        {
                return *m_pObject;
        }

        bool operator ==(CIterator target)
        {
                return m_pObject == target.m_pObject;
        }

        bool operator !=(CIterator target)
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
class GVector : public Object
{
private:
        size_t m_nSize;
        size_t m_nCapacity;
#ifdef _DEBUG_CAPACITY_MULTIPLYING
        double m_fCapacityFactor;
#endif
        T *m_pData;

#ifdef _TEST_MEMORY_LEAK
		int m_nContainedObjectsCounter;
#endif

protected:
	virtual string _internalDescription()
	{
		char *c_strDescription = (char *)malloc(2000);
		sprintf(c_strDescription, "\n\tsize = %d\n\tsapacity = %d\n\tdata pointer = 0x%x",
									m_nSize, m_nCapacity, (unsigned int)m_pData);
		string retValue = Object::_internalDescription() + string(c_strDescription);
//		retValue += "\n\telements = (";
//		for (iterator it = begin(); it != end(); ++it)
//		{
//#if (dynamic_cast<Object *>(&(*it)))
//				sprintf(c_strDescription, "\n\t\t" + (*it).description()) 
//#else
//				sprintf(c_strDescription, "\n\t\t%d", *it);
//#endif
//			retValue += string(c_strDescription);
//		}
//		retValue += ")";
		free(c_strDescription);
		return retValue;
	}

public:

	virtual string getClassName()
	{
		return "GVector";
	}

		typedef CIterator<T> iterator;
        typedef const iterator const_iterator;

        GVector() : m_nSize(0), m_nCapacity(1),
#ifdef _DEBUG_CAPACITY_MULTIPLYING
                                m_fCapacityFactor(2.0),
#endif
                                m_pData(NULL)
#ifdef _TEST_MEMORY_LEAK
								,m_nContainedObjectsCounter(0)
#endif

        {
                gvectorWasCreated();
        }

        GVector(size_t size) : m_nSize(size), m_nCapacity(m_nSize)
#ifdef _DEBUG_CAPACITY_MULTIPLYING
                                                ,m_fCapacityFactor(2.0)
#endif
#ifdef _TEST_MEMORY_LEAK
												,m_nContainedObjectsCounter(0)
#endif
        {
                m_pData = new T[m_nCapacity];
                for (iterator it = begin(); it != end(); ++it)
					*it = T();
#ifdef _TEST_MEMORY_LEAK
				m_nContainedObjectsCounter += size;
#endif
                gvectorWasCreated();
        }

        GVector(GVector& sample) : m_nSize(sample.size()), m_nCapacity(sample.capacity())
#ifdef _DEBUG_CAPACITY_MULTIPLYING
                                                         , m_fCapacityFactor(2.0)
#endif
#ifdef _TEST_MEMORY_LEAK
														 , m_nContainedObjectsCounter(0)
#endif
        {
                m_pData = new T[m_nSize];
				for (iterator it = begin(), sampleIterator = sample.begin(); sampleIterator != sample.end(); ++it, ++sampleIterator)
					*it = *sampleIterator;
#ifdef _TEST_MEMORY_LEAK
				m_nContainedObjectsCounter += size();
#endif
                gvectorWasCreated();
        }

        virtual ~GVector()
        {
#ifdef _TEST_MEMORY_LEAK
				m_nContainedObjectsCounter -= size();
				assert(0 == m_nContainedObjectsCounter);
#endif
				if (m_pData)
				{
					delete[] m_pData;
				}
                gvectorWasDestroyed();
        }

        size_t size() const
        {
			return m_nSize;
        }

        bool empty() const
        {
			return m_nSize == 0;
        }

        void clear()
        {
			erase(begin(), end());
////			delete[] m_pData;
//#ifdef _TEST_MEMORY_LEAK
//				m_nContainedObjectsCounter -= size();
//#endif
//			m_nSize = 0;
        }

        void swap(GVector& target)
        {
			std::swap(m_pData, target.m_pData);
			std::swap(m_nSize, target.m_nSize);
			std::swap(m_nCapacity, target.m_nCapacity);
#ifdef _DEBUG_CAPACITY_MULTIPLYING
			std::swap(m_fCapacityFactor, target.m_fCapacityFactor);
#endif
#ifdef _TEST_MEMORY_LEAK
			std::swap(m_nContainedObjectsCounter, target.m_nContainedObjectsCounter);
#endif
        }

        void resize(size_t requestedSize)
        {
            if (m_nSize == requestedSize)
                    return;
#ifdef _TEST_MEMORY_LEAK
			int oldSize = m_nSize;
#endif
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
#ifdef _TEST_MEMORY_LEAK
			m_nContainedObjectsCounter += (m_nSize - oldSize);
#endif
        }

        size_t capacity() const
        {
			return m_nCapacity;
        }

        void reserve(size_t requestedCapacity)
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
                                for (iterator it = begin(), newIt = (iterator)newData; it != end(); ++it, ++newIt)
									*newIt = *it;
                                delete[] m_pData;
                        }
                        m_pData = newData;
                }
        }

        iterator begin() const
        {
                return iterator(m_pData);
        }

		const_iterator begin()
		{
			return const_iterator(m_pData);
		}

        iterator end() const
        {
                return iterator(m_pData + m_nSize);
        }

		const_iterator end()
		{
			return const_iterator(m_pData + m_nSize);
		}

        T& operator [] (size_t index) const
        {
                if (index >= 0 && index < m_nSize)
                        return *(m_pData + index);
#ifdef _DEBUG_GVECTOR_EXCEPTIONS
                throw COutOfRangeException(0, (m_nSize - 1 > 0 ? m_nSize - 1 : 0), index, (Object *)this, "Access by index vector operation");
#endif
#ifndef _DEBUG_GVECTOR_EXCEPTIONS
                assert(index >= 0 && index < m_nSize);  //      which would be false
#endif
        }

        T& front() const
        {
#ifndef _DEBUG_GVECTOR_EXCEPTIONS
                if (m_nSize >= 0)
#endif
                        return (*begin());
        }

        T& back() const
        {
#ifndef _DEBUG_GVECTOR_EXCEPTIONS
                if (m_nSize > 0)
#endif
                        return m_pData[m_nSize - 1];
        }

        void push_front(const T& object)
        {
                if (!m_pData)
                        this->reserve((size_t)1);
                insert(begin(), iterator(&object));
        }

        void push_back(const T& object)
        {
                if (!m_pData)
                        this->reserve((size_t)1);
                insert(end(), (iterator)&object);
        }

        void pop_back()
        {
                if (m_nSize)
				{
                        --m_nSize;
#ifdef _TEST_MEMORY_LEAK
						--m_nContainedObjectsCounter;
#endif
				}
        }

//      segment insertion
        void insert(iterator position, iterator fromIterator, iterator toIterator)      //      [from, to)
        {
                if (fromIterator > toIterator)
                {
                        insert(position, toIterator, fromIterator);
                        return;
                }
#ifdef _DEBUG_GVECTOR_EXCEPTIONS
                if (position < begin() || position > end())
                        throw COutOfRangeException(0, (m_nSize - 1 > 0 ? m_nSize - 1 : 0), position - begin(), this, "Insert at index vector operation");
#endif
                size_t segmentSize = (toIterator - fromIterator);
                size_t indexToInsert = position - begin();
                size_t oldCapacity = m_nCapacity;
//	objects counter increases here
                this->resize(m_nSize + segmentSize);
                if (m_nCapacity != oldCapacity)
                        position = m_pData + indexToInsert;
                //      shifting
                for (iterator followingIterator = &this->back(); followingIterator > position + segmentSize - 1; --followingIterator)
                {
                        *followingIterator = *(followingIterator - segmentSize);
                }
                //      inserting
                size_t iterationNumber = 0;
                for (iterator item = fromIterator; item != toIterator; ++item, ++iterationNumber)
                {
                        iterator newIterator = (position + iterationNumber);
                        *newIterator = *item;
                }
        }

//      single element insertion
        iterator insert(iterator position, iterator targetIterator)
        {
                insert(position, targetIterator, targetIterator + 1);
                return position;
        }

        iterator erase(iterator fromIterator, iterator toIterator)      //      [from, to)
        {
                if (fromIterator > toIterator)
                {
                        return erase(toIterator, fromIterator);
                }
#ifdef _DEBUG_GVECTOR_EXCEPTIONS
                int errorIndex;
                if (fromIterator < begin() || toIterator > end())
                {
                        errorIndex = (fromIterator < begin()) ? fromIterator - begin() : toIterator - begin();
                        throw COutOfRangeException(0, (m_nSize - 1 > 0 ? m_nSize - 1 : 0), errorIndex, this, "Erase by iterator vector operation");
                }
#endif
                size_t segmentSize = (toIterator - fromIterator);

                for (iterator leftShifted = fromIterator; leftShifted != toIterator; ++leftShifted)
                {
                        iterator oldIterator = leftShifted + segmentSize;
                        *leftShifted = *oldIterator;
						//oldIterator.destroyObject();
                }
				//(iterator)end();
                m_nSize -= segmentSize;
#ifdef _TEST_MEMORY_LEAK
				m_nContainedObjectsCounter -= segmentSize;
#endif
                return fromIterator;
        }

        iterator erase(iterator targetIterator)
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
		cout << items.description();
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
        launchGVectorTests();
#ifdef _TEST_MEMORY_LEAK
        assert(gvectorCounter == 0);    //      mem leak check
#endif
        return EXIT_SUCCESS;
}
