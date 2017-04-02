//javac -cp "*:" CourseInfo
import java.util.Properties;
import java.util.Scanner;
import java.sql.*;

public class CourseInfo {
    public static void main(String[] args){
        Connection con = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;
        try{
            Class.forName("com.ibm.db2.jcc.DB2Driver");
            Properties props = new Properties() {
                {
                    put("currentSchema", "ENROLLMENT");
                    put("user", "db2guest");
                    put("password", "upKellynoisylair");
                }
            };

            con = DriverManager.getConnection("jdbc:db2://linux.student.cs.uwaterloo.ca:50002/cs348", props);
        } catch (Exception e){
            System.out.println(e);
            System.exit(-1);
        }

        String query = ""
        + "SELECT\n"
            + "class.cno,\n"
            + "course.cname,\n"
            + "SUM(enrollmentData.students) as students,\n"
            + "COUNT(class.section) sections\n,"
            + "SUM(enrollmentData.total)/SUM(enrollmentData.students) as average,\n"
            + "MAX(enrollmentData.average) as maxave,\n"
            + "MIN(enrollmentData.average) as minave\n"
        + "FROM class\n"
        + "INNER JOIN professor\n"
        + "ON class.instructor = professor.eid AND professor.dept = ?\n"
        + "INNER JOIN course\n"
        + "ON class.cno = course.cno\n"
        + "INNER JOIN (\n"
            + "SELECT\n"
                + "enrollment.cno,\n"
                + "enrollment.term,\n"
                + "enrollment.section,\n"
                + "AVG(enrollment.mark) as average,\n"
                + "SUM(enrollment.mark) as total,\n"
                + "COUNT(enrollment.mark) as students\n"
            + "FROM enrollment\n"
            + "GROUP BY\n"
                + "enrollment.cno,\n"
                + "enrollment.term,\n"
                + "enrollment.section)\n"
            + "AS enrollmentData\n"
        + "ON class.cno = enrollmentData.cno AND class.term = enrollmentData.term AND class.section = enrollmentData.section\n"
        + "WHERE ? <= SUBSTR(class.term, 2) AND ? >= SUBSTR(class.term, 2)\n"
        + "GROUP BY\n"
            + "class.cno,\n"
            + "course.cname,\n"
            + "SUBSTR(class.term, 2)\n"
        + "ORDER BY\n"
            + "SUBSTR(class.term, 2),\n"
            + "class.cno\n"
        ;

        try{
            stmt = con.prepareStatement(query);
        } catch (SQLException e){
            System.out.println(e);
            System.exit(-1);
        }

        while(true){
            Scanner reader = new Scanner(System.in);
            System.out.println("Enter Department ...");
            String dept = reader.nextLine();
            if(dept.equals("exit")){
                break;
            }
            System.out.println("Enter Start ...");
            int start = reader.nextInt();
            start -= 1900;
            System.out.println("Enter End ...");
            int end = reader.nextInt();
            end -= 1900;

            System.out.println("Year " + start);
            System.out.printf("%-7s %-20s %-10s %-10s %-10s %-12s %-12s\n", "C#", "Name", "Enrollment", "#Section", "Course Ave", "Max Class Ave", "Min Class Ave");

            try{
                stmt.setString(1, dept);
                stmt.setInt(2, start);
                stmt.setInt(3, end);
                rs = stmt.executeQuery();

                while (rs.next()){
                    String cno = rs.getString("CNO");
                    String name = rs.getString("CNAME");
                    name = (name.length() < 16) ? name : name.substring(0, 16) + " ...";
                    String enrollment = rs.getString("STUDENTS");
                    String section = rs.getString("SECTIONS");
                    String average = rs.getString("AVERAGE");
                    String max = rs.getString("MAXAVE");
                    String min = rs.getString("MINAVE");
                    System.out.printf("%-7s %-20s %-10s %-10s %-10s %-12s %-12s\n", cno, name, enrollment, section, average, max, min);
                }


                System.out.println("Year " + end);
            } catch (SQLException e){
                System.out.println(e);
                System.exit(-1);
            }
        }
        try{
            stmt.close();
            con.close();
        } catch (SQLException e){
            System.out.println(e);
            System.exit(-1);
        }

    }
}
