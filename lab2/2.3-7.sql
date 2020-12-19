SELECT sb.CityName,COUNT(PCardID) Num
FROM TakeTrainRecord tr,TrainPass tp,Station sa,Station sb
WHERE tr.TID = tp.TID
AND tr.SStationID = tp.SID
AND tr.SStationID = sa.SID
AND tr.AStationID = sb.SID
AND SStatus = 1
AND sa.CityName = '武汉'
AND CONVERT(DATE,tp.STime) = '2020-01-22'
GROUP BY sb.CityName
