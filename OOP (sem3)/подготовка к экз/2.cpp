#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>


template <typename T, typename Func>
auto convert(const std::vector<T>& input, Func func)
{
        using R = std::invoke_result_t<Func, T>;
        std::vector<R> out(input.size());
        std::transform(input.begin(), input.end(), out.begin(), func);

        return out;
}


int main()
{
        //Тестовые данные 1:
        std::vector<std::string> v1;
        v1.push_back("aaa");
        v1.push_back("bb");
        v1.push_back("cccc");

        //функция преобразования, принимающая строку и возвращающая длину
        auto func1 = [](const std::string& s)-> size_t { return s.size(); };

        std::vector<size_t> v1_result = convert(v1, func1);

        for (const auto& i : v1_result) {
                std::cout << i << std::endl;
        }
        /*корректный результат:
        3
        2
        4
        */

        //Тестовые данные 2:
        struct User { std::string name; std::string secondName; };
        std::vector<User> v2 = { User { "Ivan", "Ivanov" }, User { "Petya", "Petrov" } };

        //func2 - функция, принимающая пользователя и возвращающая строку "фамилия-имя", напишите её
        auto func2 = [](const User& user)->std::string { return user.secondName + "-" + user.name; };
        std::vector<std::string> v2_result = convert(v2, func2);

        for (const auto& i : v2_result) {
                std::cout << i << std::endl;
        }
        /*корректный результат
        Ivanov-Ivan
        Petrov-Petya
        */
}