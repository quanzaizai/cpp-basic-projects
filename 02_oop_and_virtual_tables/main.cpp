// ==============================================================================
// 💡【知识点】C++ 面向对象、继承多态与虚函数表机制 (OOP & VTable Deep Dive)
// 所属分类：C++ 核心基础语法第二讲
// 
// 🎓【核心考点与原理】：
// 1. 封装 (Encapsulation)、继承 (Inheritance) 与 多态 (Polymorphism)。
// 2. 动态多态的底层原理 —— 虚函数表 (vtable) 与 虚表指针 (vptr)：
// - 只要类中声明了 `virtual` 虚函数，编译器就会为该类生成一张虚函数表（包含所有虚函数的地址）。
// - 实例化该类的每个对象头部，都会隐式嵌入一个 8 字节的 `vptr` 指针，指向该类的 `vtable`。
// - 当使用基类指针调用 `ptr->speak()` 时，CPU 会在运行时通过 `vptr` 查表找到子类重写的函数地址，
// 完成“动态绑定（Dynamic Dispatch / Late Binding）”。
// 3. 虚析构函数的重要性（面试 100% 必考）：
// - 基类的析构函数必须声明为 `virtual ~Base()`！
// - 否则当 `Base* ptr = new Derived(); delete ptr;` 时，只会调用基类析构，导致子类特有资源泄漏。
// ==============================================================================
#include <iostream>
#include <string>
#include <memory>

// 基类：动物抽象类
class Animal {
public:
    explicit Animal(const std::string& name) : name_(name) {
        std::cout << "  [Animal 基类构造] " << name_ << "\n";
    }

    // 虚析构函数：保证多态删除时正确调用子类析构
    virtual ~Animal() {
        std::cout << "  [Animal 基类析构] " << name_ << "\n";
    }

    // 纯虚函数 (Pure Virtual Function) -> 使 Animal 成为抽象类 (Abstract Class)
    virtual void speak() const = 0;

    // 普通虚函数 (Virtual Function)
    virtual void eat() const {
        std::cout << "  " << name_ << " 正在进食普通饲料。\n";
    }

    const std::string& get_name() const { return name_; }

protected:
    std::string name_; // 允许派生类直接访问
};

// 派生类：狗
class Dog : public Animal {
public:
    explicit Dog(const std::string& name, const std::string& breed)
        : Animal(name), breed_(breed) {
        std::cout << "  [Dog 子类构造] 品种: " << breed_ << "\n";
    }

    ~Dog() override {
        std::cout << "  [Dog 子类析构] 清理狗专属资源\n";
    }

    // 重写 (override) 纯虚函数
    void speak() const override {
        std::cout << "  🐶 " << name_ << " (" << breed_ << "): 汪汪汪！\n";
    }

    void eat() const override {
        std::cout << "  🐶 " << name_ << " 正在开心地啃骨头！\n";
    }

private:
    std::string breed_;
};

// 派生类：猫
class Cat : public Animal {
public:
    explicit Cat(const std::string& name) : Animal(name) {
        std::cout << "  [Cat 子类构造]\n";
    }

    ~Cat() override {
        std::cout << "  [Cat 子类析构] 清理猫专属资源\n";
    }

    void speak() const override {
        std::cout << "  🐱 " << name_ << ": 喵喵喵～\n";
    }
};

// 统一的多态调用接口（接收基类引用）
void make_animal_talk(const Animal& animal) {
    animal.speak();
    animal.eat();
}

int main() {
    std::cout << "============================================================\n";
    std::cout << "🚀 C++ 核心语法实战 02：面向对象、继承多态与虚析构函数\n";
    std::cout << "============================================================\n";

    std::cout << "\n[步骤 1] 实例化子类对象...\n";
    Dog my_dog("旺财", "金毛犬");
    Cat my_cat("咪咪");

    std::cout << "\n[步骤 2] 通过基类引用实现动态多态调用...\n";
    make_animal_talk(my_dog);
    make_animal_talk(my_cat);

    std::cout << "\n[步骤 3] 验证基类指针指向子类对象与安全虚析构...\n";
    {
        Animal* poly_ptr = new Dog("大黄", "中华田园犬");
        poly_ptr->speak();
        
        // 关键：因为 ~Animal() 是 virtual，delete 会先调用 ~Dog() 再调用 ~Animal()
        delete poly_ptr;
    }

    std::cout << "\n============================================================\n";
    std::cout << "🎉 模块 02 全部演示执行完毕！\n";
    std::cout << "============================================================\n";
    return 0;
}
