---
title: "对git的简单用法的介绍 "
date: 2023-09-27T19:36:16+08:00
authors: 
    - "CC"
categories:
    - "guide"
summary: git是一个分布式的版本控制系统，提供了一个成熟的代码版本控制方案，被开发者们广泛地使用着。
draft: false
---
## 简要介绍 
参考https://git-scm.com/book/zh/v2/ 
git是一个分布式的版本控制系统，提供了一个成熟的代码版本控制方案，被开发者们广泛地使用着。 
在设计上，git管理的文件有三个状态：已提交、已暂存、已更改，分别对应文件的三个概念上的位置：分支中，暂存区，工作区。工作区是直接写代码的地方，在一定的工作后可以将代码中暂存到暂存区，这是从工作区到版本库的一个过渡区域，注意此处仅存储更改的快照，实现功能后，可以提交到分支中。 
在实现上，git包含四种对象：blod，存储文件内容、tree，表示目录结构，包含指向blod和其他tree的指针、conmit，记录历史状态，一个指向tree的指针及相对应的元数据、tag，对特应的commit打标签。每次不同的人提交到分支时，都会生成一个commit对象，多个commit及tree构成有向无环图。每个git对象都用一个哈希值作为唯一标识. 
## 安装 
使用winget install Git.Git或sudo apt install git或sudo pacman -S git或其他的包管理器安装即可。如果使用安装包，请注意添加系统变量。 
在开始使用前，请先指定全局的username,email和 core editor。 
```shell 
git config --global user.name "name"  
git config --global user.email youremail@email 
git config --global core.editor vim 
``` 
## 基本指令 
```shell 
git init  // 初始化本地git仓库，目录下出现./git/ 
git status  // 检查当前git状态，使用-s更加简短 
git add  // 添加文件的到暂存区，可以使用通配符＊ 
git rm  // 删除文件（不再追踪文件） 
git commit [flag]  // 提交修改，通常使用 -m “string” 来提交带说明的commit  
					  -a 来追踪已经add过的文件 
					  --amend 追加上一次提交的文件修改 
``` 
## 远程仓库 
```shell 
git clone [url] 
git remote add [name] [url] 
git fetch [name] // 同步远程仓库，不自动自动合并更改 
git pull [name]  // 同步远程仓库，合并更改 
git remote remove [name] // 删除远程仓库 
git remote rename [name] [newname]  // 重命名仓库别名 
``` 
## 分支控制 
```shell 
git branch // 检查当前分支状态 
git checkout  // 切换分支，使用-b可以创建新分支 
git merge  // 本地合并分支，有合并记录 
git rebase  // 无记录合并，具体查看参考资料 
``` 
## 为指定网站使用代理 
全局 git config --global https.proxy 'httpsproxy' 
指定网站 git config --global http.https://github.com.proxy socks5proxy 
https为格式，有ssh，http等，httpsproxy请填入代理服务器地址（可以socks5） 
如果使用clashforwindow则可填入127.0.0.1:7890. 
## Github使用 
### 1. ssh连接 
安装openssh包，使用 
```shell 
ssh-keygen -t rsa 
再指定ssh文件路径，如C:\Users\YourName.ssh\id_rsa 
``` 
将文件中的公钥拷贝到github的个人设置的密钥，选择ssh格式添加即可。 
### 2. GithubCli 
参考https://cli.github.com/manual/ 
使用winget或apt等安装gh，即githubcli后 
~~~shell 
gh auth login 
~~~ 
按提示选择ssh或https登录即可。 
## 想法 
git提供了一个成熟的版本控制系统，在代码整洁之道中，作者鼓励程序员对一切需要存储更改的文本数据使用版本控制。它为我们提供了更强大的历史记录。 