#include <array>
#include <iostream>
#include <type_traits>

/* 
컨테이너 생성 build_array() 함수 
 - 빠른 원소 순회를 보장하는 std::array를 반환
 - 가변 템플릿 사용하여 임의 개수의 매개변수 허용
 */
 
/*
파라미터 팩 "..."
- 0개 이상의 인자를 나타냄
- 템플릿의 경우 타입 앞에 온다
- 함수의 경우 타입 뒤에 온다
https://modoocode.com/290
*/

template<typename ... Args>

// 우측값 참조법, && reference
//https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=0511cjh&logNo=221590246985

// 함수 반환형을 후행 리턴 타입으로 지정
auto build_array(Args&& ... args)->
std::array<typename std::common_type<Args...>::type, sizeof...(args)>
{
	//T.43: 타입에 별명을 붙일때 typedef 보다는 using을 사용하라
	//https://www.cppkorea.org/CppCoreGuidelines/Templates/
	using commonType = typename std::common_type<Args...>::type;

	// 배열 생성

	//std::forward
	//https://velog.io/@rylynn6318/C-stdmove-%EC%99%80-stdforward
	return { std::forward<commonType>((Args&&)args)... };
}

int main() {
	auto data = build_array(1, 0u, 'a', 3.2f, false);

	for (auto i : data)
		std::cout << i << " ";
	std::cout << std::endl;
}
