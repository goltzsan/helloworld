#include "../World.hpp"
#include <gtest/gtest.h>

TEST(WorldTest, sayHello) {
  World world;
  EXPECT_EQ(0, world.sayHello());
}

TEST(WorldTest, sayThis_returns_false) {
  World world;
  EXPECT_FALSE(world.sayThis(""));
}

TEST(WorldTest, sayThis_returns_true) {
  World world;
  EXPECT_TRUE(world.sayThis("Hello World!!!"));
}

// int main(int argc, char **argv) {
// testing::InitGoogleTest(&argc, argv);
// return RUN_ALL_TESTS();
//}
