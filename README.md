# QT超市管理系统

基于Qt框架开发的超市管理系统，提供完整的商品、员工和销售管理功能。

## 项目简介

本项目是一个使用Qt开发的超市管理系统，实现了商品管理、员工管理、销售开单、账单查询等功能。系统采用JSON文件存储数据，界面美观，操作简便。

## 功能特性

### 核心功能
- ? **登录系统** - 员工登录验证
- ? **商品管理** - 添加、修改、删除商品信息
- ? **员工管理** - 添加、修改、删除员工信息
- ? **销售开单** - 商品销售、数量输入、账单生成
- ? **账单查询** - 查看历史销售记录

### 界面特性
- ? **QSS样式美化** - 自定义界面样式
- ? **图片资源** - 完整的图标和图片支持
- ? **用户友好** - 直观的操作界面

## 项目结构

```
Supermarket-management-system-by-QT/
├── 界面文件
│   ├── login.ui              # 登录界面
│   ├── mainwindow.ui         # 主窗口
│   ├── goods.ui              # 商品管理界面
│   ├── staff.ui              # 员工管理界面
│   ├── new_goods.ui          # 新增商品界面
│   ├── new_staff.ui          # 新增员工界面
│   ├── add_num.ui            # 数量输入界面
│   ├── bill.ui               # 账单界面
│   ├── manager_operation.ui  # 管理员操作界面
│   └── staff_operation.ui    # 员工操作界面
│
├── 头文件 (.h)
│   ├── login.h
│   ├── goods.h
│   ├── staff.h
│   ├── new_goods.h
│   ├── new_staff.h
│   ├── add_num.h
│   ├── bill.h
│   ├── manager_operation.h
│   ├── staff_operation.h
│   └── readwritejson.h       # JSON读写功能
│
├── 源文件 (.cpp)
│   ├── main.cpp
│   ├── login.cpp
│   ├── goods.cpp
│   ├── staff.cpp
│   ├── new_goods.cpp
│   ├── new_staff.cpp
│   ├── add_num.cpp
│   ├── bill.cpp
│   ├── manager_operation.cpp
│   ├── staff_operation.cpp
│   └── readwritejson.cpp
│
├── 资源文件
│   ├── pic/                  # 图片资源
│   ├── qss/                  # QSS样式文件
│   ├── mystyle_copy.qss      # 自定义样式
│   └── json.qrc              # Qt资源文件
│
└── Supermarket_management_system.pro  # Qt项目文件
```

## 技术栈

- **开发框架**: Qt 5.x
- **编程语言**: C++
- **数据存储**: JSON文件
- **界面设计**: Qt Designer (UI文件)
- **样式美化**: QSS (Qt Style Sheets)

## 开发环境搭建

### 环境要求
- Qt 5.x 或更高版本
- MinGW 或 MSVC 编译器
- Qt Creator IDE (推荐)

### 编译步骤

1. 使用Qt Creator打开 `Supermarket_management_system.pro` 项目文件
2. 选择合适的构建套件 (Kit)
3. 点击"构建"按钮编译项目
4. 运行生成的可执行文件

### 命令行编译 (可选)

```bash
# 生成Makefile
qmake Supermarket_management_system.pro

# 编译项目
make

# 或者 (Windows MinGW)
mingw32-make
```

## 使用说明

### 1. 登录系统
- 启动程序后进入登录界面
- 输入员工账号和密码
- 管理员和员工有不同的操作权限

### 2. 管理员功能
- 商品管理：添加、修改、删除商品
- 员工管理：添加、修改、删除员工账号
- 查看销售统计

### 3. 员工功能
- 商品销售：选择商品、输入数量、生成账单
- 查看个人销售记录

## 数据格式

系统使用JSON文件存储数据，主要包括：
- 商品信息 (商品ID、名称、价格、库存等)
- 员工信息 (员工ID、姓名、账号、密码等)
- 销售记录 (流水号、商品、数量、金额、时间等)

## 项目特色

1. **模块化设计** - 每个功能独立成模块，便于维护
2. **数据持久化** - 使用JSON文件存储，无需数据库
3. **权限管理** - 管理员和员工不同的操作权限
4. **界面美观** - 使用QSS美化界面

## 许可证

本项目仅供学习交流使用。
