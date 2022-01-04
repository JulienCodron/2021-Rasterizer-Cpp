#include "scene.h"
#include <unistd.h>

namespace aline{

    Scene::Scene(){}

    void Scene::run(){
        while(running){
            window.process_input();
            window.clear();

            for(auto obj:objects){
                aline::Object o_t = apply_object_transforms(obj);
                aline::Object o_tt = apply_camera_transforms(o_t);
                aline::Object o_clip = cull_and_clip(o_tt);
                draw_object(o_clip);
            }

            window.render_text(text1);
            window.render_text(text2);
            window.display();
        }
        shutdown();
    }


    void Scene::add_object( const Object & obj){
        objects.push_back(obj);
    }

    void Scene::initialise(int argc, const char * argv[]){
        window.set_title( "MinWin Test" );
        window.set_width( Sw );
        window.set_height( Sh );

        text1.set_pos(250,20);
        text1.set_string( "Press SPACE to change viewmod." );
        text1.set_color(minwin::white);

        text2.set_pos(300, 40 );
        text2.set_string( "Press ESC to quit." );
        text2.set_color(minwin::white);

        if( not window.load_font( "fonts/FreeMonoBold.ttf", 16u ) )
        {
            std::cerr << "Couldn't load font.\n";
        }

        window.register_quit_behavior( new QuitButtonBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_ESCAPE, new QuitKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_SPACE, new ChangeModBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_PAGEUP, new ScaleUpKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_PAGEDOWN, new ScaleDownKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_Z, new TranslateForwardKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_S, new TranslateBackwardKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_D, new TranslateRightKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_Q, new TranslateLeftKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_C, new TranslateUpKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_V, new TranslateDownKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_UP, new RotateXClockwiseKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_DOWN, new RotateXNoClockwiseKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_RIGHT, new RotateYClockwiseKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_LEFT, new RotateYNoClockwiseKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_A, new RotateZClockwiseKeyBehavior( *this ) );
        window.register_key_behavior( minwin::KEY_E, new RotateZNoClockwiseKeyBehavior( *this ) );

        
        if( not window.open() ){
            std::cerr << "Couldn't open window.\n";
            return;
        }

        load_data(argc, argv);
    }

    void Scene::load_data( int argc, const char * argv[] ){
        for(int i = 0 ; i < argc ; ++i){
            std::string file_name = std::string(argv[i]);
            if(file_name.substr(file_name.find_last_of(".") + 1) == "obj") 
                parse( "obj/" + file_name);
        }       
    }


    inline void Scene::shutdown(){window.close();}

    void Scene::QuitButtonBehavior::on_click() const { this->owner.running = false; }
    void Scene::QuitKeyBehavior::on_press() const   { this->owner.running = false; }
    void Scene::QuitKeyBehavior::on_release() const {} // does nothing

    void Scene::ChangeModBehavior::on_press() const{
        switch (owner.mod){
            case Shaded:
                this->owner.mod = Solid;
                break;

            case Solid:
                this->owner.mod = Wireframe;
                break;

            case Wireframe:
                this->owner.mod = Shaded;
                break;
        }          
        
    }
    void Scene::ChangeModBehavior::on_release() const{}// does nothing

    void Scene::ScaleUpKeyBehavior::on_press() const{
        for(auto &object:this->owner.objects){
            object.scale[0] = object.scale[0] * 1.1;
            object.scale[1] = object.scale[1] * 1.1;
            object.scale[2] = object.scale[2] * 1.1;
        }
    }
    void Scene::ScaleUpKeyBehavior::on_release() const {} 

    void Scene::ScaleDownKeyBehavior::on_press() const{
        for(auto &object:this->owner.objects){
            object.scale[0] = object.scale[0] * 0.9;
            object.scale[1] = object.scale[1] * 0.9;
            object.scale[2] = object.scale[2] * 0.9;
        }
    }
    void Scene::ScaleDownKeyBehavior::on_release() const {} 

    void Scene::TranslateUpKeyBehavior::on_press() const{
        this->owner.camera.move_forward(1);
    }
    void Scene::TranslateUpKeyBehavior::on_release() const {} 

    void Scene::TranslateDownKeyBehavior::on_press() const{
        this->owner.camera.move_backward(1);
    }
    void Scene::TranslateDownKeyBehavior::on_release() const {} 

    void Scene::TranslateLeftKeyBehavior::on_press() const{
        this->owner.camera.move_backward(0);
    }
    void Scene::TranslateLeftKeyBehavior::on_release() const {} 

    void Scene::TranslateRightKeyBehavior::on_press() const{
        this->owner.camera.move_forward(0);
    }
    void Scene::TranslateRightKeyBehavior::on_release() const {} 

    void Scene::TranslateForwardKeyBehavior::on_press() const{
        this->owner.camera.move_forward(2);
    }
    void Scene::TranslateForwardKeyBehavior::on_release() const {} 

    void Scene::TranslateBackwardKeyBehavior::on_press() const{
        this->owner.camera.move_backward(2);
    }
    void Scene::TranslateBackwardKeyBehavior::on_release() const {} 


    void Scene::RotateXClockwiseKeyBehavior::on_press() const{
        //this->owner.camera.rotate_cw(0); for the camera
        for(auto &object:this->owner.objects){
            object.rotation[0] += 1;
        }
    }
    void Scene::RotateXClockwiseKeyBehavior::on_release() const {} 

    void Scene::RotateXNoClockwiseKeyBehavior::on_press() const{
        //this->owner.camera.rotate_acw(0); for the camera
        for(auto &object:this->owner.objects){
             object.rotation[0] -= 1;
        }
    }
    void Scene::RotateXNoClockwiseKeyBehavior::on_release() const {} 

    void Scene::RotateYClockwiseKeyBehavior::on_press() const{ 
        //this->owner.camera.rotate_acw(1); for the camera   
        for(auto &object:this->owner.objects){
            object.rotation[1] += 1;
        }
    }
    void Scene::RotateYClockwiseKeyBehavior::on_release() const {} 

    void Scene::RotateYNoClockwiseKeyBehavior::on_press() const{
        //this->owner.camera.rotate_cw(1); for the camera
        for(auto &object:this->owner.objects){
            object.rotation[1] -= 1;
        }
    }
    void Scene::RotateYNoClockwiseKeyBehavior::on_release() const {} 

    void Scene::RotateZClockwiseKeyBehavior::on_press() const{
        //this->owner.camera.rotate_cw(2); for the camera
        for(auto &object:this->owner.objects){
            object.rotation[2] += 1;
        }
    }
    void Scene::RotateZClockwiseKeyBehavior::on_release() const {} 

    void Scene::RotateZNoClockwiseKeyBehavior::on_press() const{
        //this->owner.camera.rotate_cw(2); for the camera
        for(auto &object:this->owner.objects){
            object.rotation[2] -= 1;
        }
    }
    void Scene::RotateZNoClockwiseKeyBehavior::on_release() const {} 


    Vec2r viewport_to_canvas( const Vec2r & point ){
        Vec2r pts;
        pts[0] = point[0] * Sw / Vw;
        pts[1] = point[1] * Sh / Vh;
        return pts;
    }
    
    Vec2i canvas_to_window( const Vec2r & point ){
        Vec2i pts;
        pts[0] =  (Sw / 2) + point[0];
        pts[1] =  (Sh / 2) - point[1];
        return pts;
    }

    void Scene::draw_line( const Vec2i & v0, const Vec2i & v1){
        int x0 = v0[0], x1 = v1[0], y0 =  v0[1], y1 = v1[1];
        int dx = x1 - x0 , dy = y1 - y0;
        if(abs(dx) > abs(dy)){
            if(x0 > x1){
                std::swap(x0,x1);
                std::swap(y0,y1);
                dx = x1 - x0;
                dy = y1 - y0;
            }
            int ax = dx<<1 , ay = dy<<1 , d = ay - ax;
            for(;x0 < x1 ; ++x0 ){
                window.put_pixel(x0,y0,minwin::blue);
                if(d*sign(dy) >= 0){
                    y0 += sign(dy);
                    d -= ax * sign(dy);
                }
                d += ay;
            }
        }
        else{
            if(y0 > y1){
                std::swap(x1,x0);
                std::swap(y1,y0);
                dx = x1 - x0;
                dy = y1 - y0;
            }
            int ax = dx<<1 , ay = dy<<1 , d = ax - ay;
            for(;y0 < y1 ; ++y0 ){
                if(x0 > 0 && x0 < Sw && y0 > 0 && y0 < Sh)
                    window.put_pixel(x0,y0,minwin::blue);
                if(d*sign(dx) >= 0){
                    x0 += sign(dx);
                    d -= ay * sign(dx);
                }
                d += ax;
            }
        }
    }

    std::vector<real> interpolate(real i0,real d0, real i1, real d1){
        std::vector<real> interpolation;
        if( i0 == i1 ) { 
            interpolation.push_back(d0); 
            return interpolation;
        }
        real a = (d0 - d1) / (i0 - i1);
        real d = d0;
        
        for( real i = i0; i <= i1; ++i) {
            interpolation.push_back( d );
            d = d + a;
        }
        return interpolation;
    }

    void Scene::draw_shaded_line( const Vec2i & v0, real h0, const Vec2i & v1, real h1 ){
        // NOT WORKING 
        int x0 = v0[0], x1 = v1[0], y0 =  v0[1], y1 = v1[1];
        int dx = x1 - x0 , dy = y1 - y0;

        std::vector<real> x01 = interpolate(y0,x0,y1,x1);
        std::vector<real> h01 = interpolate(y0,h0,y1,h1);
        std::vector<real> h_segment;
        
        if(abs(dx) > abs(dy)){
            if(x0 > x1){
                std::swap(x0,x1);
                std::swap(y0,y1);
                dx = x1 - x0;
                dy = y1 - y0;
            }
            int ax = dx<<1 , ay = dy<<1 , d = ay - ax;
            for(; x0 < x1 ; ++x0 ){
                h_segment = interpolate( x01[y0], h01[y0], x01[y0], h01[y0] );
                window.put_pixel(x0,y0,minwin::Color { 0.0*h_segment[x0 - y0],  0.0*h_segment[x0 - y0],  1.0*h_segment[x0 - y0],  0.0 });
                if(d*sign(dy) >= 0){
                    y0 += sign(dy);
                    d -= ax * sign(dy);
                }
                d += ay;
            }
        }
        else{
            if(y0 > y1){
                std::swap(x1,x0);
                std::swap(y1,y0);
                dx = x1 - x0;
                dy = y1 - y0;
            }
            int ax = dx<<1 , ay = dy<<1 , d = ax - ay;
            for(; y0 < y1 ; ++y0 ){
                window.put_pixel(x0,y0,minwin::blue);
                if(d*sign(dx) >= 0){
                    x0 += sign(dx);
                    d -= ay * sign(dx);
                }
                d += ax;
            }
        }
    }

    void Scene::draw_wireframe_triangle( const Vec2i & v0, const Vec2i & v1, const Vec2i & v2 ){
        draw_line(v0,v1);
        draw_line(v1,v2);
        draw_line(v2,v0);
    }

    void Scene::draw_filled_triangle( const Vec2i & v0, const Vec2i & v1, const Vec2i & v2 ){
        int x0 = v0[0] ,x1 = v1[0],x2 = v2[0],y0 = v0[1],y1 = v1[1],y2 = v2[1];
        if(y1 < y0) { std::swap(x0,x1);std::swap(y0,y1);}
        if(y2 < y0) { std::swap(x2,x0);std::swap(y2,y0);}
        if(y2 < y1) { std::swap(x2,x1);std::swap(y2,y1);}

        std::vector<real> x02 = interpolate(y0,x0,y2,x2);
        std::vector<real> x01 = interpolate(y0,x0,y1,x1);
        std::vector<real> x12 = interpolate(y1,x1,y2,x2);

        x01.pop_back();
        x01.insert( x01.end(), x12.begin(), x12.end() );

        std::vector<real> x_left, x_right;
        real m = floor(x01.size() / 2 );
        if( x02[m] < x01[m] ) {
            x_left = x02;
            x_right = x01;
        } else {
            x_left = x01;
            x_right = x02;
        }

        for( int y = y0; y <= y2; ++y )
            for( int x = x_left[y - y0]+1; x <= x_right[y - y0+1]; ++x )
                window.put_pixel(x,y,minwin::green);

    }

    void Scene::draw_shaded_triangle( const Vec2i & v0, real h0, const Vec2i & v1, real h1, const Vec2i & v2, real h2 ){
        int x0 = v0[0] ,x1 = v1[0],x2 = v2[0],y0 = v0[1],y1 = v1[1],y2 = v2[1];
        if(y1 < y0) { std::swap(x0,x1);std::swap(y0,y1);std::swap(h0,h1);}
        if(y2 < y0) { std::swap(x2,x0);std::swap(y2,y0);std::swap(h2,h0);}
        if(y2 < y1) { std::swap(x2,x1);std::swap(y2,y1);std::swap(h2,h1);}

        std::vector<real> x01 = interpolate(y0,x0,y1,x1);
        std::vector<real> h01 = interpolate(y0,h0,y1,h1);
        std::vector<real> x12 = interpolate(y1,x1,y2,x2);
        std::vector<real> h12 = interpolate(y1,h1,y2,h2);
        std::vector<real> x02 = interpolate(y0,x0,y2,x2);
        std::vector<real> h02 = interpolate(y0,h0,y2,h2);


        h01.insert( h01.end(), h12.begin(), h12.end() );

        std::vector<real> x_left, x_right, h_left, h_right;
        real m = floor(x01.size() / 2 );
        if( x02[m] < x01[m] ) {
            x_left = x02;
            h_left = h02;
            
            x_right = x01;
            h_right = h01;
        } else {
            x_left = x01;
            h_left = h01;

            x_right = x02;         
            h_right = h02;
        }

        for( int y = y0; y <= y2; ++y ){
            real x_l = x_left[y - y0];

            std::vector<real> h_segment = interpolate( x_left[y - y0], h_left[y - y0], x_right[y - y0], h_right[y - y0] );
            for( int x = x_left[y - y0]+1; x <= x_right[y - y0]; ++x ){
                minwin::Color  shaded_color = minwin::Color { 1.0*h_segment[x - x_l],  0.0*h_segment[x - x_l],  0.0*h_segment[x - x_l],  0.0 };
                window.put_pixel( x, y, shaded_color );
            }
        }

    }

    std::vector<std::string> getWords(std::string line){
        std::vector<std::string> words;
        std::string word = "";
        for(size_t i = 0 ; i < line.size() ; ++i){
            if (line[i] != ' ' && line[i] != '\t'){
                word += line[i];
            }
            else{
                words.push_back(word);
                word = "";
                while(i+1 < line.size() && line[i+1] == ' ' && line[i+1] != '\t')
                    i++;     
            }
        }
        while(words.size() < 4){
            words.push_back(word);
        }
        return words;
    }

    void Scene::parse(std::string file_path){
        std::ifstream file;
        try{
            file.open(file_path);
        }
        catch(std::exception & e){
            std::cout << "file not found" << std::endl;
            return;
        }

        std::string line;
        std::vector<std::string> words;
        std::vector<Vertex> vertices;
        std::vector<Face> faces;
        while(getline(file,line))
        {  
            if (line != " " && line != "" && line != "\n" ) {
                words = getWords(line);
                if(words[0] == "v" && words[0].size() == 1){
                    Vec3r v = {atof(words[1].c_str()),atof(words[2].c_str()),atof(words[3].c_str())};
                    Vertex vertex = {v,1.0};
                    vertices.push_back(vertex);
                } 
                if(words[0] == "f" && words[0].size() == 1){
                    Face f = {(uint)stoi(words[1])-1,(uint)stoi(words[2])-1,(uint)stoi(words[3])-1,minwin::blue};
                    faces.push_back(f);
                }     
            }
        }
        Shape shape = Shape(file_path,vertices,faces);
        add_object(Object(shape));
    };

    Vec2r perspective_projection( const Vec4r & v, real d ){
        real xe = v[0], ye = v[1], ze = v[2];  
        real div = -(d/ze);
        return {div*xe,div*ye};
    }

    aline::Object Scene::apply_object_transforms(aline::Object objs){

        std::vector<aline::Face> faces = objs.shape.get_faces();
        std::vector<aline::Vertex> vertices = objs.shape.get_vertices();
        std::vector<aline::Vertex> new_vertices;
        Matrix<real,4,4> mt = objs.transform();
        for(auto vertex:vertices){ 
            Vec4r new_vector = {vertex.coordinates[0],vertex.coordinates[1],vertex.coordinates[2],1};
            new_vector = mt * new_vector;
            new_vertices.push_back({Vec3r{new_vector[0],new_vector[1],new_vector[2]},1});
        }
        aline::Shape shape {"shape", new_vertices, faces};
        return {shape, objs.translation,objs.rotation,objs.scale};
    }

    aline::Object Scene::apply_camera_transforms(aline::Object objs){
        Matrix<real,4,4> mt = camera.transform();
    
        std::vector<aline::Face> faces = objs.shape.get_faces();
        std::vector<aline::Vertex> vertices = objs.shape.get_vertices();
        std::vector<aline::Vertex> new_vertices;
        for(auto vertex:vertices){ 
            Vec4r new_vector = {vertex.coordinates[0],vertex.coordinates[1],vertex.coordinates[2],1};
            new_vector = mt * new_vector;
            new_vertices.push_back({Vec3r{new_vector[0],new_vector[1],new_vector[2]},1});
        }

        aline::Shape shape {"shape", new_vertices, faces};
        return {shape, objs.translation,objs.rotation,objs.scale};
    }


    aline::Object Scene::cull_and_clip(aline::Object objs){
        return camera.frustum.clip(camera.cull(objs));
    }



    void Scene::draw_object( const Object & o){
        std::vector<aline::Face> faces = o.shape.get_faces();
        std::vector<aline::Vertex> vertices = o.shape.get_vertices();

        for(size_t j = 0 ; j < faces.size() ; ++j){ 
            aline::Vertex v0 = vertices[(faces[j].v0)];
            aline::Vertex v1 = vertices[(faces[j].v1)];
            aline::Vertex v2 = vertices[(faces[j].v2)];

            Vec4r v04 = {v0.coordinates[0],v0.coordinates[1],v0.coordinates[2],1};
            Vec4r v14 = {v1.coordinates[0],v1.coordinates[1],v1.coordinates[2],1};
            Vec4r v24 = {v2.coordinates[0],v2.coordinates[1],v2.coordinates[2],1};


            //Object transformation (mt * v) then perspective_projection
            Vec2r v02 = perspective_projection(v04,2);
            Vec2r v12 = perspective_projection(v14,2);
            Vec2r v22 = perspective_projection(v24,2);

            Vec2i sv0 = canvas_to_window(viewport_to_canvas(v02));
            Vec2i sv1 = canvas_to_window(viewport_to_canvas(v12));
            Vec2i sv2 = canvas_to_window(viewport_to_canvas(v22));

            switch (mod){
                case Shaded:
                        draw_filled_triangle(sv0,sv1,sv2);
                        //draw_shaded_triangle(sv0,v0.color_intensity,sv1,v1.color_intensity,sv2,v2.color_intensity);
                    break;

                case Solid:
                        draw_filled_triangle(sv0,sv1,sv2);
                    break;

                case Wireframe:
                        draw_wireframe_triangle(sv0,sv1,sv2);
                    break;
            } 
        } 

    }

}
