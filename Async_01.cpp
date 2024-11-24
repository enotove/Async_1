
#include <iostream>
#include <future>
#include <vector>
#include <thread>


void min_numbers(std::vector<int> array, size_t size, std::promise<std::vector<int>> pr)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size-1; j++)
        {
            if (array[j+1] < array[j])
            {
                auto temp =array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
    pr.set_value(array);
}
int main()
{
    std::promise<std::vector<int>> pr;
    std::future<std::vector<int>> fut = pr.get_future();
    std::vector<int> vector1{ 2,6,7,54,23,3,6,7,5 };
    std::thread thread1(min_numbers, vector1, vector1.size(), std::move(pr));
    fut.wait();
    auto v = fut.get();
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << " ";
    }
    thread1.join();
}
