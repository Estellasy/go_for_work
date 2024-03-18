package main

import (
	"log"
	"os"
	"os/exec"
	"syscall"
)

func main() {
	// 指定被fork出来的新进程内的初始命令，默认使用sh来执行
	cmd := exec.Command("sh")
	cmd.SysProcAttr = &syscall.SysProcAttr{
		Cloneflags: syscall.CLONE_NEWUTS, // 创建 UTS Namespace
	}
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr

	if err := cmd.Run(); err != nil {
		log.Fatal(err)
	}
}
