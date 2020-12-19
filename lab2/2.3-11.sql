SELECT TName, SDate, CarrigeID
FROM TakeTrainRecord tr, DiagnoseRecord dr, Train t
WHERE tr.PCardID = dr.PCardID
    AND tr.TID = t.TID
    AND DStatus = 1
    AND SStatus = 1
    AND CarrigeID IS NOT NULL
GROUP BY tr.TID,TName,SDate,CarrigeID
HAVING COUNT(RID) >= 3
