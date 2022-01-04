#pragma once
#include "vector.h"
#include "color.h"
#include <vector>

namespace aline{
    
    using Color = minwin::Color;

    class Vertex{
        public:
        Vec3r coordinates;
        real color_intensity = 1;

        //Constructs a vertex whose coordinates are c and the color intensity is h.
        Vertex(const Vec3r & c, real h) : coordinates(c) , color_intensity(h) {}
    };

    class Face{
        public:
        uint v0;
        uint v1;
        uint v2;
        Color color = minwin::blue;

        //Constructs a triangular face whose vertex indexes and color are the ones given as arguments.
        Face( uint v0, uint v1, uint v2, const Color & color ) : v0(v0), v1(v1) , v2(v2) , color(color) {}
    };

    class Shape{
        std::string name;
        std::vector<Vertex> vertices;
        std::vector<Face> faces;

        public:
        //Constructs a shape whose name, vertices and faces are given as arguments.
        Shape( const std::string& name, const std::vector<Vertex> & vertices, const std::vector<Face> & faces): name(name), vertices(vertices), faces(faces){}

        Shape(){}

        //Returns the name of the face.
        inline std::string get_name() const {return name;}
        
        //Returns the list of vertices.
        inline std::vector<Vertex> get_vertices() const {return vertices;}
        
        //Returns the list of faces.
        inline std::vector<Face> get_faces() const {return faces;}

    };
}