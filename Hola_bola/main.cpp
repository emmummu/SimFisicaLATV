#include <iostream>
#include <Box2D/Box2D.h>

int main() {
    // Configura el mundo de Box2D
    b2Vec2 gravity(0.0f, -9.81f); // Gravedad terrestre
    b2World world(gravity);

    // Crea una pelota
    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody; // Cuerpo dinámica
    b2Body* ballBody = world.CreateBody(&ballDef);

    b2CircleShape ballShape;
    ballShape.m_radius = 1.0f; // Radio de 1 metro

    b2FixtureDef ballFixtureDef;
    ballFixtureDef.shape = &ballShape;
    ballFixtureDef.density = 0.0f; // no tiene densiadad definida

    ballBody->CreateFixture(&ballFixtureDef);

    // Lanza la pelota
    float angleDegrees = 75.0f;
    float velocityKmph = 20.0f;
    float velocityMs = velocityKmph * 1000.0f / 3600.0f; // Conversión de km/h a m/s
    b2Vec2 launchVelocity(velocityMs * std::cos(angleDegrees * b2_pi / 180.0f),//cambio de grados a radianes
                          velocityMs * std::sin(angleDegrees * b2_pi / 180.0f));

    ballBody->SetLinearVelocity(launchVelocity);

    // Simula el mundo
    float timeStep = 1.0f / 1.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int32 i = 0; i < 15; ++i) {
        world.Step(timeStep, velocityIterations, positionIterations);


        b2Vec2 position = ballBody->GetPosition();
        std::cout << "Tiempo: " << i * timeStep << "s, Posicion: (" << position.x << ", " << position.y << ")" << std::endl;
    }

    return 0;
}