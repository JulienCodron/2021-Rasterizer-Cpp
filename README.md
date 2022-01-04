Autor : Codron Julien 30/11/2021
version : 4

This software implement a linear algebra library, with basique fonction for Vector and Matrix. With objective to implement a rasterizer, to display 3d object.
Only work on Linux (done on Ubuntu).

Control : 
    Camera:
    move_left  : q
    move_right : d
    move_up    : z
    move_down  : s

    rotate_x_left     : up_arrow
    rotate_x_right    : down_arrow
    rotate_y_left     : left_arrow
    rotate_y_right    : right_arrow
    rotate_z_left     : a
    rotate_z_right    : e

    Object:

    scale             : page_up
    unscale           : page_down


exemple to how compile and run the software :

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:minwin/bin
make clean
make
./bin/rasterise
obj/gourd.obj


You can test the software with different object, i give you 3 who are in the object folder. If you want to try with the teapot use unscale button (pagedown)
gourd.obj is the best object to represented in this software

IN PROGRESSE:
    clipping implemented, but not functional, a big part is done, but he didn't work. Got problem to update the barycenter of object.    

BUGS : 
 -     culling implemented, he work, but got some bugs, didn't work really well, sometimes triangle disapear to fast or to late. Don't work sometimes.
 -     filled lines dind't work well, i didn't try to implement shaded after lab2 to focus on other features. 
 -     huge bug with the clipping when you pass the near plan of the frustum
 -     rotation on camera didn't work well because of the barycenter probleme, so i did the rotation on the object. (she still implemented in commentary)



