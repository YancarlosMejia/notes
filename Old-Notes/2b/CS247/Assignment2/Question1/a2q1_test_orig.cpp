#define DEBUG

#include "gtest/gtest.h"
#include "Date.h"

#define EXPECT_THROW_MESSAGE(MSG, BLOCK) try BLOCK catch(const char* error) {ASSERT_EQ(std::string(MSG), error);}

TEST(DateConstructor, ConstructorsErrors) {
	EXPECT_THROW_MESSAGE("Invalid year", { Date d(1, "April", 1800); });
	EXPECT_THROW_MESSAGE("Invalid year", { Date d(1, "April", 2800); });
	EXPECT_THROW_MESSAGE("Invalid month", { Date d(1, "april", 2000); });
	EXPECT_THROW_MESSAGE("Invalid month", { Date d(1, "apr", 2000); });

	EXPECT_THROW_MESSAGE("Invalid day of the month.", { Date d(29, "February", 2003); });
	EXPECT_NO_THROW(Date(29, "February", 2004));
}

TEST(DateConstructor, Constructors) {
	EXPECT_NO_THROW({
		Date a(1, "April", 2005);
		Date b(a);
	});
}

TEST(Accessors, Accessors) {
	Date a(1, "April", 2005);
	EXPECT_EQ(a.day(), 1);
	EXPECT_EQ(a.month(), "April");
	EXPECT_EQ(a.year(), 2005);
}

TEST(Operators, Comparison) {
	Date a(1, "April", 2005);
	
	Date b(2, "April", 2005);
	Date c(1, "December", 2005);
	Date d(1, "April", 2006);

	EXPECT_EQ(a, a);
	EXPECT_NE(a, b);
	EXPECT_NE(a, c);
	EXPECT_NE(a, d);
	
	EXPECT_LE(a, a);
	EXPECT_GE(a, a);
	
	EXPECT_LT(a, b);
	EXPECT_LE(a, b);
	EXPECT_LT(a, c);
	EXPECT_LE(a, c);
	EXPECT_LT(a, d);
	EXPECT_LE(a, d);
	
	EXPECT_GT(a, b);
	EXPECT_GE(b, a);
	EXPECT_GT(a, c);
	EXPECT_GE(c, a);
	EXPECT_GT(a, d);
	EXPECT_GE(d, a);

}
TEST(Operators, Assignment){
	Date a = Date(1, "April", 2005);
	EXPECT_NO_THROW(Date b = a);
	Date b = a;
	EXPECT_EQ(a, b);
}

TEST(Operators, Streaming) {
	Date orig = Date(1, "April", 2005);
	Date input = Date(1, "January", 1900);

	std::stringstream ss;
	std::string date = "1 April, 2005";
	EXPECT_NO_THROW(ss >> date >> input);
}