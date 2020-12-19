SELECT DISTINCT TName, CityName
FROM Train, Station
WHERE Train.AStationID = Station.SID
    AND CityName IN ('北京','上海','广州')
    