#include <gtest/gtest.h>

int main(int argc, char **argv) {
	// GTest will parse arguments it recognizes and remove them
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
