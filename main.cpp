#include "searchObj.cpp"

void FetchCabs(double x, double y)
{
    SearchObj obj;
    obj.userlocation(x,y);
    // To read carList.json file.
    obj.json_parser();
    obj.printTop5();

}

int main()
{   //Enter x and y here.
    FetchCabs(12.9611159,77.6362214);
    return 0;
}


