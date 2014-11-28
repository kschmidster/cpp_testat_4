#ifndef DYNARRAY_H_
#define DYNARRAY_H_

#include <vector>
#include <iterator>

template<typename T>
class dynArray {
	using value_type = T;
	using reference = value_type&;
	using const_reference =  const value_type&;
	using vec = std::vector<value_type>;
	using size_type = typename vec::size_type;
	using iterator = typename vec::iterator;
	using const_iterator = typename vec::const_iterator;
	using reverse_iterator = typename vec::reverse_iterator;
	using const_reverse_iterator = typename vec::const_reverse_iterator;

	vec myArray;

public:
	//ctor
	dynArray() : myArray { } { }
	dynArray(std::initializer_list<value_type> list) : myArray { } {
			myArray.insert(myArray.cend(), list.begin(), list.end());
	}
	dynArray(size_type size, const_reference value) : myArray { } {
		myArray.insert(myArray.cbegin(), size, value);
	}
	dynArray(std::istream_iterator<value_type> begin, std::istream_iterator<value_type> end) :
		myArray { begin, end } { }

	//access
	reference at(int index) {
		//TODO check implementation
		if (index >= 0) {
			return myArray.at(index);
		} else {
			return myArray.at(myArray.size() + index);
		}
	}

	const_reference at(int index) const {
		//TODO check implementation
		if (index >= 0) {
			return const_reference { myArray.at(index) };
		} else {
			return const_reference { myArray.at(myArray.size() + index) };
		}
	}

	reference operator[](int index) {
		//TODO check implementation
		if (index >= 0) {
			return reference { myArray.at(index) };
		} else {
			return reference { myArray.at(myArray.size() + index) };
		}
	}

	const_reference operator[](int index) const {
		//TODO check implementation
		if (index >= 0) {
			return myArray[index];
		} else {
			return myArray[myArray.size() + index];
		}
	}

	reference front() { return myArray.front(); }

	const_reference front() const {
		return const_reference { myArray.front() };
	}

	reference back() { return myArray.back(); }

	const_reference back() const {
		return const_reference { myArray.back() };
	}

	//Iterators TODO check iterator
	iterator begin() noexcept { return myArray.begin(); }
	const_iterator begin() const noexcept { return myArray.begin(); }
	const_iterator cbegin() const noexcept { return myArray.cbegin(); }
	reverse_iterator rbegin() noexcept { return myArray.rbegin(); }
	const_reverse_iterator rbegin() const noexcept { return myArray.rbegin(); }
	const_reverse_iterator crbegin() const noexcept { return myArray.crbegin(); }
	iterator end() noexcept { return myArray.end(); }
	const_iterator end() const noexcept { return myArray.end(); }
	const_iterator cend() const noexcept { return myArray.cend(); }
	reverse_iterator rend() noexcept { return myArray.rend(); }
	const_reverse_iterator rend() const noexcept { return myArray.rend(); }
	const_reverse_iterator crend() const noexcept { return myArray.crend(); }

	//Capacity
	bool empty() const noexcept { return myArray.empty(); }
	size_type size() const noexcept { return myArray.size(); }
	size_type capacity() const noexcept { return myArray.capacity(); }

	//Modifiers TODO check iterator
	void clear() noexcept { myArray.clear(); }
	iterator erase(iterator pos) { return myArray.erase(pos); }
	const_iterator erase(const_iterator pos) { return myArray.erase(pos); }
	iterator erase(iterator first, iterator last) {
		return myArray.erase(first, last);
	}
	const_iterator erase(const_iterator first, const_iterator last) {
		return myArray.erase(first, last);
	}
	void push_back(const_reference value) { myArray.push_back(value); }
	void pop_back() { myArray.pop_back(); }
	void resize(size_type count, value_type value = value_type()) {
		myArray.resize(count, value);
	}
	void resize(size_type count) { myArray.resize(count); }
	void resize(size_type count, const_reference value) {
		myArray.resize(count, value);
	}

	static dynArray<value_type>& makedynArray(std::initializer_list<value_type> list) {
		return dynArray { list };
	}
};

#endif /* DYNARRAY_H_ */
