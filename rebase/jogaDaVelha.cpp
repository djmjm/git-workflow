#include <iostream>
#include <time.h>

using namespace std;

#define CONVERT_STREAM \
ostream& operator << (ostream &out, value &content){ \
   switch(content){ \
        case cross: cout << " X "; break; \
        case circle: cout << " O "; break; \
        default: cout << " - "; \
    }\
    return out;\
};

enum value{
    empty, circle, cross
};

struct position{
    int x = 0, y = 0;
    value content = empty;
};

CONVERT_STREAM

class Board{
    private: 
        position pos[9];
        int seed;
        
        int played_times = 0;
        int victory = -1;
        
        bool check_victory(){
            auto c1 = pos[0].content;
            auto c2 = pos[1].content;
            auto c3 = pos[2].content;
            
            auto c4 = pos[3].content;
            auto c5 = pos[4].content;
            auto c6 = pos[5].content;
            
            auto c7 = pos[6].content;
            auto c8 = pos[7].content;
            auto c9 = pos[8].content;
            
            return ( ( c1 == c2) && c1 == c3 && c1 != value::empty)
                   ||
                   ( ( c4 == c5) && c4 == c6 && c4 != value::empty)
                   ||
                   ( ( c7 == c8) && c7 == c9 && c9 != value::empty)
                   ||
                   ( ( c1 == c4) && c7 == c4 && c7 != value::empty)
                   ||
                   ( ( c2 == c5) && c8 == c5 && c5 != value::empty)
                   ||
                   ( ( c3 == c6) && c9 == c6 && c6 != value::empty)
                   ||
                   ( ( c1 == c5) && c9 == c1 && c1 != value::empty)
                   ||
                   ( ( c3 == c5) && c7 == c3 && c3 != value::empty)
                   ;
                    
            
        }
        
    public: 
        int const size_x = 3, size_y = 3;
        Board(){
            seed = time(NULL);
            srand(seed);
        };
        friend ostream& operator << 
            (ostream &out, const Board &board);
        
        position &get_all_positions(){
            return *pos;
        }
        
        void play(){
            bool circle_put = false;
            while(played_times < 9){
                bool put = false;
                while(!put){
                    int pos_choose = (int) rand() % 9;
                    if( pos[pos_choose].content 
                        == value::empty
                    ){  
                        played_times++;
                        if( circle_put ){
                            pos[pos_choose].content 
                            = circle;
                        }else {
                            pos[pos_choose].content 
                            = cross;
                        }
                        
                        print();
                        
                        if(check_victory()){ 
                            victory = circle_put;
                            return; 
                        }
                        circle_put = !circle_put;
                        
                        put = true;
                    }
                }
            }
        }
        
        void print() {
            cout << endl
                 << " |Played Times - " << played_times
                 << endl;
            for(int i = 0; i < 3; i++){
                cout << " | ";
                for(int j = 0; j < 3; j++){
                    cout << pos[3*j + i].content
                        << " | "
                        ;
                }
                cout << endl;
            }
        }
        
        string get_winner(){
            switch(victory){
                case 1: return "\nCIRCLE WINS!!!\n";
                case -1: return "\nNOBODY WIN.\n";
                default: return "\nCROSS WINS!!!.\n";
            }
        }
};

ostream& operator << (ostream &out, Board &board){
    auto positions = &board.get_all_positions();
    
    for(int i = 0; i < 3; i++){
        cout << " | ";
        for(int j = 0; j < 3; j++){
            out << positions[3*j + i].content
                << " | "
                ;
        }
        out << endl;
    }
    return out;
};


int main(){
    auto game = *new Board();
    cout << " |GAMES HAS STARTED!!!" << endl;
    cout << game << endl << endl << endl; game.play();
    cout << endl;
    cout << " |GAME END ->>>>" << endl;
    cout << game << endl << game.get_winner();
    
    string exit;
    cin >> exit;
    
    return 0;
}
