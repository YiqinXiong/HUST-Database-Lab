SELECT DISTINCT tr.PCardID,PName,Sex,Age
FROM TakeTrainRecord tr,TrainPass tp,Passenger p,Station s
WHERE tp.SID = s.SID
AND tp.TID = tr.TID
AND tr.PCardID = p.PCardID
AND SStatus = 1
AND CityName = '武汉'
AND ((DATEPART(YYYY,tp.ATime) = '2020' AND DATEPART(MM,tp.ATime) = '01')
    OR (DATEPART(YYYY,tp.STime) = '2020' AND DATEPART(MM,tp.STime) = '01'))
AND tr.PCardID NOT LIKE '420%'