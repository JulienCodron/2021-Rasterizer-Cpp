#include "frustum.h"

namespace aline{

    Frustum::Frustum(real near_dist, real far_dist){
        real e = 100;

        near = Vec4r{0, 0, -1, -near_dist};
        far = Vec4r{0, 0, 1, far_dist};
        left =  unit_vector(Vec4r{e, 0, -1, 0});
        right =  unit_vector(Vec4r{-e, 0, -1, 0});
        bottom =  unit_vector(Vec4r{0, e, -a, 0});
        top =  unit_vector(Vec4r{0, -e, -a, 0});
    }

    Object Frustum::clip(const Object & obj){

        Object o = clipPlane(near,obj);
        o = clipPlane(far,o);
        o = clipPlane(left,o);
        o = clipPlane(right,o);
        o = clipPlane(bottom,o);
        o = clipPlane(top,o);

        return obj;
    }

    aline::Vertex Frustum::intersectPoint(Vec4r plan, Vec3r & v0 , Vec3r & v1){
        Vec4r s {v0[0],v0[1],v0[2],1};
        Vec4r v {v1[0],v1[1],v1[2],0};
        real dividande = aline::dot(plan,v);
        if(dividande ==0) return {{1,1,1},1};
        real t = -(aline::dot(plan,s)/aline::dot(plan,v));
        Vec4r p = s + t*v;
        return {{p[0],p[1],p[2]},1};
    }

    int Frustum::signed_distance(Vec4r plan, const Vec3r & v){
        Vec3r plan3D {plan[0],plan[1],plan[2]};
        return aline::dot(plan3D,v) + plan[3];
    }

    Object Frustum::clipPlane(Vec4r plan, Object obj){
    
        std::vector<aline::Face> faces = obj.shape.get_faces();
        std::vector<aline::Vertex> vertices = obj.shape.get_vertices();
        std::vector<aline::Face> new_faces;
        for(auto face:faces){           
            std::vector<Vec3r> noNeedClip;
            Vec3r v0 = vertices[face.v0].coordinates;
            Vec3r v1 = vertices[face.v1].coordinates;
            Vec3r v2 = vertices[face.v2].coordinates;  
            int s = signed_distance(plan,v0);
            if(s > 0) noNeedClip.push_back(v0);
            s = signed_distance(plan,v1);
            if(s > 0) noNeedClip.push_back(v1);   
            s = signed_distance(plan,v2);
            if(s > 0) noNeedClip.push_back(v2);    
            if(noNeedClip.size() == 3){
                new_faces.push_back(face);
                
            }
            else if(noNeedClip.size() == 2){         
                if(noNeedClip[0]==v0 && noNeedClip[1]==v1){
                    Vertex vert1 = intersectPoint(plan,v0,v2);
                    Vertex vert2 = intersectPoint(plan,v1,v2);
                    vertices.push_back(vert1);
                    new_faces.push_back(Face{(uint)vertices.size()-1,face.v1,face.v0,minwin::blue});
                    vertices.push_back(vert2);
                    new_faces.push_back(Face{(uint)vertices.size()-2,(uint)vertices.size()-1,face.v1,minwin::blue});
                }
                else if(noNeedClip[0]==v0 && noNeedClip[1]==v2){
                    Vertex vert1 = intersectPoint(plan,v0,v1);
                    Vertex vert2 = intersectPoint(plan,v2,v1);
                    vertices.push_back(vert1);
                    new_faces.push_back(Face{(uint)vertices.size()-1,face.v2,face.v0,minwin::blue});
                    vertices.push_back(vert2);
                    new_faces.push_back(Face{(uint)vertices.size()-2,(uint)vertices.size()-1,face.v2,minwin::blue});
                }
                else{
                    Vertex vert1 = intersectPoint(plan,v0,v1);
                    Vertex vert2 = intersectPoint(plan,v0,v2);
                    vertices.push_back(vert1);
                    new_faces.push_back(Face{(uint)vertices.size()-1,face.v2,face.v1,minwin::blue});
                    vertices.push_back(vert2);
                    new_faces.push_back(Face{(uint)vertices.size()-2,(uint)vertices.size()-1,face.v2,minwin::blue});
                }
                
            }
            else if (noNeedClip.size() == 1){
                Face new_face = face;
                for(auto v:noNeedClip){
                    if(v!=v0){
                        vertices.push_back(intersectPoint(plan,v0,v));
                        new_face.v0=vertices.size()-1;
                    };
                    if(v!=v1){
                        vertices.push_back(intersectPoint(plan,v1,v));
                        new_face.v1=vertices.size()-1;
                    };
                    if(v!=v2){
                        vertices.push_back(intersectPoint(plan,v2,v));
                        new_face.v2=vertices.size()-1;
                    };
                }
                new_faces.push_back(new_face);
            }
        }
        return {{"obj",vertices,new_faces},obj.translation,obj.rotation,obj.scale};
    }   
}