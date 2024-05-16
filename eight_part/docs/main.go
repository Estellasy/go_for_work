package main

import (
	"github.com/prometheus/common/model"
	"github.com/zeromicro/go-zero/tools/goctl/model/sql/test/model"
)

// func main() {
// 	ch := make(chan int)
// 	quit := make(chan bool)

// 	go func() {
// 		for {
// 			select {
// 			case num := <-ch: //如果有数据，下面打印。但是有可能ch一直没数据
// 				fmt.Println("num = ", num)
// 			case <-time.After(3 * time.Second): //上面的ch如果一直没数据会阻塞，那么select也会检测其他case条件，检测到后3秒超时
// 				fmt.Println("超时")
// 				quit <- true //写入
// 			}
// 		}

// 	}()

// 	for i := 0; i < 5; i++ {
// 		ch <- i
// 		time.Sleep(time.Second)
// 	}
// 	<-quit //这里暂时阻塞，直到可读
// 	fmt.Println("程序结束")
// }

func GithubCallBack() (resp *types.TokenResp, err error) {
	user_auth0 := model.UserAuth{}
	r := l.scvCtx.Mysql.Where("provider= ? and privider_id= ?", "github", l.ctx.Value("github_id")).First(&user_auth0)
	if r.RowsAffect == 0 {
		// 该用户为新用户 开始注册
		// 新建用户
		user := model.User{
			Password: password,
			UserNick: l.ctx.Value("github_name").("string"),
			CreateTime: nil,
			UpdateTime: nil,
		}

		l.scvCtx.Mysql.Create(&user)

		var user model.User
		// 写用户鉴权表
		user1_auth := model.UserAuth{
			CreateTime: time.Now(),
			UpdateTime: time.Now(),
			UserId:     user.UserId,
			ProviderId: l.ctx.Value("github_id").(string),
			Provider:   "github",
		}
		l.scvCtx.Mysql.Create(&user1_auth)
		// 生成accessTokenString
		accessTokenString, err := utils.GenerateToken(user.UserId, uuid.New().string())
		if accessTokenString=="" || refreshTokenString=="" {
		    
		}
		}
}
