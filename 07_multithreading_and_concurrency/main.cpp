// ==============================================================================
// 💡【知识点】现代 C++ 多线程并发编程与同步原语 (Multithreading & Concurrency)
// 所属分类：C++ 核心基础语法第七讲
// 
// 🎓【核心考点与原理】：
// 1. std::thread 生命周期：必须在销毁前调用 `.join()` 或 `.detach()`。
// 2. 互斥锁机制：
// - `std::mutex` + `std::lock_guard`: RAII 作用域自动加锁与解锁（不可手动提前释放）。
// - `std::unique_lock`: 灵活锁，支持中途手动 unlock()，专为条件变量设计。
// 3. std::atomic 原子操作：无锁（Lock-Free）保证整数增减并发安全。
// ==============================================================================
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

std::mutex g_cout_mutex;
std::atomic<int> g_atomic_counter{0};
int g_unsafe_counter = 0;

void worker_task(int thread_id) {
    for (int i = 0; i < 1000; ++i) {
        g_atomic_counter.fetch_add(1, std::memory_order_relaxed); // 原子安全自增
        g_unsafe_counter++; // 非安全自增（会发生数据竞争 Data Race）
    }

    {
        // 使用 RAII lock_guard 保护控制台输出，防止多线程打印字符错乱
        std::lock_guard<std::mutex> lock(g_cout_mutex);
        std::cout << "  [线程 " << thread_id << "] 完成 1000 次累加任务\n";
    }
}

int main() {
    std::cout << "============================================================\n";
    std::cout << "🚀 C++ 核心语法实战 07：多线程并发、互斥锁与原子操作\n";
    std::cout << "============================================================\n";

    constexpr int THREAD_COUNT = 4;
    std::vector<std::thread> threads;

    std::cout << "[步骤 1] 启动 4 个并发线程分别累加 1000 次...\n";
    for (int i = 1; i <= THREAD_COUNT; ++i) {
        threads.emplace_back(worker_task, i);
    }

    // 等待所有线程执行完毕
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\n[步骤 2] 结果对比验证:\n";
    std::cout << "  ✅ 原子计数器 (std::atomic): " << g_atomic_counter.load() << " (预期精准 4000)\n";
    std::cout << "  ⚠️ 非原子普通计数器: " << g_unsafe_counter << " (可能发生数据竞争丢失)\n";

    std::cout << "\n============================================================\n";
    std::cout << "🎉 模块 07 全部演示执行完毕！\n";
    std::cout << "============================================================\n";
    return 0;
}
