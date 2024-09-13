---
title: "Mingw-w64"
date: 2024-09-13T14:04:21+08:00
authors: 
    - "Samuka007"
categories:
    - "Advance"
tags:
    - "C++"
    - "Modern C++"
    - "Program"
summary: MinGW 是一个 Windows 平台上的开发环境，它提供了一套兼容 POSIX 的工具链，可以用来编译和运行 C/C++ 程序。MinGW 是一个缩写，它代表 Minimalist GNU for Windows。MinGW-w64 是 MinGW 的一个分支，它支持 64 位 Windows 系统。
draft: false
---

## 介绍

> - [MinGW-w64](https://www.mingw-w64.org/)

MinGW 是一个 Windows 平台上的开发环境，它提供了一套兼容 POSIX 的工具链，可以用来编译和运行 C/C++ 程序。MinGW 是一个缩写，它代表 Minimalist GNU for Windows。MinGW-w64 是 MinGW 的一个分支，它支持 64 位 Windows 系统。

## 安装

> - [Downloads - MinGW-w64](https://www.mingw-w64.org/downloads/)

`Mingw-w64` 的安装相对简单，并且许多项目提供了 `prebuilt` 的二进制包，可以直接下载安装。这里我们选择主流的两个项目，你应该选择其中一个进行安装。

### MSYS2

> - [MSYS2](https://www.msys2.org/)

MSYS2 是一个类似于 Cygwin 的项目，它提供了一套类 Unix 的环境，可以在 Windows 上运行。MSYS2 项目提供了一个软件包管理器，可以方便地安装 MinGW-w64。安装指南参考[MSYS2](https://www.msys2.org/)。

### w64devkit

> - [w64devkit on Mingw-w64](https://www.mingw-w64.org/downloads/#w64devkit)
> - [skeeto/w64devkit: Portable C and C++ Development Kit for x64 (and x86) Windows](https://github.com/skeeto/w64devkit)

w64devkit is a **portable** C and C++ development kit for x64 (and x86) Windows.

也就是说你可以把它直接丢在你的PE里，然后你在任意一台能启动的机子上都可以编译你的代码。另一方面，使用docker构建的开发环境，也很方便使用。

**安装步骤**：

- 下载 `w64devkit` 的二进制包
- 解压到你的目录下，例如 `C:\w64devkit`
- 将 `C:\w64devkit\bin` 添加到你的[`环境变量`]中
- 打开命令行，输入 `gcc --version`，如果能看到版本信息，说明安装成功

[`环境变量`]: ../environment_variable
