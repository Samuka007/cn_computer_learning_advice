---
title: "引用折叠+万能引用+std::forward == 完美转发"
date: 2023-08-28T09:32:27+08:00
authors: 
    - "Samuka007"
categories:
    - "Advance"
tags:
    - "C++"
    - "Modern C++"
    - "Program"
summary: 不想再只为某个重载了复制和移动两个版本的函数，而去写两遍一模一样的代码？你需要完美转发xd
draft: false
---

C++作为一门*兼顾优雅与效率*的语言，自然不会让你幸苦写几遍代码只为了辨析复制和移动～

所以，当你再遇到像

```c++
void insert ( const T& value );
void insert ( T&& value );
```

这样要重载两次的版本时，倘若他们之间除了形参不同，没有其他不同的话，你大可以使用 **完美转发** 来帮你优雅地省下复制粘贴的时间～（不是

要想使用 **完美转发**，你需要了解：

* 万能引用 与 引用折叠，见 [引用声明](https://zh.cppreference.com/w/cpp/language/reference)
* [std::**forward**](https://zh.cppreference.com/w/cpp/utility/forward)
* 并掌握一点点 [**模版形参推导**](https://zh.cppreference.com/w/cpp/language/template_argument_deduction#.E4.BB.8E.E5.87.BD.E6.95.B0.E8.B0.83.E7.94.A8.E6.8E.A8.E5.AF.BC) 的知识

如果你对于上述名词感到非常陌生，对于移动构造、移动语义也不太了解，可以先了解前置知识：

* 右值，见 [值类别](https://zh.cppreference.com/w/cpp/language/value_category)
* [移动构造函数](https://zh.cppreference.com/w/cpp/language/move_constructor) 与 [移动运算符](https://zh.cppreference.com/w/cpp/language/move_assignment)
* [std::**move**](https://zh.cppreference.com/w/cpp/utility/move)

其实在cppreference中，已经讲述了 完美转发 的原理了（见 [引用声明](https://zh.cppreference.com/w/cpp/language/reference) - 转发引用）。
这里通过一个demo来演示完美转发的基本使用，你也可以点此前往 [Compiler Explorer](https://godbolt.org/z/1hds1YGeh) 试一试。

> Talk is cheap. Show me the code. *Linus Torvalds*

```c++
#include    <cstdio>
#include    <utility>

using namespace std;

struct X {
    X()             { puts("X()"); }
    virtual ~X()    { puts("~X()"); }

    // copy constructor
    // X&, const X& and const X&& will call this
    X( const X& )   { puts("X( const X& )"); } 

    // move constructor
    // X&& will call this
    X( X&& )noexcept{ puts("X( X&& )"); }
};

// here Ty can be (const) X and X&
// if Ty == X, Ty&& == X&&
// if Ty == X&, Ty&& == X& && == X&
template < typename Ty > 
void construct ( Ty&& x ) {
    // in order to call constructor instead of generate a reference,
    // here use 'decay_t<Ty>' instead of 'auto'
    // you actually can write it like
    // decay_t<decltype(x)> newX ( forward<Ty>(x) );
    // which is a much more complex way to do the same thing
    decay_t<Ty> newX ( forward<Ty>(x) );
}

int main() {
    X x;
    puts("------");
    construct ( x ); // newX is a copy of x
    puts("------");
    construct ( move(x) ); // newX is move from x
    puts("------");
    // x call ~X()
}
```

或者，在`C++20`中，你也可以综合auto的形参推导和decltype来进一步省略：

```c++
void construct ( auto&& x ) {
    auto newX ( forward<decltype(x)>(x) );
}
```

> 什么时候可以 auto auto ( auto auto ) { auto; }

在这里你也可以找到关于万能引用、引用折叠与完美转发的关系：[现代C++之万能引用、完美转发、引用折叠 - Francis - 知乎](https://zhuanlan.zhihu.com/p/99524127)
