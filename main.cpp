/* Mastermind
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Mastermind-pelin. Pelissä annetaan tai arvotaan
 * ensin salainen neljän värin sarja. Sama väri voi esiintyä sarjassa
 * useita kertoja, mutta mikään neljästä positiosta ei voi olla tyhjä.
 * Käyttäjä yrittää arvata, mitkä värit esiintyvät sarjassa ja missä
 * järjestyksessä. Tätä varten käyttäjä antaa oman neljän värin sarjansa,
 * ja ohjelma ilmoittaa, kuinka monta väriarvausta meni täysin oikein
 * (oikea väri oikeassa positiossa) sekä kuinka monta arvausta meni
 * pelkästään värin osalta oikein (oikea väri väärässä positiossa).
 * Tämän jälkeen käyttäjä voi tehdä uuden arvauksen jne.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla väreillä vai käyttäjän luettelemilla väreillä.
 * (Jälkimmäinen tapa ei ole kovin järkevä, mutta se on hyödyllinen
 * testauksen kannalta.) Ensimmäisessä vaihtoehdossa käyttäjältä kysytään
 * satunnaislukugeneraattorin siemenlukua ja jälkimmäisessä häntä
 * pyydetään syöttämään neljä väriä (värien alkukirjaimet eli neljän
 * merkin mittainen merkkijono).
 *   Joka kierroksella käyttäjältä kysytään uutta arvausta. Peli päättyy
 * pelaajan voittoon, jos arvaus menee jokaisen värin kohdalta täysin
 * oikein. Peli päättyy pelaajan häviöön, jos hän ei ole arvannut oikein
 * maksimimäärällä (10) arvauskertoja.
 *   Ohjelma tarkistaa, että annetut värit kuuluvat sallittujen värien
 * joukkoon. Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Nimi: Mikko Rajakorpi
 * Opiskelijanumero: 150464570
 * Käyttäjätunnus: pnmira
 * E-Mail: mikko.rajakorpi@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <colourseries.hh>

using namespace std;

// Maximum number of guesses
const unsigned int GUESS_MAX = 10; // Not in use, yet

// Number of colors in a series
const unsigned int SIZE = 4;

// Length of the suffix part when printing a row.
// The suffix consists of three vertical lines ('|') and two digits, where one
// tells the amount of totally correct colors and the other tells the amount
// of correct colors in incorrect positions.
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;

// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";

// Reads the input way, either random or listing way,
// and fills the color series in the user-desired way.
// Repeats the question until the user enters either R or L.
void get_input(ColourSeries& secret)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    if (input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;

        secret.createRandomColourSeries(seed);
    }
    else if (input_str == "L" or input_str == "l")
    {
        bool accepted = false;
        while(not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";
            string colors = "";
            cin >> colors;

            secret.createManualColourSeries(colors);

            // check for invalid input
            if(secret.getSize() != 4)
                cout << "Wrong size" << endl;
            else if (!secret.isValid())
                cout << "Unknown color" << endl;
            else {
                accepted = true;
            }
        }
    }
    else
    {
        cout << "Bad input" << endl;
        // Below the function itself is called recursively, which makes the
        // above code executed until an acceptable input_str is given,
        // but instead you can enclose the above code inside a loop structure.
        get_input(secret);
    }
}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Prints all the guesses
void printAll(const vector<ColourSeries>& gameboard)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);

    for(uint i = 1; i < gameboard.size(); i++)
    {
        const vector<int> feedback = gameboard.at(0).compare(gameboard.at(i));

        cout << "| "<< gameboard.at(i).getString() << " | " <<
                feedback.at(0) << " | " << feedback.at(1) << " |" << endl;
    }
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}

// Implements the actual game loop, where user-given guesses are read
// and compared to the secret row.
// On each round, all rows given so far are printed.
int main()
{
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());

    vector<ColourSeries> gameboard;
    ColourSeries secret;
    bool correctGuess = false;
    int usedGuesses = 0;

    get_input(secret);

    gameboard.push_back(secret);

    // Game loop
    while (not correctGuess)
    {
        string guess;

        cout << "ROW> ";
        cin >> guess;

        if (guess == "q" or guess == "Q")
            return 0;

        ColourSeries guessedColours;
        guessedColours.createManualColourSeries(guess);

        if (guessedColours.getSize() != 4)
            cout << "Wrong size" << endl;

        else if (!guessedColours.isValid())
            cout << "Unknown color" << endl;

        else
        {
            usedGuesses++;
            gameboard.push_back(guessedColours);
            printAll(gameboard);

            // Checking win/lose conditions
            if (secret.compare(guessedColours).at(0) == 4)
            {
                correctGuess = true;
                cout << "You won: Congratulations!" << endl;
            }
            else if (usedGuesses == GUESS_MAX)
            {
                cout << "You lost: Maximum number of guesses done" << endl;
                return 0;
            }
        }
    }

    return 0;
}

