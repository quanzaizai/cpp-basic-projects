// ==============================================================================
// 💡【知识点】C++ 泛型模板编程与 STL 常用容器体系 (Templates & STL Containers)
// 所属分类：C++ 核心基础语法第五讲
// 
// 🎓【核心考点与原理】：
// 1. 函数模板 (Function Template) 与 类模板 (Class Template)。
// 2. 编译期模板实例化机制：
// - C++ 模板是在编译期（Compile-Time）根据传入的具体类型生成特化代码的，具有“零运行时抽象惩罚（Zero-Cost Abstraction）”。
// 3. 核心 STL 容器精解：
// - std::vector: 动态连续数组，支持 O(1) 随机访问，尾插平摊 O(1)，扩容倍数通常为 1.5 或 2 倍。
// - std::map: 基于红黑树（Red-Black Tree）实现的有序键值对，查找/插入/删除均为 O(log N)。
// - std::unordered_map: 基于哈希表（Hash Table）实现的无序键值对，平均时间复杂度 O(1)。
// ==============================================================================
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

// 1. 泛型函数模板
template <typename T>
T my_max(T a, T b) {
    return (a > b) ? a : b;
}

// 2. 泛型类模板：简易键值对容器
template <typename K, typename V>
class SimplePair {
public:
    SimplePair(K k, V v) : key_(k), value_(v) {}
    void print() const {
        std::cout << "  Pair[" << key_ << " => " << value_ << "]\n";
    }
private:
    K key_;
    V value_;
};

void demonstrate_stl_containers() {
    std::cout << "\n--- STL 核心容器用法演示 ---\n";

    // 1. std::vector 动态数组
    std::vector<int> nums = {5, 2, 8, 1, 9};
    nums.push_back(10);
    std::sort(nums.begin(), nums.end()); // 算法库快速排序
    std::cout << "  std::vector 排序后内容: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // 2. std::map (有序红黑树)
    std::map<std::string, int> scores;
    scores["Alice"] = 95;
    scores["Charlie"] = 88;
    scores["Bob"] = 92;
    std::cout << "  std::map (按 Key 字典序自动排序):\n";
    for (const auto& [name, score] : scores) { // C++17 结构化绑定 (Structured Binding)
        std::cout << "    " << name << " -> " << score << " 分\n";
    }

    // 3. std::unordered_map (哈希表)
    std::unordered_map<std::string, std::string> configs = {
        {"host", "127.0.0.1"},
        {"port", "8080"}
    };
    std::cout << "  std::unordered_map 快速 O(1) 查询 host: " << configs["host"] << "\n";
}

int main() {
    std::cout << "============================================================\n";
    std::cout << "🚀 C++ 核心语法实战 05：泛型模板编程与 STL 容器全景\n";
    std::cout << "============================================================\n";

    std::cout << "[步骤 1] 验证函数模板与类模板...\n";
    std::cout << "  my_max(10, 20) = " << my_max(10, 20) << "\n";
    std::cout << "  my_max(3.14, 1.59) = " << my_max(3.14, 1.59) << "\n";

    SimplePair<std::string, int> pair1("Age", 22);
    pair1.print();

    demonstrate_stl_containers();

    std::cout << "\n============================================================\n";
    std::cout << "🎉 模块 05 全部演示执行完毕！\n";
    std::cout << "============================================================\n";
    return 0;
}
