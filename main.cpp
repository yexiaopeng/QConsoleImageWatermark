#include <QCoreApplication>


#include <QApplication>

#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include "QDebug"
#include <QStaticText>
#include <QPainter>
#include <QDateTime>


int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    //此处为Qt的一个Bug，没有QApplication的实例的情况下使用drawText会发生段错误
    QApplication a(argc, argv);

    //sourceImage 载如需要添加水印的原图
    QImage * sourceImage;
    sourceImage = new QImage();
    bool rc = sourceImage->load("./123.jpeg");
    qDebug() << rc;
    if(rc){
         qDebug() << sourceImage->size();
    }

     // 中间图片，仅仅显示水印的透明图片
     QString tempImagePath="./wetest.png";
     //图片上的字符串，例如 当前时间
     QString imageText= QDateTime::currentDateTime().toString("yyyy-MM-dd ddd hh:mm:ss");
     QFont font;
     //设置显示字体的大小
     font.setPixelSize(35);

     //指定图片大小 自己调整
     QSize size(900, 100);
     //以ARGB32格式构造一个QImage
     QImage destinationImage(size, QImage::Format_ARGB32);
     //填充图片背景,120/250为透明度
     destinationImage.fill(qRgba(255, 255, 255, 0));


     //为这个QImage构造一个QPainter
     QPainter m_painter(&destinationImage);
     //设置画刷的组合模式CompositionMode_SourceOut这个模式为目标图像在上。
     //改变组合模式和上面的填充方式可以画出透明的图片。
     m_painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
     m_painter.setBrush(Qt::blue);

     //改变画笔和字体
     QPen pen = m_painter.pen();
     pen.setColor(Qt::red);

     m_painter.setPen(pen);
     m_painter.setFont(font);

     //将时间戳写在Image的中心
     m_painter.drawText(destinationImage.rect(), Qt::AlignCenter, imageText);
     destinationImage.save(tempImagePath, "PNG", 100);

    //新建一张和原图一样大小的图片，用于表示最终的图片
    QImage resultImage;
    QSize resultSize = sourceImage->size();
    resultImage = QImage(resultSize,QImage::Format_ARGB32_Premultiplied);
    QPainter::CompositionMode mode = QPainter::CompositionMode_Plus;
    QPainter painter(&resultImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, destinationImage);
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, *sourceImage);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.end();
    resultImage.save("./over.jpeg");
    return a.exec();
}

