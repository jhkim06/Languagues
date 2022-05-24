//
//  main.cpp
//  Chapter11
//
//  Created by Junho Kim on 2022/05/09.
//

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Punct_stream{
public:
    Punct_stream(istream& is) : source{is}, senstive{true} {}
    void whitespace(const string& s){
        white = s; }
    void add_white(char c){ white += c; }
    bool is_whitespace(char c);
    
    void case_senstive(bool b) { senstive = b; }
    bool is_case_senstive() { return senstive; }
    
    Punct_stream& operator>>(string& s);
    operator bool(); //
private:
    istream& source;
    istringstream buffer; // need #include <sstream>
    string white;
    bool senstive;
};

Punct_stream& Punct_stream::operator>>(string& s)
{
    while (!(buffer>>s)) { // 버퍼에서 공백문자로 구분된 단어를 하나씩 s에 입력
        if (buffer.bad() || !source.good()) return *this;
        buffer.clear();
        
        string line;
        getline(source, line);
        
        for (char& ch : line)
            if (is_whitespace(ch))
                ch = ' ';
            else if (!senstive)
                ch = tolower(ch);
        
        buffer.str(line);
    }
    return *this;
}

bool Punct_stream::is_whitespace(char c)
{
    for (char w : white)
        if (c==w) return true;
    return false;
}

Punct_stream::operator bool()
{
    return !(source.fail() || source.bad()) && source.good();
}

int main(int argc, const char * argv[]) {

    Punct_stream ps{cin};
    ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
    ps.case_senstive(false);
    
    cout << "단어 입력\n";
    vector<string> vs;
    
    for (string word; ps>>word; ){
        cout << word << " read.\n";
        vs.push_back(word);
    }
    
    sort(vs.begin(), vs.end());
    for (int i=0; i<vs.size(); ++i)
        if (i==0 || vs[i]!=vs[i-1]) cout << vs[i] << '\n';
    
}
