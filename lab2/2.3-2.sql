SELECT DISTINCT b.CityName FROM TakeTrainRecord,Station a,Station b
WHERE SStationID = a.SID
AND AStationID = b.SID
AND a.CityName = '武汉'