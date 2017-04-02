
-- Question: 6
-- Approach: Join the class and enrollment tables to calculate the class count
--      and average, then join in the professor table and group by the
--      professor's id to filter out any professor whose minimum number of
--      students taught is not at least 10. This allows us to return
--      the correct data.

select professor.eid, classdata.cno, classdata.term, classdata.section,
 classdata.AVG
from professor
    inner join (select class.cno, class.term, class.instructor, class.section,
        COUNT(enrollment.sno) as CNT, ROUND(AVG(enrollment.mark), 2) as AVG from
        enrollment
        inner join class
        on class.cno = enrollment.cno

        group by class.cno, class.term) as classdata
    on professor.eid = classdata.instructor

    group by professor.eid
    having MIN(CNT) >= 10
    ;

/*
-- Results:
EID         cno         term        section     AVG
----------  ----------  ----------  ----------  ----------
0           MATH492     F99         2           75.95
2           PHYS243     F01         3           78.85
4           MATH492     F01         1           75.95
5           MATH479     F99         2           76.62
6           CS447       F99         3           78.53
7           PHYS457     S01         3           82.03
8           CS490       W12         2           78.83
9           PHYS488     S09         2           81.72
10          PHYS442     W11         3           79.99
11          PHYS497     W09         2           81.46
12          CS490       W04         3           78.83
13          CS448       W09         2           81.47
14          MATH492     S00         2           75.95
15          PHYS452     F04         3           80.67
16          CS448       W08         3           81.47
17          CS490       W06         2           78.83
18          MATH492     W08         2           75.95
19          MATH486     F01         2           79.27
20          CS448       W10         1           81.47
21          CS488       F09         3           81.11
23          CS490       W09         3           78.83
24          CS445       F99         2           77.41
28          PHYS497     W11         1           81.46
29          PHYS497     S00         2           81.46
32          PHYS497     S12         2           81.46
33          PHYS497     W05         3           81.46
37          PHYS497     F02         2           81.46
38          PHYS497     S05         3           81.46
39          PHYS497     W12         3           81.46
40          CS490       W11         3           78.83
41          PHYS497     W04         3           81.46
46          PHYS497     W07         1           81.46
48          PHYS485     W03         2           82.03

*/
