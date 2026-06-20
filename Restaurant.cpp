#include "Restaurant.h"
#include<iostream>
using namespace std ;
Restaurant::Restaurant():breakfastMenu("not set"),dinnerMenu("not set"),mealsServedToday(0){}
Restaurant::Restaurant(const string& breakfast,const string& lunch,const string& dinner)
:breakfastMenu(breakfast),lunchMenu(lunch),dinnerMenu(dinner),mealsServedToday(0){}
void Restaurant::setBreakfastMenu(const string& menu) { breakfastMenu = menu; }
void Restaurant::setLunchMenu(const string& menu)     { lunchMenu = menu; }
void Restaurant::setDinnerMenu(const string& menu)    { dinnerMenu = menu; }string Restaurant::getBreakfastMenu() const    { return breakfastMenu; }
string Restaurant::getLunchMenu() const        { return lunchMenu; }
string Restaurant::getDinnerMenu() const       { return dinnerMenu; }
int Restaurant::getMealsServedToday() const    { return mealsServedToday; }
void Restaurant::serveMeal() {
    mealsServedToday++;
}
 
void Restaurant::resetDailyCount() {
    mealsServedToday = 0;
    cout << "Daily meal count has been reset!" << endl;
}

void Restaurant::displayMenu() const {
    cout << "-------- Today's Menu --------" << endl;
    cout << "Breakfast : " << breakfastMenu << endl;
    cout << "Lunch     : " << lunchMenu     << endl;
    cout << "Dinner    : " << dinnerMenu    << endl;
    cout << "Meals served today: " << mealsServedToday << endl;
    cout << "------------------------------" << endl;
}
 