
class Vehicle
{
  public:
    Vehicle (string idNum)
    {
        m_id = idNum;
    }
    virtual ~Vehicle();
    string id() const; // all vehicles have ID strings
    virtual string description() const = 0; // makes vehicle an ABC and cannot ask for description of a plain vehicle
    virtual bool canHover() const {return true;}
    
  private:
    string m_id;
};

Vehicle::~Vehicle()
{}
string Vehicle::id() const
{
    return m_id;
}



class Drone : public Vehicle
{
  public:
    Drone(string x);
    virtual ~Drone()
    {
        cout << "Destroying " << id() << ", " << description() << endl;
    }

    virtual string description() const
    {
        return "a Drone";
    }
};

Drone::Drone(string x)
: Vehicle(x)
{
    // do i even need a constructor for drone since it doesn't do anything other than initialize base class?
}



class Balloon : public Vehicle
{
  public:
    Balloon (string x, double d);
    virtual ~Balloon()
    {
        cout << "Destroying the balloon " << id() << endl;
    }

    virtual string description() const
    {
        if (m_d < 8)
            return "a small balloon";
        else
            return "a large balloon";
        
    }
  private:
    double m_d;
};

Balloon::Balloon(string x, double d)
: Vehicle(x) // must first initialize baseclass variables
{
    m_d = d; // initializes the extra private member of the diameter of balloons
}



class Satellite : public Vehicle
{
  public:
    Satellite(string x);
    virtual ~Satellite()
    {
        cout << "Destroying the satellite " << id() << endl;
    }
    virtual bool canHover() const
    {
        return false;
    }
    virtual string description() const
    {
        return "a satellite";
    }
};
Satellite::Satellite(string x)
: Vehicle(x)
{
    
}


