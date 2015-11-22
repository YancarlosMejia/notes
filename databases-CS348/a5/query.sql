SELECT
    class.cno,
    course.cname,
    SUM(enrollmentData.students),
    COUNT(class.section),
    SUM(enrollmentData.total)/SUM(enrollmentData.students),
    MAX(enrollmentData.average),
    MIN(enrollmentData.average)
FROM class
INNER JOIN professor
ON class.instructor = professor.eid AND professor.dept = ?
INNER JOIN course
ON class.cno = course.cno
INNER JOIN (
    SELECT
        enrollment.cno,
        enrollment.term,
        enrollment.section,
        AVG(enrollment.mark) as average,
        SUM(enrollment.mark) as total,
        COUNT(enrollment.mark) as students from enrollment
    GROUP BY
        enrollment.cno,
        enrollment.term,
        enrollment.section) AS enrollmentData
ON class.cno = enrollmentData.cno AND class.term = enrollmentData.term AND class.section = enrollmentData.section
WHERE ? <= SUBSTR(class.term, 2) AND ? >= SUBSTR(class.term, 2)
GROUP BY
    class.cno,
    class.term,
    SUBSTR(class.term, 2)
ORDER BY
    SUBSTR(class.term, 2),
    class.cno
