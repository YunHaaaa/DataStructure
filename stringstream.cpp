// https://doitnow-man.tistory.com/207

#include<iostream>
#include<sstream>

/*
* istringstream�� ���ڿ� format�� ���� �ϱ�
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
* ostringstream�� ���ڿ� format���� ���ڿ� �����Ͽ� ����
int main() {
    std::ostringstream oss;
    int inta = 10;
    std::string str = " test_string";
    oss << "test " << inta << str << std::endl;
    std::cout << oss.str();
}
*/

/*
* stringstream�� ���ڿ� ���� �� parsing �ϱ�
int main() {
    // stringstream�� ���ڿ� �ִ� ��� 1 (���ڿ��� �Է�)
    std::stringstream ss1("test 1 2 3 4 5");
    std::string str;

    // while(ss1 >> str)�̶�, �� �̻� str�� �ڷ����� �´� ������ ���� ������
    // ��� ��Ʈ������ str���� �ڷḦ ����/�����ϴ� ���̴�. ���� �����ϸ� ������.
    while (ss1 >> str) {
        std::cout << str << std::endl;
    }

    // stringstream�� ���ڿ� �ִ� ��� 2 (���ڿ� format ����Ͽ� �Է�)
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