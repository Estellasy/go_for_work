```
├── batch.go
├── benchmark
│   └── benckmark.go
├── db.go
├── errors.go
├── examples
│   ├── basic
│   │   └── main.go
│   ├── batch
│   │   └── main.go
│   ├── iterate
│   │   └── main.go
│   ├── merge
│   │   └── main.go
│   ├── ttl
│   │   └── main.go
│   └── watch
│       └── main.go
├── go.mod
├── go.sum
├── index
│   ├── btree.go
│   ├── btree_test.go
│   └── index.go
├── merge.go
├── options.go
├── record.go
├── utils
│   ├── file.go
│   ├── hash.go
│   ├── hash.s
│   └── rand_kv.go
├── wal
│   ├── options.go
│   ├── segment.go
│   └── wal.go
└── watch.go
```
# 内存和磁盘设计
## 磁盘设计
在 Write-Ahead Log（WAL）中，通常将数据存储在段（segment）文件中。这些段文件由一个或多个块（block）组成，而每个块都包含一个或多个数据块（chunk）。

1. **Segment（段）**：
   - 段是 WAL 中数据的逻辑单位，通常表示为一个单独的文件。
   - 每个段文件是以追加方式写入的，意味着一旦数据被写入到段中，它就不会被修改或删除。
   - 段文件可以包含一个或多个块，取决于写入的数据量和段的大小限制。

2. **Block（块）**：
   - 块是段文件中的物理单位，用于组织数据的存储。
   - 每个块的大小通常是固定的，以便更有效地管理和存储数据。
   - 在 WAL 中，块的大小通常是 32KB。块可以看作是段文件中的子集，它将数据分成更小的单元以便于管理。

3. **Chunk（数据块）**：
   - 数据块是块中的逻辑单位，用于存储实际的数据。
   - 每个数据块包含一个或多个数据项，它们通常是记录、事务或其他类型的数据。
   - 数据块通常具有自己的头部信息，用于标识数据类型、长度等元数据。

关系：
- 一个段（segment）文件可以由一个或多个块（block）组成，每个块具有固定的大小，例如 32KB。
- 每个块（block）内部存储着一个或多个数据块（chunk），这些数据块是实际存储数据的逻辑单位。
- 因此，数据从应用程序写入到数据块（chunk）中，然后数据块被组织成块（block），最终块被追加到段（segment）文件中。
  
在 Write-Ahead Log（WAL）中，通常将数据存储在段（segment）文件中。这些段文件由一个或多个块（block）组成，而每个块都包含一个或多个数据块（chunk）。

1. **Segment（段）**：
    
    - 段是 WAL 中数据的逻辑单位，通常表示为一个单独的文件。
    - 每个段文件是以追加方式写入的，意味着一旦数据被写入到段中，它就不会被修改或删除。
    - 段文件可以包含一个或多个块，取决于写入的数据量和段的大小限制。
2. **Block（块）**：
    
    - 块是段文件中的物理单位，用于组织数据的存储。
    - 每个块的大小通常是固定的，以便更有效地管理和存储数据。
    - 在 WAL 中，块的大小通常是 32KB。块可以看作是段文件中的子集，它将数据分成更小的单元以便于管理。
3. **Chunk（数据块）**：
    
    - 数据块是块中的逻辑单位，用于存储实际的数据。
    - 每个数据块包含一个或多个数据项，它们通常是记录、事务或其他类型的数据。
    - 数据块通常具有自己的头部信息，用于标识数据类型、长度等元数据。

关系：

- 一个段（segment）文件可以由一个或多个块（block）组成，每个块具有固定的大小，例如 32KB。
- 每个块（block）内部存储着一个或多个数据块（chunk），这些数据块是实际存储数据的逻辑单位。
- 因此，数据从应用程序写入到数据块（chunk）中，然后数据块被组织成块（block），最终块被追加到段（segment）文件中。  
在 Write-Ahead Log（WAL）中，通常将数据存储在段（segment）文件中。这些段文件由一个或多个块（block）组成，而每个块都包含一个或多个数据块（chunk）。

1. **Segment（段）**：
    
    - 段是 WAL 中数据的逻辑单位，通常表示为一个单独的文件。
    - 每个段文件是以追加方式写入的，意味着一旦数据被写入到段中，它就不会被修改或删除。
    - 段文件可以包含一个或多个块，取决于写入的数据量和段的大小限制。
2. **Block（块）**：
    
    - 块是段文件中的物理单位，用于组织数据的存储。
    - 每个块的大小通常是固定的，以便更有效地管理和存储数据。
    - 在 WAL 中，块的大小通常是 32KB。块可以看作是段文件中的子集，它将数据分成更小的单元以便于管理。
3. **Chunk（数据块）**：
    
    - 数据块是块中的逻辑单位，用于存储实际的数据。
    - 每个数据块包含一个或多个数据项，它们通常是记录、事务或其他类型的数据。
    - 数据块通常具有自己的头部信息，用于标识数据类型、长度等元数据。

关系：

- 一个段（segment）文件可以由一个或多个块（block）组成，每个块具有固定的大小，例如 32KB。
- 每个块（block）内部存储着一个或多个数据块（chunk），这些数据块是实际存储数据的逻辑单位。
- 因此，数据从应用程序写入到数据块（chunk）中，然后数据块被组织成块（block），最终块被追加到段（segment）文件中。

写入操作

在这段代码中，我们只检查块是否已满，而没有检查段是否已满的原因可能是因为写入数据时，通常是逐块逐块地写入，而不是一次性地写入整个段。

考虑到 Write Ahead Log (WAL) 的特性，写入是以块为单位进行的，每个块的大小通常是固定的。在实际场景中，如果需要写入的数据超过了一个块的大小，我们需要将其分成多个块进行写入。

而判断块是否已满则是为了在写入数据时，及时进行块的切换，以避免数据的丢失。如果当前块已满，我们需要将数据写入到下一个块中。因此，在这段代码中，我们只需要判断当前块是否已满，而不需要判断整个段是否已满。

当然，在实际的应用场景中，可能还会对段的大小进行控制，以确保 WAL 文件不会无限增长。在这种情况下，可以在写入数据时，结合块的大小和段的大小进行判断，以避免段文件无限增长造成的问题。

在上面提到的 `write` 方法中，确实存在这样的逻辑：

1. 首先，将数据写入到缓冲区中。在 `write` 方法中，调用了 `writeToBuffer` 方法，该方法将数据写入到缓冲区 `chunkBuffer` 中。
    
2. 在缓冲区中进行块处理。在 `writeToBuffer` 方法中，根据当前块的大小和数据的大小，决定是否在当前块中写入数据，或者将数据分成多个块进行写入。这个过程主要是逻辑上的处理，确保数据被正确地写入到块中。
    
3. 最后，将缓冲区中的内容写入到段文件中。在 `write` 方法中，调用了 `writeChunkBuffer` 方法，该方法将缓冲区中的数据直接写入到段文件的底层文件中。
    

在这个过程中，块的概念主要是逻辑上的存在，用于将数据进行分块处理，并决定数据在缓冲区中的存储方式。实际上，缓冲区中的数据被写入到段文件中后，会按照文件系统的逻辑划分为文件系统中的块。

`readInternal` 方法用于从段文件中读取数据块，并返回读取的数据、下一个数据块的位置信息以及可能出现的错误。下面是对该方法的总结：

1. 方法签名：`func (seg *segment) readInternal(blockNumber uint32, chunkOffset int64) ([]byte, *ChunkPosition, error)`
    
2. 参数：
    
    - `blockNumber`：要读取的数据块的编号。
    - `chunkOffset`：数据块内的偏移量。
3. 返回值：
    
    - `[]byte`：读取的数据块内容。
    - `*ChunkPosition`：下一个数据块的位置信息。
    - `error`：可能出现的错误，如文件已关闭、IO 错误等。
4. 实现逻辑：
    
    - 首先检查段文件是否已关闭，如果已关闭则返回错误。
    - 创建变量保存结果、块数据和头部信息，并获取段文件的大小。
    - 循环读取数据块，直到达到文件末尾。
    - 在循环中，尝试从缓存中读取数据块，如果缓存命中则直接使用缓存中的数据块，否则从段文件中读取数据块。
    - 根据数据块的类型更新下一个数据块的位置信息：
	    - 如果数据块是完整的或者是最后一个数据块，更新下一个数据块的块编号和偏移量。
	    - 如果是最后一个数据块，并且当前数据块的填充区已经被数据占满，说明下一个数据块应该在下一个块中，更新块编号为当前块编号加一，偏移量为零。
		- 如果数据块类型是中间类型，则继续读取下一个数据块。
	    - 读取数据块后，校验头部信息的校验和，并根据数据块类型更新下一个数据块的位置信息。
	    - 将读取的数据追加到结果中，并返回结果、下一个数据块的位置信息以及可能的错误。
1. 注意事项：
    
    - 方法内部使用了同步机制来确保多个 goroutine 安全地访问段文件和缓存。
    - 通过缓存机制提高了读取性能，避免了频繁地从文件中读取数据块。
    - 通过校验和检查确保读取的数据块的完整性。
## 内存设计
Index索引，需要一种支持高效插入、读取、删除数据的结构，如果需要数据高效遍历，需要选择**天然有序**的数据结构。
选择B树

重建索引？

# 批处理相关
**数据结构**
```go
type Batch struct {
	db *DB // 当前数据库实例指针
	pendingWrites []*LogRecord // save the data to be written 写入数据库日志记录
	pendingWritesMap map[uint64][]int // map record hash key to index, fast lookup to pendingWrites 快速查找 存储key
	options BatchOptions // 批处理选项（同步、只读）
	mu sync.RWMutex
	committed bool // whether the batch has been committed
	rollbacked bool // whether the batch has been rollbacked
	batchId *snowflake.Node // 生成批处理唯一标识符
	buffers []*bytebufferpool.ByteBuffer // 字节缓冲池
}
```
Batch提供了
- Put
- PutWithTTL
等接口，都是先写pendingWrites，先在pendingWrites中查找，再查找Index。对于Delete操作，只查找pendingWrites，如果存在，则当即撤销记录，如果不存在，则添加一条记录到pendingWrites。等到commit一起删除。
如果expired，则删除index的对应记录。
在提交（Commit）操作中，对于记录（record）的类型（Type）不同，处理方式也会不同：

1. 如果记录的类型为删除（LogRecordDeleted），则会将其写入 WAL 文件中。即使记录已被删除，也需要将其写入 WAL 文件，以确保 WAL 文件中的操作与实际数据一致性。
    
2. 如果记录的类型为其他类型（例如新增、更新等），同样会将其写入 WAL 文件中。这样可以保证 WAL 文件记录了所有数据库的操作，以便在需要时进行恢复和重放。
    

总的来说，无论记录的类型是什么，都会将其写入 WAL 文件中，以确保操作的原子性和持久性。

# Watch
Watcher（观察者）：Watcher 是一个用于临时存储数据库修改事件（Event）信息的结构。它提供了方法来存储和获取事件，以及将事件发送给数据库的观察者。
```go
type Watcher struct {
	queue eventQueue
	mu    sync.RWMutex
}
```

Event（事件）：Event 是数据库被修改时产生的事件。它包含了键值对的变化信息，以及相应的操作类型（Put 或 Delete）和批次 ID（BatchID）等信息。
```go
type Event struct {
	Action  WatchActionType
	Key     []byte
	Value   []byte
	BatchId uint64
}
```

eventQueue（事件队列）：eventQueue 是用于存储 Event 对象的队列结构。它使用循环数组实现，并提供了方法来向队列中添加事件、从队列中取出事件等操作。
```go
// eventQueue 循环事件队列
type eventQueue struct {
	Events   []*Event
	Capacity uint64
	Front    uint64 // read point
	Back     uint64 // write point
}
```

**为什么需要 watch 操作？**

观察者模式（Watch 操作）用于实现数据库的事件监听和通知机制。当数据库发生变化时（例如插入、更新、删除操作），将产生相应的事件，并由观察者（Watcher）来监听和处理这些事件。Watch 操作的主要作用是：

**实现数据库的异步事件通知：** 当数据库发生变化时，可以通过观察者模式异步通知相关的监听者，而不需要监听者轮询数据库的状态。

**提供实时性的数据更新：** 观察者可以实时获取数据库的变化情况，从而及时地对数据进行处理和响应。

**解耦数据库操作和业务逻辑：** 观察者模式将数据库操作和业务逻辑解耦，使得数据库操作和事件处理逻辑分离，提高了代码的可维护性和扩展性。

# Merge
  
Bitcask 是一种键值存储引擎，它将数据以日志的形式追加到日志文件中，并维护一个内存中的索引来加速读取操作。虽然 Bitcask 的追加写入操作非常高效，但是**由于不断追加数据，会导致日志文件不断增长**，可能会占用大量磁盘空间。

Merge 操作的主要目的是在保持数据持久性的同时，对磁盘上的数据**进行整理和压缩**，以减少磁盘空间的占用。具体来说，Merge 操作通常会做以下几件事情：

1. **合并数据文件**：将多个日志文件合并成一个更大的文件，以减少文件数量，提高读取效率。
2. **压缩数据**：将相同键的多个版本合并成一个版本，减少重复数据，节省磁盘空间。
3. **删除过期数据**：删除过期的数据，以释放磁盘空间。
4. **重建索引**：根据合并后的数据文件重新构建索引，以提高读取效率。

**Merge操作的流程**
1. **获取当前活跃的段文件 ID（prevActiveSegId）：** 在开始合并操作之前，首先获取当前数据库中活跃的段文件的 ID。
    
2. **切换写前日志（WAL）并创建新的活跃段文件：** 调用 `OpenNewActiveSegment()` 方法切换写前日志，并创建一个新的活跃段文件。这样，所有旧的段文件将会被合并到新的活跃段文件中。
    
3. **解锁数据库的互斥锁：** 在切换写前日志并创建新的活跃段文件后，解锁数据库的互斥锁。这是因为合并操作只会读取旧的段文件，而不会影响到当前的写入操作。
    
4. **打开新的合并数据库实例（mergeDB）：** 调用 `openMergeDB()` 方法打开一个新的数据库实例，用于将合并后的数据写入新的数据文件中。如果合并目录已经存在，则会先删除旧的合并目录。
    
5. **遍历旧的数据文件并写入新的数据文件：** 遍历所有旧的数据文件，并将其中有效的数据写入到新的数据文件中。对于每条记录，会检查其在索引中的位置，并确保只处理索引中最新的记录。
    
6. **标记合并操作完成：** 在重写所有数据后，创建一个文件以指示合并操作已完成。这样，在数据库重新启动时，可以通过检查此文件是否存在来确定合并操作是否已完成。如果文件存在，则表示合并操作已完成，否则将删除合并目录并重新执行合并操作。
    
7. **关闭合并数据库实例：** 在合并操作完成后，关闭合并数据库实例以释放资源。
    
8. **重新打开原始数据库文件并重建索引（可选）：** 如果指定了 `reopenAfterDone` 参数为 `true`，则会重新打开原始数据库文件，并在合并操作完成后重新构建索引。


# 数据库
**DB数据结构定义**
```go
type DB struct {
	dataFiles        *wal.WAL // data files are a sets of segment files in WAL.
	hintFile         *wal.WAL // hint file is used to store the key and the position for fast startup.
	index            index.Indexer
	options          Options
	fileLock         *flock.Flock // 文件锁
	mu               sync.RWMutex
	closed           bool
	mergeRunning     uint32    // indicate if the database is merging
	batchPool        sync.Pool // 批处理对象池
	recordPool       sync.Pool // 记录池
	encodeHeader     []byte
	watchCh          chan *Event // user consume channel for watch events
	watcher          *Watcher
	expiredCursorKey []byte     // the location to which DeleteExpiredKeys executes.
	cronScheduler    *cron.Cron // cron scheduler for auto merge task 合并定时器
}
```

**fileFlock**
```go
// create file lock, prevent multiple processes from using the same database directory
fileLock := flock.New(filepath.Join(options.DirPath, fileLockName))
hold, err := fileLock.TryLock()
if err != nil {
	return nil, err
}
if !hold {
	return nil, ErrDatabaseIsUsing
}
```
`fileLock` 的作用是确保同一时间**只有一个进程可以访问数据库目录**。这是因为在文件系统中，同一时间只能有一个进程对同一个文件进行写操作，而对数据库文件的写操作需要确保原子性，以避免数据损坏或不一致性。因此，使用文件锁可以有效地防止多个进程同时对数据库进行写操作，从而保证了数据库的完整性和稳定性。

具体来说，当一个进程打开数据库时，它会**尝试获取文件锁**。如果成功获取锁，则说明当前没有其他进程在使用数据库目录，该进程可以**安全地打开数据库并进行操作**。如果获取锁失败，则说明已经有其他进程在使用数据库目录，当前进程将无法打开数据库，从而避免了多个进程同时对数据库进行写操作的情况发生。

**expiredCursorKey**

**cronScheduler** 自动合并定时器
```go
if len(options.AutoMergeCronExpr) > 0 {
	db.cronScheduler = cron.New(
		cron.WithParser(
			cron.NewParser(cron.SecondOptional | cron.Minute | cron.Hour |
				cron.Dom | cron.Month | cron.Dow | cron.Descriptor),
		),
	)
	_, err = db.cronScheduler.AddFunc(options.AutoMergeCronExpr, func() {
		// maybe we should deal with different errors with different logic, but a background task can't omit its error.
		// after auto merge, we should close and reopen the db.
		_ = db.Merge(true)
	})
	if err != nil {
		return nil, err
	}
	db.cronScheduler.Start()
}
```
`cronScheduler` 被用于启用自动合并任务。使用了第三方库 `cron`，该库提供了用于调度周期性任务的功能。

具体来说，`cronScheduler` 的作用是根据用户提供的定时表达式（`options.AutoMergeCronExpr`）来定期执行自动合并操作。在 `Open` 函数中，如果用户提供了定时表达式，就会创建一个 `cronScheduler` 实例，并**通过 `AddFunc` 方法向其添加一个定时任务，该任务会定期执行数据库的自动合并操作（`db.Merge(true)`）**。

当数据库被打开后，`cronScheduler` 就会开始根据定时表达式定期触发自动合并操作。这样就可以定期执行合并操作，以维护数据库的性能和稳定性，同时也可以确保数据文件不会无限增长，避免影响数据库的性能。