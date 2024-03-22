#include<iostream>
 
enum week{Mon, Tue, Wed, Thur, Fri, Sat, Sun};
enum cities { Taipei, Tainan, Taichung, };

int main()
{
    enum week day;
    std::cout<< day <<"\n";
    day = Wed;
    std::cout<< day <<"\n";

    enum cities city;
    city = Tainan;
    int zipcode[] = {
        [Taipei] = 100,
        [Tainan] = 700,
        [Taichung] = 400,
        //100, 700, 400, 21321
    };
    zipcode[Tue]=10000;

    std::cout<< zipcode[Tainan]<< "\n";
    return 0;
} 
