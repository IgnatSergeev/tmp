#include <tmp/directory.hpp>

#include <gtest/gtest.h>

using tmp::directory;
namespace fs = std::filesystem;

TEST(DirectoryTest, CreateDirectory) {
  const auto tmpdir = directory("test");
  ASSERT_TRUE(fs::exists(tmpdir));

  std::cout << fs::path(tmpdir) << std::endl;
}

TEST(DirectoryTest, RemoveDirectory) {
  fs::path path;
  {
    const auto tmpdir = directory("test");
    path = tmpdir;
    ASSERT_TRUE(fs::exists(path));
  }

  EXPECT_FALSE(fs::exists(path));
}

TEST(DirectoryTest, CreateMultiple) {
  const auto path = "test";

  const auto fst = directory(path);
  ASSERT_TRUE(fs::exists(fst));

  const auto snd = directory(path);
  ASSERT_TRUE(fs::exists(snd));

  EXPECT_NE(fs::path(fst), fs::path(snd));
}

TEST(DirectoryTest, SubpathTest) {
  const auto tmpdir = directory("test");
  const auto child = tmpdir / "child";

  ASSERT_EQ(tmpdir, child.parent_path());
}

TEST(DirectoryTest, MoveConstruction) {
    auto fst = directory("test");
    const auto snd = std::move(fst);

    ASSERT_TRUE(fs::path(fst).empty());
    ASSERT_TRUE(fs::exists(snd));
}

TEST(DirectoryTest, MoveAssignment) {
    auto fst = directory("test");
    auto snd = directory("");

    const auto path1 = fs::path(fst);
    const auto path2 = fs::path(snd);

    fst = std::move(snd);

    ASSERT_FALSE(fs::exists(path1));
    ASSERT_TRUE(fs::exists(path2));

    ASSERT_TRUE(fs::exists(fst));
}
