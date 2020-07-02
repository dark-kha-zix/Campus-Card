# 校园卡管理项目设计  

| 学号 | 姓名 |
| :---: | :----: |
| 17307003 | 陈宏辉 |
| 18324061 | 文君逸 |

尊敬的杨老师，尊敬的劳健涛，文永明助教，你们好！下面我们来介绍一下我们的项目架构以及运行方法。本项目的**github**仓库地址为 **https://github.com/dark-kha-zix/Campus-Card** 。

## 项目架构

```
|-- project
    |-- 17307003_陈宏辉_18324061_文君逸_校园卡管理项目设计.pdf
    |-- README.md
    |-- Campus-Card.dev
    |-- Campus-Card.exe
    |-- include 
        |-- UI.h
        |-- project.h
    |-- src
        |-- UI.cpp
        |-- project.cpp
        |-- main.cpp
    |-- images
        |-- 流程图.png
        |-- UML.png
        |-- test_create.png
        |-- test_login.png
        |-- test_remove.png
        |-- test_service.png
    |-- test
        |-- test.md

```

## 运行方法

请你们直接打开根目录下的**Campus-Card.dev**文件，然后点击编译运行，或者直接打开**Campus-Card.exe**运行即可。如果选择管理员模式，系统会要求输入管理员密码。管理员密码已经预先设置为

```
admin
```

在创建学生后，每一位学生的**默认初始密码与其学号相同**。测试数据位于**test**文件夹下的**test.md**中。