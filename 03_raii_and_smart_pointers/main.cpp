// ==============================================================================
// 💡【知识点】RAII 机制与现代智能指针体系 (RAII & Smart Pointers)
// 所属分类：C++ 核心基础语法第三讲
// 
// 🎓【核心考点与原理】：
// 1. 什么是 RAII (Resource Acquisition Is Initialization 资源获取即初始化)？
// - C++ 区别于 C / Java 的最伟大设计哲学：将资源的生命周期与栈对象的生命周期绑定。
// - 构造函数申请资源（内存、文件句柄、互斥锁），析构函数自动释放资源。无论是正常执行完毕还是中途抛出异常，
// C++ 都会保证自动触发局部对象的析构函数（栈展开 Stack Unwinding），彻底根除内存泄露！
// 
// 2. 现代三大智能指针（全部位于 <memory> 头文件中）：
// - std::unique_ptr: 独占所有权指针。不可拷贝，只能移动（std::move）。零额外开销。
// - std::shared_ptr: 共享所有权指针。内部维护一个原子引用计数（Reference Count）。当最后一个 shared_ptr 销毁时释放对象。
// - std::weak_ptr: 弱引用观察者指针。不增加引用计数，用于解决 shared_ptr 相互引用导致的“循环引用死锁内存泄漏”。
// ==============================================================================
#include <iostream>
#include <memory>
#include <string>

class Resource {
public:
    explicit Resource(const std::string& name) : name_(name) {
        std::cout << "  ✨ [资源分配] " << name_ << " 成功创建！\n";
    }

    ~Resource() {
        std::cout << "  💥 [资源销毁] " << name_ << " 被自动安全释放！\n";
    }

    void do_work() const {
        std::cout << "  ⚙️  " << name_ << " 正在高效工作中...\n";
    }

private:
    std::string name_;
};

void test_unique_ptr() {
    std::cout << "\n--- 1. std::unique_ptr 独占指针演示 ---\n";
    // 推荐使用 std::make_unique（C++14），异常安全且高效
    std::unique_ptr<Resource> u1 = std::make_unique<Resource>("独占资源 A");
    u1->do_work();

    // std::unique_ptr<Resource> u2 = u1; // ❌ 编译报错：禁止拷贝！
    std::unique_ptr<Resource> u2 = std::move(u1); // ✅ 转移所有权给 u2
    if (!u1) {
        std::cout << "  -> u1 的所有权已成功 std::move 转移，u1 变为 nullptr\n";
    }
    u2->do_work();
} // 离开作用域，u2 自动析构释放资源

void test_shared_and_weak_ptr() {
    std::cout << "\n--- 2. std::shared_ptr 共享引用计数与 std::weak_ptr 观察者 ---\n";
    std::shared_ptr<Resource> s1 = std::make_shared<Resource>("共享资源 B");
    std::cout << "  创建 s1 后，引用计数 (use_count): " << s1.use_count() << "\n";

    {
        std::shared_ptr<Resource> s2 = s1; // 拷贝构造，引用计数 +1
        std::cout << "  创建 s2 共享后，引用计数 (use_count): " << s1.use_count() << "\n";

        // 创建 weak_ptr 观察者
        std::weak_ptr<Resource> w = s1;
        std::cout << "  创建 weak_ptr w 后，引用计数依然是: " << s1.use_count() << " (不增加计数！)\n";

        // 通过 weak_ptr.lock() 安全提升为 shared_ptr
        if (auto locked = w.lock()) {
            std::cout << "  -> weak_ptr 成功 lock 锁定资源并调用: ";
            locked->do_work();
        }
    } // s2 离开作用域销毁，引用计数 -1

    std::cout << "  离开内层块后，s2 销毁，当前引用计数: " << s1.use_count() << "\n";
} // 离开作用域，s1 销毁，计数变为 0，资源自动释放

int main() {
    std::cout << "============================================================\n";
    std::cout << "🚀 C++ 核心语法实战 03：RAII 机制与三大智能指针实战\n";
    std::cout << "============================================================\n";

    test_unique_ptr();
    test_shared_and_weak_ptr();

    std::cout << "\n============================================================\n";
    std::cout << "🎉 模块 03 全部演示执行完毕！\n";
    std::cout << "============================================================\n";
    return 0;
}
