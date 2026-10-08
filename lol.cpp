#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <random>

using namespace std;

vector<string> moves = { "rock", "scissors", "paper" };  

array<array<string, 3>, 3> pictures = {
    {
        {
            // [0][0] Rock VS Rock
            R"(
    _______           _______
---'   ____)         (____   '---
      (_____)       (_____)
      (_____)       (_____)
      (____)         (____)
---.__(___)           (___)__.---
           Rock VS Rock
)",

// [0][1] Rock VS Scissor
R"(
    _______                           ____
---'   ____)               _____(____   '---
      (_____)            (_______
      (_____)          (__________)
      (____)                 (____)
---.(___)                   (___)__.---
           Rock VS Scissor
)",

// [0][2] Rock VS Paper
R"(
    _______                     _______
---'   ____)                   ____(____   '----
      (_____)               (______
      (_____)              (_______
      (____)                (_______
---.(___)                   (_________.---
           Rock VS Paper
)"
        },

        {
            // [1][0] Scissor VS Rock
            R"(
    _______                            _______
---'   ____)_____                (____   '---
          _________)             (_____)
       ______________)       (_____)
       _______)                     (____)
---.__(___)                        (___)__.---
           Scissor VS Rock
)",

// [1][1] Scissor VS Scissor
R"(
    _______                      _______
---'   _____)___            ____(____   '---
          _________)          (______
       __________)        (__________
      (____)                    (____)
---.__(___)                      (___)__.---
             Scissor VS Scissor
)",

// [1][2] Scissor VS Paper
R"(
    _______                            ______
---'   ____)______            (____   '----
          __________)        (______
       __________)           (_______
          (____)                   (_______
---.__(___)                      (____.---
           Scissor VS Paper
)"
        },

        {
            // [2][0] Paper VS Rock
            R"(
    _______                     ______
---'    ____)____           (___   '---
           _________)        (_____)
          _________)        (_____)
         _________)          (____)
---.__________)             (___)__.---
           Paper VS Rock
)",

// [2][1] Paper VS Scissor
R"(
    _______                              _______
---'    ____)____         ______(____   '---
           ________)       (_______
          _________)      (_________
         _________)            (____)
---.__________)               (___)__.---
           Paper VS Scissor
)",

// [2][2] Paper VS Paper
R"(
     _______                     _______
---'    ____)____           ____(____   '----
           ______)         (______
          _______)         (_______
         _______)           (_______
---.__________)                (_________.---
                Paper VS Paper
)"
        }
    }
};


int getComputerMove() {
    static random_device randomDevice;
    static mt19937 generator(randomDevice());

    uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(moves.size())- 1
    );

    int index = distribution(generator);

    return index;
} // 0 1 2

int main() {
    string playAgain = "yes";


    while (playAgain == "yes") {
        int pl1;

        cout << R"(
Choose number:

1. rock
2. scissors
3. paper

)";
        cout << "your fucking answereee: ";
        cin >> pl1; // 1
        int pl_in = pl1 - 1; // 0

        int com = getComputerMove();

        cout << "you:  " << moves[pl_in] << endl; // rock ..
        cout << "computer: " << moves[com] << endl; // rock ...
        cout << "fucking answer shit compute(indehhh): " << com << endl;
        cout << pictures[pl_in][com] << endl;

        if (pl_in == com) {
            cout << "Draw!" << endl;
        }
        else if ((pl_in == 0 && com == 1) or
            (pl_in == 1 && com == 2) or
            (pl_in == 2 && com == 0)) {
            cout << "win player" << endl;
        }
        else {
            cout << "win computer" << endl;
        }

        playAgain = "";

        while (playAgain != "yes") {
            cout << "Again? (yes/no)" << endl;
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


    return 0;
}
