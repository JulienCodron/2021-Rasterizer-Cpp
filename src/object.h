#pragma once 

#include "shape.h"
#include "matrix.h"

namespace aline{

    class Object{
        public:
        Shape shape;
        //CHANGE  HERE IN THE TRANSLATION VECTOR
        Vec3r translation {0.0,0.0,-10.0};
        Vec3r rotation {0.0,0.0,0.0};
        Vec3r scale {1.0,1.0,1.0};
        Vec3r barycentre ;
        const double PI = std::acos(-1);

        Object(){
            init();
        }

        Object( Shape const& shape): shape(shape){
            init();
        }

        Object( Shape & shape): shape(shape){
            init();       
        }

        Object(const Shape & shape, const Vec3r & translation, const Vec3r & rotation, const Vec3r & scale): shape(shape),translation(translation),rotation(rotation),scale(scale){
            init();
        }

        Object(Object & o){
            shape = o.shape;
            translation = o.translation;
            rotation = o.rotation;
            scale = o.scale;
        }

        Object(const Object & o){
            shape = o.shape;
            translation = o.translation;
            rotation = o.rotation;
            scale = o.scale;
        }

        Object operator=(const Object & o){
            return{o.shape,o.translation,o.rotation,o.scale};
        }


        void init(){
            real x = 0, y = 0, z = 0;

            for(const auto vertex: shape.get_vertices()) {
                x += vertex.coordinates[0];
                y += vertex.coordinates[1];
                z += vertex.coordinates[2];
            }

            real t = shape.get_vertices().size();

            barycentre = Vec3r{x/t, y/t, z/t};

            real rayon = 0;
            for(const auto elm: shape.get_vertices()) {
                real d = dist(elm.coordinates, barycentre);
                if(d > rayon) rayon = d;
            }
        }

        real dist(Vec3r v0 , Vec3r v1){
            return std::sqrt(std::pow(v0[0]-v1[0],2)+std::pow(v0[1]-v1[1],2)+std::pow(v0[2]-v1[2],2));
        }

        //Returns the transform matrix of the object.
        Mat44r transform() const{   

            Mat44r matrix = matrixTranslation(-barycentre);

            matrix = matrixScale() * matrix;
            matrix = matrixRotation() * matrix;
            matrix = matrixTranslation(translation) * matrix;
            matrix = matrixTranslation(barycentre) * matrix;

            return matrix;
        }

        Mat44r matrixRotation() const{
            Mat44r matrix = matrixRotationX();

            matrix = matrixRotationY() * matrix;
            matrix = matrixRotationZ() * matrix;

            return matrix;
        }

        Mat44r matrixTranslation(const Vec3r &transl) const{
            return Mat44r {
                {1, 0, 0, transl[0]},
                {0, 1, 0, transl[1]},
                {0, 0, 1, transl[2]},
                {0, 0, 0, 1}
            };
        }

        Mat44r matrixScale() const{
            return Mat44r {
                {scale[0], 0, 0, 0},
                {0, scale[1], 0, 0},
                {0, 0, scale[2], 0},
                {0, 0, 0, 1}
            };
        }

        Mat44r matrixRotationX() const{
            real tmp = rotation[0]*PI /180;
            real cos = std::cos(tmp);
            real sin = std::sin(tmp);

            return Mat44r {
                {1, 0, 0, 0},
                {0, cos, -sin, 0},
                {0, sin, cos, 0},
                {0, 0, 0, 1}
            };
        }

        Mat44r matrixRotationY() const{
            real tmp = rotation[1]*PI /180;
            real cos = std::cos(tmp);
            real sin = std::sin(tmp);

            return Mat44r {
                {cos, 0, sin, 0},
                {0, 1, 0, 0},
                {-sin, 0, cos, 0},
                {0, 0, 0, 1}
            };
        }

        Mat44r matrixRotationZ() const{
            real tmp = rotation[2]*PI /180;
            real cos = std::cos(tmp);
            real sin = std::sin(tmp);

            return Mat44r {
                {cos, -sin, 0, 0},
                {sin, cos, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            };
        }
    };
}