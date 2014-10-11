#ifndef EXPR_CLASS
#define EXPR_CLASS

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#ifdef DBG
#define DEBUG(A) std::cout << A << std::endl
#else
#define DEBUG(A)
#endif

std::map<std::string, int> sym_table;

class Expr
{
public:
    struct SyntaxError
    {
        int pos;
        SyntaxError(int _pos) : pos(_pos) {}
        int position() const { return pos; }
    };
    class DivizionByZero {};

    Expr(const char *);
    ~Expr();
    int eval();
    void print();

private:
    
    enum Token_type
    {
        END, CONST, NAME,
        PLUS = '+', MINUS = '-', MULT = '*', DIV = '/',
        EQ = '=', LP = '(', RP = ')', 
    };

    class Node;
    class Constant;
    class Operation;
    class Variable;
    class Assignment;

    Node *root;

    class ExprParser;

};

class Expr::Node
{
public:
    virtual int value() = 0;
    virtual const std::string char_rep() = 0;
    virtual ~Node() {}

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
            default: throw SyntaxError(0);
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

    virtual ~Constant()
    {
        DEBUG("Delete constant");
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
        return (char)LP + l->char_rep() + op + r->char_rep() + (char)RP;
    }

    virtual ~Operation()
    {
        DEBUG("Delete operation");
        delete l;
        delete r;
    }

private:
    Node *l;
    Node *r;
    char op;
};

class Expr::Variable : public Expr::Node
{
public:
    Variable(const std::string &_name)
        : name(_name), val(sym_table[_name])
    {}

    virtual int value()
    {
        return val;
    }

    virtual const std::string char_rep()
    {
        return name;
    }

    void assign(int value)
    {
        val = value;
    }

    virtual ~Variable()
    {
        DEBUG("Delete variable");
    }

private:
    const std::string name;
    int &val;
};

class Expr::Assignment : public Expr::Node
{
public:
    Assignment(Variable *name, Node *expr)
        : n(name), e(expr)
    {}

    virtual int value()
    {
        n->assign(e->value());
        return n->value();
    }

    virtual const std::string char_rep()
    {
        return ( '(' + n->char_rep() + "=" + e->char_rep() + ')' );
    }

    virtual ~Assignment()
    {
        DEBUG("Delete assignment");
        delete n;
        delete e;
    }


private:
    Variable *n;
    Node *e;
};

class Expr::ExprParser
{
public:
    ExprParser(const char *);
    ~ExprParser()
    {
        delete in;
    }
    Node* parse();

private:
    Node* expr();
    Node* term();
    Node* prim();
    Token_type getToken();
    void skip();
    int const_value;
    std::string string_rep;
    size_t cur_pos;

    std::istream *in;
    Token_type cur_tok;
};

Expr::ExprParser::ExprParser(const char * str)
    : in(new std::stringstream(str)), cur_tok(END),
      const_value(0), cur_pos(0)
{
}

Expr::Node *Expr::ExprParser::parse()
{
    Node *node = expr();
    if (cur_tok != END)
        throw SyntaxError(cur_pos);
    return node;
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
                root = new Operation(left, term(), tmp);
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
    Token_type tmp = END;

    for (;;)
    {
        switch (cur_tok)
        {
            case MULT:
            case DIV:
                tmp = cur_tok;
                root = new Operation(left, prim(), tmp);
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
    Token_type tmp = END;
    switch(getToken())
    {
        case CONST:
            getToken();
            root = new Constant(const_value);
            break;
        case NAME:
            {
                Variable *var = new Variable(string_rep);
                if (getToken() == EQ)
                {
                    root = new Assignment(var, expr());
                    getToken();
                }
                else
                {
                    root = var;
                }
            }
            break;
        case MINUS:
        case PLUS: // for symmetry :)
            tmp = cur_tok;
            root = new Operation(new Constant(0), prim(), tmp);
            break;
        case LP:
            root = expr();
            if (cur_tok != RP) throw SyntaxError(cur_pos);
            getToken();
            break;
        default:
            throw SyntaxError(cur_pos);
    }
    return root;
}

void Expr::ExprParser::skip()
{
    char ch;
    while(in->get(ch) && isspace(ch)) ++cur_pos;
    in->putback(ch);
}

Expr::Token_type Expr::ExprParser::getToken()
{
    skip();
    char ch;
    if (!in->get(ch)) return cur_tok = END;
    ++cur_pos;

    switch(ch)
    {
        case PLUS :
        case MINUS:
        case MULT :
        case DIV  :
        case LP   :
        case RP   :
        case EQ   :
            return cur_tok = Token_type(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            const_value = 0;
            do
            {
                const_value *= 10;
                const_value += (int)(ch - '0');
                ++cur_pos;
            }
            while (in->get(ch) && ::isdigit(ch));
            if (ch) in->putback(ch);
            --cur_pos;
            return cur_tok = CONST;
        default:
            if (::isalpha(ch))
            {
                string_rep.clear();
                do
                {
                    ++cur_pos;
                    string_rep += ch;
                }
                while (in->get(ch) && ::isalnum(ch));
                if (ch) in->putback(ch);
                --cur_pos;
                return cur_tok = NAME;
            }
            throw SyntaxError(cur_pos);
    }
}



Expr::Expr(const char * str)
{
    ExprParser parser(str);
    root = parser.parse(); 
}
Expr::~Expr()
{
    DEBUG("Delete expression");
    delete root;
}
int Expr::eval()
{
    return root->value();
}
void Expr::print()
{
    std::cout << root->char_rep() << std::endl;
}

#endif // EXPR_CLASS
