#include <sstream>
#include <iostream>
#include <algorithm>

template <typename T>
class dynamic_array {
	T* data;
	size_t n;
public:
	// 배열 크기를 인자로 받는 생성자
	dynamic_array(int n) {
		this->n = n;
		data = new T[n];
	}
	// 복사생성자
	dynamic_array(const dynamic_array<T>& other) {
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
			data[i] = other[i];
	}

	// 멤버 데이터 직접 접근 위한 []연산자
	T& operator[] (int index) {
		return data[index];
	}

	const T& operator[] (int index) const {
		return data[index];
	}

	// at() 함수
	T& at(int index) {
		if (index < n)
			return data[index];
		throw "Index out of range";
	}

	// 배열 크기 반환하는 size() 멤버 함수
	size_t size() const {
		return n;
	}

	//소멸자
	~dynamic_array() {
		delete[] data; // 메모리 릭 방지
	}
};

int main() {

	return 0;
}