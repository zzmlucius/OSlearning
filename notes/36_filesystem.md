0.high level overview
1.layer
2.each layer's api
3.code and nice engineer-design

#### High level overview
- Purpose of a file system is to organize and store data.
- addresses several challenges:
    - 1.on-disk data structure
    - 2.crash recovery
    - 3.maintain invariants through different processes
    - 4.maintain in-memmory cache to bridge the speed between RAM and Disk

#### Layers : From Disk to File Descriptor
- Disk :
- mkfs() : ?what it do
    - block0 : boot
    - block1 : superblock{record NBLOCKS, log blocks...}
    - block2 ~ ? : log block
    - ? ~ end: data block
    - bitmap : ?
- API : balloc/bfree ?
---
- Buffer cache : 
    - struct buf, bcache
    - implement LRU with doubly-linked list
- API : bread/bwrite
--- 
- Log : all or none
    - structure : a header block and a sequence of logged blocks
    - transaction :
- API :
    - begin_op ?
    - log_write 
    - end_op ?
    - commit
---
- Inode : two meanings
    - on-disk structure : inode was saved in a contiguous area of a "inode block"
    - in-RAM  structure : struct dinode :
        - type \ nlink \ addrs
- API : ?
---
- Directory
---
- Pathname
---
- Fd : Abstract an uniform and easy API
    - struct file
    - fileread/filewrite/fileclose assign func according to type
    - ftable record all the opened files
    - each proc has a ofile array to record its opened files
- API : sys_write/read/link/unlink... 