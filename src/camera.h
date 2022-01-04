#pragma once

#include "matrix.h"
#include "frustum.h"
#include <vector>

namespace aline{
    

    class Camera{
    
    public: 
        Vec4r position;
        Vec3r orientation;
        real vp_aspect_ratio;
        real focal_dist;
        real default_focal_dist;
        real default_ms;
        real current_ms;
        real default_rs;
        real current_rs;
        real default_zs;
        real current_zs;
        Frustum frustum;
        const double PI = std::acos(-1);

        Camera(){
            position = {0.0, 0.0, 0.0, 1.0};
            orientation = {0.0, 0.0, 0.0};
            vp_aspect_ratio = 0.75;
            focal_dist = 2.0;
            default_focal_dist = 2.0;
            default_ms = 0.05;
            current_ms = 0.05;
            default_rs = 1.0;
            current_rs = 1.0;
            default_zs = 0.0625;
            current_zs = 0.0625;
            frustum = {5.0,100.0};
        }

        Camera( real aspect_ratio,
                real focal_dist = 2.0,
                Vec4r position = {0.0, 0.0, 0.0, 1.0},
                Vec3r orientation = {0.0, 0.0, 0.0}, // in degrees
                real move_speed = 0.05,
                real rot_speed = 1.0,
                real zoom_speed = 0.0625)
                : 
                position(position),
                orientation(orientation),
                vp_aspect_ratio(aspect_ratio),
                focal_dist(focal_dist),
                default_focal_dist(focal_dist),
                default_ms(move_speed),
                current_ms(move_speed),
                default_rs(rot_speed),
                current_rs(rot_speed),
                default_zs(zoom_speed),
                current_zs(zoom_speed),
                frustum(aline::Frustum{5.0,100.0})
            {}

        // Moves the camera forward on the given axis (x = 0, y = 1 and z = 2).
        // Hint: this function only sets the current move speed of the camera to an appropriate
        // value. It is the job of the function update() to actually change the position of the
        // camera. The same goes for the other movement, rotation and zoom functions below.
        void move_forward( uint axis ){position[axis] += current_ms;}

        //Moves the camera backward on the given axis.
        void move_backward( uint axis ){position[axis] -= current_ms;}
        
        //Rotates the camera clockwise on the given axis.
        void rotate_cw( uint axis ){orientation[axis] += current_rs;}
        
        
        //Rotates the camera anticlockwise on the given axis.
        void rotate_acw( uint axis ){orientation[axis] -= current_rs;}
        
        
        //Changes the focal distance to zoom in the scene.
        void zoom_in() {focal_dist += current_zs; }
        
        
        //Changes the focal distance to zoom in the scene.
        void zoom_out() {focal_dist -= current_zs; }
        
        
        //reset the position of the camera.
        void reset_position(){
            default_focal_dist = 2.0;
            position = {0.0, 0.0, 0.0, 1.0};
            orientation = {0.0, 0.0, 0.0};
        }
        
        
        //The transform matrix of the camera.
        Mat44r transform() const{
            real tmpX = orientation[0]*PI /180;
            real cosX = std::cos(tmpX);
            real sinX = std::sin(tmpX);

            real tmpY = orientation[1]*PI /180;
            real cosY = std::cos(tmpY);
            real sinY = std::sin(tmpY);

            real tmpZ = orientation[2]*PI /180;
            real cosZ = std::cos(tmpZ);
            real sinZ = std::sin(tmpZ);
            
            Mat44r CrX {
                {1, 0, 0, 0},
                {0, cosX, -sinX, 0},
                {0, sinX, cosX, 0},
                {0, 0, 0, 1}
            };

            Mat44r CrY {
                {cosY, 0, sinY, 0},
                {0, 1, 0, 0},
                {-sinY, 0, cosY, 0},
                {0, 0, 0, 1}
            };

            Mat44r CrZ {
                {cosZ, -sinZ, 0, 0},
                {sinZ, cosZ, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            };

            Mat44r Cr = CrX * CrY * CrZ;

            Mat44r Ct {
                {1,0,0,position[0]},
                {0,1,0,position[1]},
                {0,0,1,position[2]},
                {0,0,0,1}
            };

            return Cr * Ct;
        } 

        bool sees(const Vec3r & v0,const Vec3r & v1, const Vec3r & v2) const {
            Vec3r e01 = v1 - v0;
            Vec3r e02 = v2 - v0;
            Vec3r n = unit_vector(cross(e01,e02));
            return !(dot({0,0,1},n) < 0);
        }         

        Object cull( const Object & obj) const {
            std::vector<aline::Face> faces = obj.shape.get_faces();
            std::vector<aline::Vertex> vertices = obj.shape.get_vertices();
            std::vector<aline::Face> new_faces;
            for(auto face:faces){ 
                if(sees(vertices[face.v0].coordinates,vertices[face.v1].coordinates,vertices[face.v2].coordinates)){
                    new_faces.push_back(face);
                }
            }
            return {{"shape",vertices,new_faces},obj.translation,obj.rotation,obj.scale};
        }
    };
}