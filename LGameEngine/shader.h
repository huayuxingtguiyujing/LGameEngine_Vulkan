#pragma once
#include<iostream>
#include<mutex>

struct IShader {

};

class Shader
{
};

// 线程安全，写于9.24日，因为面试题可能会出现
class Counter {

private:
	unsigned int m_Counter;

public:
	Counter() : m_Counter(0) { }
	Counter(const Counter& c) = delete;
	~Counter() {}

	void reset() { m_Counter = 0;}
	unsigned int get() { return m_Counter; }

	void operator++() { m_Counter++; }
	void operator--() { m_Counter--; }

	friend std::ostream& operator<<(std::ostream& os, const Counter& c) {
		os << "counter is : " << c.m_Counter << std::endl;
		return os;
	}
};

template<typename T>
class Shared_ptr {

private:
	T* m_ptr;
	std::mutex* m_Mutex;
	Counter* m_Counter;

	void AddRefCount() {
		m_Mutex->lock();
		++(*m_Counter);
		m_Mutex->unlock();
	}

	void RealsePtr() {
		bool canDelete = false;

		m_Mutex->lock();
		--(*m_Counter);
		if (m_Counter->get() == 0) {
			delete m_ptr;
			delete m_Counter;
			canDelete = true;
		}
		m_Mutex->unlock();

		if (canDelete) {
			delete m_Mutex;
		}
	}

public:
	

	explicit Shared_ptr(T* ptr = nullptr) {
		m_ptr = ptr;
		m_Counter = new Counter();
		m_Mutex = new std::mutex;
		if (ptr) {
			AddRefCount();
		}
	}

	Shared_ptr(Shared_ptr<T>* sp) {
		m_ptr = sp->m_ptr;
		m_Counter = sp->m_Counter;
		AddRefCount();
	}

	Shared_ptr<T>& operator=(const Shared_ptr<T>& sp) {
		if (m_ptr != sp.m_ptr) {
			// 先释放 再赋值，shared是不讲究所有权的，auto可以剥夺所有权
			RealsePtr();
			m_ptr = sp.m_ptr;
			m_Counter = sp.m_Counter;
			m_Mutex = sp.m_Mutex;
			AddRefCount();
		}
	}

	~Shared_ptr() {	RealsePtr();}

	T* get() { return m_ptr; }
	unsigned int count() { return m_Counter->get(); }

};
