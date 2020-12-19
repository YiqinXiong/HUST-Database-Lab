CREATE TRIGGER MyTrigger2
ON DiagnoseRecord
AFTER INSERT
AS
IF(
    SELECT COUNT(*) 
    FROM inserted,TrainContactor tc
    WHERE inserted.PCardID = tc.CCardID
    AND inserted.DStatus = 1
    ) > 0
BEGIN
PRINT '在乘客紧密接触者表中修改其状态为1，确诊'
UPDATE TrainContactor
SET DStatus = 1
WHERE CCardID IN (SELECT PCardID FROM inserted)
END

