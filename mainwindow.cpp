#include "mainwindow.h"
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
#include "QDialog"
#include "QFileDialog"
#include "QFile"
#include "QTextStream"
#include "QDebug"
#include "QMessageBox"
/*
在这个构造函数中，首先使用了基类 QMainWindow 的构造函数来初始化窗口。
接着，通过 new 关键字创建了一个 Ui::MainWindow 对象并将其赋值给 ui 成员变量
*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     /*-!-0、设置窗口名称-!-*/
    this->setWindowTitle("Shd_window");

    /*-!-1、设置窗口大小-!-*/
    this->resize(900,600);

    /*-!-2、基本控件设置-!-*/
    creatMenu(); //成员函数 菜单设置

    createTool();//成员函数 工具栏设置

    tcf = new QTextCharFormat; //创建了一个新的 QTextCharFormat 对象，并将其指针保存在变量 tcf 中
    tch = new QTextCharFormat;
}


void  MainWindow::creatMenu(){
    /*-!-获取菜单栏-!-*/
    QMenuBar *menuBar = this->menuBar(); //创建了一个指向 QMenuBar 对象的指针 menuBar，并将其初始化为当前窗口的菜单栏

    /*-!-定义文件菜单和编辑菜单-!-*/
    /*
        QMenu 是 Qt 中的一个菜单类，用于创建弹出式菜单和下拉菜单
    */
    QMenu *FileMenu = menuBar->addMenu("文件");//创建了一个名为 FileMenu 的指向 QMenu 对象的指针，并将其初始化为菜单栏 menuBar 上添加一个名称为 “文件” 的菜单
    QMenu *EditMenu = menuBar->addMenu("编辑");

    /*-!-向文件菜单中添加行为-!-*/
    newfile = FileMenu->addAction(QIcon("://image/qIcon/address-book-new.png"),"新建"); //创建了一个名为 newfile 的指向 QAction 对象的指针，并将其初始化为在菜单 FileMenu 上添加一个带图标和文本的动作项
    openfile = FileMenu->addAction(QIcon("://image/qIcon/document-open.png"),"打开");
    savefile = FileMenu->addAction(QIcon("://image/qIcon/document-save.png"),"保存");
    EditMenu->addAction("翻页");
}


void  MainWindow::createTool(){


    /*-!-3、添加工具栏-!-*/
    QToolBar* toolBar = this->addToolBar("工具");

    /*-!-通过工具栏添加新建行为-!-*/
    toolBar->addAction(newfile);
    toolBar->addSeparator();  /*-!-添加分隔符-!-*/
    /*-!-通过工具栏添加打开行为-!-*/
    toolBar->addAction(openfile);
    toolBar->addSeparator();  /*-!-添加分隔符-!-*/
    /*-!-通过工具栏添加保存行为-!-*/
    toolBar->addAction(savefile);


    /*-!-4、设置字体-!-*/
    QLabel*fontTypeLabel = new QLabel("字体:");
    toolBar->addWidget(fontTypeLabel);

    /*-!-4.1、设置字体框-!-*/
    QFontComboBox* fontTypeCmb = new QFontComboBox;
    toolBar->addWidget(fontTypeCmb);

    /*-!-5、设置字号-!-*/
    QLabel*fontSizeLabel = new QLabel("字号:");
    toolBar->addWidget(fontSizeLabel);

    /*-!-5.1、设置字号框-!-*/
    QComboBox* fontSizeCmb = new QComboBox;
    toolBar->addWidget(fontSizeCmb);

    int size =1;
    while(size<72)
    {
        fontSizeCmb->addItem(QString::number(size));  /*-!-设置字号-!-*/
        size++;
    }

    /*-!-6、设置加粗按钮-!-*/
    QToolButton*boldBtn = new QToolButton;
    boldBtn->setText("B");
    toolBar->addWidget(boldBtn);
    toolBar->addSeparator();  /*-!-添加分隔符-!-*/

    /*-!-6.1、设置斜体按钮-!-*/
    QToolButton*titlicBtn = new QToolButton;
    titlicBtn->setText("I");
    toolBar->addWidget(titlicBtn);

     /*-!-7、状态栏-!-*/
    QStatusBar* statusBar = this->statusBar();
    QLabel* timeLabel = new QLabel("时间：");
    statusBar->addWidget(timeLabel);

    /*-!-8、设置浮动窗口-!-*/
    QDockWidget* dockWidget = new QDockWidget;
    this->addDockWidget(Qt::BottomDockWidgetArea,dockWidget);


    /*-!-9、设置文本编辑框-!-*/
    textEdit = new QTextEdit;
    this->setCentralWidget(textEdit); //在 Qt 框架中设置主窗口的中心窗口部件



    /*-!-10、信号与槽字体改变-!-*/
    connect(fontTypeCmb,&QFontComboBox::currentFontChanged,this,&MainWindow::setFont);

    void (QComboBox::*p)(int)=&QComboBox::currentIndexChanged; //使用函数指针区分函数的重载

    /*-!-11、信号与槽字号改变-!-*/
    connect(fontSizeCmb,p,this,&MainWindow::setFontSize);

    /*-!-12、信号与槽加粗改变-!-*/
    connect(boldBtn,&QToolButton::clicked,this,&MainWindow::setBold);


    /*-!-13、信号与槽字体斜体-!-*/
    connect(titlicBtn,&QToolButton::clicked,this,&MainWindow::setitalic);

    /*-!-14、保存文件-!-*/
    connect(savefile,&QAction::triggered,this,&MainWindow::savefilex);


    /*-!-15、打开文件-!-*/
    connect(openfile,&QAction::triggered,this,&MainWindow::openfilex);

    /*-!-16、新建文件-!-*/
    connect(newfile,&QAction::triggered,this,&MainWindow::newfilex);



}


 /*-!-10.1、信号与槽 字体改变 槽函数-!-*/
/*
   这儿为什么要用两个变量分别记录字号和字体，因为字体改变时会重新初始化字号，导致
   已经改变了的字体恢复成了原始的模样，因此用全局变量，记录字号，当字体改变时重新
   把字号也刷新一遍。但是还是有bug,当字体改变为不同时 有bug
*/

void  MainWindow::setFont(const QFont &font){
    //QTextCharFormat tch;  /*-!-文本布局-!-*/
    tcf->setFont(font);
    textEdit->mergeCurrentCharFormat(*tcf); /*-!-合并选中的布局-!-*/
    textEdit->mergeCurrentCharFormat(*tch); /*-!-合并选中的布局-!-*/
}

 /*-!-11.1、信号与槽 字号改变 槽函数-!-*/
void  MainWindow::setFontSize(int index){
    //QTextCharFormat tch;  /*-!-文本布局-!-*/
    tch->setFontPointSize(double(index));
    textEdit->mergeCurrentCharFormat(*tch); /*-!-合并选中的布局-!-*/
}

 /*-!-12.1、信号与槽 加粗 槽函数-!-*/
void  MainWindow::setBold()
{
     QTextCharFormat tch;  /*-!-文本布局-!-*/
    if(textEdit->fontWeight()>QFont::Normal)
    {
        tch.setFontWeight(QFont::Normal);
    }
    else{
        tch.setFontWeight(QFont::Bold);
    }
    textEdit->mergeCurrentCharFormat(tch);
}

 /*-!-13.1、信号与槽 斜体 槽函数-!-*/
void  MainWindow::setitalic()
{
   QTextCharFormat tch;  /*-!-文本布局-!-*/
    /*
    textEdit 可能是一个 QTextEdit 或类似的文本编辑器部件，
    而 fontItalic() 是一个成员函数，用于获取当前选中文本的字体设置是否为斜体。
    若为斜体，则返回的值大于 QFont::StyleNormal，否则返回 QFont::StyleNormal
    */
   if(textEdit->fontItalic()>QFont::StyleNormal)
   {
       tch.setFontItalic(QFont::StyleNormal);
   }
   else{
       tch.setFontItalic(QFont::StyleItalic);
   }
   textEdit->mergeCurrentCharFormat(tch);
}


void MainWindow::savefilex()
{
    //非模态对话框
//    QDialog *d = new QDialog;
//    d->show();

    QString filename = QFileDialog::getSaveFileName();//Qt 提供的用于选择保存文件路径的对话框函数。通过调用这个函数，可以让用户选择一个文件保存的路径和名称，并将选择的路径和名称作为返回值。
    QFile f(filename); //创建一个名为 f 的 QFile 对象，其中 filename 是之前通过 QFileDialog::getSaveFileName() 函数获取的文件路径和名称
    if(f.open(QIODevice::ReadWrite))
    {
        QTextStream fin(&f); //文本流绑定文件
        fin<<textEdit->toPlainText(); //通过文本流将文件输入到f文件中
        qDebug()<<"save file success!";
    }
    else
    {
        qDebug()<<"save file filed!";
    }

}


void MainWindow::openfilex()
{
    //非模态对话框
//    QDialog *d = new QDialog;
//    d->show();

    QString filename = QFileDialog::getOpenFileName();//Qt 提供的用于选择保存文件路径的对话框函数。通过调用这个函数，可以让用户选择一个文件保存的路径和名称，并将选择的路径和名称作为返回值。
    QFile f(filename); //创建一个名为 f 的 QFile 对象，其中 filename 是之前通过 QFileDialog::getSaveFileName() 函数获取的文件路径和名称
    if(f.open(QIODevice::ReadWrite))
    {
        QTextStream fout(&f); //文本流绑定文件
        textEdit->setText(fout.readAll());
        this->setWindowTitle(filename);
        qDebug()<<"read file success!";
    }
    else
    {
        qDebug()<<"read file filed!";
    }

}

void  MainWindow::newfilex()
{
    if(QMessageBox::question(this,"question","是否保存当前文件",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes)
    {
        savefilex();
    }
    textEdit->clear();
}



MainWindow::~MainWindow()
{
    delete ui;
}

