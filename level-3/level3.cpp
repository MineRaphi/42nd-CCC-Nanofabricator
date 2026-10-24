#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void) {
    ifstream file("in_level-3_2-large.txt");
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
        int power[rows][cols];

        for (int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                file >> grid[i][j];
            }
        }

        for (int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                power[i][j] = 0;
            }
        }

        int found = 0;

        int fx[] = {0, 0, 0, 0, 0, 0};
        int fy[] = {0, 0, 0, 0, 0, 0};

        for (int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                if (grid[i][j] != '-' && grid[i][j] != '*' && grid[i][j] != 'O' && grid[i][j] != 'M') {
                    fy[found] = i;
                    fx[found] = j;
                    found++;
                }
            }
        }

        for (int i=0; i<6; i++) {
            if (fy[i] == 0 && fx[i] == 0) {
                break;
            }

            int x = fx[i];
            int y = fy[i];
            
            switch (grid[fy[i]][fx[i]])
            {
            case '1':
                while(x >= 0 && y >= 0 && x < cols && y < rows) {
                    x+=2;
                    if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                    power[y][x]++;
                }
                break;
            case '2':
                while(x >= 0 && y >= 0 && x < cols && y < rows) {
                    x++;
                    y++;
                    if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                    power[y][x]++;
                }
                break;
            case '3':
                while(x >= 0 && y >= 0 && x < cols && y < rows) {
                    x--;
                    y++;
                    if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                    power[y][x]++;
                }
                break;
            case '4':
                while(x >= 0 && y >= 0 && x < cols && y < rows) {
                    x-=2;
                    if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                    power[y][x]++;
                }
                break;
            case '5':
                while(x >= 0 && y >= 0 && x < cols && y < rows) {
                    x--;
                    y--;
                    if (x < 0 || y < 0 || x >= cols || y >= rows) break;
                    power[y][x]++;
                }
                break;
            case '6':
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
                if (grid[i][j] == 'M' || grid[i][j] == 'O') {
                    if (power[i][j] == 2) {
                        grid[i][j] = 'M';
                    }
                    else if (power[i][j] > 2) {
                        grid[i][j] = 'O';
                    }
                }
            }
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