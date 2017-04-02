-- Question: 2
-- Approach: This works by joining in the professor table into the class table
--      for all professors in the cs department
--   then the prerequisite table is joined to find the prereqs for a class
--   then the class and professor tables are joined in again to get information
--      for the prerequisite classes such that the prerequisite happened at the
--      same time and is taught by a professor not in the cs department
--   then the table is grouped by relevant information to filter out
--      duplications and is sorted
--   finally the last where function filters for the correct term and the select
--      renames columns to the required values

select class.cno as CNO, professor.pname as CSNAME,
 prereqclass.cno as PrerequisiteCNO, prereqprof.pname as NonCSNAME  from class
    inner join professor
    on class.instructor = professor.eid and professor.dept = "Computer Science"
    inner join prerequisite
    on class.cno = prerequisite.cno
    inner join class prereqclass
    on prereqclass.cno = prerequisite.prereq and prereqclass.term = "S03"
    inner join professor prereqprof
    on prereqclass.instructor = prereqprof.eid
        and prereqprof.dept != "Computer Science"

    where class.term = "S03"
    group by class.cno, professor.pname, prereqclass.cno, prereqprof.pname
    order by class.cno, professor.pname, prereqclass.cno, prereqprof.pname
    ;
/*
-- Results:
CNO         CSNAME      PrerequisiteCNO  NonCSNAME
----------  ----------  ---------------  ----------
CS214       JERALD      PHYS171          DUSTIN
CS348       RODRIGO     MATH217          JESSICA
CS436       RODRIGO     MATH381          PETER
CS446       LINA        PHYS171          DUSTIN
*/
