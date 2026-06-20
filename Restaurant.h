#ifndef RESTAURANT_H
#define RESTAURANT_H
#include<string>
using namespace std ;
class Restaurant{
    private:
    string breakfastMenu;
    string lunchMenu;
    string dinnerMenu;
    int mealsServedToday;
public:
Restaurant();
Restaurant(const string& breakfast , const string& lunch, const string& dinner);
void setBreakfastMenu(const string& menu);
void setLunchMenu(const string& menu);
void setDinnerMenu(const string& menu);
string getBreakfastMenu()const ;
string getLunchMenu()const;
string getDinnerMenu()const;
int getMealsServedToday()const;
void serveMeal();
void resetDailyCount();
void displayMenu()const;

};



#endif