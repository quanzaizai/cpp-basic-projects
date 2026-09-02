# 💡 Modern C++ 7 大核心语法全景实战 (cpp-basic-projects)

所属专业课：《C++ 高级程序设计》《面向对象与现代特性》

---

## 📖 7 大核心模块目录结构速查

```text
cpp-basic-projects/
├── 01_pointers_references_and_memory/    # 💡 [第1讲] 指针 vs 引用区别、堆栈内存生命周期、const 四种指针形态
├── 02_oop_and_virtual_tables/            # 💡 [第2讲] 面向对象封装/继承/多态、虚函数表 vtable/vptr 底层原理与虚析构
├── 03_raii_and_smart_pointers/           # 💡 [第3讲] RAII 哲学、unique_ptr、shared_ptr 引用计数与 weak_ptr
├── 04_move_semantics_and_rvalues/        # 💡 [第4讲] 左值与右值引用、移动构造函数 O(1) 零拷贝掠夺指针、std::move
├── 05_templates_and_stl_containers/      # 💡 [第5讲] 函数/类模板编译期实例化、vector 扩容、map 红黑树与哈希表
├── 06_modern_cpp_lambdas_and_functional/ # 💡 [第6讲] Lambda 闭包捕获模式 ([&], [=])、std::function 通用多态包装器
├── 07_multithreading_and_concurrency/    # 💡 [第7讲] std::thread 并发、std::mutex 互斥锁、RAII lock_guard、std::atomic
├── CMakeLists.txt                        # ⚙️ CMake 构建脚本
├── Makefile                              # ⚙️ 一键测试脚本
└── README.md                             # 📘 项目全景说明
```

---

## 🛠️ 构建与测试运行

```bash
make test  # 一键自动编译并依次运行全部 7 个模块的演示程序
```
