#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>

#include "ui_mainwindow.h"
#include "QMenuBar"
#include "QToolBar"
#include "QIcon"
#include "QLabel"
#include "QFontComboBox"
#include "QComboBox"
#include "QString"
#include "QStringList"
#include "QToolButton"
#include "QStatusBar"
#include "QDockWidget"
#include "QTextEdit"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction* newfile;  //创建了一个名为 newfile 的指向 QAction 对象的指针
    QAction* openfile;
    QAction* savefile;
    QTextEdit* textEdit;
    /*
       这行代码声明了一个名为 tcf 的指向 QTextCharFormat 对象的指针，但并没有为其分配内存或初始化
       在使用指针之前，需要为其分配内存，并且初始化为有效的 QTextCharFormat 对象。可以使用 new 运算符为其分配内存
       QTextCharFormat* tcf = new QTextCharFormat;
    */
    QTextCharFormat* tcf; //字体变量
    QTextCharFormat* tch;//字号变量
    void  creatMenu(); //创建菜单槽函数
    void  createTool(); //创建工具栏槽函数
    void  setFont(const QFont &font);//创建字体格式槽函数
    void  setFontSize(int index);//创建字体大小槽函数
    void  setBold();//创建字体加粗槽函数
    void  setitalic();//创建字体斜体槽函数
    void  savefilex();//保存槽函数
    void  openfilex();//打开文件
    void  newfilex();//新建文件

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
