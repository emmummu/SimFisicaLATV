En este codigo se hacen varios poligonos en box 2D
Para el codigo de los poligonos mas grandes, en vez de calcular en una grafica como deberian de ir los vertices, utilizando la variable pi de Box2D y un ciclo for, se calcula el angulo de cada uno de los vertices para que esten horientados al centro.

#include "iostream"
#include <Box2d/box2d.h>
int main() {
    b2PolygonShape triangleShape;
    b2Vec2 vertices[3];
    vertices[0].Set(0.0f, 0.0f);
    vertices[1].Set(1.0f, 0.0f);
    vertices[2].Set(0.0f, 1.0f);
    triangleShape.Set(vertices, 3);

    b2PolygonShape squareShape;
    b2Vec2 v[4];
    v[0].Set(0.0f, 0.0f);
    v[1].Set(1.0f, 0.0f);
    v[2].Set(1.0f, 1.0f);
    v[3].Set(0.0f, 1.0f);
    squareShape.Set(v, 4);

 b2PolygonShape pentagonShape;
b2Vec2 vertices[5];
for (int i = 0; i < 5; ++i) {
    float angle = i * (2 * b2_pi / 5);
    vertices[i].Set(cos(angle), sin(angle));
}
pentagonShape.Set(vertices, 5);


    b2PolygonShape hexagonShape;
    b2Vec2 verticesh[6];
    for (int i = 0; i < 6; ++i) {
        float angle = i * (2 * b2_pi / 6);
        verticesh[i].Set(cos(angle), sin(angle));
    }
    hexagonShape.Set(verticesh, 6);


    b2PolygonShape octagonShape;
    b2Vec2 verticesO[8];
    for (int i = 0; i < 8; ++i) {
        float angle = i * (2 * b2_pi / 8);
        verticesO[i].Set(cos(angle), sin(angle));
    }
    octagonShape.Set(verticesO, 8);
}
