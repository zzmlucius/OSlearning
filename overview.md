# 00-总览：50 天成为操作系统开源贡献者

> **OS Bootcamp 2026**
>
> **50 天**

---

## Bootcamp 简介

这不是一份为了考试准备的学习计划。

这也不是一份「把 OSTEP、CSAPP 看完」的读书计划。

**这是一份以实践为核心、以开源贡献为目标的操作系统训练营（Bootcamp）。**

整个 Bootcamp 的最终目标不是让你「学过操作系统」，而是让你真正拥有以下能力：

- 能阅读操作系统源码（Source Code Reading）
- 能独立完成操作系统实验（OS Labs）
- 能使用 Linux 进行开发
- 能使用 Git 与 GitHub 进行协作
- 能阅读并理解 Open Source Project
- 能提交并维护 Pull Request（PR）
- 能逐步参与 Google Summer of Code（GSoC）和开源之夏（OSPP）

整个 Bootcamp 将坚持一个核心理念：

> **Learn → Build → Read Code → Debug → Contribute**

而不是：

> **Read Books → Read More Books → Maybe Start Coding**

---

# Bootcamp 设计理念
```
学习理论

↓

完成实验

↓

阅读源码

↓

调试代码

↓

参与开源
```
for the goal of:
- 操作系统比赛
- Google Summer of Code（GSoC）
- 开源之夏（OSPP）
- 科研项目
- 企业内核开发岗位

真正重要的是：

> **解决问题的能力，而不是记住知识点。**

---

# Bootcamp 的最终目标

完成 Bootcamp 后，希望你能够具备以下能力。

---

## Linux 开发能力

能够将 Linux 作为主要开发环境。

包括：

- 熟练使用 Bash
- 熟练使用 Git
- 熟练使用 GCC
- 熟练使用 GDB
- 熟练使用 Makefile
- 熟悉 CMake
- 能使用 `strace`
- 能使用 `objdump`
- 能使用 `nm`
- 能使用 `readelf`

---

## C 语言能力

掌握 Kernel Programming 中最常见的 C 语言特性。

包括：

- Pointer（指针）
- Function Pointer（函数指针）
- Struct（结构体）
- Typedef
- Macro（宏）
- volatile
- static
- extern
- Bit Operation（位运算）

目标不是成为 C 专家，而是能够阅读 Kernel Source Code。

---

## 操作系统基础

系统理解以下模块。

- Process（进程）
- Thread（线程）
- Context Switch（上下文切换）
- System Call（系统调用）
- Virtual Memory（虚拟内存）
- Page Table（页表）
- Interrupt（中断）
- Trap（异常）
- Synchronization（同步）
- Scheduler（调度器）
- File System（文件系统）

不仅知道概念。

更重要的是知道：

> **这些功能在源码中的哪个位置实现。**

---

## Source Code Reading（源码阅读）

能够阅读：

- xv6

并逐步过渡到：

- rCore
- Linux Kernel

培养阅读大型代码工程的能力。

---

## Git & GitHub

能够熟练使用：

- Clone
- Fork
- Branch
- Commit
- Merge
- Rebase
- Pull Request（PR）
- Code Review
- GitHub Issues
- GitHub Discussions
- Continuous Integration（CI）

---

## Open Source

能够：

- 阅读 Issue
- 阅读 PR
- 阅读 Review
- 修复简单 Bug
- 改进文档
- 编写测试
- 提交自己的 Pull Request

最终逐渐成为稳定的开源贡献者。

---

# 学习原则

整个 Bootcamp 将始终遵循以下原则。

---

## 原则一：理论服务于实践

任何理论知识，都必须对应一次实践。

例如：

```
学习 Process

↓

阅读 xv6 中 proc.c

↓

完成 MIT Lab

↓

记录学习笔记

↓

提交 Git Commit
```

不会连续几天只阅读教材。

---

## 原则二：每天必须有输出

每天至少完成以下成果中的一项：

- Git Commit
- 学习笔记
- 实验代码
- 调试记录
- 源码分析
- 技术博客

每天都必须留下可以积累的成果。

---

## 原则三：尽早阅读源码

不是等操作系统全部学完。

而是在学习对应知识点之后：

立即阅读源码。

例如：

学习 Virtual Memory

↓

阅读 xv6 的 `vm.c`

学习 File System

↓

阅读 xv6 的 `file.c`

学习 Scheduler

↓

阅读 xv6 的 `proc.c`

源码阅读将贯穿整个 Bootcamp。

---

## 原则四：尽早进入开源社区

不是第 50 天才开始使用 GitHub。

而是在前几个 Sprint 就开始：

- 阅读 GitHub Issue
- 阅读 Pull Request
- 阅读 Code Review
- 学习 Commit Message
- 学习 Maintainer 如何 Review

逐渐熟悉真实的开源开发流程。

---

# Bootcamp 总路线

```
Linux

↓

C Programming

↓

Computer System

↓

Operating System

↓

MIT 6.S081

↓

xv6 Source Reading

↓

Kernel Debugging

↓

GitHub Workflow

↓

Open Source Contribution

↓

GSoC / 开源之夏
```

整个学习路线围绕一个目标：

> **能够参与真实的开源项目。**

---

# Bootcamp 分阶段规划

## 第一阶段：开发环境与基础能力（Day 1～9）

目标：

建立完整的开发环境，熟悉 Linux 开发。

重点：

- Linux
- Bash
- Git
- C
- GDB
- Makefile
- ELF
- Build System

阶段成果：

- Linux 开发环境
- GitHub 学习仓库
- 第一批学习笔记

---

## 第二阶段：操作系统基础（Day 10～18）

目标：

第一次真正学习操作系统。

重点：

- OSTEP
- xv6
- MIT 6.S081

学习内容：

- Process
- Thread
- System Call

阶段成果：

- 编译 xv6
- 完成第一个 MIT Lab
- 第一份源码阅读笔记

---

## 第三阶段：内存管理（Day 19～30）

目标：

理解 Kernel 中最核心的部分。

重点：

- Address Space
- Virtual Memory
- Page Table
- Trap
- Interrupt

阶段成果：

- 多个 MIT Lab
- Kernel Debug
- xv6 阅读笔记

---

## 第四阶段：Kernel 开发（Day 31～42）

目标：

理解 Kernel 的主要模块。

重点：

- Scheduler
- File System
- Lock
- Buffer Cache

阶段成果：

- 更完整的源码阅读
- Kernel 调试能力
- 技术博客

---

## 第五阶段：进入开源社区（Day 43～50）

目标：

完成第一次真实的开源贡献。

重点：

- GitHub Workflow
- Issue
- Pull Request
- Code Review

阶段成果：

- 第一个真实 PR
- 开源贡献记录
- Bootcamp 作品集

---

# Sprint 总览

| Sprint | 时间 | 主题 |
| -------- | ---- | ---------------------------- |
| Sprint 1 | Day 1～3 | Linux 开发环境 |
| Sprint 2 | Day 4～6 | C 语言与开发工具 |
| Sprint 3 | Day 7～9 | Computer System 基础 |
| Sprint 4 | Day 10～12 | Process 与 xv6 |
| Sprint 5 | Day 13～15 | System Call |
| Sprint 6 | Day 16～18 | Thread 与 Synchronization |
| Sprint 7 | Day 19～21 | Virtual Memory |
| Sprint 8 | Day 22～24 | Page Table |
| Sprint 9 | Day 25～27 | Interrupt 与 Trap |
| Sprint10 | Day 28～30 | Kernel Debugging |
| Sprint11 | Day 31～33 | File System |
| Sprint12 | Day 34～36 | Scheduler |
| Sprint13 | Day 37～39 | Source Code Reading |
| Sprint14 | Day 40～42 | GitHub Workflow |
| Sprint15 | Day 43～45 | 第一次 Open Source Contribution |
| Sprint16 | Day 46～48 | 第一次 Pull Request |
| Sprint17 | Day 49～50 | Bootcamp 总结与未来规划 |

---

# 推荐每日学习安排

建议每天投入约 **8 小时**。

## 上午（2 小时）

理论学习

主要内容：

- OSTEP
- CSAPP
- MIT Notes

---

## 下午（3 小时）

实践

主要内容：

- MIT 6.S081 Lab
- xv6
- 调试实验

---

## 晚上（2 小时）

源码阅读

主要阅读：

- xv6 Source Code

结合当天理论内容分析实现。

---

## 睡前（1 小时）

成果整理

包括：

- Git Commit
- 学习笔记
- Blog
- 阅读 GitHub Issue / PR

每天都留下可以积累的成果。

---

# GitHub 仓库规划

整个 Bootcamp 期间，逐步建立自己的作品集。

建议创建：

```
os-notes/
MIT-6.S081/
xv6-reading/
kernel-debug/
linux-learning/
open-source-practice/
blog/
```

未来这些仓库将成为：

- GSoC
- 开源之夏
- 科研申请
- 实习面试

的重要展示材料。

---

# Bootcamp 完成标准（Checklist）

## Linux

- [ ] 能独立使用 Linux 完成开发
- [ ] 熟练使用 Bash
- [ ] 能使用 GDB 调试程序
- [ ] 能阅读 Makefile
- [ ] 能分析 ELF 文件

---

## Operating System

- [ ] 理解 fork() 的执行过程
- [ ] 理解 exec() 的执行过程
- [ ] 理解 Context Switch
- [ ] 理解 Virtual Memory
- [ ] 理解 Page Table
- [ ] 理解 Interrupt
- [ ] 理解 Trap
- [ ] 理解 Scheduler

---

## xv6

- [ ] 能阅读 xv6 目录结构
- [ ] 能找到 System Call 的实现位置
- [ ] 能修改 Kernel
- [ ] 能使用 GDB 调试 xv6

---

## GitHub

- [ ] 能独立提交 Pull Request
- [ ] 能解决 Merge Conflict
- [ ] 能参与 Code Review
- [ ] 至少完成一次真实开源贡献

---

# Bootcamp 结束之后

Bootcamp 并不是终点。

完成 Bootcamp 后，建议继续：

1. 深入阅读 xv6。
2. 学习 rCore。
3. 阅读 Linux Kernel 部分模块源码。
4. 持续参与 Open Source Project。
5. 为 GSoC 与开源之夏做准备。
6. 参加操作系统相关竞赛。
7. 持续完善自己的技术博客与 GitHub 作品集。

---

# Bootcamp 座右铭

> **阅读操作系统，你获得知识。**

> **实现操作系统，你获得能力。**

> **参与开源项目，你获得机会。**

**Keep Learning. Keep Building. Keep Contributing.**
