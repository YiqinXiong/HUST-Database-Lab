SELECT DISTINCT tr.PCardID,PName,Sex,Age
FROM TakeTrainRecord tr,TrainPass tp,Passenger p,Station s
WHERE tr.TID = tp.TID
AND tr.AStationID = tp.SID
AND tr.AStationID = s.SID
AND tr.PCardID = p.PCardID
AND SStatus = 1
AND CityName = '武汉'
AND DATEPART(YYYY,tp.ATime) = '2020'
AND DATEPART(MM,tp.ATime) = '01'
