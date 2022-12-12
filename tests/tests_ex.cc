// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Disk Drop", "[drop_disk]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 7),
                    std::runtime_error);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 6),
                    std::runtime_error);
}

TEST_CASE("Check Winner Vertical", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT`
  InitBoard(student);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
}

// constexpr int kBoardWidth = 7;
// constexpr int kBoardHeight = 6;

TEST_CASE("BoardLocationInBounds", "[inbounds_location]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(BoardLocationInBounds(-1, 4));
  REQUIRE_FALSE(BoardLocationInBounds(4, -1));
  REQUIRE_FALSE(BoardLocationInBounds(8, 4));
  REQUIRE_FALSE(BoardLocationInBounds(4, 8));
  REQUIRE_FALSE(BoardLocationInBounds(-1, -1));
  REQUIRE_FALSE(BoardLocationInBounds(8, 8));
  REQUIRE(BoardLocationInBounds(0, 0));
}

TEST_CASE("Check Winner Horizontal", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
}

TEST_CASE("Check Winner Right Diagonal", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
}

TEST_CASE("Check Winner Left Diagonal", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
}

TEST_CASE("Search Winner Left Diagonal", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 5);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 4);
  DropDiskToBoard(student, DiskType::kPlayer2, 4);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
}

TEST_CASE("Search Winner Right Diagonal", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer1, 3);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kRightDiag));
}

TEST_CASE("Search Winner Horizontal", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 2);
  DropDiskToBoard(student, DiskType::kPlayer2, 3);
  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kHorizontal));
}

TEST_CASE("Check Winner Vertical", "[winner_check]") {
  // SECTION("Can use sections") {}
  // clang-format off
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kVertical));
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kVertical));
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer1, 5);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  DropDiskToBoard(student, DiskType::kPlayer2, 6);
  REQUIRE_FALSE(SearchForWinner(
      student, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(
      student, DiskType::kPlayer2, WinningDirection::kVertical));
}
///////////////////////////////////////////////////////////////////////////////////////////