//
//  main.cpp
//  Chapter6
//
//  Created by Junho Kim on 2022/04/23.
//
#include <std_lib_facilities.h>

// Input examples
// 1+2*3/4%5+(6-7*(8))
/*
 Expression:
           Term
           Expression "+" Term         // addition
           Expression "–" Term         // subtraction
 Term:
           Primary
           Term "*" Primary            // multiplication
           Term "/" Primary            // division
           Term "%" Primary            // remainder (modulo)
 Primary:
           Number
            "(" Expression ")"         // grouping
 Number:
           floating-point-literal
 
 
 Token get_token()
 double expression()
 double term()
 double primary()
 */


//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
    This file is known as calculator02buggy.cpp

    I have inserted 5 errors that should cause this not to compile
    I have inserted 3 logic errors that should cause the program to give wrong results

    First try to find an remove the bugs without looking in the book.
    If that gets tedious, compare the code to that in the book (or posted source code)

    Happy hunting!

*/

const char number = '8';
const char quit = 'q';
const char print = ';';
//------------------------------------------------------------------------------

class Token{
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case print:    // for "print"
    case quit:    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
            return Token{ch};        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token{number, val};   // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
    return 0;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get(); // token_string! not token
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
            return d;
    }
    case number:            // we use '8' to represent a number
        return t.value;  // return the number's value
    case '-':
        return -1. * primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
    return 0;
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
    
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream
    
    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
/*
    switch(t.kind){
    case '+':
        left += expression();
        //t = ts.get();
        cout << "+ left " << left << "\n";
        break;
    case '-':
        left -= expression();
        //t = ts.get();
        break;
    default:
        ts.putback(t);
        return left;
    }
    return left;
*/
 }

//------------------------------------------------------------------------------

const string prompt = "> ";
const string result = "= ";

void clean_up_mess(){
    
    while(true){
        Token t = ts.get();
        if(t.kind==print) return;
    }
}

void calculate(){

    //double val = 0;
    while (cin)
    try { // why while(cin) needed here?
        cout << prompt;
        //val = expression();
        
        Token t = ts.get();
        while(t.kind==print) t=ts.get(); // to check if q is comming after ';'
        if(t.kind==quit) return;
        ts.putback(t);
        cout << result << expression() << "\n";
    }
    catch (exception& e) {
        cerr << e.what() << "\n";
        clean_up_mess();
    }
}

int main()
try // function try block!
{
    calculate();
    keep_window_open();
    return 0;

}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------
