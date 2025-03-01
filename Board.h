#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

class BoardException: public std::exception{
    string mesaj;
public:
    BoardException(string msj):mesaj{msj}{};
    string get_message()
    {
        return mesaj;
    }
};

class Board{
private:
    int size;
    vector<vector<int>> board;
    int configuration;
    int moves;
    int status; // 0 = in progress; 1 = lost, 2 = won;
    int attacked; // when 9 positions are attacked, game is won
    void load_configuration(int config);

public:
    Board(int size, int configuration):size{size}{
        board = vector(size,vector<int>(size,0));
        moves=30;
        status=0;
        attacked=0;
        load_configuration(configuration);
    }
    int get_size() const{
        return size;
    };
    int get_coordinates(int row, int col)const{
        return board[row][col];
    }
    void attack_coordinates(int row, int col);

    int get_moves(){
        return moves;
    }

    int get_status(){
        return status;
    }

    int get_attacked(){
        return attacked;
    }

};