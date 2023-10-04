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

1. Gravedad
El código establece la gravedad en b2Vec2 gravity(0.0f, -9.81f);. Esto representa la aceleración debida a la gravedad en la dirección negativa del eje y. El valor -9.81f es una aproximación de la gravedad terrestre en metros por segundo al cuadrado (m/s²), que es una constante en la superficie de la Tierra.

2. Creación de la Pelota
Se crea una pelota como un cuerpo dinámico en Box2D utilizando b2_dynamicBody. Esto significa que la pelota responderá a las fuerzas aplicadas y experimentará cambios en su velocidad y posición en respuesta a la gravedad y otras fuerzas.

3. Lanzamiento de la Pelota
Para lanzar la pelota, se calcula su velocidad inicial en función del ángulo y la velocidad en kilómetros por hora (velocityKmph). El código realiza las siguientes conversiones matemáticas:

Convierte la velocidad de kilómetros por hora (km/h) a metros por segundo (m/s) utilizando la relación 1 m/s = 1000 km/h / 3600.

Convierte el ángulo del lanzamiento de grados a radianes multiplicando por b2_pi / 180.0f, donde b2_pi es la constante que representa el valor de π en Box2D.

Utiliza funciones trigonométricas (std::cos y std::sin) para calcular las componentes horizontal y vertical de la velocidad en función del ángulo.

Establece la velocidad inicial de la pelota mediante ballBody->SetLinearVelocity(launchVelocity).

4. Simulación del Mundo
La simulación avanza en el tiempo en pasos discretos utilizando el valor de timeStep de 1.0f / 1.0f, lo que significa que la simulación se realiza a una tasa de 1 segundo por paso. Dentro del bucle de simulación, se calcula y actualiza la posición de la pelota en función de su velocidad y la gravedad.

5. Salida de Resultados
En cada iteración del bucle de simulación, se obtiene la posición de la pelota y se imprime en la consola junto con el tiempo transcurrido.

