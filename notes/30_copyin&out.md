### 关于copyin copyout copyinstr

- copyin： 用户空间 → 内核空间
- copyout：内核空间 → 用户空间
- copyinstr：用户字符串 → 内核缓冲区

---

#### copyin/copyout
copyin的典型场景: write(fd, buf, n)
用户buf -> 内核缓冲区

copyout的典型场景: read(fd, buf, n)
内核数据 -> 用户buf

---

#### 用户态的间接调用方式
| 用户调用 | 数据方向 | 内核可能使用 |
|---|---|---|
| `write(fd, buf, n)` | 用户 → 内核 | `copyin` |
| `read(fd, buf, n)` | 内核 → 用户 | `copyout` |
| `open(path, ...)` | 用户字符串 → 内核 | `copyinstr` |
| `exec(path, argv)` | 用户字符串/指针 → 内核 | `copyinstr/copyin` |
| `fstat(fd, &st)` | 内核 → 用户结构体 | `copyout` |
| `wait(&status)` | 内核 → 用户整数 | `copyout` |
| `pipe(fds)` | 内核 → 用户数组 | `copyout` |