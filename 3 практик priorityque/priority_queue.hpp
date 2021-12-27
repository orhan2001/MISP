#pragma once
#include <algorithm>
#include <vector>

template<typename T, typename Container = std::vector<T>>
class priority_queue {
	Container _container;
	
	int _leftChildIndex(int parentIndex);
	
	int _rightChildIndex(int parentIndex);
	
	int _parentIndex(int childIndex);
	
	void _siftUp(int index);
	
	void _siftDown(int index);
	
public:
	void push(const T& value);
	
	T top() const;
	
	T pop();
	
	bool empty() const;
};


template<typename T, typename Container>
int priority_queue<T, Container>::_leftChildIndex(int parentIndex) {
	return parentIndex * 2 + 1; 
}

template<typename T, typename Container>
int priority_queue<T, Container>::_rightChildIndex(int parentIndex) {
	return parentIndex * 2 + 2; 
}

template<typename T, typename Container>
int priority_queue<T, Container>::_parentIndex(int childIndex) {
	return (int)(0.5 * childIndex + 0.5) - 1; 
}


template<typename T, typename Container>
void priority_queue<T, Container>::_siftUp(int index) {
	if (index == 0) {
		return;
	}
	int parent = 0; 
	if (_container[index] > _container[_parentIndex(index)]) {
		parent = _parentIndex(index);
	}
	else {
		return;
	}
	std::swap(_container[index], _container[parent]);
	_siftUp(parent);
}


template<typename T, typename Container>
void priority_queue<T, Container>::_siftDown(int index) {
	if (index == _container.size()-1) {
		return;
	}
	int child = 0; 
	if (_leftChildIndex(index) < _container.size() && _rightChildIndex(index) < _container.size()) {
		if (_container[_leftChildIndex(index)] >= _container[_rightChildIndex(index)]) {
			child = _leftChildIndex(index);
		}
		else {
			child = _rightChildIndex(index);
		}
	}
	else if (_leftChildIndex(index) < _container.size() && _container[index] <= _container[_leftChildIndex(index)]) {
		child = _leftChildIndex(index);
	}
	/*
	else if (_rightChildIndex(index) < _container.size() && _container[index] <= _container[_rightChildIndex(index)]) {
		child = _rightChildIndex(index);
	}
	*/
	else {
		return;
	}
	std::swap(_container[index], _container[child]);
	_siftDown(child);
}


template<typename T, typename Container>
void priority_queue<T, Container>::push(const T& value) {
	_container.push_back(value); 
	if (_container.size() != 1) {
		_siftUp(_container.size() - 1);
	}
}

template<typename T, typename Container>
T priority_queue<T, Container>::top() const {
	return _container[0];
}


template<typename T, typename Container>
T priority_queue<T, Container>::pop() {
	T topValue = top();
	
	if (_container.size() != 1) {
		std::swap(_container[0], _container[_container.size() - 1]);
	}
	_container.pop_back();
	if (!empty()) {
		_siftDown(0);
	}
	return topValue;
}

template<typename T, typename Container>
bool priority_queue<T, Container>::empty() const {
	return _container.empty();
}