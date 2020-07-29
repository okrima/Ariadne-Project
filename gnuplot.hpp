/***************************************************************************
 *            output/gnuplot.hpp
 *
 *  
 *
 ****************************************************************************/
/*
 *  This file is part of Ariadne.
 *
 *  Ariadne is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne.  If not, see <https://www.gnu.org/licenses/>.
 */



#include "../output/graphics.hpp"
#include "../config.hpp"
#include "../utility/string.hpp"
#include <string>
#include <ctype.h>

#include "gnuplot-iostream.h"

namespace Ariadne{

enum _Colours // %c - es: lc, fc
{
    black,
    dark_grey,
    red,
    light_red,
    dark_red,
    web_blue,
    blue,
    light_blue,
    steelblue,
    green,
    dark_green,
    light_green,
    web_green,
    dark_spring_green,
    yellow,
    dark_yellow,
    magenta,
    light_magenta,
    dark_magenta,
    cyan,
    light_cyan,
    dark_cyan,
    dark_orange
};

const char *_colours[] = {"black", "dark-grey", "red", 
    "light-red", "dark-red", "web_blue", "blue", "light-blue",
    "steelblue", "green", "dark-green", "light-green", "web-green",
    "dark-spring-green", "yellow","dark-yellow", "magenta", 
    "light-magenta", "dark-magenta", "cyan", "light-cyan", 
    "dark-cyan", "dark-orange"};

enum _LineStyle2D // %s - es: ls, fs
{
    lines,
    linespoints, //lp
    //points,
    //dots,
    //steps,
    //impulses,

};

struct _Line2D
{
    _LineStyle2D style;
    const int lw = 1;
    const int ls = 1;
};

const char *_linestyle2D[] = {"lines", "linespoints"};// "points", "dots", "steps", "impulses"};

enum _LineStyle3D // %s - es: ls, fs
{
    lines,
    surface,
    points,
    //impulse,
    //solid   //pm3d
};

struct _Line3D
{
    _LineStyle3D style;
    const int lw = 1;
    const int ls = 1;
}

const char *_linestyle3D[] = {"lines", "surface", "point",/* "impulse", "solid"*/};

/*
enum _DimPlot
{
    Polar,  //s set polar w/ 2Dplot
    Dim2,   //plot
    Dim3    //splot
};
*/

enum _Format
{
    png,
    gif
};

const char *_format[] = {"png", "gif"};

struct _Size
{
    const int sizeX;
    const int sizeY;
};

/*
struct _Label2D
{
    const String title;
    const String xLabel;
    const String yLabel;
};
*/

/*
struct _Label3D
{
    const String title;
    const String xLabel;
    const String yLabel;
    const String zLabel;
};
*/

struct _Range2D
{
    const int Xmin = 0;
    const int Xmax;
    const int Ymin = 0;
    const int Ymax;
};

struct _Range3D
{
    const int Xmin = 0;
    const int Xmax;
    const int Ymin = 0;
    const int Ymax;
    const int Zmin = 0;
    const int Zmax;
};

struct Image2D
{
    _Colours colour;
    _Line2D linestyle2D;
    //const int linewidth;
    //_DimPlot dim;
    _Range2D range2D;
    _Size size;

};

struct Image3D
{
    _Colours colour;
    _Line3D linestyle3D;
    //const int linewidth;
    //_DimPlot dim;
    _Range3D range3D;
    _Size size;
    
};

//Command
// show colorname
// test

class GnuplotCanvas
{
private:
    //Image2D *Image2D;
    //Image3D *image3D;
    //double lw, dr;  // Line width and Dot radius
    //Colour lc, fc;  // Line colour and Fill colour
protected:  
    bool noCanvas = true;
public:
    ~GnuplotCanvas();
    // Constructors - Create the canvas
    //Create empty canvas
    GnuplotCanvas();
    //Create canvas with dimensions
    GnuplotCanvas(const Image2D& image, const int sizeX, const int sizeY);
    GnuplotCanvas(const Image3D& image, const int sizeX, const int sizeY);
    // 2D Plot
    void plot2D(Image2D& image, Array<double> data); // Fix gp.send1D
    // 3D Plot
    void plot3D(Image3D& image, Matrix<double> data); // Fix gp.send
    // Set Terminal output 2D
    void setTerminal(Gnuplot& gp, Image2D& image, _Format format, String nameFile);
    // Set Terminal output 3D
    void setTerminal(Gnuplot& gp, Image3D& image, _Format format, String nameFile)
    // Set Title and Label
    void setLabels(Gnuplot& gp, String xLabel);
    void setLabels(Gnuplot& gp, String yLabel);
    void setLabels(Gnuplot& gp, String zLabel);
    void setLabels(Gnuplot& gp, String title);
    void setLabels(Gnuplot& gp, String xLabel, String yLabel, String zLabel);
    void setLabels(Gnuplot& gp, String xLabel, String yLabel, String zLabel, String title);
    // Set X, Y range
    void setRange2D(Gnuplot& gp, Image2D& image, const int maxX, const int maxY);
    // Set X, Y range
    void setRange2D(Gnuplot& gp, Image2D& image, const int minX, const int maxX, 
                const int minY, const int maxY);
    // Set X, Y, Z range
    void setRange3D(Image3D& image, const int minX, const int maxX, 
                const int minY, const int maxY,
                const int minZ, const int maxZ);
    // Set Line style with parameter
    void setLineStyle(Image2D& image, _Line2D line, const int ls, const int lw);
    // Set line with parameter
    void setLineStyle(Image3D& image, _Line3D line, const int ls, const int lw);
    // set surface with no parameter
    void setLineStyle(Image3D& image, _Line3D line);
    // Set Colour
    void setColour(Image2D& image, _Colours color);
    // Set colour with '#abcdef'
    void setColour(Image2D& image, String color);
    // Set X Log axis
    void setXLogAxis(Gnuplot& gp);
    // Set Y Log axis
    void setYLogAxis(Gnuplot& gp);
    // Set XY Log axis
    void setXYLogAxis(Gnuplot& gp);
    // Set XZ Log axis
    void setXZLogAxis(Gnuplot& gp);
    // Set YZ Log axis
    void setYZLogAxis(Gnuplot& gp);
    // Set XYZ Log axis
    void setXYZLogAxis(Gnuplot& gp);
    // Set Legend
    void setLegend(Gnuplot& gp);
    // Set View Projection of a 3D rapresentation
    // Projection XY
    void setViewXY(Gnuplot& gp);
    // Projection XZ
    void setViewXZ(Gnuplot& gp);
    //Projection YZ
    void setViewYZ(Gnuplot& gp);


};

GnuplotCanvas::~GnuplotCanvas()
{
}



} // namespace Ariadne