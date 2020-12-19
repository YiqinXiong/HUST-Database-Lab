CREATE TRIGGER MyTrigger1
ON DiagnoseRecord
AFTER INSERT AS
IF( SELECT COUNT(*) 
    FROM inserted,TakeTrainRecord tr,TrainPass tp
    WHERE tr.PCardID = inserted.PCardID
    AND tr.TID = tp.TID
    AND tr.SStationID = tp.SID
    AND inserted.DStatus = 1
    AND SStatus = 1
    AND DATEDIFF(DD,tp.STime,FDay) <= 14 ) > 0
BEGIN
PRINT '插入一个新冠患者，同排及前后排加入乘客紧密接触者表'
INSERT INTO TrainContactor
SELECT SDate CDate,tr.PCardID CCardID,'3' DStatus,TEMP.PCardID PCardID
FROM TakeTrainRecord tr,Train t,
    (SELECT tr1.TID,CarrigeID,SeatRow,inserted.PCardID
    FROM inserted,TakeTrainRecord tr1,TrainPass tp1
    WHERE tr1.PCardID = inserted.PCardID
    AND tr1.TID = tp1.TID
    AND tr1.SStationID = tp1.SID
    AND SStatus = 1
    AND DATEDIFF(DD,tp1.STime,FDay) <= 14 ) TEMP
WHERE tr.TID = t.TID
AND tr.TID = TEMP.TID
AND tr.PCardID <> TEMP.PCardID
AND SStatus = 1
AND tr.CarrigeID = TEMP.CarrigeID
AND ABS(tr.SeatRow-TEMP.SeatRow) <= 1
END

-- DROP TRIGGER MyTrigger1