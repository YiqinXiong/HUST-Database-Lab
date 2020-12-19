SELECT tr.PCardID, TEMP.TID
FROM TakeTrainRecord tr, TrainPass tp,
    -- (SELECT PCardID,tr1.TID,STime,tr1.AStationID
    (SELECT PCardID, tr1.TID, tr1.AStationID
    FROM TakeTrainRecord tr1, TrainPass tp1, Station s1
    WHERE tr1.TID = tp1.TID
        AND tr1.SStationID = tp1.SID
        AND tr1.SStationID = s1.SID
        AND SStatus = 1
        AND SName = '武汉'
        AND CONVERT(DATE,STime) = '2020-01-22' ) TEMP
WHERE tr.PCardID = TEMP.PCardID
    AND tr.SStationID = tp.SID
    AND tr.TID = tp.TID
    AND TEMP.AStationID = tr.SStationID         --接续换乘
    AND CONVERT(DATE,tp.STime) = '2020-01-22'   --同一天
    -- AND tp.STime > TEMP.STime                --换乘时间在后
    AND SStatus = 1
ORDER BY TEMP.TID DESC,tr.PCardID
