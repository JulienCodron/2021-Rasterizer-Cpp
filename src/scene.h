#pragma once 
#include "object.h"
#include "window.h"
#include "camera.h"
#include <fstream>


namespace aline{

    enum ViewMod {Shaded,Solid,Wireframe};
    const real Vw = 2;
    const real Vh = a*Vw;

    class Scene{
        public:

        std::vector<Object> objects;
        aline::Camera camera {a};
        minwin::Window window;
        bool running { true };
        enum ViewMod mod = Wireframe;
        minwin::Text  text1;
        minwin::Text  text2;

        //Constructs an empty scene.
        Scene();

        //Adds a shape to the scene.
        void add_object( const Object & );

        //Opens a MinWin window and sets its parameters (for instance, title and size).
        void initialise(int argc, const char * argv[]);

        /*Draws the shapes previously added to the scene on the window surface1 and process
        users inputs (e.g., click on ‘X’ to quit). It must keep the window open and showing
        the shapes until the user decides to quit the application, either by clicking on the
        button ‘X’ or via some keyboard command (e.g., ‘ESC’ or ‘Q’). It must also permit
        the user to change the “view mode” of the scene. Via some keyboard command, the
        user can change from a “wireframe” mode of the scene to a “solid” and a “shaded”
        (optional bonus feature) mode.*/
        void run();
       
        /*Closes the MinWin window and frees eventual allocated memory. (For example, if
        your function add_shape() creates a list of shapes, you must clear the list.)*/
        void shutdown();

        Camera get_camera(){return camera;}

        class QuitButtonBehavior : public minwin::IButtonBehavior
        {
            public:
            QuitButtonBehavior( Scene & scene ) : owner { scene } {}
            void on_click() const override;
            private:
            Scene & owner;
        };
        
        class QuitKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            QuitKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };
  
        class ChangeModBehavior : public minwin::IKeyBehavior
        {
            public:
            ChangeModBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class ScaleUpKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            ScaleUpKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class ScaleDownKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            ScaleDownKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

         class TranslateForwardKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            TranslateForwardKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

         class TranslateBackwardKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            TranslateBackwardKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class TranslateUpKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            TranslateUpKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class TranslateRightKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            TranslateRightKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class TranslateLeftKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            TranslateLeftKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class TranslateDownKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            TranslateDownKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class RotateXClockwiseKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            RotateXClockwiseKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class RotateXNoClockwiseKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            RotateXNoClockwiseKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class RotateYClockwiseKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            RotateYClockwiseKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class RotateYNoClockwiseKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            RotateYNoClockwiseKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class RotateZClockwiseKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            RotateZClockwiseKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };

        class RotateZNoClockwiseKeyBehavior : public minwin::IKeyBehavior
        {
            public:
            RotateZNoClockwiseKeyBehavior( Scene & scene ) : owner { scene } {}
            void on_press() const override;
            void on_release() const override;
            private:
            Scene & owner;
        };


        //drawing method

        //Draws a line from v0 to v1 using the current drawing color.
        void draw_line( const Vec2i & v0, const Vec2i & v1);

        //(optional bonus feature)
        //Draws a shaded line from v0 to v1 using the current drawing color.
        void draw_shaded_line( const Vec2i & v0, real h0, const Vec2i & v1, real h1 );

        //Draws a wireframe triangle using the current drawing color.
        void draw_wireframe_triangle( const Vec2i & v0, const Vec2i & v1, const Vec2i & v2 );

        //Draws a filled triangle using the current drawing color.
        void draw_filled_triangle( const Vec2i & v0, const Vec2i & v1, const Vec2i & v2 );

        // (optional bonus feature)
        // Draws a shaded triangle whose vertices and color intensities are given as arguments
        // using the current drawing color.  
        void draw_shaded_triangle( const Vec2i & v0, real h0, const Vec2i & v1, real h1, const Vec2i & v2, real h2 );

        //Draws an object in the scene.
        void draw_object( const Object & );

        template <typename T> int sign(T val) {return (T(0) <= val) - (val < T(0));}
    
    private :

        void load_data( int argc, const char * argv[] );

        void parse(std::string file_path); 

        aline::Object apply_object_transforms(aline::Object objs);

        aline::Object apply_camera_transforms(aline::Object objs);

        aline::Object cull_and_clip(aline::Object objs);
    };

    //Converts viewport coordinates of a point to canvas coordinates.
    Vec2r viewport_to_canvas( const Vec2r & point );
    
    //Converts canvas coordinates of a point to window (screen) coordinates.
    Vec2i canvas_to_window( const Vec2r & point );
    
    // The perspective projection of the three dimentional vector v given in homogeneous
    // coordinates. The value of d is the distance from the camera to the viewport (also
    // called projection plane).
    Vec2r perspective_projection( const Vec4r & v, real d );  

    
}
