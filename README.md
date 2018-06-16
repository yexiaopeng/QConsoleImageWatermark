# QConsoleImageWatermark
- Qt 控制台程序  为照片加水印
- 开发环境：Ubuntu16 64bit + Qt 5.5
- 联系邮箱：yexiaopeng1992@126.com

## 本例实现的是一个基Qt于控制台的图片添加水印的功能
- 先生成一张中间图片。背景透明，使用drawText写入文字。
- 在生成一张尺寸与需要加水印图片一样的空白图片，将原图与带水印文字的图片合成一张最终的图。

## 演示
- 在编译出来的可执行程序路径下放置一张和代码中相同名称的图片，再运行代码就可以了

## 注意点
- 因为是控制台程序，Qt Creator自动生成的是QCoreApplication a(argc, argv)，而在使用QImage的drawText函数时，执行程序报段错误。  根据 http://srinikom.github.io/pyside-bz-archive/1146.html 中的说法，这是Qt的一个Bug，但他们不想花费过多时间修改。   解决方法是将QCoreApplication a(argc, argv)改为 QApplication a(argc, argv);

## 主要参考
- Qt 官方例子  Imagecompositon，在Qt Creator示例中搜索QPainter，图片为蝴蝶那个例子