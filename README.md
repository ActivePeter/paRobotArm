[中文](./README_CN.md)

# pa_RobotArm

## Intro

#### 🎨 robot arm project that can draw what you want

------

![image-20201204221358223](http://tuchuang.hanbaoaaa.xyz/image-20201204221358223.png)

run host on ipad, and draw on itself

![run host on ipad, and draw on itself](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/1624288368467.gif)

![image-20210621225456065](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621225456065.png)



#### The host is written with vue   (also has a old version using QT)

🎄github: [ActivePeter/RobotArmHost: Host of my robotArm Project using vue and mqtt. The old version uses qt (github.com)](https://github.com/ActivePeter/RobotArmHost)

🎁demo: [Vue-ImagePainter (hanbaoaaa.xyz)](https://hanbaoaaa.xyz/apps/RobotArmHost/)

draw path on canvas

![image-20210621225712577](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621225712577.png)

load picture and generate path

![image-20210621225811766](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621225811766.png)

## 💻Language

c/c++ (mcu)   

vue (host) (qt: old version)

## ➗Model Conversion

check the model **describe file** and **code**

[./model_describe.md](./model_describe.md)

[./main/RobotArm/RobotArmApp/RobotArmModel.cpp](./main/RobotArm/RobotArmApp/RobotArmModel.cpp)

## 🛠Developement

1. get **vscode**, install the idf extension in vscode and set up basic **esp32** development environment
2. install the necessary **extensions**, the describe of extensions is in the **Design** part

> Before coding, you should have a **darm robot arm** as that in picture.
>
> Also you should know how to connect **robot arm stepper - stepper driver(a4988) - mcu(esp32)** 
>
> **libHelperTree.json** the gpio needed is describe in config tree file

1. get my source from github, use my **[Submodule Helper](https://github.com/ActivePeter/SubmoduleHelper-vscode)** or **native git commands** to load submodules.

2. run build through vscode command pallete

   ![image-20210621235744814](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621235744814.png)

   

## ✏Design

1. It is mainly written in **c++** and well **modularized**.

   Abstracting the **driver layer** through my **[paMcuLib](https://github.com/ActivePeter/paMcuLib)**, which makes my MCU project can be easily transferred to other platformsAll the logic of the robot arm is put in class **RobotArmApp**

2. uses my vscode extension  [MacroDefineHelper](https://github.com/ActivePeter/MacroDefineHelper-vscode), I can set the platform related things easily(such as gpio)

   First I can set up **describe.txt** where I need platform related config macro.

   For example, here I need gpio config for robot arm. I created the describe.txt file to describe the header file and macros in it what I need.

   ![image-20210621233747067](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621233747067.png)

   Then using my extension, a **config tree** will be automatically generated. And now I can easily set the macros.

   ![image-20210621233312226](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621233312226.png)

   Finally, using my extension, I can generate config header files to the pre-set path

   ![image-20210621234239300](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621234239300.png)

3. Using my another extension [Submodule Helper](https://github.com/ActivePeter/SubmoduleHelper-vscode), I can load my paMcuLib modules as git submodules easily. Only need **a json config** file to describe the repositories and paths. Also I can easily switch **used** to load/remove them.

   ![image-20210621234819944](https://hanbaoaaa.xyz/tuchuang/images/2021/06/21/image-20210621234819944.png)

   

   

## 📄Record

#### 2021/6/20 almost finish. able to draw pictures.

#### 2020/12/28 已经能够跟上位机通信来更新点序列了！

#### 2020/12/6已经可以顺利的画纵向平面的五角星啦！

![image-20201206065550082](http://tuchuang.hanbaoaaa.xyz/image-20201206065550082.png)

