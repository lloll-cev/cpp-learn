#include <iostream>
#include <vector>
#include <random>
#include <string>


using namespace std;

vector<int> dc = { 1, 2, 3, 4, 5, 6 };

int getRandomNumber() {
    static random_device randomDevice;
    static mt19937 generator(randomDevice());

    uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(dc.size()) - 1
    );

    int index = distribution(generator);

    return dc[index];
}

string p1name = "";
string p2name = "";
int lead1 = 0;
int lead2 = 0;



void showLeaderboard() {
    cout << "\nLEADERBOARD\n";
    cout << p1name  << " " << lead1 << " scores\n";
    cout << p2name  << " " << lead2 << " scores\n";
    cout << "================\n\n";
}

int main() {
    cout << "Enter first player name: ";
    cin >> p1name;
    cout << "Enter second player name: ";
    cin >> p2name;

    string playAgain = "yes";

    while (playAgain == "yes") {
        int p1 = getRandomNumber();
        int p2 = getRandomNumber();
        cout << p1name << ": " << p1 << "\n" << p2name << ": "<< p2 << "\n";
        if (p1 > p2) {
            cout << "Winner: " << p1name << " \nWITHU NUMBA YUMBA:\n"<< p1 << "\n";
            lead1 += 3;
        }
        else if (p1 == p2) {
            cout << "DRAW LOSHARI\n";
            lead1 += 1;
            lead2 += 1;
        }
        else {
            cout << "Winner: " << p2name << " \nWITHU NUMBA LUBMA:\n"<< p2 << "\n";
            lead2 += 3;
        }

        showLeaderboard();

        playAgain = " ";
        while (playAgain != "yes") {
            cout << "Play again?" << endl;
            string answer;
            cin >> answer;

            for (char& character : answer) {
                character = static_cast<char>(
                    tolower(
                        static_cast<unsigned char>(character)
                    )
                    );
            }
            playAgain = answer;

            if (playAgain == "no") {
                break;
            }
        }

    }
    cout << "\nFinally Leaderboard\n";
    showLeaderboard();
    return 0;
}