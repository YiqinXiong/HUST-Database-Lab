SELECT Patients.PCardID, PName, TName, SDate
FROM (
    SELECT dr.PCardID, PName
    FROM DiagnoseRecord dr, Passenger p
    WHERE dr.PCardID = p.PCardID
        AND DStatus = 1 ) Patients
    LEFT JOIN (
        SELECT tr.PCardID, TName, SDate
    FROM TakeTrainRecord tr, Train t
    WHERE tr.TID = t.TID
        AND SStatus = 1
        AND CONVERT(CHAR(4),SDate,20) = '2020' ) TrainRecords
    ON Patients.PCardID = TrainRecords.PCardID
