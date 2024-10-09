/*  Lab 20: Modifying chair maker
    Objectives: Amend the code as follows:
        1. Change the default constructor. Instead of it assigning null values, we want it to randomly select 3 or 4 legs,
               and to randomly select prices (including dollars and cents) from $100.00 to $999.99.
        2. Change the parameter constructor. Now it has just one parameter, the number of legs.
                Make it have two parameters: number of legs, and an array of 3 doubles (the prices).
        3. In the third code block (starting at line 67), amend this such that the default constructors are used to populate these objects.
        4. Exercise your changes in main() with clear, easy-to-understand output.
*/

#include <iostream>
#include <iomanip>

using namespace std;
const int SIZE = 3;

int getRandomLegs();     // Returns random number of 3 or 4 legs
double getRandomPrice(); // Returns random price from 100.00 to 999.99

class Chair
{
private:
    int legs;
    double *prices;

public:
    // constructors
    Chair()
    {
        prices = new double[SIZE];
        legs = getRandomLegs(); // Modified to add random number of legs
        for (int i = 0; i < SIZE; i++)
            prices[i] = getRandomPrice(); // Modified to add random prices for each array element
    }
    Chair(int l, double *priceArray, int priceArraySize)
    {
        // Modified to accept array of prices and assign to object
        // Perform a deep copy in case pointer from main deletes array from main
        if (priceArraySize == SIZE)
        {
            for (unsigned int i = 0; i < priceArraySize; i++)
            {
                prices[i] = priceArray[i];
            }
        }
        legs = l;
    }

    // setters and getters
    void setLegs(int l) { legs = l; }
    int getLegs() { return legs; }

    void setPrices(double p1, double p2, double p3)
    {
        prices[0] = p1;
        prices[1] = p2;
        prices[2] = p3;
    }

    double getAveragePrices()
    {
        double sum = 0;
        for (int i = 0; i < SIZE; i++)
            sum += prices[i];
        return sum / SIZE;
    }

    void print()
    {
        cout << "CHAIR DATA - legs: " << legs << endl;
        cout << "Price history: ";
        for (int i = 0; i < SIZE; i++)
            cout << prices[i] << " ";
        cout << endl
             << "Historical avg price: " << getAveragePrices();
        cout << endl
             << endl;
    }

    // Destructor to deallocate price array on heap
    ~Chair()
    {
        delete[] prices;
    }
};

int main()
{
    cout << fixed << setprecision(2);

    // creating pointer to first chair object
    Chair *chairPtr = new Chair;
    chairPtr->setLegs(4);
    chairPtr->setPrices(121.21, 232.32, 414.14);
    chairPtr->print();

    // creating dynamic chair object with constructor
    Chair *livingChair = new Chair(3);
    livingChair->setPrices(525.25, 434.34, 252.52);
    livingChair->print();
    delete livingChair;
    livingChair = nullptr;

    // creating dynamic array of chair objects
    Chair *collection = new Chair[SIZE];
    collection[0].setLegs(4);
    collection[0].setPrices(441.41, 552.52, 663.63);
    collection[1].setLegs(4);
    collection[1].setPrices(484.84, 959.59, 868.68);
    collection[2].setLegs(4);
    collection[2].setPrices(626.26, 515.15, 757.57);
    for (int i = 0; i < SIZE; i++)
        collection[i].print();

    return 0;
}

// Returns random number of 3 or 4 legs
int getRandomLegs()
{
    return rand() % 2 + 3;
}

// Returns random price from 100.00 to 999.99
double getRandomPrice()
{
    return (rand() % (99999 - 10000 + 1) + 10000) / (double)100;
}