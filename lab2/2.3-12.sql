SELECT tc.PCardID, PName, CDate
FROM TrainContactor tc, Passenger p
WHERE tc.PCardID = p.PCardID
    AND tc.PCardID NOT IN (
    SELECT PCardID
    FROM TrainContactor
    WHERE tc.DStatus <> 3)
