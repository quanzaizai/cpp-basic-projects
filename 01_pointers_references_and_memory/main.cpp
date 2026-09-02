// ==============================================================================
// 💡【知识点】C++ 指针、引用与底层内存布局 (Pointers, References & Memory Layout)
// 所属分类：C++ 核心基础语法第一讲
// 
// 🎓【零基础保姆级讲解】：
// 1. 指针 (Pointer) vs 引用 (Reference)：
// - 指针是一个独立的变量，在内存中真实占用 8 字节（64位系统），存储的是目标变量的物理地址。指针可以为空（nullptr），可以重新指向其他变量。
// - 引用是原变量的一个“别名（Alias）”，底层由编译器通过常量指针实现，但语法上没有自己独立的存储空间。引用必须在定义时初始化，且一旦绑定绝不可更改绑定对象。
// 
// 2. 栈内存 (Stack) vs 堆内存 (Heap)：
// - 栈内存：由编译器自动分配和释放（遵循先进后出 LIFO），速度极快，用于存放局部变量与函数调用栈帧。超出作用域 `{}` 立即自动销毁。
// - 堆内存：由程序员通过 `new` 手动向操作系统申请，速度相对较慢，必须通过 `delete` 手动释放，否则导致内存泄露（Memory Leak）。
// 
// 3. const 常量关键字的四种形态（面试高频必考）：
// - `const int a = 10;`        // a 的值不可修改
// - `const int* p = &a;`       // 常量指针：指向的值不可改（*p = 20 报错），指针本身指向可以改（p = &b 合法）
// - `int* const p = &a;`       // 指针常量：指针本身指向不可改（p = &b 报错），指向的值可以改（*p = 20 合法）
// - `const int* const p = &a;  // 指针和指向的值都不可改
// ==============================================================================
#include <iostream>
#include <iomanip>

void demonstrate_pointers_and_references() {
    std::cout << "--- 1. 指针与引用的物理区别 ---\n";
    int val = 100;

    // 1. 声明指针
    int* ptr = &val;

    // 2. 声明引用（别名）
    int& ref = val;

    std::cout << "  原始变量 val 的值: " << val << " | 物理地址: " << &val << "\n";
    std::cout << "  指针变量 ptr 的值: " << ptr << " | 解引用 *ptr: " << *ptr << " | 指针自身物理地址: " << &ptr << "\n";
    std::cout << "  引用变量 ref 的值: " << ref << " | 引用所指物理地址: " << &ref << " (与 val 地址完全相同！)\n\n";

    // 修改引用会直接影响原变量
    ref = 200;
    std::cout << "  通过 ref 修改为 200 后，val = " << val << ", *ptr = " << *ptr << "\n";
}

void demonstrate_stack_vs_heap() {
    std::cout << "\n--- 2. 栈内存 vs 堆内存生命周期 ---\n";

    // 栈上分配（离开作用域自动销毁）
    int stack_var = 42;
    std::cout << "  [栈内存] stack_var 地址: " << &stack_var << " (通常位于高地址区 0x7fff...)\n";

    // 堆上分配（必须手动 delete）
    int* heap_ptr = new int(888);
    std::cout << "  [堆内存] heap_ptr 指向的地址: " << heap_ptr << " (通常位于低地址区 0x6000...)\n";
    std::cout << "  [堆内存] heap_ptr 存储的数值: " << *heap_ptr << "\n";

    // 严谨内存释放：delete 后立即置 nullptr，防止悬挂指针 (Dangling Pointer / Wild Pointer)
    delete heap_ptr;
    heap_ptr = nullptr;
    std::cout << "  [堆内存] delete 释放完毕并将指针置为 nullptr，杜绝野指针访问。\n";
}

void demonstrate_const_qualifiers() {
    std::cout << "\n--- 3. const 常量与指针修饰词 (口诀：左定值，右定向) ---\n";
    int x = 10;
    int y = 20;

    // 形态 1：指向常量的指针 (const int*)
    const int* p1 = &x;
    // *p1 = 15; // ❌ 编译报错：不可通过 p1 修改 x 的值
    p1 = &y;     // ✅ 合法：p1 可以转向指向 y
    std::cout << "  const int* p1 可以改变指向，当前 *p1 = " << *p1 << "\n";

    // 形态 2：常量指针 (int* const)
    int* const p2 = &x;
    *p2 = 30;    // ✅ 合法：可以修改 x 的值
    // p2 = &y;  // ❌ 编译报错：p2 自身的指向不能再改变
    std::cout << "  int* const p2 可以修改所指的值，修改后 x = " << x << "\n";
}

int main() {
    std::cout << "============================================================\n";
    std::cout << "🚀 C++ 核心语法实战 01：指针、引用与底层内存布局\n";
    std::cout << "============================================================\n";

    demonstrate_pointers_and_references();
    demonstrate_stack_vs_heap();
    demonstrate_const_qualifiers();

    std::cout << "\n============================================================\n";
    std::cout << "🎉 模块 01 全部演示执行完毕！\n";
    std::cout << "============================================================\n";
    return 0;
}
