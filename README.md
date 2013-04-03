Oxygarum
======
My 3D-Engine


Important Structs
=====
Vertex
====
The vertex-struct is defined as vertex_t with x,y and z coordinates in double values:

typedef struct vertex {
  double x;
  double y;
  double z;
} vertex_t;

Face
====
The face-struct groups verticies to a polygon.

typedef struct face {
  vertex_id vertex_counter;
  vertex_id *vertices;
  material_id material;
} face_t;

Object
====
An object is composed of multiple faces.

typedef struct object {
  face_id face_counter;
  face_t **faces;
} object_t;

