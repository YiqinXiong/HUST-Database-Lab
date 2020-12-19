#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemDelegate>
#include <QMainWindow>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void on_logged();  //登陆成功，显示主界面

    void on_tabWidget_currentChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void timeout_update();

    void on_submit2_clicked();

    void on_abort2_clicked();

    void on_submit3_clicked();

    void on_abort3_clicked();

    void on_submit4_clicked();

    void on_abort4_clicked();

    void on_btn_clicked();

    void on_tab6_currentChanged(int index);

    void on_btn_6_1_ok();

    void on_btn_6_1_delete();

    void on_btn_6_1_cancel();

    void on_btn_6_2_accept();

    void on_btn_6_2_reject();

    void on_addEmp_clicked();

    void on_deleteEmp_clicked();

   private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QSqlTableModel *model = nullptr;
    void show_tab1();
    void show_tab2();
    void show_tab3();
    void show_tab4();
    void show_tab5();
    void show_tab6();
    void show_tab6_tab1();
    void show_tab6_tab2();
};

class ReadOnlyDelegate : public QItemDelegate {
   public:
    ReadOnlyDelegate(QWidget *parent = nullptr) : QItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override  // final
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return nullptr;
    }
};

#endif  // MAINWINDOW_H
