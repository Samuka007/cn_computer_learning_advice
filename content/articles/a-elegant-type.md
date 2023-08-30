---
title: "如何优雅的在C++中限定模版类型"
date: 2023-08-26T22:46:17+08:00
authors: 
    - "Samuka007"
categories: "Advance"
tags:
    - "C++"
    - "Modern C++"
    - "Program"
summary: Concept 作为 `C++ 20` 引入的一个新特性，是一个语法糖，同时也提供了相当一部分模版类型限定的预设，以及提供了用户友好的模版匹配失败报错。
draft: false
---

## 引入

**Concept** 作为 `C++ 20` 引入的一个新特性，是一个语法糖，同时也提供了相当一部分模版类型限定的预设，以及提供了用户友好的模版匹配失败报错。

### 直接使用 **概念**

譬如，通过以下代码，你可以限定你的模版类 / 模版函数的模版类型 **Ty** 必须支持比较：

```C++
template < typename Ty >
requires std::totally_ordered < Ty > // 要求 Ty 完全可比较
void print_less ( Ty a, Ty b )
{
    std::cout << (a < b ? a : b) << "is the less.";
}
```

当然，要使用模版库，你需要引入头文件 **\<concepts\>** ，从而使用基础库概念们的定义。

### 定义 **概念**

当遇到需要复用的一系列概念的集合的限定，你可以像这样指定：

```C++
template < typename Ty >
concept comparable_integral = integral< Ty > && std::totally_ordered < Ty >;

template < comparable_integral T >
void check_if_int_comparable( T a, T b )
{
    std::cout << (a < b ? a : b) ;
}

int main()
{
    check_if_int_comparable( 3, 4 );
    // check_if_int_comparable( 0.5, 0.6 ); // parse failed
}
```

## 参考

更多关于 **约束传入模版类型** 详见[**C++模板如何要求传入的类型符合要求** - mq白](https://zhuanlan.zhihu.com/p/609591745)

更多关于 **Concept** 请详见 [**概念库 (C++20)** - cppreference.com](https://zh.cppreference.com/w/cpp/concepts) 与 [**C++20高级编程**(英文版) - Professional C++ ( Marc Gregoire )](https://scut-oc.obs.cn-south-1.myhuaweicloud.com/ebooks/CS_classic/C_C%2B%2B/Professional%20C%2B%2B%20%28Marc%20Gregoire%29%20%28z-lib.org%29.pdf) 中的模版章节。
