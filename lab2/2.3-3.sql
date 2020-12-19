SELECT DATEDIFF(dd,FDay,DDay) IntervalDays,Passenger.PCardID,PName,Sex,Age
FROM DiagnoseRecord,Passenger
WHERE DiagnoseRecord.PCardID = Passenger.PCardID
AND DStatus = 1
ORDER BY IntervalDays DESC