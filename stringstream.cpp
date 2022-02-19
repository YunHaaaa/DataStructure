// https://doitnow-man.tistory.com/207

#include<iostream>
#include<sstream>

/*
* istringstream로 문자열 format을 분해 하기
int main() {
        std::istringstream iss("test 123 123hah ahha");
        std::string str, str1, str2;
        int inta;

        std::cout<< iss.str() <<std::endl;
        iss >> str >> str1 >> str2 >> inta;
        std::cout<<"str  : "<< str  <<std::endl;
        std::cout<<"str1 : "<< str1 <<std::endl;
        std::cout<<"str2 : "<< str2 <<std::endl;
        std::cout<<"inta : "<< inta <<std::endl;

}
*/

/*
* ostringstream로 문자열 format으로 문자열 생성하여 저장
int main() {
    std::ostringstream oss;
    int inta = 10;
    std::string str = " test_string";
    oss << "test " << inta << str << std::endl;
    std::cout << oss.str();
}
*/

/*
* stringstream로 문자열 저장 후 parsing 하기
int main() {
    // stringstream에 문자열 넣는 방법 1 (문자열로 입력)
    std::stringstream ss1("test 1 2 3 4 5");
    std::string str;

    // while(ss1 >> str)이란, 더 이상 str의 자료형에 맞는 정보가 없을 때까지
    // 계속 스트림에서 str으로 자료를 추출/복사하는 것이다. 끝에 도달하면 끝난다.
    while (ss1 >> str) {
        std::cout << str << std::endl;
    }

    // stringstream에 문자열 넣는 방법 2 (문자열 format 사용하여 입력)
    std::stringstream ss2;
    ss2 << "1" << ' ' << -1 << ' ' << 2 << 3;

    while (ss2 >> str) {
        std::cout << str << std::endl;
    }

    return 0;
}
*/

int main()
{
    std::ostringstream oss;

    oss << "test 1";
    oss.clear();
    oss.str("");
    oss << "test 2";
    std::cout << oss.str();
    return 0;
}