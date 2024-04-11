# Golang 八股文汇总
> https://www.youandgentleness.cn/2023/08/28/Go%E8%AF%AD%E8%A8%80%E9%9D%A2%E8%AF%95%E9%A2%98%E7%B2%BE%E8%AE%B2/#Go-%E5%87%BD%E6%95%B0%E5%8F%82%E6%95%B0%E4%BC%A0%E9%80%92%E5%88%B0%E5%BA%95%E6%98%AF%E5%80%BC%E4%BC%A0%E9%80%92%E8%BF%98%E6%98%AF%E5%BC%95%E7%94%A8%E4%BC%A0%E9%80%92%EF%BC%9F
## Go基础
### 1. init和main函数相关特点
init函数（没有输入参数、返回值）的主要作用：
- 初始化不能采用初始化表达式的变量。
- 程序运行前的注册。
- 实现sync.Once功能。
- 其他

比如包的时初始化，数据库连接、日志记录的初始化等。

**init顺序**
1. 同一个package中，可以多个文件定义init方法。
2. 同一个go文件中，可以重复定义init方法。
3. 同一个package中，不同文件的init方法执行顺序按照文件名先后执行。
4. 同一文件的多个init方法，按照代码中编写的顺序执行。
5. 不同package，不相互依赖的话，按照main包中的import顺序调用包中的init函数。
6. 不同package，如果相互依赖，按照最后被依赖的最先被初始化。例如：导入顺序 main –> A –> B –> C，则初始化顺序为 C –> B –> A –> main，一次执行对应的 init 方法。

所有init函数都在同一个goroutine内执行。

所有init函数执行结束后才会执行main.main函数。

### 2. Go数据结构的零值
- 所有整数类型：0
- 浮点类型：0.0
- 布尔类型：false
- 字符串类型：""
- 指针、interface、slice、channel、map、function：nil
Go的零值初始是递归的，即数组、结构体等类型的零值初始化就是对其组成元素逐一进行零值初始化。
> error类型是一个interface{}类型，有一个方法Error，用于返回错误的字符串描述，零值类型为nil。

### 3. byte和rune的区别
byte和rune都是字符类型，且都是别名类型。

byte本质是uint8的别名，标识ASCII码的一个字符。go字符串是[]byte，通常用于处理字节数据、二进制数据和文本文件等。

rune是int32的别名，标识Unicode字符。

### 4. go struct能不能比较
具体情况具体分析，如果struct中含有不能被比较的字段类型，就不能被比较。如果所有字段都能支持比较，就可以比较。

不可以比较的类型：
- slice：slice是引用类型，只能和nil比较
- map：比较两个map只能通过循环实现
- 函数类型

其他类型都能比较

- 结构体之间只能比较它们是否相等，而不能比较它们的大小。
- 所有属性都相等且顺序一致的struct才能比较。

### 5. go初始化变量
```go
var a int = 10
var a = 10
a := 10
```

### 6. go import的三种方式
- 下划线
```go
import _ "github.com/go-sql-driver/mysql"
```
只导入init函数，无法通过包名调用。
- 加.
省略前缀的包名
- 别名

### 7. 与其他语言相比，go语言的好处
- 设计之初都是务实的，每个功能和语法都旨在让程序员的生活更轻松。
- 针对并发优化，在规模上运行良好。
- 单一的标准代码格式，gofmt格式化，可读性高。
- 自动垃圾回收机制与程序同时进行，比python和java更加有效。

### 8. go的缺陷
- 框架：相对于java，框架比较少。标准库较少。
- 错误处理机制：错误处理以来error类型，容易造成错误码的冗余，可读性和代码维护性较差。容易丢失错误发生的范围。
- 依赖管理：没有办法制定特定版本的依赖库。

### 9. go 常量取地址
```go
const i = 1000
var j = 123

func main() {
  fmt.Println(&j, j) 
	fmt.Println(&i, i)  //panic
} // go语言中 常量无法寻址 不能进行取指针操作
```

### 10. 字符串拼接
```go
str := 'abc' + '123'
str := "abc" + "123" // ✅
str ：= '123' + "abc"
fmt.Sprintf("abc%d", 123) // ✅
```

### 11. string和[]byte如何取舍
string不可变。因此比较擅长的场景：
- 需要字符串比较
- 不需要nil字符串

[]byte擅长的场景：
- 字符串修改，尤其是修改颗粒度为1字节
- 函数返回值，用nil标识含义
- 需要切片操作

### 12. 字符串转成byte数据，会发生内存拷贝吗
只要是强转都会发生内存拷贝。但是频繁的内存拷贝对性能不友好。

不发生拷贝的方法：
```go
package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

func main() {
	a := "aaa"
	ssh := (*reflect.StringHeader)(unsafe.Pointer(&a))
	b := *(*[]byte)(unsafe.Pointer(&ssh))
	fmt.Printf("%v", b)
}
```

StringHeader 是字符串在go的底层结构。
```go
type StringHeader struct {
  Data uintptr
  Len  int
}

```
SliceHeader 是切片在go的底层结构。
```go
type SliceHeader struct {
  Data uintptr
  Len  int
  Cap  int
}
```

在底层转换二者，需要将StringHeader的地址强转为SliceHeader，使用unsafe包。
unsafe.Pointer(&a)得到变量a的地址，使用`(*reflect.StringHeader)(unsafe.Pointer(&a))`强转为底层结构，`(*[]byte)(unsafe.Pointer(&ssh))`将底层结构体转为byte切片，再通过指针转为指针指向的实际内容

### 13. 翻转含有中文、数字、英文字母的字符串
**转为rune切片，再进行翻转**
```go
package main

import "fmt"

func main() {
	src := "你好abc哈哈哈"
	dst := reverse([]rune(src))
	fmt.Printf("%v", string(dst))
}

func reverse(s []rune) []rune {
	for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
		s[i], s[j] = s[j], s[i]
	}
	return s
}
```
### 14. json包变量不加tag会怎么样
json包使用的时候，json里的变量不加tag能否正常转为json字段？
- 如果变量首字母小写，则为private，不能转，得不到反射信息。
- 首字母大写
  - 不加tag，可以正常转为json字段，和结构体内原名一致。
  - 加tag，struct转json就是tag字段名

```go
package main

import (
	"encoding/json"
	"fmt"
)

type J struct {
	a string
	b string
	C string
	D string `json:"test"`
}

func main() {
	j := J{
		a: "1",
		b: "2",
		C: "3",
		D: "4",
	}
	fmt.Printf("%+v\n", j) // {a:1 b:2 C:3 D:4}
	jsonInfo, _ := json.Marshal(j)
	fmt.Printf("%+v\n", string(jsonInfo)) // {"C":"3","test":"4"}
}
```
### 15. reflect（反射包）如何获取字段tag？为什么json包不能导出私有变量的tag？

通过反射（reflect包）内的方法获取。

- printTag方法传入的是j的指针。
- reflect.TypeOf(stru).Elem()获取指针指向的值对应的结构体内容。
- NumField获得结构体的字段数。
- 遍历tag，通过t.Field(i).Tag.Get("json")得到tag为json的字段。

### 16. 昨天那个在for循环里append元素的同事，今天还在么？
```go
package main

import "fmt"

func main() {
	s := []int{1, 2, 3, 4, 5}
	for _, v := range s {
		s = append(s, v)
		fmt.Printf("len(s)=%v\n", len(s))
	}
}
```
不会死循环，for range其实是golang的语法糖，在循环开始前会获取切片的长度 len(切片)，然后再执行len(切片)次数的循环。

### 17. Golang语言的自增，自减操作
Golang语言没++i、–i，只有i++、i–。

### 18. Printf()、Sprintf()、Fprintf()函数的区别用法是什么
都是把格式好的字符串输出，只是输出的目标不一样。
- Printf()，是把格式字符串输出到标准输出（一般是屏幕，可以重定向）。Printf() 是和标准输出文件 (stdout) 关联的，Fprintf 则没有这个限制。
- Sprintf()，是把格式字符串输出到指定字符串中，所以参数比printf多一个char*。那就是目标字符串地址。
- Fprintf()，是把格式字符串输出到指定文件设备中，所以参数比 printf 多一个文件指针 FILE*。主要用于文件操作。Fprintf() 是格式化输出到一个stream，通常是到文件。
```go
func Fprintf(w io.Writer, format string, a ...any) (n int, err error) {
	p := newPrinter()
	p.doPrintf(format, a)
	n, err = w.Write(p.buf)
	p.free()
	return
}

// Printf formats according to a format specifier and writes to standard output.
// It returns the number of bytes written and any write error encountered.
func Printf(format string, a ...any) (n int, err error) {
	return Fprintf(os.Stdout, format, a...)
}

// Sprintf formats according to a format specifier and returns the resulting string.
func Sprintf(format string, a ...any) string {
	p := newPrinter()
	p.doPrintf(format, a)
	s := string(p.buf)
	p.free()
	return s
}
```

### 19. Go语言中cap 函数可以作用于哪些内容？
- array 返回数组的元素个数；
- slice 返回 slice 的最⼤容量；
- channel 返回 channel 的容量；

### 20. Golang语言的引用类型有什么?
func、interface、slice、map、channel、*
**struct是值类型不是引用类型**

### 21. 通过指针变量 p 访问其成员变量name，有哪几种方式？
```go
p.name
(*p).name
```

### 22. for select时，如果通道已经关闭会怎么样？如果只有⼀个case呢？
- for循环select时，如果一个case的通道已经关闭，则每次都会执行到这个case。
- 如果select中只有一个case，而这个case被关闭了，会出现死循环。
```go
package main

import (
	"fmt"
	"time"
)

const (
	fmat = "2006-01-02 15:04:05"
)

func main() {
	c := make(chan int)
	go func() {
		time.Sleep(1 * time.Second)
		c <- 10
		close(c)
	}()

	for {
		select {
		case x, ok := <-c:
			fmt.Printf("%v x=%v, ok=%v\n", time.Now().Format(fmat), x, ok)
			time.Sleep(500 * time.Millisecond)
		default:
			fmt.Printf("%v 没有读到消息", time.Now().Format(fmat))
			time.Sleep(500 * time.Millisecond)
		}
	}
}
```
- c通道是一个缓冲为0的通道，main开始时，启动一个协程对c通道写入10，然后关闭通道。
- 在main函数中接收通道c的值，读到了10，但是通道关闭后，一直能读出内容。
- x, ok := <-c 返回的值里第一个x是通道内的值，ok是指通道是否关闭，当通道被关闭后，ok则返回false。
- 当返回的ok为false时，执行c = nil 将通道置为nil，相当于读一个未初始化的通道，则会一直阻塞。至于为什么读一个未初始化的通道会出现阻塞。
- 对未初始化的chan进行读写
  - 永久阻塞，知道被初始化为止

- 对已关闭的chan进行读写
  - 读已经关闭的 chan 能一直读到东西，但是读到的内容根据通道内关闭前是否有元素而不同。
    - 如果 chan 关闭前，buffer 内有元素还未读 , 会正确读到 chan 内的值，且返回的第二个 bool 值（是否读成功）为 true。
    - 如果 chan 关闭前，buffer 内有元素已经被读完，chan 内无值，接下来所有接收的值都会非阻塞直接成功，返回 channel 元素的零值，但是第二个 bool 值一直为 false。
  - 写已经关闭的 chan 会 panic


### 23. Golang的bool类型的赋值
```go
b = true // ✅
b = (1 == 2) // ✅
b = 1 // ❎ int类型不能由bool类型来表示
b = bool(1) ❎ bool()不能转化int类型。int和float可以相互转化
```
### 24. Go关键字fallthrough有什么作用
fallthrough只能用在switch中，且只能在每个case分支的最后一行出现。作用是如果这个case分支执行，将会继续执行下一case分支，而不用判断下一分支的条件是否成立。

### 25. 空结构体占不占内存空间？ 为什么使用空结构体？
空结构体是没有内存大小的结构体，可以使用`unsafe.Sizeof`查看结构体的宽度。

空结构体有一个特殊起点：zerobase变量。

zerobase变量是一个占用8个字节的uintptr全局变量（用于存储指针的整数表示形式），每次定义struct{}类型变量，编译器把zerobase变量的地址给出去，内存地址都是一样的。

### 26. Go 的面向对象特性
**接口**
接口使用interface关键字声明，任何实现了该接口方法的类都可以实例化该接口，接口和实现类之间没有任何依赖。可以实现一个新的类而不依赖任何借口，也可以为已有的类创建一个新接口，而不需要修改代码。

**继承**
使用组合的方式实现继承。

**覆盖**
子类可以重新实现父类的方法。

**多态**
接口可以用任何实现该接口的指针来初始化，但是不支持父类指针指向子类。

### 27. Go语言中,下面哪个关于指针的说法是错误的?
- 指针不能进行算术运算
- 指针可以比较
- 指针可以是nil
- **指针可以指向任何类型**
指针只能指向相同类型的结构体或基本类型。将不同类型的指针赋给一个变量，会导致编译错误。

### 28. Go语言的接口类型是如何实现的？
接口通过类型嵌入embedding的方式实现。每个实现了接口类型的结构体中都有一个隐含成员，指向该接口类型的指针。
类型方法集在编译时确定。

### 29. 关于switch语句，下⾯说法正确的有?
- 条件表达式必须为常量或者整数 ❎ 可以为多个数据
- 单个case中，可以出现多个结果选项 ✅
- 需要⽤break来明确退出⼀个case ❎
- 只有在case中明确添加fallthrough关键字，才会继续执⾏紧跟的下⼀个case ✅

### 30. 下列Add函数定义正确的是？
```go
func Test54(t *testing.T) {
 var a Integer = 1
 var b Integer = 2
 var i interface{} = &a
 sum := i.(*Integer).Add(b)
 fmt.Println(sum)
}

A.
type Integer int
func (a Integer) Add(b Integer) Integer {
 return a + b
}

B.
type Integer int
func (a Integer) Add(b *Integer) Integer {
 return a + *b
}

C.
type Integer int
func (a *Integer) Add(b Integer) Integer {
 return *a + b
}

D.
type Integer int
func (a *Integer) Add(b *Integer) Integer {
 return *a + *b
}
```
答案：AC

go语言interface分为值接收和指针接收。
- 使用值接收者实现接口：结构体类型和结构体指针类型的变量都能存。
- 使用指针接收者：只能存结构体指针类型的变量。

### 31. copy是操作符还是内置函数
内置函数。

### 32. Go 两个接口之间可以存在什么关系？
- 如果两个接口有相同的方法列表，那么他们就是等价的，可以相互赋值。
- 如果接口A的方法列表是接口B的方法列表的子集，那么接口B可以赋值给接口A。接口查询是否成功，要在运行期才能够确定。

### 33. 如何在运行时检查变量类型？
使用switch检查变量类型，`switch x.(type)`。

### 34. Golang的返回值命名
有多个返回值，每个都命名。

### 35. Golang的iota如何使用？
- iota在const关键字出现时被重置为0。
- const声明块中每新增一行iota自增1。
- 第一个常量必须指定一个表达式，后续的常量如果没有表达式，则继承上面的表达式。

### 36. 数组之间如何进行比较？
数组由数组中的值和长度两部分组成，如果两部分长度不同，则是不同类型的，不能进行比较，会出现编译错误。

### 37. for range的注意点和坑
**for range的作用**
- 迭代变量：与python的`for i in range`不同，go的for range迭代变量有两个，第一个是元素在迭代集合中的序号值key（从0开始），第二个值才是元素值value。
- 针对字符串。在Go中对字符串运用for range操作，每次返回的是一个**码点**，int32类型数据，而不是一个字节。Go编译器不会为[]byte进行额外的内存分配，而是直接使用string的底层数据。
- 对map类型内元素的迭代顺序是随机的。要想有序迭代map内的元素，我们需要额外的数据结构支持，比如使用一个切片来有序保存map内元素的key值。
- 迭代变量是重用的。
- for range使用时，k,v值已经赋值好了，不会因为for循环的改变而改变。

**for循环中作用域的问题**
```go
func main() {
	src := []int{1, 2, 3, 4, 5}
	var dst2 []*int
	for _, v := range src {
		dst2 = append(dst2, &v)
		fmt.Println(&v)
	}

	for _, p := range dst2 {
		fmt.Print(*p)
	}
	// 输出
	// 5555
}
```

相当于
```go
var i int
for j := 0; j < len(src); j++ {
    i = src[j]
    dst2 = append(dst2, &i)
}
```

而不是
```go
for j := 0; j < len(src); j++ {
    dst2 = append(dst2, &src[j])
}
```

### 38. Golang的断言
go的所有类型都实现了interface{}接口，一个数据通过func funcName(interface{})的方式传进来的时候，也就意味着这个参数被自动的转为interface{}的类型。

转化过程需要使用断言。在断言之前进行判断。
或者配合switch进行判断。

### 39. 精通Golang项目依赖Go modules
| 命令         | 作用                         |
|--------------|------------------------------|
| go mod init | 生成 go.mod 文件             |
| go mod download | 下载 go.mod 文件中指明的所有依赖 |
| go mod tidy | 整理现有的依赖             |
| go mod graph | 查看现有的依赖结构         |
| go mod edit | 编辑 go.mod 文件           |
| go mod vendor | 导出项目所有的依赖到 vendor 目录 |
| go mod verify | 校验一个模块是否被篡改过   |
| go mod why | 查看为什么需要依赖某模块   |


### 40. Go string的底层实现
```go
Type stringStruct struct{
	str unsafe.Pointer // 字符串的首地址
 	len int // 字符串的长度
}
```

字符串构建过程是根据字符串构建stringStruct，再转化成string。

### 41. Go 语言的 panic 如何恢复

### 42. Go如何避免panic

### 43. 空结构体的使用场景
- 实现方法接受者：在业务场景下，需要将方法组合起来，代表是一个分组的，方便后续拓展和维护。
- 实现集合类型：go标准库没有提供集合的相关实现，在代码中使用map替代。`type Set map[string]struct{}`
- 实现空通道：go channel使用场景中，常用到通知型channel，不需要发送任何数据，只需要协调goroutine的运行，用于流转各类状态或控制并发情况。

### 44. defer的几个坑
defer 能够让我们推迟执行某些函数调用，推迟到当前函数返回前才实际执行。defer与panic和recover结合，形成了Go语言风格的异常与捕获机制。

使用场景：defer 语句经常被用于处理成对的操作，如文件句柄关闭、连接关闭、释放锁。

### 45. 使用过哪些 Golang 的 String 类库

### 46. Go结构体内嵌后的命名冲突

### 47. Go程序中的包是什么？

### 48. Go 实现不重启热部署

### 49. Go中的指针强转

### 50. Go支持什么形式的类型转换？将整数转换为浮点数。

### 51. Golang语言中==的使用

### 52. make函数底层实现

### 53. Go语言实现小根堆

### 54. Go 怎么实现func的自定义参数

### 55. 为什么go的变量申请类型是为了什么？

### 56. Go的闭包语法

### 57. Go语言中int占几个字节

### 58. Golang程序启动过程

### 59. Golang开发新手常犯的50个错误

## Slice
### 60. 
### 61. 
### 62. 
### 63. 
### 64. 
### 65. 
### 66. 
### 67. 
### 68. 
### 69. 
### 70. 
### 71. 
### 72. 
### 73. 
### 74. 
### 75. 
### 76. 
### 77. 
### 78. 
### 79. 
### 80. 
### 81. 
### 82. 
### 83. 
### 84. 
### 85. 
### 86. 
### 87. 
### 88. 
### 89. 
### 90. 
### 91. 
### 92. 
### 93. 
### 94. 
### 95. 
### 96. 
### 97. 
### 98. 
### 99. 
### 100. 

## 调度模型


## 内存管理

## 并发编程
### 1. go语言的并发原语
- goroutine：协程，通过关键字go创建，并发执行函数或者方法。
- channel：goroutine间通信机制，类型安全，通过make创建，使用'<-'发送和接收数据。
- select：多个通信操作中选择一个执行，类似switch语句。
- sync包：一系列同步原语，用于在多个 goroutine 之间进行同步和协调。例如，sync.Mutex 用于实现互斥锁，sync.WaitGroup 用于等待一组 goroutine 完成等待任务。
- atomic包：一系列原子操作，在多个goroutine之间进行原子性的内存访问，可以在不使用互斥锁的情况下实现对共享变量的安全访问。

### 2. 什么是sync.Once
- Once 可以用来执行且仅仅执行一次动作，常常用于单例对象的初始化场景。（程序运行时只存在一个实例的资源）
- Once 常常用来初始化单例资源，或者并发访问只需初始化⼀次的共享资源，或者在测试的时候初始化⼀次测试资源。
- sync.Once 只暴露了⼀个⽅法 Do，可以多次调⽤ Do ⽅法，但是只有第⼀次调⽤ Do 方法时 f 参数才会执行，这⾥的 f 是⼀个无参数无返回值的函数。
```go
type Once struct {
	m    Mutex
	done uint32
}

func (o *Once) Do(f func()) {
	if atomic.LoadUint32(&o.done) == 1 {
		return
	}
	o.m.Lock()
	defer o.m.Unlock()
	if o.done == 0 {
		defer atomic.StoreUint32(&o.done, 1)
		f()
	}
}
```

### 3. Golang除了goroutine还有什么处理并发的方法
goroutine，或channel+goroutine，以及sync提供的并发锁和信号量机制。
```go
done := make(chan struct{}, 1)
go func() {
  done <- struct{}{}
}()
```

### 4. select可以用来干什么？
Go 的通道有两种操作方式，一种是带 range 子句的 for 语句，另一种则是 select 语句，它是专门为了操作通道而存在的。
- for range：使用 for range 遍历通道可以连续地从通道中接收数据，直到通道被关闭。
- select语句：
  - 每个case必须是一个通信，select转为通道设计，每个case表达式都只能包含通道的表达式；
  - 如果有多个case都可以运行，select会选择第一个执行，其他不会执行；
  - 如果多个case都不能运行，若有default则执行default，都则将阻塞；
  - channel表达式都会被求值；
  - select机制用于处理异步IO问题；
  - select机制的最大一条限制就是每个case语句补习是一个IO操作。
  ```go
  	package main
	import (
		"fmt"
		"math/rand"
	)

	func main() {
		intChannels := [5]chan int{
			make(chan int, 1),
			make(chan int, 1),
			make(chan int, 1),
			make(chan int, 1),
			make(chan int, 1),
		}

		// 随机选择一个通道
		index := rand.Intn(5)
		fmt.Printf("The index is: %d\n", index)
		intChannels[index] <- index
		select {
		case <-intChannels[0]:
			fmt.Println("The first candidate case is selected.")
		case <-intChannels[1]:
			fmt.Println("The second candidate case is selected.")
		case elem := <-intChannels[2]:
			fmt.Printf("The third candidate case is selected. The element is %d.", elem)
		default:
			fmt.Println("No candidate case is selected!")
		}
	}
  ```
**select死锁**

如果通道没有数据发送，但是selct中存在接收通道数据的语句，将会发生死锁。

**空select**
```go
func main() {
	select {}
	// fatal error: all goroutines are asleep - deadlock!
}
```
**select和for结合使用**
select只能对其中每一个case表达式各求值一个，如果需要连续或者定时操作通道，需要在for语句中嵌入select。

**使用goto跳出循环**

**使用标签**

**使用time.After实现超时控制**
```go
func main() {
	ch := make(chan int)
	quit := make(chan bool)

	go func() {
		for {
			select {
			case num := <-ch: //如果有数据，下面打印。但是有可能ch一直没数据
				fmt.Println("num = ", num)
			case <-time.After(3 * time.Second): //上面的ch如果一直没数据会阻塞，那么select也会检测其他case条件，检测到后3秒超时
				fmt.Println("超时")
				quit <- true //写入
			}
		}

	}()

	for i := 0; i < 5; i++ {
		ch <- i
		time.Sleep(time.Second)
	}
	<-quit //这里暂时阻塞，直到可读
	fmt.Println("程序结束")
}
```

### 5. WaitGroup的坑
- Add一个负数
计数器值小于0直接panic
- Add在Wait后调用

### 6.
### 7.
### 8.
### 9.
### 10.
### 11.
### 12.
### 13.
### 14.
### 15.
### 16.
### 17.
### 18.
### 19.
### 20.
### 21.
### 22.
### 23.
### 24.
### 25.
### 26.
### 27.
### 28.
### 29.
### 30.
### 31.
### 32.
### 33.
### 34.
### 35.
### 36.
### 37.
### 38.
### 39.
### 40.
