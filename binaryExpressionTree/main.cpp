#include "BinaryExpressionTree.hpp"
#include "woodpecker.hpp"

TEST("print with addition", 1)
{
  // check if print gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("1.0 2 +");
    CHECK_EQ("1.0+2", tree.printExpression());
  }
}

TEST("print with multiplication", 1)
{
  // check if print gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("1.0 2 3 * +");
    CHECK_EQ("1.0+2*3", tree.printExpression());
  }
}

TEST("print with parenthesis", 1)
{
  // check if print gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("1.0 2 + 3 *");
    CHECK_EQ("(1.0+2)*3", tree.printExpression());
  }
}

TEST("print with multiple parenthesis", 1)
{
  // check if print gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("0.5 2.5 + 3.7 0.3 + *");
    CHECK_EQ("(0.5+2.5)*(3.7+0.3)", tree.printExpression());
  }
}

TEST("print with lecture exmple", 1)
{
  // check if print gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("1 2 + 3 * 7 6 / -");
    CHECK_EQ("((1+2)*3)-(7/6)", tree.printExpression());
  }
}

TEST("evaluate with addition", 1)
{
  // check if evaluate gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("1.0 2 +");
    CHECK_EQ(3.0, tree.evaluateExpression());
  }
}

TEST("evaluate with multiplication", 1)
{
  // check if evaluate gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("1.0 2 3 * +");
    BinaryExpressionTree tree2 = BinaryExpressionTree("2 3 * 1.0 +");
    CHECK_EQ(7.0, tree.evaluateExpression());
    CHECK_EQ(7.0, tree2.evaluateExpression());
  }
}

TEST("evaluate with parenthesis", 1)
{
  // check if evaluate gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("1.0 2 + 3 *");
    CHECK_EQ(9.0, tree.evaluateExpression());
  }
}

TEST("evaluate with multiple parentheses", 1)
{
  // check if evaluate gives back the correct result
  {
    BinaryExpressionTree tree = BinaryExpressionTree("4 5 2 * + 5 + ");
    CHECK_EQ(19.0, tree.evaluateExpression());
  }
}

WOODPECKER_TEST_MAIN(-1, -1)
