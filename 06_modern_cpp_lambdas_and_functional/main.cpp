/**
 * ==============================================================================
 * 💡【知识点】现代 C++ 闭包 Lambda 表达式与 std::function
 * 所属分类：C++ 核心基础语法第六讲
 * 
 * 🎓【核心考点与原理】：
 * 1. Lambda 表达式语法：`[捕获列表](参数列表) -> 返回类型 { 函数体 }`
 *    - `[]` : 不捕获任何外部变量
 *    - `[&]` : 以引用方式捕获所有外部变量（注意悬挂引用生命周期！）
 *    - `[=]` : 以值拷贝方式捕获所有外部变量
 *    - `[x, &y]` : 混合捕获，x 为值拷贝，y 为引用
 * 2. std::function 与 std::bind (位于 <functional>):
 *    - 可调用对象的“多态包装器”（包含普通函数、函数指针、Lambda、仿函数 Functor）。
 * ==============================================================================
 */

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

void demonstrate_lambdas() {
    std::cout << "--- 1. Lambda 表达式捕获方式演示 ---\n";
    int factor = 3;
    int base_offset = 10;

    // 值捕获与引用捕获
    auto calculate = [factor, &base_offset](int input) -> int {
        base_offset += 5; // 修改引用捕获的外部变量
        return input * factor + base_offset;
    };

    std::cout << "  执行 Lambda 计算 (输入 4): " << calculate(4) << "\n";
    std::cout << "  外部 base_offset 被修改为: " << base_offset << "\n";
}

void demonstrate_std_function() {
    std::cout << "\n--- 2. std::function 回调机制 (Callback Pattern) ---\n";
    
    // 声明一个接收 (int, int) 返回 int 的通用函数包装器
    std::function<int(int, int)> op;

    // 绑定普通加法 Lambda
    op = [](int a, int b) { return a + b; };
    std::cout << "  std::function 执行加法: 10 + 20 = " << op(10, 20) << "\n";

    // 绑定乘法 Lambda
    op = [](int a, int b) { return a * b; };
    std::cout << "  std::function 执行乘法: 10 * 20 = " << op(10, 20) << "\n";
}

int main() {
    std::cout << "============================================================\n";
    std::cout << "🚀 C++ 核心语法实战 06：Lambda 闭包与 std::function 回调\n";
    std::cout << "============================================================\n";

    demonstrate_lambdas();
    demonstrate_std_function();

    std::cout << "\n============================================================\n";
    std::cout << "🎉 模块 06 全部演示执行完毕！\n";
    std::cout << "============================================================\n";
    return 0;
}
