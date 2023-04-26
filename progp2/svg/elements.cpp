#include <deque>
#include "elements.hpp"

namespace svg {
    ellipse::ellipse(const svg::color &fill,
                     const point &center,
                     const point &radius) :
            shape(fill), center(center), radius(radius) {

    }

    void ellipse::draw(png_image &img) const {
        img.draw_ellipse(center, radius, get_color());
    }

    void ellipse::translate(const point &t) {
        center = center.translate(t);
    }

    void ellipse::scale(const point &origin, int v) {
        radius.x *= v;
        radius.y *= v;
        center = center.scale(origin, v);
    }

    void ellipse::rotate(const point &origin, int degrees) {
        center = center.rotate(origin, degrees);
    }

    shape *ellipse::duplicate() const {
        return new ellipse(get_color(), center, radius);
    }


    polygon::polygon(const svg::color &fill,
                     const std::vector<point> &points) :
            shape(fill), points(points) {

    }

    void polygon::draw(png_image &img) const {
        img.draw_polygon(points, get_color());
    }

    void polygon::translate(const point &t) {
        for (auto &p: points) {
            p = p.translate(t);
        }
    }

    void polygon::scale(const point &origin, int v) {
        for (auto &p: points) {
            p = p.scale(origin, v);
        }

    }

    void polygon::rotate(const point &origin, int degrees) {
        for (auto &p: points) {
            p = p.rotate(origin, degrees);
        }
    }

    shape *polygon::duplicate() const {
        return new polygon(get_color(), points);
    }

    polyline::polyline(const svg::color &fill,
                       const std::vector<point> &points) :
            shape(fill), points(points) {

    }

    void polyline::draw(png_image &img) const {
        int n = points.size() - 1;
        for (int a = 0; a < n; a++) {
            img.draw_line(points[a], points[a + 1], get_color());
        }
    }

    void polyline::translate(const point &t) {
        for (auto &p: points) {
            p = p.translate(t);
        }
    }

    void polyline::scale(const point &origin, int v) {
        for (auto &p: points) {
            p = p.scale(origin, v);
        }

    }

    void polyline::rotate(const point &origin, int degrees) {
        for (auto &p: points) {
            p = p.rotate(origin, degrees);
        }
    }

    shape *polyline::duplicate() const {
        return new polyline(get_color(), points);
    }

    group::group( const std::vector<shape*>&shapes) :
            shape({255,255,255}), shapes(shapes) {
    }
        group::~group() {
        for (auto s: shapes) {
            delete s;
        }
    }

    void group::draw(png_image &img) const {
        for (auto s: shapes)
            s->draw(img);
    }

    void group::translate(const point &t) {
        for (auto s: shapes)
            s->translate(t);
    }

    void group::scale(const point &origin, int v) {
        for (auto s: shapes)
            s->scale(origin, v);
    }

    void group::rotate(const point &origin, int degrees) {
        for (auto s: shapes)
            s->rotate(origin, degrees);

    }

    shape *group::duplicate() const {
        std::vector<shape *>shape;
        for(int a = 0; a < shapes.size(); a++) {
            shape.push_back(shapes.at(a)->duplicate());
        }
        return new group(shape);
    }
    }
