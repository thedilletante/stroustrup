#ifndef EXPR_CLASS
#define EXPR_CLASS


// implement struct - tree of nodes
// node - abstract
//  constant
//  operation
#include <iostream>
#include <string>
#include <sstream>

class Expr
{
//...
public:
    class SyntaxError {};
    class DivizionByZero {};

    Expr(const char *);
    ~Expr();
    int eval();
    void print();

private:
    
    enum Token_type
    {
        END, CONST,
        PLUS = '+', MINUS = '-', MULT = '*', DIV = '/',
        LP = '(', RP = ')'
    };

    class Node;
    class Constant;
    class Operation;

    Node *root;

    class ExprParser;

};

class Expr::Node
{
public:
    virtual int value() = 0;
    virtual const std::string char_rep() = 0;

protected:
    int evaluate(int lh, int rh, char op)
    {
        int result = lh;
        switch(op)
        {
            case PLUS: result += rh; break;
            case MINUS: result -= rh; break;
            case MULT: result *= rh; break;
            case DIV:
                if (rh == 0) throw DivizionByZero(); 
                result /= rh;
                break;
            default: throw SyntaxError();
        }
        return result;
    }
};

class Expr::Constant : public Expr::Node
{
public:
    Constant(int value)
        : val(value)
    {
    }

    virtual int value()
    {
        return val;
    }

    virtual const std::string char_rep()
    {
        std::stringstream s;
        s << val;
        return s.str();
    }
private:
    int val;
};


class Expr::Operation : public Expr::Node
{
public:
    Operation(Node *left, Node *right, Token_type tok)
        : l(left), r(right), op(tok)
    {

    }

    virtual int value()
    {
        return evaluate(l->value(), r->value(), op);
    }

    virtual const std::string char_rep()
    {
        return l->char_rep() + op + r->char_rep();
    }

private:
    Node *l;
    Node *r;
    char op;
};



class Expr::ExprParser
{
public:
    ExprParser(const char *);
    Node* parse();

private:
    Node* expr();
    Node* term();
    Node* prim();
    Token_type getToken();
    void skip();
    int const_value;

    std::istream *in;
    Token_type cur_tok;
};

Expr::ExprParser::ExprParser(const char * str)
{
    in = new std::stringstream(str);
    cur_tok = END;
    const_value = 0;
}

Expr::Node *Expr::ExprParser::parse()
{
    return expr();
}

// handle PLUS and MINUS
Expr::Node *Expr::ExprParser::expr()
{
    Node *left = term();
    Node *root = NULL;
    Token_type tmp = END;

    for (;;)
    {
        switch (cur_tok)
        {
            case PLUS:
            case MINUS:
                tmp = cur_tok;
                root = new Operation(left, prim(), tmp);
                left = root;
                break;
            default:
                return root ? root : left;
        }
    }
}

// hanle MULT and DIV
Expr::Node *Expr::ExprParser::term()
{
    Node *left = prim();
    Node *root = NULL;

    for (;;)
    {
        switch (cur_tok)
        {
            case MULT:
            case DIV:
                root = new Operation(left, prim(), cur_tok);
                left = root;
                break;
            default:
                return root ? root : left;
        }
    }
}

// handle CONST, unary MINUS and LP-RP
Expr::Node *Expr::ExprParser::prim()
{
    Node *root = NULL;
    switch(getToken())
    {
        case CONST:
            getToken();
            root = new Constant(const_value);
            break;
        case MINUS:
            getToken();
            root = new Constant(-const_value);
            break;
        case LP:
            root = expr();
            if (cur_tok != RP) throw SyntaxError();
            getToken();
            break;
        default:
            throw SyntaxError();
    }
    return root;
}

void Expr::ExprParser::skip()
{
    char ch;
    while(in->get(ch) && isspace(ch));
    in->putback(ch);
}

Expr::Token_type Expr::ExprParser::getToken()
{
    skip();
    char ch;
    if (!in->get(ch)) return END;

    switch(ch)
    {
        case PLUS :
        case MINUS:
        case MULT :
        case DIV  :
        case LP   :
        case RP   :
            return cur_tok = Token_type(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            in->putback(ch);
            (*in) >> const_value;
            return cur_tok = CONST;
        default: throw SyntaxError();
    }
}



Expr::Expr(const char * str)
{
    ExprParser parser(str);
    root = parser.parse(); 
}
Expr::~Expr(){}
int Expr::eval()
{
    return root->value();
}
void Expr::print()
{
    std::cout << root->char_rep() << std::endl;
}

#endif // EXPR_CLASS