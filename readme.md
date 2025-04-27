> 2025/4/27 14:50:04

##### windows下编译

* 编译时报错C2001 常量中有换行符：file，另存为，保存那里选择编码后保存，选择unicode带bom的格式

* 编译时报错为什么这写不错那个错误	C2666	“Point::operator ==”: 重载函数具有类似的转换	：对于operator==(const)要声明为operator==(const) const

* 错误	C2614	“StartInterface”: 非法的成员初始化:“speed”不是基或成员	：转该文件名为带bom编译通过

##### vs关联到远程仓库

git init初始->创建gitignore文件->git add and git commit，github上手动创建仓库

git remote add origin xxx.git，然后git push -u origin master

之后在vs中视图->git更改就可以操作

或者没在远程创建仓库，直接点击git更改配置创建

