#include <thread>
#include <vector>
#include <iostream>
#include <functional>

DenseMat MatMulParal(const DenseMat& a, const DenseMat& b, int thread_count) {
    DenseMat c(a.Rows(), b.Cols());
    std::function<void(int64_t, int64_t)> f =
        [&](int64_t firRow, int64_t numRow) {
        for (int64_t row = firRow; row <= firRow + numRow; row++) {
            for (int64_t col = 0; col < c.Cols(); col++) {
                for (int64_t q = 0; q < a.Cols(); q++) {
                    c(row, col) += a(row, q) * b(q, col);
                }
            }
        }
    };

    thread_count--;
    if (thread_count == 0) {
        f(0, c.Rows() - 1);
    } else {
        std::vector<std::function<void(int64_t, int64_t)>> funcs;
        for (int i = 0; i < thread_count; i++) {
            funcs.push_back(f);
        }

        int64_t rowNum = c.Rows() / (thread_count + 1);
        std::vector<std::thread> threads;
        for (int64_t i = 0; i < thread_count; i++) {
            threads.push_back(std::thread(funcs[i], i * rowNum, rowNum - 1));
        }
        f(thread_count * rowNum, c.Rows() - thread_count * rowNum - 1);

        for (int i = 0; i < thread_count; i++) {
            threads[i].join();
        }
    }
    return c;
}
