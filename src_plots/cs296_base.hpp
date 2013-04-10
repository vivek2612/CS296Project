/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{

  //! What is the difference between a class and a struct in C++? \n
  //! The default access - specifier is public for members of a struct and private for members of \n
  //! a class.
  class base_sim_t;
  struct settings_t;
  
  //! Why do we use a typedef ? \n
  //! Typedef provides a level of abstraction when writing programs. It helps abstract out the \n
  //! name of a data type to make it more intuitive and think about the function a variable  \n
  //! is supposed to peform. It also helps in maintaining code as if the definition of the variable \n
  //! change, a modification in a single location is enough to make the code work again. It allows you \n
  //! to create an alias for a data type.
  typedef base_sim_t* sim_create_fcn(); 

  //! Simulation settings. Some can be controlled in the GUI.
  //!
  
  /*!
     \brief Description of the struct settings_t()
      \section  settings_t
          This section refers to the documentation of the settings_t() \n

          This struct enables/disables various drawing modes. These modes include the modes of drawing forces, center of mass , contact normal forces
          ,pairs, joints, stats, profile etc. In addition to these drawing modes it also allows to set the graphic user interface for other things like 
          pause, view port of the window. 
            
          * - \c view_center(0.0f, 20.0f)-    center of gui as (0.0f, 20.0f) \n
          * - \c velocity_iterations(8)-    Default no of velocity iterations set to 8 \n
          * - \c position_iterations(3)-     Default no of position iterations set to 3 \n
          * - \c draw_shapes(1)-    enables drawing of shapes \n
          * - \c draw_joints(1) -     enables drawing of joints \n
          * - \c draw_AABBs(0) -     disables drawing AABBs :AABBs is axis-aligned bounding boxes \n
          * - \c draw_pairs(0) -      disables drawing pairs \n
          * - \c draw_contact_points(0)-    disable contact points from showing \n
          * - \c draw_contact_normals(0) -    disable contact normals from showing \n
          * - \c draw_contact_forces(0) -    disable friction forces from showing \n
          * - \c draw_COMs(0) -    Disable showing of COM \n
          * - \c draw_stats(0) -     disable showing statistics (no of bodies,contacts,joints,etc)  \n
          * - \c enable_continuous(1) -    for continuous evaluation of velocity,position,etc  \n
          * - \c enable_sub_stepping(0) -     disables sub stepping \n
          * - \c pause(0) -     Disables pause \n
          * - \c single_step(0) -    Disable single step which could be used to see what happens in a single step of changing position, velocity etc.  \n
    
  */
  struct settings_t
  {
    //! Notice the initialization of the class members in the constructor
    //! How is this happening? \n
    //! Initialization can take place by defining a constructor that takes arguments when \n
    //! an object of that class is defined. Arguments to the constructor are passed when the
    //! object is created by using syntax similar to that shown.
    settings_t() :
      view_center(0.0f, 20.0f),
      hz(60.0f),
      velocity_iterations(8),
      position_iterations(3),
      draw_shapes(1),
      draw_joints(1),
      draw_AABBs(0),
      draw_pairs(0),
      draw_contact_points(0),
      draw_contact_normals(0),
      draw_contact_forces(0),
      draw_friction_forces(0),
      draw_COMs(0),
      draw_stats(0),
      draw_profile(0),
      enable_warm_starting(1),
      enable_continuous(1),
      enable_sub_stepping(0),
      pause(0),
      single_step(0)
    {}
    
    b2Vec2 view_center;
    float32 hz;
    int32 velocity_iterations;
    int32 position_iterations;
    int32 draw_shapes;
    int32 draw_joints;
    int32 draw_AABBs;
    int32 draw_pairs;
    int32 draw_contact_points;
    int32 draw_contact_normals;
    int32 draw_contact_forces;
    int32 draw_friction_forces;
    int32 draw_COMs;
    int32 draw_stats;
    int32 draw_profile;
    int32 enable_warm_starting;
    int32 enable_continuous;
    int32 enable_sub_stepping;
    int32 pause;
    int32 single_step;
  };
  
  /*!
     \brief Description of the struct sim_t()
      \section  sim_t
          This section refers to the documentation of the sim_t() \n

          This struct is responsible for the creating the simulation object and starting the simulation. \n 
            
          * - \c const char *name- Name of the simulation object. \n
          * - \c create_fcn() - To start on the simulation. \n

  */
  struct sim_t
  {
    const char *name;
    sim_create_fcn *create_fcn;

    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  
  const int32 k_max_contact_points = 2048;  
  /*!
     \brief Description of the struct  contact_point_t()
      \section   contact_point_t
          This section refers to the documentation of the  contact_point_t \n 

          This struct is responsible for the defining the contact point.
          It consists of fixtures (reference) of the two bodies whose contact is to analysed \n 
            
          * - \c b2Fixture* fixtureA : Defines one of the fixture in contact  \n
          * - \c b2Fixture* fixtureB  :Defines another fixture in contact \n
          * - \c b2Vec2 normal : Defines the normal of the contact point \n
          * - \c b2Vec2 position :  Defines position of the contact point  \n
          * - \c b2PointState state : Stores state of points of contact \n
  */  
  struct contact_point_t
  {
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
  };
  /*!
     \brief Description of the class  base_sim_t()
      \section    base_sim_t 
          This section refers to the documentation of the class base_sim_t \n 

          This class has been inherited from another class b2ContactListener. It consists of some basic methods of displaying the statistics
          on the screen like setting the number of lines when showing the profile. Also it keeps the contact related information and comprises the
          callback methods for the contact events. Also, if certain keys are not used then compiler shows the warnings. In order to avoid that 
          some methods have been invoked in this class like keyboard(), keyboard_up() \n.
          Some of the variables/members of this class have been described below. \n           
          * - \c void set_text_line(int32 line) : Set the max number of lines  when showing profile or statistics \n
          * - \c void draw_title(int x, int y, const char *string) : To write the title in given x and y coordinate of a particular string \n
          * - \c virtual void step(settings_t* settings) : Function called for taking a single step with parameters as settings of the simulation \n
          * - \c void joint_destroyed : to inform that a joint has been destroyed  \n
          * - \c void begin_contact : callback for when the contact takes place \n
          * - \c void end_contact: callback for when contact ends. \n
          * - \c pre_solve(): callback for after collision detection, but before collision resolution. \n
          * - \c post_solve() : The post solve event is where you can gather collision impulse results. \n
  */  
  class base_sim_t : public b2ContactListener
  {
  public:
    
    base_sim_t();

    //! Virtual destructors - amazing objects. Why are these necessary? \n
    //! In case a pointer of the type of the parent class is used to refer to an object for the derived\n
    //! class, then it may happen that when the object is deleted, memory for the derived class may not be de \n
    //! allocated. The virtual keyword forces the program to decide the destructor based on the actual object \n
    //! being deleted.
    virtual ~base_sim_t();
    
    void set_text_line(int32 line) { m_text_line = line; }
    void draw_title(int x, int y, const char *string);
    
    virtual void step(settings_t* settings);

    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }

    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }
    inline const b2World* get_world(void) { return m_world; }

    
    // Let derived tests know that a joint was destroyed.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    // Callbacks for derived classes.
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

  //!How are protected members different from private memebers of a class in C++ ? \n
  //!Protected members are different because classes that inherit from one class can still access the protected members of the parent class
  //!but not the private members of the parent.
  protected:

    //! What are Friend classes? \n
    //! A class when declared the friend of another class in C++ has access to private and protected members of the class it has been \n
    //! declared a friend of. 
    friend class contact_listener_t;
    
    b2Body* m_ground_body;
    b2AABB m_world_AABB;
    contact_point_t m_points[k_max_contact_points];
    int32 m_point_count;

    debug_draw_t m_debug_draw;
    int32 m_text_line;
    b2World* m_world;

    int32 m_step_count;
    
    b2Profile m_max_profile;
    b2Profile m_total_profile;
  };
}

#endif
