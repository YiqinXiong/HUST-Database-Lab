#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

struct Employee {
    bool logged = false;  //是否登录
    int EID;              //工号
    int EType;            //类别，0店员，1店长
    QString PWD;          //密码
    int SID;              //门店号
    QString EName;        //姓名
};

namespace Ui {
class login;
}

class login : public QDialog {
    Q_OBJECT

   public:
    static struct Employee loggedEmp;
    explicit login(QWidget *parent = nullptr);
    ~login();

   private slots:
    void on_buttonBox_accepted();
   signals:
    void logged();

   private:
    Ui::login *ui;
};

#endif  // LOGIN_H
