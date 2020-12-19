USE master
GO
CREATE DATABASE Epidemic_Train
GO
USE Epidemic_Train
GO
--车站表【车站编号，车站名，所属城市】--
CREATE TABLE Station(
    SID INT PRIMARY KEY,    --车站编号
    SName CHAR(20),         --车站名
    CityName CHAR(30)       --所属城市
)
--车次表【列车编号，发车日期，列车名称，起点站编号，终点站编号，开出时刻，终点时刻】--
CREATE TABLE Train(
    TID INT PRIMARY KEY,            --列车编号
    SDate DATE,                     --发车日期
    TName CHAR(20) NOT NULL,        --列车名称
    SStationID INT,                 --起点站编号
    AStationID INT,                 --终点站编号
    STime DATETIME,                 --开出时刻
    ATime DATETIME,                 --终点时刻
    FOREIGN KEY (SStationID) REFERENCES Station(SID),
    FOREIGN KEY (AStationID) REFERENCES Station(SID)
)
--车程表【列车编号，车站序号，车站编号，到达时刻，离开时刻】--
CREATE TABLE TrainPass(
    TID INT,                --列车编号
    SNo SMALLINT,           --车站序号
    SID INT,                --车站编号
    STime DATETIME,         --到达时刻
    ATime DATETIME,         --离开时刻
    PRIMARY KEY (TID, SNo),
    FOREIGN KEY (SID) REFERENCES Station(SID)
)
--乘客表【乘客身份证号，姓名，性别，年龄】--
CREATE TABLE Passenger(
    PCardID CHAR(18) PRIMARY KEY,   --乘客身份证号
    PName char(20),                 --姓名
    Sex bit,                        --性别(1男0女)
    Age SMALLINT                    --年龄
)
--乘车记录表【记录编号，乘客身份证号，列车编号，出发站编号，到达站编号，车厢号，席位排号，席位编号，席位状态】--
CREATE TABLE TakeTrainRecord(
    RID INT,            --记录编号
    PCardID CHAR(18),   --乘客身份证号
    TID INT,            --列车编号
    SStationID INT,     --出发站编号
    AStationID INT,     --到达站编号
    CarrigeID SMALLINT, --车厢号 (比如2车16F中的2，NULL表示无座)
    SeatRow SMALLINT,   --席位排号 (比如2车16F中的16)
    SeatNo CHAR(1),     --席位编号 (比如2车16F中的F，A\B\C\E\F或NULL)
    SStatus INT         --席位状态 (0--退票，1--正常，2--乘客没上车)
    PRIMARY KEY (RID),
    FOREIGN KEY (PCardID) REFERENCES Passenger(PCardID),
    FOREIGN KEY (TID) REFERENCES Train(TID),
    FOREIGN KEY (SStationID) REFERENCES Station(SID),
    FOREIGN KEY (AStationID) REFERENCES Station(SID)
)
--诊断表【诊断编号，病人身份证号，诊断日期，诊断结果，发病日期】--
CREATE TABLE DiagnoseRecord(
    DID INT PRIMARY KEY,    --诊断编号
    PCardID CHAR(18),       --病人身份证号
    DDay DATE,              --诊断日期
    DStatus SMALLINT,       --诊断结果 (1--确诊，2--疑似，3--排除新冠)
    FDay DATE,              --发病日期
)
--乘客紧密接触者表【接触日期, 被接触者身份证号，接触者状态，病患身份证号】--
CREATE TABLE TrainContactor(
    CDate DATE,         --接触日期
    CCardID CHAR(18),   --被接触者身份证号
    DStatus SMALLINT,   --接触者状态 (1--确诊，2--疑似，3--排除新冠)
    PCardID CHAR(18)    --接触的病患的身份证号
    PRIMARY KEY (CDate, CCardID, DStatus, PCardID),
    FOREIGN KEY (PCardID) REFERENCES Passenger(PCardID),
    FOREIGN KEY (CCardID) REFERENCES Passenger(PCardID)
)
GO