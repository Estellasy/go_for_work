# 引言
Docker是什么？
Docker脱胎于Linux Container（LXC）技术。一系列技术cgroups、namespace、unionfs整合，降低容器技术的复杂度。
Docker开源了Docker Engine，定义了一个以容器镜像为标准的应用打包风格，并建立Docker Hub服务进行镜像分发与协作。
云平台成为分布式网络操作系统，容器成为“进程”执行单元，可以动态运行在不同宿主机环境中。
Docker是使用Linux Kernel的Namespace和Cgroups实现的一种容器技术。
什么是Namespace？
什么是Cgroups？
# 容器与开发语言
1. 什么是Docker？
	Docker 容器将一系列软件包装在一个完整的**文件系统**中，这个文件系统包含应用程序运行所需要的一切：**代码、运行时工具、系统工具、系统依赖**，几乎有任何可以安装在服务器上的东西。这些策略保证了容器内应用程序运行环境的稳定性，不会被容器外的系统环境所影响。
2. Docker的特点？
	- 轻量级：统一宿主机上的容器共享系统Kernel，可以迅速启动且占用内存极少。镜像是以分层文件系统构造的，可以共享相同的文件，使得磁盘使用率和镜像下载速度得到提高。
	- 开放：基于开放标准。
	- 安全：隔离应用程序。
3. 容器和虚拟机的比较？
	- 虚拟机：包含用户程序、函数库和整个客户端OS。
		![[Pasted image 20240317143642.png]]
	- 容器：包含用户程序和所有依赖，但是是共享Kernel的，容器在宿主机上互相隔离，在用户态下运行。
		![[Pasted image 20240317143812.png]]
4. Go语言
	- Go和C++：Go不包括异常处理、继承、泛型、断言、虚函数等，但包括slice、并发、管道、垃圾回收、接口等语言特性。
	- Go内嵌了关联数组（hash或dict）
	- Go等开源框架：beego（web框架，同gin）
# 基础技术
## Namespace
Linux Namespace是Kernel的一个功能，可以隔离一系列的系统资源，比如PID、User ID、Network等。Namespace可以在一些资源上将进程隔离起来，包括进程数树、网络接口、挂载点等。
Namespace可以做到UID级别的隔离，以UID为n的用户，虚拟化出一个Namespace，在这个Namespace中，用户具有root权限。PID也可以被虚拟，自己的init进程PID为1，其他进程PID递增，子命名空间的进程映射到父命名空间的进程上。子命名空间和父命名空间之间是隔离的。
Linux一共实现了6种不同类型的namespace。
- Mount：挂载点隔离
- UTS：主机和域名隔离 
- IPC：进程间通信隔离
- PID：进程隔离
- Network：网络隔离
- User：用户和用户组隔离
主要使用3个系统调用。
- clone：创建新进程，判断哪些类型的namespace被创建，子进程也包含在这些namespace中
- unshare：移除namespace
- setns：加入namespace
**UTS Namespace**
UTS Namaspace主要用来隔离nodename和domainname。在UTS Namespace里面，每个Namespace允许有自己的hostname。
> chroot命令
> - chroot 是一个系统调用，用于改变进程的根目录，使得进程只能在指定的根目录下访问文件系统，无法访问其他目录。通常用于创建一个与主系统隔离的环境，比如用于软件开发、系统修复等。
> - chroot 只能隔离文件系统，无法实现对进程的其他资源（比如进程 ID、网络、IPC 等）进行隔离。
> - chroot 提供的隔离相对较弱，因为一旦获得足够的权限，进程仍然可以逃出 chroot 环境。
# Cgroups
# Union File System
# 构造容器
# 构造镜像
# 构造容器进阶
# 容器网络