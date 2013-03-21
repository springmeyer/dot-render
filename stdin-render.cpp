#include <mapnik/map.hpp>
#include <mapnik/request.hpp>
#include <mapnik/ctrans.hpp>
#include <mapnik/box2d.hpp>
#include <mapnik/graphics.hpp>
#include <mapnik/image_compositing.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/color.hpp>
#include <mapnik/util/conversions.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "util.hpp"

const double divisible = std::pow(10.0,7);

mapnik::box2d<double> extent;

class renderer {
public:
    renderer(mapnik::image_32 & im,
             mapnik::image_32 & marker) :
        im_(im),
        marker_(marker) {}

    void apply(double dx, double dy,
               mapnik::composite_mode_e comp_op=mapnik::multiply,
               double opacity = 1.0) const
    {
          double cx = 0.5 * marker_.width();
          double cy = 0.5 * marker_.height();
          mapnik::composite(im_.data(), marker_.data(),
                            comp_op, opacity,
                            std::floor(dx - cx),
                            std::floor(dy - cy), false);
    }

private:
    mapnik::image_32 & im_;
    mapnik::image_32 & marker_;
};

void render_loop(mapnik::request const& req,
                 renderer const& renderer,
                 mapnik::proj_transform const& prj)
{
    std::string input_line;
    std::ios_base::sync_with_stdio(false);
    mapnik::CoordTransform transform(req.width(),req.height(),req.extent(),0,0);
    std::vector<util::StringRef> v;
    while(std::cin) {
        getline(std::cin, input_line);
        v.clear();
        split3( v, input_line );
        if (v.size() >= 2) {
            double x = 0;
            double y = 0;
            if (mapnik::util::string2double(v[0].begin(),v[0].end(),y)
                && mapnik::util::string2double(v[1].begin(),v[1].end(),x))
            {
                  //prj.forward(x,y,0);
                  x /= divisible;
                  y /= divisible;
/*
                  if (!extent.valid())
                      extent.init(x,y,x,y);
                  else
                      extent.expand_to_include(x,y);
*/
                  //std::clog << std::fixed << x << "," << y << "\n";
                  transform.forward(&x,&y);
                  renderer.apply(x,y);
            }
        }
    }
}


int main() {
    try {
        mapnik::box2d<double> zextent(-127.7923332999999957,31.3267771000000010,-102.0448844000000008,49.0113344000000026);
        unsigned width = 800;
        unsigned height = 800;
        mapnik::Map map(width,height);
        map.set_aspect_fix_mode(mapnik::Map::GROW_CANVAS);
        map.zoom_to_box(zextent);
        mapnik::request req(map.width(),map.height(),map.get_current_extent());
        mapnik::image_32 im(map.width(),map.height());
        im.set_background(mapnik::color(255,255,255));
        mapnik::image_32 marker(1,1);
        marker.set_background(mapnik::color(0, 0, 0, 5));
        marker.premultiply();
        renderer ren(im,marker);
        mapnik::projection source("+init=epsg:4326",true);
        mapnik::projection dest("+init=epsg:4326",true);
        mapnik::proj_transform prj(source,dest);
        render_loop(req,ren,prj);
        mapnik::save_to_file(im,"test.png");
    } catch (std::exception const& ex) {
        std::clog << "error: " << ex.what() << "\n";
        return -1;
    }
    std::clog << extent << "\n";
    return 0;

}
