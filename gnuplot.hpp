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

#include "gnuplot-iostream.h"

namespace Ariadne{

struct ImageSize2D {
    Nat nx, ny;
    ImageSize2D(Nat _nx, Nat _ny) : nx(_nx), ny(_ny) {}
    ImageSize2D(Nat _nx, Nat _ny) {
        ARIADNE_ASSERT(_nx > 0 && _ny > 0);
        nx = static_assert<Nat>(_nx);
        ny = static_assert<Nat>(_ny);
    }
};

enum _Colours // %c - es: lc, fc
{
    red,
    blue,
    green,
    yellow,
    magenta,
    cyan
};

const char *_colours[] = {"red", "blue", "green", "yellow", "magenta", "cyan"};

enum _LineStyle2D // %s - es: ls, fs
{
    line,
    dot,
    dash,
    point,
    linepoints, //lp
    solid,
    impulses,
    style1, //1
    style2, //2
    style3, //3
    style4,  //4
    //filled  // filledcurves
};

const char *_linestyle2D[] = {"line", "dot", "dash", "point", "linepoints", "solid", "impulses"
                                "ls 1", "ls 2", "ls 3", "ls 4", "ls 5",};

enum _LineStyle3D // %s - es: ls, fs
{
    line,
    surface,
    point,
    impulse,
    solid   //pm3d
};

const char *_linestyle3D[] = {"line", "surface", "point", "impulse", "solid"};

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

struct _Label2D
{
    const String title;
    const String xLabel;
    const String yLabel;
};

struct _Label3D
{
    const String title;
    const String xLabel;
    const String yLabel;
    const String zLabel;
};

struct _Range2D
{
    const int Xmin;
    const int Xmax;
    const int Ymin;
    const int Ymax;
};

struct _Range3D
{
    const int Xmin;
    const int Xmax;
    const int Ymin;
    const int Ymax;
    const int Zmin;
    const int Zmax;
};

struct Image2D
{
    _Colours colour;
    _LineStyle2D linestyle2D;
    const int linewidth;
    //_DimPlot dim;
    _Label2D label;
    _Format format;
    _Range2D range2D;
    _Size size;
    String nameFile;

};

struct Image3D
{
    _Colours colour;
    _LineStyle3D linestyle3D;
    const int linewidth;
    //_DimPlot dim;
    _Label3D label;
    _Format format;
    _Range3D range2D;
    _Size size;
    String nameFile;
    
};


class GnuplotCanvas
{
private:
    //Image2D *Image2D;
    //Image3D *image3D;
    //double lw, dr;  // Line width and Dot radius
    //Colour lc, fc;  // Line colour and Fill colour
protected: 
    bool noCanvas;
public:
    ~GnuplotCanvas();
    // Constructors - Create the canvas
    //Create empty canvas
    GnuplotCanvas();
    //Create canvas with dimensions
    GnuplotCanvas(const Image2D& image, const int sizeX, const int sizeY);
    // 2D Plot
    void plot2D(Image2D& image); //pag. 100
    //splot()
    void setRange2D(Image2D& image, const int minX, const int maxX, 
                const int minY, const int maxY);
    void setRange3D(Image3D& image, const int minX, const int maxX, 
                const int minY, const int maxY,
                const int minZ, const int maxZ);
    //TODO from p.119

};

GnuplotCanvas::GnuplotCanvas(/* args */)
{
}

GnuplotCanvas::~GnuplotCanvas()
{
}



} // namespace Ariadne