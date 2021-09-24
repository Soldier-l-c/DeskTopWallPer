## 桌面壁纸随机更换
### 随机图api接口：
https://unsplash.it/1600/900?random
### 图片存储位置：
%programdata%/DesktopWallper
### 命令行及参数
```
//随机图api地址 默认https://unsplash.it/1600/900?random
#define C_IMAGE_URL		"image_url="    
//轮询间隔 默认10*60*1000.10分钟
#define C_OERIOD_TIME	"period_time="  
//是否执行一次 默认false
#define C_IS_CALL_ONCE	"call_once="   
//轮询次数 默认INT_MAX
#define C_NUM_OF_PERIOD	"period_num="   

//demo
DeskTopWallPer.exe image_url=https://unsplash.it/1600/900?random period_time=1000 call_once=0 period_num=2
```


