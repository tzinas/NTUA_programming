/*
#include <iostream>
#include <stdexcept>

using namespace std;
*/
class Move {
public:
    // Take sc coins from heap sh and put tc coins to heap th.
    Move(int sh, int sc, int th, int tc){
        source_heap = sh;
        source_coins = sc;
        target_heap = th;
        target_coins = tc;
    }        

    int getSource() const{
        return source_heap;
    }
    int getSourceCoins() const{
        return source_coins;
    }
    int getTarget() const{
        return target_heap;
    }
    int getTargetCoins() const{
        return target_coins;
    }

    friend ostream & operator << (ostream &out, const Move &move){
        out << "takes " << move.source_coins << " coins from heap " << move.source_heap << " and puts ";
        if (move.target_coins == 0){
            out << "nothing";
            return out;
        }
        out << move.target_coins << " coins to heap " << move.target_heap;
        return out;
    }

private:
    int source_heap, source_coins, target_heap, target_coins;
};

class State {
public:
    // State with h heaps, where the i-th heap starts with c[i] coins.
    State(int h, const int c[]){
        A = new int[h];
        heaps = h;

        for(int i=0; i<h; i++){
            A[i] = c[i];
        }
    }
    ~State(){
        delete [] A;
    }

    void next(const Move &move) throw(logic_error){
        int from = move.getSource();
        int  to = move.getTarget();

        int from_coins = move.getSourceCoins();
        int to_coins = move.getTargetCoins();

        if (from < 0 || from >= heaps || to < 0 || to >= heaps || from_coins > A[from]) throw logic_error("invalid heap");
        if (to_coins >= from_coins) throw logic_error("invalid move");

        A[from] -= from_coins;
        A[to] += to_coins;

    }
        
    bool winning() const{
        for (int i=0; i<heaps; i++){
            if (A[i] != 0){
                return false;
            }
        }
        return true;
    }

    int getHeaps() const{
        return heaps;
    }
    int getCoins(int h) const throw(logic_error){
        if (h < 0 || h >= heaps) throw logic_error("invalid heap");
        return A[h];
    }

    friend ostream & operator << (ostream &out, const State &state){
        for (int i=0; i<state.heaps - 1; i++){
            out << state.A[i] << ", ";
        }
        out << state.A[state.heaps - 1];
        
        return out;
    }

private:
    int *A;
    int heaps;
};

class Player {
public:
    Player(const string &n){
        name = n;
    }
    virtual ~Player(){
        delete name;
    }

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player);

protected:
    string *name;
};

class GreedyPlayer: public Player{
     
};

/*
int main(){
    Move M(0, 1, 3, 0);
    int v[4];
    v[0] = 1;
    v[1] = 5;
    v[2] = 10;
    State L(3, v);
    cout << L;
    return 0;
}
*/
