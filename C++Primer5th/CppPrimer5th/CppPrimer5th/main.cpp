
#include <memory> // shared_ptr
#include <iostream>
#include <vector> // vector 

/// <summary>
/// shared_ptr construct
/// </summary>
/// <returns></returns>
int testSharedPtr();

/// <summary>
/// test vector copy
/// </summary>
/// <returns></returns>
int testVector();


int main()
{
    testVector();

	return 0;
}


int testSharedPtr()
{

    std::shared_ptr<int> p = std::make_shared<int>(42);
    std::cout << p.get() << "  " << p << "  " << *p << std::endl;

    std::shared_ptr<std::string> p2 = std::make_shared<std::string>(10, '9');
    std::cout << p2.get() << "  " << p2 << "  " << *p2 << std::endl;

    std::shared_ptr<int> p3 = std::make_shared<int>();
    std::cout << p3.get() << "  " << p3 << "  " << *p3 << std::endl;

    auto p4 = std::make_shared<int>();
    std::cout << p4.get() << "  " << p4 << "  " << *p4 << std::endl;

    getchar();
    return 0;

}



int testVector()
{
    std::vector<std::string> v1;
    {
        std::vector<std::string> v2 = { "1", "2", "3" };
        v1 = v2;
    }

    for (auto n : v1)
    {
        std::cout << n << std::endl;
    }

    return 0;
}
