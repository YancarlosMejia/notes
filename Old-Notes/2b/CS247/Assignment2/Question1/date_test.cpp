#define DEBUG
#include "gtest/gtest.h"
#include "Date.cpp"

#define EXPECT_THROW_MSG(MSG, BLOCK) try BLOCK catch( const char* err ) { ASSERT_EQ( string(MSG), err ); }

class DateTest : public ::testing::Test {
private:
  streambuf* old_cout;

protected:
  stringstream output;

  DateTest() {
    old_cout = cout.rdbuf(output.rdbuf());
  }

  virtual ~DateTest() {
    cout.rdbuf(old_cout);
  }
};

TEST_F(DateTest, invalidYear) {
  EXPECT_THROW_MSG("Invalid year.",{Date* test = new Date(1,"January", 2101);});
}

TEST_F(DateTest, invalidDay) {
  EXPECT_THROW_MSG("Invalid day of the month.", {Date* test = new Date(31,"November", 2000);});
}

TEST_F(DateTest, invalidDayLeapYear) {
  EXPECT_THROW_MSG("Invalid day of the month.", {Date* test = new Date(29,"February", 1900);});
}

TEST_F(DateTest, validDayLeapYear) {
  ASSERT_NO_THROW(Date* test = new Date(29,"February", 2000));
}

TEST_F(DateTest, invalidMonth) {
  EXPECT_THROW_MSG("Invalid month.", {Date* test = new Date(1,"Janury", 2100);});
}

TEST_F(DateTest, validDate) {
  EXPECT_NO_THROW(Date* test = new Date(1,"January", 2100));
  Date* test = new Date(1,"January", 2100);
  EXPECT_EQ(test->day(), 1);
  EXPECT_EQ(test->month(), "January");
  EXPECT_EQ(test->year(), 2100);
}

TEST_F(DateTest, printDate) {
  const Date& test = Date(2,"January", 2001);
  cout << test;
  stringstream ss;
  ss << "2 January, 2001";
  EXPECT_EQ(ss.str(), output.str());
}

TEST_F(DateTest, dateEquality) {
  const Date& test = Date(2,"January", 2001);
  const Date& test2 = Date(2,"January", 2001);
  EXPECT_EQ(test.day(), test2.day());
  EXPECT_EQ(test.month(), test2.month());
  EXPECT_EQ(test.year(), test2.year());
}

TEST_F(DateTest, addYearToLeapYear) {
  const Date& test = Date(29,"February", 2000);
  const Date& test2 = incYears(test, 1);
  cout << test2;
  EXPECT_EQ(output.str(), "28 February, 2001");
}

TEST_F(DateTest, basicAddMonths) {
  const Date& test = Date(29,"February", 2000);
  const Date& test2 = incMonths(test, 10);
  cout << test2;
  EXPECT_EQ(output.str(), "29 December, 2000");
}

TEST_F(DateTest, basicAddMonths2) {
  const Date& test = Date(31,"March", 2000);
  const Date& test2 = incMonths(test, 1);
  cout << test2;
  EXPECT_EQ(output.str(), "30 April, 2000");
}

TEST_F(DateTest, addMonthsToChangeYear) {
  const Date& test = Date(31,"March", 2000);
  const Date& test2 = incMonths(test, 24);
  cout << test2;
  EXPECT_EQ(output.str(), "31 March, 2002");
}

TEST_F(DateTest, basicDaysAdd) {
  const Date& test = Date(29,"January", 2000);
  const Date& test2 = incDays(test, 369);
  cout << test2;
  EXPECT_EQ(output.str(), "1 February, 2001");
}

TEST_F(DateTest, checkLeapYearDay) {
  const Date& test = Date(28,"February", 2000);
  const Date& test2 = incDays(test, 1);
  cout << test2;
  EXPECT_EQ(output.str(), "29 February, 2000");
}

TEST_F(DateTest, addDaysToLeapYear) {
  const Date& test = Date(29,"February", 2000);
  const Date& test2 = incDays(test, 730);
  cout << test2;
  EXPECT_EQ(output.str(), "28 February, 2002");
}

TEST_F(DateTest, addDaysToBecomeLeapYear) {
  const Date& test = Date(31,"January", 1999);
  const Date& test2 = incDays(test, 500);
  cout << test2;
  EXPECT_EQ(output.str(), "14 June, 2000");
}

TEST_F(DateTest, leapYearToLeapYear) {
  const Date& test = Date(29,"February", 2000);
  const Date& test2 = incDays(test, 1461);
  cout << test2;
  EXPECT_EQ(output.str(), "29 February, 2004");
}

TEST_F(DateTest, addDayPastBounds) {
  const Date& test = Date(31,"December", 2100);
  ASSERT_ANY_THROW(incDays(test, 1));
}

TEST_F(DateTest, copyDate) {
  const Date test = Date(29,"February", 2000);
  const Date test2(test);
  EXPECT_EQ(true, test == test2);
}

TEST_F(DateTest, assignDate) {
  Date test = Date(29,"February", 2000);
  Date test2 = Date(30, "May", 2050);
  test = test2;

  string expected = "New date = 30 May, 2050, old date = 30 May, 2050";
  cout << "New date = " << test.day() << " " << test.month() << ", " << test.year() << ", old date = " << test.day() << " " + test.month() << ", " << test.year();
  EXPECT_EQ(output.str(), expected);
}

TEST_F(DateTest, readInDate) {
  stringbuf test_input("10 March, 2014", ios_base::in);
  streambuf * const cin_buf = cin.rdbuf(&test_input);
  Date test = Date(29,"February", 2000);
  cin >> test;
  cout << test;
  EXPECT_EQ(cin.fail(),false);
  cin.rdbuf(cin_buf);
  EXPECT_EQ("10 March, 2014",output.str());
}

TEST_F(DateTest, readInBadDate) {
  stringbuf test_input("March 10, 2014", ios_base::in);
  streambuf * const cin_buf = cin.rdbuf(&test_input);
  Date test = Date(29,"February", 2000);
  EXPECT_THROW_MSG("Invalid date value.",{cin >> test;});
  EXPECT_EQ(cin.fail(), true);
  cin.rdbuf(cin_buf);
}

TEST_F(DateTest, readInBadDateComma) {
  stringbuf test_input("10 March 2014", ios_base::in);
  streambuf * const cin_buf = cin.rdbuf(&test_input);
  Date test = Date(29,"February", 2000);
  EXPECT_THROW_MSG("Invalid date value.",{cin >> test;});
  EXPECT_EQ(cin.fail(), true);
  cin.rdbuf(cin_buf);
}

TEST_F(DateTest, compareDates) {
  Date test = Date(27,"February", 2000);
  Date test2 = Date(27,"February", 2010);
  Date test3 = Date(28,"February", 2000);
  Date test4 = Date(29,"March", 2000);

  EXPECT_EQ(test != test2, true);
  EXPECT_EQ(test < test2, true);
  EXPECT_EQ(test < test3, true);
  EXPECT_EQ(test < test4, true);
  EXPECT_EQ(test4 > test3, true);
  EXPECT_EQ(test2 >= test2, true);
  EXPECT_EQ(test2 >= test4, true);
  EXPECT_EQ(test3 <= test3, true);
}
