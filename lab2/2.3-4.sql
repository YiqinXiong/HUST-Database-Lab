SELECT TID,TName FROM Train,Station
WHERE Train.SStationID = Station.SID
AND CityName = '武汉'
AND SDate = '2020-01-22'
