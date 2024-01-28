#include <tmp/directory.hpp>

#include <gtest/gtest.h>

namespace fs = std::filesystem;

TEST(DirectoryTest, CreateDirectory) {
    {
        const auto tmpdir = tmp::directory(PREFIX);
        ASSERT_TRUE(fs::exists(tmpdir));
    }
    {
        const auto tmpdir = tmp::directory();
        ASSERT_TRUE(fs::exists(tmpdir));
    }
}

TEST(DirectoryTest, RemoveDirectory) {
    auto path = fs::path();
    {
        const auto tmpdir = tmp::directory(PREFIX);
        path = tmpdir;
        ASSERT_TRUE(fs::exists(path));
    }

    EXPECT_FALSE(fs::exists(path));
}

TEST(DirectoryTest, CreateMultiple) {
    const auto fst = tmp::directory(PREFIX);
    ASSERT_TRUE(fs::exists(fst));

    const auto snd = tmp::directory(PREFIX);
    ASSERT_TRUE(fs::exists(snd));

    EXPECT_NE(fs::path(fst), fs::path(snd));
}

TEST(DirectoryTest, SubpathTest) {
    const auto tmpdir = tmp::directory(PREFIX);
    const auto child = tmpdir / "child";

    ASSERT_EQ(fs::path(tmpdir), child.parent_path());
}

TEST(DirectoryTest, MoveConstruction) {
    auto fst = tmp::directory(PREFIX);
    const auto snd = std::move(fst);

    ASSERT_TRUE(fst->empty());
    ASSERT_TRUE(fs::exists(snd));
}

TEST(DirectoryTest, MoveAssignment) {
    auto fst = tmp::directory(PREFIX);
    auto snd = tmp::directory(PREFIX);

    const auto path1 = fs::path(fst);
    const auto path2 = fs::path(snd);

    fst = std::move(snd);

    ASSERT_FALSE(fs::exists(path1));
    ASSERT_TRUE(fs::exists(path2));

    ASSERT_TRUE(fs::exists(fst));
    ASSERT_EQ(fs::path(fst), path2);
}
