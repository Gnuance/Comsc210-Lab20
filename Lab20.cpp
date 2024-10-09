/*  Lab 20: Modifying chair maker
    Objectives: Amend the code as follows:
        1. Change the default constructor. Instead of it assigning null values, we want it to randomly select 3 or 4 legs,
               and to randomly select prices (including dollars and cents) from $100.00 to $999.99.
        2. Change the parameter constructor. Now it has just one parameter, the number of legs.
                Make it have two parameters: number of legs, and an array of 3 doubles (the prices).
        3. In the third code block (starting at line 67), amend this such that the default constructors are used to populate these objects.
        4. Exercise your changes in main() with clear, easy-to-understand output.

    Design decisions:
        1. For the parameter constructor, I used an array pointer as the parameter for the price array, but a normal array pass by value or by const &
                would work as well. I like the idea of passing by pointer or const & just in case the array is large. In this case it's only 3 values, but if it
                were 3,000 then it might make some difference. I also passed the size of the array as well. I know the assignment only said 2 parameters,
                but I'd like to make sure the array sizes match before copying data.
            a. Because it's a pointer, I performed a deep copy because the assumption is the original array data in main will be deleted.
        2. Added cout statements for each constructor section output, and added '$' for all of the price info.
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
    // I know the assignment said 2 parameters, but because an array has no bounds checking, I included the array size as a parameter.
    Chair(int l, const double *priceArray, int priceArraySize)
    {
        // Modified to accept array of prices and assign to object
        // Perform a deep copy in case pointer from main deletes array inside main
        prices = new double[SIZE];
        if (priceArraySize == SIZE) // Make sure arrays are same size before you try to assign
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
            cout << "$" << prices[i] << " ";
        cout << endl
             << "Historical avg price: $" << getAveragePrices();
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
    // Price array to pass to parameter constructor
    double *prices = new double[SIZE];
    cout << fixed << setprecision(2);

    // creating pointer to first chair object
    cout << "> Default no arg constructor to generate chair object:" << endl;
    Chair *chairPtr = new Chair;
    chairPtr->setLegs(4);
    chairPtr->setPrices(121.21, 232.32, 414.14);
    chairPtr->print();
    // Delet object from heap and nullify pointer
    delete chairPtr;
    chairPtr = nullptr;

    // creating dynamic chair object with constructor
    cout << "> Parameter constructor to generate chair object:" << endl;
    prices[0] = 525.25;
    prices[1] = 434.34;
    prices[2] = 252.52;
    Chair *livingChair = new Chair(3, prices, SIZE); // Because the array has no bounds checking, I included the array size as an argument.
    // livingChair->setPrices(525.25, 434.34, 252.52); // No longer needed
    livingChair->print();
    delete livingChair;
    livingChair = nullptr;

    // Modify to use default constructors
    // creating dynamic array of chair objects
    cout << "> Default constructor to generate chair objects with array:" << endl;
    Chair *collection = new Chair[SIZE];
    for (int i = 0; i < SIZE; i++)
        collection[i].print();

    // Clean up heap allocations
    delete[] prices;

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