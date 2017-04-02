-- Question: 5
-- Approach join the enrollment table with the student table based on the
--      student number inorder to get the student name for printing
--      group by the student number to get all classes attended by that student
--      to calculate and filter on the number of classes and minimum mark
-- Assumptions: the student minimum enrollment constraint is not term based
--      (this query checks over all time)

select student.sname, ROUND(AVG(enrollment.mark), 2) as AVG from enrollment
    inner join student
    on enrollment.sno = student.sno

    group by student.sno
    having COUNT(enrollment.sno) >= 5 AND MIN(enrollment.mark) >= 80

    order by student.sname, ROUND(AVG(enrollment.sno),2)
    ;
/*
-- Results:
SNAME        AVG
-----------  ----------
ANITA, STEVE  84.0
CHRISTIAN, R  86.0
KAREN, BENJA  87.4
SETH, GERMAI  82.33
SUSIE, VIRGI  84.0
*/
