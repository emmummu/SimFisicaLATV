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
