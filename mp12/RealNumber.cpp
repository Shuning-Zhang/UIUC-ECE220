#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    /* Your code here */
    real_component=0.0;
    magnitude = 0.0;
    phase = 0.0;
    number_type = REAL;
}

RealNumber::RealNumber(double rval)
{
    /* Your code here */
    real_component = rval;
    magnitude = abs(rval);
    phase = calculate_phase(rval, 0.0);
    number_type = REAL;
}

RealNumber::RealNumber( const RealNumber& other )
{//set up the other number type
    /* Your code here */
    real_component = other.get_real_component();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    number_type = REAL;
}

void RealNumber::set_real_component (double rval)
{
    /* Your code here */
    real_component = rval;
    magnitude = abs(rval);
    phase = calculate_phase(rval, 0.0);
}

double RealNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

double RealNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component + arg.get_real_component());
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component - arg.get_real_component());
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component * arg.get_real_component());
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component / arg.get_real_component());
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
    double real  = real_component;
    double img = 0 + arg.get_imaginary_component();
  return ComplexNumber(real, img);
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */

    double real = real_component;
    double img = 0 - arg.get_imaginary_component();
	return ComplexNumber(real, img);
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
    return ImaginaryNumber(real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
    return ImaginaryNumber(real_component / arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */

    double real = real_component + arg.get_real_component();
    double img = 0 + arg.get_imaginary_component();
	return ComplexNumber(real,img);

}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
    double real = real_component - arg.get_real_component();
    double img = 0 - arg.get_imaginary_component();
    return ComplexNumber(real,img);
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
    double real = real_component * arg.get_real_component();
    double img = real_component * arg.get_imaginary_component();
    return ComplexNumber(real,img);
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
    double b= arg.get_real_component();
    double a = real_component, c =arg.get_imaginary_component();
    double real = (a*b)/((b*b)+(c*c));
    double img =  (-1*a*c)/((c*c)+(b*b));
    return ComplexNumber(real,img);
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}
