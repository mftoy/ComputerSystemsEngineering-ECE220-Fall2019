#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name){name_ = name;}
string Shape::getName(){return name_;}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here


double Rectangle::getArea()const{return width_*length_;}
double Rectangle::getVolume() const { return 0;}
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
  width_ = width;
  length_ = length;
}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}
Rectangle Rectangle::operator + (const Rectangle& rec){
  double l = length_ + rec.getLength();
  double w = width_ + rec.getWidth();
  Rectangle* shape_ptr = new Rectangle(w,l);
  return *shape_ptr;
}
Rectangle Rectangle::operator - (const Rectangle& rec){
  double l = length_ - rec.getLength();
  double w = width_ - rec.getWidth();
  if(l<0) {l=0;}
  if(w<0){w=0;}
  Rectangle* shape_ptr = new Rectangle(w,l);
  return *shape_ptr;
}

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

double Circle::getRadius()const{return radius_;}
Circle::Circle(double radius):Shape("Circle"){
  radius_ = radius;
}
double Circle::getArea()const{return M_PI*radius_*radius_;}
double Circle::getVolume() const { return 0;}
Circle Circle::operator + (const Circle& cir){
  double r = radius_+cir.getRadius();
  Circle* shape_ptr = new Circle(r);
  return *shape_ptr;
}
Circle Circle::operator - (const Circle& cir){
  double r = radius_ - cir.getRadius();
  if (r<0){r=0;}
  Circle *shape_ptr = new Circle(r);
  return *shape_ptr;
}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here



double Sphere::getRadius()const{return radius_;}
Sphere::Sphere(double radius):Shape("Sphere"){
  radius_ = radius;
}
double Sphere::getArea() const {return 4*M_PI*radius_*radius_;}
double Sphere::getVolume() const { return (4.0/3.0)*radius_*radius_*radius_*M_PI;}
Sphere Sphere::operator + (const Sphere& sph){
  double r = radius_ + sph.getRadius();
  Sphere* shape_ptr = new Sphere (r);
  return *shape_ptr;
}
Sphere Sphere::operator - (const Sphere& sph){
  double r = radius_ - sph.radius_;
  if(r<0){r=0;}
  Sphere* shape_ptr = new Sphere (r);
  return *shape_ptr;
}


//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here


double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
  width_ = width;
  length_ = length;
  height_ = height;
}
double RectPrism::getArea() const {return 2*(length_*width_+length_*height_+width_*height_);}
double RectPrism::getVolume() const { return width_*length_*height_;}
RectPrism RectPrism::operator + (const RectPrism& rectp){
  double w = width_ + rectp.getWidth();
  double l = length_ + rectp.getLength();
  double h = height_ + rectp.getHeight();
  RectPrism* shape_ptr = new RectPrism(w,l,h);
  return *shape_ptr;
}
RectPrism RectPrism::operator - (const RectPrism& rectp){
  double w = width_ - rectp.getWidth();
  double l = length_ - rectp.getLength();
  double h = height_ - rectp.getHeight();
  if(w<0){w=0;}
  if(l<0){l=0;}
  if(h<0){h=0;}
  RectPrism* shape_ptr = new RectPrism(w,l,h);
  return *shape_ptr;
}

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here

  int num;

  ifstream ifs (file_name,std::ifstream::in);
  ifs >> num;
  vector<Shape*> master;

  for(num;num>0;num--){
    string name;
    ifs >> name;

    if(name == "Circle"){
      double r;
      ifs >> r;
      Shape* shape_ptr = new Circle(r);
      master.push_back(shape_ptr);
    }
    else if (name == "Rectangle"){
      double w, l;
      ifs >> w >> l;
      Shape* shape_ptr = new Rectangle(w,l);
      master.push_back(shape_ptr);

    }
    else if (name == "Sphere"){
      double r;
      ifs >> r;
      Shape* shape_ptr = new Sphere (r);
      master.push_back(shape_ptr);

    }
    else if (name == "RectPrism"){
      double w, l,h;
      ifs >> w >> l >> h;
      Shape* shape_ptr = new RectPrism(w,l,h);
      master.push_back(shape_ptr);
    }
  }
  ifs.close();
	return master; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  int i;
  max_area=shapes[0]->getArea();
  for(i = 1;i<shapes.size();i++){
    if(shapes[i]->getArea() > max_area){
      max_area = shapes[i]->getArea();
    }
  }

	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  max_volume = shapes[0]->getVolume();
  int i;
  for (i = 1;i<shapes.size();i++){
    if(shapes[i]->getVolume() > max_volume){
      max_volume = shapes[i]->getVolume();
    }
  }

	return max_volume;
}
