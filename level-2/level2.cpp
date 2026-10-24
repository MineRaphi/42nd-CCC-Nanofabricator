#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void) {
    ifstream file("in_level-2_2-large.txt");
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
        int r, rows, cols;
        file >> r;
        file >> rows;
        file >> cols;

        char grid[rows][cols];

        for (int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                file >> grid[i][j];
            }
        }

        int x = 0;
        int y = r;
        bool found = false;

        int fx, fy;

        for (int i=0; i<rows && !found; i++) {
            for(int j=0; j<cols && !found; j++) {
                if (grid[i][j] != '-' && grid[i][j] != '*' && grid[i][j] != 'O') {
                    fy = i;
                    fx = j;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cerr << "FUCK!";
            return 1;
        }

        
        int dir = grid[fy][fx] - '0';
        
        x = fx;
        y = fy;

        switch (dir)
        {
        case 1:
            while(x >= 0 && y >= 0 && x < cols && y < rows) {
                x+=2;
                if (grid[y][x] == 'O') {
                    grid[y][x] = 'M';
                }
            }
            break;
        case 2:
            while(x >= 0 && y >= 0 && x < cols && y < rows) {
                x++;
                y++;
                if (grid[y][x] == 'O') {
                    grid[y][x] = 'M';
                }
            }
            break;
        case 3:
            while(x >= 0 && y >= 0 && x < cols && y < rows) {
                x--;
                y++;
                if (grid[y][x] == 'O') {
                    grid[y][x] = 'M';
                }
            }
            break;
        case 4:
            while(x >= 0 && y >= 0 && x < cols && y < rows) {
                x-=2;
                if (grid[y][x] == 'O') {
                    grid[y][x] = 'M';
                }
            }
            break;
        case 5:
            while(x >= 0 && y >= 0 && x < cols && y < rows) {
                x--;
                y--;
                if (grid[y][x] == 'O') {
                    grid[y][x] = 'M';
                }
            }
            break;
        case 6:
            while(x >= 0 && y >= 0 && x < cols && y < rows) {
                x++;
                y--;
                if (grid[y][x] == 'O') {
                    grid[y][x] = 'M';
                }
            }
            break;

        }

        for (int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                out << grid[i][j];
            }
            out << "\n";
        } 
        out << "\n";
    }
}