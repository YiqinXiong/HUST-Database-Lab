CREATE VIEW XG_TakeTrain AS
SELECT TOP 100 PERCENT dr.PCardID,PName,Age,tr.TID,SDate,CarrigeID,SeatRow,SeatNo
FROM DiagnoseRecord dr,Passenger p,TakeTrainRecord tr,Train t
WHERE dr.DStatus = 1
AND dr.PCardID = p.PCardID
AND dr.PCardID = tr.PCardID
AND tr.TID = t.TID
AND SStatus = 1
ORDER BY dr.PCardID,SDate DESC

