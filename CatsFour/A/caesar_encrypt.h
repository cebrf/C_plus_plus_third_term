#pragma once
#include <thread>
#include <mutex>
#include <atomic>
#include <string>
#include <vector>
#include <iostream>
#include <functional>

void CaesarEncrypt(std::string* s)
{
    std::int64_t n = s->size(),
        m = std::thread::hardware_concurrency();
    m = 4;

    std::vector<std::function<void(char*, char*)>> funcs;
    for (int i = 0; i < m; i++)
    {
        funcs.push_back(std::function([&](char* fir, char* las) {
            for (; fir != las; fir++)
            {
                *fir = 'a' + (*fir + 3 - 'a') % 26;
            }
            *fir = 'a' + (*fir + 3 - 'a') % 26;
            }));
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < m - 1; i++)
    {
        threads.push_back(std::thread(funcs[i],
            &(*s)[n / m * i],
            &(*s)[n / m * (i + 1) - 1]));
    }
    funcs[m - 1](&(*s)[n / m * (m - 1)], &(*s)[n - 1]);

    for (int i = 0; i < m - 1; i++)
    {
        threads[i].join();
    }
}
