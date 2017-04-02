-- Question: 1
-- Approach: This joins in the course information to get the course name
--     it then joins the schedule information matching on cno, term, and
--      section to prevent duplication
--      finally the query is filtered for rows where the term and room are
--      appropriate values
--      select choses the correct columns to print
select course.cname, course.cno, professor.pname from class
    inner join course
    on class.cno = course.cno
    inner join schedule
    on class.cno = schedule.cno and class.term = schedule.term
        and class.section = schedule.section
    inner join professor
    on class.instructor = professor.eid
    where class.term="F10" AND schedule.room="RCH122"
    ;
1
-- Results:
/*
CNAME                                                CNO         PNAME
---------------------------------------------------  ----------  ----------
Elementary Algorithm Design and Data Abstraction...  CS146       HOLLIS
Computer Architecture                                CS450       BARBARA
Computer Security and Privacy                        CS458       HOLLIS
Advanced Biochemistry                                PHYS442     LILIA
Research Project                                     PHYS451     DEBORA
*/
