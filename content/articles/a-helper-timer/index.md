---
title: "基于chrono的简易计时库"
date: 2023-09-13T23:20:49+08:00
authors: 
    - "Samuka007"
categories: "Advance"
tags:
    - "C++"
summary: 给大家拿来算函数运行时间的玩具库
draft: false
---
这是一个给大家拿来算函数运行时间的玩具库。

## 先看用法

```c++
#include "timer11.hpp"
#include <iostream>
#include <functional>

void timeConsum() {
    int c = 6;
}

void funcWithArgs( int a, int b ) {
    int c = 666;
}

int main() {
    std::cout << runtime::ns::count( timeConsum ) << "ns\n";
    std::cout << runtime::ms::countNtimes( 10000000, timeConsum ) << "ms\n";
    std::cout << runtime::s::countNtimes( 1000000000, funcWithArgs, 1, 2 ) << "s\n";
}

// 运行结果：
// 41ns
// 18ms
// 2s
```

### namespace

`runtime` namespace 下, `ns` `ms` `s` 下的函数分别返回不同长度时间单位的整数值

### 函数说明

**count ( `function_name`, `function_arguments(optional)` )**

传入 `函数名` 以及 **可选** 的 `函数参数`，返回该命名空间下时间单位的运行时间。

**countNtimes ( `run_times`, `function_name`, `function_arguments(optional)` )**

传入 `运行次数`， `函数名` 以及 **可选** 的 `函数参数`，将该传入函数名所对应的函数执行 `运行次数` 次，返回该命名空间下时间单位的运行时间。

## 更推荐的做法

实际上一个count函数就可以解决重复执行的问题，只需要使用lambda函数，甚至实现批量化计时。

**lambda表达式格式简单来说就是**

\[`从环境中获取的变量`\]\(`向传入的参数`\) \{ `函数体，可以包含返回值，返回值自动推导` \}

```c++
// run from 2500 times to 20000 times
for ( auto i{2500}; i<=20000; i*=2 ) {
    std::cout << "run " << i << " times, cost "
        << runtime::ns::count(
            [i]() { // 从这里开始
                for ( auto j {0}; j<i; ++j ) {  
                    timeConsum();               
                }                               
            } // 到这里结束，是lambda表达式
        ) 
        << " ns\n";
}
// result:
// run 2500 times, cost 4292 ns
// run 5000 times, cost 8167 ns
// run 10000 times, cost 16209 ns
```

## 注意

{{< alert >}}
**注意** 未限定传入参数类型，请保证传入参数正确。
{{< /alert >}}

## 如何包含在项目中

点击文章标题旁的编辑图标前往github仓库在同一目录下下载头文件。

你也可以直接将以下内容包含在你的源文件中。

> ps: 你的编译器至少要支持`C++11`标准（一般都支持的啦）。

```c++
#include <chrono>

namespace runtime {
namespace ms {

template < typename Func, typename... Arg >
long long count( Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    func( args... );
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::milliseconds > (std::chrono::steady_clock::now() - start).count();
}

template < typename Func, typename... Arg >
long long countNtimes( auto times, Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    for ( auto i{0}; i<times; ++i ) {
        func(args...);
    }
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::milliseconds > (std::chrono::steady_clock::now() - start).count();
}

}

namespace ns {
    
template < typename Func, typename... Arg >
long long count( Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    func( args... );
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::nanoseconds > (std::chrono::steady_clock::now() - start).count();
}

template < typename Func, typename... Arg >
long long countNtimes( auto times, Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    for ( auto i{0}; i<times; ++i ) {
        func(args...);
    }
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::nanoseconds > (std::chrono::steady_clock::now() - start).count();
}

}

namespace s {

template < typename Func, typename... Arg >
long long count( Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    func( args... );
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::seconds > (std::chrono::steady_clock::now() - start).count();
}

template < typename Func, typename... Arg >
long long countNtimes( auto times, Func&& func, Arg&&...args ) {
    auto start = std::chrono::steady_clock::now();
    for ( auto i{0}; i<times; ++i ) {
        func(args...);
    }
    auto stop = std::chrono::steady_clock::now();
    return std::chrono::duration_cast< std::chrono::seconds > (std::chrono::steady_clock::now() - start).count();
}
}

}
```

关于chrono库的使用大家可以参考 [日期和时间工具 - cppreference.com](https://en.cppreference.com/w/cpp/chrono)
