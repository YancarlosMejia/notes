-- Question: 3
-- Approach: This works by joining in the professor table into the class table
--       for all professors in the cs department
--   then the prerequisite table is joined to find the prereqs for a class
--   then the class and professor tables are joined in again to get information
--      for the prerequisite classes such that the prerequisite happened at the
--      same time and is taught by a professor not in the cs department
--   then the table is grouped by relevant information to filter out
--      duplications and is sorted
--   finally the last where function filters for the correct term and the select
--      renames columns to the required values


select professor.pname, professor.dept, class.cno, class.term, class.section,
ROUND(AVG(enrollment.mark),2) as AVG from class
    inner join enrollment
    on class.cno = enrollment.cno and class.term = enrollment.term
    inner join professor
    on class.instructor = professor.eid

    group by class.cno, class.term, class.section
    having AVG(enrollment.mark) > 85 and COUNT(enrollment.cno) > 10

    order by professor.pname, professor.dept, class.cno
    ;
/*
-- Results:
PNAME       DEPT              CNO         TERM        SECTION     AVG
----------  ----------------  ----------  ----------  ----------  ----------
ANN         Computer Science  CS213       F11         2           85.92
BARBARA     Computer Science  CS137       S02         3           85.25
BARBARA     Computer Science  CS213       W13         1           85.46
BARBARA     Computer Science  CS213       W13         3           85.46
BETH        Physics           PHYS457     F01         2           86.64
BETH        Physics           PHYS458     S07         1           85.92
CODY        Computer Science  CS462       S06         2           87.58
DEBORA      Physics           PHYS451     F10         1           86.83
DEBORA      Physics           PHYS478     F01         3           85.31
DUSTIN      Physics           PHYS214     W12         2           86.18
DUSTIN      Physics           PHYS271     W13         3           85.17
DUSTIN      Physics           PHYS312     W12         2           85.46
DUSTIN      Physics           PHYS477     W11         3           86.0
HERMINIA    Physics           PHYS229     S06         2           86.27
HERMINIA    Physics           PHYS312     W12         1           85.46
HOLLIS      Computer Science  CS462       S06         3           87.58
JACKLYN     Physics           PHYS147     W07         2           86.09
JERALD      Computer Science  CS137       S02         1           85.25
JERALD      Computer Science  CS138       F10         2           85.08
JESSICA     Mathematics       MATH226     F12         1           85.55
LILIA       Physics           PHYS189     F11         2           86.92
LINA        Computer Science  CS350       S03         1           85.42
MORRIS      Physics           PHYS271     W13         1           85.17
MORRIS      Physics           PHYS458     S07         3           85.92
PETER       Mathematics       MATH358     W00         1           86.25
PETER       Mathematics       MATH452     F08         3           86.73
RODRIGO     Computer Science  CS135       S11         2           86.0
RODRIGO     Computer Science  CS350       S03         2           85.42
STUART      Physics           PHYS289     F09         2           85.5
ULYSSES     Physics           PHYS229     S06         3           86.27
ULYSSES     Physics           PHYS312     F11         1           85.08
ULYSSES     Physics           PHYS331     S05         1           86.73
ULYSSES     Physics           PHYS478     F01         2           85.31

*/
