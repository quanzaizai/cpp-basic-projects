# 💡 Modern C++ 核心语法与现代特性实战全景 (cpp-basic-projects)

本项目是专为巩固 **Modern C++（C++11/14/17）核心语法与底层原理** 打造的保姆级实战代码库。每个模块均配有**超详尽的逐行注释、底层内存模型图解与避坑指南**。

---

## 📚 模块学习路径

| 编号 | 模块名称 | 核心知识点与考点 |
| :--- | :--- | :--- |
| **01** | [`01_pointers_references_and_memory`](./01_pointers_references_and_memory) | 指针 vs 引用区别、堆栈内存分配、`const` 常量四种指针形态 |
| **02** | [`02_oop_and_virtual_tables`](./02_oop_and_virtual_tables) | 封装/继承/多态、虚函数表 `vtable` 与虚表指针 `vptr` 底层、虚析构函数 |
| **03** | [`03_raii_and_smart_pointers`](./03_raii_and_smart_pointers) | RAII 哲学、`unique_ptr` 独占所有权、`shared_ptr` 引用计数、`weak_ptr` |
| **04** | [`04_move_semantics_and_rvalues`](./04_move_semantics_and_rvalues) | 左值与右值、右值引用 `Type&&`、移动构造函数 O(1) 零拷贝、`std::move` |
| **05** | [`05_templates_and_stl_containers`](./05_templates_and_stl_containers) | 函数/类模板编译期实例化、`std::vector`、`std::map` (红黑树)、`std::unordered_map` (哈希表) |
| **06** | [`06_modern_cpp_lambdas_and_functional`](./06_modern_cpp_lambdas_and_functional) | Lambda 捕获模式 (`[&]`, `[=]`)、闭包、`std::function` 通用函数包装与回调 |
| **07** | [`07_multithreading_and_concurrency`](./07_multithreading_and_concurrency) | `std::thread` 并发、`std::mutex` 锁与 RAII `lock_guard`、`std::atomic` 原子操作 |

---

## 🛠️ 一键编译与测试

```bash
make test    # 自动编译并依次运行全部 7 大模块
```
