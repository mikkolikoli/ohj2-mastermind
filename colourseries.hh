/* ColourSeries luokka:
 *
 * Luokka hallitsee yksittäisten värisarjojen toiminnallisuutta.
 * Tämä sisältää värisarjan luomisen joko manuaalisella tai
 * satunnaisella tavalla, tämän vertaaminen muuhun värisarjaan
 * sekä muita pienempiä apumethodeja.
 *
 * Nimi: Mikko Rajakorpi
 * Opiskelijanumero: 150464570
 * Käyttäjätunnus: pnmira
 * E-Mail: mikko.rajakorpi@tuni.fi
 *
*/

#ifndef COLOURSERIES_HH
#define COLOURSERIES_HH

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class ColourSeries
{
public:
    ColourSeries();

    void createRandomColourSeries(int seed);
    void createManualColourSeries(string colourSeries);

    string getString() const;
    vector<int> compare(const ColourSeries& other) const;
    bool isValid();
    vector<string> getSeries() const;
    int getSize() const;

private:
    vector<string> series;
    const vector<string> VALID_COLOURS;
};

#endif // COLOURSERIES_HH
