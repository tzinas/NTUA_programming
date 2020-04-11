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
