#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base Ride Class
class Ride {
protected:
    int rideID;
    string pickupLocation;
    string dropoffLocation;
    double distance;
    double fareAmount;

public:
    Ride(int id, string pickup, string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist), fareAmount(0) {}

    // Polymorphic fare calculation
    virtual void calculateFare() {
        fareAmount = distance * 1.0; // base fare
    }

    virtual void rideDetails() {
        cout << "Ride ID: " << rideID << ", Pickup: " << pickupLocation 
             << ", Dropoff: " << dropoffLocation << ", Distance: " << distance 
             << " miles, Fare: $" << fareAmount << endl;
    }

    virtual ~Ride() {}
};

// Standard Ride subclass
class StandardRide : public Ride {
public:
    StandardRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    void calculateFare() override {
        fareAmount = distance * 1.5; // Standard rate
    }
};

// Premium Ride subclass
class PremiumRide : public Ride {
public:
    PremiumRide(int id, string pickup, string dropoff, double dist)
        : Ride(id, pickup, dropoff, dist) {}

    void calculateFare() override {
        fareAmount = distance * 3.0; // Premium rate
    }
};

// Driver class
class Driver {
private:
    int driverID;
    string name;
    double rating;
    vector<Ride*> assignedRides; // Encapsulation: private

public:
    Driver(int id, string n, double r) : driverID(id), name(n), rating(r) {}

    void addRide(Ride* ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() {
        cout << "Driver ID: " << driverID << ", Name: " << name << ", Rating: " << rating << endl;
        cout << "Assigned Rides:" << endl;
        for (Ride* ride : assignedRides) {
            ride->rideDetails();
        }
    }
};

// Rider class
class Rider {
private:
    int riderID;
    string name;
    vector<Ride*> requestedRides;

public:
    Rider(int id, string n) : riderID(id), name(n) {}

    void requestRide(Ride* ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() {
        cout << "Rider ID: " << riderID << ", Name: " << name << endl;
        cout << "Requested Rides:" << endl;
        for (Ride* ride : requestedRides) {
            ride->rideDetails();
        }
    }
};

// Main function to demonstrate
int main() {
    // Create rides
    StandardRide ride1(101, "A", "B", 10);
    PremiumRide ride2(102, "C", "D", 5);

    // Calculate fares (demonstrating polymorphism)
    vector<Ride*> rides = { &ride1, &ride2 };
    for (Ride* r : rides) {
        r->calculateFare();
        r->rideDetails();
    }

    // Create driver and assign rides
    Driver driver1(1, "John Doe", 4.8);
    driver1.addRide(&ride1);
    driver1.addRide(&ride2);
    driver1.getDriverInfo();

    // Create rider and request rides
    Rider rider1(201, "Alice");
    rider1.requestRide(&ride1);
    rider1.requestRide(&ride2);
    rider1.viewRides();

    return 0;
}
