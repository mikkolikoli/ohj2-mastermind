#include "colourseries.hh"

// Constructor
// Sets VALID_COLOURS constant to include all the possible colours
ColourSeries::ColourSeries():
    VALID_COLOURS({"B", "R", "Y", "G", "O", "V"})
{

}

// Creates a colour series from a seed given as parameter
void ColourSeries::createRandomColourSeries(int seed)
{
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(0, 5);

    for (int i = 0; i < 4; i++)
    {
        string randomColour = VALID_COLOURS[distr(gen)];
        series.push_back(randomColour);
    }
}

// Creates a colour series from a string given as parameter
void ColourSeries::createManualColourSeries(string colourSeries)
{
    series = {};

    // makes the string uppercase
    for (char& currentChar: colourSeries)
    {
        currentChar = toupper(currentChar);
    }

    // splits the string into individual 1 character long strings to be added to the vector series
    for (uint i = 0; i < colourSeries.length(); i++)
    {
        string colour(1, colourSeries.at(i));
        series.push_back(colour);
    }
}

// returns the colour series as a string that can be used to print it in main.cpp
string ColourSeries::getString() const
{
    string seriesString = 
        series.at(0) + " " + series.at(1) + " " + series.at(2) + " " + series.at(3);
    return seriesString;
}

// compares the colour series to another one given as parameter and returns
// a vector<int> that counts how many colours are on the correct place
// at index 0 and how many colours are in the colour series, but
// at the wrong place
vector<int> ColourSeries::compare(const ColourSeries& other) const
{
    vector<int> feedback = {0, 0};

    vector<string> otherSeries = other.getSeries();
    vector<string> seriesColoursLeft = {};
    vector<string> otherColoursLeft = {};

    // checks for colours at the right place
    for (int i = 0; i < 4; i++)
    {
        if (series.at(i) == otherSeries.at(i)) 
            feedback.at(0)++;

        else
        {
            seriesColoursLeft.push_back(series.at(i));
            otherColoursLeft.push_back(otherSeries.at(i));
        }
    }

    if (feedback.at(0) == 4)
        return feedback;

    // checks for correct colours at the wrong place
    for (const string& currentColour: seriesColoursLeft)
    {
        if (count(otherColoursLeft.begin(), otherColoursLeft.end(), currentColour))
        {
            feedback.at(1)++;

            // deletes the colour from otherColoursLeft so that it works with 3 duplicates in the guess
            // of which 1 is at the correct place and another one is at a wrong place
            auto colourIterator = find(otherColoursLeft.begin(), otherColoursLeft.end(), currentColour);
            otherColoursLeft.erase(colourIterator);
        }
    }

    return feedback;
}

// checks if the colours in the colour series are valid by checking if the
// colours are also in the VALID_COLOURS constant
bool ColourSeries::isValid()
{
    bool valid = true;

    for (const string& colour: series)
    {
        if (!count(VALID_COLOURS.begin(), VALID_COLOURS.end(), colour))
            valid = false;
    }

    return valid;
}

// returns the vector
// needed for the compare method
vector<string> ColourSeries::getSeries() const
{
    return series;
}

// returns the size of the vector
// used to check if the colour series is the correct size
int ColourSeries::getSize() const
{
    return series.size();
}
