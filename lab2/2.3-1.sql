SELECT RID,tr.PCardID,tr.TID,SStationID,AStationID,CarrigeID,SeatRow,SeatNo,SStatus
FROM TakeTrainRecord tr,TrainPass tp,DiagnoseRecord dr,Passenger p
WHERE tr.TID = tp.TID
AND tr.SStationID = tp.SID
AND dr.PCardID = p.PCardID
AND dr.PCardID = tr.PCardID
AND SStatus = 1
AND PName = '张三'
AND DStatus = 1
AND DATEDIFF(DD,tp.STime,FDay) <= 14
AND DATEDIFF(DD,tp.STime,FDay) >= 0
