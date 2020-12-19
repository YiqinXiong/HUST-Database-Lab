SELECT TrainPass.TID,TName FROM TrainPass,Train,Station
WHERE TrainPass.SID = Station.SID
AND TrainPass.TID = Train.TID
AND CityName = '武汉'
AND (CONVERT(DATE,TrainPass.STime) = '2020-01-22'
    OR CONVERT(DATE,TrainPass.ATime) = '2020-01-22')
    