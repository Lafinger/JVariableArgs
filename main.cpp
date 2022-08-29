#include <iostream>
#include <vector>
#include <string>

// <<<<<<<<<<<<<<<<<<<<<<<< Variable args expand >>>>>>>>>>>>>>>>>>>>>>>>>>>>

//------------------------ Funtion template expand --------------------------
// 1.recursively
void FuntionTemplateInRecursively() {
    std::cout << "end" << std::endl;
}
template <typename F, typename ...Args>
void FuntionTemplateInRecursively(F first, Args&& ...args) {
    
    std::cout << first << std::endl;
    FuntionTemplateInRecursively(args...);
}
// 2.not recursively
// (1) (print(args), 0)... = ( (print(args1), 0), (print(args2), 0), (print(args3), 0), ...)
// template <class T>
// void print(T arg)
// {
//     std::cout << arg << std::endl;
// }
// template <typename ...Args>
// void FuntionTemplateNotRecursively(Args&& ...args) {
//     std::vector<int> vec = { (print(args), 0)... };
// }
// (2) function's args
template <typename F, typename ...Args>
void FuntionTemplateNotRecursively(const F& f, Args&& ...args) {

    // std::vector<int> test {(f(std::forward<Args>(args)), 0)...};
    (f(std::forward<Args>(args)), ...);
}
//------------------------ Funtion template expand ----------------------------

//---------------------------  Class template expand ---------------------------
// 1.inheritance expand
template<typename ...All> class ExpandTemplateByInheritance {};
template <typename Head, typename ...Tail>
class ExpandTemplateByInheritance<Head, Tail...> : public ExpandTemplateByInheritance<Tail...> {
public:
    ExpandTemplateByInheritance()
    {
        std::cout << "type : " << typeid(head).name() << std::endl;
    }

    Head head;
};
template <> class ExpandTemplateByInheritance<> {};

// 2.recursively expand
// (1)
template<typename ...All> class ExpandTemplateByRecursively {};
template <typename Head, typename ...Tail>
class ExpandTemplateByRecursively<Head, Tail...> {
public:
    ExpandTemplateByRecursively() {
        std::cout << typeid(Head).name() << std::endl;
        std::cout << typeid(ExpandTemplateByRecursively<Tail...>::head).name() << std::endl;
    }

    static Head head;
};
template <> class ExpandTemplateByRecursively<> {};
// (2)
template <long... nums> struct Multiply;
template <long first, long... last>
struct Multiply<first, last...>
{
    static const long val = first * Multiply<last...>::val;
};
template<> struct Multiply<> {static const long val = 1;};
//---------------------------  Class template expand --------------------------- 


int main() {

    // Funtion template expand
    FuntionTemplateInRecursively(0, 1, 2, 3, 4);
    // FuntionTemplateNotRecursively(0, 1, 2, 3, 4);
    // FuntionTemplateNotRecursively([](int i){std::cout << i << std::endl;}, 1, 2, 3); // c++11
    FuntionTemplateNotRecursively([](auto i){std::cout << i << std::endl;}, 1, 2.2, "test"); // c++14

    // Class template expand
    ExpandTemplateByInheritance<int, char, float> inheritance;
    // ExpandTemplateByRecursively<int, char, float> recursively;
    // std::cout << Multiply<2, 3, 4, 5>::val << std::endl; // 120
	return 0;
}