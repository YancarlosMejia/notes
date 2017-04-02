#define DEBUG
#include "AccountTestHarness.cpp"
#include "gtest/gtest.h"


class AccountTest : public ::testing::Test {
	streambuf* old_cout;
protected:
	AccountNo accountNo;
	stringstream output;

	AccountTest() {
		old_cout = cout.rdbuf(output.rdbuf());
	}

	virtual ~AccountTest() {
		cout.rdbuf(old_cout);
	}
};

TEST_F(AccountTest, Init) {
	CheapAccount* cAccount = new CheapAccount(accountNo);
	ExpensiveAccount* eAccount = new ExpensiveAccount(accountNo);

	EXPECT_EQ(0, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
