// ==============================================================================
// 💡【知识点】移动语义、左值与右值引用 (Move Semantics & Rvalues)
// 所属分类：C++ 核心基础语法第四讲 (C++11 革命性特性)
// 
// 🎓【核心考点与原理】：
// 1. 什么是左值 (Lvalue) 与右值 (Rvalue)？
// - 左值：可以在内存中寻址、有明确变量名、可以取地址 `&` 的表达式（如 `int a = 10;` 中的 `a`）。
// - 右值：临时产生的无名对象、字面量、将要被销毁的临时值（如 `10`, `a + b`, 函数返回的临时对象）。
// 
// 2. 为什么需要移动语义 (Move Semantics)？
// - 在传统 C++98 中，把一个包含大数组的 vector 传给另一个 vector 时，必须进行“深拷贝（Deep Copy）”：
// 重新 malloc 内存 -> 遍历复制每个元素 -> 销毁旧临时对象。性能极低。
// - C++11 引入了右值引用 `Type&&` 和移动构造函数：直接“偷取”临时对象的内存指针（浅拷贝指针），
// 将原指针置为 nullptr，将深拷贝的 O(N) 耗时降低到 O(1) 指针交换！
// ==============================================================================
#include <iostream>
#include <cstring>
#include <utility>

class BigBuffer {
public:
    // 普通构造函数
    explicit BigBuffer(size_t size, const char* label) : size_(size) {
        data_ = new char[size_];
        label_ = label;
        std::cout << "  🔨 [普通构造] " << label_ << " (申请了 " << size_ << " 字节内存)\n";
    }

    // 1. 拷贝构造函数 (深拷贝 - 耗时)
    BigBuffer(const BigBuffer& other) : size_(other.size_), label_(other.label_ + "_copy") {
        data_ = new char[size_];
        std::memcpy(data_, other.data_, size_);
        std::cout << "  📋 [深拷贝构造] 从 " << other.label_ << " 完整复制了 " << size_ << " 字节\n";
    }

    // 2. 移动构造函数 (右值移动 - 极速零拷贝)
    BigBuffer(BigBuffer&& other) noexcept 
        : data_(other.data_), size_(other.size_), label_(other.label_ + "_moved") {
        // 直接偷取对方指针，并将对方置空
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "  ⚡ [移动构造] 直接掠夺了 " << other.label_ << " 的堆内存指针！O(1) 零拷贝！\n";
    }

    // 析构函数
    ~BigBuffer() {
        if (data_) {
            std::cout << "  💥 [析构释放] " << label_ << " 释放了堆内存\n";
            delete[] data_;
        } else {
            std::cout << "  👻 [空析构] " << label_ << " (指针已空，无需释放)\n";
        }
    }

private:
    char* data_{nullptr};
    size_t size_{0};
    std::string label_;
};

int main() {
    std::cout << "============================================================\n";
    std::cout << "🚀 C++ 核心语法实战 04：左值/右值引用与 std::move 移动语义\n";
    std::cout << "============================================================\n";

    std::cout << "\n[场景 1] 演示传统左值深拷贝 (复制一个具名对象)...\n";
    BigBuffer buf1(1024 * 1024, "Buffer-A");
    BigBuffer buf2 = buf1; // 触发拷贝构造 (耗费深拷贝)

    std::cout << "\n[场景 2] 演示 std::move 强制将左值转为右值进行移动...\n";
    // std::move 本质上并不移动任何数据，只是强制将左值类型转换为右值引用 (static_cast<T&&>)
    BigBuffer buf3 = std::move(buf1); // 触发移动构造 (零拷贝)

    std::cout << "\n[场景 3] 离开作用域，观察析构行为...\n";
    return 0;
}
