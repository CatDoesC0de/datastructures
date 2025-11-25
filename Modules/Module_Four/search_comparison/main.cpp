#include <list>
#include <random>
#include <chrono>
#include <print>
#include <algorithm>

std::list<int> build_list(std::size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10000);

    std::list<int> lst;
    while (n--)
        lst.push_back(dist(gen));

    return lst;
}

std::list<int> merge_lists(std::list<int>& a, std::list<int>& b)
{
    std::list<int> result;

    auto itA = a.begin();
    auto itB = b.begin();

    while (itA != a.end() && itB != b.end())
    {
        if (*itA <= *itB)
        {
            result.push_back(*itA);
            ++itA;
        }
        else
        {
            result.push_back(*itB);
            ++itB;
        }
    }

    result.insert(result.end(), itA, a.end());
    result.insert(result.end(), itB, b.end());

    return result;
}

std::list<int> merge_sort(std::list<int> lst)
{
    if (lst.size() <= 1)
        return lst;

    auto mid = lst.begin();
    std::advance(mid, lst.size() / 2);

    std::list<int> left(lst.begin(), mid);
    std::list<int> right(mid, lst.end());

    left = merge_sort(left);
    right = merge_sort(right);

    return merge_lists(left, right);
}

void selection_sort(std::list<int>& lst)
{
    for (auto i = lst.begin(); i != lst.end(); ++i)
    {
        auto min_it = i;
        for (auto j = std::next(i); j != lst.end(); ++j)
        {
            if (*j < *min_it)
                min_it = j;
        }
        if (min_it != i)
            std::iter_swap(i, min_it);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::println("Usage: {} <element_count>", argv[0]);
        return 1;
    }

    std::size_t n = std::stoul(argv[1]);

    auto list_merge = build_list(n);
    auto list_select = list_merge;

    using namespace std::chrono;

    // merge sort
    auto start = high_resolution_clock::now();
    list_merge = merge_sort(list_merge);
    auto end = high_resolution_clock::now();
    std::println("Merge sort took {} µs",
                 duration_cast<microseconds>(end - start).count());

    // selection sort
    start = high_resolution_clock::now();
    selection_sort(list_select);
    end = high_resolution_clock::now();
    std::println("Selection sort took {} µs",
                 duration_cast<microseconds>(end - start).count());

    return 0;
}

