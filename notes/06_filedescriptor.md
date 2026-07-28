## 文件描述符

| 对象 | 职责 |
|------|------|
| **fd** | 一个整数，下标（如 `3`） |
| **FD Table（文件描述符表）** | 完成 `fd → Open File Description` 的映射 |
| **Open File Description（打开文件对象）** | 保存打开状态（如 `offset`、`flags` 等），并指向 `inode` |
| **inode（索引节点）** | 表示实际文件的数据和元信息 |

- fd table是用户态的，每个进程都有一份，open file description才是内核态的。
- fork()子进程会复制父进程的fd table，并继承已打开的文件。
