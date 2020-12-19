SELECT PCardID,sb.CityName,CONVERT(DATE,tpb.ATime) ArriveDate
FROM TakeTrainRecord tr,TrainPass tpa,TrainPass tpb,Station sa,Station sb
WHERE tr.TID = tpa.TID
AND tr.SStationID = tpa.SID
AND tr.TID = tpb.TID
AND tr.AStationID = tpb.SID
AND tr.SStationID = sa.SID
AND tr.AStationID = sb.SID
AND SStatus = 1
AND sa.CityName = '武汉'
AND CONVERT(DATE,tpa.STime) = '2020-01-22'
