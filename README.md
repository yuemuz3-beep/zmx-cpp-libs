# zmx-cpp-libs

作者：张明栩

一个用于 ACM / 算法竞赛的可复用 C++ 库集合。

## 当前包含

### bigint

高精度整数运算库，支持高精度整数的加、减、乘、除以及取模等基本运算。

详细说明：

- [bigint](libs/bigint/README.md)

## 项目结构

<!-- TREE START -->

```text
zmx-cpp-libs/
├── .gitignore
├── CMakeLists.txt
├── README.md
├── examples
│   └── bigint
│       └── bigint_demo.cpp
├── libs
│   ├── bigint
│   │   ├── CMakeLists.txt
│   │   ├── README.md
│   │   ├── bigint.cpp
│   │   └── bigint.h
│   └── decimal
│       ├──  README.md
│       ├── CMakeLists.txt
│       ├── decimal.cpp
│       └── decimal.h
├── scripts
│   └── update-tree.py
└── tests
    └── bigint
        ├── BigInt_test.cpp
        ├── algorithm_test.cpp
        └── normalize_test.cpp
```

<!-- TREE END -->
## TODO
- [ ] 增加更多竞赛常用库
- [ ] 完善自动化测试
- [ ] 完善构建与使用方式
