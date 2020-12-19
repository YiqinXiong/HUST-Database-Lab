#include <QApplication>

#include "login.h"
#include "mainwindow.h"
#include "utils.h"

bool OpenDatabase() {
    QSqlDatabase db =
        QSqlDatabase::addDatabase("QODBC");  //数据库驱动类型为SQL Server
    qDebug() << "ODBC driver?" << db.isValid();
    QString dsn = QString::fromLocal8Bit("MyShop");  //数据源名称
    db.setHostName("localhost");      //选择本地主机，127.0.1.1
    db.setDatabaseName(dsn);          //设置数据源名称
    db.setUserName("db_read_write");  //登录用户
    db.setPassword("xyq1999411");     //密码
    if (!db.open())                   //打开数据库
    {
        qDebug() << db.lastError().text();
        QMessageBox::critical(nullptr, QObject::tr("Database error"),
                              db.lastError().text());
        return false;  //打开失败
    } else
        qDebug() << "database open success!";
    return true;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //加载翻译文件
    QTranslator translator;
    translator.load("qt_zh_CN.qm");
    a.installTranslator(&translator);
    //连接数据库
    if (!OpenDatabase()) return 1;
    //创建窗口对象
    MainWindow w;
    login l;
    w.setWindowTitle(QStringLiteral("LEGO零售店库存管理系统"));
    l.setWindowTitle(QStringLiteral("登录系统"));
    //显示login窗口
    l.show();
    //槽函数连接登录窗口和主窗口，login界面登录成功后唤醒mainwindow
    QObject::connect(&l, SIGNAL(logged()), &w, SLOT(on_logged()));
    return a.exec();
}
