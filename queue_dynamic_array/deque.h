#pragma once

#ifndef SJTU_DEQUE_HPP

#define SJTU_DEQUE_HPP



#include "exceptions.h"



#include <cstddef>


namespace sjtu {



	template<class T>

	class deque {


	public:

		class const_iterator;

		class iterator {

		private:

			/*

			* TODO add data members

			*   just add whatever you want.

			*/


		public:
		    T *first;
			T *last;
			T *cur;
			T **node;
			int  buff_size;

			void changeNode(T **newNode)
			{
				node = newNode;
				first = *node;
				last = first + buff_size;
			}
			iterator():cur(NULL), first(NULL),buff_size(512), last(NULL), node(NULL) {}

			iterator(T *cur,T **nod) :first(*nod), buff_size(512),last(*nod+512),cur(cur),node(nod) {}

			iterator(const iterator& x): cur(x.cur),  buff_size(512), first(x.first), last(x.last), node(x.node) {}



			/*

			* return a new iterator which pointer n-next elements

			*   even if there are not enough elements, the behaviour is **undefined**.

			* as well as operator-

			*/

			iterator operator+(const int &n) const {

				iterator temp=*this;
				return temp+=n;

				//TODO

			}

			iterator operator-(const int &n) const {
				iterator temp = *this;
				return temp+=(-n);
				//TODO

			}

			// return th distance between two iterator,

			// if these two iterators points to different vectors, throw invaild_iterator.

			int operator-(const iterator &rhs) const {

				return buff_size * (node - rhs.node - 1) + cur - first - (rhs.last - rhs.cur);
				//TODO

			}

			iterator operator+=(const int &n) {
				int moveTo = n + cur - first,moveNode;
				if (moveTo < buff_size and moveTo>=0)
					cur += n;
				else
				{
					moveNode = moveTo>0 ? moveTo / buff_size:-(-moveTo-1)/buff_size-1;
					changeNode(node + moveNode);
					cur = first + n - moveNode * buff_size;
				}

				//TODO
				return *this;

			}

			iterator operator-=(const int &n) {

				*this += (-n);
				return *this;
				//TODO

			}

			/*

			* TODO iter++

			*/

			iterator operator++(int)
			{
				iterator temp = *this;
				++*this;
				return temp;
			}

			/*

			* TODO ++iter

			*/

			iterator& operator++()
			{
				cur++;
				if (cur == last)
				{
					changeNode(node + 1);
					cur = first;
				}
				return *this;
			}

			/**

			* TODO iter--

			*/

			iterator operator--(int)
			{
				iterator temp=*this;
				--*this;
				return temp;
			}

			/**

			* TODO --iter

			*/

			iterator& operator--()
			{
				if (cur == first)
				{
					changeNode(node - 1);
					cur = last;
				}
				cur--;
				return *this;
			}

			/*

			* TODO *it

			*/

			T& operator*() const { return *cur; }

			/*

			* TODO it->field

			*/

			T* operator->() const noexcept { return cur; }

			/*

			* a operator to check whether two iterators are same (pointing to the same memory).

			*/

			bool operator==(const iterator &rhs) const { return cur==rhs.cur; }

			bool operator==(const const_iterator &rhs) const { return cur==rhs.cur; }

			/*

			* some other operator for iterator.

			*/

			bool operator!=(const iterator &rhs) const { return cur != rhs.cur; }

			bool operator!=(const const_iterator &rhs) const { return cur != rhs.cur; }

		};

		class const_iterator {

			// it should has similar member method as iterator.

			//  and it should be able to construct from an iterator.

		private:

			// data members.
			T * first;
			T *last;
			T *cur;
			T **node;
			int buff_size;

		public:

			const_iterator() :cur(NULL), first(NULL), buff_size(512), last(NULL), node(NULL) {

				// TODO

			}

			const_iterator(const const_iterator &other)
				: cur(other.cur), buff_size(512), first(other.first), last(other.last), node(other.node)
			{

				// TODO

			}

			const_iterator(const iterator &other)
				: cur(other.cur), buff_size(512 ), first(other.first), last(other.last), node(other.node)
			{

				// TODO

			}

			// And other methods in iterator.

			// And other methods in iterator.

			// And other methods in iterator.


			void changeNode(T **newNode)
			{
				node = newNode;
				first = *node;
				last = first + buff_size;
			}


			const_iterator operator+(const int &n) const {

				const_iterator temp = *this;
				return temp = +n;

			}

			const_iterator operator-(const int &n) const {
				const_iterator temp = *this;
				return temp += (-n);

			}


			int operator-(const const_iterator &rhs) const {

				return buff_size * (node - rhs.node - 1) + cur - first - (rhs.last - rhs.cur);


			}

			const_iterator operator+=(const int &n) {
				int moveTo = n + cur - first, moveNode;
				if (moveTo < buff_size and moveTo >= 0)
					cur += n;
				else
				{
					moveNode = moveTo>0 ? moveTo / buff_size : -(-moveTo - 1) / buff_size - 1;
					changeNode(node + moveNode);
					cur = first + n - moveNode * buff_size;
				}

				return *this;

			}

			const_iterator operator-=(const int &n) {

				*this += (-n);
				return *this;

			}


			const_iterator operator++(int)
			{
				const_iterator temp = *this;
				++*this;
				return temp;
			}

			const_iterator& operator++()
			{
				cur++;
				if (cur == last)
				{
					changeNode(node + 1);
					cur = first;
				}
				return *this;
			}

			const_iterator operator--(int)
			{
				const_iterator temp = *this;
				--*this;
				return temp;
			}

			const_iterator& operator--()
			{
				if (cur == first)
				{
					changeNode(node - 1);
					cur = last;
				}
				cur--;
				return *this;
			}


			T operator*() const { return *cur; }


			T* operator->() const noexcept { return cur; }


			bool operator==(const iterator &rhs) const { return cur == rhs.cur; }

			bool operator==(const const_iterator &rhs) const { return cur == rhs.cur; }


			bool operator!=(const iterator &rhs) const { return cur != rhs.cur; }

			bool operator!=(const const_iterator &rhs) const { return cur != rhs.cur; }




		};

	protected:
		iterator start;
		iterator finish;
		T** map;
		size_t mapSize;
		int buffSize;

		void create_node_front(T** newOne)
		{
			*newOne = new T[buffSize];
			start.changeNode(newOne);
			start.cur = start.last - 1;
		}
		void create_node_back(T** newOne)
		{
			*newOne = new T[buffSize];
			finish.changeNode(newOne);
			finish.cur = finish.first;
		}

	public:


		/*

		* TODO Constructors

		*/

		deque() :mapSize(9), buffSize(512)
		{
			map = new T*[mapSize];
			map[mapSize / 2] = new T[buffSize];
			start.changeNode(&map[mapSize/2]);
			start.cur = start.first + buffSize / 2;
			finish.changeNode(&map[mapSize/2]);
			finish.cur = start.first + buffSize / 2;
		}

		deque(const deque &other) : buffSize(other.buffSize){
			long long mapIndex,nodeNum = other.size();
			mapSize=nodeNum/buffSize+3;
			map = new T*[mapSize];
			map[1] = new T[buffSize];
			start.changeNode(&map[1]);
			start.cur = start.first;
			mapIndex = nodeNum % buffSize == 0 ? nodeNum / buffSize : (nodeNum / buffSize + 1);
			for (long long i = 1; i <= mapIndex; i++)
				map[i] = new T[buffSize];
			finish = copy_node_back(other.start,other.finish,start);
		}


		iterator copy_node_back(const iterator& orig_start, const iterator& orig_finish, iterator& cpy_start)//从前往后复制所有的点
		{
			iterator tempOther = orig_start, temp = cpy_start;
			while (tempOther != orig_finish)
			{
				*temp = *tempOther;
				temp++;
				tempOther++;
			}
			return temp;
		}


		/*

		* TODO Deconstructor

		*/

		~deque() {
			for (T** i = start.node; i<=finish.node; i++)
				delete[] i;
			delete[] map;
		}

		/*

		* TODO assignment operator

		*/

		deque &operator=(const deque &other) {
			if (&other != this)
			{
				size_t len = size(),otherLen=other.size();
				size_t diff= start + otherLen - finish;

				if (diff<=0)
				{

					iterator temp(start), tempOther(other.start);
					while (tempOther != other.finish)
					{
						*temp = *tempOther;
						temp++;
						tempOther++;
					}
					finish = temp;
				}
			}
			return *this;
		}

		/*

		* access specified element with bounds checking

		* throw index_out_of_bound if out of bound.

		*/

		T & at(const size_t &pos)
		{
			size_t Size = size();
			if (pos < 0 or pos >= Size)
				throw index_out_of_bound();
			return *(start + pos);
		}

		const T & at(const size_t &pos) const
		{
			size_t Size = size();
			if (pos < 0 or pos >= Size)
				throw index_out_of_bound();
			return *(start + pos);
		}

		T & operator[](const size_t &pos)
		{
			size_t Size = size();
			if (pos < 0 or pos >= Size)
				throw index_out_of_bound();
			return *(start + pos);
		}

		const T & operator[](const size_t &pos) const
		{
			size_t Size = size();
			if (pos < 0 or pos >= Size)
				throw index_out_of_bound();
			return *(start + pos);
		}

		/*

		* access the first element

		* throw container_is_empty when the container is empty.

		*/

		const T & front() const {
			if (empty())
				throw container_is_empty();
			return *start; }

		/*

		* access the last element

		* throw container_is_empty when the container is empty.

		*/

		const T & back() const {
			if (empty())
				throw container_is_empty();
			return *(finish-1); }

		/*

		* returns an iterator to the beginning.

		*/

		iterator begin() { return start; }

		const_iterator cbegin() const { return const_iterator(start); }

		/*

		* returns an iterator to the end.

		*/

		iterator end() { return finish; }

		const_iterator cend() const { return const_iterator(finish); }

		/*

		* checks whether the container is empty.

		*/

		bool empty() const { return start==finish; }

		/*

		* returns the number of elements

		*/

		size_t size() const
		{
			return finish-start;
		}

		/*

		* clears the contents

		*/

		void clear()
		{
			for (T** i = start.node; i <= finish.node; i++)
				delete[] map[i];
			map[mapSize / 2] = new T[buffSize];
			start.changeNode(&map[mapSize / 2]);
			start.cur = start.first + buffSize / 2;
			finish.changeNode(&map[mapSize / 2]);
			finish.cur = start.first + buffSize / 2;
		}



		void resizeMapAtBack(size_t nodeNum = 1)
		{
			if (mapSize < finish.node - start.node + 1 + nodeNum)
				resizeMap(nodeNum, false);
		}
		void resizeMapAtFront(size_t nodeNum = 1)
		{
			if (start.node - map < nodeNum)
				resizeMap(nodeNum, true);
		}
		void resizeMap(size_t addNodeNum, bool atFront)
		{
			size_t oldNodeNum = finish.node - start.node + 1;
			size_t newNodeNum = oldNodeNum + addNodeNum;
			size_t posStart, posFinish;
			T** newStart;
			posStart = start.cur - start.first;
			posFinish = finish.cur - finish.first;

			if (mapSize > 2 * newNodeNum)
			{
				newStart = map + (mapSize - newNodeNum) / 2 + (atFront ? addNodeNum : 0);
				T** temp, newTemp;
				size_t dist = newStart - start.node;
				if (newStart < start.node)
				{
					for (temp = finish.node; temp >= start.node; temp--)
					{
						*(temp + dist) = *temp;
					}
				}
				else
				{
					for (temp = start.node; temp <= finish.node; temp++)
					{
						*temp = *(temp + dist);
					}
				}

			}
			else
			{
				size_t newMapSize = mapSize + (mapSize > addNodeNum ? mapSize : addNodeNum) + 2;
				T** newMap = new T*[newMapSize];
				T** temp = start.node;
				newStart = newMap + (newMapSize - newNodeNum) / 2 + (atFront ? addNodeNum : 0);
				T** otherTemp = newStart;
				while (temp - finish.node<=0)
				{
					*otherTemp = *temp;
					temp++;
					otherTemp++;
				}
				mapSize = newMapSize;
				delete[] map;
				map = newMap;
			}
			start.changeNode(newStart);
			start.cur = start.first + posStart;
			finish.changeNode(newStart + oldNodeNum-1);
			finish.cur = finish.first + posFinish;
		}




		/*

		* inserts elements at the specified locat on in the container.

		* inserts value before pos

		* returns an iterator pointing to the inserted value

		*     throw if the iterator is invalid or it point to a wrong place.

		*/

		iterator insert(iterator pos, const T &value) {
			if (pos.node > finish.node or pos.node < start.node or (pos.node == start.node and pos.cur > start.cur) or (pos.node == finish.node and pos.cur >= finish.cur))
				throw;
			if (pos == start)
			{
				push_front(value);
				return start;
			}
			else if (pos == finish)
			{
				push_back(value);
				return finish;
			}
			else
			{
				size_t dist = pos - start;
				if (dist < size() / 2)
				{
					iterator temp = start;
					push_front(front());
					while (temp != pos-1)
					{
						*temp = *(temp + 1);
						temp++;
					}
					*temp = value;
					return temp;
				}
				else
				{
					iterator temp = finish;
					push_back(back());
					while (temp != pos)
					{
						*temp = *(temp - 1);
						temp--;
					}
					*temp = value;
					return temp;
				}
			}
		}

		/*

		* removes specified element at pos.

		* removes the element at pos.

		* returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.

		* throw if the container is empty, the iterator is invalid or it points to a wrong place.

		*/

		iterator erase(iterator pos) {
			if (start == finish or pos.node > finish.node or pos.node < start.node or (pos.node == start.node and pos.cur > start.cur) or (pos.node == finish.node and pos.cur >= finish.cur))
				throw;
			size_t dist = pos - start;
			if (dist < size() / 2)
			{
				iterator temp = pos;
				while (temp != start)
				{
					*temp = *(temp - 1);
					temp--;
				}
				pop_front();
			}
			else
			{
				iterator temp = pos;
				while (temp != finish)
				{
					*temp = *(temp + 1);
					temp++;
				}
				pop_back();
			}
		}

		/*

		* adds an element to the end

		*/

		void push_back(const T &value)
		{

			*finish = value;
			++finish.cur;
			if (finish.cur == finish.last)
			{
				resizeMapAtBack();
				create_node_back(finish.node + 1);
			}

		}

		/*

		* removes the last element

		*     throw when the container is empty.

		*/

		void pop_back()
		{
			if (empty())
				throw;
			if (finish.cur == finish.first)
			{
				finish.changeNode(finish.node - 1);
				finish.cur = finish.last;
				delete[] *(finish.node + 1);
			}
			finish.cur--;
		}

		/*

		* inserts an element to the beginning.

		*/

		void push_front(const T &value) {
			if (start.cur == start.first)
			{
				resizeMapAtFront();
				create_node_front(start.node + 1);
			}
			*start = value;
		}

		/*

		* removes the first element.

		*     throw when the container is empty.

		*/

		void pop_front() {
			if (empty())
				throw;
			if (start.cur == start.last - 1)
			{
				delete[] start.node;
				start.changeNode(start.node + 1);
				start.cur = start.first - 1;
			}
			start.cur++ ;
		}

	};



}



#endif
