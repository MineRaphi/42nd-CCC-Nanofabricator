#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void) {
    ifstream file("in_level-1_2-large.txt");
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

        int j;

        // first line
        out << string(r, '-');
        out << '*';
        for (j=0; j<r; j++) {
            out << '-' << '*';
        }
        out << string(r, '-') << "\n";
         
        // top + middle
        for (int k=1; k<=r; k++) {
            out << string(r-k, '-') << '*' << '-';

            for (int l=0; l<k-1+r; l++) {
                out << 'O' << '-';
            }

            out << '*' << string(r-k, '-') << "\n";
        }

        // bottom
        for (int k=r-1; k>0; k--) {
            out << string(r-k, '-') << '*' << '-';

            for (int l=0; l<k-1+r; l++) {
                out << 'O' << '-';
            }

            out << '*' << string(r-k, '-') << "\n";
        }

        // last line
        out << string(r, '-');
        out << '*';
        for (j=0; j<r; j++) {
            out << '-' << '*';
        }
        out << string(r, '-') << "\n";

        out << "\n";
    }
}