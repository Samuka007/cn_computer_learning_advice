---
title: "VSCode 通用C++环境"
date: 2024-09-13T14:04:21+08:00
authors: 
    - "Samuka007"
categories:
    - "Advance"
tags:
    - "VSCode"
    - "C++"
draft: false
---

## 安装C++插件

> [Get Started with C++ and MinGW-w64 in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites)

VSCode插件 搜索 `C/C++ Extension Pack`

![](https://code.visualstudio.com/assets/docs/cpp/cpp/cpp-extension.png)
> 下面第三个，包含了 `C/C++` 的语言支持包， `CMake` 的支持包 ，以及 `C/C++ Themes` 的主题包。

VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack

## work with xmake
以下内容搬运自xmake，做了一丢丢裁剪，以适应本文档的内容。
> shoutout to [xmake](https://xmake.io/#/zh-cn/)

## VSCode 插件

* [xmake-vscode](https://github.com/xmake-io/xmake-vscode)

<img src="https://raw.githubusercontent.com/xmake-io/xmake-vscode/master/res/problem.gif" width="650px" />

[VSCode](https://code.visualstudio.com/)是常用的文本编辑器，xmake提供了插件支持。

### 插件安装

由于VSCode本身只提供了文本编辑的功能，我们需要安装插件以支持配置，编译，调试，语法提示等功能:

* XMake
* C/C++
* CodeLLDB

在完成插件的安装后，重启VSCode可以看到下方的状态栏:

![](/assets/img/guide/vscode_status_bar.png)

可以在状态栏设置平台，架构，编译模式，工具链等选项，随后点击Build开始构建。

<details>
<summary>自定义选项</summary>
如果这些选项不够，可以创建.vscode/settings.json并编写xmake需要的设置，如

```
{
...
  "xmake.additionalConfigArguments": [
    "--my_option=true"
  ],
...
}
```

其他xmake的选项也同样可以在settings.json中完成设置。修改后可通过 `> XMake: Configure` 命令刷新配置。

</details>

### 配置 Intellsence

为了更好的 C++ 语法提示体验，xmake提供了对[Language Server Protocol](https://microsoft.github.io/language-server-protocol/)（简称LSP）的支持。

在 vscode 中，我们可以通过使用 vscode-cpptools 或者 clangd 来提供 intellsence 支持。

另外，为了支持 intellsence，xmake 提供了 compile_commands.json 的生成支持。

#### 生成 compile_commands

##### 自动触发生成

通常在修改 xmake.lua 后点击保存，xmake-vscode 插件就会触发自动生成 compile_commands.json，默认存储在 .vscode 目录下。

这也是推荐方式，通常装完 xmake-vscode 插件，打开带有 xmake.lua 的工程后，只需要编辑 xmake.lua 保存即可触发，不需要任何其他额外操作。

##### 手动触发生成

当然，如果没看到文件被生成，我们也可以在 vscode 中，可以使用 `>XMake: UpdateIntellisense` 命令手动触发生成 .vscode/compile_commands.json。

##### 配置 xmake.lua 自动生成

或者，我们也可以使用这个规则来自动更新生成 compile_commandss.json

```lua
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
target("test")
    set_kind("binary")
    add_files("src/*.c")
```

这会使得在每次 build 后，自动更新此文件。

<details>
<summary>手动执行命令生成</summary>

##### 手动执行命令生成

如果上述方式都无效，我们也可以执行命令来生成。

```console
$ xmake project -k compile_commands .vscode
```
</details>

#### vscode-cpptools

如果我们使用 vscode-cpptools 插件来提供 intellsence 支持，需要先去 vscode 插件市场，搜下 C++，默认第一个插件就是，安装下。

装完后，这个插件提供了 intellsence 和 调试支持。

然后，我们需要配置下 c_cpp_properties.json 文件，关联上我们生成的 `.vscode/compile_commands.json`。

```
{
  "env": {
    "myDefaultIncludePath": ["${workspaceFolder}", "${workspaceFolder}/include"],
    "myCompilerPath": "/usr/local/bin/gcc-7"
  },
  "configurations": [
    {
      "name": "Mac",
      "intelliSenseMode": "clang-x64",
      "includePath": ["${myDefaultIncludePath}", "/another/path"],
      "macFrameworkPath": ["/System/Library/Frameworks"],
      "defines": ["FOO", "BAR=100"],
      "forcedInclude": ["${workspaceFolder}/include/config.h"],
      "compilerPath": "/usr/bin/clang",
      "cStandard": "c11",
      "cppStandard": "c++17",
      "compileCommands": "/path/to/compile_commands.json",
      "browse": {
        "path": ["${workspaceFolder}"],
        "limitSymbolsToIncludedHeaders": true,
        "databaseFilename": ""
      }
    }
  ],
  "version": 4
}
```

也就是上面的 `"compileCommands": "/path/to/compile_commands.json"` 配置项。

关于如果打开这个配置文件，以及更多的配置说明，见：

- https://code.visualstudio.com/docs/cpp/configure-intellisense-crosscompilation
- https://code.visualstudio.com/docs/cpp/c-cpp-properties-schema-reference

当然，理论上可以做到 xmake-vscode 插件自动关联设置这个文件，但是考虑到用户不一定使用 cpptools，有可能还会使用 clangd。

因此，默认自动配置并不是很好，而且作者暂时也没时间精力去改进它。

#### clangd

与此同时，我们可以选择安装支持 LSP 的语法提示插件，如 LLVM 推出的[clangd](https://clangd.llvm.org/)，其功能稳定且提示流畅，
并通过 LSP 标准完成对不同编译工具链的支持。

使用 clangd 时，可能与上述的C/C++插件的提示功能有冲突，可以在 .vscode/settings.json 中添加设置将C/C++的语法提示功能关闭:

```
{
  "C_Cpp.codeAnalysis.runAutomatically": false,
  "C_Cpp.intelliSenseEngine": "Disabled",
  "C_Cpp.formatting": "Disabled",
  "C_Cpp.autoAddFileAssociations": false,
  "C_Cpp.autocompleteAddParentheses": false,
  "C_Cpp.autocomplete": "Disabled",
  "C_Cpp.errorSquiggles": "Disabled",
...
}
```

同时由于 XMake 生成的 compile_commands.json 在 .vscode 目录，还需要设置 clangd 传参使其在正确位置寻找:

```
{
  "clangd.arguments": [
    "--compile-commands-dir=.vscode",
...
  ]
...
}
```

如果配置后，还是没生效，可以尝试重启 vscode 和 clangd 进程，再验证下。
