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
  /*! Documentation of the constructor of the dominos_t class \n
    * \b Ground \n
	* This section is used for the description of the Ground block
	* - \c b2EdgeShape shape - The Edgeshape variable "shape" is used to define the dimensions of the ground which is 180 m in length and it's y coordinate is 0. \n
	* - \c b2BodyDef bd - b2BodyDef object bd is used to define the properties of the ground. \n
	* - \c b2Body* b1 - This refers to the body object that defines the ground. \n
	
			
      	
    * \b Top \b Horizontal \b Shelf \n
	* This section describes the creation of the Horizontal shelf in the simulation
	* - \c	b2PolygonShape shape - Describes the shape of the top horizontal shelf (box 12m long and 0.50m high).\n
	* - \c b2BodyDef bd - Defines body properties of the shelf (static) and position (-31.0f, 30.0f).\n
	* - \c ground - Body object that uses the properties of the 'bd' to create a body object.
	* - \c createFixature- To create the fixature between the body and the shape. 
      			
    * \b Dominos \n
    * This section describes the dominos that rest on the top horizontal shelf
    * - \c	b2PolygonShape shape - Describes the shape of a single domino (0.2m wide and 2m tall). \n
    * - \c b2FixtureDef fd - Used for defining the properties of the fixature. Shape, density and friction     			  				are defined as the "shape" variable described above, 20.0 Kg/m^2 and friction coefficient 0.1. \n
    * - \c	b2BodyDef bd - Describes the Position of the Dominos and the nature (dynamic bodies).\n
	* - \c for loop- The for loop produces 10 dominos on the shelf spaced at the distance of 1m on the shelf.
      	
    * \b Another \b Shelf \n
    * This describes the Horizontal shelf on which the train of balls that land into the basket lie
 	* - \c b2PolygonShape shape - Defines shape of shelf (14.0m, 0.50m are Length and Height respectively),
      	   the position of the origin of the shape (-20.f,20.f) and densite 0.0 (infinity). \n
      			
    * \b Pendulum \n
    * This describes the section of the code that defines the Pendulum \n
    * - \c \bThe \b Static \b block \b below \b Pendulum \n
	* 	- \c b2Body* b2 - The static block below the pendulum \n
    * 	- \c	b2PolygonShape shape - Shape of static block below pendulum 0.5m wide and 3.0m tall. \n
    * 	- \c b2BodyDef bd - Defines properties like density of the block and adopts the shape specified by
      				the shape variable.(Density = 10.0 Kg/m^2) \n
    * - \c \bPendulum \b Bob \n
    * 	- \c b2Body* b4 - The body object defining the pendulum. \n
    * 	- \c b2PolygonShape shape - Shape of the pendulum is defined as a square of side 0.5m. \n
    * 	- \c b2BodyDef bd - Contains information about the pendulum bob (type, shape, position and 
      				density is set during the creation of the object) The position is at (-40.0m,33.0m) and 
      				the density is 2 Kg/m^2. its nature is dynamic as it will move during the simulation. \n
	* - \c \b Joint \n
	* 	- \c b2RevoluteJointDef jd -Creates the joint object which creates a joint between pendulum bob, the satic block 						through the anchor. The joint is attached to the pendulum at one end and to the block below.
	* 	- \c b2Vec2 anchor - Specifies the anchor about which the pendulum is suppposed to revolve (-37.0m,40.0m). \n
      	
    * \b Spheres \n
    * This describes the Spheres that roll into the basket \n
   	* - \c b2Body* spherebody - Body object for a sphere. \n
    * - \c b2CircleShape circle - creating the circle shape object. \n 
    * - \c circle.m_radius- Gives radius of 0.5m to the circular spheres. \n
    * - \c b2FixtureDef ballfd - the fixature object for the spheres which contains details about the shape, density, 				friction and restitution of the spheres (circle, 1.0 Kg/m^2, 0.0, 0.0). \n
    * - \c b2BodyDef ballbd - the body object for the spheres which contains information about the nature of the body 				(dynamic in this case) amongst other things. \n
	* - \c The for loop then proceeds to make 10 spheres on the shelf which are spaced at the distance of 1m. 
      	
    * \b Pulley \n
    * This section describes the pulley system in the simulation. \n
    * - \c \b Box \n	
    * 	- \c b2BodyDef *bd - Body definition for the box. It is set as a dynamic body as it has to move, it's position is specified as 				 (-10,15) and it's rotation is restricted as we don't want it rotate about the hinge but only translate. \n
	* 	- \c b2FixtureDef *fd1 - Fixture defines properties of a segment of the box like density(10.0f),
			 friction (0.5), restitution (0.f) and shape which is set to be a polygon. \n
    * 	- \c b2PolygonShape bs1 -  Defines a shape for the bar which has length 4m and height 0.4m, it's 
			initial position (0.f,-1.9f) and the angle by which it's been rotated (0). \n
	* 	- \c b2FixtureDef *fd2 - Fixture defines properties of a segment of the box like density(10.0f),
			friction (0.5), restitution (0.f) and shape which is set to be a polygon. \n
	* 	- \c b2PolygonShape bs2 -  Defines a shape for the bar which has length 0.4m and height 4m, it's 
			 initia position (2.0f,0.f) and the angle by which it's been rotated (0). \n
			 b2FixtureDef *fd3 - Fixture defines properties of a segment of the box like density(10.0f),
			 friction (0.5), restitution (0.f) and shape which is set to be a polygon. \n
    * 	- \c b2PolygonShape bs3 -  Defines a shape for the bar which has length 0.4m and height 4m, it's 
			 initia position (-2.0.f,0.f) and the angle by which it's been rotated (0). \n
			 b2Body* box1 - Utilizes data from bd to render the box on screen, \n
			 These three constitute the three sides of the box. \n
			 
    * - \c \b The \b Counter \b Balance \b (bar)
	* 	- \c b2Body* box2 - Creates counter balance using the same body definitions as bd except that density
			 has been increased to 34.0 and position has been shifted to (10,15). \n
	* - \c \b Joint \n
	* 	- \c b2PulleyJointDef* myjoint - Object which is responsible for creating the joints on the pulley.\n
	* 	- \c b2Vec2 worldAnchorOnBody1(-10, 15) - Anchor point on the Box \n
    * 	- \c b2Vec2 worldAnchorOnBody2(10, 15) - Anchor point on the Counter Balance \n
	* 	- \c b2Vec2 worldAnchorGround1(-10, 20) - Anchor point in the ground \n
	* 	- \c b2Vec2 worldAnchorGround2(10, 20) - Anchor point on the ground \n
	* 	- \c float32 ratio = 1.0f - Defines the ratio which will create the disbalance of the pulley and the two sides will 
			 start moving. \n
		
	* \b The \b Revolving \b Horizontal \b Platform \n
	* Decribes the revolving Horizontal platform \n
	* - \c b2PolygonShape shape - The shape of the platform (4.4m long and 0.4m high) \n
	* - \c b2BodyDef bd - Describes body properties of the platform (Position is (14.0m,14.0m) and it
			is a dynamic body \n
	* - \c b2Body* body - The body object of the platform borrowing properties from the 'bd'  \n
	* - \c b2FixtureDef *fd - Additional features of the platform like shape which is described above,and it's density (1.f) are described 			   here. \n
	* - \c b2PolygonShape shape2 - The shape of the hinge in the wall.(Box with length 0.4m and height	4m)  \n
	* - \c b2BodyDef bd2 - Sets position of the static body at (14.0m, 16.0m) \n
	* - \c b2Body* body2 - The body object of the hinge \n
	* - \c b2RevoluteJointDef jointDef - The two objects (the platform and the hinge) are connected with a joint. \n
	* - \c jointDef.localAnchorA: The local anchor point relative to bodyA's origin.
	* - \c jointDef.localAnchorB: The local anchor point relative to bodyA's origin. 
				
	* \b The \b Heavy \b Sphere \b on \b the \b Platform \n
	* Describes the heavy sphere on the revolving platform \n
	* - \c b2Body* sbody - The body object responsible for the sphere that eventually inherits
				properties of fixture and body. \n
	* - \c b2CircleShape circle - The radius of the sphere is 1.0m. 
	* - \c b2FixtureDef ballfd - Describes the density (50.0f), friction (0.0), restitution (0.0) and
				shape (from circle) of the sphere. \n
	* - \c b2BodyDef ballbd - Specifies position (14.0m,18.0m) and nature (dynamic) of the sphere. \n
	
	* \b The \b See-saw \b structure \b on \b the \b ground \b \n
	* This section describes the see-saw structure at the bottom of the page. \n
	* - \c b2Body* sbody - The body object for the triangular wedge \n
	* - \c b2PolygonShape poly - The shape for the traingular wedge \n
	 		b2Vec2 vertices[3] - Holds the 3 vertices for the corners of the triangular wedge. The corners
			are at (-1.0,0.0), (1.0,0.0) and (0.0,1.5). \n
	* - \c b2FixtureDef wedgefd - Sets the shape (from poly) the density (10.0), the friction (0.0) and the
			restitution (0.0) of the wedge. \n
	* - \c b2BodyDef wedgebd - Sets the position (30.0f, 0.0f). \n
	* - \c b2PolygonShape shape - Shape of the plank on the wedge (Rectangle - 30m long and 0.4m high) \n
	* - \c b2BodyDef bd2 - Set's the position (30.0m, 1.5m) and the nature (dynamic) of the plank. \n
	* - \c b2Body* body - Body object responsible for the Plank. \n
	* - \c b2FixtureDef *fd2 - Fixtures for the Plank which specify shape (from "shape"), density (1.f). \n
	* - \c b2RevoluteJointDef jd - The definition for the joint which connects it to the Plank, the Wedge
			at the anchor.\n
	* - \c b2Vec2 anchor - Specifies the point where the Plank and the Wedge are connected (30.0m, 1.5m). \n
	* - \c b2PolygonShape shape2 - Shape of the light box on the Plank (4m high and 4m wide). \n
	* - \c b2BodyDef bd3 - Sets nature and position of the box (dynamic and (40.0m, 2.0m)).\n
	* - \c b2FixtureDef *fd3 - The fixtures which define the density (0.01f) and shape (from shape2) of the box
			on the Plank. \n
*/
  dominos_t::dominos_t()
  {
    //Ground
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
      
    //Top horizontal shelf
    {
      b2PolygonShape shape;   
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
      
    //Another horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


    //The pendulum that knocks the dominos off
    {
      b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 1.5f);
	  
	b2BodyDef bd;
	bd.position.Set(-36.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.25f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-40.0f, 33.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-37.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
      
    //The train of small spheres
    {
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.5;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
    }

    //The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
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
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(10,15);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(14.0f, 16.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

    //The heavy sphere on the platform
    {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    //The see-saw system at the bottom
    {
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      //The light box on the right side of the see-saw

      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
