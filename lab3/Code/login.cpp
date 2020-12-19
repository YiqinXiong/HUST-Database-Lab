#include "login.h"

#include "mainwindow.h"
#include "ui_login.h"
#include "utils.h"

struct Employee login::loggedEmp;

login::login(QWidget *parent) : QDialog(parent), ui(new Ui::login) {
    ui->setupUi(this);
    ui->inputEID->setFocus();  //把焦点放在输入工号的框
    ui->inputPWD->setEchoMode(QLineEdit::Password);  //密码输入形式
    ui->buttonBox->button(QDialogButtonBox::Ok)
        ->setText(QStringLiteral("提交"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)
        ->setText(QStringLiteral("取消"));
}

login::~login() { delete ui; }

//提交登录信息后
void login::on_buttonBox_accepted() {
    QString inputEID = ui->inputEID->text();
    QString inputPWD = ui->inputPWD->text();
    if (inputEID == "" || inputPWD == "") {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("工号和密码需填写完整"),
                             QMessageBox::Ok, QMessageBox::Ok);
        this->show();
        return;
    }
    bool isIntEID;
    int intEID = inputEID.toInt(&isIntEID, 10);
    if (!isIntEID) {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("工号需为数字"), QMessageBox::Ok,
                             QMessageBox::Ok);
        this->show();
        return;
    }
    QSqlQuery query;  //查询
    QString sqlStr =
        QString("select * from qbb.Employee where EID = %1").arg(intEID);
    query.exec(sqlStr);
    qDebug() << sqlStr;
    while (query.next()) {
        qDebug() << query.value(0);
        // 登陆成功
        if (inputPWD == query.value(3).toString()) {
            loggedEmp.EID = intEID;
            loggedEmp.PWD = inputPWD;
            loggedEmp.SID = query.value(1).toInt();
            loggedEmp.EType = query.value(2).toInt();
            loggedEmp.EName = query.value(4).toString();
            loggedEmp.logged = true;
            emit logged();
            return;
        }
    }
    // 登陆失败
    QMessageBox::warning(nullptr, QStringLiteral("警告"),
                         QStringLiteral("用户名或密码错误"), QMessageBox::Ok,
                         QMessageBox::Ok);
    this->show();
    return;
}
