#ifndef DYNARRAY_H_
#define DYNARRAY_H_

#include <vector>

template<typename T>
struct dynArray {
	using vector = std::vector<T>;
	using value_type = typename vector::value_type;
	using reference = typename vector::reference;
	using const_reference = typename vector::const_reference;
	using size_type = typename vector::size_type;
	using iterator = typename vector::iterator;
	using const_iterator = typename vector::const_iterator;
	using reverse_iterator = typename vector::reverse_iterator;
	using const_reverse_iterator = typename vector::const_reverse_iterator;
	using istream_iterator = std::istream_iterator<value_type>;
	using initializer_list = std::initializer_list<value_type>;

	//ctor
	dynArray() : myArray { } { }
	dynArray(initializer_list list) : myArray { list } { }
	dynArray(size_type size, const_reference value) : myArray (size, value) { }
	template<typename Iter>
	dynArray(Iter begin, Iter end) : myArray (begin, end) { }

	//access
	reference at(int index) {
		if (index >= 0) {
			return myArray.at(index);
		} else {
			return myArray.at(myArray.size() + index);
		}
	}

	const_reference at(int index) const {
		if (index >= 0) {
			return myArray.at(index);
		} else {
			return myArray.at(myArray.size() + index);
		}
	}

	reference operator[](int index) {
		if (index >= 0) {
			return myArray[index];
		} else {
			return myArray[myArray.size() + index];
		}
	}

	const_reference operator[](int index) const {
		if (index >= 0) {
			return myArray[index];
		} else {
			return myArray[myArray.size() + index];
		}
	}

	reference front() { return myArray.front(); }

	const_reference front() const {
		return myArray.front();
	}

	reference back() { return myArray.back(); }

	const_reference back() const {
		return myArray.back();
	}

	//Iterators
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

	//Modifiers
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
	void resize(size_type count) { myArray.resize(count); }
	void resize(size_type count, const_reference value) {
		myArray.resize(count, value);
	}

	static dynArray<value_type> makedynArray(initializer_list list) {
		return dynArray<value_type> { list };
	}

private:
	vector myArray;
};

#endif /* DYNARRAY_H_ */
