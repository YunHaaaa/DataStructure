#include <string>
#include <iostream>
#include <forward_list>

struct citizen {
	std::string name;
	int age;
};

std::ostream& operator<<(std::ostream& os, const citizen& c) {
	return (os << "[" << c.name << "," << c.age << "]");
}

// std::forward_list 사용하여 시민 정보 초기화, 추후 다시 초기화하는 것을 피하기 위해 복사본을 만들어 둠
int main() {
	std::forward_list<citizen> citizens = {
		{"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}
	};

	auto citizens_copy = citizens; // 깊은 복사

	std::cout << "전체 시민들: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens.remove_if([](const citizen& c) {
		return (c.age < 19);
	});

	std::cout << "투표권이 있는 시민들: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens_copy.remove_if([](const citizen& c) {
		return (c.age != 18);
	});

	std::cout << "내년에 투표권이 생기는 시민들: ";
	for (const auto& c : citizens_copy)
		std::cout << c << " ";
	std::cout << std::endl;
}
