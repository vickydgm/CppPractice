#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class Salesperson
{
   public:
   Salesperson( const string& name = "", int sales = 0,int district = 0 );
   bool operator>( const Salesperson& rhs ) const;
   void print() const;

   private:
   int district_;
   string name_;
   int sales_;
};

inline
Salesperson::Salesperson( const string& name, int sales,
   int district )
   : district_( district ), name_( name ), sales_( sales )
{} 

inline
bool Salesperson::operator>( const Salesperson& rhs ) const
{ return sales_ > rhs.sales_; }

inline
void Salesperson::print() const
{ cout << name_ << " from District " << district_
   << " has sales of $" << sales_ << endl;
}

int main( )
{
   list<Salesperson> list1;
   list1.push_back( Salesperson( "A", 37000, 1 ) );
   list1.push_back( Salesperson( "B", 49000, 1 ) );
   list1.push_back( Salesperson( "C", 48500, 1 ) );

   // sort District 1 salespeople in descending order and display
   list1.sort( greater<Salesperson>() );
   //for_each( list1.begin(), list1.end(), mem_fun_ref( &Salesperson::print ) ); depricated in c++17
   for_each( list1.begin(), list1.end(), mem_fn( &Salesperson::print ) );

   list<Salesperson> list2;
   list2.push_back( Salesperson( "A", 65000, 2 ) );
   list2.push_back( Salesperson( "B", 33000, 2 ) );
   list2.push_back( Salesperson( "C", 47000, 2 ) );

   // sort District 2 salespeople in descending order and display
   list2.sort( greater<Salesperson>() );
   for_each( list2.begin(), list2.end(), mem_fn( &Salesperson::print ) );

}