#define INF 0x3f3f3f3f

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
