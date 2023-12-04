---
title: "Python 多环境管理总结（转载）"
date: 2023-12-04
authors: 
categories:
    - "Advance"
summary: Python 绕不过去的一道坎就是多环境管理了，为什么 Python 要多环境管理呢？这个得从 Python 的依赖管理说起。
draft: false
---

> 转载自 [知乎 **火眼狻猊**​](https://www.zhihu.com/people/huo-yan-suan-ni-6) ，内容有调整

## 前言
Python 绕不过去的一道坎就是多环境管理了，为什么 Python 要多环境管理呢？

这个得从 Python 的依赖管理说起。

从前有个 Python 解释器，名字叫小派，和其他 Python 解释器相比，他非常富有。

因为他建了一个仓库，专门用来存放他多年以来积攒下来的装备（库），每场战斗（项目）需要什么装备，他都去这个仓库找，既方便又经济。当其他 Python 解释器还要在每场战斗（项目）前买装备（库）时，他已经拿了现成的装备冲锋了。

久而久之，其他 Python 解释器还在疲于打怪刷装备，但是小派却很少，越来越富有，副本刷的那叫一个快啊！

小派给这个仓库取了个名字，叫 site-packages，他也很无私，将他的经验传授给了其他 Python 解释器。其他的 Python 解释器都开始效仿小派，建了 site-packages 仓库，从此大家走上了狂刷副本的巅峰。

然而好景不长，又出现了新的问题。

这是一场艰难的战斗（项目），队长要求小派带上他最擅长的 98K 1.2 版本，配合先锋突击队，远程狙杀。

嘭！嘭！嘭！随着一声声枪响，敌人一个个倒下。正当突击队兴奋之时，一个庞然巨物突然从地底钻出。只见它披着厚重的装甲，提着加特林机枪对着突击队一阵扫射。是装甲巨兽！突击队来不及掩蔽，死伤惨重。

铛！小派一枪命中巨兽的头颅，但是它的装甲坚固无比，子弹竟然被弹开了！

小派又连续击中它的多处要害，均无法对它造成伤害。

“这可怎么办？”小派有些心急了，面对队友的伤亡，他第一次感到了无力。

动图封面
“只能用这个了！”队长拿出一个弹夹给小派，“这是震爆炸弹，是上古遗留的装备，振动波可传到装甲之后，起到隔山打牛的效果。”

“快给我，我来个这个崽子来一发！”小派接过弹夹准备更换。

“诶！？不对啊，这个弹夹怎么装不上，它不是 98K 的吗？”小派疑惑地问。

“是 98K 的，可能上古遗留的装备，只能用在 98K 0.9 版本以下，新的不支持。”队长经验老道，一眼就看出来了。

“那可怎么办？我只有一把 98K 啊，是最新的钛合金版，威力最大。”小派无奈地说。

队长沉思片刻后，说到：“那只能用上大杀器了！它能让你有多个装备仓库，每个装备可以有独立的版本，互不干扰。这是一类装备，但是它们有个共同的目的：多环境管理！”

## 多环境隔离的好处
让我们来看看 Python 的多环境管理吧。

Python 多环境隔离，可以让你的每个项目拥有独立的依赖库，即 site-packages。

- 如果两个项目的依赖相冲突，可起到隔离的作用
- 可以多个 Python 版本共存，如 Python2 和 Python3
- 依赖统一管理，方便项目协作和迁移
- 项目独立打包等

例如 CentOS 7 系统默认自带了 `Python2.7`，但是我们的项目又需要的是 `Python3.6`。默认 python 环境是 `python2.7`，而如果我们要用 `python3.6`，只能用 `python3` 命令，有点蛋疼。这时候如果我们又增加了一个 `Python3.8`，那我们就要用 `python3.6` 命令和 `python3.8` 命令来区分了，蛋不要了!

由于 Python 的依赖库管理是中心化的，而且大版本上的不兼容且长期并行，就出现了这么一个独特的话题。

>你的环境隔离了吗？

## 多环境隔离解决方案
Python 社区对这个问题也是倾注了很多精力，涌现了许多优秀的库，下面我们就来好好比较一下。

### [venv](https://docs.python.org/zh-cn/3.8/library/venv.html)
为什么把 venv 放在第一个，因为它是自 3.3 版本之后添加的官方库，自 3.6 版本之后，成为官方推荐的多环境管理工具。也就是说，你不需要安装任何第三方库就可以实现多环境管理了。

只需要一个命令就可以创建一个虚拟环境。
```shell
python -m venv /path/to/new/virtual/environment
```
这个命令会生成一个目录，里面的内容如下：

```shell
> python -m venv C:\Users\Samuka007\Documents\test
> ls
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d----           2023/12/4    18:37                Include
d----           2023/12/4    18:37                Lib
d----           2023/12/4    18:37                Scripts
-a---           2023/12/4    18:37            234 pyvenv.cfg
```

`pyvenv.cfg` 是我们的配置文件，为什么叫 `pyvenv`，因为这个库的前身就叫 `pyvenv`。 而我们的 `site-packages` 就在 `lib` 目录下。

然后我们需要激活这个环境，运行 `bin` 目录下的 `activate` 脚本。


注意，激活后环境的名字会出现在命令行前面。

这就是你独立的小天地了，所有 `pip` 安装的依赖都会在 `lib` 目录下，所以每个项目都会有自己的一套隔离环境。激活后使用的 `python` 和 `pip` 程序其实是 `bin` 目录下的程序了。

很简单吧，不用安装其他的库就能使用，但是 venv 也有自己的缺点，最大的就是不能自动创建不同版本的 Python 环境。

### [virtualenv](https://virtualenv.pypa.io/en/latest/index.html)
virtualenv 可以说是 venv 的增强版本，不过早在 venv 出现之前，virtualenv 就算是最受欢迎的命令行环境管理工具了。venv 的许多特性也是借鉴的 virtualenv，相比于 venv，其强大之处主要在：

- 更快
- 扩展性更强
- 自动发现并可创建多版本的 Python 环境
- 可通过 pip 更新
- 丰富的编程接口

virtualenv 的原理和使用方式和 venv 类似。

首先需要安装

Python3.5 版本之后推荐使用 pipx 安装
```shell
pipx install virtualenv
```
也可以使用 pip 安装
```shell
python -m pip --user install virtualenv
```
使用更简单

virtualenv
就使用 virtualenv 默认的 Python 解释器创建了一个包含基础库（例如 pip，setuptools，wheel）的虚拟环境。然后，同样使用 activate 脚本激活环境。

指定目录和 Python 版本
```shell
virtualenv venv -p python3
```
激活后可以使用 deactivate 脚本退出环境。

当然，你可以自定义初始化的基础库，激活脚本等，功能强大。

### [pyenv](https://github.com/pyenv/pyenv)
pyenv 主要用来对 Python 解释器进行管理，可以管理系统上的多个版本的 Python 解释器。它的主要原理就是将新的解释器路径放在 PATH 环境变量的前面，这样新的 python 程序就“覆盖”了老的 python 程序，达到了切换解释器的目的。

使用 git 来安装
```shell
git clone https://github.com/pyenv/pyenv.git ~/.pyenv
```
配置环境变量
```shell
echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bash_profile
echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bash_profile
```
安装一个新的 Python 解释器
```shell
pyenv install 2.7.8
```
设置全局默认解释器
```shell
pyenv global 2.7.8
```
更多的命令可以参考文档，可以配合 virtualenv 使用，使用 pyenv-virtualenv 实现自动化。

### [pipenv](https://pipenv.kennethreitz.org/en/latest/)
pipenv 是一款比较新的包管理工具，其借鉴了 javascript 的 npm 和 PHP 的 composer 等理念，通过一个依赖描述文件 Pipfile 来安装和管理依赖，以达到协同开发的目的。如果你熟悉 npm 或者 composer 的话，那 pipenv 正合你胃口。pipenv 其实整合了 pip 和 virtualenv 等库，在其上推出了更便捷的使用方式。

安装 pipenv
```shell
pip install --user pipenv
```
创建虚拟环境
```shell
pipenv --three  # python3
pipenv --two  # python2
```
然后编辑目录下的 Pipfile
```txt
[[source]]
url = "https://pypi.python.org/simple"
verify_ssl = true
name = "pypi"

[packages]
requests = "*"


[dev-packages]
pytest = "*"
```
然后安装所有依赖
```
pipenv install  # 类似与 npm install
```
命令行安装一个依赖并添加到 Pipfile
```
pipenv install <package>  # 类似与 npm install <package>
```
依赖的安装详情也会写入 Pipfile.lock 文件

激活环境
```
pipenv shell
```
而新人接手旧的项目也只要`pipenv install`一下就好了。

是不是很酷！

### [conda](https://conda.io/en/latest/)
最后说说 conda，conda 是一个神奇的库，它是著名的 Python 发行版 Anaconda 附带的包管理工具。它其实不是针对 Python 环境管理，而是 Python, R, Ruby, Lua, Scala, Java, JavaScript, C/ C++, FORTRAN 等等语言的包、依赖和环境管理工具。它的野心很大，甚至还有 UI 界面。

![](https://pic1.zhimg.com/80/v2-f08c73c7cfabe329b4ec502e96a5ee18_720w.webp)

conda 的安装可以在官网下载 Anaconda 或者 Miniconda，Miniconda 是基本的命令行功能，而 Anaconda 有界面，常用 Python 库，相关软件、学习资源等，是科学计算的全能工具包，也可以作为 Python 的环境管理工具。

查看所有环境
```
conda env list
```
创建一个新环境
```
conda create -n python2 python=2
```
激活环境
```
conda activate python2
```
退出环境
```
conda deactivate
```
界面管理环境

![](https://pic2.zhimg.com/80/v2-f0606f0191d561ff23614ec88467ab2d_720w.webp)

conda 除了管理环境，还有其他很多功能。例如和 pip 一样安装依赖的功能。
```
conda install requests
```
列出安装的包

conda list
删除依赖

conda remove requests
conda 其实是在 anaconda 的安装目录下的 envs 子目录下创建环境，而不是项目目录下，也就是说，多个项目其实是可以共用同一个环境的。

不过，用 conda 来安装依赖和 pip 不太一样，conda 可以安装一些非 python 的依赖，但是 python 的依赖没有 pip 全，安装 python 依赖还是可以继续使用 pip。

Anaconda 的界面甚至还有许多科学计算的软件、免费学习教程、文档等等，用好了非常强大。

### 总结
下面我来总结一下

#### venv
优点：Python3.3 以上无需额外安装依赖，使用简单

缺点：功能有限

适用性：只适用于简单创建隔离目录的需求

#### virtualenv
优点：虚拟环境功能完善

缺点：仅仅是命令行工具，不便于工程化

适用性：适用于命令行爱好者

#### pyenv
优点：方便的多版本管理

缺点：其他库很强，显得略有鸡肋

适用性：适用于仅需要多个 Python 版本的管理

#### pipenv
优点：便于项目内部协同工作

缺点：Bug 很多，确实比较年轻，安装的流程有些让人困惑，不像 pip 这么直接好理解

适用性：喜欢 npm 类似体验的人

>（补充by搬运：现在体验很好，bug也少，现在搬运就在用这个）

#### conda
优点：功能很多，还有 UI

缺点：就 Python 包管理而言，太重

适用性：喜欢 Anaconda 科学计算开发包或者 UI 界面管理的人



不知道大家钟爱哪一款？

### 后记
嘭！一声巨响后，装甲巨兽抱头倒下。“这个玩意还不错嘛！”小派嘴角微微上扬，“现在我可有无限仓库了。”