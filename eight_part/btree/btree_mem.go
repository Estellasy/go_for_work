// Copyright 2014 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//go:build ignore
// +build ignore

// This binary compares memory usage between btree and gollrb.
package main

import (
	"flag"
	"fmt"
	"math/rand"
	"runtime"
	"time"

	"github.com/google/btree"
	"github.com/petar/GoLLRB/llrb"
)

/*
比较btree和gollrb的内存使用情况
*/
var (
	size   = flag.Int("size", 1000000, "size of the tree to build") // 树的大小
	degree = flag.Int("degree", 8, "degree of btree")               // 树的高度
	gollrb = flag.Bool("llrb", true, "use llrb instead of btree")   //是否使用llrb树
)

func main() {
	flag.Parse()
	vals := rand.Perm(*size) // 生成大小为size的随机数组
	var t, v interface{}
	v = vals
	var stats runtime.MemStats // 内存统计
	for i := 0; i < 10; i++ {  // GC10次
		runtime.GC()
	}
	fmt.Println("-------- BEFORE ----------")
	runtime.ReadMemStats(&stats)
	fmt.Printf("%+v\n", stats)
	start := time.Now()
	if *gollrb {
		tr := llrb.New() // 创建llrb树
		for _, v := range vals {
			tr.ReplaceOrInsert(llrb.Int(v))
		}
		t = tr // keep it around
	} else {
		tr := btree.New(*degree)
		for _, v := range vals {
			tr.ReplaceOrInsert(btree.Int(v))
		}
		t = tr // keep it around
	}
	fmt.Printf("%v inserts in %v\n", *size, time.Since(start))
	fmt.Println("-------- AFTER ----------")
	runtime.ReadMemStats(&stats)
	fmt.Printf("%+v\n", stats)
	for i := 0; i < 10; i++ {
		runtime.GC()
	}
	fmt.Println("-------- AFTER GC ----------")
	runtime.ReadMemStats(&stats)
	fmt.Printf("%+v\n", stats)
	if t == v {
		fmt.Println("to make sure vals and tree aren't GC'd")
	}
}
