/**
 * constants.h
 *
 * Some constants and types in Sarumawashi.
 * 
 * @author kotarot
 * @version 0.1 2014-10-16
 */

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <string>
#include <vector>

namespace Sarumawashi {

typedef char int8_t;
typedef unsigned char uint8_t;

/** Variations of corner-cubes. Orientations are not considered. */
typedef enum _TAG_CORNERS {
    UFR = 0, ULF, DRF, DFL, URB, UBL, DBR, DLB,
    NUM_OF_CORNERS
} corner_t;

/** Variations of edge-cubes. Orientations are not considered. */
typedef enum _TAG_EDGES {
    UF = 0, FR, FL, DF, UR, UL, DR, DL, UB, BR, BL, DB,
    NUM_OF_EDGES
} edge_t;

typedef struct _TAG_CORNERCUBE {
    corner_t c; // cube
    uint8_t  p; // parity
} cornercube_t;

typedef struct _TAG_EDGECUBE {
    edge_t  c; // cube
    uint8_t p; // parity
} edgecube_t;

/** Face type of a cube. */
typedef enum _TAG_FACES {
    R = 0, L, U, D, F, B,
    NUM_OF_FACES
} face_t;

/** Rotation type. Number means the count of quarter clockwise rotations. */
typedef enum _TAG_ROTATIONS {
    CW = 1, // quarter turn clockwise
    HALF,   // half turn
    CCW     // quarter turn counter-clockwise
} rotation_t;

/** Parity adjactments when showing developments. */
const int cdev[4] = {2, 1, 1, 2}; // Corners in R, L, F, B.
const int edev[4] = {1, 0, 0, 1}; // Edges in F, B,

/** Corner-parity of each face. */
const int cparity[6][4] = {
    {1, 2, 1, 2}, // R: UFR, URB, DBR, DRF
    {2, 1, 2, 1}, // L: ULF, DFL, DLB, UBL
    {0, 0, 0, 0}, // U: UFR, ULF, UBL, URB
    {0, 0, 0, 0}, // D: DRF, DBR, DLB, DFL
    {2, 1, 2, 1}, // F: UFR, DRF, DFL, ULF
    {1, 2, 1, 2}  // B: URB, UBL, DLB, DBR
};

/** Edge-parity of each face. */
const int eparity[6][4] = {
    {0, 0, 0, 0}, // R: UR, BR, DR, FR
    {0, 0, 0, 0}, // L: UL, FL, DL, BL
    {0, 0, 0, 0}, // U: UF, UL, UB, UR
    {0, 0, 0, 0}, // D: DF, DR, DB, DL
    {1, 1, 1, 1}, // F: UF, FR, DF, FL
    {1, 1, 1, 1}  // B: UB, BL, DB, BR
};

/** Corner cubes on each face in the clockwise order. */
const int8_t cornercubes[6][4][3] = {
    {{-1, -1, -1},  // R: UFR
     {-1, -1,  1},  // R: URB
     {-1,  1,  1},  // R: DBR
     {-1,  1, -1}}, // R: DRF
    {{ 1, -1, -1},  // L: ULF
     { 1,  1, -1},  // L: DFL
     { 1,  1,  1},  // L: DLB
     { 1, -1,  1}}, // L: UBL
    {{-1, -1, -1},  // U: UFR
     { 1, -1, -1},  // U: ULF
     { 1, -1,  1},  // U: UBL
     {-1, -1,  1}}, // U: URB
    {{-1,  1, -1},  // D: DRF
     {-1,  1,  1},  // D: DBR
     { 1,  1,  1},  // D: DLB
     { 1,  1, -1}}, // D: DFL
    {{-1, -1, -1},  // F: UFR
     {-1,  1, -1},  // F: DRF
     { 1,  1, -1},  // F: DFL
     { 1, -1, -1}}, // F: ULF
    {{-1, -1,  1},  // B: URB
     { 1, -1,  1},  // B: UBL
     { 1,  1,  1},  // B: DLB
     {-1,  1,  1}}, // B: DBR
};

/** Edge cubes on each face in the clockwise order. */
const int8_t edgecubes[6][4][3] = {
    {{-1, -1,  0},  // R: UR
     {-1,  0,  1},  // R: BR
     {-1,  1,  0},  // R: DR
     {-1,  0, -1}}, // R: FR
    {{ 1, -1,  0},  // L: UL
     { 1,  0, -1},  // L: FL
     { 1,  1,  0},  // L: DL
     { 1,  0,  1}}, // L: BL
    {{ 0, -1, -1},  // U: UF
     { 1, -1,  0},  // U: UL
     { 0, -1,  1},  // U: UB
     {-1, -1,  0}}, // U: UR
    {{ 0,  1, -1},  // D: DF
     {-1,  1,  0},  // D: DR
     { 0,  1,  1},  // D: DB
     { 1,  1,  0}}, // D: DL
    {{ 0, -1, -1},  // F: UF
     {-1,  0, -1},  // F: FR
     { 0,  1, -1},  // F: DF
     { 1,  0, -1}}, // F: FL
    {{ 0, -1,  1},  // B: UB
     { 1,  0,  1},  // B: BL
     { 0,  1,  1},  // B: DB
     {-1,  0,  1}}, // B: BR
};

/** Strings of corners for debugging. */
const std::string dbg_corners[NUM_OF_CORNERS + 1] = {
    "UFR", "ULF", "DRF", "DFL", "URB", "UBL", "DBR", "DLB", ""
};

/** Chars of corners for serializing. */
const char srl_corners[NUM_OF_CORNERS + 1] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', '?'
};
/** Strings of edges for debugging. */
const std::string dbg_edges[NUM_OF_EDGES + 1] = {
    "UF", "FR", "FL", "DF", "UR", "UL", "DR", "DL", "UB", "BR", "BL", "DB", ""
};
/** Chars of edges for serializing. */
const char srl_edges[NUM_OF_EDGES + 1] = {
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', '?'
};

} // end of namespace

#endif
