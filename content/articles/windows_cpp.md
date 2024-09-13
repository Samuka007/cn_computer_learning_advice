---
title: "VSCode C++项目 Windows环境 从零配置保姆指南"
date: 2024-09-13T14:04:21+08:00
authors: 
    - "Samuka007"
categories:
    - "Advance"
tags:
    - "VSCode"
    - "C++"
    - "Windows"
summary: 本篇指南会带你从零开始，在完全干净的Windows环境中，配置一个足够上项目规模的，基于VSCode的，现代的C++开发环境。
draft: false
---

本篇指南会带你从零开始，在完全干净的Windows环境中，配置一个足够上项目规模的，基于VS Code的，现代的C++开发环境。

配置预览：

- Visual Studio Code
- Mingw-w64 (GCC)
- XMake
- Clangd

## 配置Visual Studio Code

1. 完成安装：[在Windows上安装 Visual Studio Code](../install_vscode_on_windows)
2. （可选）新建一个Profile，避免插件污染，以及过多插件在同一个Profile造成的加载缓慢：[Profile](../using_vscode#profile)
3. 安装 `C/C++ Extension Pack` 插件，参考：[VSCode 通用C++环境](../vscode_cpp_common)
4. 其他插件的安装会在后续步骤中分别进行

## 安装Mingw-w64

### MSYS2

直接参考 [Get Started with C++ and MinGW-w64 in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw) 中的安装步骤。

**中文参考**：[Visual Studio Code 中的 C++ 和 MinGW-w64 入门 Vscode中文网](https://vscode.github.net.cn/docs/cpp/config-mingw)

### w64devkit

> - [安装 - Mingw-w64](../mingw#w64devkit)

**安装步骤**：

- 下载 `w64devkit` 的二进制包
- 解压到你的目录下，例如 `C:\w64devkit`
- 将 `C:\w64devkit\bin` 添加到你的[`环境变量`]中
- 打开命令行，输入 `gcc --version`，如果能看到版本信息，说明安装成功

[`环境变量`]: ../environment_variable

## 配置XMake

> - [Windows安装指南 - xmake](https://xmake.io/#/zh-cn/guide/installation?id=windows)

这里建议使用安装包安装，避免遇到Powershell的权限问题。

完成xmake的安装后，在VSCode中安装xmake插件：

```shell
code --install-extension xmake-vscode.xmake
```

![](https://raw.githubusercontent.com/xmake-io/xmake-vscode/master/res/problem.gif)
> ▲ xmake 插件使用预览 \
> Reference: [VSCode插件 - xmake](https://xmake.io/#/zh-cn/plugin/more_plugins?id=vscode-%e6%8f%92%e4%bb%b6)

## (Optional) 配置Intellsense

有时候xmake-vscode并不能很好的配置Intellsence，这时候如果仍然希望使用 `cpp-tools` 提供的内联提示，我们需要手动配置其配置文件，参考：[配置Intellsence](https://guide.samuka007.xyz/articles/vscode_cpp_common/#%E9%85%8D%E7%BD%AE-intellsence)
<!-- use absolute route duel to incomplete chinese support -->

## 使用/测试配置

命令行在你的指定目录下，使用xmake创建一个新项目，并使用VS Code打开该项目：

```shell
$ xmake create -l c++ -t console test
# create test ...
#   [+]: xmake.lua
#   [+]: src/main.cpp
#   [+]: .gitignore
# create ok!
$ code test
```

在VS Code下，理论上你应该能看到类似下图的提示：
![](https://xmake.io/assets/img/guide/vscode_status_bar.png)

并且，打开 `src/main.cpp` 文件，应该不会有任何错误提示，有现成的代码模板，可以直接编译运行。按下 `Ctrl` 并将光标移到标识符上，你应该能看到内联提示正常的起了作用。

由于我们使用的是 `MinGW` 的工具链，我们需要点击工具栏中的 `windows`，选择 `mingw`；点击 `tooltrain`，选择 `gcc`，随后点击 `Build` 开始构建。如果一切正常，你会看到以下提示：
```shell
[ 50%]: cache compiling.debug src/main.cpp
[ 75%]: linking.debug test
[100%]: build ok, spent 1.731s
```
然后点击 `default` 旁的小三角，你就可以运行该程序了！

## 配置Clangd
TODO