#include "mainwindow.h"

#include "login.h"
#include "ui_mainwindow.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(1);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout_update()));
    timer->start(1000);  //每1s刷新一次
}

MainWindow::~MainWindow() {
    delete ui;
    delete model;
    delete timer;
}

//每1s触发
void MainWindow::timeout_update() {
//    qDebug() << "in func \"timeout_update\"";
    QString MDate;  //售出日期和时间
    QDateTime dateTime;
    MDate = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->curTime->setText(
        QString("%1:%2").arg(QStringLiteral("当前系统时间")).arg(MDate));
}

//登陆后展示窗口
void MainWindow::on_logged() {
    qDebug() << login::loggedEmp.EID << login::loggedEmp.EType
             << login::loggedEmp.PWD << login::loggedEmp.SID
             << login::loggedEmp.logged;
    this->show();
    ui->NAME->setText(login::loggedEmp.EName);
    ui->EID->setNum(login::loggedEmp.EID);
    QString typeStr = login::loggedEmp.EType == 1 ? QStringLiteral("店长")
                                                  : QStringLiteral("店员");
    ui->TYPE->setText(typeStr);
    ui->SID->setNum(login::loggedEmp.SID);
    //    show_tab1();
}

//切换tab页面时刷新
void MainWindow::on_tabWidget_currentChanged(int index) {
    switch (index) {
        case 0:
            //人员管理
            show_tab1();
            break;
        case 1:
            //货品查询
            show_tab2();
            break;
        case 2:
            //进货
            show_tab3();
            break;
        case 3:
            //售货
            show_tab4();
            break;
        case 4:
            //销售记录统计
            show_tab5();
            break;
        case 5:
            //调货申请处理
            show_tab6();
            break;
        default:
            break;
    }
}

//人员管理页面
void MainWindow::show_tab1() {
    qDebug() << QStringLiteral("切换到tab1");
    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate();  //设置某列只读
    //仅店主可增删员工
    if (login::loggedEmp.EType != 1) {
        ui->groupBox_12->setVisible(false);  //按钮不可见
    }
    if (model == nullptr) model = new QSqlTableModel(this);
    model->setTable("qbb.Employee");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //    仅店主可查看所有信息
    if (login::loggedEmp.EType != 1)
        model->setFilter(QString("SID=%1 and EID=%2")
                             .arg(login::loggedEmp.SID)
                             .arg(login::loggedEmp.EID));
    else
        model->setFilter(QString("SID=%1").arg(login::loggedEmp.SID));
    model->setSort(0, Qt::AscendingOrder);  //按工号升序
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("工号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("所属门店号"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("员工类型码"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("密码"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("名字"));

    //    不可编辑列
    ui->tableView->setItemDelegateForColumn(0, readOnlyDelegate);
    ui->tableView->setItemDelegateForColumn(1, readOnlyDelegate);
    if (login::loggedEmp.EType != 1)
        ui->tableView->setItemDelegateForColumn(2, readOnlyDelegate);
    //    宽度自适应填满
    ui->tableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    //    颜色交错
    ui->tableView->setAlternatingRowColors(true);
    //    设置model
    ui->tableView->setModel(model);
    ui->tableView->show();
}

//货品查询页面
void MainWindow::show_tab2() {
    qDebug() << QStringLiteral("切换到tab2");
    //设置默认值
    //    on_abort2_clicked();
    //设置表格
    ui->table2->setColumnCount(8);
    QStringList headers;  //表头
    headers << QStringLiteral("货号") << QStringLiteral("品名")
            << QStringLiteral("积木块数") << QStringLiteral("适合年龄")
            << QStringLiteral("单价") << QStringLiteral("折扣")
            << QStringLiteral("所在门店") << QStringLiteral("数量");
    ui->table2->setHorizontalHeaderLabels(headers);
    ui->table2->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);                                       //填满
    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table2->horizontalHeader()->setStretchLastSection(true);    //填满
}

//进货页面
void MainWindow::show_tab3() {
    qDebug() << QStringLiteral("切换到tab3");
    //设置默认值
    //    on_abort3_clicked();
    QSqlQuery query;  //查询
    QString sqlStr;
    int nRow, nCol;
    //**********最近一周稀缺统计**********
    QString curDate;  //当前日期
    QDate date;
    curDate = date.currentDate().toString("yyyy-MM-dd");
    //进行查询
    sqlStr = QString("select JID,COUNT(*) as Records,SUM(LNum) as Amount ");
    sqlStr.append("from qbb.LackCount ");
    sqlStr.append(QString("where DATEDIFF(DD,LDate,'%1') between 0 and 6 ")
                      .arg(curDate));  //一周内记录
    sqlStr.append("group by JID ");
    sqlStr.append(
        "order by Amount desc,JID ");  //按缺货数降序，若缺货数相同则按货号升序
    qDebug() << sqlStr;
    query.exec(sqlStr);
    //设置表格
    ui->table3_1->setColumnCount(4);
    QStringList headers;  //表头
    headers << QStringLiteral("排名") << QStringLiteral("货号")
            << QStringLiteral("缺货单数") << QStringLiteral("缺货数");
    ui->table3_1->setHorizontalHeaderLabels(headers);
    ui->table3_1->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);  //填满
    ui->table3_1->setEditTriggers(
        QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table3_1->horizontalHeader()->setStretchLastSection(true); //填满
    //填写表格
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table3_1->setRowCount(nRow);
    nCol = ui->table3_1->columnCount();
    for (int i = 0; i < nRow; i++) {
        qDebug() << query.value(0).toInt();
        for (int j = 0; j < nCol; j++) {
            if (j == 0) {
                ui->table3_1->setItem(
                    i, j, new QTableWidgetItem(QString("%1").arg(i + 1)));
            } else {
                ui->table3_1->setItem(
                    i, j, new QTableWidgetItem(query.value(j - 1).toString()));
            }
            ui->table3_1->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                       Qt::AlignVCenter);
        }
        query.next();
    }
    //**********本店缺货记录**********
    //进行查询
    sqlStr = QString("select LID,JID,Lack.EID,LNum,LDate ");
    sqlStr.append("from qbb.Lack,EmployeeSafe ");
    sqlStr.append("where Lack.EID=EmployeeSafe.EID ");
    sqlStr.append(QString("and SID=%1 ").arg(login::loggedEmp.SID));
    qDebug() << sqlStr;
    query.exec(sqlStr);
    //设置表格
    ui->table3_2->setColumnCount(5);
    QStringList headers_myshop;  //表头
    headers_myshop << QStringLiteral("缺货编号") << QStringLiteral("货号")
                   << QStringLiteral("操作工号") << QStringLiteral("缺货数")
                   << QStringLiteral("时间");
    ui->table3_2->setHorizontalHeaderLabels(headers_myshop);
    ui->table3_2->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);  //填满
    ui->table3_2->setEditTriggers(
        QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table3_1->horizontalHeader()->setStretchLastSection(true); //填满
    //填写表格
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table3_2->setRowCount(nRow);
    nCol = ui->table3_2->columnCount();
    for (int i = 0; i < nRow; i++) {
//        qDebug() << query.value(0).toInt();
        for (int j = 0; j < nCol; j++) {
            //倒数第一列为时间
            if (j == nCol - 1) {
                ui->table3_2->setItem(
                    i, j,
                    new QTableWidgetItem(query.value(j).toDateTime().toString(
                        "yyyy-MM-dd hh:mm:ss")));
            } else {
                ui->table3_2->setItem(
                    i, j, new QTableWidgetItem(query.value(j).toString()));
            }
            ui->table3_2->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                       Qt::AlignVCenter);
        }
        query.next();
    }
}

//售货页面
void MainWindow::show_tab4() {
    qDebug() << QStringLiteral("切换到tab4");
    //设置默认值
    //    on_abort4_clicked();
    //设置表格
    ui->table4->setColumnCount(10);
    QStringList headers;  //表头
    headers << QStringLiteral("货号") << QStringLiteral("品名")
            << QStringLiteral("积木块数") << QStringLiteral("适合年龄")
            << QStringLiteral("单价") << QStringLiteral("折扣")
            << QStringLiteral("所在门店") << QStringLiteral("库存数量")
            << QStringLiteral("售出数量") << QStringLiteral("操作");
    ui->table4->setHorizontalHeaderLabels(headers);
    ui->table4->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);                                       //填满
    ui->table4->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table2->horizontalHeader()->setStretchLastSection(true);    //填满
}

//销售记录统计页面
void MainWindow::show_tab5() {
    qDebug() << QStringLiteral("切换到tab5");
    //仅店主可访问
    if (login::loggedEmp.EType != 1) {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("仅店主可访问此页面"),
                             QMessageBox::Ok, QMessageBox::Ok);
        ui->tabWidget->setCurrentIndex(1);
        return;
    }
    //**********本店销售统计**********
    //进行查询
    QSqlQuery query;  //查询
    QString sqlStr;
    //    sqlStr = QString("select
    //    EmployeeSafe.EID,EmployeeSafe.EName,Records,Items,Amount,SID from
    //    EmployeeSafe,"); sqlStr.append("(select EmployeeSafe.EID as
    //    EID,COUNT(*) as Records,SUM(MNum) as Items,SUM(TotalPrice) as Amount
    //    "); sqlStr.append("from EmployeeSafe,Market ");
    //    sqlStr.append(QString("where EmployeeSafe.EID=Market.EID and SID=%1
    //    ").arg(login::loggedEmp.SID)); sqlStr.append("group by
    //    EmployeeSafe.EID) as temp "); sqlStr.append("where
    //    temp.EID=EmployeeSafe.EID "); sqlStr.append("order by Amount
    //    desc,EID");
    sqlStr = QString("select * from SaleCount where SID=%1")
                 .arg(login::loggedEmp.SID);
    sqlStr.append(
        "order by Amount desc,EID");  //按销售额降序，若销售额相同则按工号升序
    qDebug() << sqlStr;
    query.exec(sqlStr);
    //设置表格
    ui->table5->setColumnCount(7);
    QStringList headers;  //表头
    headers << QStringLiteral("排名") << QStringLiteral("工号")
            << QStringLiteral("姓名") << QStringLiteral("销售单数")
            << QStringLiteral("销售商品数量") << QStringLiteral("销售额")
            << QStringLiteral("所在门店号");
    ui->table5->setHorizontalHeaderLabels(headers);
    ui->table5->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);                                       //填满
    ui->table5->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table2->horizontalHeader()->setStretchLastSection(true);    //填满
    //填写表格
    int nRow, nCol;
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table5->setRowCount(nRow);
    nCol = ui->table5->columnCount();
    for (int i = 0; i < nRow; i++) {
//        qDebug() << query.value(0).toInt();
        for (int j = 0; j < nCol; j++) {
            if (j == 0) {
                ui->table5->setItem(
                    i, j, new QTableWidgetItem(QString("%1").arg(i + 1)));
            } else {
                ui->table5->setItem(
                    i, j, new QTableWidgetItem(query.value(j - 1).toString()));
            }
            ui->table5->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                     Qt::AlignVCenter);
        }
        query.next();
    }
    //**********全局销售统计**********
    //开始SQL语句
    bool res2;
    sqlStr = QString(
        "select top 100 percent Shop.SID,SName,CityName,SUM(Records) as "
        "Rec,SUM(Items) as Ite,SUM(Amount) as Amo ");
    sqlStr.append("from SaleCount,qbb.Shop ");
    sqlStr.append("where SaleCount.SID=Shop.SID ");
    sqlStr.append("group by Shop.SID,SName,CityName ");
    sqlStr.append(
        "order by Amo desc,SID");  //按销售额降序，若销售额相同则按店号升序
    qDebug() << sqlStr;
    res2 = query.exec(sqlStr);
    //结束SQL语句

    //设置表格
    ui->table5_global->setColumnCount(7);
    QStringList headers_global;  //表头
    headers_global << QStringLiteral("排名") << QStringLiteral("店号")
                   << QStringLiteral("店名") << QStringLiteral("所在地")
                   << QStringLiteral("销售单数")
                   << QStringLiteral("销售商品数量")
                   << QStringLiteral("销售额");
    ui->table5_global->setHorizontalHeaderLabels(headers_global);
    ui->table5_global->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);  //填满
    ui->table5_global->setEditTriggers(
        QAbstractItemView::NoEditTriggers);  //不可编辑
    //填写表格
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table5_global->setRowCount(nRow);
    nCol = ui->table5_global->columnCount();
    for (int i = 0; i < nRow; i++) {
//        qDebug() << query.value(0).toInt();
        for (int j = 0; j < nCol; j++) {
            if (j == 0) {
                ui->table5_global->setItem(
                    i, j, new QTableWidgetItem(QString("%1").arg(i + 1)));
            } else {
                ui->table5_global->setItem(
                    i, j, new QTableWidgetItem(query.value(j - 1).toString()));
            }
            ui->table5_global->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                            Qt::AlignVCenter);
        }
        query.next();
    }
}

//调货申请处理页面
void MainWindow::show_tab6() {
    qDebug() << QStringLiteral("切换到tab6");
    ui->tab6->setCurrentIndex(0);
    show_tab6_tab1();
}

// tab1提交
void MainWindow::on_buttonBox_accepted() {
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, QStringLiteral("警告"),
                             QStringLiteral("数据库报告了错误: %1")
                                 .arg(model->lastError().text()));
    }
    show_tab1();
}

// tab1重置
void MainWindow::on_buttonBox_rejected() { model->revertAll(); }

// tab2提交
void MainWindow::on_submit2_clicked() {
    bool JID2isInt;
    int JID2;        //货号
    QString JName2;  //品名
    int JNum2;       //积木数
    int JAge2;       //适龄
    double Price;    //单价
    //读取查询单
    JID2 = ui->JID2->text().toInt(&JID2isInt, 10);
    if (ui->JID2->text() != "" && !JID2isInt) {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("货号需为数字"), QMessageBox::Ok,
                             QMessageBox::Ok);
        return;
    }
    JName2 = ui->JName2->text();
    JNum2 = ui->JNum2->value();
    JAge2 = ui->JAge2->value();
    Price = ui->Price2->value();
    //进行查询
    QSqlQuery query;  //查询
    QString sqlStr;
    sqlStr = QString(
        "select JID,JName,JNum,JAge,Price,Discount,SID,RNum from RepoDetail ");
    if (ui->JID2->text() != "") {
        sqlStr.append(QString("where JID=%1 ").arg(JID2));
        sqlStr.append(
            QString("and SID=%1 ").arg(login::loggedEmp.SID));  //限于本店内库存
    } else {
        if (JName2 == "") JName2 = "%";
        qDebug() << "JName2:" << JName2;
        sqlStr.append(QString("where JName like '%1'").arg(JName2));
        sqlStr.append(QString("and JNum >= %1 ").arg(JNum2));
        sqlStr.append(QString("and JAge <= %1 ").arg(JAge2));
        sqlStr.append(QString("and Price <= %1 ").arg(Price));
        sqlStr.append(
            QString("and SID=%1 ").arg(login::loggedEmp.SID));  //限于本店内库存
    }

    query.exec(sqlStr);
    //设置表格
    ui->table2->setColumnCount(8);
    QStringList headers;  //表头
    headers << QStringLiteral("货号") << QStringLiteral("品名")
            << QStringLiteral("积木块数") << QStringLiteral("适合年龄")
            << QStringLiteral("单价") << QStringLiteral("折扣")
            << QStringLiteral("所在门店") << QStringLiteral("数量");
    ui->table2->setHorizontalHeaderLabels(headers);
    ui->table2->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);                                       //填满
    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table2->horizontalHeader()->setStretchLastSection(true);    //填满
    //填写表格
    int nRow, nCol;
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table2->setRowCount(nRow);
    nCol = ui->table2->columnCount();
    for (int i = 0; i < nRow; i++) {
        qDebug() << query.value(0).toInt();
        for (int j = 0; j < nCol; j++) {
            ui->table2->setItem(
                i, j, new QTableWidgetItem(query.value(j).toString()));
            ui->table2->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                     Qt::AlignVCenter);
        }
        query.next();
    }
}

// tab2重置
void MainWindow::on_abort2_clicked() {
    ui->JID2->setText("");
    ui->JName2->setText("");
    ui->JNum2->setValue(0);
    ui->JAge2->setValue(100);
    ui->Price2->setValue(999999.00);
    //    ui->table2->clear();
    ui->table2->setRowCount(0);
}

// tab3提交
void MainWindow::on_submit3_clicked() {
    bool JIDisInt;
    int JID;          //货号
    QString JName;    //品名
    int JNum;         //积木数
    int JAge;         //适龄
    double Price;     //单价
    double Discount;  //折扣
    int RNum;         //进货数目
    if (ui->JID3->text() == "") {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("货号必须填写"), QMessageBox::Ok,
                             QMessageBox::Ok);
        return;
    }
    //读取查询单
    JID = ui->JID3->text().toInt(&JIDisInt, 10);
    if (!JIDisInt) {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("货号需为数字"), QMessageBox::Ok,
                             QMessageBox::Ok);
        return;
    }
    JName = ui->JName3->text();
    JNum = ui->JNum3->value();
    JAge = ui->JAge3->value();
    Price = ui->Price3->value();
    Discount = ui->Discount3->value();
    RNum = ui->RNum3->value();

    QSqlQuery query;  //查询
    query.exec(QString("select * from qbb.Juggle where JID=%1").arg(JID));
    QString msg;
    //货号存在
    if (query.first()) {
        query.exec(QString("select * from qbb.Repo where JID=%1 and SID=%2")
                       .arg(JID)
                       .arg(login::loggedEmp.SID));
        //本店有库存
        if (query.first()) {
            query.exec(
                QString(
                    "update qbb.Repo set RNum=RNum+%1 where JID=%2 and SID=%3")
                    .arg(RNum)
                    .arg(JID)
                    .arg(login::loggedEmp.SID));
            msg = QStringLiteral("进货成功！店内有库存，直接更新库存数目");
        }
        //本店无库存
        else {
            query.exec(QString("insert into qbb.Repo values (%1,%2,%3)")
                           .arg(login::loggedEmp.SID)
                           .arg(JID)
                           .arg(RNum));
            msg = QStringLiteral("进货成功！店内无库存，插入新库存项");
        }
    }
    //货号不存在
    else {
        if (JName == "") {
            QMessageBox::warning(nullptr, QStringLiteral("警告"),
                                 QStringLiteral("货号不存在，品名必须填写"),
                                 QMessageBox::Ok, QMessageBox::Ok);
            return;
        }
        //开始事务
        query.exec("begin transaction");
        //新货品信息加入Juggle表
        bool ok1 = query.exec(
            QString("insert into qbb.Juggle values (%1,'%2',%3,%4,%5,%6)")
                .arg(JID)
                .arg(JName)
                .arg(JNum)
                .arg(JAge)
                .arg(Price)
                .arg(Discount));
        //新库存信息加入Repo表
        bool ok2 = query.exec(QString("insert into qbb.Repo values (%1,%2,%3)")
                                  .arg(login::loggedEmp.SID)
                                  .arg(JID)
                                  .arg(RNum));
        if (ok1 && ok2) {
            query.exec("commit");
            msg = QStringLiteral(
                "进货成功！货号不存在，货品表插入新货品，库存表插入新库存");
        } else {
            query.exec("rollback");
            QMessageBox::warning(nullptr, QStringLiteral("警告"),
                                 QStringLiteral("出现错误，已回滚"),
                                 QMessageBox::Ok, QMessageBox::Ok);
        }
        //结束事务
    }
    QTime time = QTime::currentTime();
    QString t_str = time.toString("hh:mm:ss");
    ui->list3->addItem(QString("[%1]%2").arg(t_str).arg(msg));
}

// tab3重置
void MainWindow::on_abort3_clicked() {
    ui->JID3->setText("");
    ui->JName3->setText("");
    ui->JNum3->setValue(0);
    ui->JAge3->setValue(100);
    ui->Price3->setValue(999999.00);
    ui->Discount3->setValue(1.00);
    ui->RNum3->setValue(1);
    ui->list3->clear();
}

// tab4提交
void MainWindow::on_submit4_clicked() {
    //刷新table
    ui->table4->clear();
    ui->table4->setRowCount(0);
    bool JIDisInt;
    int JID;        //货号
    QString JName;  //品名
    int JNum;       //积木数
    int JAge;       //适龄
    double Price;   //单价
    int MNum;       //售出数量
    QString MDate;  //售出日期和时间
    QDateTime dateTime;
    MDate = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    //读取查询单
    JID = ui->JID4->text().toInt(&JIDisInt, 10);
    if (ui->JID4->text() != "" && !JIDisInt) {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("货号需为数字"), QMessageBox::Ok,
                             QMessageBox::Ok);
        return;
    }
    JName = ui->JName4->text();
    JNum = ui->JNum4->value();
    JAge = ui->JAge4->value();
    Price = ui->Price4->value();
    MNum = ui->MNum4->value();
    //进行查询
    QSqlQuery query;      //查询
    QSqlQuery queryLack;  //查询缺货
    QString sqlStr;
    sqlStr = QString(
        "select JID,JName,JNum,JAge,Price,Discount,SID,RNum from RepoDetail ");
    if (ui->JID4->text() != "") {
        sqlStr.append(QString("where JID=%1 ").arg(JID));
    } else {
        if (JName == "") JName = "%";
        qDebug() << "JName2:" << JName;
        sqlStr.append(QString("where JName like '%1'").arg(JName));
        sqlStr.append(QString("and JNum >= %1 ").arg(JNum));
        sqlStr.append(QString("and JAge <= %1 ").arg(JAge));
        sqlStr.append(QString("and Price <= %1 ").arg(Price));
    }
    sqlStr.append(
        QString("and RNum >= %1 ").arg(MNum));  //剩余库存数大于将要售出数
    sqlStr.append("order by SID,RNum desc");  //按店号排序，同一店内按剩余数降序
    query.exec(sqlStr);
    //设置表格
    ui->table4->setColumnCount(10);
    QStringList headers;  //表头
    headers << QStringLiteral("货号") << QStringLiteral("品名")
            << QStringLiteral("积木块数") << QStringLiteral("适合年龄")
            << QStringLiteral("单价") << QStringLiteral("折扣")
            << QStringLiteral("所在门店") << QStringLiteral("库存数量")
            << QStringLiteral("售出数量") << QStringLiteral("操作");
    ui->table4->setHorizontalHeaderLabels(headers);
    ui->table4->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);                                       //填满
    ui->table4->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table2->horizontalHeader()->setStretchLastSection(true);    //填满
    //    若未查询到相关信息则写入缺货记录
    if (!query.first()) {
        if (queryLack.exec(QString("insert into Lack(EID,JID,LNum,LDate) "
                                   "values (%1,%2,%3,'%4')")
                               .arg(login::loggedEmp.EID)
                               .arg(JID)
                               .arg(MNum)
                               .arg(MDate)))
            QMessageBox::warning(nullptr, QStringLiteral("警告"),
                                 QStringLiteral("无结果，已写入缺货记录"),
                                 QMessageBox::Ok, QMessageBox::Ok);
        else
            QMessageBox::warning(nullptr, QStringLiteral("警告"),
                                 QStringLiteral("货号不存在"), QMessageBox::Ok,
                                 QMessageBox::Ok);
        return;
    }
    //填写表格
    int nRow, nCol;
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table4->setRowCount(nRow);
    nCol = ui->table4->columnCount();
    for (int i = 0; i < nRow; i++) {
        qDebug() << query.value(0).toInt();
        for (int j = 0; j < nCol - 2; j++) {
            ui->table4->setItem(
                i, j, new QTableWidgetItem(query.value(j).toString()));
            ui->table4->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                     Qt::AlignVCenter);
        }
        //倒数第二列添加售出数量
        ui->table4->setItem(i, nCol - 2,
                            new QTableWidgetItem(QString("%1").arg(MNum)));
        ui->table4->item(i, nCol - 2)
            ->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //最后一列添加按钮
        QPushButton *pBtn = new QPushButton();
        if (query.value(6).toInt() == login::loggedEmp.SID) {
            pBtn->setText(QStringLiteral("出售"));
        } else {
            pBtn->setText(QStringLiteral("调货"));
        }
        connect(pBtn, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
        ui->table4->setCellWidget(i, nCol - 1, pBtn);  //如果点击按钮出现崩溃现象，就添加QTableWidgetItem
                                                       //到按钮的那个单元格
        //下一条query结果
        query.next();
    }
}

// tab4重置
void MainWindow::on_abort4_clicked() {
    ui->JID4->setText("");
    ui->JName4->setText("");
    ui->JNum4->setValue(0);
    ui->JAge4->setValue(100);
    ui->Price4->setValue(999999.00);
    ui->MNum4->setValue(1);
    //    ui->table4->clear();
    ui->table4->setRowCount(0);
}

//出售、调货按钮
void MainWindow::on_btn_clicked() {
    QPushButton *sendBtn = qobject_cast<QPushButton *>(sender());
    if (sendBtn == nullptr) {
        return;
    }
    QModelIndex index = ui->table4->indexAt(
        QPoint(sendBtn->frameGeometry().x(), sendBtn->frameGeometry().y()));
    int row = index.row();
    int JID = ui->table4->item(row, 0)->text().toInt();
    double Price = ui->table4->item(row, 4)->text().toDouble();
    double Discount = ui->table4->item(row, 5)->text().toDouble();
    int SID = ui->table4->item(row, 6)->text().toInt();
    int MNum = ui->table4->item(row, 8)->text().toInt();
    double TotalPrice;                     //合计收款
    TotalPrice = Price * Discount * MNum;  //总价=单价*折扣*数量
    QString MDate;                         //售出日期和时间
    QDateTime dateTime;
    MDate = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //数据库查询
    QSqlQuery query, queryRepo, queryLack, queryMarket, queryTransfer;
    //本店售出
    if (SID == login::loggedEmp.SID) {
        //开始事务
        query.exec("begin transaction");
        //更新库存数量
        bool repoOK = query.exec(
            QString("update qbb.Repo set RNum=RNum-%1 where JID=%2 and SID=%3")
                .arg(MNum)
                .arg(JID)
                .arg(SID));
        //写入销售记录
        bool marketOK = query.exec(
            QString("insert into qbb.Market(JID,MNum,TotalPrice,EID,MDate) "
                    "values (%1,%2,%3,%4,'%5')")
                .arg(JID)
                .arg(MNum)
                .arg(TotalPrice)
                .arg(login::loggedEmp.EID)
                .arg(MDate));
        if (repoOK && marketOK) {
            query.exec("commit");
            QMessageBox::information(nullptr, QStringLiteral("完成"),
                                     QStringLiteral("售货成功!"),
                                     QMessageBox::Ok, QMessageBox::Ok);
        } else {
            query.exec("rollback");
            QMessageBox::warning(nullptr, QStringLiteral("警告"),
                                 QStringLiteral("出现错误，已回滚"),
                                 QMessageBox::Ok, QMessageBox::Ok);
        }
        //结束事务
    }
    //外店调货
    else {
        int FSID = login::loggedEmp.SID;
        int TSID = SID;
        //开始事务
        query.exec("begin transaction");
        //写入缺货记录
        bool lackOK =
            query.exec(QString("insert into qbb.Lack(EID,JID,LNum,LDate) "
                               "values (%1,%2,%3,'%4')")
                           .arg(login::loggedEmp.EID)
                           .arg(JID)
                           .arg(MNum)
                           .arg(MDate));
        //写入调货记录
        bool transferOK = query.exec(
            QString(
                "insert into qbb.Transfer(FSID,TSID,JID,TNum,TDate,TStatus) "
                "values (%1,%2,%3,%4,'%5','%6')")
                .arg(FSID)
                .arg(TSID)
                .arg(JID)
                .arg(MNum)
                .arg(MDate)
                .arg(QChar('2')));
        if (lackOK && transferOK) {
            query.exec("commit");
            QMessageBox::information(nullptr, QStringLiteral("完成"),
                                     QStringLiteral("调货申请发送成功!"),
                                     QMessageBox::Ok, QMessageBox::Ok);
        } else {
            query.exec("rollback");
            QMessageBox::warning(nullptr, QStringLiteral("警告"),
                                 QStringLiteral("出现错误，已回滚"),
                                 QMessageBox::Ok, QMessageBox::Ok);
        }
        //结束事务
    }
    show_tab4();
}

// tab6切换页面
void MainWindow::on_tab6_currentChanged(int index) {
    switch (index) {
        case 0:
            //发出的申请
            show_tab6_tab1();
            break;
        case 1:
            //收到的申请
            show_tab6_tab2();
            break;
        default:
            break;
    }
}

//发出的申请页面
void MainWindow::show_tab6_tab1() {
    qDebug() << QStringLiteral("切换到tab6_tab1");
    //刷新table
    ui->table6_1->clear();
    ui->table6_1->setRowCount(0);
    //进行查询
    QSqlQuery query;      //查询
    QSqlQuery queryRepo;  //查询库存
    QString sqlStr;
    sqlStr = QString("select * from TransferDetail ");
    sqlStr.append(
        QString("where FSID=%1").arg(login::loggedEmp.SID));  //发出申请的为本店
    query.exec(sqlStr);

    //设置表格
    ui->table6_1->setColumnCount(14);
    QStringList headers;  //表头
    headers << QStringLiteral("调货编号") << QStringLiteral("货号")
            << QStringLiteral("品名") << QStringLiteral("单价")
            << QStringLiteral("申请店号") << QStringLiteral("申请店名")
            << QStringLiteral("申请店所在地") << QStringLiteral("被申请店号")
            << QStringLiteral("被申请店名") << QStringLiteral("被申请店所在地")
            << QStringLiteral("申请数目") << QStringLiteral("申请时间")
            << QStringLiteral("状态") << QStringLiteral("操作");
    ui->table6_1->setHorizontalHeaderLabels(headers);
    ui->table6_1->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);  //填满
    ui->table6_1->setEditTriggers(
        QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table6_1->horizontalHeader()->setStretchLastSection(true); //填满

    //填写表格
    int nRow, nCol;
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table6_1->setRowCount(nRow);
    nCol = ui->table6_1->columnCount();
    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol - 1; j++) {
            //倒数第三列为时间
            if (j == nCol - 3) {
                ui->table6_1->setItem(
                    i, j,
                    new QTableWidgetItem(query.value(j).toDateTime().toString(
                        "yyyy-MM-dd hh:mm:ss")));
            }
            //倒数第二列添加状态
            else if (j == nCol - 2) {
                QString statusStr;
                int statusInt = query.value(j).toInt();
                if (statusInt == 0) {
                    statusStr = QStringLiteral("同意");
                } else if (statusInt == 1) {
                    statusStr = QStringLiteral("拒绝");
                } else {
                    statusStr = QStringLiteral("等待");
                }
                ui->table6_1->setItem(i, nCol - 2,
                                      new QTableWidgetItem(statusStr));
            }
            //其余列正常
            else {
                ui->table6_1->setItem(
                    i, j, new QTableWidgetItem(query.value(j).toString()));
            }
            ui->table6_1->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                       Qt::AlignVCenter);
        }
        //最后一列添加按钮
        QPushButton *pBtn = new QPushButton();
        //分情况讨论按钮状态和行为
        QString btnTextStr;
        int statusInt = query.value(nCol - 2).toInt();
        if (statusInt == 0) {
            btnTextStr = QStringLiteral("确认");
            connect(pBtn, SIGNAL(clicked()), this, SLOT(on_btn_6_1_ok()));
        } else if (statusInt == 1) {
            btnTextStr = QStringLiteral("删除");
            connect(pBtn, SIGNAL(clicked()), this, SLOT(on_btn_6_1_delete()));
        } else {
            btnTextStr = QStringLiteral("取消");
            connect(pBtn, SIGNAL(clicked()), this, SLOT(on_btn_6_1_cancel()));
        }
        pBtn->setText(btnTextStr);
        ui->table6_1->setCellWidget(i, nCol - 1, pBtn);
        //下一条query结果
        query.next();
    }
}

//收到的申请页面
void MainWindow::show_tab6_tab2() {
    qDebug() << QStringLiteral("切换到tab6_tab2");
    //仅店主可访问
    if (login::loggedEmp.EType != 1) {
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("仅店主可访问此页面"),
                             QMessageBox::Ok, QMessageBox::Ok);
        ui->tabWidget->setCurrentIndex(1);
        return;
    }
    //刷新table
    ui->table6_2->clear();
    ui->table6_2->setRowCount(0);
    //进行查询
    QSqlQuery query;      //查询
    QSqlQuery queryRepo;  //查询库存
    QString sqlStr;
    sqlStr = QString(
        "select "
        "TID,JID,JName,Price,FSID,FSName,FCityName,TSID,TSName,TCityName,TNum,"
        "TDate ");
    sqlStr.append("from TransferDetail ");
    sqlStr.append(QString("where TSID=%1 ")
                      .arg(login::loggedEmp.SID));  //收到申请的为本店
    sqlStr.append(QString("and TStatus='%1'").arg('2'));  //处于等待状态
    qDebug() << sqlStr;
    query.exec(sqlStr);

    //设置表格
    ui->table6_2->setColumnCount(13);
    QStringList headers;  //表头
    headers << QStringLiteral("调货编号") << QStringLiteral("货号")
            << QStringLiteral("品名") << QStringLiteral("单价")
            << QStringLiteral("申请店号") << QStringLiteral("申请店名")
            << QStringLiteral("申请店所在地") << QStringLiteral("被申请店号")
            << QStringLiteral("被申请店名") << QStringLiteral("被申请店所在地")
            << QStringLiteral("申请数目") << QStringLiteral("申请时间")
            << QStringLiteral("操作");
    ui->table6_2->setHorizontalHeaderLabels(headers);
    ui->table6_2->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);  //填满
    ui->table6_2->setEditTriggers(
        QAbstractItemView::NoEditTriggers);  //不可编辑
    //    ui->table6_2->horizontalHeader()->setStretchLastSection(true); //填满

    //填写表格
    int nRow, nCol;
    query.last();
    nRow = query.at() + 1;
    query.first();
    qDebug() << "nRow:" << nRow;
    ui->table6_2->setRowCount(nRow);
    nCol = ui->table6_2->columnCount();
    for (int i = 0; i < nRow; i++) {
//        qDebug() << query.value(0).toInt();
        for (int j = 0; j < nCol - 1; j++) {
//            qDebug() << j << " " << query.value(j).toString();
            //倒数第二列为时间
            if (j == nCol - 2) {
                ui->table6_2->setItem(
                    i, j,
                    new QTableWidgetItem(query.value(j).toDateTime().toString(
                        "yyyy-MM-dd hh:mm:ss")));
            }
            //其余列正常
            else {
                ui->table6_2->setItem(
                    i, j, new QTableWidgetItem(query.value(j).toString()));
            }
            ui->table6_2->item(i, j)->setTextAlignment(Qt::AlignHCenter |
                                                       Qt::AlignVCenter);
        }
        //最后一列添加按钮
        QPushButton *pBtn1 = new QPushButton(QStringLiteral("允许"));
        QPushButton *pBtn2 = new QPushButton(QStringLiteral("拒绝"));
        connect(pBtn1, SIGNAL(clicked()), this, SLOT(on_btn_6_2_accept()));
        connect(pBtn2, SIGNAL(clicked()), this, SLOT(on_btn_6_2_reject()));
        //新建垂直布局，将按钮加进布局
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(pBtn1);
        layout->addWidget(pBtn2);
        layout->alignment();
        QWidget *widget = new QWidget();
        widget->setMinimumHeight(40);
        widget->setLayout(layout);
        ui->table6_2->setCellWidget(i, nCol - 1, widget);
        //下一条query结果
        query.next();
    }
}

//申请被允许
void MainWindow::on_btn_6_1_ok() {
    qDebug() << "on_btn_6_1_ok";
    QPushButton *sendBtn = qobject_cast<QPushButton *>(sender());
    if (sendBtn == nullptr) return;
    QModelIndex index = ui->table6_1->indexAt(
        QPoint(sendBtn->frameGeometry().x(), sendBtn->frameGeometry().y()));
    int row = index.row();
    qDebug() << "row:" << row;
    int TID = ui->table6_1->item(row, 0)->text().toInt();
    int JID = ui->table6_1->item(row, 1)->text().toInt();
    int TNum = ui->table6_1->item(row, 10)->text().toInt();
    int SID = login::loggedEmp.SID;
    QSqlQuery query;
    //开始事务
    query.exec("begin transaction");
    bool ok1 =
        query.exec(QString("select * from qbb.Repo where JID=%1 and SID=%2")
                       .arg(JID)
                       .arg(SID));
    //本店有库存
    QString msg;
    bool ok2;
    if (query.first()) {
        qDebug()<<"Has Repo";
        ok2 = query.exec(
            QString("update qbb.Repo set RNum=RNum+%1 where JID=%2 and SID=%3")
                .arg(TNum)
                .arg(JID)
                .arg(SID));
        msg = QStringLiteral("调货成功！店内有库存，直接更新库存数目");
    }
    //本店无库存
    else {
        qDebug()<<"No Repo";
        ok2 = query.exec(QString("insert into qbb.Repo values (%1,%2,%3)")
                             .arg(SID)
                             .arg(JID)
                             .arg(TNum));
        msg = QStringLiteral("调货成功！店内无库存，插入新库存项");
    }

    //删除调货记录
    bool ok3 =
        query.exec(QString("delete from qbb.Transfer where TID=%1").arg(TID));
    if (ok1 && ok2 && ok3) {
        query.exec("commit");
        QMessageBox::information(nullptr, QStringLiteral("完成"), msg,
                                 QMessageBox::Ok, QMessageBox::Ok);
    } else {
        query.exec("rollback");
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("出现错误，已回滚"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    //结束事务
    //刷新页面
    show_tab6_tab1();
}

//申请被拒绝
void MainWindow::on_btn_6_1_delete() {
    qDebug() << "on_btn_6_1_delete";
    QPushButton *sendBtn = qobject_cast<QPushButton *>(sender());
    if (sendBtn == nullptr) return;
    QModelIndex index = ui->table6_1->indexAt(
        QPoint(sendBtn->frameGeometry().x(), sendBtn->frameGeometry().y()));
    int row = index.row();
    qDebug() << "row:" << row;
    int TID = ui->table6_1->item(row, 0)->text().toInt();
    QSqlQuery queryTransfer;
    //删除调货记录
    queryTransfer.exec(
        QString("delete from qbb.Transfer where TID=%1").arg(TID));
    //刷新页面
    show_tab6_tab1();
}

//申请在等待中
void MainWindow::on_btn_6_1_cancel() {
    qDebug() << "on_btn_6_1_cancel";
    QPushButton *sendBtn = qobject_cast<QPushButton *>(sender());
    if (sendBtn == nullptr) return;
    QModelIndex index = ui->table6_1->indexAt(
        QPoint(sendBtn->frameGeometry().x(), sendBtn->frameGeometry().y()));
    int row = index.row();
    qDebug() << "row:" << row;
    int TID = ui->table6_1->item(row, 0)->text().toInt();
    QSqlQuery queryTransfer;
    //删除调货记录
    queryTransfer.exec(
        QString("delete from qbb.Transfer where TID=%1").arg(TID));
    //刷新页面
    show_tab6_tab1();
}

//允许申请
void MainWindow::on_btn_6_2_accept() {
    qDebug() << "on_btn_6_2_accept";
    QPushButton *sendBtn = qobject_cast<QPushButton *>(sender());
    if (sendBtn == nullptr) return;
    QModelIndex index = ui->table6_2->indexAt(
        QPoint(sendBtn->frameGeometry().x(), sendBtn->frameGeometry().y()));
    int row = index.row();
    qDebug() << "row:" << row;
    int TID = ui->table6_2->item(row, 0)->text().toInt();
    int JID = ui->table6_2->item(row, 1)->text().toInt();
    int TNum = ui->table6_2->item(row, 10)->text().toInt();
    int SID = login::loggedEmp.SID;
    QSqlQuery queryRepo;
    queryRepo.exec(QString("select RNum from qbb.Repo where JID=%1 and SID=%2")
                       .arg(JID)
                       .arg(SID));
    qDebug() << QString("select RNum from qbb.Repo where JID=%1 and SID=%2")
                    .arg(JID)
                    .arg(SID);
    if (queryRepo.first() && queryRepo.value(0).toInt() >= TNum) {
        //允许调货，减少本店库存
        if (queryRepo.exec(
                QString(
                    "update qbb.Repo set RNum=RNum-%1 where JID=%2 and SID=%3")
                    .arg(TNum)
                    .arg(JID)
                    .arg(SID)))
            QMessageBox::information(nullptr, QStringLiteral("完成"),
                                     QStringLiteral("已减少本店库存"),
                                     QMessageBox::Ok, QMessageBox::Ok);
        else
            qDebug() << QString(
                            "update qbb.Repo set RNum=RNum-%1 where JID=%2 and "
                            "SID=%3")
                            .arg(TNum)
                            .arg(JID)
                            .arg(SID);
        QSqlQuery queryTransfer;
        //修改调货记录状态
        queryTransfer.exec(
            QString("update qbb.Transfer set TStatus='0' where TID=%1")
                .arg(TID));
    } else {
        //本店库存不足，不允许调货
        QMessageBox::warning(nullptr, QStringLiteral("警告"),
                             QStringLiteral("本店库存不足，不允许调货"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
    //刷新页面
    show_tab6_tab2();
}

//拒绝申请
void MainWindow::on_btn_6_2_reject() {
    qDebug() << "on_btn_6_2_reject";
    QPushButton *sendBtn = qobject_cast<QPushButton *>(sender());
    if (sendBtn == nullptr) return;
    QModelIndex index = ui->table6_2->indexAt(
        QPoint(sendBtn->frameGeometry().x(), sendBtn->frameGeometry().y()));
    int row = index.row();
    qDebug() << "row:" << row;
    int TID = ui->table6_2->item(row, 0)->text().toInt();
    QSqlQuery queryTransfer;
    //修改调货记录状态
    queryTransfer.exec(
        QString("update qbb.Transfer set TStatus='1' where TID=%1").arg(TID));
    //弹窗提示
    QMessageBox::information(nullptr, QStringLiteral("完成"),
                             QStringLiteral("已拒绝对方的调货申请"),
                             QMessageBox::Ok, QMessageBox::Ok);
    //刷新页面
    show_tab6_tab2();
}

//增加员工
void MainWindow::on_addEmp_clicked() {
    int rowNum = model->rowCount();
    qDebug() << "rowNum:" << rowNum;
    int maxEID = model->record(rowNum - 1).value(0).toInt();
    qDebug() << "maxEID:" << maxEID;
    model->insertRow(rowNum);
    model->setData(model->index(rowNum, 0), maxEID + 1);
    model->setData(model->index(rowNum, 1), login::loggedEmp.SID);
}

//删除员工
void MainWindow::on_deleteEmp_clicked() {
    int rowIndex = ui->tableView->currentIndex().row();
    //店长不能删除自己
    if (model->record(rowIndex).value(2).toInt() == 1) {
        QMessageBox::warning(this, QStringLiteral("警告"),
                             QStringLiteral("店长不能删除自己"),
                             QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    qDebug() << "rowIndex:" << rowIndex;
    if (rowIndex >= 0) {
        model->removeRow(rowIndex);
        int ok = QMessageBox::warning(this, QStringLiteral("警告"),
                                      QStringLiteral("确定开除该员工？"),
                                      QMessageBox::Yes, QMessageBox::No);
        if (ok == QMessageBox::No)
            model->revertAll();  //如果不删除，则撤销
        else
            model->submitAll();  //否则提交，在数据库中删除该行
    }
}
