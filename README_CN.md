# pa_RobotArm

## 介绍

#### 🎨 一个可以绘制你想绘制的东西的机械臂项目

------

![image-20201204221358223](http://tuchuang.hanbaoaaa.xyz/image-20201204221358223.png)

再ipad上运行上位机并且在它上面画画

![run host on ipad, and draw on itself](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/1624288368467.gif)

画猫猫

![image-20210621225456065](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621225456065.png)



#### 上位机是用vue写的  (也有旧版本使用的QT+串口协议）

🎄github: [ActivePeter/RobotArmHost: Host of my robotArm Project using vue and mqtt. The old version uses qt (github.com)](https://github.com/ActivePeter/RobotArmHost)

🎁demo: [Vue-ImagePainter (hanbaoaaa.xyz)](https://hanbaoaaa.xyz/apps/RobotArmHost/)

在canvas 上绘制轨迹

![image-20210621225712577](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621225712577.png)

加载图片并生成路径

![image-20210621225811766](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621225811766.png)

## 💻语言

c/c++ (mcu)   

vue (上位机) (qt: 旧版)

## ➗模型换算

查看**describe 文件** 和**代码**

[./model_describe.md](./model_describe.md)

[./main/RobotArm/RobotArmApp/RobotArmModel.cpp](./main/RobotArm/RobotArmApp/RobotArmModel.cpp)

## 🛠开发

1. 获取 **vscode**, 在vscode里安装idf插件 并设置好基础的**esp32**开发环境
2. 安装必要的vscode插件, 关于插件的描述在**设计**部分

> 在开始写代码之前, 你应该获得一个跟图里一样的dart机械臂
>
> 当然你也应该知道如何链接 **机械臂步进电机 - 步进电机驱动(a4988) - mcu(esp32)** 
>
> **libHelperTree.json** 关于gpio的描述可以参考这个文件，当然你也可以自行修改

1. 从github获取我的源码, 使用我的 **[Submodule Helper](https://github.com/ActivePeter/SubmoduleHelper-vscode)** 或**原生 git 指令**来加载子模块.

2. 在vscode命令面板执行编译和下载

   ![image-20210621235744814](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621235744814.png)

   

## ✏设计

1. 主要使用c++编写，并且做了比较完备的模块化处理

   通过我的单片机通用库 **[paMcuLib](https://github.com/ActivePeter/paMcuLib)**，对驱动层进行了统一的抽象，这使得我的单片机项目可以轻易的被转移到其他平台上。

   所有跟机械臂相关的逻辑都放在 **RobotArmApp** 类里。通过创建对象来进行必要函数的调用

2. 使用我的vscode插件 [MacroDefineHelper](https://github.com/ActivePeter/MacroDefineHelper-vscode), 我可以**轻易的修改平台相关的宏定义参数**并且生成对应头文件

   首先我可以在我需要特殊宏定义设置的模块文件夹内创建 **describe.txt** 

   例如, 这里我需要给我的机械臂设置必要的gpio宏，那么我就像下图一样在文件里写入对应的描述，需要的头文件也可以自定义生成名称

   ![image-20210621233747067](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621233747067.png)

   然后使用我的插件，自动生成一个配置树, 然后我可以轻易的修改宏对应的值

   ![image-20210621233312226](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621233312226.png)

   最终，使用我的插件，自动根据配置树生成对应的配置头文件

   ![image-20210621234239300](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621234239300.png)

3. 使用我的另一个插件 [Submodule Helper](https://github.com/ActivePeter/SubmoduleHelper-vscode), 我可以轻松的加载和管理我的**paMcuLib 通用库组件**. 只需要一个 **json 配置** 文件来描述仓库和对应的路径。我也可以通过修改**used**轻易的切换**是否使用这些子模块**

   ![image-20210621234819944](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621234819944.png)

   

   

## 📄记录

#### 2021/6/20 基本完成，可以绘制图片和canvas轨迹

#### 2020/12/28 已经能够跟上位机通信来更新点序列了！

#### 2020/12/6已经可以顺利的画纵向平面的五角星啦！

![image-20201206065550082](http://tuchuang.hanbaoaaa.xyz/image-20201206065550082.png)

