SELECT RID,PCardID,TID,SStationID,ASTationID,CarrigeID,SeatRow,SeatNo,SStatus
INTO WH_TakeTrainRecord
FROM TakeTrainRecord tr,Station s
WHERE tr.SStationID = s.SID
AND CityName = '武汉'