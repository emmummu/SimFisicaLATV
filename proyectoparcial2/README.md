Simulación de una maquina de Goldberg en el cual se utilizan los Joints vistos en clase además de las librerias de SFML

## Requisitos

- SFML: Asegúrate de tener la biblioteca Simple and Fast Multimedia Library instalada en tu sistema. Puedes descargarla desde [el sitio oficial de SFML](https://www.sfml-dev.org/download.php) o instalarla utilizando un administrador de paquetes si estás utilizando un sistema operativo basado en Unix.
    
- Box2D: Necesitarás la biblioteca Box2D. Puedes descargarla desde [el repositorio oficial de Box2D en GitHub](https://github.com/erincatto/Box2D). Asegúrate de seguir las instrucciones de instalación proporcionadas en la documentación de Box2D.
    


## Sobre el codigo
el código utiliza las clases que nos proporciono el profe, con algunas modificaciones, para que se hiciera mas optimo la declaración de los constructores,
se utilizan los 10 Joints que se pidió en la asignación 
Se utilizan los joints que se pidió en la asigancion que fueron: distancia, engrane, revolucion,prismatica y polea. 


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;


class Circle {
public:
    Circle(b2World &world, float x, float y, float h,float w,float r,float density, sf::Color Color ) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        bodydef.type = b2_dynamicBody;


        body = world.CreateBody( &bodydef);
        origin = b2Vec2(x/SCALE, y/SCALE);
        b2CircleShape circle;
        circle.m_p.Set((h/2)/SCALE, (w/2)/SCALE);
        circle.m_radius = r/SCALE;

        b2FixtureDef fixturedef;
        fixturedef.shape = &circle;
        fixturedef.density = density;
        body->CreateFixture(&fixturedef);

        cir.setRadius(r);
        cir.setFillColor(sf::Color::Cyan);
        cir.setOrigin(h/2, w/2);

        cir.setFillColor(Color);
    }

    void update() {
        cir.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        cir.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(cir);
    }

    void resetPosition() {
        body->SetTransform(origin, body->GetAngle());
        body->SetLinearVelocity(b2Vec2(0,0));
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::CircleShape cir;
    b2Body *body;
    b2Vec2 origin;
};

class Cube {
public:
    Cube(b2World &world, float x, float y, bool Dynamic, float h,float w,float ang, float density,sf::Color color) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        if(Dynamic) {
            bodydef.type = b2_dynamicBody;
        }
        bodydef.angle = ang * b2_pi;
        OrgAngle = ang * b2_pi;
        body = world.CreateBody(&bodydef);
        origin = b2Vec2(x/SCALE, y/SCALE);
        b2PolygonShape shape;
        shape.SetAsBox((h / 2) / SCALE, (w / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(h, w));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(h/2, w/2);
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);

        box.setFillColor(color);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    void resetPosition() {
        body->SetTransform(origin, OrgAngle);
        body->SetLinearVelocity(b2Vec2(0,0));
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }





    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
    b2Vec2 origin;
    float OrgAngle;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "EXAMEN PARCIAL2");

    b2Vec2 gravity(0.0f, 0.01f);
    b2World world(gravity);

    Circle circulochido(world,950, 50,10,10,10,1,sf::Color::Green);

    Cube cubochido(world, 950, 80,false ,60,10,-0.05,0,sf::Color::Red);

    Cube cubochido2(world, 880, 120,false ,200,10,0,0,sf::Color::Red);
    Cube cubochido3(world, 900, 85,true,10,50,0,10.f,sf::Color::Magenta);
    Cube cubochido4(world, 850, 85,true,10,50,0,10.f,sf::Color::Magenta);
    Cube cubochido5(world, 735, 85, true,10,50,0,1.f,sf::Color::Cyan);
    Circle circulochido2(world,840, 85,10,10,10,1,sf::Color::Green);

    Cube cuboJoint2(world, 735, 15, true  ,10,10,0,0,sf::Color::Cyan);

    Cube cubochido6(world, 630,125,false,150,10,-0.05f,0,sf::Color::Red);
    Circle circulochido3(world,690, 105,10,10,10,1,sf::Color::Green);

    Cube cubo10(world, 545, 115,true,10,70,0.f,.1f,sf::Color::Red);
    Cube cubo11(world, 545, 5,true,10,10,0.f,0,sf::Color::Red);
    Cube cubo12(world, 530, 145,true,10,10,0.f,.01f,sf::Color::Red);
//Joint1
    b2RevoluteJointDef jointRev2;
    jointRev2.Initialize(cubo11.getBody(),cubo10.getBody(),cubo10.getBody()->GetWorldCenter());
    world.CreateJoint(&jointRev2);

    Cube cubo13(world, 225, 325,false,10,250,0.f,.1f,sf::Color::White);
    Cube cubo14(world, 250, 325, true,50,10,0.f,.1f,sf::Color::Red);
//joint2
    b2PrismaticJointDef prismaticJointDef;
    prismaticJointDef.Initialize(cubo13.getBody(),cubo14.getBody(),cubo13.getBody()->GetWorldCenter(),b2Vec2(0,.5f));
    prismaticJointDef.enableLimit=true;
    prismaticJointDef.lowerTranslation=-1.0f;
    prismaticJointDef.upperTranslation=4.0f;

    world.CreateJoint(&prismaticJointDef);

    Circle circulo4(world,250, 345,10,10,10,.2f,sf::Color::Green);

    Cube cubo15(world, 950, 345, true,40,40,0.f,.1f,sf::Color::Red);
//joint3
    b2DistanceJointDef distanceJointDef;
    distanceJointDef.Initialize(cubo15.getBody(),circulo4.getBody(),cubo15.getBody()->GetWorldCenter(),circulo4.getBody()->GetWorldCenter());
    world.CreateJoint(&distanceJointDef);

    //polea1
    Cube cubochido7(world, 680, 250,true,30,10,0,.1f,sf::Color::Magenta);
    Cube Punto2(world, 680, 200, true,10,10,0,1.f,sf::Color::Magenta);

    Cube cubochido8(world,600, 350, true,60,10,0,.1f,sf::Color::Magenta);
    Cube Punto(world, 600, 300, true,10,10,0,1.f,sf::Color::Blue);

    Cube cubo22(world,520, 330, false   ,90,10,-0.05f,.1f,sf::Color::Red);
    Circle circulo5(world,558,310,10,10,10,.2f,sf::Color::Green);
    Cube cubo25(world,520, 330, true,90,10,-0.05f,.1f,sf::Color::Red);
    Cube cubo23(world,445, 390,true ,50,10,0.05f,.1f,sf::Color::Red);
    Cube cubo24(world,500, 390,true,40,10,0.1f,.1f,sf::Color::Red);
    b2RevoluteJointDef reulturepolea;
    reulturepolea.Initialize(cubo23.getBody(),cubo25.getBody(),cubo23.getBody()->GetWorldCenter());
    b2RevoluteJointDef reulturepolea2;
    reulturepolea2.Initialize(cubo24.getBody(),cubo25.getBody(),cubo24.getBody()->GetWorldCenter());



   b2RevoluteJoint* revoluteJointA = (b2RevoluteJoint*)world.CreateJoint(&reulturepolea);
    b2RevoluteJoint* revoluteJointB = (b2RevoluteJoint*)world.CreateJoint(&reulturepolea2);
    b2GearJointDef gearJointDef;

   gearJointDef.bodyA=revoluteJointA->GetBodyA();
   gearJointDef.bodyB=revoluteJointB->GetBodyB();
   gearJointDef.joint2=revoluteJointA;
   gearJointDef.joint1=revoluteJointB;
    gearJointDef.ratio = 1.0f;

    world.CreateJoint(&gearJointDef);

        //polea2
    Cube cubochido16(world, 950, 750,true,80,10,0,.1f,sf::Color::Blue);

    Cube Punto3(world, 890, 400, true,10,10,0,1.f,sf::Color::Green);
    Cube cubo20(world, 890, 800, false,10,200,0.f,.1f,sf::Color::Black);
    Cube cubo21(world, 990, 800, false,10,200,0.f,.1f,sf::Color::Black);
//joint4
    b2PrismaticJointDef prismaticJointDef2;
    prismaticJointDef2.Initialize(cubo20.getBody(),cubochido16.getBody(),cubo20.getBody()->GetWorldCenter(),b2Vec2(0,.5f));
    prismaticJointDef2.enableLimit=true;
    prismaticJointDef2.lowerTranslation=-1.0f;
    prismaticJointDef2.upperTranslation=4.0f;

    world.CreateJoint(&prismaticJointDef2);

    world.CreateJoint(&prismaticJointDef2);





    Cube cubochido17(world, 80, 860, true,70,50,0,.1f,sf::Color::Green);
    Cube cubo18(world, 40, 800, false,10,200,0.f,.1f,sf::Color::Green);
    Cube cubo19(world, 125, 800, false,10,200,0.f,.1f,sf::Color::Black);
    Cube Punto4(world, 90, 700, true,10,10,0,1.f,sf::Color::Blue);


//joint5
    b2PulleyJointDef pulleyJointDef2;
    pulleyJointDef2.Initialize(cubochido16.getBody(),cubochido17.getBody(),Punto3.getBody()->GetWorldCenter(),Punto4.getBody()->GetWorldCenter(),cubochido16.getBody()->GetWorldCenter(),cubochido17.getBody()->GetWorldCenter(),1);
world.CreateJoint(&pulleyJointDef2);
    //joint6
    b2RevoluteJointDef jointRev;
    jointRev.Initialize(cuboJoint2.getBody(),cubochido5.getBody(),cuboJoint2.getBody()->GetWorldCenter());
    //Joint7
    b2PulleyJointDef pulleyJoint;
    pulleyJoint.Initialize(cubochido8.getBody(),cubochido7.getBody(),Punto.getBody()->GetWorldCenter(),Punto2.getBody()->GetWorldCenter(),cubochido8.getBody()->GetWorldCenter(),cubochido7.getBody()->GetWorldCenter(),1);

    world.CreateJoint(&jointRev);
    world.CreateJoint(&pulleyJoint);

    while (window.isOpen()) {
        sf::Event event;


        circulochido.getBody()->ApplyForceToCenter(b2Vec2(0.f,0.2f),true);
        cuboJoint2.getBody()->ApplyForceToCenter(b2Vec2(10.0f,10.0f),true);


        world.Step(1 / 60.f, 2, 3);

#pragma region update

    circulochido.update();
    circulochido2.update();
    cuboJoint2.update();
    //cube1.update();
    //cube2.update();
    cubochido3.update();
    cubochido4.update();
    circulochido3.update();
    cubochido5.update();
    cubochido7.update();
    cubochido8.update();
    cubo10.update();
    cubo12.update();
    cubo14.update();
    circulo4.update();
    cubo15.update();
    cubochido16.update();
    cubochido17.update();
    circulo5.update();
    cubo23.update();
    cubo24.update();
#pragma endregion
        window.clear();

#pragma region draw

cubochido2.draw(window);

        circulochido2.draw(window);
        cubochido5.draw(window);
        cubochido.draw(window);
        circulochido.draw(window);
        cubochido3.draw(window);
        cubochido4.draw(window);
        cubochido6.draw(window);
        circulochido3.draw(window);
        cubochido7.draw(window);
        cubochido8.draw(window);
cubo10.draw(window);
      Punto.draw(window);
       cuboJoint2.draw(window);
       cubo11.draw(window);
       cubo12.draw(window);
       cubo13.draw(window);
    cubo14.draw(window);
    Punto2.draw(window);
    cubo10.draw(window);
    circulo4.draw(window);
    cubo15.draw(window);
    cubochido16.draw(window);
    cubochido17.draw(window);
    cubo18.draw(window);
    Punto4.draw(window);
    Punto3.draw(window);
    cubo19.draw(window);
    cubo20.draw(window);
    cubo21.draw(window);
    cubo22.draw(window);
    circulo5.draw(window);
    cubo23.draw(window);
    cubo24.draw(window);
    cubo25.draw(window);
#pragma endregion
        window.display();
    }
    return 0;
}
