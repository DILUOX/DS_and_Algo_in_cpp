/*** Written by Márton Kozma, finished on 2023/10/9  ***/

#ifndef KHF03_BINARYEXPRESSIONTREE_HPP
#define KHF03_BINARYEXPRESSIONTREE_HPP

#include "iostream"
#include "stack.h"
#include "sstream"

class BinaryExpressionTree
{
private:
    struct Node
    {
    private:
        std::string data;
        Node *left;
        Node *right;

    public:
        Node() : data(std::string()), left(nullptr), right(nullptr) {}
        Node(std::string data) : data(data), left(nullptr), right(nullptr) {}
        Node(std::string data_, Node *left_, Node *right_) : data(data_), left(left_), right(right_) {}

        Node *getleft() { return left; }
        Node *getright() { return right; }
        void setleft(Node *new_) { left = new_; }
        void setright(Node *new_) { right = new_; }

        std::string get_data() { return data; }
        char get_operand() { return data.front(); }
        void set_data(std::string data_) { data = data_; }
        void set_data(char data_) { data = data_; }
    };
    Node *root;

    bool isEmpty() const;

    void insert(Node *n);
    void remove(std::string s);

    std::size_t size(Node *root_);

    std::string inorder(Node *r) const;
    double postorder(Node *r) const;

    // std::string preorder() = 0;

    bool isNum(char c) const { return 48 <= c && c <= 57; }
    bool isOp(char c) const { return c == '+' || c == '-' || c == '*' || c == '/'; }
    int priority(char c) const
    {
        if (c == '+' || c == '-')
            return 1;
        else
            return 2;
    }
    double do_operation(char op, double a, double b) const;

    void destroy(Node *r);

public:
    explicit BinaryExpressionTree(std::string postfixExpression);
    ~BinaryExpressionTree();
    std::string printExpression() const;
    double evaluateExpression() const;
};

/***                               Implementations                                   ***/

/***    Constructor initializes binary expression tree from postfix expression
 *      ----------------------------------------------------------------------
 *      Works only with correct postfix operations, error handling is happening
 *      but it is mostly caused by undefined behavior
 *                                                                                  ***/
BinaryExpressionTree::BinaryExpressionTree(std::string postfixExpression) : root(nullptr)
{
    std::size_t i = 0;
    std::size_t length = postfixExpression.length();

    char investigated;
    auto expressions = stack<std::string>(); // stack for numbers in the expression
    auto nodes = stack<Node *>();            // stack for side trees generated during reading the expression
    int numcount = 0;                        // counter for currently available numbers in the stack

    /***the algorithm works in the following way:
     * while going through the expression, it stores found numbers in the expressions stack
     * then, if it finds an operator, it pops out the last one or two numbers from the stack, according to how many numbers are left
     * and appends it to the operator as left and/or right nodes. Then it pushes the connected nodes into the node stack.
     * This method gives us a reverse order of the operations which is optimal to build an expression tree from it.
     * After this procedure, it empties the node stack, and insert the nodes being popped to the expression tree.
     */

    while (i < length)
    {
        investigated = postfixExpression[i];

        if (isNum(investigated))
        { // pushing the whole number till the next space character
            std::size_t eon = postfixExpression.find(" ", i) - 1;

            if (eon != length)
            {
                expressions.push(postfixExpression.substr(i, eon - i + 1));
                i += expressions.top()->get_data().length();
                numcount++;
                continue;
            }
        }
        if (isOp(investigated))
        {
            Node *l = nullptr;
            Node *r = nullptr;
            if (numcount > 1)
            { // dealing with 2 numbers
                r = new Node(expressions.pop());
                l = new Node(expressions.pop());
                numcount -= 2;
            }
            else if (numcount > 0)
            { // dealing with one number and one side result
                if (priority(nodes.top()->get_data()->get_operand()) <= priority(investigated))
                {                                    // if the investigated operands priority is higher
                    r = new Node(expressions.pop()); // then the previous operator's priority,
                                                     //  then the previous operation goes to the right
                } // if not, then it goes to the left
                else
                {
                    l = new Node(expressions.pop());
                }

                numcount--;
            }
            else
            { // dealing with two side results
                r = nodes.pop();
                l = nodes.pop();
            }

            Node *curr = new Node(postfixExpression.substr(i, 1), l, r); // generating new side tree with the currently investigated operator
            nodes.push(curr);
        }
        i++;
    }
    while (!nodes.isEmpty())
    {
        insert(nodes.pop());
    }
}

std::string BinaryExpressionTree::printExpression() const
{
    return inorder(root);
}

double BinaryExpressionTree::evaluateExpression() const
{
    return postorder(root);
}

BinaryExpressionTree::~BinaryExpressionTree()
{
    destroy(root);
}

bool BinaryExpressionTree::isEmpty() const
{
    return root == nullptr;
}

// special expressiontree insertion
void BinaryExpressionTree::insert(Node *n)
{
    if (isEmpty())
    {
        root = n;
        return;
    }

    Node *start = root;
    // we load the tree from left to right
    bool finish = false;
    while (!finish) // tree's height > 0
    {
        // insertion happens here:
        if (start->getleft() == nullptr)
        {
            start->setleft(n);
            finish = true;
            continue;
        }
        else if (start->getright() == nullptr)
        {
            start->setright(n);
            finish = true;
            continue;
        }
        // navigation by checking if one of the two children is a number; if yes, we go to the opposite direction,because the numbers are the leafs
        if (isNum(start->getright()->get_operand()))
        { // checking right side
            start = start->getleft();
        }
        else if (isNum(start->getleft()->get_operand()))
        { // checking left side
            start = start->getright();
        }
        else
            start = start->getleft(); // if both are numbers, which is impossible from correct input, then we go to the left, hoping that we find something useful there
    }
}

// recursive size reading function; returns the number of elements in the sidetree given by root_
std::size_t BinaryExpressionTree::size(BinaryExpressionTree::Node *root_)
{
    if (root_ == nullptr)
    {
        return 0;
    }
    else
    {
        return size(root_->getleft()) + size((root_->getright())) + 1;
    }
}

// inorder read of the expression tree, with builtin brace addition

std::string BinaryExpressionTree::inorder(Node *r) const
{
    if (r == nullptr)
    {
        return "";
    }

    if (r->getleft() != nullptr && r->getright() != nullptr)
    {
        // the case when r operates with two side results(which two side tree's root is also an operand)
        if (!isNum(r->getleft()->get_operand()) && !isNum(r->getright()->get_operand()))
        {
            return '(' + inorder(r->getleft()) + ')' + r->get_data() + '(' + inorder(r->getright()) + ')';
        }

        // the case when r operates with one side result
        if (!isNum(r->getleft()->get_operand()) && isNum(r->getright()->get_operand()))
        {
            return '(' + inorder(r->getleft()) + ')' + r->get_data() + inorder(r->getright());
        }
    }
    // r is a basic operator with 2 operands

    return inorder(r->getleft()) + r->get_data() + inorder(r->getright());
}

double BinaryExpressionTree::do_operation(char op, double a, double b) const
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        break;
    }
    return 0;
}

// recursive postorder math function; this function evaluates the expression stored in the tree, returning the result as a double
double BinaryExpressionTree::postorder(BinaryExpressionTree::Node *r) const
{
    if (r == nullptr)
    {
        return 0;
    }
    if (isOp(r->get_operand()))
    {
        return do_operation(r->get_operand(), postorder(r->getleft()), postorder(r->getright()));
    }
    else
    {
        std::stringstream s;
        s << r->get_data();
        double mynum;
        s >> mynum;
        return mynum;
    }
}

void BinaryExpressionTree::destroy(BinaryExpressionTree::Node *r)
{
    if (r == nullptr)
    {
        return;
    }
    destroy(r->getleft());
    destroy(r->getright());
    delete r;
}

#endif // KHF03_BINARYEXPRESSIONTREE_HPP
