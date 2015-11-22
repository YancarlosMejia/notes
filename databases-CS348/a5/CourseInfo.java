//javac -cp "*:" CourseInfo
import java.util.Properties;
import java.util.Scanner;
import java.sql.*;

public class CourseInfo {
    public static void main(String[] args){
        Connection con = null;
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

        PreparedStatement stmt = null;
        ResultSet rs = null;
        while(true){
            Scanner reader = new Scanner(System.in);
            String dept = "CS";
            int start = 90;
            int end = 99;
/*            System.out.println("Enter Department ...");
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
*/
            System.out.println("Year " + start);
            System.out.printf("%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "C#", "Name", "Enrollment", "#Section", "Course Ave", "Max Class", "Min Class Ave");

            try{
                String query = ""
                + "SELECT *\n"
                + "FROM class\n"
                + "INNER JOIN professor\n"
                + "ON class.instructor = professor.eid AND professor.dept = ?\n"
                + "WHERE ? <= SUBSTR(class.term, 2) AND ? >= SUBSTR(class.term, 2)\n"
                ;
                stmt = con.prepareStatement(query);
                stmt.setString(1, dept);
                stmt.setInt(2, start);
                stmt.setInt(3, end);
                rs = stmt.executeQuery();

                while (rs.next()){
                     System.out.printf("%-10s %-10s\n", rs.getString("CNO"), rs.getString("TERM"));
                }


                System.out.println("Year " + end);
            } catch (SQLException e){
                System.out.println(e);
                System.exit(-1);
            }

            break;

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
