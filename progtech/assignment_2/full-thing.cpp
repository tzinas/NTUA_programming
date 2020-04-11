#include <iostream>
#include <stdexcept>
#define INF 0x3f3f3f3f

using namespace std;

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

    virtual const string & getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream & operator << (ostream &out, const Player &player){
        out << player.getType() << " player " << player.name;
        return out;
    }

protected:
    string name;
};

class GreedyPlayer: public Player{
public:
    GreedyPlayer(const string &n): Player(n){}

    const string & getType() const override{
        return type;
    }
    Move play(const State &s) override{
        int heaps = s.getHeaps();
        int max_coins = 0, max_h = 0;
        for (int i=0; i<heaps; i++){
            int coins = s.getCoins(i);
            if (coins > max_coins){
                max_coins = coins;
                max_h = i;
            }
        }
        return Move(max_h, max_coins, 0, 0);
    }
private:
    string type = "Greedy";
};

class SpartanPlayer: public Player{
public:
    SpartanPlayer(const string &n): Player(n){}

    const string & getType() const override{
        return type;
    }
    Move play(const State &s) override{
        int heaps = s.getHeaps();
        int max_coins = 0, max_h = 0;
        for (int i=0; i<heaps; i++){
            int coins = s.getCoins(i);
            if (coins > max_coins){
                max_coins = coins;
                max_h = i;
            }
        }
        return Move(max_h, 1, 0, 0);
    }
private:
    string type = "Spartan";
};

class SneakyPlayer: public Player{
public:
    SneakyPlayer(const string &n): Player(n){}
    const string & getType() const override{
        return type;
    }
    Move play(const State &s) override{
        int heaps = s.getHeaps();
        int min_coins = INF, min_h = 0;
        for (int i=0; i<heaps; i++){
            int coins = s.getCoins(i);
            if (coins < min_coins && coins > 0){
                min_coins = coins;
                min_h = i;
            }
        }
        return Move(min_h, min_coins, 0, 0);
    }
private:
    string type = "Sneaky";
};

class RighteousPlayer: public Player{
public:
    RighteousPlayer(const string &n): Player(n){}
    const string & getType() const override{
        return type;
    }
    Move play(const State &s) override{
        int heaps = s.getHeaps();
        int min_coins = s.getCoins(0), min_h = 0;
        int max_coins = 0, max_h = 0;
        for (int i=0; i<heaps; i++){
            int coins = s.getCoins(i);
            if (coins < min_coins){
                min_coins = coins;
                min_h = i;
            }
            if (coins > max_coins){
                max_coins = coins;
                max_h = i;
            }
        }

        return Move(max_h, (max_coins + 1) / 2, min_h, ((max_coins + 1) / 2) - 1);
    }
private:
    string type = "Righteous";
};

class Game {
public:
    Game(int h, int p){
        max_heaps = h;
        max_players = p;
        players = new Player*[p];
        state = new int[h];
    }
    ~Game(){
        delete players;
        delete [] state;
    }
    void addHeap(int coins) throw(logic_error){
        if (current_heaps == max_heaps) throw logic_error("max heaps");
        state[current_heaps] = coins;
        current_heaps++;
    }
    void addPlayer(Player *player) throw(logic_error){
        if (current_players == max_players) throw logic_error("max players");
        players[current_players] = player;
        current_players++;
    }
    void play(ostream &out) throw(logic_error){
        State S(current_heaps, state);
        int j = 0;
        while(!S.winning()){
            out <<"State: " <<  S <<endl;
            out << *players[j] << " " << players[j] -> play(S) << endl;
            S.next(players[j] -> play(S));
            j++;
            if(j == current_players){j = 0;}
        }
        out <<"State: " <<  S <<endl;
        if(j == 0){j = current_players;}
        out << *players[j-1] << " wins" << endl;
    }

private:
    Player **players;
    int *state;
    int max_heaps, max_players, current_heaps = 0, current_players = 0;
};

int main() {
    Game specker(3, 4);
    specker.addHeap(10);
    specker.addHeap(20);
    specker.addHeap(17);
    specker.addPlayer(new SneakyPlayer("Tom"));
    specker.addPlayer(new SpartanPlayer("Mary"));
    specker.addPlayer(new GreedyPlayer("Alan"));
    specker.addPlayer(new RighteousPlayer("Robin"));
    specker.play(cout);
}
