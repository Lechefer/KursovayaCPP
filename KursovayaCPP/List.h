#pragma once
#include <stdexcept>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <algorithm>

template<typename T>
class List
{
public:
	List()
	{
		this->_head = nullptr;
	}

	void Add(T newData)
	{
		TNode* newEl = new TNode();
		newEl->data = newData;

		TNode* el = this->_head;
		if (this->_head == nullptr)
		{
			this->_head = newEl;
			return;
		}

		while (el->next != nullptr) {
			el = el->next;
		}

		el->next = newEl;
		newEl->prev = el;
	}

	void Remove(int index)
	{
		int localIndex = 0;
		if (index < localIndex) {
			throw std::out_of_range("out of range");
		}

		TNode* el = _head;
		while (localIndex < index) {
			if (el->next == nullptr) {
				throw std::out_of_range("out of range");
			}
			el = el->next;
			localIndex++;
		}

		if (el->next != nullptr && el->next->prev != nullptr) {
			el->prev->next = el->next;
			el->next->prev = el->prev;
		}
		else if (el->prev != nullptr && el->next == nullptr) {
			el->prev->next = nullptr;
		}
		else if (el->next != nullptr && el->prev == nullptr) {
			el->next->prev = nullptr;
			_head = el;
		}
		else {
			_head = nullptr;
		}

		delete el;
	}

	void Clear()
	{
		delete _head;
		_head = nullptr;
	}

	void Swap(int firstIndex, int secondIndex)
	{
		if (firstIndex == secondIndex)
		{
			return;
		}

		std::pair<int, int> bounds = std::minmax(firstIndex, secondIndex);

		int localIndex = 0;
		if (firstIndex < localIndex || secondIndex < localIndex) {
			throw std::out_of_range("out of range");
		}

		TNode* el = _head;
		while (localIndex < bounds.first) {
			if (el->next == nullptr) {
				throw std::out_of_range("out of range");
			}
			el = el->next;
			localIndex++;
		}

		TNode* firstNode = el;

		while (localIndex < bounds.second) {
			if (el->next == nullptr) {
				throw std::out_of_range("out of range");
			}
			el = el->next;
			localIndex++;
		}

		TNode* secondNode = el;

		if (firstNode->prev == nullptr && secondNode->next == nullptr) {
			firstNode->next->prev = secondNode;
			secondNode->prev->next = firstNode;
			firstNode->prev = secondNode->prev;
			secondNode->prev = nullptr;
			firstNode->next = nullptr;
			_head = secondNode;
		}
		else if (firstNode->prev != nullptr && firstNode->next != nullptr && secondNode->next == nullptr) {
			secondNode->prev->next = firstNode;
			firstNode->prev->next = secondNode;
			firstNode->next->prev = secondNode;

			secondNode->next = firstNode->next;
			firstNode->next = nullptr;
			TNode* temp = secondNode->prev;
			secondNode->prev = firstNode->prev;
			firstNode->prev = temp;
		}
		else {
			secondNode->prev->next = firstNode;
			secondNode->next->prev = firstNode;
			firstNode->prev->next = secondNode;
			firstNode->next->prev = secondNode;

			TNode* temp = secondNode->next;
			secondNode->next = firstNode->next;
			firstNode->next = temp;
			temp = secondNode->prev;
			secondNode->prev = firstNode->prev;
			firstNode->prev = temp;
		}
	}

	void InsertOf(T newData, int index)
	{
		TNode* newEl = new TNode();
		newEl->data = newData;

		int localIndex = 0;
		if (index < localIndex) {
			throw std::out_of_range("out of range");
		}

		TNode* el = _head;
		while (localIndex < index) {
			if (el->next == nullptr) {
				throw std::out_of_range("out of range");
			}
			el = el->next;
			localIndex++;
		}

		if (this->_head == nullptr)
		{
			this->_head = newEl;
			return;
		}

		if (el->prev == nullptr)
		{
			if (el == nullptr)
			{
				this->_head = newEl;
			}
			else {
				this->_head = newEl;
				newEl->next = el;
				el->prev = newEl;
			}
		}
		else if (el->next == nullptr) {
			newEl->prev = el->prev;
			newEl->next = el;
			el->prev = newEl;
		}
		else {
			newEl->prev = el->prev;
			newEl->next = el;
			el->prev = newEl;
		}
	}

	T operator [] (int index)
	{
		int localIndex = 0;
		if (index < localIndex) {
			throw std::out_of_range("out of range");
		}

		TNode* el = this->_head;
		while (localIndex < index) {
			if (el->next == nullptr) {
				throw std::out_of_range("out of range");
			}
			el = el->next;
			localIndex++;
		}

		return el->data;
	}

	int GetLength() 
	{ 
		int length = 0;
		TNode* el = this->_head;
		if (this->_head == nullptr)
		{
			return length;
		}

		length++;

		while (el->next != nullptr) {
			el = el->next;
			length++;
		}

		return length;
	}

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& _head;
	}

	struct TNode
	{
	public:
		T data;
		TNode* next;
		TNode* prev;

		TNode()
		{
			next = nullptr;
			prev = nullptr;
		}

		~TNode()
		{
			delete next;
			delete prev;
		}

	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& data;
			ar& next;
			ar& prev;
		}
	};

	TNode* _head;
};

