class TeaBreak
{
public:
    virtual ~TeaBreak() {}

    // Return minutes taken to make the drinks
    int morningTea();


protected:
    virtual int makeCoffee(bool milk, double sugars) = 0;
    virtual int makeHerbalTea() = 0;
};
