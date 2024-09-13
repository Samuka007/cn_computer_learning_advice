---
title: "Install Visual Studio Code on Windows"
date: 2024-09-13T14:04:22+08:00
authors: 
    - "Samuka007"
categories:
    - "Advance"
tags:
    - "C++"
    - "Modern C++"
    - "Program"
summary: Install Visual Studio Code on Windows
draft: false
---

> [Getting started with VS Code · Visual Studio Code - The Essentials](https://microsoft.github.io/vscode-essentials/en/01-getting-started.html)

## 获取软件包

简要描述，你有若干方式获取VSCode，这里是常用的两种：

- 从官网安装

    > [Download Visual Studio Code - Mac, Linux, Windows](https://code.visualstudio.com/Download)

    点此前往VS Code官网，在下载中心，选择适合你的版本下载安装。这里推荐的是使用 `Installer` 而不是 `User Installer`，避免将VS Code安装在用户目录下。

- 使用Windows包管理器[WinGet]安装

    ```shell
    winget install Microsoft.VisualStudioCode
    ```

## 配置安装

在安装VS Code的过程中，会提示你是否将VS Code添加到环境变量中。这里推荐你选择添加，这样你就可以在命令行中直接使用 `code` 命令打开VS Code。

同时，也会提示你是否将VS Code添加到右键菜单中。这里推荐你选择添加，这样你可以在文件夹中直接右键打开VS Code。
<!-- link to using_vscode -->

[WinGet]: https://learn.microsoft.com/en-us/windows/package-manager/winget/