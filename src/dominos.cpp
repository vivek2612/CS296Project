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


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
	/*! Documentation of the constructor of the dominos_t class modified to run the Rube Goldberg Machine of Group 14 \n
	 *	\b Ground \n
	 *	This describes the construction of the Ground Block of the Rube Goldberg Machine. It is the lowest possible level in the simulation. 
	 *	- b2EdgeShape shape - This describes the shape of the ground block. It is a single static edge from -90.0m to 90m in the x-coordinate and at a constant -15.0m in the y-coordinate. \n
	 *	- b2BodyDef bd - The body definition associated with the static body. 
	 *	- b2Body* b1 - The body associated with the static body Ground. It does not have a fixture as it is a static edge and is not required. \n 
	 *	<b> The Long Top Horizontal Shelf </b> \n
	 *	This describes the long horizontal shelf at the top upon which the two balls which start the simulation lie.
	 *	- b2PolygonShape shape - This describes the shape of the shelf (A box of dimensions 60.0mx0.20m)
	 * 	- b2BodyDef bd - The body definition of the shelf which is located at 0.0m along the x axis and 50.0m along the y axis.	
	 *	- b2Body* topShelf - The body object associated with the shelf. \n
	 *	<b> The Balls Responsible for Starting The Simulation </b> \n
	 *	- The falling ball from the top
	 *		- b2Body* fallingTopBall - The Body Object associated with the ball falling from the top.
	 *		- b2CircleShape circle - It is a cricle of radius 1.0m.
	 *		- b2FixtureDef bodyfd - Defines the density (200.0), friction (0.1) and restitution (0.0) of the ball.
	 *		- b2BodyDef bodybd - Body definition of the ball (Dyanmic which falls from 65m in the air) 
	 *	- The right ball (The left ball is symmetric about x = 0.0)
	 *		- b2Body* ball1 - The body object of the ball.
	 *		- b2BodyDef ball1bd - The body definition of the ball at the right (it is at 1.8m along the x axis and at 51m along the y axis)
	 *		- b2FixtureDef bodyfd - The same fixture is used for this ball as the one which collides with it except the density is 0.5f. \n
	 *	<b> The Tilted Bar Attached To The Top-Shelf </b> \n
	 *	- b2PolygonShape shape - It is a box with dimensions 4.0m and 0.2m rotated about it's end point by -45 degrees for the right side and 45 degrees for the left.
	 *	- b2BodyDef bd - It's body definition consisting of the position of the object (32.6,48.5).
	 *	- b2Body* tiltedBar - The body object associated with the tilted bar. \n
	 *	<b> The Eyebrows Of The Bull </b> \n
	 *	- b2PolygonShape shape - They are set as static boxes of dimentions (10.0x0.10f) rotated by pi/6 or -pi/6 depending which eyebrow it is
	 *	- b2BodyDef bd - The body definition of the eyebrows positioned at (32.6,48.5) for the right and (-32.6,48.5) for the left.
	 *	- b2Body* tiltedBar - The body object associated with the eyebrow. \n
	 *	<b> The Eyeballs </b> \n
	 *	- b2Body* ball or ball2 - Body objects associated with the two eyes of the bull.
	 *	- b2CircleShape circle - They are circles of radius 2.0m.
	 *	- b2BodyDef bodybd - The body definition of the eyes (they are set at (12.0,35.5) and (-12.0,35.5)).
	 *	- b2FixtureDef bodyfd - The fixtures associated with the eyeballs. \n
	 *	<b> The Shelf Attached With Tilted Bar </b> \n
	 *	The horizontal shelf which is attached to the bar at the top of the simulation through the slanted bars
	 *	- b2PolygonShape shape - The shape definition of the shelf (Box with dim 4.0x0.20)
	 *	- b2Body* shelf - Body object associated with shelf. It is a static body with no fixture definitions
	 *	- b2BodyDef bd - The body definition of the shelf positioned at (35.0,47.0) and (-35.0,47.0) for the right and left sides. \n
	 *  <b> The Vertical Revolving Bar Attached To The Shelf Described Above </b> \n
	 *	- b2PolygonShape shape2 - The shape of the vertical bar (0.2x4.0).
	 *	- b2BodyDef bd2 - Body definition of the bar positioned at (37.2,49.0) or (-37.2,49.0) for left or right sides and is a dynamic body.
	 *	- b2FixtureDef *fd - The fixture definition of the bar density  is 2.0 units.
	 *	- b2Body* shelf - The body object corresponding to the bar. \n
	 *  <b> The joint connecting the two components described above </b> \n
	 *	- b2RevoluteJointDef jointDef - The definition of the revolute joint connecting the two bodies.
	 *	- The local anchors are set on the two bodies and this gives the vertical bar the ability to rotate about the joint. \n
	 *	<b> Another Shelf </b> \n
	 *	The shelf below the components described above
	 *	- b2PolygonShape shape - The shape of the shelf (14mx0.2m)
	 *	- It is static and it is positioned at (35.0,42.5) and (-35.0,42.5) for the right and left sides respectively. \n
	 *	The Vertical Bar on the shelf that stops the two balls at the top from moving further
	 *	- b2PolygonShape shape2 - The dimensions of the bar (0.2x4.0)
	 *	- It is positioned at the end of the shelf to prevent the balls from moving further. \n
	 *	The ball on the shelf set in motion by the revolving bar described in the section preceeding. These eventually
	 *	roll into the the face of the bull.
	 *	- b2CircleShape circle - Circle of radius 1.0m
	 * 	- b2FixtureDef bodyfd - Friction, density, shape and restitution of the balls are set.
	 *	- b2BodyDef bodybd - It is a dynamic body positioned at (36.0,43.5) and (-36,43.5) for the right and left sided.
	 *	- b2Body* ball - The body object associated with the ball. \n
	 *	<b> The Three Rotatable Planks </b> \n
	 *	The three rotating the planks which interact together when one is set in motion as part of the simulation. \n
	 *	- b2PolygonShape shape - The common shape object used to determine the shapes of the three planks that interact together when rotated.
	 *	- b2RevoluteJointDef jointDef - Common joint definition for each of the three planks.
	 *	- b2BodyDef bd3 and b2BodyDef bd32 - Body definition of the invisible body used for connecting the revolute joint to the planks
	 *	- b2BodyDef bd and b2BodyDef bd2 - Body definitions of the planks to which the joints are connected.
	 *	- b2Body* body and b2Body* body2 - Actual body objects of the planks that are created in the for loop.
	 *	- b2FixtureDef *fd - Fixture definitions of the planks redefined everytime in the for loop.
	 *	- The collideConnected value is set to false because we do not want the plank to collide with the body it's connected to. \n
	 *	<b> The Path for the Ball <\b> \n
	 *	This provides a path for the ball which sets the interacting planks in motion to reach a state where they don't disturb the simulation.
	 *	This forms a part of the bull that is perceivable from the simultion. \n
	 *	- b2Body* b1 and b2 - The body objects of the two sides of the bull's face
	 *	- b2EdgeShape shape - Common edge shape object which is intially from (25.0,34.0) to (10.0,9.8) in the world frame for the right part of the face
	 *	and then goes from	(-25.0,34.0) to (-10.0,9.8) for the left part of the face.
	 *	- It is a static object and does not require any fixture object. \n
	 *	<b> The Horizontal Edge </b> \n
	 *	This forms the lowermost portion of the Bull's face \n
	 *	- b2Body* b - The Body Object.
	 *	- b2EdgeShape shape - Edge shape from (10.0,9.8) to (-10.0,9.8) 
	 *	- b2BodyDef bd - The body definition \n
	 *	<b> The Ball Placed on The Extreme Planks </b> \n
	 *	This ball is used to set the pulley in motion to collapse the dominos in the simulation. \n
	 *	- b2Body* ball and ball2 - These are the body objects of the two balls on the left and right sides of the simulation.
	 *	- b2CircleShape circle - The balls are of radius 0.5m.
	 *	- b2FixtureDef bodyfd - The fixture definition of the balls (density = 10.5, friction = 0.1 and restitution = 0.0).
	 *	- The balls are set at positions (38.5,37) and (-38.5,37) respectively. \n
	 *	<b> Triangular Wedge </b> \n
	 *	The triangular wedge which provides a path for the ball in the simulation that falls into the pulley to set the pendulum in motion. \n
	 *	- b2Body* sbody - The body object of the wedge.
	 *	- b2PolygonShape poly - Defines the shape of a wedge with vertex coordinates (-3,0), (0,0) and (0,2.5) with respect to the position body definition that defines the wedge.
	 *	- b2Vec2 vertices[] - Stores the vertices of the wedge.
	 *	- b2FixtureDef wedgefd - The fixture definition for the wedge. Inspite of the body being static, we needed to define the friction and restitution of the body which was
	 *	simplified by the usage of a fixture object.\n
	 *	<b> The Pulley Below The Wedge </b> \n
	 *	- b2BodyDef *bd - The body definition of the box that collects the ball that is described in the section above, which is placed at (32,28) and (-32,28) respectively.
	 *	- b2FixtureDef *fd1 fd2 and fd3 - The fixture definitions of the three sides of the box (the bottom, right and left sides respectively). Their densities and restitutions
	 *	are defined.
	 *	- b2Body* box1 and box12 - The body objects which correspond to the boxes on the right and left sides of the simulation.
	 *	- b2Body* box2  and box22- The plank objects on the other side of the pulley.
	 *	- b2PulleyJointDef* myjoint - Common joint definition object used for both left and right sides of the simulation. They are connected to the box and the plank.
	 *	- bcVec2 *Anchor* - Define the anchors on the body and in the world for the pulley joints. (Body anchors are in the body perspective while Ground anchors are in the world perspective). \n
	 *	<b> The revolving bar with the ball on it, which when triggered by the pulley sets the ball onto the curve. </b> \n
	 *	The ball is used to trigger the pendulum which knocks the dominos down to set the next stage of the simulation. \n
	 *	- b2PolygonShape shape - The dimensions of the bar (6.4x0.4).
	 *	- b2BodyDef bd - The body definition of the bar (It being dynamic is the only property we require).
	 *	- b2Body* body - The body object of the bar upon which the ball is placed.
	 *	- b2Body* body3 - The invisible body that is used to connect the bar at a static location in the world.
	 *	- b2BodyDef bd3 - The body definition of the invisible body which is located at (44,32.3) and (-44,32.3) for the right and left sides which coincides with the centre of the bar.
	 *	- b2RevoluteJointDef jointDef - The joint definition object that connects the invisible body and the bar together (collideConnected is set to false as we do not want the box to
	 *	rotate but only translate).
	 *	- b2Body* ball - The body object of the ball that is placed directly above the joint of the bar.
	 *	- b2CircleShape circle - The shape ball which is a circle of radius 0.5m.
	 *	- b2FixtureDef bodyfd - The fixture definition of the ball with it's attributes defined.
	 *	- b2BodyDef bodybd - The body definition of the ball which defines it's position in the world. \n
	 *	<b> The Circular Path for the Ball </b> \n
	 *	The ball falling off the revolving joint onto this curve collides with a pendulum to continue the simulation. The curve is approximated by using 11 short straight lines. \n
	 *	- b2Body * curve1 and curve2 - The body objects of the curves on the left and right sides of the simulation.
	 *	- b2EdgeShape[] shape1 and shape2 - These are the arrays that store the length and locations of each of the 11 lines used.
	 *	- b2BodyDef[] shape1bd and shape2bd - These arrays store the body definitions needed for creating each of the lines.
	 *	- b2FixtureDef[] shape1fd and shape2fd - These arrays store the fixture definitions of each of the curves (Friction and Restitution are required for these curves).
	 *	- A circular arc is created for making the path of the ball. \n
	 *	<b> The Pendulum </b> \n
	 *	The pendulum is triggered by the ball that falls on the curve and it in turn knocks down the set of dominos that follow. \n
	 *	- b2Body* ball and ball2 - The bobs of the pendulum (the body objects).
	 *	- b2CircleShape circle - The shape of the bobs at the end of the pendulum (a circle of radius 0.3m).
	 *	- b2BodyDef bodybd - The body definition of the bobs (They are dynamic and are located at (37,15.5) and (-37,15.5) for the right and left sides).
	 *	- b2FixtureDef bodyfd - The fixture definition of the bobs (the friction, density and the restitution of the bobs are set here).
	 *	- b2BodyDef bd2 - The body definition of the point where the pendulum is nailed to the wall.
	 *	- b2Body* body2 and body22 - The body objects of the invisible bodies attached to the wall from where the bobs are suspended.
	 *	- b2RevoluteJointDef jointDef - The joint definition of the joint which connects the bob of the pendulum to the nail in the wall. \n
	 *	<b> The Shelf With the Dominos </b> \n
	 *	This is the shelf upon which the dominos in the simulation lie. \n
	 *	- b2PolygonShape shape - The shape of the shelf (a box with dimensions 6.0x0.2).
	 *	- b2BodyDef bd - The body definition of the shelf, positioned at (32.0,14.8) and (-32.0,14.8) for the right and left sides of the simulation.
	 *	- b2Body* pan1 and pan2 - The body objects of the two shelves in the simulation. \n
	 *	<b> The Dominos </b> \n
	 *	These are the dominos that are set in motion by the collision with the bob of the pendulum. The last domino collides with the large sphere described
	 *	in the next section to continue the simulation. \n
	 *	- b2PolygonShape shape - This defines the shape of each domino (A box of dimensions 0.2x2.0).
	 *	- b2FixtureDef fd - The fixture definition of the 6 identical dominos (density is 10.0 and friction is 0.1).
	 *	- b2BodyDef bd - An object of b2BodyDef is created each time for each of the dominos in the simulation and represents
	 *	  the body definition of the domino currently being constructed.
	 *	- b2Body* body - The body object of the domino being constructed.
	 *	- The dominos are positioned on the shelf described in the above section. \n
	 *	<b> Slanted Path for Large Sphere </b> \n
	 *	This is the path followed by the large sphere that is triggered by the falling of the last domino. \n
	 *	- b2Body* b1 and b2 - These are the body objects corresponding to the two paths on the two sides of the simulaion.
	 *	- b2EdgeShape shape - This defines the start and end points on the path.
	 *	- b2BodyDef bd - This is the body definition required to make the path appear in the simulation.\n
	 *	<b> The Big Sphere on The Slope </b> \n
	 *	This is the sphere that uses that path described in the section before this one to fall onto the see-saw structure
	 *	and launch the light box into the air.
	 *	- b2Body* spherebody and spherebody2 - The body objects corresponding to the two spheres on the two sides of the simulation.
	 *	- b2CircleShape circle - The shape of the sphere which is a cricle of radius 2.0.
	 *	- b2FixtureDef ballfd - The fixture definition of the sphere which sets the density (15.0), friction (0) and restitution (0) of the sphere.
	 *	- b2BodyDef ballbd - The body definition of the sphere. The spheres are located at (26.0,14.8) and (-26.0,14.8) right above the path that
	 *	  they roll down. \n
	 *	<b> The See-Saw Systems </b> \n
	*/
  dominos_t::dominos_t()
  {

    //Ground
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, -15.0f), b2Vec2(90.0f, -15.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }   

    //balls at the top
    {
      // falling ball from the top
      b2Body* fallingTopBall;
      b2CircleShape circle;
      circle.m_radius = 1.0;
      
      b2FixtureDef bodyfd;
      bodyfd.shape=&circle;
      bodyfd.density=200.0f;
      bodyfd.friction=0.1f;
      bodyfd.restitution = 0.0f;
      
      b2BodyDef bodybd;
      bodybd.type = b2_dynamicBody;
      bodybd.position.Set(0.0f,65.f);
      fallingTopBall=  m_world->CreateBody(&bodybd);
      fallingTopBall->CreateFixture(&bodyfd);

      // the right ball
      b2Body* ball1;
      b2BodyDef ball1bd;
      ball1bd.type=b2_dynamicBody;
      ball1bd.position.Set(1.8f,51.f);
      ball1=m_world->CreateBody(&ball1bd);
      bodyfd.density=0.5f;
      ball1->CreateFixture(&bodyfd);

      // the left ball
      b2Body* ball2;
      ball1bd.position.Set(-1.8f,51.f);
      ball2=m_world->CreateBody(&ball1bd);
      ball2->CreateFixture(&bodyfd);
      

    }

    //Top Long horizontal shelf
    {
      b2PolygonShape shape;   
      shape.SetAsBox(30.0f, 0.10f);
	
      b2BodyDef bd;
      bd.position.Set(0.0f, 50.0f);
      b2Body* topShelf = m_world->CreateBody(&bd);
      topShelf->CreateFixture(&shape, 0.0f);
	}
	
	//tilted bar attached with the Topshelf
    {
      float pi=3.1415926;
      b2PolygonShape shape;
      shape.SetAsBox(2.0f,0.10f,b2Vec2(-1,0),-pi/4);
      b2BodyDef bd;
      bd.position.Set(32.6f, 48.5f);
      b2Body* tiltedBar= m_world->CreateBody(&bd);
      tiltedBar->CreateFixture(&shape, 0.0f);

       bd.position.Set(-32.6f, 48.5f);      
       b2Body* tiltedBar2= m_world->CreateBody(&bd);
       shape.SetAsBox(2.0f,0.10f,b2Vec2(1,0),pi/4);
       tiltedBar2->CreateFixture(&shape, 0.0f);
    }
  
  // bull's eyebrows
    {
      b2PolygonShape shape;   
      shape.SetAsBox(5.0f, 0.10f,b2Vec2(-5,0),b2_pi/6);
  
      b2BodyDef bd;
      bd.position.Set(15.0f, 40.0f);
      b2Body* topShelf = m_world->CreateBody(&bd);
      topShelf->CreateFixture(&shape, 0.0f);

      bd.position.Set(-15.0f, 40.0f);
      shape.SetAsBox(5.0f, 0.10f,b2Vec2(5,0),b2_pi-b2_pi/6);
      b2Body* topShelf2 = m_world->CreateBody(&bd);
      topShelf2->CreateFixture(&shape, 0.0f);

    }

    // eyeballs
    {
      b2Body* ball; b2Body* ball2; 
      b2CircleShape circle;
      circle.m_radius = 2;
    
      b2FixtureDef bodyfd;
      bodyfd.shape=&circle;
      
      b2BodyDef bodybd;
      bodybd.type = b2_dynamicBody;
      bodybd.gravityScale=0.0;
      bodybd.position.Set(12.0f,35.5f);
      ball=  m_world->CreateBody(&bodybd);
      ball->CreateFixture(&bodyfd);

      bodybd.position.Set(-12.0f,35.5f);
      ball2=  m_world->CreateBody(&bodybd);
      ball2->CreateFixture(&bodyfd);
    }
    
 //tilted bar attached with the Topshelf
    {
      float pi=3.1415926;
      b2PolygonShape shape;
      shape.SetAsBox(2.0f,0.10f,b2Vec2(-1,0),-pi/4);
      b2BodyDef bd;
      bd.position.Set(32.6f, 48.5f);
      b2Body* tiltedBar= m_world->CreateBody(&bd);
      tiltedBar->CreateFixture(&shape, 0.0f);

       bd.position.Set(-32.6f, 48.5f);      
       b2Body* tiltedBar2= m_world->CreateBody(&bd);
       shape.SetAsBox(2.0f,0.10f,b2Vec2(1,0),pi/4);
       tiltedBar2->CreateFixture(&shape, 0.0f);
    }

    // shelf attached with tilted bar
    {
      b2PolygonShape shape;   
      shape.SetAsBox(2.0f, 0.10f);
      b2BodyDef bd;
      bd.position.Set(35.0f, 47.0f);
      b2Body* shelf= m_world->CreateBody(&bd);
      shelf->CreateFixture(&shape, 0.0f);

      bd.position.Set(-35.0f, 47.0f);
      b2Body* shelf2= m_world->CreateBody(&bd);
      shelf2->CreateFixture(&shape, 0.0f);
  

      // the vertical bar
      b2PolygonShape shape2;
      shape2.SetAsBox(0.10f, 2.0f);

      b2BodyDef bd2;
      bd2.position.Set(37.2f, 49.0f);
      bd2.type = b2_dynamicBody;
      b2Body* verticalBar = m_world->CreateBody(&bd2);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 2.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape2;
      verticalBar->CreateFixture(fd);

      bd2.position.Set(-37.2f, 49.0f);
      b2Body* verticalBar2 = m_world->CreateBody(&bd2);
      verticalBar2->CreateFixture(fd);

      b2BodyDef bd3;
      bd3.position.Set(37.2f, 47.0f);
      b2Body* body3 = m_world->CreateBody(&bd3);

      b2RevoluteJointDef jointDef;    
      jointDef.bodyA = verticalBar;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,-2);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(& jointDef);

      bd3.position.Set(-37.2f, 47.0f);
      b2Body* body32 = m_world->CreateBody(&bd3);

      jointDef.bodyA = verticalBar2;
      jointDef.bodyB = body32;
      jointDef.localAnchorA.Set(0,-2);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(& jointDef);
    }


    {
      // Another Shelf
      b2PolygonShape shape;   
      shape.SetAsBox(7, 0.10f);
      b2BodyDef bd;
      bd.position.Set(35.0f, 42.5f);
      b2Body* shelf= m_world->CreateBody(&bd);
      shelf->CreateFixture(&shape, 0.0f);

      bd.position.Set(-35.0f, 42.5f);
      b2Body* shelf2= m_world->CreateBody(&bd);
      shelf2->CreateFixture(&shape, 0.0f);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.10,2.0);
      b2BodyDef bd2;
      bd2.position.Set(42.0f, 44.5f);
      b2Body* verticalBar= m_world->CreateBody(&bd2);
      verticalBar->CreateFixture(&shape2, 0.0f);

      bd2.position.Set(-42.0f, 44.5f);
      b2Body* verticalBar2= m_world->CreateBody(&bd2);
      verticalBar2->CreateFixture(&shape2, 0.0f);

      // ball present on this shelf
      b2Body* ball;
      b2CircleShape circle;
      circle.m_radius = 1;
    
      b2FixtureDef bodyfd;
      bodyfd.shape=&circle;
      bodyfd.density=0.5f;
      bodyfd.friction=0.1f;
      bodyfd.restitution = 0.0f;
      
      b2BodyDef bodybd;
      bodybd.type = b2_dynamicBody;
      bodybd.position.Set(36.0f,43.5f);
      ball=  m_world->CreateBody(&bodybd);
      ball->CreateFixture(&bodyfd);

      b2Body* ball2;
      bodybd.position.Set(-36.0f,43.5f);
      ball2=  m_world->CreateBody(&bodybd);
      ball2->CreateFixture(&bodyfd);
    }

    

    // the three rotatable planks
    {
      b2PolygonShape shape;   
      shape.SetAsBox(3.5f, 0.10f);
      b2BodyDef bd;
      b2BodyDef bd2;
      b2BodyDef bd3; // for invisible body with which joint has to be made
      b2BodyDef bd32;
      b2RevoluteJointDef jointDef;
      bd.type=b2_dynamicBody;
      bd2.type=b2_dynamicBody;
      for(int i=-1;i<2;i++){

        if(i==0) {shape.SetAsBox(2.6f,0.10f); bd.position.Set(35,38.5); bd3.position.Set(35,38.5); bd2.position.Set(-35,38.5); bd32.position.Set(-35,38.5); }
        if(i==1){ shape.SetAsBox(2.0f,0.10f); bd.position.Set(35+3.5,38.5-2); bd3.position.Set(35+3.5,38.5-2);bd2.position.Set(-35-3.5,38.5-2); bd32.position.Set(-35-3.5,38.5-2); }
        if(i==-1) {shape.SetAsBox(4.5f,0.10f); bd.position.Set(35-6,38.5-2);bd3.position.Set(35-6,38.5-2);bd2.position.Set(-35+6,38.5-2);bd32.position.Set(-35+6,38.5-2);}
       
        b2Body* body = m_world->CreateBody(&bd);
        b2Body* body3 = m_world->CreateBody(&bd3);

        b2Body* body2 = m_world->CreateBody(&bd2);
        b2Body* body32 = m_world->CreateBody(&bd32);

        b2FixtureDef *fd = new b2FixtureDef;
        fd->density = 3.f;
        fd->shape = new b2PolygonShape;
        fd->shape = &shape;
        body->CreateFixture(fd);
        body2->CreateFixture(fd);

        // creating joint between invisible body and plank
        jointDef.bodyA = body;
        jointDef.bodyB = body3;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(& jointDef);

        jointDef.bodyA = body2;
        jointDef.bodyB = body32;
        jointDef.localAnchorA.Set(0,0);
        jointDef.localAnchorB.Set(0,0);
        jointDef.collideConnected = false;
        m_world->CreateJoint(& jointDef);
      }     

      // the path for the ball
    {
      b2Body* b1;
      b2Body* b2;
      b2EdgeShape shape;
      shape.Set(b2Vec2(25.0f, 34.0f), b2Vec2(10.0f, 9.8f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);

      shape.Set(b2Vec2(-25.0f, 34.0f), b2Vec2(-10.0f, 9.8f));
      b2 = m_world->CreateBody(&bd);
      b2->CreateFixture(&shape, 0.0f);
    }

    // the horizontal Edge
    {
      b2Body* b;
      b2EdgeShape shape;
      shape.Set(b2Vec2(10.0f, 9.8f), b2Vec2(-10.0f, 9.8f));

      b2BodyDef bd;
      b = m_world->CreateBody(&bd);
      b->CreateFixture(&shape, 0.0f);
    }


      // ball placed on rightmost plank
      b2Body* ball;
      b2Body* ball2;
      b2CircleShape circle;
      circle.m_radius = 0.5;
      
      b2FixtureDef bodyfd;
      bodyfd.shape=&circle;
      bodyfd.density=10.5f;
      bodyfd.friction=0.1f;
      bodyfd.restitution = 0.0f;
      
      b2BodyDef bodybd;
      bodybd.type = b2_dynamicBody;
      bodybd.position.Set(35+3.5,38.5-2+0.5);
      ball=  m_world->CreateBody(&bodybd);
      ball->CreateFixture(&bodyfd);

      bodybd.position.Set(-35-3.5,38.5-2+0.5);
      ball2=  m_world->CreateBody(&bodybd);
      ball2->CreateFixture(&bodyfd);

    }


    // triangular wedge
     {
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-3,0);
      vertices[1].Set(0,0);
      vertices[2].Set(0,2.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(37.3f, 32.5f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
    }
    {
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(0,0);
      vertices[1].Set(3,0);
      vertices[2].Set(0,2.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(-37.3f, 32.5f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);
    }
    
    // pulley below wedge
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      float boxx=32, boxy=28;
      bd->position.Set(boxx,boxy);
      bd->fixedRotation = true;

      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-2), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1); 
      box1->CreateFixture(fd2); 
      box1->CreateFixture(fd3); 

      float boxx2=-32, boxy2=28;
      bd->position.Set(boxx2,boxy2);
      b2Body* box12 = m_world->CreateBody(bd);
      box12->CreateFixture(fd1);
      box12->CreateFixture(fd2);
      box12->CreateFixture(fd3);



      //The bar
      float barx=39.0,bary=29;
      bd->position.Set(barx,bary);  

      fd1->density = 30.0;    
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      float barx2=-39.0,bary2=29;
      bd->position.Set(barx2,bary2);
      b2Body* box22 = m_world->CreateBody(bd);
      box22->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(boxx, boxy); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(barx, bary); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(boxx, boxy+4); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(barx, bary+3); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);

      b2Vec2 worldAnchorOnBody12(boxx2, boxy2); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody22(barx2, bary2); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround12(boxx2, boxy2+4); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround22(barx2, bary2+3); // Anchor point for ground 2 in world axis
      myjoint->Initialize(box12, box22, worldAnchorGround12, worldAnchorGround22, box12->GetWorldCenter(), box22->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);


    }

    // the bar right to the pulley on which the ball is placed
    {
      
      b2PolygonShape shape;
      shape.SetAsBox(3.2f, 0.2f);

      float x=44, y=32.3;
       
      b2BodyDef bd;
      bd.position.Set(x,y);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);

      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2BodyDef bd3;
      bd3.position.Set(x,y);
      b2Body* body3 = m_world->CreateBody(&bd3);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);

      // reverse side
      float x2=-44, y2=32.3; 
      bd.position.Set(x2,y2);
      b2Body* body2 = m_world->CreateBody(&bd);
      body2->CreateFixture(fd);

      bd3.position.Set(x2,y2);
      b2Body* body32 = m_world->CreateBody(&bd3);

      jointDef.bodyA = body2;
      jointDef.bodyB = body32;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);


      // ball placed on this
      b2Body* ball;
      b2CircleShape circle;
      circle.m_radius = 0.5;
      
      b2FixtureDef bodyfd;
      bodyfd.shape=&circle;
      bodyfd.density=10.5f;
      bodyfd.friction=0.1f;
      bodyfd.restitution = 0.0f;
      
      b2BodyDef bodybd;
      bodybd.type = b2_dynamicBody;
      bodybd.position.Set(x,y+0.5);
      ball=  m_world->CreateBody(&bodybd);
      ball->CreateFixture(&bodyfd);

      b2Body* ball2;
      bodybd.position.Set(x2,y2+0.5);
      ball2=  m_world->CreateBody(&bodybd);
      ball2->CreateFixture(&bodyfd);

      
    }

    // the circular path (curve)
    {

      b2Body * curve1; b2Body * curve2;
      b2EdgeShape shape1[11]; b2EdgeShape shape2[11];
      b2BodyDef shape1bd[11]; b2BodyDef shape2bd[11];
      b2FixtureDef shape1fd[11]; b2FixtureDef shape2fd[11];

      float32 x1 = 39.5f; float32 y1 = 24.5f;
      float32 x2=-39.5;  float32 y2 = 24.5f;
      float32 radius = 10;

      float init_angle=b2_pi*2.0/3.0;
      float init_angle2=-b2_pi*2.0/3.0;

      for(int i = 0 ; i < 11 ; i++){
        shape1[i].Set(b2Vec2( x1+radius*sin(init_angle+i*b2_pi/30.0) , y1 + radius*cos(init_angle+i*b2_pi/30.0)) , 
          b2Vec2( x1+radius*sin(init_angle+(i+1)*b2_pi/30.0) , y1 + radius*cos(init_angle+(i+1)*b2_pi/30.0)));

        shape2[i].Set(b2Vec2( x2+radius*sin(init_angle2-i*b2_pi/30.0) , y2 + radius*cos(init_angle2-i*b2_pi/30.0)) , 
          b2Vec2( x2+radius*sin(init_angle2-(i+1)*b2_pi/30.0) , y2 + radius*cos(init_angle2-(i+1)*b2_pi/30.0)));

        shape1fd[i].friction = 0; shape2fd[i].friction = 0;
        shape1fd[i].shape = &shape1[i]; shape2fd[i].shape = &shape2[i];
        shape1fd[i].restitution = 0; shape2fd[i].restitution = 0;
        curve1 = m_world->CreateBody(&shape1bd[i]);
        curve1->CreateFixture(&shape1fd[i]);
        curve2 = m_world->CreateBody(&shape2bd[i]);
        curve2->CreateFixture(&shape2fd[i]);
      }
    }
	
	// The Pendulum
	
    {
      b2Body* ball; b2Body* ball2;
      b2CircleShape circle;
      circle.m_radius = 0.3;
      
      b2FixtureDef bodyfd;
      bodyfd.shape=&circle;
      bodyfd.density=10.5f;
      bodyfd.friction=0.1f;
      bodyfd.restitution = 0.0f;
      
      b2BodyDef bodybd;
      bodybd.type = b2_dynamicBody;
      bodybd.position.Set(37,15.5);
      ball=  m_world->CreateBody(&bodybd);
      ball->CreateFixture(&bodyfd);

      bodybd.position.Set(-37,15.5);
      ball2=  m_world->CreateBody(&bodybd);
      ball2->CreateFixture(&bodyfd);

      b2BodyDef bd2;
      bd2.position.Set(37,22);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = ball;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,6.5);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);

      bd2.position.Set(-37,22);
      b2Body* body22 = m_world->CreateBody(&bd2);
       jointDef.bodyA = ball2;
      jointDef.bodyB = body22;
      jointDef.localAnchorA.Set(0,6.5);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);

    }

    
    // shelf with dominoes
    {
      b2PolygonShape shape;   
      shape.SetAsBox(3.0f, 0.10f);
  
      b2BodyDef bd;
      bd.position.Set(32.0f, 14.8f);
      b2Body* pan1 = m_world->CreateBody(&bd);
      pan1->CreateFixture(&shape, 0.0f);

      bd.position.Set(-32.0f, 14.8f);
      b2Body* pan2 = m_world->CreateBody(&bd);
      pan2->CreateFixture(&shape, 0.0f);

    }
    
    // Shelf redirecting box
    {
    	float pi = 3.1415926;
    	b2PolygonShape rightMirror;
    	rightMirror.SetAsBox(3.464101615,0.1,b2Vec2(0,0),pi/6.0);
    	
    	b2BodyDef rightMir;
    	rightMir.position.Set(32.0f,14.8-1.732050808);
    	b2Body* rightRefl = m_world->CreateBody(&rightMir);
    	rightRefl->CreateFixture(&rightMirror,0.0f);
    	
    	b2PolygonShape leftMirror;
    	leftMirror.SetAsBox(3.464101615,0.1,b2Vec2(0,0),-pi/6.0);
    	
    	b2BodyDef leftMir;
    	leftMir.position.Set(-32.0f,14.8-1.732050808);
    	b2Body* leftRefl = m_world->CreateBody(&leftMir);
    	leftRefl->CreateFixture(&leftMirror,0.0f);
    }


    // slanted path for bigger sphere
    {
      b2Body* b1;  b2Body* b2;
      b2EdgeShape shape;
      shape.Set(b2Vec2(26.0f, 13.0f), b2Vec2(19.5f, 1.2f));
  
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);

       shape.Set(b2Vec2(-26.0f, 13.0f), b2Vec2(-19.5f, 1.2f)); 
       b2 = m_world->CreateBody(&bd);
      b2->CreateFixture(&shape, 0.0f);   
    }   


    //The big sphere on the slope
    {
      b2Body* spherebody;  b2Body* spherebody2;
  
      b2CircleShape circle;
      circle.m_radius = 2.0;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 15.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;

      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(26.0, 14.8f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);

      ballbd.position.Set(-26.0, 14.8f);
      spherebody2 = m_world->CreateBody(&ballbd);
      spherebody2->CreateFixture(&ballfd);      
    }

    // dominoes
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f); // 0.1 is width of the dominos
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 10.0f;
      fd.friction = 0.1f;
    
      for (int i = 0; i < 6; ++i){
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(29.2f + 1.0f * i, 15.8f);
        b2Body* body = m_world->CreateBody(&bd);
        body->CreateFixture(&fd);

        bd.position.Set(-29.2f - 1.0f * i, 15.8f);
        b2Body* body2 = m_world->CreateBody(&bd);
        body2->CreateFixture(&fd);
      }
    }


    // the see saw system on the right
    {
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,2.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(21.0f, -15.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      b2PolygonShape addend;
      addend.SetAsBox(0.1f,2.0f,b2Vec2(-13.0f,2.0f),0.0);
      shape.SetAsBox(13.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(21.0f, -12.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      b2FixtureDef *adFix = new b2FixtureDef;
      adFix->density = 0.1f;
      adFix->shape = &addend;
      adFix->friction = 1.0f;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      fd2->friction=1.0;
      body->CreateFixture(fd2);
      body->CreateFixture(adFix);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(21.0f, -12.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      //The light box on the right side of the see-saw

      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd3;
      bd3.position.Set(31.3f, -9.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.2f;
      fd3->friction = 1.0f;
      fd3->restitution = 0.5f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
    
    // the see saw system on the left
    {
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,2.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(-21.0f, -15.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      b2PolygonShape addend;
      addend.SetAsBox(0.1f,2.0f,b2Vec2(13.0f,2.0f),0.0);
      shape.SetAsBox(13.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(-21.0f, -12.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      b2FixtureDef *adFix = new b2FixtureDef;
      adFix->density = 0.1f;
      adFix->shape = &addend;
      adFix->friction = 1.0f;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      fd2->friction=1.0;
      body->CreateFixture(fd2);
      body->CreateFixture(adFix);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-21.0f, -12.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      //The light box on the right side of the see-saw

      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd3;
      bd3.position.Set(-31.3f, -9.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.2f;
      fd3->friction = 1.0f;
      fd3->restitution = 0.5f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }    
    
    b2Body* topOfHouse;
	// The House at the botton
	{
		float pi=3.1415926;
		
		b2FixtureDef* leftTop = new b2FixtureDef;
		b2FixtureDef* rightTop = new b2FixtureDef;
		b2PolygonShape rightTopShape;
		b2PolygonShape leftTopShape;
		leftTopShape.SetAsBox(5.0f,0.1f,b2Vec2(-3.535533906f,0),pi/4.0);
		rightTopShape.SetAsBox(5.0f,0.1f,b2Vec2(3.535533906f,0),-pi/4.0);
		leftTop->density = 0.1f;
		leftTop->friction = 0.0f;
		leftTop->restitution = 0.0f;
		leftTop->shape = new b2PolygonShape;
		rightTop->shape = new b2PolygonShape;
		leftTop->shape = &leftTopShape;
		rightTop->density = 0.1f;
		rightTop->friction = 0.0f;
		rightTop->restitution = 0.0f;
		rightTop->shape = &rightTopShape;
				
		b2BodyDef *topDef = new b2BodyDef;
		topDef->type = b2_dynamicBody;
		topDef->gravityScale = 0.0;
		topDef->position.Set (0.0f,-11.264466094f);
		
		topOfHouse = m_world->CreateBody(topDef);
		topOfHouse->CreateFixture(leftTop);
		topOfHouse->CreateFixture(rightTop);
		
		b2FixtureDef* leftBottom = new b2FixtureDef;
		b2FixtureDef* rightBottom = new b2FixtureDef;
		leftBottom->density = 0.1f;
		leftBottom->friction = 0.0f;
		leftBottom->restitution = 0.0f;
		b2PolygonShape leftBottomShape;
		leftBottomShape.SetAsBox(5.0f,0.1f,b2Vec2(5.0,0),0.0);
		rightBottom->density = 0.1f;
		rightBottom->friction = 0.0f;
		rightBottom->restitution = 0.0f;
		b2PolygonShape rightBottomShape;
		rightBottomShape.SetAsBox(5.0f,0.1f,b2Vec2(-5.0,0),0.0);
		leftBottom->shape = new b2PolygonShape;
		leftBottom->shape = &leftBottomShape;
		rightBottom->shape = new b2PolygonShape;
		rightBottom->shape = &rightBottomShape;
		
		b2BodyDef* leftBot = new b2BodyDef;
		b2BodyDef* rightBot = new b2BodyDef;
		leftBot->type = b2_dynamicBody;
		rightBot->type = b2_dynamicBody;
		leftBot->gravityScale = 1.0;
		rightBot->gravityScale = 1.0;
		leftBot->position.Set(-7.035533906f,-14.8f);
		rightBot->position.Set(7.035533906f,-14.8f);
		
		b2Body* leftBottomOfHouse = m_world->CreateBody(leftBot);
		leftBottomOfHouse->CreateFixture(leftBottom);
		b2Body* rightBottomOfHouse = m_world->CreateBody(rightBot);
		rightBottomOfHouse->CreateFixture(rightBottom);
		
		b2RevoluteJointDef leftJoint;
		b2RevoluteJointDef rightJoint;
		leftJoint.bodyA = topOfHouse;
		rightJoint.bodyA = topOfHouse;
		leftJoint.bodyB = leftBottomOfHouse;
		rightJoint.bodyB = rightBottomOfHouse;
		leftJoint.localAnchorA.Set(-7.071067812,-3.535533906);
		rightJoint.localAnchorA.Set(7.071067812,-3.535533906);
		leftJoint.localAnchorB.Set(0.0,0.0);
		rightJoint.localAnchorB.Set(0.0,0.0);
		leftJoint.collideConnected = false;
		rightJoint.collideConnected = false;
		leftJoint.enableMotor = true;
		rightJoint.enableMotor = true;
		leftJoint.maxMotorTorque = 5.0f;
		rightJoint.maxMotorTorque = 5.0f;
		m_world->CreateJoint(&leftJoint);
		m_world->CreateJoint(&rightJoint);
	}    
  // The Pulley System for hoisting the house
  	{
  		// The box on the right which acts as a counter balance to the house
  		b2Body* pulleyBoxRight;
  		{
  			b2FixtureDef* leftVert = new b2FixtureDef;
  			b2FixtureDef* rightVert = new b2FixtureDef;
	  		b2FixtureDef* centBottom = new b2FixtureDef;
	  		centBottom->density = 0.01f;
	  		rightVert->density = 0.0f;
	  		leftVert->density = 0.0f;
	  		centBottom->friction = 0.0f;
	  		rightVert->friction = 0.0f;
	  		leftVert->friction = 0.0f;
	  		centBottom->restitution = 0.0f;
	  		rightVert->restitution = 0.0f;
	  		leftVert->restitution = 0.0f;
	  		leftVert->shape = new b2PolygonShape;
	  		rightVert->shape = new b2PolygonShape;
	  		centBottom->shape = new b2PolygonShape;
	  		
	  		b2PolygonShape rightShape;
	  		rightShape.SetAsBox(0.1,2,b2Vec2(2.0,2.0),0);
	  		b2PolygonShape leftShape;
	  		leftShape.SetAsBox(0.1,2,b2Vec2(-2.0,2.0),0);
	  		b2PolygonShape centShape;
	  		centShape.SetAsBox(2.0,0.1,b2Vec2(0.0,0.0),0);
	  		
	  		rightVert->shape = &rightShape;
	  		leftVert->shape = &leftShape;
	  		centBottom->shape = &centShape;
	  		
	  		b2BodyDef* box = new b2BodyDef;
	  		box->type = b2_dynamicBody;
	  		box->gravityScale = 1.0;
	  		box->position.Set(43.0,-5.0);
	  		box->fixedRotation = true;
	  		
	  		pulleyBoxRight = m_world->CreateBody(box);
	  		pulleyBoxRight->CreateFixture(centBottom);
	  		pulleyBoxRight->CreateFixture(rightVert);
  			pulleyBoxRight->CreateFixture(leftVert);
  		}
  		
  		// The box on the left which acts as a counter balance to the house
  		b2Body* pulleyBoxLeft;
  		{
	  		b2FixtureDef* leftVert = new b2FixtureDef;
	  		b2FixtureDef* rightVert = new b2FixtureDef;
	  		b2FixtureDef* centBottom = new b2FixtureDef;
	  		centBottom->density = 0.01f;
	  		rightVert->density = 0.0f;
	  		leftVert->density = 0.0f;
	  		centBottom->friction = 0.0f;
	  		rightVert->friction = 0.0f;
	  		leftVert->friction = 0.0f;
	  		centBottom->restitution = 0.0f;
	  		rightVert->restitution = 0.0f;
	  		leftVert->restitution = 0.0f;
	  		leftVert->shape = new b2PolygonShape;
	  		rightVert->shape = new b2PolygonShape;
	  		centBottom->shape = new b2PolygonShape;
	  		
	  		b2PolygonShape rightShape;
	  		rightShape.SetAsBox(0.1,2,b2Vec2(2.0,2.0),0);
	  		b2PolygonShape leftShape;
	  		leftShape.SetAsBox(0.1,2,b2Vec2(-2.0,2.0),0);
	  		b2PolygonShape centShape;
	  		centShape.SetAsBox(2.0,0.1,b2Vec2(0.0,0.0),0);
	  		
	  		rightVert->shape = &rightShape;
	  		leftVert->shape = &leftShape;
	  		centBottom->shape = &centShape;
	  		
	  		b2BodyDef* box = new b2BodyDef;
	  		box->type = b2_dynamicBody;
	  		box->gravityScale = 1.0;
	  		box->position.Set(-43.0,-5.0);
	  		box->fixedRotation = true;
	  		
	  		pulleyBoxLeft = m_world->CreateBody(box);
	  		pulleyBoxLeft->CreateFixture(centBottom);
	  		pulleyBoxLeft->CreateFixture(rightVert);
	  		pulleyBoxLeft->CreateFixture(leftVert);
  		}
  		// The pulley joint on the right connecting the house to the counter weight
  		{
  			b2Vec2 topOfHouseAnchor(topOfHouse->GetWorldCenter().x + 3.535533906,topOfHouse->GetWorldCenter().y);
  			b2Vec2 boxAnchor = pulleyBoxRight->GetWorldCenter();
  			b2Vec2 GroundAnchor1(boxAnchor.x,0.0);
  			b2Vec2 GroundAnchor2(topOfHouseAnchor.x,0.0);
  			b2PulleyJointDef* rightJoint = new b2PulleyJointDef();
  			rightJoint->Initialize(pulleyBoxRight,topOfHouse,GroundAnchor1,GroundAnchor2,boxAnchor,topOfHouseAnchor,1.0);
  			m_world->CreateJoint(rightJoint); 
  		}
  		// The pulley joint on the left connecting the house to the counter weight
  		{
  			b2Vec2 topOfHouseAnchor(topOfHouse->GetWorldCenter().x - 3.535533906,topOfHouse->GetWorldCenter().y);
  			b2Vec2 boxAnchor = pulleyBoxLeft->GetWorldCenter();
  			b2Vec2 GroundAnchor1(boxAnchor.x,0.0);
  			b2Vec2 GroundAnchor2(topOfHouseAnchor.x,0.0);
  			b2PulleyJointDef* leftJoint = new b2PulleyJointDef();
  			leftJoint->Initialize(pulleyBoxLeft,topOfHouse,GroundAnchor1,GroundAnchor2,boxAnchor,topOfHouseAnchor,1.0);
  			m_world->CreateJoint(leftJoint); 
  		}  		
  	}
  }   
  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

