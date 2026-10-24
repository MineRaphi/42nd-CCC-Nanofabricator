#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void createBoard(int r);

int main(void) {
    ifstream file("in_level-4_2-large.txt");
    if (!file) {
        cerr << "Couldn't open input file\n";
        return 1;
    }

    ofstream out("output.txt");
    if (!out) {
        cerr << "Couldn't open output file\n";
        return 1;
    }

    int n;

    file >> n;

    for (int i=0; i<n; i++) {
        int r;

        file >> r;

        createBoard(r);

        int c;
        file >> c;

        ifstream tmp("tmp.txt");
        if (!tmp) {
            cerr << "Couldn't open tmp file\n";
            return 1;
        }

        int rows = 2*r+1;
        int cols = 4*r+1;

        char board[2*r+1][4*r+1];

        for (int i=0; i<2*r+1; i++) {
            for(int j=0; j<4*r+1; j++) {
                tmp >> board[i][j];
            }
        }

        tmp.close();

        int posx[6] = { 0, r, cols-1-r, cols-1, cols-1-r, r };
        int posy[6] = { r, 0, 0, r, rows-1, rows-1 };
        bool on[6] = { false, false, false, false, false, false };

        for (int j=0; j<c; j++) {
            char inst;
    
            for (int k=0; k<6; k++) {
                file >> inst;

                if (inst == '-') {
                    continue;;
                }
                else if (inst == 'T') {
                    on[k] = !on[k];
                }
                else if (inst == 'F') {
                    if (posx[k] == 0) {
                        posx[k]++;
                        posy[k]--;
                    }
                    else if (posx[k] == cols-1) {
                        posx[k]--;
                        posy[k]++;
                    }
                    else if (posy[k] < r) {
                        if (posx[k]+2 < cols && board[posy[k]][posx[k]+2] == '*') {
                            posx[k]+=2;
                        }
                        else if (posy[k]-1 >= 0 && posx[k]+1 < cols && board[posy[k]-1][posx[k]+1] == '*') {
                            posx[k]++;
                            posy[k]--;
                        }
                        else if (posy[k]+1 < rows && posx[k]+1 < cols && board[posy[k]+1][posx[k]+1] == '*') {
                            posx[k]++;
                            posy[k]++;
                        }
                    }
                    else if (posy[k] > r) {
                        if (posx[k]-2 >= 0 && board[posy[k]][posx[k]-2] == '*') {
                            posx[k]-=2;
                        }
                        else if (posy[k]-1 >= 0 && posx[k]-1 >= 0 && board[posy[k]-1][posx[k]-1] == '*') {
                            posx[k]--;
                            posy[k]--;
                        }
                        else if (posy[k]+1 < rows && posx[k]-1 >= 0 && board[posy[k]+1][posx[k]-1] == '*') {
                            posx[k]--;
                            posy[k]++;
                        }
                    }
                }
                else if (inst == 'B') {
                    if (posx[k] == 0) {
                        posx[k]++;
                        posy[k]++;
                    }
                    else if (posx[k] == cols-1) {
                        posx[k]--;
                        posy[k]--;
                    }
                    else if (posy[k] < r) {
                        if (posx[k]-2 >= 0 && board[posy[k]][posx[k]-2] == '*') {
                            posx[k]-=2;
                        }
                        else if (posy[k]+1 < rows && posx[k]-1 >= 0 && board[posy[k]+1][posx[k]-1] == '*') {
                            posx[k]--;
                            posy[k]++;
                        }
                        else if (posy[k]-1 >= 0 && posx[k]-1 >= 0 && board[posy[k]-1][posx[k]-1] == '*') {
                            posx[k]--;
                            posy[k]--;
                        }
                    }
                    else if (posy[k] > r) {
                        if (posx[k]+2 < cols && board[posy[k]][posx[k]+2] == '*') {
                            posx[k]+=2;
                        }
                        else if (posy[k]+1 < rows && posx[k]+1 < cols && board[posy[k]+1][posx[k]+1] == '*') {
                            posx[k]++;
                            posy[k]++;
                        }
                        else if (posy[k]-1 >= 0 && posx[k]+1 < cols && board[posy[k]-1][posx[k]+1] == '*') {
                            posx[k]++;
                            posy[k]--;
                        }
                    }
                }
                else {
                    cout << "something went wrong";
                    return 1;
                }
            }
            
            int power[rows][cols];

            for (int i=0; i<rows; i++) {
                for(int j=0; j<cols; j++) {
                    power[i][j] = 0;
                }
            }

            for (int k=0; k<6; k++) {
                int x = posx[k];
                int y = posy[k];

                if (on[k] == false) {
                    continue;
                }
                
                switch (k)
                {
                case 0:
                    while(x >= 0 && y >= 0 && x < cols && y < rows) {
                        x+=2;
                        if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                        power[y][x]++;
                    }
                    break;
                case 1:
                    while(x >= 0 && y >= 0 && x < cols && y < rows) {
                        x++;
                        y++;
                        if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                        power[y][x]++;
                    }
                    break;
                case 2:
                    while(x >= 0 && y >= 0 && x < cols && y < rows) {
                        x--;
                        y++;
                        if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                        power[y][x]++;
                    }
                    break;
                case 3:
                    while(x >= 0 && y >= 0 && x < cols && y < rows) {
                        x-=2;
                        if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                        power[y][x]++;
                    }
                    break;
                case 4:
                    while(x >= 0 && y >= 0 && x < cols && y < rows) {
                        x--;
                        y--;
                        if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                        power[y][x]++;
                    }
                    break;
                case 5:
                    while(x >= 0 && y >= 0 && x < cols && y < rows) {
                        x++;
                        y--;
                        if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                        power[y][x]++;
                    }
                    break;
                }
            }
        
            for (int i=0; i<rows; i++) {
                for(int j=0; j<cols; j++) {
                    if (board[i][j] == 'M' || board[i][j] == 'O') {
                        if (power[i][j] == 2) {
                            board[i][j] = 'M';
                        }
                        else if (power[i][j] > 2) {
                            board[i][j] = 'O';
                        }
                    }
                }
            }
        }

        for (int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                out << board[i][j];
            }
            out << "\n";
        } 
        out << "\n";
    }
}

void createBoard(int r) {
    ofstream tmp("tmp.txt");
    if (!tmp) {
        cerr << "Couldn't open tmp file\n";
        return;
    }

    int j;

    // first line
    tmp << string(r, '-');
    tmp << '*';
    for (j=0; j<r; j++) {
        tmp << '-' << '*';
    }
    tmp << string(r, '-') << "\n";
        
    // top + middle
    for (int k=1; k<=r; k++) {
        tmp << string(r-k, '-') << '*' << '-';

        for (int l=0; l<k-1+r; l++) {
            tmp << 'O' << '-';
        }

        tmp << '*' << string(r-k, '-') << "\n";
    }

    // bottom
    for (int k=r-1; k>0; k--) {
        tmp << string(r-k, '-') << '*' << '-';

        for (int l=0; l<k-1+r; l++) {
            tmp << 'O' << '-';
        }

        tmp << '*' << string(r-k, '-') << "\n";
    }

    // last line
    tmp << string(r, '-');
    tmp << '*';
    for (j=0; j<r; j++) {
        tmp << '-' << '*';
    }
    tmp << string(r, '-') << "\n";

    tmp << "\n";
}