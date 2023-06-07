#include <vector>
enum class pointPlace 
{
    INSIDE=2, 
    OUTSIDE=1,
    ON_EDGE=0
};

class Point{
    public:
        double X, Y;

        Point() = default;

        Point(double x, double y);

        pointPlace point_in_polygon(int point_number, std::vector<Point> p);
};

