"Base Ride Class"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance fareAmount |

    Ride class >> new: id pickup: p dropoff: d distance: dist [
        ^self new initialize: id pickup: p dropoff: d distance: dist
    ]

    initialize: id pickup: p dropoff: d distance: dist [
        rideID := id.
        pickupLocation := p.
        dropoffLocation := d.
        distance := dist.
        fareAmount := 0.
    ]

    calculateFare [
        fareAmount := distance * 1.0.
    ]

    rideDetails [
        Transcript show: 'Ride ID: ', rideID printString, ', Pickup: ', pickupLocation,
                        ', Dropoff: ', dropoffLocation, ', Distance: ', distance printString,
                        ', Fare: $', fareAmount printString; cr.
    ]
]

"Standard Ride Subclass"
Ride subclass: StandardRide [
    calculateFare [
        fareAmount := distance * 1.5.
    ]
]

"Premium Ride Subclass"
Ride subclass: PremiumRide [
    calculateFare [
        fareAmount := distance * 3.0.
    ]
]

"Driver Class"
Object subclass: Driver [
    | driverID name rating assignedRides |

    Driver class >> new: id name: n rating: r [
        ^self new initialize: id name: n rating: r
    ]

    initialize: id name: n rating: r [
        driverID := id.
        name := n.
        rating := r.
        assignedRides := Array new.
    ]

    addRide: ride [
        assignedRides := assignedRides copyWith: ride.
    ]

    getDriverInfo [
        Transcript show: 'Driver ID: ', driverID printString, ', Name: ', name, ', Rating: ', rating printString; cr.
        Transcript show: 'Assigned Rides:'; cr.
        assignedRides do: [:r | r rideDetails].
    ]
]

"Rider Class"
Object subclass: Rider [
    | riderID name requestedRides |

    Rider class >> new: id name: n [
        ^self new initialize: id name: n
    ]

    initialize: id name: n [
        riderID := id.
        name := n.
        requestedRides := Array new.
    ]

    requestRide: ride [
        requestedRides := requestedRides copyWith: ride.
    ]

    viewRides [
        Transcript show: 'Rider ID: ', riderID printString, ', Name: ', name; cr.
        Transcript show: 'Requested Rides:'; cr.
        requestedRides do: [:r | r rideDetails].
    ]
]

"Sample Execution"
| ride1 ride2 driver1 rider1 rides |
ride1 := StandardRide new: 101 pickup: 'A' dropoff: 'B' distance: 10.
ride2 := PremiumRide new: 102 pickup: 'C' dropoff: 'D' distance: 5.

rides := {ride1. ride2}.
rides do: [:r | r calculateFare. r rideDetails].

driver1 := Driver new: 1 name: 'John Doe' rating: 4.8.
driver1 addRide: ride1.
driver1 addRide: ride2.
driver1 getDriverInfo.

rider1 := Rider new: 201 name: 'Alice'.
rider1 requestRide: ride1.
rider1 requestRide: ride2.
rider1 viewRides.
